// lab3-6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <numeric>
#include <assert.h>
#include <algorithm>
#include <functional>
#include <map>
#include <vector>
#include <boost/iterator/transform_iterator.hpp>

using namespace std;

using namespace boost;

struct Translation
{
    string word;
    bool isNew;

    Translation() : isNew(false) {}
};

void TranslateWords(map<string, Translation>& vocabulary);
void ReadVocabulary(char* vocabularyFilePath, map<string, Translation>& vocabulary);
void AppendVocabularyFromString(const string& currentString, map<string, Translation>& vocabulary);
void SaveNewTranslations(char* vocabularyFilePath, map<string, Translation>& vocabulary);
bool CheckIsEmptyNewTranslations(const map<string, Translation>& vocabulary);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Incorrect format - lab3-5.exe <vocabulary_file> for translation" << endl;
        return 1;
    }

    map<string, Translation> vocabulary;
    ReadVocabulary(argv[1], vocabulary);

    TranslateWords(vocabulary);

    if (!CheckIsEmptyNewTranslations(vocabulary))
    {
        cout << "There are new words in vocabulary, enter Y or y if you wont to save them" << endl;
        char choice;
        cin >> choice;

        if (choice == 'y' || choice == 'Y')
        {
            SaveNewTranslations(argv[1], vocabulary);
        }
    }

	return 0;
}

void TranslateWords(map<string, Translation>& vocabulary)
{
    cout << "Enter word for translate, if you want to stop, enter ..." << endl;
    string newWord;
    getline(cin, newWord);

    while(newWord != "...")
    {
        if (newWord == "")
        {
            getline(cin, newWord);
            continue;
        }
        transform(newWord.begin(), newWord.end(), newWord.begin(), ::tolower);
        auto newWordIterator = vocabulary.find(newWord);
        if (newWordIterator != vocabulary.end())
        {
            cout << (newWordIterator->second).word << endl;
        }
        else
        {
            cout << "Unknow word \"" << newWord << "\". Enter translation or N for cancel" << endl;
            Translation newTranslation;
            getline(cin, newTranslation.word);
            if (newTranslation.word == "N")
            {
                cout << "Word \"" << newWord << "\" was ignored" << endl;
            }
            else
            {
                newTranslation.isNew = true;
                vocabulary[newWord] = newTranslation;
                cout << "Word \"" << newWord << "\" was saved in vocabulary like \"" << newTranslation.word << "\"." << endl;
            }            
        }        
        getline(cin, newWord);
    }
}

void ReadVocabulary(char* vocabularyFilePath, map<string, Translation>& vocabulary)
{
    ifstream vocabularyFile(vocabularyFilePath);
    if (vocabularyFile.is_open())
    {
        string newString;
        while(!vocabularyFile.eof())
        {
            getline(vocabularyFile, newString);
            AppendVocabularyFromString(newString, vocabulary);
        }
    }
}

void AppendVocabularyFromString(const string& currentString, map<string, Translation>& vocabulary)
{
    size_t firstWordSeparator = currentString.find("[");
    size_t secondWordSeparator = currentString.find("]");
    size_t translationSeparator = currentString.find(" ", secondWordSeparator + 1);

    if (firstWordSeparator == string::npos || secondWordSeparator == string::npos ||
        firstWordSeparator >= secondWordSeparator || translationSeparator == string::npos)
    {
        return;
    }
    ++firstWordSeparator;
    ++translationSeparator;
    Translation translation;
    string word      = currentString.substr(firstWordSeparator, secondWordSeparator - firstWordSeparator);
    translation.word = currentString.substr(translationSeparator, currentString.length() - translationSeparator);
    
    if (word.length() != 0 && translation.word.length() != 0)
    {
        vocabulary[word] = translation;
    }
}

void SaveNewTranslations(char* vocabularyFilePath, map<string, Translation>& vocabulary)
{
    ofstream vocabularyFile(vocabularyFilePath, fstream::app);
    if (vocabularyFile.is_open())
    {
        for (auto i : vocabulary)
        {
            if (i.second.isNew)
            {
                vocabularyFile << "[" << i.first << "] "<< i.second.word << endl;
            }
        }
    }
}

bool CheckIsEmptyNewTranslations(const map<string, Translation>& vocabulary)
{
    return find_if(vocabulary.begin(), vocabulary.end(), [](pair<string, Translation> item){return item.second.isNew;}) == vocabulary.end();
}