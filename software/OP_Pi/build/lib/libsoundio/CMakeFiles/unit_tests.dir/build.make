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
include lib/libsoundio/CMakeFiles/unit_tests.dir/depend.make

# Include the progress variables for this target.
include lib/libsoundio/CMakeFiles/unit_tests.dir/progress.make

# Include the compile flags for this target's objects.
include lib/libsoundio/CMakeFiles/unit_tests.dir/flags.make

lib/libsoundio/CMakeFiles/unit_tests.dir/test/unit_tests.c.o: lib/libsoundio/CMakeFiles/unit_tests.dir/flags.make
lib/libsoundio/CMakeFiles/unit_tests.dir/test/unit_tests.c.o: ../lib/libsoundio/test/unit_tests.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/libsoundio/CMakeFiles/unit_tests.dir/test/unit_tests.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/unit_tests.dir/test/unit_tests.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/test/unit_tests.c

lib/libsoundio/CMakeFiles/unit_tests.dir/test/unit_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_tests.dir/test/unit_tests.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/test/unit_tests.c > CMakeFiles/unit_tests.dir/test/unit_tests.c.i

lib/libsoundio/CMakeFiles/unit_tests.dir/test/unit_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_tests.dir/test/unit_tests.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/test/unit_tests.c -o CMakeFiles/unit_tests.dir/test/unit_tests.c.s

lib/libsoundio/CMakeFiles/unit_tests.dir/src/soundio.c.o: lib/libsoundio/CMakeFiles/unit_tests.dir/flags.make
lib/libsoundio/CMakeFiles/unit_tests.dir/src/soundio.c.o: ../lib/libsoundio/src/soundio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lib/libsoundio/CMakeFiles/unit_tests.dir/src/soundio.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/unit_tests.dir/src/soundio.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/soundio.c

lib/libsoundio/CMakeFiles/unit_tests.dir/src/soundio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_tests.dir/src/soundio.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/soundio.c > CMakeFiles/unit_tests.dir/src/soundio.c.i

lib/libsoundio/CMakeFiles/unit_tests.dir/src/soundio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_tests.dir/src/soundio.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/soundio.c -o CMakeFiles/unit_tests.dir/src/soundio.c.s

lib/libsoundio/CMakeFiles/unit_tests.dir/src/util.c.o: lib/libsoundio/CMakeFiles/unit_tests.dir/flags.make
lib/libsoundio/CMakeFiles/unit_tests.dir/src/util.c.o: ../lib/libsoundio/src/util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object lib/libsoundio/CMakeFiles/unit_tests.dir/src/util.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/unit_tests.dir/src/util.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/util.c

lib/libsoundio/CMakeFiles/unit_tests.dir/src/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_tests.dir/src/util.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/util.c > CMakeFiles/unit_tests.dir/src/util.c.i

lib/libsoundio/CMakeFiles/unit_tests.dir/src/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_tests.dir/src/util.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/util.c -o CMakeFiles/unit_tests.dir/src/util.c.s

lib/libsoundio/CMakeFiles/unit_tests.dir/src/os.c.o: lib/libsoundio/CMakeFiles/unit_tests.dir/flags.make
lib/libsoundio/CMakeFiles/unit_tests.dir/src/os.c.o: ../lib/libsoundio/src/os.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object lib/libsoundio/CMakeFiles/unit_tests.dir/src/os.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/unit_tests.dir/src/os.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/os.c

lib/libsoundio/CMakeFiles/unit_tests.dir/src/os.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_tests.dir/src/os.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/os.c > CMakeFiles/unit_tests.dir/src/os.c.i

lib/libsoundio/CMakeFiles/unit_tests.dir/src/os.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_tests.dir/src/os.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/os.c -o CMakeFiles/unit_tests.dir/src/os.c.s

lib/libsoundio/CMakeFiles/unit_tests.dir/src/dummy.c.o: lib/libsoundio/CMakeFiles/unit_tests.dir/flags.make
lib/libsoundio/CMakeFiles/unit_tests.dir/src/dummy.c.o: ../lib/libsoundio/src/dummy.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object lib/libsoundio/CMakeFiles/unit_tests.dir/src/dummy.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/unit_tests.dir/src/dummy.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/dummy.c

