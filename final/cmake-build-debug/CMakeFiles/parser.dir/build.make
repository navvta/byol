# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/adrian/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/182.4505.18/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/adrian/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/182.4505.18/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adrian/programming/byol/ch12

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adrian/programming/byol/ch12/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/parser.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/parser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/parser.dir/flags.make

CMakeFiles/parser.dir/builtins.c.o: CMakeFiles/parser.dir/flags.make
CMakeFiles/parser.dir/builtins.c.o: ../builtins.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adrian/programming/byol/ch12/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/parser.dir/builtins.c.o"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/parser.dir/builtins.c.o   -c /home/adrian/programming/byol/ch12/builtins.c

CMakeFiles/parser.dir/builtins.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/parser.dir/builtins.c.i"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adrian/programming/byol/ch12/builtins.c > CMakeFiles/parser.dir/builtins.c.i

CMakeFiles/parser.dir/builtins.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/parser.dir/builtins.c.s"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adrian/programming/byol/ch12/builtins.c -o CMakeFiles/parser.dir/builtins.c.s

CMakeFiles/parser.dir/lval.c.o: CMakeFiles/parser.dir/flags.make
CMakeFiles/parser.dir/lval.c.o: ../lval.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adrian/programming/byol/ch12/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/parser.dir/lval.c.o"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/parser.dir/lval.c.o   -c /home/adrian/programming/byol/ch12/lval.c

CMakeFiles/parser.dir/lval.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/parser.dir/lval.c.i"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adrian/programming/byol/ch12/lval.c > CMakeFiles/parser.dir/lval.c.i

CMakeFiles/parser.dir/lval.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/parser.dir/lval.c.s"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adrian/programming/byol/ch12/lval.c -o CMakeFiles/parser.dir/lval.c.s

CMakeFiles/parser.dir/mpc.c.o: CMakeFiles/parser.dir/flags.make
CMakeFiles/parser.dir/mpc.c.o: ../mpc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adrian/programming/byol/ch12/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/parser.dir/mpc.c.o"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/parser.dir/mpc.c.o   -c /home/adrian/programming/byol/ch12/mpc.c

CMakeFiles/parser.dir/mpc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/parser.dir/mpc.c.i"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adrian/programming/byol/ch12/mpc.c > CMakeFiles/parser.dir/mpc.c.i

CMakeFiles/parser.dir/mpc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/parser.dir/mpc.c.s"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adrian/programming/byol/ch12/mpc.c -o CMakeFiles/parser.dir/mpc.c.s

CMakeFiles/parser.dir/parser.c.o: CMakeFiles/parser.dir/flags.make
CMakeFiles/parser.dir/parser.c.o: ../parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adrian/programming/byol/ch12/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/parser.dir/parser.c.o"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/parser.dir/parser.c.o   -c /home/adrian/programming/byol/ch12/parser.c

CMakeFiles/parser.dir/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/parser.dir/parser.c.i"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adrian/programming/byol/ch12/parser.c > CMakeFiles/parser.dir/parser.c.i

CMakeFiles/parser.dir/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/parser.dir/parser.c.s"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adrian/programming/byol/ch12/parser.c -o CMakeFiles/parser.dir/parser.c.s

# Object files for target parser
parser_OBJECTS = \
"CMakeFiles/parser.dir/builtins.c.o" \
"CMakeFiles/parser.dir/lval.c.o" \
"CMakeFiles/parser.dir/mpc.c.o" \
"CMakeFiles/parser.dir/parser.c.o"

# External object files for target parser
parser_EXTERNAL_OBJECTS =

parser: CMakeFiles/parser.dir/builtins.c.o
parser: CMakeFiles/parser.dir/lval.c.o
parser: CMakeFiles/parser.dir/mpc.c.o
parser: CMakeFiles/parser.dir/parser.c.o
parser: CMakeFiles/parser.dir/build.make
parser: CMakeFiles/parser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adrian/programming/byol/ch12/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable parser"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/parser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/parser.dir/build: parser

.PHONY : CMakeFiles/parser.dir/build

CMakeFiles/parser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/parser.dir/cmake_clean.cmake
.PHONY : CMakeFiles/parser.dir/clean

CMakeFiles/parser.dir/depend:
	cd /home/adrian/programming/byol/ch12/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adrian/programming/byol/ch12 /home/adrian/programming/byol/ch12 /home/adrian/programming/byol/ch12/cmake-build-debug /home/adrian/programming/byol/ch12/cmake-build-debug /home/adrian/programming/byol/ch12/cmake-build-debug/CMakeFiles/parser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/parser.dir/depend
