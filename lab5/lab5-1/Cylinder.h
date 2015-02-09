#pragma once

#include "Body.h"

class CCylinder : public CBody
{
public:
    CCylinder(void);
    CCylinder(double density, double radius, double height);
    ~CCylinder(void);
    double GetRadius() const;
    double GetHeight() const;
    double GetVolume() const override;
    std::string ToString() const override;

private:
    double m_radius;
    double m_height;
};

