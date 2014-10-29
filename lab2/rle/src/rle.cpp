// rle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

void ExecuteFileOperation(char* inputFilePath, char* outputFilePath, int& resultCode, void (*fileOperation) (FILE*, FILE*, int&));
void PackFile(FILE* packingFile, FILE* resultFile, int& resultCode);
void UnpackFile(FILE* unpackingFile, FILE* resultFile, int& resultCode);
bool PrintCoupleBytesToFile(FILE* file, unsigned char firstByte, unsigned char secondByte);
const char* GetErrorMessageByResultCode(int resultCode);
bool CheckFileLength(FILE* file);
bool CheckParityOfFileLength(FILE* file);

const int BYTE_MAX = 255;
const long MAX_FILE_SIZE = 2097152;

const char* PACK_OPERATION   = "pack";
const char* UNPACK_OPERATION = "unpack";
const char* HELP             = "-h";

const char* CAN_NOT_OPEN_INPUT_FILE_MESSAGE          = "Can not open input file!\n";
const char* CAN_NOT_OPEN_OUTPUT_FILE_MESSAGE         = "Can not open output file!\n";
const char* TOO_LARGE_INPUT_FILE_MESSAGE             = "Too large input file!\n";
const char* ODD_LENGTH_OF_INPUT_FILE_MESSAGE         = "Odd length of input file!\n";
const char* INPUT_FILE_INCLUDE_ZERO_SEQUENCE_MESSAGE = "Input file include zero sequence!\n";
const char* CAN_NOT_WRITE_TO_OUTPUT_FILE_MESSAGE     = "Can not write to output file\n";

enum {CAN_NOT_OPEN_INPUT_FILE_CODE, CAN_NOT_OPEN_OUTPUT_FILE_CODE, TOO_LARGE_INPUT_FILE_CODE,
      ODD_LENGTH_OF_INPUT_FILE_CODE, INPUT_FILE_INCLUDE_ZERO_SEQUENCE_CODE,                                    CAN_NOT_WRITE_TO_OUTPUT_FILE_CODE};

int main(int argc, char* argv[])
{
    if ((argc == 2) && (strcmp(HELP, argv[1]) == 0))
    {
        printf("rle.exe pack <input_file> <output_file> - for packing");
        printf("rle.exe unpack <input_file> <output_file> - for unpacking");
        return 0;
    }
    else if (argc < 4)
    {
        printf("Incorrect format of parameters! Enter -h for help");
        return 1;
    }
    
    void (*fileOperation) (FILE*, FILE*, int&);
    if (strcmp(PACK_OPERATION, argv[1]) == 0)
    {
        fileOperation = PackFile;
    }
    else if (strcmp(UNPACK_OPERATION, argv[1]) == 0)
    {
        fileOperation = UnpackFile;
    }
    else
    {
        printf("Incorrect format of parameters! Enter -h for help");
        return 1;
    }
    int resultCode = 0;
    ExecuteFileOperation(argv[2], argv[3], resultCode, fileOperation);

    if (resultCode != 0)
    {
        printf("%s", GetErrorMessageByResultCode(resultCode));
        return 1;
    }

	return 0;
}

void ExecuteFileOperation(char* inputFilePath, char* outputFilePath, int& resultCode, void (*fileOperation) (FILE*, FILE*, int&))
{
    FILE* inputFile = fopen(inputFilePath, "rb");
    FILE* outputFile  = fopen(outputFilePath, "wb");

    if ((inputFile != NULL) && (outputFile != NULL))
    {
        if (!CheckFileLength(inputFile))
        {
            resultCode = TOO_LARGE_INPUT_FILE_CODE;
        }
        else
        {
            (*fileOperation) (inputFile, outputFile, resultCode);
        }  
    }
    else if (inputFile == NULL)
    {
        resultCode = CAN_NOT_OPEN_INPUT_FILE_CODE;
    }
    else if (outputFile == NULL)
    {
        resultCode = CAN_NOT_OPEN_OUTPUT_FILE_CODE;
    }

    if (inputFile != NULL)
    {
        fclose(inputFile);
        inputFile  = NULL;
    }
    if (outputFile != NULL)
    {
        fclose(outputFile);
        outputFile = NULL;
    }
    return;
}

