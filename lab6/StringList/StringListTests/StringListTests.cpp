﻿#define CATCH_CONFIG_MAIN

#include "../../../catch2/catch.hpp"
#include "../StringList/StringList.h"
#include <sstream>

TEST_CASE("Initializing string list")
{
	StringList list;
	REQUIRE(list.IsEmpty());
	REQUIRE(list.GetLength() == 0);
}

TEST_CASE("Try get element from back and front of empty list")
{
	StringList list;
	REQUIRE(list.IsEmpty());
	REQUIRE(list.GetLength() == 0);

	REQUIRE_THROWS_AS(list.GetFront(), std::logic_error);
	REQUIRE_THROWS_WITH(list.GetFront(), "List is empty");

	REQUIRE_THROWS_AS(list.GetBack(), std::logic_error);
	REQUIRE_THROWS_WITH(list.GetBack(), "List is empty");
}

TEST_CASE("Pushing elements to back")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());

	list.PushBack(str1);
	REQUIRE(list.GetBack() == str1);
	REQUIRE(list.GetLength() == 1);
	REQUIRE(!list.IsEmpty());

	list.PushBack(str2);
	REQUIRE(list.GetBack() == str2);
	REQUIRE(list.GetLength() == 2);
	REQUIRE(!list.IsEmpty());

	list.PushBack(str3).PushBack(str4);
	REQUIRE(list.GetBack() == str4);
	REQUIRE(list.GetLength() == 4);
	REQUIRE(!list.IsEmpty());
}

TEST_CASE("Push elements to front and back")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());

	list.PushBack(str1);
	REQUIRE(list.GetBack() == str1);
	REQUIRE(list.GetFront() == str1);
	REQUIRE(list.GetLength() == 1);
	REQUIRE(!list.IsEmpty());

	list.PushFront(str2);
	REQUIRE(list.GetBack() == str1);
	REQUIRE(list.GetFront() == str2);
	REQUIRE(list.GetLength() == 2);
	REQUIRE(!list.IsEmpty());

	list.PushBack(str3).PushFront(str4);
	REQUIRE(list.GetBack() == str3);
	REQUIRE(list.GetFront() == str4);
	REQUIRE(list.GetLength() == 4);
	REQUIRE(!list.IsEmpty());
}

TEST_CASE("Test Clear method")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());

	list.PushBack(str1).PushBack(str2).PushBack(str3).PushBack(str4);
	REQUIRE(!list.IsEmpty());
	REQUIRE(list.GetLength() == 4);

	list.Clear();
	REQUIRE(list.IsEmpty());
	REQUIRE(list.GetLength() == 0);
}

TEST_CASE("Test bool cast operator")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());
	REQUIRE(!list);

	list.PushBack(str1);
	REQUIRE(!list.IsEmpty());
	REQUIRE(list);
}

TEST_CASE("Test PopBack method")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());
	REQUIRE_THROWS_AS(list.PopBack(), std::logic_error);

	list.PushBack(str1).PushFront(str2);
	REQUIRE(!list.IsEmpty());
	REQUIRE(list.GetLength() == 2);
	REQUIRE(list.GetBack() == str1);

	list.PopBack();
	REQUIRE(list.GetLength() == 1);
	REQUIRE(list.GetBack() == str2);

	list.PushBack(str3);
	REQUIRE(list.GetLength() == 2);
	REQUIRE(list.GetBack() == str3);

	list.PopBack().PopBack();
	REQUIRE(list.IsEmpty());
	REQUIRE_THROWS_AS(list.GetBack(), std::logic_error);
	REQUIRE_THROWS_AS(list.GetFront(), std::logic_error);
}

TEST_CASE("Test PopFront method")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());
	REQUIRE_THROWS_AS(list.PopFront(), std::logic_error);

	list.PushFront(str1).PushBack(str2);
	REQUIRE(!list.IsEmpty());
	REQUIRE(list.GetLength() == 2);
	REQUIRE(list.GetBack() == str2);
	REQUIRE(list.GetFront() == str1);

	list.PopFront();
	REQUIRE(list.GetLength() == 1);
	REQUIRE(list.GetBack() == str2);
	REQUIRE(list.GetFront() == str2);

	list.PushFront(str3);
	REQUIRE(list.GetLength() == 2);
	REQUIRE(list.GetFront() == str3);

	list.PopFront().PopFront();
	REQUIRE(list.IsEmpty());
	REQUIRE_THROWS_AS(list.GetBack(), std::logic_error);
	REQUIRE_THROWS_AS(list.GetFront(), std::logic_error);
}

