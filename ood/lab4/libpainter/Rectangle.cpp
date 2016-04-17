#include "stdafx.h"
#include "Rectangle.h"


CRectangle::CRectangle(std::string color, CShapePoint top, CShapePoint bottom)
	: CShape(color),
	m_top(top),
	m_bottom(bottom)
{}


CRectangle::~CRectangle()
{}

void CRectangle::Draw(ICanvas& canvas)
{
	canvas;
}