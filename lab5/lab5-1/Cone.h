#include "Body.h"

#pragma once
class CCone : public CBody
{
public:
    CCone();
    CCone( double density, double radius, double height);
    ~CCone();
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