TEST_CASE("Test iterator increment operator")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());

	list.PushBack(str1).PushBack(str2).PushBack(str3).PushBack(str4);
	REQUIRE(list.GetLength() == 4);

	SECTION("Increment begin() iterator once")
	{
		REQUIRE(list.GetFront() == *list.begin());

		std::string secondElement = *(++list.begin());
		list.PopFront();
		REQUIRE(list.GetFront() == secondElement);
		REQUIRE(list.GetFront() == *list.begin());
	}

	SECTION("Increment begin() iterator several times")
	{
		StringList::ConstIterator iterator = list.begin();

		REQUIRE(*iterator++ == "Provide");
		REQUIRE(*iterator == "Strong");
		REQUIRE(*++iterator == "Exception");
		++iterator;
		REQUIRE(*iterator == "Safety");
	}

	SECTION("Try increment end() iterator")
	{
		StringList::ConstIterator iterator = list.end();

		REQUIRE_THROWS_AS(++iterator, std::logic_error);
		REQUIRE_THROWS_AS(iterator++, std::logic_error);
	}

	SECTION("Try increment rend() iterator")
	{
		StringList::ConstReverseIterator iterator = list.rend();

		CHECK_THROWS_AS(++++iterator, std::logic_error);
		CHECK_THROWS_AS(iterator++++, std::logic_error);
	}
}

TEST_CASE("Test iterator decrement operator")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());

	list.PushBack(str1).PushBack(str2).PushBack(str3).PushBack(str4);
	REQUIRE(list.GetLength() == 4);

	SECTION("Decrement end() iterator once")
	{
		REQUIRE(list.GetBack() == "Safety");
		REQUIRE(list.GetBack() == *(--list.end()));

		list.PopBack();
		REQUIRE(list.GetBack() == "Exception");
		REQUIRE(list.GetBack() == *(--list.end()));
	}

	SECTION("Decrement end() iterator several times")
	{
		StringList::ConstIterator iterator = list.end();

		REQUIRE(*--iterator == "Safety");
		REQUIRE(*iterator-- == "Safety");
		REQUIRE(*iterator == "Exception");
		REQUIRE(*--iterator == "Strong");
		REQUIRE(*--iterator == "Provide");
	}

	SECTION("Try decrement begin() before iterator")
	{
		StringList::ConstIterator iterator = list.begin();

		REQUIRE_THROWS_AS(----iterator, std::logic_error);
	}

	SECTION("Try decrement rbegin() before iterator")
	{
		StringList::ConstReverseIterator iterator = list.rbegin();

		REQUIRE_THROWS_AS(----iterator, std::logic_error);
	}
}

TEST_CASE("Test iterator equality and non-equality operators")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());
	REQUIRE(list.begin() == list.end());

	list.PushBack(str1).PushBack(str2).PushBack(str3).PushBack(str4);
	REQUIRE(list.GetLength() == 4);

	REQUIRE(list.begin() != list.end());
	REQUIRE(++++list.begin() == ----list.end());

	REQUIRE(list.rbegin() != list.rend());
	REQUIRE(++++list.rbegin() == ----list.rend());

	list.PopBack().PopFront();

	REQUIRE(++list.begin() == --list.end());
	REQUIRE(++list.rbegin() == --list.rend());
}

TEST_CASE("Test regular const and non-const iterator")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");
	std::ostringstream oss;

	StringList list;
	REQUIRE(list.IsEmpty());

	list.PushBack(str1).PushBack(str2).PushBack(str3).PushBack(str4);
	REQUIRE(list.GetLength() == 4);

	SECTION("Write strings to ostream using const iterator")
	{
		StringList::ConstIterator iterator = list.begin();

		for (; iterator != list.end(); ++iterator)
		{
			oss << *iterator << ' ';
		}

		REQUIRE(oss.str() == "Provide Strong Exception Safety ");
	}

	SECTION("Mutate string list data using regular iterator")
	{
		StringList::Iterator iterator = list.begin();

		for (; iterator != list.end(); ++iterator)
		{
			(*iterator)[0] = 'W';
		}

		for (iterator = list.begin(); iterator != list.end(); ++iterator)
		{
			oss << *iterator << ' ';
		}

		REQUIRE(list.GetFront() == "Wrovide");
		REQUIRE(list.GetBack() == "Wafety");
		REQUIRE(oss.str() == "Wrovide Wtrong Wxception Wafety ");
	}
}

TEST_CASE("Test reverse const and non-const iterator")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");
	std::ostringstream oss;

	StringList list;
	REQUIRE(list.IsEmpty());

	list.PushBack(str1).PushBack(str2).PushBack(str3).PushBack(str4);
	REQUIRE(list.GetLength() == 4);

	SECTION("Write strings to ostream using reverse const iterator")
	{
		StringList::ConstReverseIterator iterator = list.rbegin();

		for (; iterator != list.rend(); ++iterator)
		{
			oss << *iterator << ' ';
		}

		REQUIRE(oss.str() == "Safety Exception Strong Provide ");
	}

	SECTION("Mutate string list data using reverse iterator")
	{
		StringList::ReverseIterator iterator = list.rbegin();

		for (; iterator != list.rend(); ++iterator)
		{
			(*iterator)[0] = 'W';
		}

		for (iterator = list.rbegin(); iterator != list.rend(); ++iterator)
		{
			oss << *iterator << ' ';
		}

		REQUIRE(list.GetFront() == "Wrovide");
		REQUIRE(list.GetBack() == "Wafety");
		REQUIRE(oss.str() == "Wafety Wxception Wtrong Wrovide ");
	}
}

