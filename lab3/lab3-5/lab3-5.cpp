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
#include <map>
#include <vector>

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

    bool URLData::operator == (URLData otherURLData)
    {
        if (protocol == otherURLData.protocol && host == otherURLData.host &&
            port == otherURLData.port && document == otherURLData.document)
        {
            return true;
        }
        return false;
    }
};

bool ParseURL(string const& url, Protocol & protocol, int & port, string & host, string & document);
Protocol GetProtocol(string const& sourceUrl);
string GetHost(string const& url);
int GetPort(string const& url, const Protocol& protocol);
string GetDocument(string const& url);
size_t GetHostPosition(string const& url);
size_t GetPortSeparatorPosition(string const& url);
size_t GetDocumentSeparatorPosition(string const& url);
int PortStringToInt(string const& str);

void TestParseURLEmptyPortHTTP();
void TestParseURLWithPortHTTP();
void TestParseURLEmptyPortHTTPS();

const string PROTOCOL_SEPARATOR = "://";

int main(int argc, char* argv[])
{
    TestParseURLEmptyPortHTTP();
    TestParseURLWithPortHTTP();
    TestParseURLEmptyPortHTTPS();

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
        protocol = GetProtocol(url);
        host     = GetHost(url);
        port     = GetPort(url, protocol);
        document = GetDocument(url);
    }
    catch (std::exception const& e)
    {
        cout << e.what();
        return false;
    }
    return true;
}

Protocol GetProtocol(string const& sourceUrl)
{
    string url = sourceUrl;
    transform(url.begin(), url.end(), url.begin(), ::tolower);

    map <string, Protocol> protocolsLib;
    protocolsLib["http"]  = HTTP;
    protocolsLib["https"] = HTTPS;
    protocolsLib["ftp"]   = FTP;

    size_t position = url.find(PROTOCOL_SEPARATOR);
    if (position == string::npos)
    {
        throw runtime_error("Can not find protocol!");
    }
    string protocolString = url.substr(0, position);

    auto protocolType = protocolsLib.find(protocolString);
    if (protocolType == protocolsLib.end())
    {
        throw runtime_error("Undefind protocol!");
    }     
    return protocolType->second;
}

string GetHost(string const& url)
{
    size_t startPosition = GetHostPosition(url);
    size_t documentPosition = GetDocumentSeparatorPosition(url);
    size_t portPosition = GetPortSeparatorPosition(url);
    size_t endPosition = (documentPosition > portPosition) ? portPosition : documentPosition;
    return url.substr(startPosition, endPosition - startPosition);
}

int GetPort(string const& url, const Protocol& protocol)
{
    size_t documentPosition = GetDocumentSeparatorPosition(url);
    size_t portPosition = GetPortSeparatorPosition(url);

    int port = 0;
    if (documentPosition > portPosition)
    {   
        ++portPosition;
        string portString = url.substr(portPosition, documentPosition - portPosition);
        port = PortStringToInt(portString);
    }
    else
    {
        map<Protocol, int> protocolsLib;
        protocolsLib[HTTP]  = 80;
        protocolsLib[HTTPS] = 443;
        protocolsLib[FTP]   = 21;
        port = protocolsLib[protocol];
    }
    return port;
}

string GetDocument(string const& url)
{
    size_t startPosition = GetDocumentSeparatorPosition(url);
    startPosition = (startPosition == url.length()) ? startPosition : startPosition + 1;
    return url.substr(startPosition, url.length() - startPosition);
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
    try
    {
        int value = stoi(str);
        if ((value < 1) || (value > MAX_PORT_NUMBER))
        {
            throw domain_error("Port must be greater than 1 and less than 65535");
        }
        return value;
    }
    catch (invalid_argument const&)
    {
        throw domain_error("Port must be a number");
    }
}

void TestParseURLEmptyPortHTTP()
{
    URLData urlTest;
    URLData urlResult;
    urlResult.protocol = HTTP;
    urlResult.port     = 80;
    urlResult.host     = "mysite.com";
    urlResult.document = "doc/document1.html";

    ParseURL("http://mysite.com/doc/document1.html", urlTest.protocol, urlTest.port, urlTest.host, urlTest.document);
    assert(urlTest == urlResult && "Algorithm error!");
}

void TestParseURLWithPortHTTP()
{
    URLData urlTest;
    URLData urlResult;
    urlResult.protocol = HTTP;
    urlResult.port     = 100;
    urlResult.host     = "mysite.com";
    urlResult.document = "doc/document1.html";

    ParseURL("http://mysite.com:100/doc/document1.html", urlTest.protocol, urlTest.port, urlTest.host, urlTest.document);
    assert(urlTest == urlResult && "Algorithm error!");
}

void TestParseURLEmptyPortHTTPS()
{
    URLData urlTest;
    URLData urlResult;
    urlResult.protocol = HTTPS;
    urlResult.port     = 443;
    urlResult.host     = "mysite.com";
    urlResult.document = "doc/document1.html";

    ParseURL("https://mysite.com/doc/document1.html", urlTest.protocol, urlTest.port, urlTest.host, urlTest.document);
    assert(urlTest == urlResult && "Algorithm error!");
}