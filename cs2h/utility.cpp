#include "utility.hpp"

#include <cstdlib>
#include <vector>

#ifdef _MSVC_LANG
#pragma warning(disable : 4996)
#endif

std::wstring cs2h::convert_string_to_wstring(const std::string& str)
{
	std::vector<wchar_t> storage(str.length());

	const auto size = std::mbstowcs(storage.data(), str.c_str(), str.length());

	std::wstring ret;

	for (size_t index = 0; index < size; index++) ret.push_back(storage[index]);

	return ret;
}

std::string cs2h::read_string_from_memory(void* memory, size_t length)
{
	return std::string(static_cast<const char*>(memory));
}

std::string cs2h::to_upper(const std::string& str)
{
	std::string ret; ret.resize(str.length());

	for (size_t index = 0; index < str.length(); index++) {
		if (str[index] >= 'a' && str[index] <= 'z')
			ret[index] = str[index] + 'A' - 'a';
		else
			ret[index] = str[index];
	}

	return ret;
}