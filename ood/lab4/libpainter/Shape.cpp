#include "stdafx.h"
#include "Shape.h"


CShape::CShape(std::string color) : m_color(color)
{
	if (m_color != "red" && m_color != "green" && m_color != "blue" && m_color != "pink" &&
		m_color != "yellow" && m_color != "black")
	{
		throw std::invalid_argument("Incorrect color value");
	}
}


CShape::~CShape()
{}

const std::string& CShape::GetColor()const
{
	return m_color;
}
