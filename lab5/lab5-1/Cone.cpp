#include "stdafx.h"
#include "Cone.h"
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

CCone::CCone()
    : m_radius(0.0),
      m_height(0.0),
      m_density(0.0),
      m_volume(0.0),
      m_weight(0.0)
{}

CCone::CCone( double density, double radius, double height)
    : m_radius(radius),
      m_height(height),
      m_density(density)
{
    m_volume = pow(m_radius,2) * M_PI * m_height;
    m_weight = m_volume * m_density;
}

CCone::~CCone(void)
{}

double CCone::GetRadius() const
{
    return m_radius;
}

double CCone::GetHeight() const
{
    return m_height;
}

double CCone::GetDensity() const
{
    return m_density;
}

double CCone::GetVolume() const
{
    return m_volume;
}

double CCone::GetWeight() const
{
    return m_weight;
}

string CCone::ToString() const
{
    std::ostringstream strm;
    strm << "Cone: density " << m_density << " radius " << m_radius << 
            " height " << m_height << " volume " << 
            GetVolume() << " weight " << GetWeight();
	return strm.str();
}
