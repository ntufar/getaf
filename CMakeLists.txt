cmake_minimum_required(VERSION 3.10)

project(GETAF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third_party/tinyxml2)
add_subdirectory(Source)