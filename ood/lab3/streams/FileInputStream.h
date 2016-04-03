#pragma once
#include "IInputStream.h"

class CFileInputStream : public IInputStream
{
public:
	CFileInputStream();
	~CFileInputStream();

	bool IsEOF() const override;
	BYTE ReadByte() override;
	void ReadBlock(std::vector<BYTE>& dstData, size_t dataSize) override;
};

