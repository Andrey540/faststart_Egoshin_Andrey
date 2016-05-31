#include "stdafx.h"
#include "ImageImpl.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

CImageImpl::CImageImpl(const std::string & srcPath, size_t width, size_t height, const std::string & dscPath)
{
	if (!fs::exists(srcPath) || fs::is_directory(srcPath))
	{
		throw std::runtime_error("Can not copy file");
	}
	fs::copy_file(srcPath, dscPath);
	m_image = CImage(dscPath, width, height);
}

CImageImpl::~CImageImpl()
{
	if (fs::exists(GetPath()))
	{
		fs::remove(GetPath());
	}
}

std::string CImageImpl::GetPath() const
{
	return m_image.GetPath();
}

size_t CImageImpl::GetWidth() const
{
	return m_image.GetWidth();
}

size_t CImageImpl::GetHeight() const
{
	return m_image.GetHeight();
}

void CImageImpl::Resize(size_t width, size_t height)
{
	m_image.Resize(width, height);
}

std::string CImageImpl::GetDescription()
{
	return "Image: " + std::to_string(m_image.GetWidth()) + " " + std::to_string(m_image.GetHeight()) + " " + m_image.GetPath();
}