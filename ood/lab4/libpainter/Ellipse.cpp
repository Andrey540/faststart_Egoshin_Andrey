#include "stdafx.h"
#include "Ellipse.h"
#include <exception>

CEllipse::CEllipse(std::string color, CShapePoint center, double verticalRadius, double horizontalRadius)
	: CShape(color),
	m_center(center),
	m_verticalRadius(verticalRadius),
	m_horizontalRadius(horizontalRadius)
{
	if (m_verticalRadius <= 0)
	{
		std::invalid_argument("incorrent vertical radius value");
	}
	if (m_horizontalRadius <= 0)
	{
		std::invalid_argument("incorrent horizontal radius value");
	}
}

CEllipse::~CEllipse()
{}

void CEllipse::Draw(ICanvas& canvas)
{
	canvas;
}
