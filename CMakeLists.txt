# ----------------------------------------------------------------------------
# listDecoder project
# ----------------------------------------------------------------------------

cmake_minimum_required (VERSION 3.4)
project (listDecoder C CXX)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14 -fPIC -W -pedantic -O3 -oFast -fopenmp")

# ----------------------------------------------------------
# Options to enable/disable binaries building.
option(BUILD_BIN "Suppress building MQF binaries" OFF)
if(BUILD_BIN)
    add_definitions(-DBUILD_BIN=1)
else()
    add_definitions(-DBUILD_BIN=0)
endif()
# ----------------------------------------------------------




# ----------------------------------------------------------------------------
# Seqan Setup
# ----------------------------------------------------------------------------

# Search for zlib as a dependency for SeqAn.
find_package (ZLIB)

# Load the SeqAn module and fail if not found.
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/lib/seqan/util/cmake")
set(SEQAN_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/lib/seqan/include")
message("${PROJECT_SOURCE_DIR}/lib/seqan/include")
find_package (SeqAn REQUIRED)

# Add include directories.
include_directories (${SEQAN_INCLUDE_DIRS})
message("${SEQAN_INCLUDE_DIRS}")
# Add definitions set by find_package (SeqAn).
add_definitions (${SEQAN_DEFINITIONS})

# ----------------------------------------------------------------------------
# END Seqan Setup
# ----------------------------------------------------------------------------


# Add CXX flags found by find_package (SeqAn).
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SEQAN_CXX_FLAGS}")


file(GLOB SOURCES
        "./src/*.cpp"
)

set(PHMAP_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/lib/parallel-hashmap")
set(LISTDECODER_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories(${PHMAP_INCLUDE_DIRS})
include_directories(lib/gzstream)

add_library(listDecoder STATIC ${SOURCES})
target_include_directories(listDecoder INTERFACE ${PHMAP_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/lib/seqan/include ${LISTDECODER_INCLUDE_DIRS})
target_link_libraries(listDecoder z)


message("Building listDecoder binaries")
add_subdirectory(bin)