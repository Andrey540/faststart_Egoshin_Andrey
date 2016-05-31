// ISpringWord.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Menu.h"
#include "Document.h"

using namespace std;
using namespace std::placeholders;

namespace
{

class CEditor
{
public:
	CEditor()  //-V730
		:m_document(make_unique<CDocument>())
	{
		m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
		m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
		AddMenuItem("setTitle", "Changes title. Args: <new title>", &CEditor::SetTitle);
		AddMenuItem("insertParagraph", "Insert paragraph. Args: <position>|end <text>", &CEditor::InsertParagraph);
		AddMenuItem("insertImage", "Insert image. Args: <position>|end <width> <height> <path>", &CEditor::InsertImage);
		AddMenuItem("replaceText", "Replace text from paragraph. Args: <position> <text>", &CEditor::ReplaceText);
		AddMenuItem("resizeImage", "Resize image. Args: <position> <width> <height>", &CEditor::ResizeImage);
		AddMenuItem("deleteItem", "Delete item. Args: <position>", &CEditor::DeleteItem);
		AddMenuItem("getItemsCount", "Print items count", &CEditor::GetItemsCount);
		AddMenuItem("save", "Save document. Args: <path>", &CEditor::Save);
		m_menu.AddItem("list", "Show document", bind(&CEditor::List, this, _1));
		AddMenuItem("undo", "Undo command", &CEditor::Undo);
		AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
	}

	void Start()
	{
		m_menu.Run();
	}

private:
	// Указатель на метод класса CEditor, принимающий istream& и возвращающий void
	typedef void (CEditor::*MenuHandler)(istream & in);

	void AddMenuItem(const string & shortcut, const string & description, MenuHandler handler)
	{
		m_menu.AddItem(shortcut, description, bind(handler, this, _1));
	}

	void SetTitle(istream & in)
	{
		string title = GetTextFromStream(in);
		m_document->SetTitle(title);
	}

	void InsertParagraph(istream & in)
	{
		boost::optional<size_t> position = GetPositionFromStream(in);
		string text = GetTextFromStream(in);		
		m_document->InsertParagraph(text, position);
	}

	void InsertImage(istream & in)
	{
		boost::optional<size_t> position = GetPositionFromStream(in);
		size_t width = GetNumberFromStream(in);
		size_t height = GetNumberFromStream(in);
		string path = GetStringFromStream(in);
		m_document->InsertImage(path, width, height, position);
	}

	void ReplaceText(istream & in)
	{
		size_t position = GetNumberFromStream(in);
		string text = GetTextFromStream(in);
		m_document->ReplaceText(text, position);
	}

	void ResizeImage(istream & in)
	{
		size_t position = GetNumberFromStream(in);
		size_t width = GetNumberFromStream(in);
		size_t height = GetNumberFromStream(in);
		m_document->ResizeImage(width, height, position);
	}

	void DeleteItem(istream & in)
	{
		size_t position = GetNumberFromStream(in);
		m_document->DeleteItem(position);
	}

	void GetItemsCount(istream &)
	{
		cout << m_document->GetItemsCount() << endl;
	}

	void List(istream &)
	{
		cout << "-------------" << endl;
		cout << m_document->GetTitle() << endl;
		for (size_t i = 0; i < m_document->GetItemsCount(); ++i)
		{
			auto item = m_document->GetItem(i);
			cout << i << ". " << item.GetDescription() << endl;
		}
		cout << "-------------" << endl;
	}

	void Undo(istream &)
	{
		if (m_document->CanUndo())
		{
			m_document->Undo();
		}
		else
		{
			cout << "Can't undo" << endl;
		}
	}

	void Redo(istream &)
	{
		if (m_document->CanRedo())
		{
			m_document->Redo();
		}
		else
		{
			cout << "Can't redo" << endl;
		}
	}

	void Save(istream & in)
	{
		string path = GetStringFromStream(in);
		m_document->Save(path);
	}

	string GetTextFromStream(istream & in)
	{
		string head;
		string tail;

		if (in >> head)
		{
			getline(in, tail);
		}
		return head + tail;
	}

	boost::optional<size_t> GetPositionFromStream(istream & in)
	{
		string positionStr;
		boost::optional<size_t> position;		
		if (in >> positionStr && positionStr != "end")
		{
			position = GetNumberFromStream(in);
		}		
		return position;
	}

	size_t GetNumberFromStream(istream & in)
	{
		size_t number;
		if (!(in >> number))
		{
			throw invalid_argument("Invalid number format");
		}
		return number;
	}

	std::string GetStringFromStream(istream & in)
	{
		std::string result;
		if (!(in >> result))
		{
			throw invalid_argument("Invalid string format");
		}
		return result;
	}

	CMenu m_menu;
	unique_ptr<IDocument> m_document;
};

}

int main()
{
	CEditor editor;
	editor.Start();
    return 0;
}

