#include "stdafx.h"
#include "Parallelepiped.h"
#include <sstream>

using namespace std;

CParallelepiped::CParallelepiped()
    : m_width(0.0),
      m_height(0.0),
      m_depth(0.0),
      CBody(0.0)
{}

CParallelepiped::CParallelepiped(double density, double width, double height, double depth)
    : m_width(width),
      m_height(height),
      m_depth(depth),
      CBody(density)
{}

CParallelepiped::~CParallelepiped()
{}

double CParallelepiped::GetWidth() const
{
    return m_width;
}

double CParallelepiped::GetHeight() const
{
    return m_height;
}

double CParallelepiped::GetDepth() const
{
    return m_depth;
}

double CParallelepiped::GetVolume() const
{
    return m_width * m_height * m_depth;
}

string CParallelepiped::ToString() const
{
    std::ostringstream strm;
    strm << "Parallelepiped: density " << GetDensity() << " width " << m_width << 
            " height " << m_height << " depth " << m_depth << " volume " << 
            GetVolume() << " weight " << GetWeight();
	return strm.str();
}