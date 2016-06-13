#pragma once
#include "Shape.h"

class ISlide : public IDrawable
{
public:
	virtual double GetWidth()const = 0;
	virtual double GetHeight()const = 0;

	virtual IShapes & GetShapes() = 0;

	virtual ~ISlide() = default;
};

class CSlide : public ISlide, public IShapes
{
public:
	CSlide() {}

	double GetWidth()const override
	{
		return m_shapes.GetFrame().width;
	}
	double GetHeight()const override
	{
		return m_shapes.GetFrame().height;
	}

	IShapes & GetShapes() override
	{
		return m_shapes;
	}

	void Draw(ICanvas & canvas) override
	{
		m_shapes.Draw(canvas);
	}
	size_t GetShapesCount()const override
	{
		return m_shapes.GetShapesCount();
	}
	void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) override
	{
		m_shapes.InsertShape(shape, position);
	}
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override
	{
		return m_shapes.GetShapeAtIndex(index);
	}
	void RemoveShapeAtIndex(size_t index) override
	{
		m_shapes.RemoveShapeAtIndex(index);
	}

	void SetOutlineStyle(std::shared_ptr<ILineStyle> style)
	{
		m_shapes.SetOutlineStyle(style);
	}
	void SetFillStyle(std::shared_ptr<IStyle> style)
	{
		m_shapes.SetFillStyle(style);
	}

private:
	CGroupShape m_shapes;
};

