// lab3-2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <assert.h>
#include <iostream>
#include <assert.h>

using namespace std;

string RemoveExtraSpaces(string const& arg);
void ConvertStream(istream& inputStream, ostream& outputStream);

int main(int argc, char* argv[])
{
    assert(RemoveExtraSpaces("  Hello  world!  ") == "Hello world!", "Algorithm error!");
    assert(RemoveExtraSpaces("Some  humans think,  that  world...  ") == "Some humans think, that world...", "Algorithm error!");
    cout << "Enter some strings, please. For end enter empty string" << endl;
    ConvertStream(cin, cout);
	return 0;
}

string RemoveExtraSpaces(string const& arg)
{
    string str = arg;
    string result = "";
    size_t whiteSpaceOffset = str.find(" ");
    while (whiteSpaceOffset != string::npos)
    {
        if (whiteSpaceOffset == 0)
        {
            str.erase(0, 1);
        }
        else
        {
            if (result.length() != 0)
            {
                result += " ";
            }
            result += str.substr(0, whiteSpaceOffset);
            str.erase(0, whiteSpaceOffset);
        }
        whiteSpaceOffset = str.find(" ");
    }
    return result;
}

void ConvertStream(istream& inputStream, ostream& outputStream)
{
    string newString;
    do
	{
		getline(cin, newString);
		if (!newString.empty())
		{
			outputStream << RemoveExtraSpaces(newString);
		}
	}while(!newString.empty());
}