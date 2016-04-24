#include "OutputStreamDecorator.h"

COutputStreamDecorator::COutputStreamDecorator(IOutputStreamPtr && outputStreame)
	: m_outputStream(move(outputStreame))
{}

void COutputStreamDecorator::WriteByte(uint8_t byte)
{
	m_outputStream->WriteByte(DecorateByte(byte));
}

void COutputStreamDecorator::WriteBlock(const void * srcData, std::streamsize size)
{
	std::vector<uint8_t> decoratedBuffer;
	DecorateBlock(srcData, size, decoratedBuffer);

	uint8_t *buffer = new uint8_t[decoratedBuffer.size()];
	for (unsigned i = 0; i < decoratedBuffer.size(); ++i)
	{
		buffer[i] = decoratedBuffer[i];
	};
	m_outputStream->WriteBlock(buffer, decoratedBuffer.size());
}
