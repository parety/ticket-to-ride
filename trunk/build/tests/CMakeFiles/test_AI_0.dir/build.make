# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_AI_0.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_AI_0.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_AI_0.dir/flags.make

tests/CMakeFiles/test_AI_0.dir/test_AI_0.c.o: tests/CMakeFiles/test_AI_0.dir/flags.make
tests/CMakeFiles/test_AI_0.dir/test_AI_0.c.o: ../tests/test_AI_0.c
	$(CMAKE_COMMAND) -E cmake_progress_report /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object tests/CMakeFiles/test_AI_0.dir/test_AI_0.c.o"
	cd /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test_AI_0.dir/test_AI_0.c.o   -c /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/tests/test_AI_0.c

tests/CMakeFiles/test_AI_0.dir/test_AI_0.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_AI_0.dir/test_AI_0.c.i"
	cd /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/tests/test_AI_0.c > CMakeFiles/test_AI_0.dir/test_AI_0.c.i

tests/CMakeFiles/test_AI_0.dir/test_AI_0.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_AI_0.dir/test_AI_0.c.s"
	cd /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/tests/test_AI_0.c -o CMakeFiles/test_AI_0.dir/test_AI_0.c.s

tests/CMakeFiles/test_AI_0.dir/test_AI_0.c.o.requires:
.PHONY : tests/CMakeFiles/test_AI_0.dir/test_AI_0.c.o.requires

tests/CMakeFiles/test_AI_0.dir/test_AI_0.c.o.provides: tests/CMakeFiles/test_AI_0.dir/test_AI_0.c.o.requires
	$(MAKE) -f tests/CMakeFiles/test_AI_0.dir/build.make tests/CMakeFiles/test_AI_0.dir/test_AI_0.c.o.provides.build
.PHONY : tests/CMakeFiles/test_AI_0.dir/test_AI_0.c.o.provides

tests/CMakeFiles/test_AI_0.dir/test_AI_0.c.o.provides.build: tests/CMakeFiles/test_AI_0.dir/test_AI_0.c.o

# Object files for target test_AI_0
test_AI_0_OBJECTS = \
"CMakeFiles/test_AI_0.dir/test_AI_0.c.o"

# External object files for target test_AI_0
test_AI_0_EXTERNAL_OBJECTS =

tests/test_AI_0: tests/CMakeFiles/test_AI_0.dir/test_AI_0.c.o
tests/test_AI_0: tests/CMakeFiles/test_AI_0.dir/build.make
tests/test_AI_0: src/liblink.a
tests/test_AI_0: src/libcards.a
tests/test_AI_0: src/libplay.a
tests/test_AI_0: tests/CMakeFiles/test_AI_0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable test_AI_0"
	cd /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_AI_0.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_AI_0.dir/build: tests/test_AI_0
.PHONY : tests/CMakeFiles/test_AI_0.dir/build

tests/CMakeFiles/test_AI_0.dir/requires: tests/CMakeFiles/test_AI_0.dir/test_AI_0.c.o.requires
.PHONY : tests/CMakeFiles/test_AI_0.dir/requires

tests/CMakeFiles/test_AI_0.dir/clean:
	cd /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_AI_0.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_AI_0.dir/clean

tests/CMakeFiles/test_AI_0.dir/depend:
	cd /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/tests /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/tests /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/tests/CMakeFiles/test_AI_0.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_AI_0.dir/depend

