# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/dictionary_tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/dictionary_tests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/dictionary_tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dictionary_tests.dir/flags.make

CMakeFiles/dictionary_tests.dir/trie.c.o: CMakeFiles/dictionary_tests.dir/flags.make
CMakeFiles/dictionary_tests.dir/trie.c.o: ../trie.c
CMakeFiles/dictionary_tests.dir/trie.c.o: CMakeFiles/dictionary_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/dictionary_tests.dir/trie.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/dictionary_tests.dir/trie.c.o -MF CMakeFiles/dictionary_tests.dir/trie.c.o.d -o CMakeFiles/dictionary_tests.dir/trie.c.o -c /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/trie.c

CMakeFiles/dictionary_tests.dir/trie.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dictionary_tests.dir/trie.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/trie.c > CMakeFiles/dictionary_tests.dir/trie.c.i

CMakeFiles/dictionary_tests.dir/trie.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dictionary_tests.dir/trie.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/trie.c -o CMakeFiles/dictionary_tests.dir/trie.c.s

CMakeFiles/dictionary_tests.dir/doublets.c.o: CMakeFiles/dictionary_tests.dir/flags.make
CMakeFiles/dictionary_tests.dir/doublets.c.o: ../doublets.c
CMakeFiles/dictionary_tests.dir/doublets.c.o: CMakeFiles/dictionary_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/dictionary_tests.dir/doublets.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/dictionary_tests.dir/doublets.c.o -MF CMakeFiles/dictionary_tests.dir/doublets.c.o.d -o CMakeFiles/dictionary_tests.dir/doublets.c.o -c /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/doublets.c

CMakeFiles/dictionary_tests.dir/doublets.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dictionary_tests.dir/doublets.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/doublets.c > CMakeFiles/dictionary_tests.dir/doublets.c.i

CMakeFiles/dictionary_tests.dir/doublets.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dictionary_tests.dir/doublets.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/doublets.c -o CMakeFiles/dictionary_tests.dir/doublets.c.s

CMakeFiles/dictionary_tests.dir/trie_tests.c.o: CMakeFiles/dictionary_tests.dir/flags.make
CMakeFiles/dictionary_tests.dir/trie_tests.c.o: ../trie_tests.c
CMakeFiles/dictionary_tests.dir/trie_tests.c.o: CMakeFiles/dictionary_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/dictionary_tests.dir/trie_tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/dictionary_tests.dir/trie_tests.c.o -MF CMakeFiles/dictionary_tests.dir/trie_tests.c.o.d -o CMakeFiles/dictionary_tests.dir/trie_tests.c.o -c /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/trie_tests.c

CMakeFiles/dictionary_tests.dir/trie_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dictionary_tests.dir/trie_tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/trie_tests.c > CMakeFiles/dictionary_tests.dir/trie_tests.c.i

CMakeFiles/dictionary_tests.dir/trie_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dictionary_tests.dir/trie_tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/trie_tests.c -o CMakeFiles/dictionary_tests.dir/trie_tests.c.s

# Object files for target dictionary_tests
dictionary_tests_OBJECTS = \
"CMakeFiles/dictionary_tests.dir/trie.c.o" \
"CMakeFiles/dictionary_tests.dir/doublets.c.o" \
"CMakeFiles/dictionary_tests.dir/trie_tests.c.o"

# External object files for target dictionary_tests
dictionary_tests_EXTERNAL_OBJECTS =

dictionary_tests: CMakeFiles/dictionary_tests.dir/trie.c.o
dictionary_tests: CMakeFiles/dictionary_tests.dir/doublets.c.o
dictionary_tests: CMakeFiles/dictionary_tests.dir/trie_tests.c.o
dictionary_tests: CMakeFiles/dictionary_tests.dir/build.make
dictionary_tests: ../lib/libcriterion.so
dictionary_tests: CMakeFiles/dictionary_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable dictionary_tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dictionary_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dictionary_tests.dir/build: dictionary_tests
.PHONY : CMakeFiles/dictionary_tests.dir/build

CMakeFiles/dictionary_tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dictionary_tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dictionary_tests.dir/clean

CMakeFiles/dictionary_tests.dir/depend:
	cd /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug/CMakeFiles/dictionary_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dictionary_tests.dir/depend
