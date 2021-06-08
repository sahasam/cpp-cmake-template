cmake_minimum_required(VERSION 3.18.1)

# All Source files to compile into Adder Library
set(ADDER_SOURCES
    adder/adder.h
    adder/adder.cpp
)

add_library(Adder ${ADDER_SOURCES})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} Adder)