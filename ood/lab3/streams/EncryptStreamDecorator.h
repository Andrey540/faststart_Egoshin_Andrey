#pragma once
#include "InputStreamDecorator.h"
class CEncryptStreamDecorator : public CInputStreamDecorator
{
public:
	CEncryptStreamDecorator(IInputStreamPtr && inputStream);
	~CEncryptStreamDecorator();

	uint8_t DecorateByte(uint8_t byte) override;
	void DecorateBlock(void * dstBuffer, std::streamsize size) override;
};

