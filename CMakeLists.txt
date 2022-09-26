cmake_minimum_required(VERSION 3.10)

project(json-packer VERSION 1.0)
add_executable(json-packer main.c)
set(COMPILER_FLAGS "-Wall -O2")
set(C_COMPILER_FLAGS "gcc ${COMPILER_FLAGS}")

# - Find Apache Portable Runtime
# Find the APR includes and libraries
# This module defines
#  APR_INCLUDE_DIR and APRUTIL_INCLUDE_DIR, where to find apr.h, etc.
#  APR_LIBRARIES and APRUTIL_LIBRARIES, the libraries needed to use APR.
#  APR_FOUND and APRUTIL_FOUND, If false, do not try to use APR.
# also defined, but not for general use are
#  APR_LIBRARY and APRUTIL_LIBRARY, where to find the APR library.

###################
# Searching APR
###################
find_path(APR_INCLUDE_DIR apr.h
        /opt/homebrew/opt/apr/include/apr-1
        /usr/local/include/apr-1
        /usr/local/include/apr-1.0
        /usr/include/apr-1
        /usr/include/apr-1.0
        /usr/local/apr/include/apr-1)

set(APR_NAMES ${APR_NAMES} apr-1)
find_library(APR_LIBRARY
        NAMES ${APR_NAMES}
        HINTS
        /opt/homebrew/opt/apr/lib
        PATHS
        /usr/lib
        /usr/local/lib
        /usr/local/apr/lib)

if (APR_LIBRARY AND APR_INCLUDE_DIR)
    set(APR_LIBRARIES ${APR_LIBRARY})
    set(APR_FOUND "YES")
else (APR_LIBRARY AND APR_INCLUDE_DIR)
    set(APR_FOUND "NO")
endif (APR_LIBRARY AND APR_INCLUDE_DIR)


if (APR_FOUND)
    if (NOT APR_FIND_QUIETLY)
        message(STATUS "Found APR headers: ${APR_INCLUDE_DIR}")
        message(STATUS "Found APR library: ${APR_LIBRARIES}")
    endif (NOT APR_FIND_QUIETLY)
else (APR_FOUND)
    if (APR_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find APR library")
    endif (APR_FIND_REQUIRED)
endif (APR_FOUND)

###################
# Searching APRUTIL
###################
find_path(APRUTIL_INCLUDE_DIR apu.h
        /opt/homebrew/opt/apr-util/include/apr-1
        /usr/local/include/apr-1
        /usr/local/include/apr-1.0
        /usr/include/apr-1
        /usr/include/apr-1.0
        /usr/local/apr/include/apr-1)

set(APRUTIL_NAMES ${APRUTIL_NAMES} aprutil-1)
find_library(APRUTIL_LIBRARY
        NAMES ${APRUTIL_NAMES}
        HINTS
        /opt/homebrew/opt/apr-util/lib
        PATHS
        /usr/lib
        /usr/local/lib
        /usr/local/apr/lib)

if (APRUTIL_LIBRARY AND APRUTIL_INCLUDE_DIR)
    set(APRUTIL_LIBRARIES ${APRUTIL_LIBRARY})
    set(APRUTIL_FOUND "YES")
else (APRUTIL_LIBRARY AND APRUTIL_INCLUDE_DIR)
    set(APRUTIL_FOUND "NO")
endif (APRUTIL_LIBRARY AND APRUTIL_INCLUDE_DIR)


if (APRUTIL_FOUND)
    if (NOT APRUTIL_FIND_QUIETLY)
        message(STATUS "Found APRUTIL headers: ${APRUTIL_INCLUDE_DIR}")
        message(STATUS "Found APRUTIL library: ${APRUTIL_LIBRARIES}")
    endif (NOT APRUTIL_FIND_QUIETLY)
else (APRUTIL_FOUND)
    if (APRUTIL_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find APRUTIL library")
    endif (APRUTIL_FIND_REQUIRED)
endif (APRUTIL_FOUND)

###################################
# Adding apr and apr-util headers
###################################

include_directories(${APR_INCLUDE_DIR})
include_directories(${APRUTIL_INCLUDE_DIR})

###########################
# Linking apr and apr-util
###########################

target_link_libraries(json-packer ${APR_LIBRARY})
target_link_libraries(json-packer ${APRUTIL_LIBRARY})
