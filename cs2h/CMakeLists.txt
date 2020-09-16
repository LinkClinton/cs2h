# CMakeList.txt : CMake project for cs2h, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(nlohmann_json CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# Add source to this project's executable.
add_executable (cs2h   "main.cpp"   "compiler/compiler_fxc.hpp" "utility.hpp" "compiler/compiler_fxc.cpp" "utility.cpp" "compiler/compiler_dxc.hpp" "compiler/compiler_dxc.cpp"  "build/build_list.hpp" "build/build_list.cpp" "compiler/compiler.hpp" "compiler/compiler.cpp")

target_link_libraries (cs2h "d3dcompiler.lib")
target_link_libraries (cs2h "dxcompiler.lib")

target_link_libraries (cs2h nlohmann_json::nlohmann_json)

# TODO: Add tests and install targets if needed.

enable_testing()

add_test(
	NAME cs2h_basic_test 
	COMMAND cs2h "cs2h_basic_test.json"
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/cs2h/tests/cs2h_basic_test)
set_tests_properties(cs2h_basic_test PROPERTIES FAIL_REGULAR_EXPRESSION "compile shader failed.")