bool CheckFileLength(FILE* file)
{
    if (file == NULL)
    {
        return false;
    }
    fseek(file, 0, SEEK_END);
    long fileSizeBytes = ftell(file);
    fseek(file, 0, SEEK_SET);
    return (fileSizeBytes <= MAX_FILE_SIZE);
}

bool CheckParityOfFileLength(FILE* file)
{
    if (file == NULL)
    {
        return false;
    }
    fseek(file, 0, SEEK_END);
    long fileSizeBytes = ftell(file);
    fseek(file, 0, SEEK_SET);
    return (fileSizeBytes % 2 == 0);
}

void PackFile(FILE* packingFile, FILE* resultFile, int& resultCode)
{
    unsigned char previousCharacterizedByte = 0;
    unsigned char newByte = 0;
    unsigned char count = 0;
    while(fread(&newByte, sizeof(unsigned char), 1, packingFile))
    {
        if (count == 0)
        {
            previousCharacterizedByte = newByte;
        }
        else if (newByte != previousCharacterizedByte)
        {
            if (!PrintCoupleBytesToFile(resultFile, count, previousCharacterizedByte))
            {
                resultCode = CAN_NOT_WRITE_TO_OUTPUT_FILE_CODE;
                return;
            }
            previousCharacterizedByte = newByte;
            count = 0;
        }
        else
        {
            if (BYTE_MAX - count == 0)
            {
                PrintCoupleBytesToFile(resultFile, count, previousCharacterizedByte);
                count = 0;
            }
        }
        ++count;
    }

    if (count != 0)
    {
        PrintCoupleBytesToFile(resultFile, count, previousCharacterizedByte);
    }

    return;
}

bool PrintCoupleBytesToFile(FILE* file, unsigned char firstByte, unsigned char secondByte)
{
    if (file == NULL)
    {
        return false;
    }
    return (fwrite(&firstByte, sizeof(unsigned char), 1, file) &&
            fwrite(&secondByte, sizeof(unsigned char), 1, file));
}

void UnpackFile(FILE* unpackingFile, FILE* resultFile, int& resultCode)
{
    if (!CheckParityOfFileLength(unpackingFile))
    {
        resultCode = ODD_LENGTH_OF_INPUT_FILE_CODE;
        return;
    }

    unsigned char newBytes[2];
    while(fread(&newBytes, sizeof(unsigned char), 2, unpackingFile) == 2)
    {
        if (newBytes[0] == 0)
        {
            resultCode = INPUT_FILE_INCLUDE_ZERO_SEQUENCE_CODE;
            return;
        }
        for (int i = 0; i < newBytes[0]; ++i)
        {
            if (!fwrite(&newBytes[1], sizeof(unsigned char), 1, resultFile))
            {
                resultCode = CAN_NOT_WRITE_TO_OUTPUT_FILE_CODE;
                return;
            }
        }
    }
    return;
}

const char* GetErrorMessageByResultCode(int resultCode)
{
    switch(resultCode)
    {
        case CAN_NOT_OPEN_INPUT_FILE_CODE:
            return CAN_NOT_OPEN_INPUT_FILE_MESSAGE;
        case CAN_NOT_OPEN_OUTPUT_FILE_CODE:
            return CAN_NOT_OPEN_OUTPUT_FILE_MESSAGE;
        case TOO_LARGE_INPUT_FILE_CODE:
            return TOO_LARGE_INPUT_FILE_MESSAGE;
        case ODD_LENGTH_OF_INPUT_FILE_CODE:
            return ODD_LENGTH_OF_INPUT_FILE_MESSAGE;
        case INPUT_FILE_INCLUDE_ZERO_SEQUENCE_CODE:
            return INPUT_FILE_INCLUDE_ZERO_SEQUENCE_MESSAGE;
        case CAN_NOT_WRITE_TO_OUTPUT_FILE_CODE:
            return CAN_NOT_WRITE_TO_OUTPUT_FILE_MESSAGE;
    }
    return "";
}