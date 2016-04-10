#pragma once
#include "OutputStreamDecorator.h"
class CDecryptStreamDecorator :
	public COutputStreamDecorator
{
public:
	CDecryptStreamDecorator(IOutputStreamPtr && outputStream);
	~CDecryptStreamDecorator();

	uint8_t DecorateByte(uint8_t byte) override;
	const std::vector<uint8_t>& DecorateBlock(const void * srcData, std::streamsize size) override;
};

