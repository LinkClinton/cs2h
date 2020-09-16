#include "compiler_fxc.hpp"

#include <d3dcompiler.h>
#include <wrl/client.h>

std::tuple<std::vector<byte>, std::string> cs2h::compile_shader_from_file_using_fxc(
	const std::string& filename,
	const std::string& version,
	const std::string& entry,
	const std::vector<shader_macro>& macros)
{
	Microsoft::WRL::ComPtr<ID3DBlob> message;
	Microsoft::WRL::ComPtr<ID3DBlob> codes;

	std::vector<D3D_SHADER_MACRO> d3d_macros(macros.size() + 1);

	for (size_t index = 0; index < macros.size(); index++) {
		d3d_macros[index].Name = macros[index].name.c_str();
		d3d_macros[index].Definition = macros[index].value.c_str();
	}

	d3d_macros[macros.size()] = { nullptr, nullptr };

	const auto filename_wide = convert_string_to_wstring(filename);

	D3DCompileFromFile(filename_wide.c_str(), d3d_macros.data(), D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entry.c_str(), version.c_str(), 0, 0,
		codes.GetAddressOf(), message.GetAddressOf());

	std::string message_string;
	std::vector<byte> compiled_code;
	
	if (message != nullptr) {
		message_string = read_string_from_memory(
			message->GetBufferPointer(), message->GetBufferSize());

		if (!message_string.empty() && message_string.back() == '\n') message_string.pop_back();
	}

	if (codes != nullptr) {
		compiled_code = std::vector<byte>(codes->GetBufferSize());

		std::memcpy(compiled_code.data(), codes->GetBufferPointer(), codes->GetBufferSize());
	}

	return { compiled_code, message_string };
}
