#pragma once
#include "Shape.h"
class CRegularPolygon :
	public CShape
{
public:
	CRegularPolygon(std::string color, CShapePoint center, double vertexCount, double radius);
	~CRegularPolygon();

	void Draw(ICanvas& canvas) override;
private:
	CShapePoint m_center;
	double m_vertexCount;
	double m_radius;
};

