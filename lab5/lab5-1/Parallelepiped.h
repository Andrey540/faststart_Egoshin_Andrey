#include "Body.h"

#pragma once
class CParallelepiped : public CBody
{
public:
    CParallelepiped();
    CParallelepiped( double density, double width, double height, double depth);
    ~CParallelepiped();
    double GetWidth() const;
    double GetHeight() const;
    double GetDepth() const;
    double GetDensity() const override;
    double GetVolume() const override;
    double GetWeight() const override;
    std::string ToString() const override;

private:
    double m_width;
    double m_height;
    double m_depth;
    double m_density;
    double m_volume;
    double m_weight;
};

