#include "EncryptStreamDecorator.h"

CEncryptStreamDecorator::CEncryptStreamDecorator(IInputStreamPtr && inputStream)
	: CInputStreamDecorator(move(inputStream))
{}

CEncryptStreamDecorator::~CEncryptStreamDecorator()
{}

BYTE CEncryptStreamDecorator::DecorateByte(BYTE byte)
{
	return byte;
}

void CEncryptStreamDecorator::DecorateBlock(std::vector<BYTE>& dstData)
{

}
