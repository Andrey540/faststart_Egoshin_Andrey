#pragma once
#include "AbstractCommand.h"
#include "ImageImpl.h"

class CResizeImageCommand :
	public CAbstractCommand
{
public:
	CResizeImageCommand(std::shared_ptr<CImageImpl> image, size_t width, size_t height);
	~CResizeImageCommand();

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::shared_ptr<CImageImpl> m_image;
	size_t m_width;
	size_t m_height;

	void ResizeImageAndSavePrevSize();
};

