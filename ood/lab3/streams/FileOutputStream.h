#pragma once
#include <fstream>
#include "IOutputStream.h"

class CFileOutputStream : public IOutputStream
{
public:
	CFileOutputStream(const std::string& fileName);
	~CFileOutputStream();

	void WriteByte(uint8_t byte) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;

private:
	std::ofstream m_file;	
};

