cmake_minimum_required(VERSION 3.10)

project(FrameworkTests)

add_executable(FrameworkTests
    ConfigReader.cpp
    HTTPClient.cpp
    DBConnector.cpp
    TestReporter.cpp
)

target_link_libraries(FrameworkTests PRIVATE Framework gtest_main tinyxml2)
