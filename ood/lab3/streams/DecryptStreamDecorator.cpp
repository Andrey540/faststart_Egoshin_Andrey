#include "DecryptStreamDecorator.h"

CDecryptStreamDecorator::CDecryptStreamDecorator(IOutputStreamPtr && outputStream)
	: COutputStreamDecorator(move(outputStream))
{}

CDecryptStreamDecorator::~CDecryptStreamDecorator()
{}

BYTE CDecryptStreamDecorator::DecoratorByte(BYTE byte)
{
	return byte;
}

const std::vector<BYTE>& CDecryptStreamDecorator::DecoratorBlock(const std::vector<BYTE>& srcData, size_t dataSize)
{
	m_buffer.clear();
	std::copy(srcData.begin(), srcData.end(), m_buffer.end());
	return m_buffer;
}
