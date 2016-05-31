#pragma once
class CHtmlDocumentBuilder
{
public:
	CHtmlDocumentBuilder();
	~CHtmlDocumentBuilder();

	void AddTitle(const std::string & text);
	void AddParagraph(const std:: string & text);
	void AddImage(size_t width, size_t height, const std::string & path);
	void Save(const std::string & path);

private:
	std::string m_title;
	std::string m_documentBody;
};

