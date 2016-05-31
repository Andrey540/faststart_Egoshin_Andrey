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
	// ��������� �������� ������ � ��������� ������� (������� ����������� ��������)
	// ���� �������� position �� ������, ������� ���������� � ����� ���������
	virtual void InsertParagraph(const std::string& text, boost::optional<size_t> position = boost::none) = 0;

	//// ��������� ����������� � ��������� ������� (������� ����������� ��������)
	//// �������� path ������ ���� � ������������ �����������
	//// ��� ������� ����������� ������ ������������ � ���������� images 
	//// ��� ������������� ��������������� ������
	virtual void InsertImage(const std::string& path, size_t width, size_t height, boost::optional<size_t> position = boost::none) = 0;

	virtual void ReplaceText(const std::string& text, size_t index) = 0;
	virtual void ResizeImage(size_t width, size_t height, size_t index) = 0;

	//// ���������� ���������� ��������� � ���������
	virtual size_t GetItemsCount()const = 0;

	//// ������ � ���������
	virtual CDocumentItem const& GetItem(size_t index)const = 0;
	virtual CDocumentItem& GetItem(size_t index) = 0;

	//// ������� ������� �� ���������
	virtual void DeleteItem(size_t index) = 0;

	// ���������� ��������� ���������
	virtual std::string GetTitle()const = 0;
	// �������� ��������� ���������
	virtual void SetTitle(const std::string & title) = 0;

	// �������� � ����������� �������� Undo
	virtual bool CanUndo()const = 0;
	// �������� ������� ��������������
	virtual void Undo() = 0;

	// �������� � ����������� �������� Redo
	virtual bool CanRedo()const = 0;
	// ��������� ���������� ������� ��������������
	virtual void Redo() = 0;

	//// ��������� �������� � ������� html. ����������� ����������� � ���������� images.
	//// ���� � ������������ ����������� ������������ ���� � ������������ HTML �����
	virtual void Save(const std::string& path)const = 0;

	virtual ~IDocument() = default;
};
