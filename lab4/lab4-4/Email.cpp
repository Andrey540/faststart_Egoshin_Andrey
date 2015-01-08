#include "stdafx.h"
#include "Email.h"
#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

CEmail::CEmail(void)
{}

CEmail::CEmail(const string& email) : CStringField(email)
{}

CEmail::CEmail(const CStringField& field)
{
    SetValue(field.GetValue());
}

CEmail::~CEmail(void)
{}

bool CEmail::IsMatches(const string& email) const
{
    locale ruLocale("ru");
    string currentEmail = GetValue(); 
    string otherEmail = email;
    to_lower(currentEmail, ruLocale);
    to_lower(otherEmail, ruLocale);

    return currentEmail.find(otherEmail) != string::npos;
}