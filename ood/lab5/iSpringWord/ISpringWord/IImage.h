#pragma once
#include <string>

class IImage
{
public:
	//// Возвращает путь относительно каталога документа
	virtual std::string GetPath()const = 0;

	//// Ширина изображения в пикселях
	virtual size_t GetWidth()const = 0;
	//// Высота изображения в пикселях
	virtual size_t GetHeight()const = 0;

	//// Изменяет размер изображения
	virtual void Resize(size_t width, size_t height) = 0;

	virtual ~IImage() = default;
};
