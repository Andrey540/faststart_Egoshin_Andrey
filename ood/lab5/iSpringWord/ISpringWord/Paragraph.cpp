#include "stdafx.h"
#include "Paragraph.h"
#include "ParagraphImpl.h"

CParagraph::CParagraph(std::string text)
	: m_text(text)
{}

std::string& CParagraph::GetText()
{
	return m_text;
}

void CParagraph::SetText(const std::string& text)
{
	m_text = text;
}