cmake_minimum_required(VERSION 3.10)
project(laser C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

configure_file(biscuit.txt . COPYONLY)


add_executable(laser
        laser.c laser.h
        )
target_compile_options(laser PRIVATE -DMAIN)

add_executable(test
        test.c
        laser.c laser.h
        )
target_compile_options(test PRIVATE -DTEST)
