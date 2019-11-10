cmake_minimum_required (VERSION 3.4)

project (listDecoder C CXX)

add_executable(test_listDecoder test.cpp)

target_link_libraries(test_listDecoder listDecoder)