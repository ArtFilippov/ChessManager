# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_SOURCE_DIR = /home/user/SimpleChessTournament

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/SimpleChessTournament/build/Desktop-Debug

# Utility rule file for SimpleChessTournament_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/SimpleChessTournament_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SimpleChessTournament_autogen.dir/progress.make

CMakeFiles/SimpleChessTournament_autogen: SimpleChessTournament_autogen/timestamp

SimpleChessTournament_autogen/timestamp: /usr/lib/qt5/bin/moc
SimpleChessTournament_autogen/timestamp: /usr/lib/qt5/bin/uic
SimpleChessTournament_autogen/timestamp: CMakeFiles/SimpleChessTournament_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/user/SimpleChessTournament/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target SimpleChessTournament"
	/usr/bin/cmake -E cmake_autogen /home/user/SimpleChessTournament/build/Desktop-Debug/CMakeFiles/SimpleChessTournament_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /home/user/SimpleChessTournament/build/Desktop-Debug/SimpleChessTournament_autogen/timestamp

SimpleChessTournament_autogen: CMakeFiles/SimpleChessTournament_autogen
SimpleChessTournament_autogen: SimpleChessTournament_autogen/timestamp
SimpleChessTournament_autogen: CMakeFiles/SimpleChessTournament_autogen.dir/build.make
.PHONY : SimpleChessTournament_autogen

# Rule to build all files generated by this target.
CMakeFiles/SimpleChessTournament_autogen.dir/build: SimpleChessTournament_autogen
.PHONY : CMakeFiles/SimpleChessTournament_autogen.dir/build

CMakeFiles/SimpleChessTournament_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SimpleChessTournament_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SimpleChessTournament_autogen.dir/clean

CMakeFiles/SimpleChessTournament_autogen.dir/depend:
	cd /home/user/SimpleChessTournament/build/Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/SimpleChessTournament /home/user/SimpleChessTournament /home/user/SimpleChessTournament/build/Desktop-Debug /home/user/SimpleChessTournament/build/Desktop-Debug /home/user/SimpleChessTournament/build/Desktop-Debug/CMakeFiles/SimpleChessTournament_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/SimpleChessTournament_autogen.dir/depend

