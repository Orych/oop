#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HttpUrl/CHttpUrl.h"

TEST_CASE("constructor URL parse from string")
{

	// разбить на разные test_case 
	CHttpUrl url("https://www.volgatech.net/news/");
	REQUIRE(url.GetDomain() == "www.volgatech.net");
	REQUIRE(url.GetDocument() == "/news/");
	REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	REQUIRE(url.GetPort() == 443);

	CHttpUrl url1("http://www.volgatech");
	REQUIRE(url1.GetDomain() == "www.volgatech");
	REQUIRE(url1.GetDocument() == "/");
	REQUIRE(url1.GetProtocol() == CHttpUrl::Protocol::HTTP);
	REQUIRE(url1.GetPort() == 80);

	REQUIRE_NOTHROW(CHttpUrl("http://volgatech.net:65535"));
	REQUIRE_NOTHROW(CHttpUrl("http://volgatech.net:1"));

	SECTION("incorrect URL parse")
	{
		REQUIRE_THROWS_AS(CHttpUrl("http:://volgatech.net"), std::exception);
		REQUIRE_THROWS_AS(CHttpUrl("httpq://volgatech.net"), std::exception);
		REQUIRE_THROWS_AS(CHttpUrl("http://volgatech.net:65536"), std::exception);
		REQUIRE_THROWS_AS(CHttpUrl("http://volgatech.net:0"), std::exception);
	}
}

TEST_CASE("constructor URL parse from domain, document, [protocol]")
{
	CHttpUrl url("www.volgatech", "/news", CHttpUrl::Protocol::HTTPS);
	REQUIRE(url.GetDomain() == "www.volgatech");
	REQUIRE(url.GetDocument() == "/news");
	REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	REQUIRE(url.GetPort() == 443);

	SECTION("without protocol")
	{
		CHttpUrl url1("www.volgatech", "/news");
		REQUIRE(url1.GetProtocol() == CHttpUrl::Protocol::HTTP);
	}

	SECTION("document without '/'")
	{
		CHttpUrl url1("www.volgatech", "news");
		REQUIRE(url1.GetDocument() == "/news");

		CHttpUrl url2("www.volgatech", "");
		REQUIRE(url2.GetDocument() == "/");
	}

	SECTION("incorrect URL parse")
	{
		REQUIRE_THROWS_AS(CHttpUrl("", "/news"), std::exception);
	}
}

TEST_CASE("Constructor URL parse from domain, document, protocol, port")
{
	CHttpUrl url("www.volgatech", "/news", CHttpUrl::Protocol::HTTPS, 123);
	REQUIRE(url.GetDomain() == "www.volgatech");
	REQUIRE(url.GetDocument() == "/news");
	REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	REQUIRE(url.GetPort() == 123);

	SECTION("document without '/'")
	{
		CHttpUrl url1("www.volgatech", "news", CHttpUrl::Protocol::HTTPS, 123);
		REQUIRE(url1.GetDocument() == "/news");

		CHttpUrl url2("www.volgatech", "", CHttpUrl::Protocol::HTTPS, 123);
		REQUIRE(url2.GetDocument() == "/");
	}

	SECTION("incorrect URL parse")
	{
		REQUIRE_THROWS_AS(CHttpUrl("", "/news", CHttpUrl::Protocol::HTTPS, 123), std::exception);
		REQUIRE_THROWS_AS(CHttpUrl("www.volgatech", "/news", CHttpUrl::Protocol::HTTP, 0), std::exception);
	}
}

TEST_CASE("prepared url")
{
	CHttpUrl url1("www.volgatech", "news", CHttpUrl::Protocol::HTTPS, 123);
	REQUIRE(url1.GetURL() == "https://www.volgatech:123/news");

	SECTION("without port")
	{
		CHttpUrl url2("www.volgatech", "news", CHttpUrl::Protocol::HTTP);
		REQUIRE(url2.GetURL() == "http://www.volgatech/news");
	}
}

TEST_CASE("Protocol To String")
{
	CHttpUrl url1("https://www.volgatech.net/news/");
	REQUIRE(url1.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	REQUIRE(CHttpUrl::ProtocolToString(url1.GetProtocol()) == "https");

	CHttpUrl url2("http://www.volgatech.net/news/");
	REQUIRE(url2.GetProtocol() == CHttpUrl::Protocol::HTTP);
	REQUIRE(CHttpUrl::ProtocolToString(url2.GetProtocol()) == "http");
}