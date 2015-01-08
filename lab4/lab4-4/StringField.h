#include <string>
#include <vector>

#pragma once
class CStringField
{
public:    
    virtual ~CStringField(void);

    void SetValue(const std::string& value);
    std::string GetValue() const;
    virtual bool IsMatches(const std::string& value) const;
    virtual bool IsEqual(const std::string& value) const;
    virtual void Print(std::string ident = "") const;

    bool const operator == (const CStringField& other)
    {
        return IsEqual(other.GetValue());
    }

    bool const operator != (const CStringField& other)
    {
        return !(*this == other);
    }    

protected:
    CStringField(void);
    CStringField(std::string value);
    virtual std::vector<std::string> SepareteString(std::string str) const;
    void SetDelimiters(const std::string& delimiters);
    std::string PrepareValueForCompereEqual(const std::string& value) const;

private:
    std::string m_Value;    
    std::string m_Delimiters;
};