#include "DecryptStreamDecorator.h"

CDecryptStreamDecorator::CDecryptStreamDecorator(IOutputStreamPtr && outputStream)
	: COutputStreamDecorator(move(outputStream))
{}

CDecryptStreamDecorator::~CDecryptStreamDecorator()
{}

uint8_t CDecryptStreamDecorator::DecorateByte(uint8_t byte)
{
	return byte;
}

const std::vector<uint8_t>& CDecryptStreamDecorator::DecorateBlock(const void * srcData, std::streamsize size)
{
	std::vector<uint8_t> buffer;
	return buffer;
}
