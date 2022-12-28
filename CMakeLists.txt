cmake_minimum_required(VERSION 3.5)

project(map-docs VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(map-docs
                include/structures.h
                src/main.cpp
                )
