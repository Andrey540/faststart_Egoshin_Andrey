// lab2-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int SearchEntries(ifstream& sourceFile, string searchingExp);
string ReadString(ifstream& file);

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("Parameters are empty!");
        return 1;
    }
    else if (argc == 2)
    {
        printf("Searching word is empty!");
        return 1;
    }

    ifstream sourceFile(argv[1]);

    if (sourceFile.is_open())
    {
        string searchingString(argv[2], strlen(argv[2]));        
        if (SearchEntries(sourceFile, searchingString) == 1)
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

int SearchEntries(ifstream& sourceFile, string searchingExp)
{
    int nLine = 1;
    int count = 0;
    while(!sourceFile.eof())
    {
        string newString = ReadString(sourceFile);

        if (newString.find(searchingExp) != -1)
        {
            printf("%d\n", nLine);
            count++;
        }

        nLine++;
    }

    if (count == 0)
    {
        return 1;
    }

    return 0;
}

string ReadString(ifstream& file)
{
    string str;
    getline(file, str);
    return str;
}