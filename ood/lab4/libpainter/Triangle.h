#pragma once
#include "Shape.h"
class CTriangle :
	public CShape
{
public:
	CTriangle(std::string color, CShapePoint vertex1, CShapePoint vertex2, CShapePoint vertex3);
	~CTriangle();

	void Draw(ICanvas& canvas) override;
private:
	CShapePoint m_vertex1;
	CShapePoint m_vertex2;
	CShapePoint m_vertex3;
};

