#pragma once
#include <fstream>
#include "IInputStream.h"

class CFileInputStream : public IInputStream
{
public:
	CFileInputStream(const std::string& fileName);
	~CFileInputStream();

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:
	std::ifstream m_file;

	void CheckIsEOF();
};

