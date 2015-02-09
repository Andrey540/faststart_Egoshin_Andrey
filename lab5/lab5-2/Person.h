#include <string>

#pragma once
class CPerson
{
public:
    CPerson(void);
    CPerson(bool isMan, unsigned age, double growth, double weight, const std::wstring& name);
    virtual ~CPerson(void);

    void SetAge(unsigned age);
    void SetName(const std::wstring& name);
    void SetWeight(double weight);
    void SetGrowth(double growth);

    unsigned GetAge() const;
    std::wstring GetName() const;
    double GetWeight() const;
    double GetGrowth() const;
    bool IsMan() const;

    bool const operator == (const CPerson& other) const
    {
        return this == std::addressof(other);
    }

    bool const operator != (const CPerson& other) const
    {             
        return !(*this == other);
    }

private:
    bool m_isMan;
    unsigned m_age;    
    double m_growth;
    double m_weight;
    std::wstring m_name;

    void CheckValidValue(const std::string& parameterName, double value) const;
};

