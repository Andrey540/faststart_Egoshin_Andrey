#pragma once
#include <boost/optional.hpp>
#include "CommonTypes.h"

class IStyle
{
public:
	virtual boost::optional<bool> IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual boost::optional<RGBAColor> GetColor()const = 0;
	virtual void SetColor(RGBAColor color) = 0;

	virtual ~IStyle() = default;
};

class ILineStyle: public IStyle
{
public:
	virtual size_t GetLineWidth()const = 0;
	virtual void SetLineWidth(size_t width) = 0;

	virtual ~ILineStyle() = default;
};

class CStyle : public IStyle
{
public:
	CStyle() {}
	CStyle(RGBAColor color) 
		: m_color(color),
		  m_isEnable(true)
	{}
	boost::optional<bool> IsEnabled()const override
	{
		return m_isEnable;
	}
	void Enable(bool enable) override
	{
		m_isEnable = enable;
	}
	boost::optional<RGBAColor> GetColor()const override
	{
		return m_color;
	}
	void SetColor(RGBAColor color) override
	{
		m_color = color;
	}
private:
	boost::optional<RGBAColor> m_color;
	boost::optional<bool> m_isEnable;
};

class CLineStyle : public ILineStyle
{
public:
	CLineStyle() {}
	CLineStyle(RGBAColor color) : m_color(color) {}
	CLineStyle(RGBAColor color, size_t width)
		: m_color(color),
		  m_width(width),
		  m_isEnable(true)
	{}

	boost::optional<bool> IsEnabled()const override
	{
		return m_isEnable;
	}
	void Enable(bool enable) override
	{
		m_isEnable = enable;
	}
	boost::optional<RGBAColor> GetColor()const override
	{
		return m_color;
	}
	void SetColor(RGBAColor color) override
	{
		m_color = color;
	}

	size_t GetLineWidth()const override
	{
		return *m_width;
	}
	void SetLineWidth(size_t width) override
	{
		m_width = width;
	}
private:
	boost::optional<size_t> m_width;
	boost::optional<RGBAColor> m_color;
	boost::optional<bool> m_isEnable;
};
