#pragma once
#include <string>

using NodePtr = struct ListNode*;

struct ListNode
{
	ListNode() = default;

	ListNode(std::string data)
		: data(std::move(data))
	{
	}

	std::string data;
	NodePtr next = nullptr;
	NodePtr prev = nullptr;
};