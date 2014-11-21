// lab3-3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <iterator>
#include <assert.h>

using namespace std;

void CalculateRepeatedWords(istream& inputStream, map<string, int>& repeatedWords);
void PrintRepeatedWords(ostream& outputStream, map<string, int>& repeatedWords);
void TestCalculateRepeatedWordsInEmptyString();
void TestCalculateRepeatedWords();

int main(int argc, char* argv[])
{
    TestCalculateRepeatedWordsInEmptyString();
    TestCalculateRepeatedWords();

    cout << "Enter some strings, please. For end enter sign end of file" << endl;
    map<string, int> repeatedWords;
    CalculateRepeatedWords(cin, repeatedWords);
    PrintRepeatedWords(cout, repeatedWords);
	return 0;
}

void CalculateRepeatedWords(istream& inputStream, map<string, int>& repeatedWords)
{
    string newString;
    while (inputStream >> newString)
	{
        transform(newString.begin(), newString.end(), newString.begin(), ::tolower);
		++repeatedWords[newString];
	}
}

void PrintRepeatedWords(ostream& outputStream, map<string, int>& repeatedWords)
{
    for (auto i = repeatedWords.begin(); i != repeatedWords.end(); ++ i)
    {
        outputStream << i->first << ": " << i->second << endl;
    }
}

void TestCalculateRepeatedWordsInEmptyString()
{
    map<string, int> testRepeatedWords;
    map<string, int> resultRepeatedWords;
    istringstream inputStream(""); 
    CalculateRepeatedWords(inputStream, testRepeatedWords);
    assert(testRepeatedWords == resultRepeatedWords && "Algorithm error!");
}

void TestCalculateRepeatedWords()
{
    map<string, int> testRepeatedWords;
    map<string, int> resultRepeatedWords;
    resultRepeatedWords["begin"] = 2;
    resultRepeatedWords["end"]   = 3;
    resultRepeatedWords["until"] = 1;
    istringstream inputStream("  end  until  begin  end begin end"); 
    CalculateRepeatedWords(inputStream, testRepeatedWords);
    assert(testRepeatedWords == resultRepeatedWords && "Algorithm error!");
}