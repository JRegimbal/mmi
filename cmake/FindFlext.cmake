message("Begin FindFlext.cmake")
set(FLEXT_SEARCH_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /usr/local/lib
    /usr/lib
    /opt/local
    /opt
    ${FLEXT_PATH}
)

find_library(Flext_LIBRARY
    NAMES flext-pd flext
    PATHS ${FLEXT_SEARCH_PATHS}
    PATH_SUFFIXES *
)

find_path(Flext_INCLUDE_DIR flext.h
    PATH_SUFFIXES include/flext include
    PATHS ${FLEXT_SEARCH_PATHS}
)

message("End FindFlext.cmake")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Flext FLEXT_LIBRARY FLEXT_INCLUDE_DIR)
