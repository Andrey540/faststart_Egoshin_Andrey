#include "stdafx.h"
#include "Sphere.h"
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

CSphere::CSphere()
    : CBody(0.0),
      m_radius(0.0)
{}

CSphere::CSphere(double density, double radius)
    : CBody(density),
      m_radius(radius)
{}

CSphere::~CSphere()
{}

double CSphere::GetRadius() const
{
    return m_radius;
}

double CSphere::GetVolume() const
{
    return 4 * M_PI * pow(m_radius, 3) / 3;
}

string CSphere::ToString() const
{
    std::ostringstream strm;
    strm << "Sphere: density " << GetDensity() << " radius " << m_radius << 
            " volume " << GetVolume() << " weight " << GetWeight();
	return strm.str();
}