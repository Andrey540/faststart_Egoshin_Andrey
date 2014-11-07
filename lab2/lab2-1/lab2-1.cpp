// lab2-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <functional>

using namespace std;

typedef function<void(int lineIndex)> SearchResultHandler;

bool SearchStringsInFile(ifstream &sourceFile, string const& searchString, SearchResultHandler const& handler = SearchResultHandler());
void PrintHelp();
string ReadString(ifstream& file);

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Incorrect format!" << endl;
        PrintHelp();
        return 1;
    }

    ifstream sourceFile(argv[1]);

    if (sourceFile.is_open())
    {
        if (!(SearchStringsInFile(sourceFile, argv[2], [](int lineIndex){
            cout << lineIndex << endl;
        })))
        {
            cout << "Text not found!" << endl;
            return 1;
        }
    }
    else
    {
        cout << "Can not open file!" << endl;
        return 1;
    }

	return 0;
}

bool SearchStringsInFile(ifstream &sourceFile, string const& searchString, SearchResultHandler const& handler)
{
    int nLine = 1;
    int count = 0;
    while(!sourceFile.eof())
    {
        string newString = ReadString(sourceFile);

        if (newString.find(searchString) != string::npos && handler)
        {
            handler(nLine);
            ++count;
        }

        ++nLine;
    }

    return count != 0;
}

void PrintHelp()
{
    cout << "Correct format - findtext.exe <input_file> <searching_string>" << endl;
    return;
}

string ReadString(ifstream& file)
{
    string str;
    getline(file, str);
    return str;
}