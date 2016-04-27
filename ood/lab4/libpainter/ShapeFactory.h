#pragma once
#include "IShapeFactory.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"
#include <map>
#include <boost/function.hpp>
#include <boost/bind/bind.hpp>

class CShapeFactory :
	public IShapeFactory
{
public:
	CShapeFactory();
	std::unique_ptr<CShape> CreateShape(const std::string & description) override;

	~CShapeFactory();
private:
	typedef boost::function< std::unique_ptr<CShape>(std::istream &) > CreateShapeFunc;
	
	std::unique_ptr<CShape> CreateRectangle(std::istream & in);
	std::unique_ptr<CShape> CreateTriangle(std::istream & in);
	std::unique_ptr<CShape> CreateEllipse(std::istream & in);
	std::unique_ptr<CShape> CreateRegularPolygon(std::istream & in);

	std::map<std::string, CreateShapeFunc> m_shapeTypeToCreator;
};

