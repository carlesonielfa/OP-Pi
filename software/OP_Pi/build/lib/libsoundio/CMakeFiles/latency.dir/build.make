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
include lib/libsoundio/CMakeFiles/latency.dir/depend.make

# Include the progress variables for this target.
include lib/libsoundio/CMakeFiles/latency.dir/progress.make

# Include the compile flags for this target's objects.
include lib/libsoundio/CMakeFiles/latency.dir/flags.make

lib/libsoundio/CMakeFiles/latency.dir/test/latency.c.o: lib/libsoundio/CMakeFiles/latency.dir/flags.make
lib/libsoundio/CMakeFiles/latency.dir/test/latency.c.o: ../lib/libsoundio/test/latency.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/libsoundio/CMakeFiles/latency.dir/test/latency.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/latency.dir/test/latency.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/test/latency.c

lib/libsoundio/CMakeFiles/latency.dir/test/latency.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/latency.dir/test/latency.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/test/latency.c > CMakeFiles/latency.dir/test/latency.c.i

lib/libsoundio/CMakeFiles/latency.dir/test/latency.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/latency.dir/test/latency.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/test/latency.c -o CMakeFiles/latency.dir/test/latency.c.s

lib/libsoundio/CMakeFiles/latency.dir/src/soundio.c.o: lib/libsoundio/CMakeFiles/latency.dir/flags.make
lib/libsoundio/CMakeFiles/latency.dir/src/soundio.c.o: ../lib/libsoundio/src/soundio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lib/libsoundio/CMakeFiles/latency.dir/src/soundio.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/latency.dir/src/soundio.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/soundio.c

lib/libsoundio/CMakeFiles/latency.dir/src/soundio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/latency.dir/src/soundio.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/soundio.c > CMakeFiles/latency.dir/src/soundio.c.i

lib/libsoundio/CMakeFiles/latency.dir/src/soundio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/latency.dir/src/soundio.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/soundio.c -o CMakeFiles/latency.dir/src/soundio.c.s

lib/libsoundio/CMakeFiles/latency.dir/src/util.c.o: lib/libsoundio/CMakeFiles/latency.dir/flags.make
lib/libsoundio/CMakeFiles/latency.dir/src/util.c.o: ../lib/libsoundio/src/util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object lib/libsoundio/CMakeFiles/latency.dir/src/util.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/latency.dir/src/util.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/util.c

lib/libsoundio/CMakeFiles/latency.dir/src/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/latency.dir/src/util.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/util.c > CMakeFiles/latency.dir/src/util.c.i

lib/libsoundio/CMakeFiles/latency.dir/src/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/latency.dir/src/util.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/util.c -o CMakeFiles/latency.dir/src/util.c.s

lib/libsoundio/CMakeFiles/latency.dir/src/os.c.o: lib/libsoundio/CMakeFiles/latency.dir/flags.make
lib/libsoundio/CMakeFiles/latency.dir/src/os.c.o: ../lib/libsoundio/src/os.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object lib/libsoundio/CMakeFiles/latency.dir/src/os.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/latency.dir/src/os.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/os.c

lib/libsoundio/CMakeFiles/latency.dir/src/os.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/latency.dir/src/os.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/os.c > CMakeFiles/latency.dir/src/os.c.i

lib/libsoundio/CMakeFiles/latency.dir/src/os.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/latency.dir/src/os.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/os.c -o CMakeFiles/latency.dir/src/os.c.s

lib/libsoundio/CMakeFiles/latency.dir/src/dummy.c.o: lib/libsoundio/CMakeFiles/latency.dir/flags.make
lib/libsoundio/CMakeFiles/latency.dir/src/dummy.c.o: ../lib/libsoundio/src/dummy.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object lib/libsoundio/CMakeFiles/latency.dir/src/dummy.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/latency.dir/src/dummy.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/dummy.c

lib/libsoundio/CMakeFiles/latency.dir/src/dummy.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/latency.dir/src/dummy.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/dummy.c > CMakeFiles/latency.dir/src/dummy.c.i

