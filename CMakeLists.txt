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

# Web Configurations
if ("${PLATFORM}" STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index" SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PUBLIC 
        "-sASSERTIONS=1"
        "-sFORCE_FILESYSTEM"
        "-sALLOW_MEMORY_GROWTH"
        "-sUSE_GLFW=3"
        "-sEXPORTED_RUNTIME_METHODS=['HEAPF32']"
        "--preload-file=${CMAKE_SOURCE_DIR}/resources@resources"
        "--preload-file=${CMAKE_SOURCE_DIR}/settings.txt@settings.txt"
    )
    if ("${SHELL}" STREQUAL "Minimal")
        target_link_options(${PROJECT_NAME} PUBLIC "--shell-file" "${CMAKE_SOURCE_DIR}/src/shell_minimal.html")
    endif()
endif()
