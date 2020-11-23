message("Begin FindFlext.cmake")
set(FLEXT_SEARCH_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /Applications
    /usr/local
    /usr
    /usr/local/lib
    /usr/lib
    /opt/local
    /opt
    ${FLEXT_PATH}
    ${PD_PATH}
)

find_library(Flext_LIBRARY
    NAMES flext-pd flext
    PATHS ${FLEXT_SEARCH_PATHS}
    PATH_SUFFIXES *
)

find_path(Flext_INCLUDE_DIR flext.h
    PATH_SUFFIXES include include/flext *
    PATHS ${FLEXT_SEARCH_PATHS}
)

message("Path: ${PD_PATH}")
find_path(Flext_PD_INCLUDE m_pd.h
    PATH_SUFFIXES include include/pd src *
    PATHS ${FLEXT_SEARCH_PATHS}
)

message("End FindFlext.cmake")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Flext Flext_LIBRARY Flext_INCLUDE_DIR Flext_PD_INCLUDE)
