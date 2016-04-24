#include "DecoratorCreator.h"

CDecoratorCreator::CDecoratorCreator()
{
}

CDecoratorCreator::~CDecoratorCreator()
{
}

std::unique_ptr<IInputStream> CDecoratorCreator::CreateInputStream(std::vector<std::string> && parameters)
{
	if (parameters.size() == 0)
	{
		std::invalid_argument("empty parameters");
	}

	std::unique_ptr<IInputStream> inputStream = std::make_unique<CFileInputStream>(parameters.front());
	for (unsigned i = 0; i < parameters.size(); ++i)
	{
		if (parameters[i] == "--compress")
		{
			inputStream = std::make_unique<CCompressStreamDecorator>(move(inputStream));
		}
		else if (parameters[i] == "--encrypt")
		{
			if (i == parameters.size() - 1)
			{
				std::invalid_argument("invalidy parameters");
			}
			inputStream = std::make_unique<CEncryptStreamDecorator>(move(inputStream), std::stoi(parameters[++i]));
		}
		else
		{
			std::invalid_argument("uncnown parameter " + parameters[i]);
		}
	}

	return move(inputStream);
}

std::unique_ptr<IOutputStream> CDecoratorCreator::CreateOutputStream(std::vector<std::string> && parameters)
{
	if (parameters.size() == 0)
	{
		std::invalid_argument("empty parameters");
	}
	std::unique_ptr<IOutputStream> outputStream = std::make_unique<CFileOutputStream>(parameters.front());
	for (unsigned i = 0; i < parameters.size(); ++i)
	{
		if (parameters[i] == "--decrypt")
		{
			if (i == parameters.size() - 1)
			{
				std::invalid_argument("invalidy parameters");
			}			
			outputStream = std::make_unique<CDecryptStreamDecorator>(move(outputStream), std::stoi(parameters[++i]));
		}
		else if (parameters[i] == "--decompress")
		{			
			outputStream = std::make_unique<CDecompressStreamDecorator>(move(outputStream));
		}
		else
		{
			std::invalid_argument("uncnown parameter " + parameters[i]);
		}
	}

	return move(outputStream);
}
