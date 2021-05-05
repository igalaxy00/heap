cmake_minimum_required(VERSION 3.19)
project(lowlevelprog C)

set(CMAKE_C_STANDARD 11)

add_executable(lowlevelprog lab5/src/main.c lab5/include/heap.h lab5/src/heap.c lab5/include/libHeap.h lab5/test/test.c lab5/test/CuTest.h lab5/test/CuTest.c)