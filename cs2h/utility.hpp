#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

#include <iostream>
#include <string>
#include <vector>

namespace cs2h {

	using byte = unsigned char;

	struct shader_macro {
		std::string name;
		std::string value;
	};

	using shader_code = std::vector<byte>;
	
	std::wstring convert_string_to_wstring(const std::string& str);
	
	std::string read_string_from_memory(void* memory, size_t length);

	std::string to_upper(const std::string& str);
	
}

#endif