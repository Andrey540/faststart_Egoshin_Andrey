#pragma once
#include "IDocument.h"
#include "History.h"
#include "DocumentItem.h"

class CDocument:public IDocument
{
public:
	CDocument();
	~CDocument();

	void SetTitle(const std::string & title) override;
	std::string GetTitle() const override;

	void InsertParagraph(const std::string& text, boost::optional<size_t> position = boost::none) override;
	void InsertImage(const std::string & path, size_t width, size_t height, boost::optional<size_t> position = boost::none) override;

	void ReplaceText(const std::string& text, size_t index) override;
	void ResizeImage(size_t width, size_t height, size_t index) override;

	size_t GetItemsCount()const override;
	void DeleteItem(size_t index) override;

	CDocumentItem const& GetItem(size_t index)const override;
	CDocumentItem & GetItem(size_t index) override;

	bool CanUndo() const override;	
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

	void Save(const std::string& path) const override;

private:
	std::string m_title;
	CHistory m_history;
	std::deque<std::shared_ptr<CDocumentItem>> m_items;
	size_t imagesCount = 0;

	void CheckPosition(size_t position) const;
	void SaveDocument(const std::string& path) const;
	void RemoveTmpFolder() const;
};