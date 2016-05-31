#include "stdafx.h"
#include "DocumentItem.h"

CDocumentItem::CDocumentItem(std::shared_ptr<CImageImpl> image)
	: m_image(image),
	  m_item(image)
{}
CDocumentItem::CDocumentItem(std::shared_ptr<CParagraphImpl> paragraph)
	: m_paragraph(paragraph),
	  m_item(paragraph)
{}

std::shared_ptr<CImageImpl> CDocumentItem::GetImage()
{
	return m_image;
}

std::shared_ptr<CParagraphImpl> CDocumentItem::GetParagraph()
{
	return m_paragraph;
}

std::string CDocumentItem::GetDescription()
{
	return  m_item->GetDescription();
}