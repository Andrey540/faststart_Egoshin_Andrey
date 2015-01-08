#include "stdafx.h"
#include "PhoneNumber.h"
#include <string>

using namespace std;

CPhoneNumber::CPhoneNumber(void)
{
    SetDelimiters(" -()");
}

CPhoneNumber::CPhoneNumber(const string& address) : CStringField(address)
{
    SetDelimiters(" -()");
}

CPhoneNumber::CPhoneNumber(const CStringField& field)
{
    SetValue(field.GetValue());
    SetDelimiters(" -()");
}

CPhoneNumber::~CPhoneNumber(void)
{}


bool CPhoneNumber::IsMatches(const string& number) const
{
    string currentPhoneNumber = PrepareValueForCompereEqual(GetValue());
    string otherPhoneNumber = PrepareValueForCompereEqual(number);

    return currentPhoneNumber.find(otherPhoneNumber) != string::npos;
}
