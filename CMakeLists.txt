cmake_minimum_required(VERSION 3.26)
project(TIZD_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(TIZD_2 main.cpp
        menu/MenuItem.cpp
        menu/MenuItem.h
        menu/MenuManager.cpp
        menu/MenuManager.h
        tree.h
        exceptions/exceptions.h
)
