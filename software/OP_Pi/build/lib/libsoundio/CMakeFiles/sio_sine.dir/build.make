# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/OP-Pi/software/OPPi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/OP-Pi/software/OPPi/build

# Include any dependencies generated for this target.
include lib/libsoundio/CMakeFiles/sio_sine.dir/depend.make

# Include the progress variables for this target.
include lib/libsoundio/CMakeFiles/sio_sine.dir/progress.make

# Include the compile flags for this target's objects.
include lib/libsoundio/CMakeFiles/sio_sine.dir/flags.make

lib/libsoundio/CMakeFiles/sio_sine.dir/example/sio_sine.c.o: lib/libsoundio/CMakeFiles/sio_sine.dir/flags.make
lib/libsoundio/CMakeFiles/sio_sine.dir/example/sio_sine.c.o: ../lib/libsoundio/example/sio_sine.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/libsoundio/CMakeFiles/sio_sine.dir/example/sio_sine.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sio_sine.dir/example/sio_sine.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/example/sio_sine.c

lib/libsoundio/CMakeFiles/sio_sine.dir/example/sio_sine.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sio_sine.dir/example/sio_sine.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/example/sio_sine.c > CMakeFiles/sio_sine.dir/example/sio_sine.c.i

lib/libsoundio/CMakeFiles/sio_sine.dir/example/sio_sine.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sio_sine.dir/example/sio_sine.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/example/sio_sine.c -o CMakeFiles/sio_sine.dir/example/sio_sine.c.s

# Object files for target sio_sine
sio_sine_OBJECTS = \
"CMakeFiles/sio_sine.dir/example/sio_sine.c.o"

# External object files for target sio_sine
sio_sine_EXTERNAL_OBJECTS =

lib/libsoundio/sio_sine: lib/libsoundio/CMakeFiles/sio_sine.dir/example/sio_sine.c.o
lib/libsoundio/sio_sine: lib/libsoundio/CMakeFiles/sio_sine.dir/build.make
lib/libsoundio/sio_sine: lib/libsoundio/libsoundio.so.2.0.0
lib/libsoundio/sio_sine: /usr/lib/arm-linux-gnueabihf/libjack.so
lib/libsoundio/sio_sine: /usr/lib/arm-linux-gnueabihf/libpulse.so
lib/libsoundio/sio_sine: /usr/lib/arm-linux-gnueabihf/libasound.so
lib/libsoundio/sio_sine: lib/libsoundio/CMakeFiles/sio_sine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable sio_sine"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sio_sine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/libsoundio/CMakeFiles/sio_sine.dir/build: lib/libsoundio/sio_sine

.PHONY : lib/libsoundio/CMakeFiles/sio_sine.dir/build

lib/libsoundio/CMakeFiles/sio_sine.dir/clean:
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && $(CMAKE_COMMAND) -P CMakeFiles/sio_sine.dir/cmake_clean.cmake
.PHONY : lib/libsoundio/CMakeFiles/sio_sine.dir/clean

lib/libsoundio/CMakeFiles/sio_sine.dir/depend:
	cd /home/pi/OP-Pi/software/OPPi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/OP-Pi/software/OPPi /home/pi/OP-Pi/software/OPPi/lib/libsoundio /home/pi/OP-Pi/software/OPPi/build /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio/CMakeFiles/sio_sine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/libsoundio/CMakeFiles/sio_sine.dir/depend

