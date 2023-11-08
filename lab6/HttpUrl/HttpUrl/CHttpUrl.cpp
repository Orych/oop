#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <map>
#include <regex>
#include <stdexcept>


const std::map<CHttpUrl::Protocol, unsigned short> PORTS = {
	{ CHttpUrl::Protocol::HTTP, 80 },
	{ CHttpUrl::Protocol::HTTPS, 443 }
};

constexpr int MIN_PORT = 1;
constexpr int MAX_PORT = 65535;
	
const std::string URL_REGULAR_EXPRESSION = R"(^(https?)://([-.[:alnum:]]+)(:([[:digit:]]+))?(/(.*))*$)";

// уровень безопасности кода, 
CHttpUrl::CHttpUrl(std::string const& url)
{
	try
	{
		SetUrl(url);
	}
	catch (const std::exception& error)
	{
		throw CUrlParsingError(error.what());
	}
}


CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol const& protocol, unsigned short port)
{
	if (domain.empty())
	{
		throw CUrlParsingError("Domain can't be empty");
	}
	if (port < MIN_PORT || port > MAX_PORT)
	{
		throw CUrlParsingError("Invalid port. Port must be in segment [1, 65535]");
	}

	m_protocol = protocol;
	m_domain = domain;
	m_port = port;
	m_document = ParseDocument(document);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol const& protocol)
	: CHttpUrl(domain, document, protocol, GetDefaultPort(protocol))
{
}

std::string CHttpUrl::GetURL() const
{
	std::string port = (m_port != GetDefaultPort(m_protocol)) ? ":" + std::to_string(m_port) : "";

	return ProtocolToString(m_protocol) + "://" + m_domain + port + m_document;
}

const std::string& CHttpUrl::GetDomain() const
{
	return m_domain;
}

const std::string& CHttpUrl::GetDocument() const
{
	return m_document;
}

CHttpUrl::Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::ProtocolToString(Protocol const& protocol)
{
	if (protocol == Protocol::HTTP)
	{
		return "http";
	}
	else if (protocol == Protocol::HTTPS)
	{
		return "https";
	}
	else
	{
		throw CUrlParsingError("A protocol doesn't exist.");
	}
}

CHttpUrl::Protocol CHttpUrl::ParseProtocol(std::string protocol) const
{
	std::transform(protocol.begin(), protocol.end(), protocol.begin(),
		[](unsigned char c) { return std::tolower(c); });

	if (protocol == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocol == "https")
	{
		return Protocol::HTTPS;
	}
	else
	{
		throw CUrlParsingError("Invalid protocol.");
	}
}

void CHttpUrl::SetUrl(std::string const& url)
{
	std::smatch matches;
	std::regex regex(URL_REGULAR_EXPRESSION);
	std::regex_search(url, matches, regex);

	if (matches.empty())
	{
		throw CUrlParsingError("Invalid url. Format: protocol://domain[:<port>]/document");
	}

	m_protocol = ParseProtocol(matches[1]);
	m_domain = matches[2];
	m_port = ParsePort(matches[4], m_protocol);
	m_document = ParseDocument(matches[5]);
}

unsigned short CHttpUrl::GetDefaultPort(Protocol const& protocol) const
{
	auto it = PORTS.find(protocol);

	if (it != PORTS.end())
	{
		return it->second; 
	}
	else
	{
		throw CUrlParsingError("Protocol doesn't have default port.");
	}
}

std::string CHttpUrl::ParseDocument(std::string const& document) const
{
	return (document.empty() || document[0] != '/') ? '/' + document : document;
}

unsigned short CHttpUrl::ParsePort(std::string const& port, Protocol const& protocol) const
{
	if (port.empty())
	{
		return GetDefaultPort(protocol);
	}

	int resultPort;
	try
	{
		resultPort = std::stoi(port.c_str());
	}
	catch (const std::exception& ex)
	{
		throw CUrlParsingError("Error when trying to parse a port to a number");
	}

	if (resultPort >= MIN_PORT && resultPort <= MAX_PORT)
	{
		return resultPort;
	}
	else
	{
		throw CUrlParsingError("Invalid port. Port should be in [1, 65535]");
	}
}