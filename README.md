C++ Library for implementation of Tree and Graph Data Structure
================================================================

This is a simple and developer friendly implementation of the Tree and Graph Data Structure

- This library is fully generic so that it can be used with different programs
- Complexity of the implementations are simple and easy to manage
- Traversals and Algorithms implementations are efficient

## Installation

### Requirements

- GNU or MSVC compiler
- CMake

Clone the repository to your project

    git clone https://github.com/saswatdash65/graphandtree.git

You can dowload this repo as a submodule of your project

    git clone --recursive-submodule https://github.com/saswatdash65/graphandtree

### For Linux users

After ccloneing navigate to the repo ddirectory and make a build directory

    cd graphandtree
    mkdir builD

Run the following commands to build Makefile and install the library to your system

    cmake -B ./build
    cd build
    make
    sudo make install

If you don't want to install the library and only use it as submodule

    cmake -DINSTALL_LIB=OFF -B ./build
    cd build
    make

Add this script to your CMakeLists.txt file

    add_subdirectory(graphandtree)
    target_link_libraries(${PROJECT_NAME} ./graphandtree/build/libgraphandtree)
    target_include_directories(${PROJECT_NAME} PUBLIC ./graphandtree/include)
    target_link_directories(${PROJECT_NAME} PUBLIC ./graphandtree/build)

**Note:** This library is in development and not fully completed yet.