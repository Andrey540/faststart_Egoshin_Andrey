#pragma once
#include "Shape.h"
class CRectangle :
	public CShape
{
public:
	CRectangle(std::string color, CShapePoint top, CShapePoint bottom);
	~CRectangle();

	void Draw(ICanvas& canvas) override;

private:
	CShapePoint m_top;
	CShapePoint m_bottom;
};

