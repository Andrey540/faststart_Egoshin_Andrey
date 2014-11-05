// crypt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdexcept>
#include <boost\optional.hpp>
#include <functional>
#include <string>
#include <iostream>
#include <fstream>
     
using namespace boost;
using namespace std;

void CodeFile(char* inputFilePath, char* outputFilePath, function <unsigned char(const unsigned char byte, const unsigned char key)> byteOperation, const unsigned char key);
unsigned char EncryptByte(const unsigned char byte, const unsigned char key);
unsigned char DecryptByte(const unsigned char byte, const unsigned char key);
optional<int> GetKey(string const& str);
optional<int> ReadIntValue(string const& prompt, function<void(int value)> validate);
void PrintHelp();

const string ENCRYPT_OPERATION = "crypt";
const string DECRYPT_OPERATION = "decrypt";

const int BYTE_MAX = 255;

int main(int argc, char* argv[])
{
    assert(CHAR_BIT == 8. "Incorrect platform char size");
    if (argc != 5)
    {
        PrintHelp();
        return 1;
    }

    void (*fileOperation) (ifstream&, ofstream&, const unsigned char);
    function <unsigned char(const unsigned char byte, const unsigned char key)> byteOperation;
    if (ENCRYPT_OPERATION == argv[1])
    {
        byteOperation = EncryptByte;
    }
    else if (DECRYPT_OPERATION == argv[1])
    {
        byteOperation = DecryptByte;
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
        CodeFile(argv[2], argv[3], byteOperation, (unsigned char)key.get());
    }
    catch (std::exception const& e)
    {
        cout << e.what();
        return 1;
    }
    return 0;
}

void CodeFile(char* inputFilePath, char* outputFilePath, function <unsigned char(const unsigned char byte, const unsigned char key)> byteOperation, const unsigned char key)
{
    ifstream inputFile(inputFilePath, ios::binary);
    ofstream outputFile(outputFilePath, ios::binary);

    if ((inputFile.is_open()) && (outputFile.is_open()))
    {
        while(!inputFile.eof())
        {
            unsigned char byte = 0;
            inputFile.read(reinterpret_cast<char *>(&byte), sizeof(byte));
            byte = byteOperation(byte, key);
            if (!inputFile.eof())
            {
                outputFile.write(reinterpret_cast<char *>(&byte), sizeof(byte));
            }
        }
    }

    if (!inputFile.is_open())
    {
        throw runtime_error("Can not open input file!");
    }
    if (outputFile.is_open())
    {
        outputFile.close();
    }
    else
    {
        throw runtime_error("Can not open output file!");
    }
    return;
}

unsigned char EncryptByte(const unsigned char byte, const unsigned char key)
{
    unsigned char decryptBye = byte ^ key;    
    return
        ((decryptBye & 96)  >> 5) | // 6,7 bits => 1,2 bits
        ((decryptBye & 7)   << 2) | // 1,2,3 bits => 3,4,5 bits
        ((decryptBye & 24)  << 3) | // 4,5 bits => 7,8 bits
        ((decryptBye & 128) >> 2);  // 8 bit => 6 bit
}

unsigned char DecryptByte(unsigned char byte, const unsigned char key)
{
    unsigned char decryptBye =
        ((byte & 28)  >> 2) | // 3,4,5 bits => 1,2,3 bits
        ((byte & 192) >> 3) | // 7,8 bits => 4,5 bits
        ((byte & 3)   << 5) | // 1,2 bits => 6,7 bits
        ((byte & 32)  << 2);  // 6 bit => 8 bit
    return decryptBye ^= key;
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
    cout << "crypt.exe crypt <input_file> <output_file> <key>- for encrypt" << endl;
    cout << "crypt.exe decrypt <input_file> <output_file> <key>- for decrypt" << endl;
    return;
}