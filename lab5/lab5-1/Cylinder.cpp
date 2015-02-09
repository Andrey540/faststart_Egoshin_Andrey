#include "stdafx.h"
#include "Cylinder.h"
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

CCylinder::CCylinder(void)
    : m_radius(0.0),
      m_height(0.0),
      CBody(0.0)
{}

CCylinder::CCylinder(double density, double radius, double height)
    : m_radius(radius),
      m_height(height),
      CBody(density)
{}

CCylinder::~CCylinder(void)
{}

double CCylinder::GetRadius() const
{
    return m_radius;
}

double CCylinder::GetHeight() const
{
    return m_height;
}

double CCylinder::GetVolume() const
{
    return pow(m_radius,2) * M_PI * m_height;
}

string CCylinder::ToString() const
{
    std::ostringstream strm;
    strm << "Cylinder: density " << GetDensity() << " radius " << m_radius << 
            " height " << m_height << " volume " << 
            GetVolume() << " weight " << GetWeight();
	return strm.str();
}
