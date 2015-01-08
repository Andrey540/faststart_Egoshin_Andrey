#include "stdafx.h"
#include "PostAddress.h"
#include <string>

using namespace std;

CPostAddress::CPostAddress(void)
{
    SetDelimiters(" ,");
}

CPostAddress::CPostAddress(const string& address) : CStringField(address)
{
    SetDelimiters(" ,");
}

CPostAddress::~CPostAddress(void)
{}