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
include CMakeFiles/ch12.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ch12.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ch12.dir/flags.make

CMakeFiles/ch12.dir/builtins.c.o: CMakeFiles/ch12.dir/flags.make
CMakeFiles/ch12.dir/builtins.c.o: ../builtins.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adrian/programming/byol/ch12/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ch12.dir/builtins.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ch12.dir/builtins.c.o   -c /home/adrian/programming/byol/ch12/builtins.c

CMakeFiles/ch12.dir/builtins.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ch12.dir/builtins.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adrian/programming/byol/ch12/builtins.c > CMakeFiles/ch12.dir/builtins.c.i

CMakeFiles/ch12.dir/builtins.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ch12.dir/builtins.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adrian/programming/byol/ch12/builtins.c -o CMakeFiles/ch12.dir/builtins.c.s

CMakeFiles/ch12.dir/lval.c.o: CMakeFiles/ch12.dir/flags.make
CMakeFiles/ch12.dir/lval.c.o: ../lval.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adrian/programming/byol/ch12/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ch12.dir/lval.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ch12.dir/lval.c.o   -c /home/adrian/programming/byol/ch12/lval.c

CMakeFiles/ch12.dir/lval.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ch12.dir/lval.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adrian/programming/byol/ch12/lval.c > CMakeFiles/ch12.dir/lval.c.i

CMakeFiles/ch12.dir/lval.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ch12.dir/lval.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adrian/programming/byol/ch12/lval.c -o CMakeFiles/ch12.dir/lval.c.s

CMakeFiles/ch12.dir/mpc.c.o: CMakeFiles/ch12.dir/flags.make
CMakeFiles/ch12.dir/mpc.c.o: ../mpc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adrian/programming/byol/ch12/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/ch12.dir/mpc.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ch12.dir/mpc.c.o   -c /home/adrian/programming/byol/ch12/mpc.c

CMakeFiles/ch12.dir/mpc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ch12.dir/mpc.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adrian/programming/byol/ch12/mpc.c > CMakeFiles/ch12.dir/mpc.c.i

CMakeFiles/ch12.dir/mpc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ch12.dir/mpc.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adrian/programming/byol/ch12/mpc.c -o CMakeFiles/ch12.dir/mpc.c.s

CMakeFiles/ch12.dir/parser.c.o: CMakeFiles/ch12.dir/flags.make
CMakeFiles/ch12.dir/parser.c.o: ../parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adrian/programming/byol/ch12/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/ch12.dir/parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ch12.dir/parser.c.o   -c /home/adrian/programming/byol/ch12/parser.c

CMakeFiles/ch12.dir/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ch12.dir/parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adrian/programming/byol/ch12/parser.c > CMakeFiles/ch12.dir/parser.c.i

CMakeFiles/ch12.dir/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ch12.dir/parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adrian/programming/byol/ch12/parser.c -o CMakeFiles/ch12.dir/parser.c.s

# Object files for target ch12
ch12_OBJECTS = \
"CMakeFiles/ch12.dir/builtins.c.o" \
"CMakeFiles/ch12.dir/lval.c.o" \
"CMakeFiles/ch12.dir/mpc.c.o" \
"CMakeFiles/ch12.dir/parser.c.o"

# External object files for target ch12
ch12_EXTERNAL_OBJECTS =

ch12: CMakeFiles/ch12.dir/builtins.c.o
ch12: CMakeFiles/ch12.dir/lval.c.o
ch12: CMakeFiles/ch12.dir/mpc.c.o
ch12: CMakeFiles/ch12.dir/parser.c.o
ch12: CMakeFiles/ch12.dir/build.make
ch12: CMakeFiles/ch12.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adrian/programming/byol/ch12/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable ch12"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ch12.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ch12.dir/build: ch12

.PHONY : CMakeFiles/ch12.dir/build

CMakeFiles/ch12.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ch12.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ch12.dir/clean

CMakeFiles/ch12.dir/depend:
	cd /home/adrian/programming/byol/ch12/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adrian/programming/byol/ch12 /home/adrian/programming/byol/ch12 /home/adrian/programming/byol/ch12/cmake-build-debug /home/adrian/programming/byol/ch12/cmake-build-debug /home/adrian/programming/byol/ch12/cmake-build-debug/CMakeFiles/ch12.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ch12.dir/depend

