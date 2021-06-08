

# C++ CMake Template
---

This template was not made for multiple operating systems in mind. This works on my
mac and I don't have a windows installation to try and get cross-compatibility.
I have not tested this on Linux, but there should be little to know changes necessary.

This readme contains everything you need to know about this template. It will
provide an installation section you can copy paste into future README's. It will
describe how to use the structure I created as well.

## Installation

to install this project, run the following commands:

```bash
git clone https://github.com/[user]/[project_name]
cd [project_name]
mkdir build && cd build
cmake ..
make -j4
sudo make install
```

## Usage Details :orangutan:

To understand how to use any c++ project structure, the first question that comes
to mind is where you put your code. I decided to use the `src/`folder to place all
source and header files required for my projects. Many existing structures use
an `include/` folder, but I don't see myself making libraries anytime soon.

```
<TOPLEVEL_DIR>
    src/                # Any code that you write goes in here
        adder/          # Logically grouped source files
            adder.h
            adder.cpp
        main.cpp
    lib/                # Any dependencies get git submodule'd in here
        glfw/
            ...
        opencv/
            ...
    .gitignore          # comes preprepared with ignores for cmake and c++
    CMakeLists.txt      # preloaded with secret sauce
```


