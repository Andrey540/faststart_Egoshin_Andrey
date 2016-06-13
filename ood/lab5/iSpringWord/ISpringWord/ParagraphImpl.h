#pragma once
#include "Paragraph.h"
#include "IDocumentItem.h"

class CParagraphImpl : public IDocumentItem, IParagraph
{
public:
	CParagraphImpl(std::string text);

	std::string& GetText();
	void SetText(const std::string& text);

	std::string GetDescription() override;

private:
	CParagraph m_paragraph;
};

