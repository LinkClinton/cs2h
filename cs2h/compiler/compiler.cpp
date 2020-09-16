#include "compiler.hpp"

#include "compiler_dxc.hpp"
#include "compiler_fxc.hpp"

int find_first_version(const std::string& version)
{
	for (const auto& character : version) {
		if (character >= '0' && character <= '9') return character - '0';
	}

	return -1;
}

std::tuple<std::vector<cs2h::byte>, std::string> cs2h::compile_shader_from_file(
	const std::string& filename, 
	const std::string& version,
	const std::string& entry,
	const std::vector<shader_macro>& macros)
{
	if (find_first_version(version) >= 6)
		return compile_shader_from_file_using_dxc(filename, version, entry, macros);
	else
		return compile_shader_from_file_using_fxc(filename, version, entry, macros);
}