lib/libsoundio/CMakeFiles/unit_tests.dir/src/dummy.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_tests.dir/src/dummy.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/dummy.c > CMakeFiles/unit_tests.dir/src/dummy.c.i

lib/libsoundio/CMakeFiles/unit_tests.dir/src/dummy.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_tests.dir/src/dummy.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/dummy.c -o CMakeFiles/unit_tests.dir/src/dummy.c.s

lib/libsoundio/CMakeFiles/unit_tests.dir/src/channel_layout.c.o: lib/libsoundio/CMakeFiles/unit_tests.dir/flags.make
lib/libsoundio/CMakeFiles/unit_tests.dir/src/channel_layout.c.o: ../lib/libsoundio/src/channel_layout.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object lib/libsoundio/CMakeFiles/unit_tests.dir/src/channel_layout.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/unit_tests.dir/src/channel_layout.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/channel_layout.c

lib/libsoundio/CMakeFiles/unit_tests.dir/src/channel_layout.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_tests.dir/src/channel_layout.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/channel_layout.c > CMakeFiles/unit_tests.dir/src/channel_layout.c.i

lib/libsoundio/CMakeFiles/unit_tests.dir/src/channel_layout.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_tests.dir/src/channel_layout.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/channel_layout.c -o CMakeFiles/unit_tests.dir/src/channel_layout.c.s

lib/libsoundio/CMakeFiles/unit_tests.dir/src/ring_buffer.c.o: lib/libsoundio/CMakeFiles/unit_tests.dir/flags.make
lib/libsoundio/CMakeFiles/unit_tests.dir/src/ring_buffer.c.o: ../lib/libsoundio/src/ring_buffer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object lib/libsoundio/CMakeFiles/unit_tests.dir/src/ring_buffer.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/unit_tests.dir/src/ring_buffer.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/ring_buffer.c

lib/libsoundio/CMakeFiles/unit_tests.dir/src/ring_buffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_tests.dir/src/ring_buffer.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/ring_buffer.c > CMakeFiles/unit_tests.dir/src/ring_buffer.c.i

lib/libsoundio/CMakeFiles/unit_tests.dir/src/ring_buffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_tests.dir/src/ring_buffer.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/ring_buffer.c -o CMakeFiles/unit_tests.dir/src/ring_buffer.c.s

lib/libsoundio/CMakeFiles/unit_tests.dir/src/jack.c.o: lib/libsoundio/CMakeFiles/unit_tests.dir/flags.make
lib/libsoundio/CMakeFiles/unit_tests.dir/src/jack.c.o: ../lib/libsoundio/src/jack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object lib/libsoundio/CMakeFiles/unit_tests.dir/src/jack.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/unit_tests.dir/src/jack.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/jack.c

lib/libsoundio/CMakeFiles/unit_tests.dir/src/jack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_tests.dir/src/jack.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/jack.c > CMakeFiles/unit_tests.dir/src/jack.c.i

lib/libsoundio/CMakeFiles/unit_tests.dir/src/jack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_tests.dir/src/jack.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/jack.c -o CMakeFiles/unit_tests.dir/src/jack.c.s

lib/libsoundio/CMakeFiles/unit_tests.dir/src/pulseaudio.c.o: lib/libsoundio/CMakeFiles/unit_tests.dir/flags.make
lib/libsoundio/CMakeFiles/unit_tests.dir/src/pulseaudio.c.o: ../lib/libsoundio/src/pulseaudio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object lib/libsoundio/CMakeFiles/unit_tests.dir/src/pulseaudio.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/unit_tests.dir/src/pulseaudio.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/pulseaudio.c

lib/libsoundio/CMakeFiles/unit_tests.dir/src/pulseaudio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_tests.dir/src/pulseaudio.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/pulseaudio.c > CMakeFiles/unit_tests.dir/src/pulseaudio.c.i

lib/libsoundio/CMakeFiles/unit_tests.dir/src/pulseaudio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_tests.dir/src/pulseaudio.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/pulseaudio.c -o CMakeFiles/unit_tests.dir/src/pulseaudio.c.s

lib/libsoundio/CMakeFiles/unit_tests.dir/src/alsa.c.o: lib/libsoundio/CMakeFiles/unit_tests.dir/flags.make
lib/libsoundio/CMakeFiles/unit_tests.dir/src/alsa.c.o: ../lib/libsoundio/src/alsa.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object lib/libsoundio/CMakeFiles/unit_tests.dir/src/alsa.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/unit_tests.dir/src/alsa.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/alsa.c

