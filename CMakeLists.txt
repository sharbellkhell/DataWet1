cmake_minimum_required(VERSION 3.22)
project(AVLTree)

set(CMAKE_CXX_STANDARD 11)

add_executable(AVLTree AVLTree.cpp main.cpp  AVLTree.h Auxilaries.cpp Auxilaries.h exceptions.h remove.cpp)
