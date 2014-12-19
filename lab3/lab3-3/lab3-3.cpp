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

typedef map<string, int> WordFrequency;

void CalculateRepeatedWords(istream& inputStream, WordFrequency& repeatedWords);
void PrintRepeatedWords(ostream& outputStream, WordFrequency& repeatedWords);
void AssertFrequencyMapsAreEqual(istringstream& inputStream, WordFrequency& comparedFrequency);
void TestCalculateRepeatedWordsInEmptyString();
void TestCalculateRepeatedWords();

int main(int argc, char* argv[])
{
    TestCalculateRepeatedWordsInEmptyString();
    TestCalculateRepeatedWords();

    cout << "Enter some strings, please. For end enter sign end of file" << endl;
    WordFrequency repeatedWords;
    CalculateRepeatedWords(cin, repeatedWords);
    PrintRepeatedWords(cout, repeatedWords);
	return 0;
}

void CalculateRepeatedWords(istream& inputStream, WordFrequency& repeatedWords)
{
    string newString;
    while (inputStream >> newString)
	{
        transform(newString.begin(), newString.end(), newString.begin(), ::tolower);
		++repeatedWords[newString];
	}
}

void PrintRepeatedWords(ostream& outputStream, WordFrequency& repeatedWords)
{
    for (auto repeatedWord:repeatedWords)
    {
        outputStream << repeatedWord.first << ": " << repeatedWord.second << endl;
    }
}

void AssertFrequencyMapsAreEqual(istringstream& inputStream, WordFrequency& comparedFrequency)
{
    map<string, int> testRepeatedWords;
    CalculateRepeatedWords(inputStream, testRepeatedWords);
    assert(testRepeatedWords == comparedFrequency && "Algorithm error!");
}

void TestCalculateRepeatedWordsInEmptyString()
{
    map<string, int> resultRepeatedWords;
    AssertFrequencyMapsAreEqual(istringstream(""), resultRepeatedWords);
}

void TestCalculateRepeatedWords()
{
    map<string, int> resultRepeatedWords;
    pair<string, int> expectedItems[] = {make_pair("begin", 2), make_pair("end", 3), make_pair("until", 1)};
    map<string, int> expectedMap(begin(expectedItems), end(expectedItems));
    AssertFrequencyMapsAreEqual(istringstream("  end  until  begin  end begin end"), expectedMap);
}