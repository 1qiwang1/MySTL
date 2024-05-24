cmake_minimum_required(VERSION 3.28)
project(MySTL)

set(CMAKE_CXX_STANDARD 11)

add_executable(MySTL main.cpp
        MyVector.h
        MyList.h
        HashTable.h
        MyDeque.h
        RedBlackTree.h
        MySet.h)
