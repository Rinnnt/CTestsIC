cmake_minimum_required(VERSION 3.10)
project(gogen C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

configure_file(gogen-challenge.txt . COPYONLY)
configure_file(gogen-easy.txt . COPYONLY)


add_executable(letter_mask
        letter_mask.c letter_mask.h
        )
target_compile_options(letter_mask PRIVATE -DMAIN_LETTER_MASK)

add_executable(gogen
        gogen.c gogen.h
        letter_mask.c letter_mask.h
        )
target_compile_options(gogen PRIVATE -DMAIN_GOGEN)

add_executable(testA
        testA.c
        letter_mask.c letter_mask.h
        )

add_executable(testB
        testB.c
        gogen.c gogen.h
        letter_mask.c letter_mask.h
        )
