#include "stdafx.h"
#include "RegularPolygon.h"
#include <exception>

CRegularPolygon::CRegularPolygon(std::string color, CShapePoint center, double vertexCount, double radius)
	: CShape(color),
	m_center(center),
	m_vertexCount(vertexCount),
	m_radius(radius)
{
	if (m_vertexCount <= 2)
	{
		std::invalid_argument("incorrent count vertex value");
	}
	if (m_radius <= 0)
	{
		std::invalid_argument("incorrent radius value");
	}
}

CRegularPolygon::~CRegularPolygon()
{}

void CRegularPolygon::Draw(ICanvas& canvas)
{
	canvas;
}
