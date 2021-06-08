cmake_minimum_required(VERSION 3.19.1)

project(template)

# Saves all source files in src/ to a variable
set(SOURCES src/main.cpp src/adder/adder.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})