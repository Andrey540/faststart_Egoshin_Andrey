#include "stdafx.h"
#include "Ellipse.h"


CEllipse::CEllipse(std::string color, CShapePoint center, double verticalRadius, double horizontalRadius)
	: CShape(color),
	m_center(center),
	m_verticalRadius(verticalRadius),
	m_horizontalRadius(horizontalRadius)
{}

CEllipse::~CEllipse()
{}

void CEllipse::Draw(ICanvas& canvas)
{
	canvas;
}
