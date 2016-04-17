#include "stdafx.h"
#include "ShapeFactory.h"
#include <iostream>
#include <string>
#include <sstream>


CShapeFactory::CShapeFactory()
{
}

std::unique_ptr<CShape> CShapeFactory::CreateShape(const std::string & description)
{
	SeparateParameters(description);
	if (m_parameters.size() < 1 || !IsValidColor(m_parameters[1]))
	{
		throw std::invalid_argument("Incorrect color value");
	}

	PrepareDoubleParameters();

	if (m_parameters[0] == "rectangle")
	{
		return CreateRectangle();
	}
	else if (m_parameters[0] == "triangle")
	{
		return CreateTriangle();
	}
	else if (m_parameters[0] == "ellipse")
	{
		return CreateEllipse();
	}
	else if (m_parameters[0] == "regularpolygon")
	{
		return CreateRegularPolygon();
	}
	else
	{
		throw std::invalid_argument("unknown shape");
	}
}

std::unique_ptr<CShape> CShapeFactory::CreateRectangle()
{
	if (m_parameters.size() != 6)
	{
		throw std::invalid_argument("Incorect parameters count");
	}
	CShapePoint top(m_doubleParameters[0], m_doubleParameters[1]);
	CShapePoint bottom(m_doubleParameters[2], m_doubleParameters[3]);
	return std::make_unique<CRectangle>(m_parameters[1], top, bottom);
}

std::unique_ptr<CShape> CShapeFactory::CreateTriangle()
{
	if (m_parameters.size() != 8)
	{
		throw std::invalid_argument("Incorect parameters count");
	}
	CShapePoint vertex1(m_doubleParameters[0], m_doubleParameters[1]);
	CShapePoint vertex2(m_doubleParameters[2], m_doubleParameters[3]);
	CShapePoint vertex3(m_doubleParameters[4], m_doubleParameters[5]);
	return std::make_unique<CTriangle>(m_parameters[1], vertex1, vertex2, vertex3);
}

std::unique_ptr<CShape> CShapeFactory::CreateEllipse()
{
	if (m_parameters.size() != 6)
	{
		throw std::invalid_argument("Incorect parameters count");
	}
	CShapePoint center(m_doubleParameters[0], m_doubleParameters[1]);
	return std::make_unique<CEllipse>(m_parameters[1], center, m_doubleParameters[2], m_doubleParameters[3]);
}

std::unique_ptr<CShape> CShapeFactory::CreateRegularPolygon()
{
	if (m_parameters.size() != 6)
	{
		throw std::invalid_argument("Incorect parameters count");
	}
	CShapePoint center(m_doubleParameters[0], m_doubleParameters[1]);
	return std::make_unique<CRegularPolygon>(m_parameters[1], center, m_doubleParameters[2], m_doubleParameters[3]);
}

CShapeFactory::~CShapeFactory()
{
}

void CShapeFactory::SeparateParameters(const std::string& descriprion)
{
	m_parameters.clear();
	std::istringstream istream(descriprion);
	std::string tmp;
	while (istream >> tmp)
	{
		m_parameters.push_back(tmp);
	}
}

void CShapeFactory::PrepareDoubleParameters()
{
	m_doubleParameters.clear();
	for (size_t i = 2; i < m_parameters.size(); ++i)
	{
		double parameter = std::stod(m_parameters[i]);
		m_doubleParameters.push_back(parameter);
	}
}

bool CShapeFactory::IsValidColor(const std::string& color)const
{
	return color == "red" || color == "green" || color == "blue" || color == "pink" || 
		   color == "yellow" || color == "black";
}
