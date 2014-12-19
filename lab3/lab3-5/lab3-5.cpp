// lab3-5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdexcept>
#include <boost\optional.hpp>
#include <string>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace boost;
using namespace std;

enum Protocol
{
    HTTP,
    HTTPS,
    FTP
};

struct URLData
{
    Protocol protocol;
    string host;
    int port;
    string document;

    URLData()
    {
    }

    URLData(Protocol& protocol, int port, string& host, string document)
    {
        this->protocol = protocol;
        this->host = host;
        this->port = port;
        this->document = document;
        return;
    }

    bool const operator == (URLData otherURLData)
    {
        if (protocol == otherURLData.protocol && host == otherURLData.host &&
            port == otherURLData.port && document == otherURLData.document)
        {
            return true;
        }
        return false;
    }

    bool const operator != (URLData otherURLData)
    {
        return !(*this == otherURLData);
    }
};

bool ParseURL(string const& url, Protocol & protocol, int & port, string & host, string & document);
bool BeginsWith(const string& haystack,const string& needle);
Protocol GetProtocol(string const& sourceUrl);
string GetHost(string const& url, size_t& position);
int GetPort(string const& url, const Protocol& protocol, size_t& position);
string GetDocument(string const& url, size_t& position);
size_t GetHostPosition(string const& url);
size_t GetPortSeparatorPosition(string const& url);
size_t GetDocumentSeparatorPosition(string const& url);
int PortStringToInt(string const& str);

void AssertParsingURLSucceed(string const& url, Protocol protocol, int port, string host, string document);
void AssertParsingErrorURL(string const& url, Protocol protocol, int port, string host, string document);
void TestParseURLEmptyPortHTTP();
void TestParseURLWithPortHTTP();
void TestParseURLEmptyPortHTTPS();
void TestParsingURLsWithDefaultPortAndEmptyDocument();
void TestParsingURLsWithInvalidPort();

const string PROTOCOL_SEPARATOR = "://";

int main(int argc, char* argv[])
{
    TestParseURLEmptyPortHTTP();
    TestParseURLWithPortHTTP();
    TestParseURLEmptyPortHTTPS();
    TestParsingURLsWithDefaultPortAndEmptyDocument();
    TestParsingURLsWithInvalidPort();

    string newString;
    cout << "Enter url" << endl;
    while (cin >> newString)
	{
        URLData urlInfo;
        if (ParseURL(newString, urlInfo.protocol, urlInfo.port, urlInfo.host, urlInfo.document))
        {
            cout << newString << endl;
            cout << "HOST: " << urlInfo.host << endl;
            cout << "PORT: " << urlInfo.port << endl;
            cout << "DOCUMENT: " << urlInfo.document << endl;
        }
        else
        {
            cout << "Parse url error!" << endl;
        }
	}
	return 0;
}

bool ParseURL(string const& url, Protocol & protocol, int & port, string & host, string & document)
{
    try
    {
        size_t position;
        protocol = GetProtocol(url);
        host     = GetHost(url, position);
        port     = GetPort(url, protocol, position);
        document = GetDocument(url, position);
    }
    catch (std::exception const& e)
    {
        cout << e.what();
        return false;
    }
    return true;
}

bool BeginsWith(const string& haystack,const string& needle)
{
    return haystack.compare(0, needle.length(), needle) == 0;
}

Protocol GetProtocol(string const& sourceUrl)
{
    Protocol result;

    if (BeginsWith(sourceUrl, "http://"))
    {
        result = HTTP;
    }
    else if(BeginsWith(sourceUrl, "https://"))
    {
        result = HTTPS;
    }
    else if(BeginsWith(sourceUrl, "ftp://"))
    {
        result = FTP;
    }
    else
    {
        throw runtime_error("Undefind protocol!");
    }

    return result;
}

string GetHost(string const& url, size_t& position)
{
    size_t startPosition = GetHostPosition(url);
    size_t documentPosition = GetDocumentSeparatorPosition(url);
    size_t portPosition = GetPortSeparatorPosition(url);
    position = (documentPosition > portPosition) ? portPosition : documentPosition;
    return url.substr(startPosition, position - startPosition);
}

