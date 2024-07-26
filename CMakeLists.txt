cmake_minimum_required(VERSION 3.28)
project(MountainCar)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(MountainCar main.cpp
        Window.cpp
        Window.h
        Game.cpp
        Game.h
        Snake.h
        Snake.cpp
        Snake.h
        World.cpp
        World.h
        State.h
        QLearningAgent.cpp
        QLearningAgent.h)

target_link_libraries(MountainCar sfml-graphics)
