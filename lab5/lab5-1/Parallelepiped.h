#pragma once

#include "Body.h"

class CParallelepiped : public CBody
{
public:
    CParallelepiped();
    CParallelepiped( double density, double width, double height, double depth);
    ~CParallelepiped();
    double GetWidth() const;
    double GetHeight() const;
    double GetDepth() const;
    double GetVolume() const override;
    std::string ToString() const override;

private:
    double m_width;
    double m_height;
    double m_depth;
};

