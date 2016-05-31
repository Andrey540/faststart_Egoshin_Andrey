#include "stdafx.h"
#include "Document.h"
#include "ParagraphImpl.h"
#include "ChangeStringCommand.h"
#include "InsertItemCommand.h"
#include "DeleteItemCommand.h"
#include "ResizeImageCommand.h"
#include "HtmlDocumentBuilder.h"
#include <filesystem>
#include <fstream>
#include <experimental/filesystem>

using namespace std;
namespace fs = experimental::filesystem;

static const string TMP_PATH = "tmp";

CDocument::CDocument()
{
	RemoveTmpFolder();
	fs::create_directories(TMP_PATH);
}

CDocument::~CDocument()
{
	RemoveTmpFolder();
}

void CDocument::SetTitle(const std::string & title)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

void CDocument::InsertParagraph(const std::string& text, boost::optional<size_t> position)
{
	if (position != boost::none)
	{
		CheckPosition(*position);
	}	
	m_history.AddAndExecuteCommand(
		make_unique<CInsertItemCommand>(m_items, make_shared<CDocumentItem>(make_shared<CParagraphImpl>(text)), position)
	);
}

void CDocument::InsertImage(const std::string & path, size_t width, size_t height, boost::optional<size_t> position)
{
	if (position != boost::none)
	{
		CheckPosition(*position);
	}
	++imagesCount;
	string preparedPath = TMP_PATH + "/" + to_string(imagesCount);
	size_t index = path.rfind('.');
	if (index != string::npos)
	{
		preparedPath += "." + path.substr(index + 1);
	}
	m_history.AddAndExecuteCommand(
		make_unique<CInsertItemCommand>(m_items, make_shared<CDocumentItem>(make_shared<CImageImpl>(path, width, height, preparedPath)), position)
	);
}

void CDocument::ResizeImage(size_t width, size_t height, size_t index)
{
	CheckPosition(index);
	auto image = GetItem(index).GetImage();
	if (image == nullptr)
	{
		throw invalid_argument("Item is not paragraph");
	}
	m_history.AddAndExecuteCommand(make_unique<CResizeImageCommand>(image, width, height));
}

void CDocument::ReplaceText(const std::string& text, size_t index)
{
	CheckPosition(index);
	auto paragraph = GetItem(index).GetParagraph();
	if (paragraph == nullptr)
	{
		throw invalid_argument("Item is not image");
	}
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(paragraph->GetText(), text));
}

void CDocument::DeleteItem(size_t index)
{
	CheckPosition(index);
	m_history.AddAndExecuteCommand(make_unique<CDeleteItemCommand>(m_items, index));
}

size_t CDocument::GetItemsCount() const
{
	return m_items.size();
}

CDocumentItem const& CDocument::GetItem(size_t index) const
{
	CheckPosition(index);
	return *m_items[index];
}

CDocumentItem & CDocument::GetItem(size_t index)
{
	CheckPosition(index);
	return *m_items[index];
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}

void CDocument::Save(const std::string& path) const
{
	fs::create_directories(path);
	string imagesPath = path + "/images";
	fs::create_directories(imagesPath);
	SaveDocument(path + "/index.html");
	for (auto item : m_items)
	{
		auto image = item->GetImage();
		if (image != nullptr)
		{
			string path = image->GetPath();
			size_t index = path.rfind('/');
			if (index != string::npos)
			{
				string fileName = path.substr(index + 1);
				fs::copy_file(path, imagesPath + "/" + fileName);
			}
		}
	}
}

void CDocument::SaveDocument(const std::string& path) const
{
	CHtmlDocumentBuilder htmlBuilder;
	htmlBuilder.AddTitle(m_title);
	for (auto item : m_items)
	{
		auto image = item->GetImage();
		if (image != nullptr)
		{
			htmlBuilder.AddImage(image->GetWidth(), image->GetHeight(), image->GetPath());
		}
		auto paragraph = item->GetParagraph();
		if (paragraph != nullptr)
		{
			htmlBuilder.AddParagraph(paragraph->GetText());
		}
	}
	htmlBuilder.Save(path);
}

void CDocument::CheckPosition(size_t position) const
{
	if (position >= GetItemsCount())
	{
		throw invalid_argument("Incorrect position");
	}
}

void CDocument::RemoveTmpFolder() const
{
	if (fs::exists(TMP_PATH) && fs::is_directory(TMP_PATH))
	{
		fs::remove_all(TMP_PATH);
	}
}