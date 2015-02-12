#include "stdafx.h"
#include "Student.h"
#include <exception>
#include <algorithm>
#include <functional>

using namespace std;

const int STUDENT_AGE_UPPER_BOUNCE = 60;
const int STUDENT_AGE_LOWER_BOUNCE = 14;

CStudent::CStudent(void)
    : m_name(""),
      m_surname(""),
      m_patronymic(""),
      m_age(0)
{}

CStudent::CStudent(const string& name, const string& surname, const string& patronymic, unsigned age)
    : m_name(""),
      m_surname(""),
      m_patronymic(""),
      m_age(0)
{
    Rename(name, surname, patronymic);
    SetAge(age);
}

CStudent::~CStudent(void)
{}

void CStudent::Rename(const string& name, const string& surname, const string& patronymic)
{
    string newName       = name;
    string newSurname    = surname;
    string newPatronymic = patronymic;

    if (name.empty() || IsConsistOnlyOfWhiteSpaces(name))
    {
        throw invalid_argument("Name can not be empty");
    }
    if (surname.empty() || IsConsistOnlyOfWhiteSpaces(surname))
    {
        throw invalid_argument("Surname can not be empty");
    }
    if (!patronymic.empty() && IsConsistOnlyOfWhiteSpaces(patronymic))
    {
        throw invalid_argument("Patronymic can not consist only white spaces");
    }

    swap(newName, m_name);
    swap(newSurname, m_surname);
    swap(newPatronymic, m_patronymic);
}

void CStudent::SetAge(unsigned age)
{
    if (age < m_age)
    {
        throw domain_error("age can not be less than exist");
    }
    if (age < STUDENT_AGE_LOWER_BOUNCE || age > STUDENT_AGE_UPPER_BOUNCE)
    {
        throw out_of_range("argument age out of range");
    }
    m_age = age;
}

const string& CStudent::GetName()const
{
    return m_name;
}

const string& CStudent::GetSurname()const
{
    return m_surname;
}

const string& CStudent::GetPatronymic()const
{
    return m_patronymic;
}

unsigned CStudent::GetAge()const
{
    return m_age;
}

bool CStudent::IsConsistOnlyOfWhiteSpaces(const string& str)const
{
    auto result = find_if(str.begin(), str.end(), bind2nd(not_equal_to<char>(), ' '));
    return result == str.end();
}


 