#include "Body.h"

#pragma once
class CSphere : public CBody
{
public:
    CSphere();
    CSphere(double density, double radius);
    ~CSphere() override;
    double GetRadius() const;
    double GetDensity() const override;
    double GetVolume() const override;
    double GetWeight() const override;
    std::string ToString() const override;

private:
    double m_density;
    double m_radius;
    double m_volume;
    double m_weight;
};

