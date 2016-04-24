#pragma once
#include "OutputStreamDecorator.h"
class CDecompressStreamDecorator :
	public COutputStreamDecorator
{
public:
	CDecompressStreamDecorator(IOutputStreamPtr && outputStream);
	~CDecompressStreamDecorator();

protected:
	uint8_t DecorateByte(uint8_t byte) override;
	void DecorateBlock(const void * srcData, std::streamsize size, std::vector<uint8_t>& buffer) override;
private:
	void FilleBuffer(std::vector<uint8_t>& buffer, uint8_t byte, std::streamsize size);
};
