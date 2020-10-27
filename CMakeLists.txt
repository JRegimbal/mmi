project(mm-interpolation)
cmake_minimum_required(VERSION 3.18)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE src_files "src/*.cpp")
file(GLOB_RECURSE include_files "include/*.h")

add_executable(mm-interpolation ${src_files})
target_include_directories(mm-interpolation PUBLIC
    include
    src
    eigen
)

add_custom_target(lint
    COMMAND clang-format -i ${src_files} ${include_files}
)
