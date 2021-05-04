cmake_minimum_required(VERSION 3.19)
project(lowlevelprog C)

set(CMAKE_C_STANDARD 11)

add_executable(lowlevelprog lab5/src/main.c lab5/src/heap.h lab5/src/heap_main.c lab5/src/libHeap.h)