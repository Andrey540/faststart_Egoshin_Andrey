// lab2-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

bool SearchEntries(ifstream& sourceFile, string const& searchingExp);
void PrintHelp();
string ReadString(ifstream& file);

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Incorrect format!");
        PrintHelp();
        return 1;
    }

    ifstream sourceFile(argv[1]);

    if (sourceFile.is_open())
    {
        string searchingString(argv[2]);        
        if (!SearchEntries(sourceFile, searchingString))
        {
            sourceFile.close();
            printf("Text not found\n");
            return 1;
        }
        sourceFile.close();
    }
    else
    {
        printf("Can not open file!");
        return 1;
    }

	return 0;
}

bool SearchEntries(ifstream& sourceFile, string const& searchingExp)
{
    int nLine = 1;
    int count = 0;
    while(!sourceFile.eof())
    {
        string newString = ReadString(sourceFile);

        if (newString.find(searchingExp) == std::string::npos)
        {
            printf("%d\n", nLine);
            ++count;
        }

        ++nLine;
    }

    if (count == 0)
    {
        return false;
    }

    return true;
}

void PrintHelp()
{
    printf("Correct format - findtext.exe <input_file> <searching_string>");
    return;
}

string ReadString(ifstream& file)
{
    string str;
    getline(file, str);
    return str;
}