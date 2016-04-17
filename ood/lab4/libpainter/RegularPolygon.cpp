#include "stdafx.h"
#include "RegularPolygon.h"


CRegularPolygon::CRegularPolygon(std::string color, CShapePoint center, double vertexCount, double radius)
	: CShape(color),
	m_center(center),
	m_vertexCount(vertexCount),
	m_radius(radius)
{}

CRegularPolygon::~CRegularPolygon()
{}

void CRegularPolygon::Draw(ICanvas& canvas)
{
	canvas;
}
