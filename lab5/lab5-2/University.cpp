#include "stdafx.h"
#include "University.h"
#include "Student.h"

using namespace std;

CUniversity::CUniversity(void)
    : m_name(L""),
      m_isModified(false)
{}

CUniversity::CUniversity(const wstring& name)
    : m_name(name),
      m_isModified(false)
{
    CheckValidName(name);
}

CUniversity::~CUniversity(void)
{
    m_students.clear();
}

void CUniversity::SetName(const std::wstring& name)
{
    CheckValidName(name);
    m_name = name;
}

std::wstring CUniversity::GetName() const
{
    return m_name;
}

const std::vector<std::shared_ptr<CStudent>>& CUniversity::GetStudents() const
{
    return m_students;
}

void CUniversity::AddStudent(const CStudent& student)
{
    m_students.push_back(make_shared<CStudent>(student));
    m_isModified = true;
}

void CUniversity::ResetModified()
{
    m_isModified = false;
}

bool CUniversity::IsModified()
{
    return m_isModified;
}

void CUniversity::DeleteStudent(unsigned index)
{
    if (index > m_students.size() || index == 0)
    {
        throw runtime_error("Incorrect student index");
    }
    m_students.erase(m_students.begin() + index - 1);
    m_isModified = true;
}

void CUniversity::ChangeStudent(unsigned index, const CStudent& student)
{
    if (index > m_students.size() || index == 0)
    {
        throw runtime_error("Incorrect student index");
    }
    m_students[index - 1] = std::make_shared<CStudent>(student);
    m_isModified = true;
}

void CUniversity::CheckValidName(const std::wstring& value) const
{
    if(value.empty())
    {
        throw domain_error("Name cant be empty string");
    }
}