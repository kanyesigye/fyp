# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/johntuza/Downloads/clion-2017.3.4/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/johntuza/Downloads/clion-2017.3.4/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/johntuza/CLionProjects/Distributed_Rpc_Client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/johntuza/CLionProjects/Distributed_Rpc_Client/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Distributed_Rpc_Client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Distributed_Rpc_Client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Distributed_Rpc_Client.dir/flags.make

CMakeFiles/Distributed_Rpc_Client.dir/main.c.o: CMakeFiles/Distributed_Rpc_Client.dir/flags.make
CMakeFiles/Distributed_Rpc_Client.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/johntuza/CLionProjects/Distributed_Rpc_Client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Distributed_Rpc_Client.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Distributed_Rpc_Client.dir/main.c.o   -c /home/johntuza/CLionProjects/Distributed_Rpc_Client/main.c

CMakeFiles/Distributed_Rpc_Client.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Distributed_Rpc_Client.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/johntuza/CLionProjects/Distributed_Rpc_Client/main.c > CMakeFiles/Distributed_Rpc_Client.dir/main.c.i

CMakeFiles/Distributed_Rpc_Client.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Distributed_Rpc_Client.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/johntuza/CLionProjects/Distributed_Rpc_Client/main.c -o CMakeFiles/Distributed_Rpc_Client.dir/main.c.s

CMakeFiles/Distributed_Rpc_Client.dir/main.c.o.requires:

.PHONY : CMakeFiles/Distributed_Rpc_Client.dir/main.c.o.requires

CMakeFiles/Distributed_Rpc_Client.dir/main.c.o.provides: CMakeFiles/Distributed_Rpc_Client.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/Distributed_Rpc_Client.dir/build.make CMakeFiles/Distributed_Rpc_Client.dir/main.c.o.provides.build
.PHONY : CMakeFiles/Distributed_Rpc_Client.dir/main.c.o.provides

CMakeFiles/Distributed_Rpc_Client.dir/main.c.o.provides.build: CMakeFiles/Distributed_Rpc_Client.dir/main.c.o


# Object files for target Distributed_Rpc_Client
Distributed_Rpc_Client_OBJECTS = \
"CMakeFiles/Distributed_Rpc_Client.dir/main.c.o"

# External object files for target Distributed_Rpc_Client
Distributed_Rpc_Client_EXTERNAL_OBJECTS =

Distributed_Rpc_Client: CMakeFiles/Distributed_Rpc_Client.dir/main.c.o
Distributed_Rpc_Client: CMakeFiles/Distributed_Rpc_Client.dir/build.make
Distributed_Rpc_Client: CMakeFiles/Distributed_Rpc_Client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/johntuza/CLionProjects/Distributed_Rpc_Client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Distributed_Rpc_Client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Distributed_Rpc_Client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Distributed_Rpc_Client.dir/build: Distributed_Rpc_Client

.PHONY : CMakeFiles/Distributed_Rpc_Client.dir/build

CMakeFiles/Distributed_Rpc_Client.dir/requires: CMakeFiles/Distributed_Rpc_Client.dir/main.c.o.requires

.PHONY : CMakeFiles/Distributed_Rpc_Client.dir/requires

CMakeFiles/Distributed_Rpc_Client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Distributed_Rpc_Client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Distributed_Rpc_Client.dir/clean

CMakeFiles/Distributed_Rpc_Client.dir/depend:
	cd /home/johntuza/CLionProjects/Distributed_Rpc_Client/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/johntuza/CLionProjects/Distributed_Rpc_Client /home/johntuza/CLionProjects/Distributed_Rpc_Client /home/johntuza/CLionProjects/Distributed_Rpc_Client/cmake-build-debug /home/johntuza/CLionProjects/Distributed_Rpc_Client/cmake-build-debug /home/johntuza/CLionProjects/Distributed_Rpc_Client/cmake-build-debug/CMakeFiles/Distributed_Rpc_Client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Distributed_Rpc_Client.dir/depend
