#include "stdafx.h"
#include "ShapeFactory.h"
#include <iostream>
#include <string>
#include <sstream>
#include <exception>


CShapeFactory::CShapeFactory()
{
	m_shapeTypeToCreator["rectangle"]      = boost::bind(&CShapeFactory::CreateRectangle, *this, _1);
	m_shapeTypeToCreator["triangle"]       = boost::bind(&CShapeFactory::CreateTriangle, *this, _1);
	m_shapeTypeToCreator["ellipse"]        = boost::bind(&CShapeFactory::CreateEllipse, *this, _1);
	m_shapeTypeToCreator["regularpolygon"] = boost::bind(&CShapeFactory::CreateRegularPolygon, *this, _1);
}

std::unique_ptr<CShape> CShapeFactory::CreateShape(const std::string & description)
{
	try
	{
		std::string shapeType;
		std::istringstream strm(description);
		strm.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		strm >> shapeType;
		return m_shapeTypeToCreator.at(shapeType)(strm);
	}
	catch (...)
	{
		throw std::runtime_error("Shape creation error");
	}
}

std::unique_ptr<CShape> CShapeFactory::CreateRectangle(std::istream & in)
{
	std::string color;
	double x0, y0, x1, y1;
	in >> color >> x0 >> y0 >> x1 >> y1;
	return std::make_unique<CRectangle>(color, CShapePoint(x0, y0), CShapePoint(x1, y1));
}

std::unique_ptr<CShape> CShapeFactory::CreateTriangle(std::istream & in)
{
	std::string color;
	double x0, y0, x1, y1, x3, y3;
	in >> color >> x0 >> y0 >> x1 >> y1 >> x3 >> y3;
	return std::make_unique<CTriangle>(color, CShapePoint(x0, y0), CShapePoint(x1, y1), CShapePoint(x3, y3));
}

std::unique_ptr<CShape> CShapeFactory::CreateEllipse(std::istream & in)
{
	std::string color;
	double x, y, r1, r2;
	in >> color >> x >> y >> r1 >> r2;
	return std::make_unique<CEllipse>(color, CShapePoint(x, y), r1, r2);
}

std::unique_ptr<CShape> CShapeFactory::CreateRegularPolygon(std::istream & in)
{
	std::string color;
	double x, y, vertexCount, r;
	in >> color >> x >> y >> vertexCount >> r;
	return std::make_unique<CRegularPolygon>(color, CShapePoint(x, y), vertexCount, r);
}

CShapeFactory::~CShapeFactory()
{
}
