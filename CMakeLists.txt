cmake_minimum_required(VERSION 3.20)
project(Code)

set(CMAKE_CXX_STANDARD 17)

add_executable(Code main.cpp Planet.cpp Planet.h PlanetTest.cpp)
