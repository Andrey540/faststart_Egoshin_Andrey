#include "stdafx.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <boost/algorithm/string.hpp>
#include "StringField.h"

using namespace std;
using namespace boost;

CStringField::CStringField(void) : m_Delimiters(" ")
{}

CStringField::CStringField(string value) : m_Value(value), m_Delimiters(" ")
{}

CStringField::~CStringField(void)
{}

bool CStringField::IsMatches(const string& value) const
{
    vector<string> currentValues = SepareteString(m_Value);
    vector<string> values = SepareteString(value);

    for(string value : values)
    {
        bool result = false;
        for(string currentValue : currentValues)
        {
            if (value == currentValue)
            {
                result = true;
                break;
            }
        }

        if (!result)
        {
            return false;
        }
    }
    return true;
}

bool CStringField::IsEqual(const string& value) const
{
    string currentPreparedValue = PrepareValueForCompereEqual(m_Value);
    string preparedValue = PrepareValueForCompereEqual(value);

    return currentPreparedValue == preparedValue;
}

void CStringField::Print(string ident) const
{
    cout << ident << m_Value << endl;
}

string CStringField::GetValue() const
{
    return m_Value;
}

void CStringField::SetValue(const string& value)
{
    m_Value = value;
}

vector<string> CStringField::SepareteString(string str) const
{    
    locale ruLocale("ru");
    to_lower(str, ruLocale);
    vector<string> result;
    string::size_type lastPos = str.find_first_not_of(m_Delimiters, 0);
    string::size_type pos = str.find_first_of(m_Delimiters, lastPos);
    while (wstring::npos != pos || wstring::npos != lastPos)
    {
        result.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(m_Delimiters, pos);
        pos = str.find_first_of(m_Delimiters, lastPos);
    }

    return result;
}

void CStringField::SetDelimiters(const string& delimiters)
{
    m_Delimiters = delimiters;
}

string CStringField::PrepareValueForCompereEqual(const string& value) const
{
    vector<string> values = SepareteString(value);
    string preparedValue = accumulate(values.begin(), values.end(), string(""));
    return preparedValue;
}
