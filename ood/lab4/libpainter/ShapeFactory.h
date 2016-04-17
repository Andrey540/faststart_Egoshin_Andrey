#pragma once
#include "IShapeFactory.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"
#include <vector>

class CShapeFactory :
	public IShapeFactory
{
public:
	CShapeFactory();
	std::unique_ptr<CShape> CreateShape(const std::string & description) override;

	~CShapeFactory();
private:
	void SeparateParameters(const std::string& descriprion);
	void PrepareDoubleParameters();
	bool IsValidColor(const std::string& color)const;
	
	std::unique_ptr<CShape> CreateRectangle();
	std::unique_ptr<CShape> CreateTriangle();
	std::unique_ptr<CShape> CreateEllipse();
	std::unique_ptr<CShape> CreateRegularPolygon();

	std::vector<std::string> m_parameters;
	std::vector<double> m_doubleParameters;
};

