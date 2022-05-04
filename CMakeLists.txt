cmake_minimum_required(VERSION 3.22)
project(AVLTree)

set(CMAKE_CXX_STANDARD 11)

#add_custom_target(AVLTree COMMAND make -C ${mytest_SOURCE_DIR}
#        CLION_EXE_DIR=${PROJECT_BINARY_DIR})

#add_executable(AVLTree AVLTree.cpp Company.cpp main.cpp Auxilaries.cpp Employee.cpp)
add_executable(AVLTree AVLTree.cpp main.cpp Auxilaries.cpp)
