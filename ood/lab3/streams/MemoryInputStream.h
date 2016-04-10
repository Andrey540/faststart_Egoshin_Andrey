#pragma once
#include "IInputStream.h"
class CMemoryInputStream : public IInputStream
{
public:
	CMemoryInputStream(std::vector<uint8_t>& buffer);
	~CMemoryInputStream();

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:
	std::vector<uint8_t>& m_buffer;
	size_t m_position = 0;
};

