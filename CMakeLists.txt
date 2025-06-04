cmake_minimum_required(VERSION 3.28)
project(2D_Drawing)

set(CMAKE_CXX_STANDARD 14)

add_executable(2D_Drawing
        main.cpp
        Source/Utils.cpp
        Source/Circle.cpp
        Source/Clipping.cpp
        Source/MenuController.cpp
        Source/Line.cpp
        Source/Ellipse.cpp
        Source/Filling.cpp
        Source/Curves.cpp)
