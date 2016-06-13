#include "stdafx.h"
#include "HtmlDocumentBuilder.h"
#include <fstream>

CHtmlDocumentBuilder::CHtmlDocumentBuilder()
{}

CHtmlDocumentBuilder::~CHtmlDocumentBuilder()
{}

void CHtmlDocumentBuilder::AddTitle(const std::string & text)
{
	m_title = text;
}

void CHtmlDocumentBuilder::AddParagraph(const std::string & text)
{
	m_documentBody += "    <p>" + text + "</p>\n";
}

void CHtmlDocumentBuilder::AddImage(size_t width, size_t height, const std::string & path)
{
	m_documentBody += "    <img style='width: " + std::to_string(width) + "px; height: " +
				   std::to_string(height) + "px;' src='" + path + "'" + " / >\n";
}

void CHtmlDocumentBuilder::Save(const std::string & path)
{
	std::ofstream file;
	file.open(path);
	if (!file.is_open())
	{
		throw std::ios_base::failure("Can not open file");
	}

	file << "<!DOCTYPE html>\n";
	file << "<html>\n";
	file << "  <head>\n";
	file << "    <title>" << m_title << "</title>\n";
	file << "  </head>\n";
	file << "  <body>\n";
	file << m_documentBody;
	file << "  </body>\n";
	file << "</html>\n";

	file.close();
}