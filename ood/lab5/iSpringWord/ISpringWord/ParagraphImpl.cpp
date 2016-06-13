#include "stdafx.h"
#include "ParagraphImpl.h"

CParagraphImpl::CParagraphImpl(std::string text)
	: m_paragraph(text)
{}

std::string& CParagraphImpl::GetText()
{
	return m_paragraph.GetText();
}

void CParagraphImpl::SetText(const std::string& text)
{
	m_paragraph.SetText(text);
}

std::string CParagraphImpl::GetDescription()
{
	return "Paragraph: " + m_paragraph.GetText();
}