TEST_CASE("Test range-based for")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");
	std::ostringstream oss;

	StringList list;
	REQUIRE(list.IsEmpty());

	list.PushBack(str1).PushBack(str2).PushBack(str3).PushBack(str4);
	REQUIRE(list.GetLength() == 4);

	for (const std::string& element : list)
	{
		oss << element;
	}

	REQUIRE(oss.str() == "ProvideStrongExceptionSafety");
}

TEST_CASE("Test Insert method")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());

	SECTION("Insert to begin pos")
	{
		list.Insert(list.begin(), str1);
		REQUIRE(list.GetLength() == 1);
		REQUIRE(list.GetFront() == str1);
		REQUIRE(list.GetBack() == str1);
	}

	SECTION("Insert to end pos")
	{
		list.Insert(list.cend(), str2);
		REQUIRE(list.GetLength() == 1);
		REQUIRE(list.GetFront() == str2);
		REQUIRE(list.GetBack() == str2);
	}

	SECTION("Insert to the middle")
	{
		list.Insert(list.cend(), str1);
		list.Insert(list.cend(), str2);
		REQUIRE(list.GetLength() == 2);
		REQUIRE(list.GetFront() == str1);
		REQUIRE(list.GetBack() == str2);

		list.Insert(++list.cbegin(), str3);
		REQUIRE(list.GetLength() == 3);
		REQUIRE(list.GetFront() == str1);
		REQUIRE(list.GetBack() == str2);

		REQUIRE(list.PopFront().GetFront() == str3);

		list.Insert(--list.cend(), str4);
		REQUIRE(list.GetLength() == 3);
		REQUIRE(list.GetFront() == str3);
		REQUIRE(list.GetBack() == str2);

		REQUIRE(list.PopBack().GetBack() == str4);
	}
}

TEST_CASE("Test Erase method")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());

	list.PushBack(str1).PushBack(str2).PushBack(str3).PushBack(str4);
	REQUIRE(list.GetLength() == 4);

	SECTION("Erase first element")
	{
		REQUIRE(list.GetFront() == str1);
		REQUIRE(list.GetLength() == 4);

		list.Erase(list.cbegin());

		REQUIRE(list.GetLength() == 3);
		REQUIRE(list.GetFront() == str2);
	}

	SECTION("Erase last element")
	{
		REQUIRE(list.GetBack() == str4);
		REQUIRE(list.GetLength() == 4);

		list.Erase(--list.cend());

		REQUIRE(list.GetLength() == 3);
		REQUIRE(list.GetBack() == str3);
	}

	SECTION("Erase element in the middle")
	{
		REQUIRE(list.GetFront() == str1);
		REQUIRE(list.GetLength() == 4);

		list.Erase(++++list.cbegin()); // erase str3

		REQUIRE(list.GetLength() == 3);
		REQUIRE(list.GetFront() == str1);
		REQUIRE(*(++++list.begin()) == str4);
		REQUIRE(*(----list.end()) == str2);
	}

	SECTION("Try erase past-the-last element")
	{
		REQUIRE_THROWS_AS(list.Erase(list.cend()), std::logic_error);
		REQUIRE_THROWS_AS(list.Erase(--list.crend().base()), std::logic_error);
	}
}

TEST_CASE("Test copy constructor")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList src;
	REQUIRE(src.IsEmpty());

	src.PushBack(str1).PushBack(str2).PushBack(str3).PushBack(str4);
	REQUIRE(src.GetLength() == 4);

	SECTION("Copy constructor")
	{
		StringList dest(src);
		REQUIRE(dest);

		REQUIRE(dest.GetLength() == 4);
		REQUIRE(dest.GetFront() == str1);
		REQUIRE(dest.GetBack() == str4);
		dest.PopFront().PopBack();
		REQUIRE(dest.GetFront() == str2);
		REQUIRE(dest.GetBack() == str3);

		REQUIRE(src.GetLength() == 4);
		REQUIRE(src.GetFront() == str1);
		REQUIRE(src.GetBack() == str4);
	}

	SECTION("Copy assignment operator")
	{
		StringList dest;
		REQUIRE(!dest);

		dest = src;
		REQUIRE(dest.GetLength() == 4);
		REQUIRE(dest.GetFront() == str1);
		REQUIRE(dest.GetBack() == str4);
		dest.PopFront().PopBack();
		REQUIRE(dest.GetFront() == str2);
		REQUIRE(dest.GetBack() == str3);

		REQUIRE(src.GetLength() == 4);
		REQUIRE(src.GetFront() == str1);
		REQUIRE(src.GetBack() == str4);
	}
}

TEST_CASE("Test default constructed iterator")
{
	StringList::ConstIterator iterator;

	REQUIRE_THROWS_AS(*iterator, std::logic_error);
	REQUIRE_THROWS_AS(++iterator, std::logic_error);
	REQUIRE_THROWS_AS(iterator++, std::logic_error);
	REQUIRE_THROWS_AS(--iterator, std::logic_error);
	REQUIRE_THROWS_AS(iterator--, std::logic_error);
	REQUIRE_THROWS_AS(iterator->empty(), std::logic_error);
}