#include "StringField.h"

#pragma once
class CPostAddress : public CStringField
{
public:
    CPostAddress(void);
    CPostAddress(const std::string& address);
    virtual ~CPostAddress(void) override;
};

