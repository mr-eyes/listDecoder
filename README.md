# listDecoder

[![Build Status](https://travis-ci.com/mr-eyes/listDecoder.svg?branch=master)](https://travis-ci.com/mr-eyes/listDecoder)

## Quick Setup (using CMake)

Create `CMakeLists.txt` file in your project directory

```cmake
cmake_minimum_required (VERSION 3.4)
project (LD_test C CXX)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")
add_subdirectory(listDecoder)

```

Use the generated static lib either using Cmake `add_subdirectory()` or by linking to compilation command.

## Usage Example

```cpp
#include "listDecoder.hpp"

listDecoder *LD = new Items("bin/sample.tsv");

while (!LD->end()) {
        LD->next_chunk();

        for (const auto &seq : *LD->getKmers()) {
            std::cout << "Parent: " << seq.first << std::endl;
            for (const auto &item : seq.second) {
                std::cout << item.str << ": " << item.hash << std::endl;
            }
        }
    }

```