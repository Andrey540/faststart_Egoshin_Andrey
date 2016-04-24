#include "InputStreamDecorator.h"

CInputStreamDecorator::CInputStreamDecorator(IInputStreamPtr && inputStreame)
	: m_inputStream(move(inputStreame))
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
	uint8_t *buffer = new uint8_t[static_cast<unsigned>(size)];
	std::streamsize readSize = m_inputStream->ReadBlock(buffer, size);
	std::vector<uint8_t> vectorBuffer;
	for (int i = 0; i < readSize; ++i)
	{
		vectorBuffer.push_back(buffer[i]);
	}
	return DecorateBlock(dstBuffer, vectorBuffer);
}

