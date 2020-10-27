project(mm-interpolation)
cmake_minimum_required(VERSION 3.18)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE src_files "src/*.cpp")

add_executable(mm-interpolation ${src_files})
target_include_directories(mm-interpolation PUBLIC
    include
    src
    eigen
)
