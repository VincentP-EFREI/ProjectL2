cmake_minimum_required(VERSION 3.24)
project(ProjectL2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ProjectL2
        contact.c
        contact.h
        main.c
        set.c
        set.h
        timer.c
        timer.h
        TimeTest.c
        TimeTest.h)
