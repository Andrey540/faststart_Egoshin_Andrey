#pragma once

#include "Person.h"
#include <memory>
#include <iostream>
#include "University.h"

class CStudent : public CPerson
{
public:
    CStudent(void);
    CStudent(bool isMan, unsigned age, double growth, double weight, const std::wstring& name,
             unsigned course, const std::shared_ptr<CUniversity>& university);
    virtual ~CStudent(void);
    void SetCourse(unsigned course);
    unsigned GetCourse() const;
    void SetUniversity(const std::shared_ptr<CUniversity>& university);
    const CUniversity& GetUniversity();

private:
    unsigned m_course;
    std::shared_ptr<const CUniversity> m_university;
};

