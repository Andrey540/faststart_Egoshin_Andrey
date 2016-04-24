#pragma once
#include "InputStreamDecorator.h"

class CCompressStreamDecorator :
	public CInputStreamDecorator
{
public:
	CCompressStreamDecorator(IInputStreamPtr && inputStream);
	~CCompressStreamDecorator();

protected:
	uint8_t DecorateByte(uint8_t byte) override;
	std::streamsize DecorateBlock(void * dstBuffer, std::vector<uint8_t>& readBuffer) override;
};
