#pragma once
#include <memory>
#include <string>
#include <boost\optional.hpp>
#include <boost\none.hpp>
#include "IParagraph.h"
#include "IImage.h"
#include "DocumentItem.h"

class IDocument
{
public:
	// Вставляет параграф текста в указанную позицию (сдвигая последующие элементы)
	// Если параметр position не указан, вставка происходит в конец документа
	virtual void InsertParagraph(const std::string& text, boost::optional<size_t> position = boost::none) = 0;

	//// Вставляет изображение в указанную позицию (сдвигая последующие элементы)
	//// Параметр path задает путь к вставляемому изображению
	//// При вставке изображение должно копироваться в подкаталог images 
	//// под автоматически сгенерированным именем
	virtual void InsertImage(const std::string& path, size_t width, size_t height, boost::optional<size_t> position = boost::none) = 0;

	virtual void ReplaceText(const std::string& text, size_t index) = 0;
	virtual void ResizeImage(size_t width, size_t height, size_t index) = 0;

	//// Возвращает количество элементов в документе
	virtual size_t GetItemsCount()const = 0;

	//// Доступ к элементам
	virtual CDocumentItem const& GetItem(size_t index)const = 0;
	virtual CDocumentItem& GetItem(size_t index) = 0;

	//// Удаляет элемент из документа
	virtual void DeleteItem(size_t index) = 0;

	// Возвращает заголовок документа
	virtual std::string GetTitle()const = 0;
	// Изменяет заголовок документа
	virtual void SetTitle(const std::string & title) = 0;

	// Сообщает о доступности операции Undo
	virtual bool CanUndo()const = 0;
	// Отменяет команду редактирования
	virtual void Undo() = 0;

	// Сообщает о доступности операции Redo
	virtual bool CanRedo()const = 0;
	// Выполняет отмененную команду редактирования
	virtual void Redo() = 0;

	//// Сохраняет документ в формате html. Изображения сохраняются в подкаталог images.
	//// Пути к изображениям указываются относительно пути к сохраняемому HTML файлу
	virtual void Save(const std::string& path)const = 0;

	virtual ~IDocument() = default;
};
