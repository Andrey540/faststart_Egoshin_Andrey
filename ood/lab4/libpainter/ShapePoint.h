#pragma once
class CShapePoint
{
public:
	CShapePoint(double x, double y)
		: m_x(x),
		m_y(y)
	{};
	~CShapePoint() {};

	double getX()
	{
		return m_x;
	}

	double getY()
	{
		return m_y;
	}

private:
	double m_x;
	double m_y;
};

