#include "stdafx.h"
#include "Image.h"

CImage::CImage(const std::string & path, size_t width, size_t height)
	: m_path(path)
{
	Resize(width, height);
}

std::string CImage::GetPath() const
{
	return m_path;
}

size_t CImage::GetWidth() const
{
	return m_width;
}

size_t CImage::GetHeight() const
{
	return m_height;
}

void CImage::Resize(size_t width, size_t height)
{
	CheckParameter(width, "Invalid width value");
	CheckParameter(height, "Invalid height value");
	m_width = width;
	m_height = height;
}

void CImage::CheckParameter(size_t parameter, const std::string& errorMsg)
{
	static const size_t MAX_SIZE = 10000;
	if (parameter < 1 || parameter > MAX_SIZE)
	{
		throw std::invalid_argument(errorMsg);
	}
}