#include "stdafx.h"
#include "Rectangle.h"
#include <exception>

CRectangle::CRectangle(std::string color, CShapePoint top, CShapePoint bottom)
	: CShape(color),
	m_top(top),
	m_bottom(bottom)
{
	if (m_top.getX() >= m_bottom.getX() || m_top.getY() >= m_bottom.getY())
	{
		std::invalid_argument("incorrent point value");
	}
}


CRectangle::~CRectangle()
{}

void CRectangle::Draw(ICanvas& canvas)
{
	canvas;
}