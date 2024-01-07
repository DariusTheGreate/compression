cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDART 17)

project(jopeg)

set(SOURCES jopeg.cpp)

add_executable(jopeg ${SOURCES})
