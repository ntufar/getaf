cmake_minimum_required(VERSION 3.10)

project(GameLogic)

# This is a placeholder for the UE5 game project.
# The actual UE5 project would be built using the Unreal Build Tool (UBT).
# For the purpose of the test framework build, we create a dummy library.

add_library(GameLogic
    Character.h
    Character.cpp
    Collectible.h
    Collectible.cpp
    AIController.h
    AIController.cpp
    GameHUD.h
    GameHUD.cpp
)

target_include_directories(GameLogic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})