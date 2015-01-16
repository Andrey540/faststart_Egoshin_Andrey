#include "Body.h"

#pragma once
class CCylinder : public CBody
{
public:
    CCylinder(void);
    CCylinder(double density, double radius, double height);
    ~CCylinder(void);
    double GetRadius() const;
    double GetHeight() const;
    double GetDensity() const override;
    double GetVolume() const override;
    double GetWeight() const override;
    std::string ToString() const override;

private:
    double m_density;
    double m_volume;
    double m_weight;
    double m_radius;
    double m_height;
};

