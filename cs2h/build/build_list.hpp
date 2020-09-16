#ifndef __BUILD_LIST_HPP__
#define __BUILD_LIST_HPP__

#include "../utility.hpp"

#include <vector>

namespace cs2h {
	
	struct build_item {
		std::vector<shader_macro> macros;
		
		std::string filename;
		std::string version;
		std::string entry;

		std::string variable;
	};	

	struct build_list {
		std::vector<build_item> items;

		std::string name_of_namespace;
		std::string directory;
		std::string filename;
	};

	build_list read_build_list_from_json(const std::string& filename);
}

#endif
