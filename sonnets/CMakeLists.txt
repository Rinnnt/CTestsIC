cmake_minimum_required(VERSION 3.10)
project(sonnets C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

configure_file(dictionary.txt . COPYONLY)
configure_file(empty.txt . COPYONLY)
configure_file(shakespeare.txt . COPYONLY)
configure_file(spenser.txt . COPYONLY)
configure_file(petrarch.txt . COPYONLY)

add_executable(trie
        trie.c trie.h
        )
target_compile_options(trie PRIVATE -DTRIE_MAIN)

add_executable(sonnets_trie
        sonnets.c sonnets.h
        trie.c trie.h
        maps.c maps.h
        )
target_compile_options(sonnets_trie PRIVATE -DMY_TRIE -DSONNETS_MAIN)

add_executable(sonnets_map
        sonnets.c sonnets.h
        trie.c trie.h
        maps.c maps.h
        )
target_compile_options(sonnets_map PRIVATE -DSONNETS_MAIN)

add_executable(testA
        testA.c
        trie.c trie.h
        )
target_compile_options(testA PRIVATE -DTESTING)

add_executable(testB
        testB.c
        sonnets.c sonnets.h
        trie.c trie.h
        maps.c maps.h
        )
target_compile_options(testB PRIVATE -DTESTING)
