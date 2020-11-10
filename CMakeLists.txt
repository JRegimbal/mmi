project(mm-interpolation)
cmake_minimum_required(VERSION 3.18)
set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_library(mmi SHARED src/externals.cpp src/gaussian.cpp src/interpolation.cpp)
    target_include_directories(mmi PUBLIC
        include
        eigen
        /usr/include/pd
        /usr/include/flext
    )
    target_compile_options(mmi PRIVATE -Wall -Wextra -pedantic)
    target_compile_definitions(mmi
        PUBLIC UNIX
        PUBLIC FLEXT_SYS=2
        PUBLIC FLEXT_SHARED
        PUBLIC FLEXT_USE_CMEM
        PUBLIC PD
    )
    target_link_libraries(mmi
        flext-pd
    )
    set_target_properties(mmi PROPERTIES
        OUTPUT_NAME "mmi.pd_linux"
        SUFFIX ""
        PREFIX ""
    )
endif()

add_custom_target(lint
    COMMAND clang-format -i ${src_files} ${include_files}
)
