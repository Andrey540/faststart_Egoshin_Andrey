#pragma once

#include "Body.h"

class CSphere : public CBody
{
public:
    CSphere();
    CSphere(double density, double radius);
    ~CSphere() override;
    double GetRadius() const;
    double GetVolume() const override;
    std::string ToString() const override;

private:
    double m_radius;
};

