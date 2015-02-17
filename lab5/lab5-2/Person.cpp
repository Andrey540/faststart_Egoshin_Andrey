#include "stdafx.h"
#include "Person.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

CPerson::CPerson(bool isMan, unsigned age, double growth, double weight, const wstring& name)
    : m_isMan(isMan),
      m_age(age),
      m_growth(growth),
      m_weight(weight),
      m_name(name)
{
    if(name.empty())
    {
        throw domain_error("Name cant be empty string");
    }
    CheckValidValue("Growth", growth);
    CheckValidValue("Weight", weight);
}

CPerson::~CPerson(void)
{}


void CPerson::SetAge(unsigned age)
{
    if (age < m_age)
    {
        throw domain_error("Age must be greater than previous value");
    }
    m_age = age;
}

void CPerson::SetName(const wstring& name)
{
    if(name.empty())
    {
        throw domain_error("Name cant be empty string");
    }
    m_name = name;
}

void CPerson::SetWeight(double weight)
{
    CheckValidValue("Weight", weight);
    m_weight = weight;
}

void CPerson::SetGrowth(double growth)
{
    if (growth < m_growth)
    {
        throw domain_error("Growth must be greater than previous value");
    }
    m_growth = growth;
}

unsigned CPerson::GetAge() const
{
    return m_age;
}

std::wstring CPerson::GetName() const
{
    return m_name;
}

double CPerson::GetWeight() const
{
    return m_weight;
}

double CPerson::GetGrowth() const
{
    return m_growth;
}

bool CPerson::IsMan() const
{
    return m_isMan;
}

void CPerson::CheckValidValue(const std::string& parameterName, double value) const
{
    if (value <= 0)
    {
        throw domain_error(parameterName + " must be greater than 0");
    }
}