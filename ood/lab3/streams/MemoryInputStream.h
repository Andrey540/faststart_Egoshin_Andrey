#pragma once
#include "IInputStream.h"
class CMemoryInputStream : public IInputStream
{
public:
	CMemoryInputStream();
	~CMemoryInputStream();

	bool IsEOF() const override;
	BYTE ReadByte() override;
	void ReadBlock(std::vector<BYTE>& dstData, size_t dataSize) override;
};

