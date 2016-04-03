#pragma once
#include "InputStreamDecorator.h"
class CEncryptStreamDecorator : public CInputStreamDecorator
{
public:
	CEncryptStreamDecorator(IInputStreamPtr && inputStream);
	~CEncryptStreamDecorator();

	BYTE DecorateByte(BYTE byte) override;
	void DecorateBlock(std::vector<BYTE>& dstData) override;
};

