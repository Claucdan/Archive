cmake_minimum_required(VERSION 3.26)
project(test_c C)

set(CMAKE_C_STANDARD 17)

add_executable(test_c main.c
        abc.h
        tree_of_haffman.h
        string.h
        arc.h
        decode_arc_file.h
)
