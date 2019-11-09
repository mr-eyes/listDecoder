# kmerDecoder
[![Build Status](https://travis-ci.com/mr-eyes/listDecoder.svg?branch=master)](https://travis-ci.com/mr-eyes/listDecoder)

## Quick Setup (using CMake)

Create `CMakeLists.txt` file in your project directory

```cmake
cmake_minimum_required (VERSION 3.4)
project (LD_Test C CXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")

add_subdirectory(listDecoder)

add_executable (ldtest ${CPP_SOURCE_FILE})

target_link_libraries(ldtest kmerDecoder)

```
