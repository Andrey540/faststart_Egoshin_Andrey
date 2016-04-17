#pragma once
#include "Shape.h"
class CEllipse :
	public CShape
{
public:
	CEllipse(std::string color, CShapePoint center, double verticalRadius, double horizontalRadius);
	~CEllipse();

	void Draw(ICanvas& canvas) override;
private:
	CShapePoint m_center;
	double m_verticalRadius;
	double m_horizontalRadius;
};

