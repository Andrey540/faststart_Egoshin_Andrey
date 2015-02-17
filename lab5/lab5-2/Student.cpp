#include "stdafx.h"
#include "Student.h"

using namespace std;

CStudent::CStudent(bool isMan, unsigned age, double growth, double weight, const std::wstring& name,
                   unsigned course, const std::shared_ptr<CUniversity>& university)
    : CPerson(isMan, age, growth, weight, name),
      m_course(course),
      m_university(university)
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

void CStudent::SetUniversity(const shared_ptr<CUniversity>& university)
{
    m_university = university;
}

const shared_ptr<CUniversity> CStudent::GetUniversity() const
{
    return shared_ptr<CUniversity>(m_university);
}