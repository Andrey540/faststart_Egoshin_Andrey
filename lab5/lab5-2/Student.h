#pragma once

#include "Person.h"
#include <memory>
#include <iostream>
#include "University.h"

class CStudent : public CPerson
{
public:
    CStudent(void);
    CStudent(bool isMan, unsigned age, double growth, double weight, const std::wstring& name, unsigned course, const CUniversity& university);
    virtual ~CStudent(void);
    void SetCourse(unsigned course);
    unsigned GetCourse() const;
    void SetUniversity(const CUniversity& university);
    const CUniversity& GetUniversity();

    bool const operator == (const CStudent& other) const
    {        
        return ((CPerson)(*this) == (CPerson)(other)) && (m_course == other.m_course) && 
                m_university == other.m_university;
    }

    bool const operator != (const CStudent& other) const
    {             
        return !(*this == other);
    }

private:
    unsigned m_course;
    std::shared_ptr<const CUniversity> m_university;
};

