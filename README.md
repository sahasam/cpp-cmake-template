

# C/C++ CMake Template :pray:
---

This template does not promise OS independence. This works on my mac and I don't have a windows installation to try and get cross-compatibility. I have not tested this on Linux, but there should be little minimal modifcation required.

This readme contains everything you need to know about this template. It will provide an installation section you can copy paste into future README's, as well as describe how to use the structure I templated.

## Installation :rocket:

to install this project, run the following commands:

```bash
git clone https://github.com/[user]/[project_name]
cd [project_name]
mkdir build && cd build
cmake ..
make -j4
sudo make install
```

## Coding with it :monkey:

To understand how to use any c++ project structure, the first question that matters is where you put your code. I decided to use the `src/`folder to place all source and header files required for my projects. Many existing structures use an `include/` folder, but I don't see myself making libraries anytime soon.

```
<TOPLEVEL_DIR>
    src/                # Any code that you write goes in here
        adder/          # Logically grouped source files
            adder.h
            adder.cpp
        main.cpp
        CMakeLists.txt
    lib/                # Any dependencies get git submodule'd in here
        glfw/
            ...
    tests/
        adder/
            adder.cpp
        test.cpp
        CMakeLists.txt
    .gitignore          # comes preprepared with ignores for cmake and c++
    CMakeLists.txt      # preloaded with secret seasoning
```

## Adding dependencies to CMake Build System :mage:

Use the `git submodule` command to clone whatever repository you like into `lib/[libname]`. If your archaic repository of choice isn't on git, then recursively copy the entire project directory with CMakeLists.txt at the toplevel. This is important. CMake __has__ to be used for this to work. There are alternatives if CMake isn't the build system in use, but they are not covered here.

> <span style="color: red">NOTE:</span> the command given here uses the version of the library in the master branch. If you need a specific commit or release, change the submodule command accordingly.

* Step 1: add git submodule

    `git submodule add https://github.com/glfw/glfw.git lib/glfw`
* Step 2: add stuff to CMakeLists.txt
    ```CMake
    # where git submodule was submodule'd in
    add_subdirectory(lib/glfw)

    # where include folder is so includes can be found
    target_include_directories(${PROJECT_NAME} PUBLIC lib/glfw/include)

    # where sources are built to in build folder so linker is happy.
    # In projects, look for where the lib[somelib].a is located in
    # build folder
    target_link_directories(${PROJECT_NAME} PRIVATE lib/glfw/src)

    # tell cmake to generate compilation with -l[libname] flag. This is
    # determined by the dependency you install. (80% sure of that)
    target_link_libraries(${PROJECT_NAME} glfw)
    ```
* Step 3 (already built into this template):
    In order to automate the process of adding submodules before compiling your source code, we can add a script to CMakeLists.txt that automatically git submodule's in missing dependencies. This is taken straight from [this repository](https://github.com/codetechandtutorials/OurLordAndSavior/). 
    ```cmake
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

    ```

## Tests :robot:

There are 2 main well-qualified testing frameworks I was considering: Catch2 and GoogleTest. I want to work at Google, so I chose GoogleTest. Just kidding. GoogleTest started working first, so now I'm sticking with it to the grave.

Getting basic tests was not that difficult. It was as hard as copying code from examples. Integrating it, however, with the src/ module was quite difficult to figure out. I ended up creating a static library out of the `src/` module, and linking it to the test code. Because the source code was linked as a library, `#include` statements should contain angle brackets like so:

    #include <adder/adder.h>

If the test executable need to be linked with any external libraries in the project, they should be linked in the toplevel CMakeLists.txt. It works, so I'm not complaining.

## Projects I've made with this template :banana::gorilla:

I just made this template. I *will* update this in the future. :v:
