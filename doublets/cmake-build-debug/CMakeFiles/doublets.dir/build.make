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
include CMakeFiles/doublets.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/doublets.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/doublets.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/doublets.dir/flags.make

CMakeFiles/doublets.dir/main.c.o: CMakeFiles/doublets.dir/flags.make
CMakeFiles/doublets.dir/main.c.o: ../main.c
CMakeFiles/doublets.dir/main.c.o: CMakeFiles/doublets.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/doublets.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/doublets.dir/main.c.o -MF CMakeFiles/doublets.dir/main.c.o.d -o CMakeFiles/doublets.dir/main.c.o -c /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/main.c

CMakeFiles/doublets.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/doublets.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/main.c > CMakeFiles/doublets.dir/main.c.i

CMakeFiles/doublets.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/doublets.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/main.c -o CMakeFiles/doublets.dir/main.c.s

CMakeFiles/doublets.dir/doublets.c.o: CMakeFiles/doublets.dir/flags.make
CMakeFiles/doublets.dir/doublets.c.o: ../doublets.c
CMakeFiles/doublets.dir/doublets.c.o: CMakeFiles/doublets.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/doublets.dir/doublets.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/doublets.dir/doublets.c.o -MF CMakeFiles/doublets.dir/doublets.c.o.d -o CMakeFiles/doublets.dir/doublets.c.o -c /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/doublets.c

CMakeFiles/doublets.dir/doublets.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/doublets.dir/doublets.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/doublets.c > CMakeFiles/doublets.dir/doublets.c.i

CMakeFiles/doublets.dir/doublets.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/doublets.dir/doublets.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/doublets.c -o CMakeFiles/doublets.dir/doublets.c.s

CMakeFiles/doublets.dir/trie.c.o: CMakeFiles/doublets.dir/flags.make
CMakeFiles/doublets.dir/trie.c.o: ../trie.c
CMakeFiles/doublets.dir/trie.c.o: CMakeFiles/doublets.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/doublets.dir/trie.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/doublets.dir/trie.c.o -MF CMakeFiles/doublets.dir/trie.c.o.d -o CMakeFiles/doublets.dir/trie.c.o -c /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/trie.c

CMakeFiles/doublets.dir/trie.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/doublets.dir/trie.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/trie.c > CMakeFiles/doublets.dir/trie.c.i

CMakeFiles/doublets.dir/trie.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/doublets.dir/trie.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/trie.c -o CMakeFiles/doublets.dir/trie.c.s

# Object files for target doublets
doublets_OBJECTS = \
"CMakeFiles/doublets.dir/main.c.o" \
"CMakeFiles/doublets.dir/doublets.c.o" \
"CMakeFiles/doublets.dir/trie.c.o"

# External object files for target doublets
doublets_EXTERNAL_OBJECTS =

doublets: CMakeFiles/doublets.dir/main.c.o
doublets: CMakeFiles/doublets.dir/doublets.c.o
doublets: CMakeFiles/doublets.dir/trie.c.o
doublets: CMakeFiles/doublets.dir/build.make
doublets: CMakeFiles/doublets.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable doublets"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/doublets.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/doublets.dir/build: doublets
.PHONY : CMakeFiles/doublets.dir/build

CMakeFiles/doublets.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/doublets.dir/cmake_clean.cmake
.PHONY : CMakeFiles/doublets.dir/clean

CMakeFiles/doublets.dir/depend:
	cd /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug /homes/tk1622/Documents/computing_practical_1/c/PastCTests/doublets/cmake-build-debug/CMakeFiles/doublets.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/doublets.dir/depend
