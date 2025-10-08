cmake_minimum_required(VERSION 3.10)

project(Framework)

# Add nlohmann/json dependency
include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(json)


# Create a library for the framework
add_library(Framework
    ConfigReader.cpp
    ConfigReader.h
    TestReporter.cpp
    TestReporter.h
)

# Public headers
target_include_directories(Framework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Framework PUBLIC ${json_SOURCE_DIR}/include)
target_include_directories(Framework PUBLIC ${CMAKE_SOURCE_DIR}/third_party/tinyxml2)

# Link dependencies
target_link_libraries(Framework PRIVATE tinyxml2)


# Include GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Link GoogleTest to the framework library for testing
target_link_libraries(Framework PRIVATE GTest::gtest_main)