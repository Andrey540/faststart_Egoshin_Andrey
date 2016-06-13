#pragma once
#include <iostream>
#include "CommonTypes.h"

class ICanvas
{
public:
	virtual void SetLineColor(RGBAColor color) = 0;
	virtual void BeginFill(RGBAColor color) = 0;
	virtual void EndFill() = 0;
	virtual void MoveTo(double x, double y) = 0;
	virtual void LineTo(double x, double y) = 0;
	virtual void SetLineWidth(size_t width) = 0;
	virtual void DrawEllipse(double left, double top, double width, double height) = 0;

	virtual ~ICanvas() = default;
};

class CCanvas : public ICanvas
{
public:
	CCanvas()
	{}

	void SetLineColor(RGBAColor color) override
	{
		m_lineColor = color;
		std::cout << "set color " << color << std::endl;
	}
	void BeginFill(RGBAColor color) override
	{
		m_fillColor = color;
		std::cout << "begin fill with color " << color << std::endl;
	}
	void EndFill() override
	{
		std::cout << "end fill" << std::endl;
	}
	void MoveTo(double x, double y) override
	{
		std::cout << "move to x = " << x << " y = " << y << std::endl;
	}
	void LineTo(double x, double y) override
	{
		std::cout << "line to x = " << x << " y = " << y << std::endl;
	}
	void SetLineWidth(size_t width) override
	{
		m_lineWidth = width;
		std::cout << "set line width " << width << std::endl;
	}
	void DrawEllipse(double left, double top, double width, double height) override
	{
		std::cout << "draw ellipse left: " << left << " top: " << top << " width: " << width << " height: " << height << std::endl;
	}

private:
	RGBAColor m_lineColor;
	RGBAColor m_fillColor;
	size_t m_lineWidth;
};