int GetPort(string const& url, const Protocol& protocol, size_t& position)
{
    size_t documentPosition = GetDocumentSeparatorPosition(url);
    int port = 0;
    if (documentPosition != position)
    {   
        ++position;
        string portString = url.substr(position, documentPosition - position);
        port = PortStringToInt(portString);
        position = documentPosition;
    }
    else
    {
        if (protocol == HTTP)
        {
            port = 80;
        }
        else if (protocol == HTTPS)
        {
            port = 443;
        }
        else
        {
            port = 21;
        }
    }
    return port;
}

string GetDocument(string const& url, size_t& position)
{
    position = (position == url.length()) ? position : position + 1;
    return url.substr(position, url.length() - position);
}

size_t GetHostPosition(string const& url)
{
    size_t position = url.find(PROTOCOL_SEPARATOR);
    if (position == string::npos)
    {
        throw runtime_error("Incorrect url format!");
    }
    return position + PROTOCOL_SEPARATOR.length();
}

size_t GetPortSeparatorPosition(string const& url)
{
    size_t startPosition = GetHostPosition(url);
    size_t portPosition = url.find(":", startPosition);
    return (portPosition == string::npos) ? url.length() : portPosition;
}

size_t GetDocumentSeparatorPosition(string const& url)
{
    size_t startPosition = GetHostPosition(url);
    size_t documentSeparatorPosition = url.find("/", startPosition);
    return (documentSeparatorPosition == string::npos) ? url.length() : documentSeparatorPosition;
}

int PortStringToInt(string const& str)
{
    const int MAX_PORT_NUMBER = 65535;
    char* pLastChar = nullptr;

    int value = strtol(str.c_str(), &pLastChar, 10);
    if((str.c_str() == '\0') || (*pLastChar != '\0'))
    {
        throw domain_error("Port must be a number\n");
    }
    if ((value < 1) || (value > MAX_PORT_NUMBER))
    {
        throw domain_error("Port must be greater than 1 and less than 65535\n");
    }
    return value;
}

void TestParseURLEmptyPortHTTP()
{
    AssertParsingURLSucceed("http://mysite.com/doc/document1.html", HTTP, 80, "mysite.com", "doc/document1.html");
}

void TestParseURLWithPortHTTP()
{
    AssertParsingURLSucceed("http://mysite.com:100/doc/document1.html", HTTP, 100, "mysite.com", "doc/document1.html");
}

void TestParseURLEmptyPortHTTPS()
{
    AssertParsingURLSucceed("https://mysite.com/doc/document1.html", HTTPS, 443, "mysite.com", "doc/document1.html");
}

void TestParsingURLsWithDefaultPortAndEmptyDocument()
{
    AssertParsingURLSucceed("http://yandex.ru", HTTP, 80, "yandex.ru", "");
    AssertParsingURLSucceed("https://yandex.ru", HTTPS, 443, "yandex.ru", "");
    AssertParsingURLSucceed("ftp://yandex.ru", FTP, 21, "yandex.ru", "");
}

void TestParsingURLsWithInvalidPort()
{
    AssertParsingErrorURL("http://ya.ru:65535:/doc.txt", HTTP, 65535, "ya.ru", "doc.txt");
    AssertParsingErrorURL("http://ya.ru:80doc", HTTPS, 80, "ya.ru", "");
}

void AssertParsingURLSucceed(string const& url, Protocol protocol, int port, string host, string document)
{
    URLData urlTest;
    URLData urlResult(protocol, port, host, document);

    ParseURL(url, urlTest.protocol, urlTest.port, urlTest.host, urlTest.document);
    assert(urlTest == urlResult && "Algorithm error!");

    return;
}

void AssertParsingErrorURL(string const& url, Protocol protocol, int port, string host, string document)
{
    URLData urlTest;
    URLData urlResult(protocol, port, host, document);

    ParseURL(url, urlTest.protocol, urlTest.port, urlTest.host, urlTest.document);
    assert(urlTest != urlResult && "Algorithm error!");

    return;
}