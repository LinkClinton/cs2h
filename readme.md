# compile shader to header-file

cs2h is a program read `json` config and compile `HLSL` using `dxc` or `fxc` to c++ header file.

You can use this program to compile the shaders to a c++ header file and using the array of byte as shaders. It can help you build shaders as source code and use it directly when compiling your program.

## Json format

You can see the example to know the format and you can not ignore any elements.

```json
{
  "directory" : "",
  "filename": "cs2h_basic_test",
  "name_of_namespace": "cs2h",
  "shaders": [
    {
      "macros": [ { "__HLSL_SHADER__": 1 } ],
      "filename": "cs2h_basic_test_shader.hlsl",
      "variable": "shader_vs",
      "version": "vs_5_1",
      "entry": "vs_main"
    },
    {
      "macros": [ { "__HLSL_SHADER__": 1 } ],
      "filename": "cs2h_basic_test_shader.hlsl",
      "variable": "shader_ps",
      "version": "ps_5_1",
      "entry": "ps_main"
    }
  ]
}
```

- `directory` shows the directory of output file.
- `filename` shows the output file of c++ header-file(do not add `.hpp` or `.h`).
- `name_of_namespace` shows the namespace of strings of shader code.
- `shaders` is an array contain some shaders we will compile.
- `shaders.macros` is an array contain the macros we will use in shader compling.
- `shaders.filename` shows the shader file we will compile.
- `shaders.variable` shows the variable name of shader code in c++ header-file.
- `shaders.version` shows the profile of shader(it decides which compiler we will use).
- `shaders.entry` shows the entry point of shader.

## How to use

Just input `program_name json_file` on your terminal.

## Notice

If you want to use [dxc](https://github.com/microsoft/DirectXShaderCompiler) to compile the shader, you should ensure the `.dll` and `.lib` file are on your system. You can download it from [here](https://github.com/microsoft/DirectXShaderCompiler/releases).

The fxc only support profile with `xx_5_1` or lower version and dxc only support profile with `xx_6_0` or higher.

## ThirdParty

- [json](https://github.com/nlohmann/json) : JSON for Modern C++.