#include "compiler_dxc.hpp"

#include <combaseapi.h>
#include <wrl/client.h>
#include <dxcapi.h>

std::tuple<std::vector<byte>, std::string> cs2h::compile_shader_from_file_using_dxc(
	const std::string& filename,
	const std::string& version, 
	const std::string& entry, 
	const std::vector<shader_macro>& macros)
{
	const auto filename_wide = convert_string_to_wstring(filename);
	const auto version_wide = convert_string_to_wstring(filename);
	const auto entry_wide = convert_string_to_wstring(filename);

	std::vector<std::wstring> macros_define;
	std::vector<std::wstring> macros_value;

	for (size_t index = 0; index < macros.size(); index++) {
		macros_define[index] = convert_string_to_wstring(macros[index].name);
		macros_value[index] = convert_string_to_wstring(macros[index].value);
	}
	
	Microsoft::WRL::ComPtr<IDxcIncludeHandler> include;
	Microsoft::WRL::ComPtr<IDxcCompiler> compiler;
	Microsoft::WRL::ComPtr<IDxcLibrary> library;
	
	DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(library.GetAddressOf()));
	DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(compiler.GetAddressOf()));

	library->CreateIncludeHandler(include.GetAddressOf());

	Microsoft::WRL::ComPtr<IDxcBlobEncoding> encoding_blob;

	library->CreateBlobFromFile(filename_wide.c_str(), nullptr, encoding_blob.GetAddressOf());

	Microsoft::WRL::ComPtr<IDxcOperationResult> result;

	std::vector<DxcDefine> defines(macros.size());

	for (size_t index = 0; index < defines.size(); index++) {
		defines[index].Name = macros_define[index].c_str();
		defines[index].Value = macros_value[index].c_str();
	}

	compiler->Compile(encoding_blob.Get(),
		filename_wide.c_str(), 
		entry_wide.c_str(),
		version_wide.c_str(),
		nullptr, 0,
		defines.data(), static_cast<UINT32>(defines.size()),
		include.Get(), result.GetAddressOf());

	Microsoft::WRL::ComPtr<IDxcBlobEncoding> error_code;
	Microsoft::WRL::ComPtr<IDxcBlob> result_code;
	HRESULT result_status;

	result->GetErrorBuffer(error_code.GetAddressOf());
	result->GetResult(result_code.GetAddressOf());
	result->GetStatus(&result_status);

	std::string message_string;
	std::vector<byte> compiled_code;
	
	if (error_code != nullptr) {
		message_string = read_string_from_memory(error_code->GetBufferPointer(), error_code->GetBufferSize());

		if (!message_string.empty() && message_string.back() == '\n') message_string.pop_back();
	}
	
	if (result_code != nullptr) {
		compiled_code = std::vector<byte>(result_code->GetBufferSize());

		std::memcpy(compiled_code.data(), result_code->GetBufferPointer(), result_code->GetBufferSize());
	}

	return { compiled_code, message_string };
}
