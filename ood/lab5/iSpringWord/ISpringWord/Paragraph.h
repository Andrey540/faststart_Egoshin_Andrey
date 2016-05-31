#pragma once
#include "IParagraph.h"

class CParagraphImpl;

class CParagraph:public IParagraph
{
public:
	CParagraph(std::string text);
	std::string& GetText() override;
	void SetText(const std::string& text) override;
private:
	std::string m_text;
};

