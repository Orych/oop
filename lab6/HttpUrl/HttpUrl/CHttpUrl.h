#pragma once
#include <string>

class CHttpUrl
{
public:
	enum class Protocol
	{
		HTTP,
		HTTPS
	};

	CHttpUrl(std::string const& url);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol const& protocol = Protocol::HTTP);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol const& protocol, unsigned short port);


	std::string GetURL() const;
	const std::string& GetDomain() const;
	const std::string& GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

	static std::string ProtocolToString(Protocol const& protocol);



private:
	void SetUrl(std::string const& url);

	Protocol ParseProtocol(std::string protocol) const;
	unsigned short ParsePort(std::string const& port, Protocol const& protocol) const;
	std::string ParseDocument(std::string const& document) const;
	unsigned short GetDefaultPort(Protocol const& protocol) const;


	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	unsigned short m_port;
};