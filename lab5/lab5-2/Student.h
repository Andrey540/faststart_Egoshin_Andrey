#pragma once

#include "Person.h"
#include <memory>
#include <iostream>
#include "University.h"

class CStudent : public CPerson
{
public:
    CStudent(bool isMan, unsigned age, double growth, double weight, const std::wstring& name,
             unsigned course, const std::shared_ptr<CUniversity>& university);
    ~CStudent(void);
    void SetCourse(unsigned course);
    unsigned GetCourse() const;
    void SetUniversity(const std::shared_ptr<CUniversity>& university);
    const std::shared_ptr<CUniversity> GetUniversity()const;

private:
    unsigned m_course;
    std::weak_ptr<CUniversity> m_university;
};

