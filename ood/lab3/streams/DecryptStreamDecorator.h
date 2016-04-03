#pragma once
#include "OutputStreamDecorator.h"
class CDecryptStreamDecorator :
	public COutputStreamDecorator
{
public:
	CDecryptStreamDecorator(IOutputStreamPtr && outputStream);
	~CDecryptStreamDecorator();

	BYTE DecoratorByte(BYTE byte) override;
	const std::vector<BYTE>& DecoratorBlock(const std::vector<BYTE>& srcData, size_t dataSize) override;
private:
	std::vector<BYTE> m_buffer;
};

