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

# Add cpr dependency
FetchContent_Declare(
  cpr
  GIT_REPOSITORY https://github.com/libcpr/cpr.git
  GIT_TAG 1.10.5
)
FetchContent_MakeAvailable(cpr)

# Add mysql-connector-c++ dependency
FetchContent_Declare(
  mysql_connector_cpp
  GIT_REPOSITORY https://github.com/mysql/mysql-connector-cpp.git
  GIT_TAG 9.4.0
)
FetchContent_MakeAvailable(mysql_connector_cpp)


# Create a library for the framework
add_library(Framework
    ConfigReader.cpp
    ConfigReader.h
    HTTPClient.cpp
    HTTPClient.h
    DBConnector.cpp
    DBConnector.h
    TestReporter.cpp
    TestReporter.h
)

# Public headers
target_include_directories(Framework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Framework PUBLIC ${json_SOURCE_DIR}/include)
target_include_directories(Framework PUBLIC ${mysql_connector_cpp_SOURCE_DIR}/include)

# Link dependencies
target_link_libraries(Framework PRIVATE cpr::cpr mysql_connector_cpp::mysql_connector_cpp)


# Include GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Link GoogleTest to the framework library for testing
target_link_libraries(Framework GTest::gtest_main)