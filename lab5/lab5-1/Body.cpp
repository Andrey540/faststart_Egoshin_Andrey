#include "stdafx.h"
#include "Body.h"


CBody::CBody(double density)
    : m_density(density)
{}


double CBody::GetDensity() const
{
    return m_density;
}

double CBody::GetWeight() const
{
    return GetVolume() * GetDensity();
}

