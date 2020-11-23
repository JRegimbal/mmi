project(mm-interpolation)
cmake_minimum_required(VERSION 3.17)
set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(Flext REQUIRED)

file(GLOB_RECURSE src_files "src/*.cpp")
file(GLOB_RECURSE include_files "include/*.h")

add_executable(mm-interpolation src/main.cpp src/gaussian.cpp src/interpolation.cpp)
target_include_directories(mm-interpolation PUBLIC
    include
    eigen
)
if (MSVC)
    target_compile_options(mm-interpolation PRIVATE /W4 /WX)
else()
    target_compile_options(mm-interpolation PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

add_library(mmi SHARED src/externals.cpp src/gaussian.cpp src/interpolation.cpp)
target_include_directories(mmi PUBLIC
    include
    eigen
    ${Flext_INCLUDE_DIR}
)
target_link_libraries(mmi
    ${Flext_LIBRARY}
)
if (MSVC)
    target_compile_options(mmi PRIVATE /W4 /WX)
else()
    target_compile_options(mmi PRIVATE -Wall -Wextra -pedantic)
endif()
target_compile_definitions(mmi
    PUBLIC UNIX
    PUBLIC FLEXT_SYS=2
    PUBLIC FLEXT_SHARED
    PUBLIC FLEXT_USE_CMEM
    PUBLIC PD
)
if (UNIX)
    target_compile_definitions(mmi
        PUBLIC UNIX
    )
endif()
if (MSVC)
    set_target_properties(mmi PROPERTIES
        OUTPUT_NAME "mmi.dll"
        SUFFIX ""
        PREFIX ""
    )
elseif (APPLE)
    set_target_properties(mmi PROPERTIES
        OUTPUT_NAME "mmi.pd_darwin"
        SUFFIX ""
        PREFIX ""
    )
else()
    set_target_properties(mmi PROPERTIES
        OUTPUT_NAME "mmi.pd_linux"
        SUFFIX ""
        PREFIX ""
    )
endif()

add_custom_target(lint
    COMMAND clang-format -i ${src_files} ${include_files}
)
