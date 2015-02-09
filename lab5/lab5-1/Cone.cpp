#include "stdafx.h"
#include "Cone.h"
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

CCone::CCone()
    : CBody(0.0),
      m_radius(0.0),
      m_height(0.0)
{}

CCone::CCone(double density, double radius, double height)
    : m_radius(radius),
      m_height(height),
      CBody(density)
{}

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

double CCone::GetVolume() const
{
    return pow(m_radius,2) * M_PI * m_height;
}

string CCone::ToString() const
{
    std::ostringstream strm;
    strm << "Cone: density " << GetDensity() << " radius " << m_radius << 
            " height " << m_height << " volume " << 
            GetVolume() << " weight " << GetWeight();
	return strm.str();
}
