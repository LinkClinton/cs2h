#include "compiler/compiler.hpp"
#include "build/build_list.hpp"

#include <filesystem>
#include <fstream>

namespace cs2h {

	void output_header_file(const build_list& list, const std::vector<shader_code>& shaders)
	{
		std::string content = "";

		const auto header_file_macro = "__" + to_upper(list.filename) + "_HPP__";
		
		content += "#ifndef " + header_file_macro + "\n";
		content += "#define " + header_file_macro + "\n";

		content += "\n";

		if (!list.name_of_namespace.empty()) 
			content += "namespace " + list.name_of_namespace + " {\n\n";

		for (size_t index = 0; index < list.items.size(); index++) {
			if (!list.name_of_namespace.empty()) content += "\t";

			content += "constexpr unsigned char " + list.items[index].variable + "[] = { ";
			
			for (size_t code_index = 0; code_index < shaders[index].size(); code_index++) {
				content += std::to_string(shaders[index][code_index]);

				if (code_index + 1 != shaders[index].size()) content += ", ";
			}

			content += " };\n";
		}

		content += "\n";
		
		if (!list.name_of_namespace.empty())
			content += "}\n";
		
		content += "\n#endif\n";

		std::ofstream stream((!list.directory.empty() ? list.directory + "/" : "") + list.filename + ".hpp");

		stream << content << std::endl;
		stream.close();

		std::cout << "finished writing header file." << std::endl;
	}
	
	void build_and_output(const std::string& filename)
	{
		if (!std::filesystem::exists(filename)) {
			std::cout << "\"" << filename << "\" is not existed." << std::endl;

			return;
		}

		std::cout << "start building \"" << filename << "\"." << std::endl;

		const auto list = read_build_list_from_json(filename);

		std::vector<shader_code> shaders;
		
		for (const auto& build_item : list.items) {
			const auto [shader, message] = compile_shader_from_file(
				build_item.filename,
				build_item.version,
				build_item.entry,
				build_item.macros);
			
			shaders.push_back(shader);

			if (shader.empty()) std::cout << "compile shader failed." << std::endl;
			if (!message.empty()) std::cout << message << std::endl;
		}

		output_header_file(list, shaders);
		
		std::cout << "end building." << std::endl;
	}
	
}

int main(int argc, char** argv)
{
	if (argc == 1) {
		std::cout << "required filename!" << std::endl;

		return 1;
	}
	
	cs2h::build_and_output(argv[1]);
}