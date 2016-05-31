#include "stdafx.h"
#include "ParagraphImpl.h"

CParagraphImpl::CParagraphImpl(std::string text)
	: m_parahraph(text)
{}

std::string& CParagraphImpl::GetText()
{
	return m_parahraph.GetText();
}

void CParagraphImpl::SetText(const std::string& text)
{
	m_parahraph.SetText(text);
}

std::string CParagraphImpl::GetDescription()
{
	return "Paragraph: " + m_parahraph.GetText();
}