lib/libsoundio/CMakeFiles/latency.dir/src/dummy.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/latency.dir/src/dummy.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/dummy.c -o CMakeFiles/latency.dir/src/dummy.c.s

lib/libsoundio/CMakeFiles/latency.dir/src/channel_layout.c.o: lib/libsoundio/CMakeFiles/latency.dir/flags.make
lib/libsoundio/CMakeFiles/latency.dir/src/channel_layout.c.o: ../lib/libsoundio/src/channel_layout.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object lib/libsoundio/CMakeFiles/latency.dir/src/channel_layout.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/latency.dir/src/channel_layout.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/channel_layout.c

lib/libsoundio/CMakeFiles/latency.dir/src/channel_layout.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/latency.dir/src/channel_layout.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/channel_layout.c > CMakeFiles/latency.dir/src/channel_layout.c.i

lib/libsoundio/CMakeFiles/latency.dir/src/channel_layout.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/latency.dir/src/channel_layout.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/channel_layout.c -o CMakeFiles/latency.dir/src/channel_layout.c.s

lib/libsoundio/CMakeFiles/latency.dir/src/ring_buffer.c.o: lib/libsoundio/CMakeFiles/latency.dir/flags.make
lib/libsoundio/CMakeFiles/latency.dir/src/ring_buffer.c.o: ../lib/libsoundio/src/ring_buffer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object lib/libsoundio/CMakeFiles/latency.dir/src/ring_buffer.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/latency.dir/src/ring_buffer.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/ring_buffer.c

lib/libsoundio/CMakeFiles/latency.dir/src/ring_buffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/latency.dir/src/ring_buffer.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/ring_buffer.c > CMakeFiles/latency.dir/src/ring_buffer.c.i

lib/libsoundio/CMakeFiles/latency.dir/src/ring_buffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/latency.dir/src/ring_buffer.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/ring_buffer.c -o CMakeFiles/latency.dir/src/ring_buffer.c.s

lib/libsoundio/CMakeFiles/latency.dir/src/jack.c.o: lib/libsoundio/CMakeFiles/latency.dir/flags.make
lib/libsoundio/CMakeFiles/latency.dir/src/jack.c.o: ../lib/libsoundio/src/jack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object lib/libsoundio/CMakeFiles/latency.dir/src/jack.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/latency.dir/src/jack.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/jack.c

lib/libsoundio/CMakeFiles/latency.dir/src/jack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/latency.dir/src/jack.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/jack.c > CMakeFiles/latency.dir/src/jack.c.i

lib/libsoundio/CMakeFiles/latency.dir/src/jack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/latency.dir/src/jack.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/jack.c -o CMakeFiles/latency.dir/src/jack.c.s

lib/libsoundio/CMakeFiles/latency.dir/src/pulseaudio.c.o: lib/libsoundio/CMakeFiles/latency.dir/flags.make
lib/libsoundio/CMakeFiles/latency.dir/src/pulseaudio.c.o: ../lib/libsoundio/src/pulseaudio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object lib/libsoundio/CMakeFiles/latency.dir/src/pulseaudio.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/latency.dir/src/pulseaudio.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/pulseaudio.c

lib/libsoundio/CMakeFiles/latency.dir/src/pulseaudio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/latency.dir/src/pulseaudio.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/pulseaudio.c > CMakeFiles/latency.dir/src/pulseaudio.c.i

lib/libsoundio/CMakeFiles/latency.dir/src/pulseaudio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/latency.dir/src/pulseaudio.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/pulseaudio.c -o CMakeFiles/latency.dir/src/pulseaudio.c.s

lib/libsoundio/CMakeFiles/latency.dir/src/alsa.c.o: lib/libsoundio/CMakeFiles/latency.dir/flags.make
lib/libsoundio/CMakeFiles/latency.dir/src/alsa.c.o: ../lib/libsoundio/src/alsa.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object lib/libsoundio/CMakeFiles/latency.dir/src/alsa.c.o"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/latency.dir/src/alsa.c.o   -c /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/alsa.c

