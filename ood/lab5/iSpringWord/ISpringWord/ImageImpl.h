#pragma once
#include "Image.h"
#include "IDocumentItem.h"

class CImageImpl : public IDocumentItem, IImage
{
public:
	CImageImpl(const std::string & srcPath, size_t width, size_t height, const std::string & dscPath);
	~CImageImpl();

	std::string GetPath()const override;
	size_t GetWidth()const override;
	size_t GetHeight()const override;
	void Resize(size_t width, size_t height) override;

	std::string GetDescription() override;
	std::string GetName() const;

private:
	CImage m_image;
};

