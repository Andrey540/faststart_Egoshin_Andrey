#include "StringField.h"

#pragma once
class CName : public CStringField
{
public:
    CName(void);
    CName(const std::string& name);
    virtual ~CName(void) override;  
};

