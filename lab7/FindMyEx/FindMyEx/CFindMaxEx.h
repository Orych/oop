#pragma once
#include <vector>

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	//по дефолту less выставлять и проверять выбрасываются ли исключения 
	if (arr.empty())
	{
		return false;
	}
	auto maxElement = arr.begin();
	for (auto it = arr.begin() + 1; it < arr.end(); it++)
	{
		if (less(*maxElement, *it))
		{
			maxElement = it;
		}
	}
	maxValue = *maxElement;

	return true;
}