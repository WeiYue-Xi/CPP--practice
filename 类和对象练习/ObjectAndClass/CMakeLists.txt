cmake_minimum_required(VERSION 4.0)
project(ObjectAndClass)

set(CMAKE_CXX_STANDARD 20)

add_executable(ObjectAndClass main.cpp
        example/Student.cpp
        example/Student.h
        example/Point.cpp
        example/Point.h
        example/Tracker.cpp
        example/Tracker.h
        example/Score.cpp
        example/Score.h
)
