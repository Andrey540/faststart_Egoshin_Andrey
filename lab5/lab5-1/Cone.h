#pragma once

#include "Body.h"

class CCone : public CBody
{
public:
    CCone();
    CCone(double density, double radius, double height);
    ~CCone();
    double GetRadius() const;
    double GetHeight() const;
    double GetVolume() const override;
    std::string ToString() const override;

private:
    double m_radius;
    double m_height;
};

