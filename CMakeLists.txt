cmake_minimum_required(VERSION 3.30)
project(C_Store_Management C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Store_Management main.c
        src/function.c
        include/function.h
        include/datatype.h
        include/product.h
        include/category.h
        src/category.c
        src/product.c)
