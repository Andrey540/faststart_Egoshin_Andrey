#include "DecoratorCreator.h"



int main(int argc, char ** argv)
{
	if (argc < 5)
	{
		std::cout << "Empty parameters" << std::endl;
		return 1;
	}
	
	std::vector<std::string> parameters;
	for (unsigned i = 1; i < argc; ++i)
	{
		parameters.push_back(std::string(argv[i]));
	}
	if (parameters[0] != "input" && parameters[0] != "output")
	{
		std::cout << "Wrong parameters" << std::endl;
		return 1;
	}

	std::vector<std::string> inputStreamParameters;
	std::vector<std::string> outputStreamParameters;
	bool isInputParameters = parameters[0] == "input";
	for (unsigned it = 1; it < parameters.size(); ++it)
	{
		if (parameters[it] == "input")
		{
			isInputParameters = true;
			continue;
		}
		if (parameters[it] == "output")
		{
			isInputParameters = false;
			continue;
		}
		if (isInputParameters)
		{
			inputStreamParameters.push_back(parameters[it]);
		}
		else
		{
			outputStreamParameters.push_back(parameters[it]);
		}
	}
	
	if (inputStreamParameters.size() == 0 || outputStreamParameters.size() == 0)
	{
		std::cout << "Wrong parameters" << std::endl;
		return 1;
	}

	CDecoratorCreator decoratorCreator;
	auto fileInputStream = decoratorCreator.CreateInputStream(move(inputStreamParameters));
	auto fileOutputStream = decoratorCreator.CreateOutputStream(move(outputStreamParameters));

	uint8_t bytes[100];
	std::streamsize readSize = 0;
	do
	{
		readSize = fileInputStream->ReadBlock(bytes, 100);
		fileOutputStream->WriteBlock(bytes, readSize);
	} while (readSize > 0);

	return 0;
}