lib/libsoundio/CMakeFiles/unit_tests.dir/src/alsa.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/unit_tests.dir/src/alsa.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/alsa.c > CMakeFiles/unit_tests.dir/src/alsa.c.i

lib/libsoundio/CMakeFiles/unit_tests.dir/src/alsa.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/unit_tests.dir/src/alsa.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/alsa.c -o CMakeFiles/unit_tests.dir/src/alsa.c.s

# Object files for target unit_tests
unit_tests_OBJECTS = \
"CMakeFiles/unit_tests.dir/test/unit_tests.c.o" \
"CMakeFiles/unit_tests.dir/src/soundio.c.o" \
"CMakeFiles/unit_tests.dir/src/util.c.o" \
"CMakeFiles/unit_tests.dir/src/os.c.o" \
"CMakeFiles/unit_tests.dir/src/dummy.c.o" \
"CMakeFiles/unit_tests.dir/src/channel_layout.c.o" \
"CMakeFiles/unit_tests.dir/src/ring_buffer.c.o" \
"CMakeFiles/unit_tests.dir/src/jack.c.o" \
"CMakeFiles/unit_tests.dir/src/pulseaudio.c.o" \
"CMakeFiles/unit_tests.dir/src/alsa.c.o"

# External object files for target unit_tests
unit_tests_EXTERNAL_OBJECTS =

lib/libsoundio/unit_tests: lib/libsoundio/CMakeFiles/unit_tests.dir/test/unit_tests.c.o
lib/libsoundio/unit_tests: lib/libsoundio/CMakeFiles/unit_tests.dir/src/soundio.c.o
lib/libsoundio/unit_tests: lib/libsoundio/CMakeFiles/unit_tests.dir/src/util.c.o
lib/libsoundio/unit_tests: lib/libsoundio/CMakeFiles/unit_tests.dir/src/os.c.o
lib/libsoundio/unit_tests: lib/libsoundio/CMakeFiles/unit_tests.dir/src/dummy.c.o
lib/libsoundio/unit_tests: lib/libsoundio/CMakeFiles/unit_tests.dir/src/channel_layout.c.o
lib/libsoundio/unit_tests: lib/libsoundio/CMakeFiles/unit_tests.dir/src/ring_buffer.c.o
lib/libsoundio/unit_tests: lib/libsoundio/CMakeFiles/unit_tests.dir/src/jack.c.o
lib/libsoundio/unit_tests: lib/libsoundio/CMakeFiles/unit_tests.dir/src/pulseaudio.c.o
lib/libsoundio/unit_tests: lib/libsoundio/CMakeFiles/unit_tests.dir/src/alsa.c.o
lib/libsoundio/unit_tests: lib/libsoundio/CMakeFiles/unit_tests.dir/build.make
lib/libsoundio/unit_tests: /usr/lib/arm-linux-gnueabihf/libjack.so
lib/libsoundio/unit_tests: /usr/lib/arm-linux-gnueabihf/libpulse.so
lib/libsoundio/unit_tests: /usr/lib/arm-linux-gnueabihf/libasound.so
lib/libsoundio/unit_tests: lib/libsoundio/CMakeFiles/unit_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking C executable unit_tests"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unit_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/libsoundio/CMakeFiles/unit_tests.dir/build: lib/libsoundio/unit_tests

.PHONY : lib/libsoundio/CMakeFiles/unit_tests.dir/build

lib/libsoundio/CMakeFiles/unit_tests.dir/clean:
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && $(CMAKE_COMMAND) -P CMakeFiles/unit_tests.dir/cmake_clean.cmake
.PHONY : lib/libsoundio/CMakeFiles/unit_tests.dir/clean

lib/libsoundio/CMakeFiles/unit_tests.dir/depend:
	cd /home/pi/OP-Pi/software/OPPi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/OP-Pi/software/OPPi /home/pi/OP-Pi/software/OPPi/lib/libsoundio /home/pi/OP-Pi/software/OPPi/build /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio/CMakeFiles/unit_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/libsoundio/CMakeFiles/unit_tests.dir/depend

