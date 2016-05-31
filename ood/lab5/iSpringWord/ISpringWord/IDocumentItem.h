#pragma once
#include <string>

class IDocumentItem
{
public:
	virtual ~IDocumentItem() = default;
	virtual std::string GetDescription() = 0;
};

