#pragma once
#include "CommonTypes.h"
#include "Canvas.h"
#include "Style.h"
#include <memory>
#include <numeric>

#include <cstdint>
#include <boost/optional.hpp>
#include <vector>
#include <memory>
#include <limits>
#include <functional>

class IDrawable
{
public:
	virtual void Draw(ICanvas & canvas) = 0;

	virtual ~IDrawable() = default;
};

class IGroupShape;

class IShape : public IDrawable
{
public:
	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD & rect) = 0;

	virtual void SetOutlineStyle(std::shared_ptr<ILineStyle> style) = 0;
	virtual std::shared_ptr<ILineStyle>  GetOutlineStyle() = 0;
	virtual std::shared_ptr<const ILineStyle> GetOutlineStyle()const = 0;

	virtual void SetFillStyle(std::shared_ptr<IStyle> style) = 0;
	virtual std::shared_ptr<IStyle> GetFillStyle() = 0;
	virtual std::shared_ptr<const IStyle> GetFillStyle()const = 0;

	virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
	virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

	virtual ~IShape() = default;
};

class IShapes
{
public:
	virtual size_t GetShapesCount()const = 0;
	virtual void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) = 0;
	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;

	virtual ~IShapes() = default;
};


class IGroupShape : public IShape, public IShapes
{
public:
	virtual ~IGroupShape() = default;
};

class CShape : public IShape
{
public:
	virtual void Draw(ICanvas & canvas) = 0;
	virtual ~CShape() = default;

	CShape(std::shared_ptr<ILineStyle> lineStyle, std::shared_ptr<IStyle> fillStyle, RectD rect)
		: m_outlineStyle(lineStyle),
		  m_fillStyle(fillStyle),
		  m_rect(rect)
	{}
	RectD GetFrame() const override
	{
		return m_rect;
	}
	void SetFrame(const RectD & rect) override
	{
		m_rect = rect;
	}
	void SetOutlineStyle(std::shared_ptr<ILineStyle> style) override
	{
		m_outlineStyle = style;
	}
	std::shared_ptr<ILineStyle> GetOutlineStyle() override
	{
		return m_outlineStyle;
	}
	std::shared_ptr<const ILineStyle> GetOutlineStyle()const override
	{
		return m_outlineStyle;
	}
	void SetFillStyle(std::shared_ptr<IStyle> style) override
	{
		m_fillStyle = style;
	}
	std::shared_ptr<IStyle> GetFillStyle() override
	{
		return m_fillStyle;
	}
	std::shared_ptr<const IStyle> GetFillStyle()const override
	{
		return m_fillStyle;
	}
	std::shared_ptr<IGroupShape> GetGroup() override
	{
		return nullptr;
	}
	std::shared_ptr<const IGroupShape> GetGroup() const override
	{
		return nullptr;
	}	
private:
	std::shared_ptr<ILineStyle> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
	RectD m_rect;
};

typedef std::function<void(ICanvas & canvas, const IShape & shape)> DrawingStrategy;

class CSimpleShape : public IShape
{
public:
	CSimpleShape(const DrawingStrategy & drawingStrategy)
	{
		(void)&drawingStrategy;
	}
};

