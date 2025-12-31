cmake_minimum_required(VERSION 3.14)
project(JsonBenchmark)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# nlohmann/json
add_subdirectory(thirdparty/json)

# simdjson
add_subdirectory(thirdparty/simdjson)

# yyjson
add_subdirectory(thirdparty/yyjson)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include/)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -static)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json simdjson yyjson)