lib/libsoundio/CMakeFiles/latency.dir/src/alsa.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/latency.dir/src/alsa.c.i"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/alsa.c > CMakeFiles/latency.dir/src/alsa.c.i

lib/libsoundio/CMakeFiles/latency.dir/src/alsa.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/latency.dir/src/alsa.c.s"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && /bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/OP-Pi/software/OPPi/lib/libsoundio/src/alsa.c -o CMakeFiles/latency.dir/src/alsa.c.s

# Object files for target latency
latency_OBJECTS = \
"CMakeFiles/latency.dir/test/latency.c.o" \
"CMakeFiles/latency.dir/src/soundio.c.o" \
"CMakeFiles/latency.dir/src/util.c.o" \
"CMakeFiles/latency.dir/src/os.c.o" \
"CMakeFiles/latency.dir/src/dummy.c.o" \
"CMakeFiles/latency.dir/src/channel_layout.c.o" \
"CMakeFiles/latency.dir/src/ring_buffer.c.o" \
"CMakeFiles/latency.dir/src/jack.c.o" \
"CMakeFiles/latency.dir/src/pulseaudio.c.o" \
"CMakeFiles/latency.dir/src/alsa.c.o"

# External object files for target latency
latency_EXTERNAL_OBJECTS =

lib/libsoundio/latency: lib/libsoundio/CMakeFiles/latency.dir/test/latency.c.o
lib/libsoundio/latency: lib/libsoundio/CMakeFiles/latency.dir/src/soundio.c.o
lib/libsoundio/latency: lib/libsoundio/CMakeFiles/latency.dir/src/util.c.o
lib/libsoundio/latency: lib/libsoundio/CMakeFiles/latency.dir/src/os.c.o
lib/libsoundio/latency: lib/libsoundio/CMakeFiles/latency.dir/src/dummy.c.o
lib/libsoundio/latency: lib/libsoundio/CMakeFiles/latency.dir/src/channel_layout.c.o
lib/libsoundio/latency: lib/libsoundio/CMakeFiles/latency.dir/src/ring_buffer.c.o
lib/libsoundio/latency: lib/libsoundio/CMakeFiles/latency.dir/src/jack.c.o
lib/libsoundio/latency: lib/libsoundio/CMakeFiles/latency.dir/src/pulseaudio.c.o
lib/libsoundio/latency: lib/libsoundio/CMakeFiles/latency.dir/src/alsa.c.o
lib/libsoundio/latency: lib/libsoundio/CMakeFiles/latency.dir/build.make
lib/libsoundio/latency: /usr/lib/arm-linux-gnueabihf/libjack.so
lib/libsoundio/latency: /usr/lib/arm-linux-gnueabihf/libpulse.so
lib/libsoundio/latency: /usr/lib/arm-linux-gnueabihf/libasound.so
lib/libsoundio/latency: lib/libsoundio/CMakeFiles/latency.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/OP-Pi/software/OPPi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking C executable latency"
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/latency.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/libsoundio/CMakeFiles/latency.dir/build: lib/libsoundio/latency

.PHONY : lib/libsoundio/CMakeFiles/latency.dir/build

lib/libsoundio/CMakeFiles/latency.dir/clean:
	cd /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio && $(CMAKE_COMMAND) -P CMakeFiles/latency.dir/cmake_clean.cmake
.PHONY : lib/libsoundio/CMakeFiles/latency.dir/clean

lib/libsoundio/CMakeFiles/latency.dir/depend:
	cd /home/pi/OP-Pi/software/OPPi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/OP-Pi/software/OPPi /home/pi/OP-Pi/software/OPPi/lib/libsoundio /home/pi/OP-Pi/software/OPPi/build /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio /home/pi/OP-Pi/software/OPPi/build/lib/libsoundio/CMakeFiles/latency.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/libsoundio/CMakeFiles/latency.dir/depend