class CGroupShape : public IGroupShape
{
public:
	CGroupShape()
		: m_frame({ (double)std::numeric_limits<size_t>::max(),  (double)std::numeric_limits<size_t>::max(), 0, 0})
	{}
	size_t GetShapesCount()const override
	{
		return m_shapes.size();
	}
	void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) override
	{
		if (m_outlineStyle)
		{
			shape->SetOutlineStyle(m_outlineStyle);
		}
		if (m_fillStyle)
		{
			shape->SetFillStyle(m_fillStyle);
		}
		if (position != std::numeric_limits<size_t>::max())
		{
			CheckIndex(position);
			m_shapes.insert(m_shapes.begin() + position, shape);
		}
		else
		{
			m_shapes.insert(m_shapes.end(), shape);
		}
		auto shapeFrame = shape->GetFrame();
		RecalculateFrameByShapeFrame(shapeFrame);
	}
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override
	{
		CheckIndex(index);
		return m_shapes[index];
	}
	void RemoveShapeAtIndex(size_t index) override
	{
		CheckIndex(index);
		m_shapes.erase(m_shapes.begin() + index);
	}

	RectD GetFrame() const override
	{
		return m_frame;
	}
	void SetFrame(const RectD & rect) override
	{
		double topOffest  = m_frame.top - rect.top;
		double leftOffest = m_frame.left - rect.left;
		double heightScale = m_frame.height / rect.height;
		double widthScale  = m_frame.width / rect.width;

		for (auto shapePtr : m_shapes)
		{
			auto shapeFrame = shapePtr->GetFrame();
			shapeFrame.top  = m_frame.top + (shapeFrame.top - m_frame.top) / heightScale;
			shapeFrame.top -= topOffest;
			shapeFrame.left  = m_frame.left + (shapeFrame.left - m_frame.left) / widthScale;
			shapeFrame.left -= leftOffest;
			shapeFrame.height /= heightScale;
			shapeFrame.width  /= widthScale;
			shapePtr->SetFrame(shapeFrame);
		}
		m_frame = rect;
	}
	void SetOutlineStyle(std::shared_ptr<ILineStyle> style) override
	{
		m_outlineStyle = style;
		for (auto shapePtr : m_shapes)
		{
			shapePtr->SetOutlineStyle(m_outlineStyle);
		}
	}
	std::shared_ptr<ILineStyle> GetOutlineStyle() override
	{
		return m_outlineStyle;
	}
	std::shared_ptr<const ILineStyle> GetOutlineStyle()const override
	{
		return m_outlineStyle;
	}
	void SetFillStyle(std::shared_ptr<IStyle> style) override
	{
		m_fillStyle = style;
		for (auto shapePtr : m_shapes)
		{
			shapePtr->SetFillStyle(m_fillStyle);
		}
	}
	std::shared_ptr<IStyle> GetFillStyle() override
	{
		return m_fillStyle;
	}
	std::shared_ptr<const IStyle> GetFillStyle()const override
	{
		return m_fillStyle;
	}

	std::shared_ptr<IGroupShape> GetGroup() override
	{
		return std::make_shared<CGroupShape>(*this);
	}
	std::shared_ptr<const IGroupShape> GetGroup() const override
	{
		return std::make_shared<CGroupShape>(*this);
	}

	void Draw(ICanvas & canvas) override
	{
		for (auto shapePtr : m_shapes)
		{
			shapePtr->Draw(canvas);
		}
	}

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	RectD  m_frame;
	std::shared_ptr<ILineStyle> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;

	void CheckIndex(size_t index)
	{
		if (index >= m_shapes.size())
		{
			throw std::runtime_error("Invalid index " + index);
		}
	}

	void RecalculateFrame()
	{
		for (auto shapePtr : m_shapes)
		{
			auto shapeFrame = shapePtr->GetFrame();
			RecalculateFrameByShapeFrame(shapeFrame);
		}
	}

	void RecalculateFrameByShapeFrame(RectD  shapeFrame)
	{
		if (shapeFrame.top < m_frame.top)
		{
			m_frame.top = shapeFrame.top;
		}
		if (shapeFrame.left < m_frame.left)
		{ 
			m_frame.left = shapeFrame.left;
		}
		if (shapeFrame.top + shapeFrame.height > m_frame.top + m_frame.height)
		{
			m_frame.height = shapeFrame.top + shapeFrame.height - m_frame.top;
		}
		if (shapeFrame.left + shapeFrame.width > m_frame.left + m_frame.width)
		{
			m_frame.width = shapeFrame.left + shapeFrame.width - m_frame.left;
		}
	}
};
