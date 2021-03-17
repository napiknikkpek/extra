cmake_minimum_required(VERSION 3.16)

project(extra)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS ON NO_OUTPUT_DIRS ON)

find_package(Boost 1.74 REQUIRED)
find_package(Threads REQUIRED)

add_compile_options(
    -Wall
    -Wextra
    -Wno-unknown-pragmas
    -fno-omit-frame-pointer
    # -fconcepts-diagnostics-depth=10
)

add_subdirectory(include)
add_subdirectory(test)
