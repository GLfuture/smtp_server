# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/gong/projects/Smtp_Server/smtp_proxy_server/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gong/projects/Smtp_Server/smtp_proxy_server/src/build

# Include any dependencies generated for this target.
include Base64/CMakeFiles/base64.dir/depend.make

# Include the progress variables for this target.
include Base64/CMakeFiles/base64.dir/progress.make

# Include the compile flags for this target's objects.
include Base64/CMakeFiles/base64.dir/flags.make

Base64/CMakeFiles/base64.dir/base64.cc.o: Base64/CMakeFiles/base64.dir/flags.make
Base64/CMakeFiles/base64.dir/base64.cc.o: ../Base64/base64.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/projects/Smtp_Server/smtp_proxy_server/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Base64/CMakeFiles/base64.dir/base64.cc.o"
	cd /home/gong/projects/Smtp_Server/smtp_proxy_server/src/build/Base64 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base64.dir/base64.cc.o -c /home/gong/projects/Smtp_Server/smtp_proxy_server/src/Base64/base64.cc

Base64/CMakeFiles/base64.dir/base64.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base64.dir/base64.cc.i"
	cd /home/gong/projects/Smtp_Server/smtp_proxy_server/src/build/Base64 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/projects/Smtp_Server/smtp_proxy_server/src/Base64/base64.cc > CMakeFiles/base64.dir/base64.cc.i

Base64/CMakeFiles/base64.dir/base64.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base64.dir/base64.cc.s"
	cd /home/gong/projects/Smtp_Server/smtp_proxy_server/src/build/Base64 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/projects/Smtp_Server/smtp_proxy_server/src/Base64/base64.cc -o CMakeFiles/base64.dir/base64.cc.s

# Object files for target base64
base64_OBJECTS = \
"CMakeFiles/base64.dir/base64.cc.o"

# External object files for target base64
base64_EXTERNAL_OBJECTS =

/home/gong/projects/Smtp_Server/smtp_proxy_server/lib/libbase64.so: Base64/CMakeFiles/base64.dir/base64.cc.o
/home/gong/projects/Smtp_Server/smtp_proxy_server/lib/libbase64.so: Base64/CMakeFiles/base64.dir/build.make
/home/gong/projects/Smtp_Server/smtp_proxy_server/lib/libbase64.so: Base64/CMakeFiles/base64.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gong/projects/Smtp_Server/smtp_proxy_server/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library /home/gong/projects/Smtp_Server/smtp_proxy_server/lib/libbase64.so"
	cd /home/gong/projects/Smtp_Server/smtp_proxy_server/src/build/Base64 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/base64.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Base64/CMakeFiles/base64.dir/build: /home/gong/projects/Smtp_Server/smtp_proxy_server/lib/libbase64.so

.PHONY : Base64/CMakeFiles/base64.dir/build

Base64/CMakeFiles/base64.dir/clean:
	cd /home/gong/projects/Smtp_Server/smtp_proxy_server/src/build/Base64 && $(CMAKE_COMMAND) -P CMakeFiles/base64.dir/cmake_clean.cmake
.PHONY : Base64/CMakeFiles/base64.dir/clean

Base64/CMakeFiles/base64.dir/depend:
	cd /home/gong/projects/Smtp_Server/smtp_proxy_server/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gong/projects/Smtp_Server/smtp_proxy_server/src /home/gong/projects/Smtp_Server/smtp_proxy_server/src/Base64 /home/gong/projects/Smtp_Server/smtp_proxy_server/src/build /home/gong/projects/Smtp_Server/smtp_proxy_server/src/build/Base64 /home/gong/projects/Smtp_Server/smtp_proxy_server/src/build/Base64/CMakeFiles/base64.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Base64/CMakeFiles/base64.dir/depend

