// crypt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdexcept>
#include <optional.hpp>
#include <functional>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

#define exception std::exception
     
using namespace std;
using namespace boost;

void ExecuteFileOperation(char* inputFilePath, char* outputFilePath, void (*fileOperation) (ifstream&, ofstream&, const unsigned char), const unsigned char key);
void EncryptFile(ifstream& inputFile, ofstream& outputFile, const unsigned char key);
void DecryptFile(ifstream& inputFile, ofstream& outputFile, const unsigned char key);
unsigned char ShuffleByte(unsigned char byte);
unsigned char UnShuffleByte(unsigned char byte);
void GetBitsFromByte(unsigned char byte, int* bits);
void GetByteFromBits(unsigned char &byte, int* bits);
optional<int> GetKey(string const& str);
optional<int> ReadIntValue(string const& prompt, function<void(int value)> validate);
void PrintHelp();

const char* ENCRYPT_OPERATION = "crypt";
const char* DECRYPT_OPERATION = "decrypt";

const int BYTE_MAX = 255;
const long MAX_FILE_SIZE = 2097152;

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        PrintHelp();
        return 1;
    }

    void (*fileOperation) (ifstream&, ofstream&, const unsigned char);
    if (strcmp(ENCRYPT_OPERATION, argv[1]) == 0)
    {
        fileOperation = EncryptFile;
    }
    else if (strcmp(DECRYPT_OPERATION, argv[1]) == 0)
    {
        fileOperation = DecryptFile;
    }
    else
    {
        PrintHelp();
        return 1;
    }

    try
    {
        string strKey(argv[4]);
        optional<int> key = GetKey(strKey);
        ExecuteFileOperation(argv[2], argv[3], fileOperation, (unsigned char)key.get());    
    }
    catch (exception const& e)
    {
        cout << e.what();
        return 1;
    }
    return 0;
}

void ExecuteFileOperation(char* inputFilePath, char* outputFilePath, void (*fileOperation) (ifstream&, ofstream&, const unsigned char), const unsigned char key)
{
    ifstream inputFile(inputFilePath, ios::binary);
    ofstream outputFile(outputFilePath, ios::binary);

    if ((inputFile.is_open()) && (outputFile.is_open()))
    {
        if (inputFile.tellg() > MAX_FILE_SIZE)
        {
            throw domain_error("Too large input file!");
        }
        (*fileOperation) (inputFile, outputFile, key);
    }

    if (inputFile.is_open())
    {
        inputFile.close();
    }
    else
    {
        throw domain_error("Can not open input file!");
    }
    if (outputFile.is_open())
    {
        outputFile.close();
    }
    else
    {
        throw domain_error("Can not open output file!");
    }
    return;
}

void EncryptFile(ifstream& inputFile, ofstream& outputFile, const unsigned char key)
{
    while(!inputFile.eof())
    {
        unsigned char byte = 0;
        inputFile.read(reinterpret_cast<char *>(&byte), sizeof(unsigned char));
        byte ^= key;
        byte = ShuffleByte(byte);
        if (!inputFile.eof())
        {
            outputFile.write(reinterpret_cast<char *>(&byte), sizeof(unsigned char));
        }
    }
    return;
}

void DecryptFile(ifstream& inputFile, ofstream& outputFile, const unsigned char key)
{
    while(!inputFile.eof())
    {
        unsigned char byte = 0;
        inputFile.read(reinterpret_cast<char *>(&byte), sizeof(unsigned char));
        byte = UnShuffleByte(byte);
        byte ^= key;    
        if (!inputFile.eof())
        {
            outputFile.write(reinterpret_cast<char *>(&byte), sizeof(unsigned char));
        }
    }
    return;

}

unsigned char ShuffleByte(unsigned char byte)
{
    int bits[8];
    GetBitsFromByte(byte, (int*)bits);
    int shuffleBits[8];

    shuffleBits[0] = bits[5];
    shuffleBits[1] = bits[6];
    shuffleBits[2] = bits[0];
    shuffleBits[3] = bits[1];
    shuffleBits[4] = bits[2];
    shuffleBits[5] = bits[7];
    shuffleBits[6] = bits[3];
    shuffleBits[7] = bits[4];

    GetByteFromBits(byte, (int*)bits);

    return byte;
}

unsigned char UnShuffleByte(unsigned char byte)
{
    int bits[8];
    GetBitsFromByte(byte, (int*)bits);
    int unShuffleBits[8];

    unShuffleBits[0] = bits[2];
    unShuffleBits[1] = bits[3];
    unShuffleBits[2] = bits[4];
    unShuffleBits[3] = bits[6];
    unShuffleBits[4] = bits[7];
    unShuffleBits[5] = bits[0];
    unShuffleBits[6] = bits[1];
    unShuffleBits[7] = bits[5];

    GetByteFromBits(byte, (int*)bits);

    return byte;
}

void GetBitsFromByte(unsigned char byte, int* bits)
{
   for (int i = 0; i < 8; ++i)
   {
       bits[i] = (byte & (1 << i)) != 0;       
   }
}

void GetByteFromBits(unsigned char &byte, int* bits)
{
   byte = 0;
   for (int i = 0; i < 8; ++i)
   {
       byte += bits[i] * (1 << i);
   }
}

optional<int> GetKey(string const& str)
{
    optional<int> key;
    key = ReadIntValue(str, [](int value){
        if ((value < 0) || (value >= BYTE_MAX))
        {
            throw domain_error("Key must be greater than 0 and less than 255");
        }
    });
    return key;
}

optional<int> ReadIntValue(string const& str, function<void(int value)> validate)
{
    try
    {
        int value = stoi(str);
        validate(value);
        return value;
    }
    catch (invalid_argument const&)
    {
        throw domain_error("Key must be a number");
    }
}

void PrintHelp()
{
    printf("crypt.exe crypt <input_file> <output_file> <key>- for encrypt\n");
    printf("crypt.exe decrypt <input_file> <output_file> <key>- for decrypt\n");
    return;
}