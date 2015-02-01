#include "stdafx.h"
#include "Student.h"

using namespace std;

CStudent::CStudent(void)
    : m_course(0),
      m_university(nullptr)
{}

CStudent::CStudent(bool isMan, unsigned age, double growth, double weight, const std::wstring& name, unsigned course, const CUniversity& university)
    : CPerson(isMan, age, growth, weight, name),
      m_course(course),
      m_university(make_shared<const CUniversity>(university))
{}

CStudent::~CStudent(void)
{}

void CStudent::SetCourse(unsigned course)
{
    if (course < m_course)
    {
        throw domain_error("Course must be greater than previous value");
    }
    m_course = course;
}

unsigned CStudent::GetCourse() const
{
    return m_course;
}

void CStudent::SetUniversity(const CUniversity& university)
{
    m_university = make_shared<const CUniversity>(university);
}

const CUniversity& CStudent::GetUniversity()
{
    return *m_university;
}