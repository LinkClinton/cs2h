#ifndef __COMPILER_DXC_HPP__
#define __COMPILER_DXC_HPP__

#include "../utility.hpp"

#include <vector>

namespace cs2h {

	std::tuple<std::vector<byte>, std::string> compile_shader_from_file_using_dxc(
		const std::string& filename,
		const std::string& version,
		const std::string& entry,
		const std::vector<shader_macro>& macros = {});
	
}

#endif