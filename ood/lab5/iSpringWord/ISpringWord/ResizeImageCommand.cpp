#include "stdafx.h"
#include "ResizeImageCommand.h"


CResizeImageCommand::CResizeImageCommand(std::shared_ptr<CImageImpl> image, size_t width, size_t height)
	: m_image(image),
	  m_width(width),
	  m_height(height)
{}

CResizeImageCommand::~CResizeImageCommand()
{}

void CResizeImageCommand::DoExecute()
{
	ResizeImageAndSavePrevSize();
}

void CResizeImageCommand::DoUnexecute()
{
	ResizeImageAndSavePrevSize();
}

void CResizeImageCommand::ResizeImageAndSavePrevSize()
{
	size_t width = m_image->GetWidth();
	size_t height = m_image->GetHeight();
	m_image->Resize(m_width, m_height);
	m_width = width;
	m_height = height;
}
