cmake_minimum_required(VERSION 3.28)
project(ProcessMemoryManipulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProcessMemoryManipulator main.cpp
        MemoryManipulator.cpp
        MemoryManipulator.h
        WindowsMemoryManipulator.cpp
        WindowsMemoryManipulator.h)
