// rle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <functional>

using namespace::std;

typedef enum {
    NO_ERROR,
    CAN_NOT_OPEN_INPUT_FILE,
    CAN_NOT_OPEN_OUTPUT_FILE,
    TOO_LARGE_INPUT_FILE,
    ODD_LENGTH_OF_INPUT_FILE,
    INPUT_FILE_INCLUDE_ZERO_SEQUENCE,
    CAN_NOT_WRITE_TO_OUTPUT_FILE
} ErrorCode;

typedef struct
{
   unsigned char counter;
   unsigned char value;
} RlePacket;

ErrorCode ExecuteFileOperation(char* inputFilePath, char* outputFilePath, function<ErrorCode(ifstream& inputFile, ofstream& outputFile)> fileOperation);
ErrorCode PackFile(ifstream& inputFile, ofstream& outputFile);
ErrorCode UnpackFile(ifstream& inputFile, ofstream& outputFile);
unsigned long long GetFileLength(ifstream& file);
const string GetErrorMessageByResultCode(ErrorCode& resultCode);

const int BYTE_MAX = 255;
const unsigned long long MAX_FILE_SIZE = 2147483648;

const string PACK_OPERATION   = "pack";
const string UNPACK_OPERATION = "unpack";
const string HELP             = "-h";

const string CAN_NOT_OPEN_INPUT_FILE_MESSAGE          = "Can not open input file!";
const string CAN_NOT_OPEN_OUTPUT_FILE_MESSAGE         = "Can not open output file!";
const string TOO_LARGE_INPUT_FILE_MESSAGE             = "Too large input file!";
const string ODD_LENGTH_OF_INPUT_FILE_MESSAGE         = "Odd length of input file!";
const string INPUT_FILE_INCLUDE_ZERO_SEQUENCE_MESSAGE = "Input file include zero sequence!";
const string CAN_NOT_WRITE_TO_OUTPUT_FILE_MESSAGE     = "Can not write to output file";

int main(int argc, char* argv[])
{
    if ((argc == 2) && HELP == argv[1])
    {
        cout << "rle.exe pack <input_file> <output_file> - for packing" << endl;
        cout << "rle.exe unpack <input_file> <output_file> - for unpacking" << endl;
        return 0;
    }
    else if (argc < 4)
    {
        cout << "Incorrect format of parameters! Enter -h for help" << endl;
        return 1;
    }
    
    function<ErrorCode(ifstream& inputFile, ofstream& outputFile)> fileOperation;
    if (PACK_OPERATION == argv[1])
    {
        fileOperation = PackFile;
    }
    else if (UNPACK_OPERATION == argv[1])
    {
        fileOperation = UnpackFile;
    }
    else
    {
        cout << "Incorrect format of parameters! Enter -h for help" << endl;
        return 1;
    }

    ErrorCode resultCode = ExecuteFileOperation(argv[2], argv[3], fileOperation);
    if (resultCode != NO_ERROR)
    {
        cout << GetErrorMessageByResultCode(resultCode);
        return 1;
    }

	return 0;
}

ErrorCode ExecuteFileOperation(char* inputFilePath, char* outputFilePath, function<ErrorCode(ifstream& inputFile, ofstream& outputFile)> fileOperation)
{
    ifstream inputFile(inputFilePath, ios::binary);
    ofstream outputFile(outputFilePath, ios::binary);
    ErrorCode resultCode = NO_ERROR;

    if ((inputFile.is_open()) && (outputFile.is_open()))
    {
        if (GetFileLength(inputFile) > MAX_FILE_SIZE)
        {
            resultCode = TOO_LARGE_INPUT_FILE;
        }
        else
        {
            resultCode = fileOperation(inputFile, outputFile);
        }  
    }
    else if (!inputFile.is_open())
    {
        resultCode = CAN_NOT_OPEN_INPUT_FILE;
    }
    else if (!outputFile.is_open())
    {
        resultCode = CAN_NOT_OPEN_OUTPUT_FILE;
    }

    if (outputFile.is_open())
    {
        outputFile.close();
    }
    return resultCode;
}

ErrorCode PackFile(ifstream& inputFile, ofstream& outputFile)
{
    RlePacket rlePacket;
    
    rlePacket.counter = 0;
    while(!inputFile.eof())
    {
        unsigned char newByte = 0;
        inputFile.read(reinterpret_cast<char *>(&newByte), sizeof(unsigned char));
        if (inputFile.eof())
        {
            break;
        }
    
        if (rlePacket.counter == 0)
        {
            rlePacket.value = newByte;
        }
        else if (newByte != rlePacket.value)
        {
            outputFile.write(reinterpret_cast<char *>(&rlePacket), sizeof(rlePacket));
            rlePacket.value = newByte;
            rlePacket.counter = 0;
        }
        else if (BYTE_MAX - rlePacket.counter == 0)
        {
            outputFile.write(reinterpret_cast<char *>(&rlePacket), sizeof(rlePacket));
            rlePacket.counter = 0;
        }
        ++rlePacket.counter;
    }

    if (rlePacket.counter != 0)
    {
        outputFile.write(reinterpret_cast<char *>(&rlePacket), sizeof(rlePacket));
    }

    return NO_ERROR;
}

ErrorCode UnpackFile(ifstream& inputFile, ofstream& outputFile)
{
    if (GetFileLength(inputFile) % 2 != 0)
    {
        return ODD_LENGTH_OF_INPUT_FILE;
    }
    
    while(!inputFile.eof())
    {
        RlePacket rlePacket;
        inputFile.read(reinterpret_cast<char *>(&rlePacket), sizeof(rlePacket));
        if (inputFile.eof())
        {
            break;
        }

        if (rlePacket.counter == 0)
        {
            return INPUT_FILE_INCLUDE_ZERO_SEQUENCE;
        }
        for (int i = 0; i < rlePacket.counter; ++i)
        {
            if (!outputFile.write(reinterpret_cast<char *>(&rlePacket.value), sizeof(unsigned char)))
            {
                return CAN_NOT_WRITE_TO_OUTPUT_FILE;
            }
        }
    }
    return NO_ERROR;
}

unsigned long long GetFileLength(ifstream& file)
{
    file.seekg (0, std::ios::end);
    unsigned long long size = file.tellg();
    file.seekg (0, std::ios::beg);
    return size;
}

const string GetErrorMessageByResultCode(ErrorCode& resultCode)
{
    switch(resultCode)
    {
        case CAN_NOT_OPEN_INPUT_FILE:
            return CAN_NOT_OPEN_INPUT_FILE_MESSAGE;
        case CAN_NOT_OPEN_OUTPUT_FILE:
            return CAN_NOT_OPEN_OUTPUT_FILE_MESSAGE;
        case TOO_LARGE_INPUT_FILE:
            return TOO_LARGE_INPUT_FILE_MESSAGE;
        case ODD_LENGTH_OF_INPUT_FILE:
            return ODD_LENGTH_OF_INPUT_FILE_MESSAGE;
        case INPUT_FILE_INCLUDE_ZERO_SEQUENCE:
            return INPUT_FILE_INCLUDE_ZERO_SEQUENCE_MESSAGE;
        case CAN_NOT_WRITE_TO_OUTPUT_FILE:
            return CAN_NOT_WRITE_TO_OUTPUT_FILE_MESSAGE;
    }
    return "";
}