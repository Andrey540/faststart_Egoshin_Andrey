#pragma once
#include "ICanvas.h"
#include "ShapePoint.h"
class CShape
{
public:
	CShape(std::string color);
	virtual ~CShape();

	const std::string& GetColor()const;

	virtual void Draw(ICanvas& canvas) = 0;
private:
	std::string m_color;
};

