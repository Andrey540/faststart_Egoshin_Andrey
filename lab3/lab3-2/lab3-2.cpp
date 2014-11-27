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
void TestRemoveExtraSpacesInEmptyText();
void TestRemoveExtraSpacesInNormalText();
void TestRemoveExtraSpaces();

int main(int argc, char* argv[])
{
    TestRemoveExtraSpacesInEmptyText();
    TestRemoveExtraSpacesInNormalText();
    TestRemoveExtraSpaces();

    cout << "Enter some strings, please. For end enter empty string" << endl;
    ConvertStream(cin, cout);
	return 0;
}

string RemoveExtraSpaces(string const& arg)
{
    string result = "";
    size_t whiteSpaceOffset = 0;
    size_t prevWhiteSpace   = 0;
    do
    {
        whiteSpaceOffset = arg.find(" ", prevWhiteSpace);
        size_t currentPosition = (whiteSpaceOffset == string::npos) ? arg.length() : whiteSpaceOffset;
        if (currentPosition - prevWhiteSpace != 0)
        {
            if (result.length() != 0)
            {
                result += " ";
            }
            result.append(arg ,prevWhiteSpace, currentPosition - prevWhiteSpace);
        }
        prevWhiteSpace = whiteSpaceOffset + 1;
    }while (whiteSpaceOffset != string::npos);
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

void TestRemoveExtraSpacesInEmptyText()
{
    assert(RemoveExtraSpaces("").empty() && "Algorithm error!");
    return;
}

void TestRemoveExtraSpacesInNormalText()
{
    assert(RemoveExtraSpaces("Hello world!") == "Hello world!" && "Algorithm error!");
    return;
}

void TestRemoveExtraSpaces()
{
    assert(RemoveExtraSpaces("  Hello  world!  ") == "Hello world!" && "Algorithm error!");
    return;
}