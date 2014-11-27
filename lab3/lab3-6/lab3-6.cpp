// lab3-6.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <numeric>
#include <assert.h>
#include <algorithm>
#include <functional>
#include <map>
#include <vector>

using namespace::std;

struct Translation
{
    string word;
    bool isNew;

    Translation()
    {
        isNew = false;
    }
};

void TrnaslateWords(map<string, Translation>& vocabulary);
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

    TrnaslateWords(vocabulary);

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

void TrnaslateWords(map<string, Translation>& vocabulary)
{
    cout << "Enter word for translate, if you want to stop, enter ..." << endl;
    string newWord;

    while(cin >> newWord)
    {
        if (newWord == "...")
        {
            break;
        }
        transform(newWord.begin(), newWord.end(), newWord.begin(), ::tolower);

        if (vocabulary.find(newWord) != vocabulary.end())
        {
            cout << vocabulary[newWord].word << endl;
        }
        else
        {
            cout << "Unknow word \"" << newWord << "\". Enter translation or N for cancel" << endl;
            Translation newTranslation;
            cin >> newTranslation.word;
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
    }
    return;
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
    return;
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
    return;
}

void SaveNewTranslations(char* vocabularyFilePath, map<string, Translation>& vocabulary)
{
    ofstream vocabularyFile(vocabularyFilePath, fstream::app);
    if (vocabularyFile.is_open())
    {
        for (auto i = vocabulary.begin(); i != vocabulary.end(); ++i)
        {
            if (i->second.isNew)
            {
                vocabularyFile << "[" << i->first << "] "<< i->second.word << endl;
            }
        }
    }
    return;
}

bool CheckIsEmptyNewTranslations(const map<string, Translation>& vocabulary)
{
    for (auto i = vocabulary.begin(); i != vocabulary.end(); ++i)
    {
        if (i->second.isNew)
        {
            return false;
        }
    }
    return true;
}