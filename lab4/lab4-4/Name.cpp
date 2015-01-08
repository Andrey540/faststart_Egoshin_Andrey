#include "stdafx.h"
#include "Name.h"
#include <string>

using namespace std;

CName::CName(void)
{}

CName::CName(const string& name) : CStringField(name)
{}

CName::~CName(void)
{}
