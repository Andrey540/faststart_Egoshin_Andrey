#include "StringField.h"

#pragma once
class CPhoneNumber : public CStringField
{
public:
    CPhoneNumber(void);
    CPhoneNumber(const std::string& number);
    CPhoneNumber(const CStringField& field);
    virtual ~CPhoneNumber(void) override;
    virtual bool IsMatches(const std::string& number) const override;
};

