#include <iostream>
#include <string>
#include <cstdint>
#include "FileInputStream.h"
#include "FileOutputStream.h"

int main(int argc, char ** argv)
{
	if (argc < 3)
	{
		std::cout << "Empty parameters" << std::endl;
		return 1;
	}

	std::string inputFile(argv[1]);
	std::string outputFile(argv[2]);
	CFileInputStream fileInput(inputFile);
	CFileOutputStream fileOutput(outputFile);
	while (!fileInput.IsEOF())
	{
		uint8_t byte = fileInput.ReadByte();
		std::cout << byte << std::endl;
		fileOutput.WriteByte(byte);
	}

	return 0;
}