#pragma once
#include "IInputStream.h"
class CInputStreamDecorator :
	public IInputStream
{
public:
	CInputStreamDecorator(IInputStreamPtr && inputStreame);
	~CInputStreamDecorator();

	bool IsEOF() const override;
	BYTE ReadByte() override;
	void ReadBlock(std::vector<BYTE>& dstData, size_t dataSize) override;

	virtual BYTE DecorateByte(BYTE byte) = 0;
	virtual void DecorateBlock(std::vector<BYTE>& dstData) = 0;
private:
	IInputStreamPtr m_inputStream;
};

