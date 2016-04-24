#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <iostream>
#include <functional>
#include "FileInputStream.h"
#include "FileOutputStream.h"
#include "EncryptStreamDecorator.h"
#include "DecryptStreamDecorator.h"
#include "CompressStreamDecorator.h"
#include "DecompressStreamDecorator.h"

class CDecoratorCreator
{
public:
	CDecoratorCreator();
	~CDecoratorCreator();

	std::unique_ptr<IInputStream> CreateInputStream(std::vector<std::string> && parameters);
	std::unique_ptr<IOutputStream> CreateOutputStream(std::vector<std::string> && parameters);
};

