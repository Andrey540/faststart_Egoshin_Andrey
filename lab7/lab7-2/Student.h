#pragma once

#include <string>

class CStudent
{
public:
    CStudent(void);
    CStudent(const std::string& name, const std::string& surname, const std::string& patronymic, unsigned age);
    ~CStudent(void);    
    void Rename(const std::string& name, const std::string& surname, const std::string& patronymic);
    void SetAge(unsigned age);
    const std::string& GetName()const;
    const std::string& GetSurname()const;
    const std::string& GetPatronymic()const;
    unsigned GetAge()const;    

private:
    std::string m_name;
    std::string m_surname;
    std::string m_patronymic;
    unsigned m_age;   

    bool IsConsistOnlyOfWhiteSpaces(const std::string& str)const;
};

