cmake_minimum_required(VERSION 3.27)
project(Mini_Photo_Editor)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        Mini_Photo_Editor main.cpp
        stb_image.h
        stb_image_write.h
)
