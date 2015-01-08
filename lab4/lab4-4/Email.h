#include "StringField.h"

#pragma once
class CEmail : public CStringField
{
public:
    CEmail(void);
    CEmail(const std::string& email);
    CEmail(const CStringField& field);
    virtual ~CEmail(void) override;
    virtual bool IsMatches(const std::string& email) const override;

    CEmail operator = (const CStringField& other)
    {
        SetValue(other.GetValue());
    }
};

