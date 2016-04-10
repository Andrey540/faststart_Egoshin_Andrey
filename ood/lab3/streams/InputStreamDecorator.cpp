#include "InputStreamDecorator.h"

CInputStreamDecorator::CInputStreamDecorator(IInputStreamPtr && inputStreame)
	: m_inputStream(move(inputStreame))
{}

CInputStreamDecorator::~CInputStreamDecorator()
{}

bool CInputStreamDecorator::IsEOF() const
{
	return m_inputStream->IsEOF();
}

uint8_t CInputStreamDecorator::ReadByte()
{
	return DecorateByte(m_inputStream->ReadByte());
}

std::streamsize CInputStreamDecorator::ReadBlock(void * dstBuffer, std::streamsize size)
{
	std::streamsize readSize = m_inputStream->ReadBlock(dstBuffer, size);
	DecorateBlock(dstBuffer, readSize);
	return readSize;
}
