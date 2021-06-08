cmake_minimum_required(VERSION 3.19.1)

project(template)

# Saves all source files in src/ to a variable
set(SOURCES src/adder/adder.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp)

add_subdirectory(lib/glfw)
add_subdirectory(lib/catch2)

target_include_directories(${PROJECT_NAME} PUBLIC lib/glfw/include)

# DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#           CHECK ALL THE SUBMODULES
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/lib/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

target_link_directories(${PROJECT_NAME} PRIVATE lib/glfw/src)
target_link_libraries(${PROJECT_NAME} glfw)