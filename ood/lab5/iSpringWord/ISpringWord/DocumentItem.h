#pragma once
#include <memory>
#include "IDocumentItem.h"
#include "ImageImpl.h"
#include "ParagraphImpl.h"

class CDocumentItem : public IDocumentItem
{
public:
	CDocumentItem(std::shared_ptr<CImageImpl> image);
	CDocumentItem(std::shared_ptr<CParagraphImpl> paragraph);
	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<CImageImpl> GetImage();
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<CParagraphImpl> GetParagraph();

	std::string GetDescription() override;

private:
	std::shared_ptr<CImageImpl> m_image;
	std::shared_ptr<CParagraphImpl> m_paragraph;
	std::shared_ptr<IDocumentItem> m_item;
};
