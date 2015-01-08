// lab4-3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "File.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Incorrect format - lab4-3.exe <input_file> <output_file>" << endl;
        return 1;
    }
    CFile inputFile, outputFile;

    if (!inputFile.Open(argv[1], "r"))
    {
        cout << "Cant open input file!" << endl;
        return 1;
    }

    if (!outputFile.Open(argv[2], "w"))
    {
        cout << "Cant open output file!" << endl;
        return 1;
    }

    vector<char> buffer;
    char ch;
    while ((ch = inputFile.GetChar()) != EOF)
    {
        buffer.push_back(ch);
    }
    reverse(buffer.begin(), buffer.end());
    for(char item : buffer)
    {
        outputFile.PutChar(item);
    }
	return 0;
}

