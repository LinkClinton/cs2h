#include "build_list.hpp"

#include <nlohmann/json.hpp>
#include <fstream>

cs2h::build_list cs2h::read_build_list_from_json(const std::string& filename)
{
	nlohmann::json json;

	std::ifstream stream(filename);
	
	stream >> json;

	stream.close();

	build_list list;

	list.name_of_namespace = json["name_of_namespace"].get<std::string>();
	list.directory = json["directory"].get<std::string>();
	list.filename = json["filename"].get<std::string>();
	
	for (const auto& shader : json["shaders"]) {
		build_item item;

		for (const auto& macros : shader["macros"]) {
			for (auto it = macros.begin(); it != macros.end(); ++it) {
				item.macros.push_back({ it.key(), std::to_string(it.value().get<int>()) });
			}
		}
		
		item.filename = shader["filename"].get<std::string>();
		item.version = shader["version"].get<std::string>();
		item.entry = shader["entry"].get<std::string>();

		item.variable = shader["variable"].get<std::string>();

		list.items.push_back(item);
	}
	
	return list;
}