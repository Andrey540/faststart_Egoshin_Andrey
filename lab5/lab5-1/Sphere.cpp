#include "stdafx.h"
#include "Sphere.h"
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

CSphere::CSphere()
    : m_density(0.0),
      m_radius(0.0),
      m_volume(0.0),
      m_weight(0.0)
{}

CSphere::CSphere(double density, double radius)
    : m_density(density),
      m_radius(radius)
{
    m_volume = 4 * M_PI * pow(m_radius, 3) / 3;
    m_weight = m_volume * m_density;
}

CSphere::~CSphere()
{}

double CSphere::GetRadius() const
{
    return m_radius;
}

double CSphere::GetDensity() const
{
    return m_density;
}

double CSphere::GetVolume() const
{
    return m_volume;
}

double CSphere::GetWeight() const
{
    return m_weight;
}

string CSphere::ToString() const
{
    std::ostringstream strm;
    strm << "Sphere: density " << m_density << " radius " << m_radius << 
            " volume " << GetVolume() << " weight " << GetWeight();
	return strm.str();
}