#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle(std::string color, CShapePoint vertex1, CShapePoint vertex2, CShapePoint vertex3)
	: CShape(color),
	m_vertex1(vertex1),
	m_vertex2(vertex2),
	m_vertex3(vertex3)
{}

CTriangle::~CTriangle()
{}

void CTriangle::Draw(ICanvas& canvas)
{
	canvas;
}
