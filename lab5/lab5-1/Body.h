#pragma once

#include <string>

class CBody
{
public:
    CBody(double density);
    virtual ~CBody(){};
    double GetDensity() const;
    double GetWeight() const;
    virtual double GetVolume() const = 0;    
    virtual std::string ToString() const = 0;    
private:
    double m_density;
};

