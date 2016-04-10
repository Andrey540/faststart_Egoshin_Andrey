#include "EncryptStreamDecorator.h"

CEncryptStreamDecorator::CEncryptStreamDecorator(IInputStreamPtr && inputStream)
	: CInputStreamDecorator(move(inputStream))
{}

CEncryptStreamDecorator::~CEncryptStreamDecorator()
{}

uint8_t CEncryptStreamDecorator::DecorateByte(uint8_t byte)
{
	return byte;
}

void CEncryptStreamDecorator::DecorateBlock(void * dstBuffer, std::streamsize size)
{

}
