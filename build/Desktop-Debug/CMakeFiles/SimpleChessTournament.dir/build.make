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

# Include any dependencies generated for this target.
include CMakeFiles/SimpleChessTournament.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SimpleChessTournament.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SimpleChessTournament.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SimpleChessTournament.dir/flags.make

SimpleChessTournament_autogen/timestamp: /usr/lib/qt5/bin/moc
SimpleChessTournament_autogen/timestamp: /usr/lib/qt5/bin/uic
SimpleChessTournament_autogen/timestamp: CMakeFiles/SimpleChessTournament.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/user/SimpleChessTournament/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target SimpleChessTournament"
	/usr/bin/cmake -E cmake_autogen /home/user/SimpleChessTournament/build/Desktop-Debug/CMakeFiles/SimpleChessTournament_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /home/user/SimpleChessTournament/build/Desktop-Debug/SimpleChessTournament_autogen/timestamp

CMakeFiles/SimpleChessTournament.dir/SimpleChessTournament_autogen/mocs_compilation.cpp.o: CMakeFiles/SimpleChessTournament.dir/flags.make
CMakeFiles/SimpleChessTournament.dir/SimpleChessTournament_autogen/mocs_compilation.cpp.o: SimpleChessTournament_autogen/mocs_compilation.cpp
CMakeFiles/SimpleChessTournament.dir/SimpleChessTournament_autogen/mocs_compilation.cpp.o: CMakeFiles/SimpleChessTournament.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/SimpleChessTournament/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SimpleChessTournament.dir/SimpleChessTournament_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SimpleChessTournament.dir/SimpleChessTournament_autogen/mocs_compilation.cpp.o -MF CMakeFiles/SimpleChessTournament.dir/SimpleChessTournament_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/SimpleChessTournament.dir/SimpleChessTournament_autogen/mocs_compilation.cpp.o -c /home/user/SimpleChessTournament/build/Desktop-Debug/SimpleChessTournament_autogen/mocs_compilation.cpp

CMakeFiles/SimpleChessTournament.dir/SimpleChessTournament_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SimpleChessTournament.dir/SimpleChessTournament_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/SimpleChessTournament/build/Desktop-Debug/SimpleChessTournament_autogen/mocs_compilation.cpp > CMakeFiles/SimpleChessTournament.dir/SimpleChessTournament_autogen/mocs_compilation.cpp.i

CMakeFiles/SimpleChessTournament.dir/SimpleChessTournament_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SimpleChessTournament.dir/SimpleChessTournament_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/SimpleChessTournament/build/Desktop-Debug/SimpleChessTournament_autogen/mocs_compilation.cpp -o CMakeFiles/SimpleChessTournament.dir/SimpleChessTournament_autogen/mocs_compilation.cpp.s

CMakeFiles/SimpleChessTournament.dir/main.cpp.o: CMakeFiles/SimpleChessTournament.dir/flags.make
CMakeFiles/SimpleChessTournament.dir/main.cpp.o: /home/user/SimpleChessTournament/main.cpp
CMakeFiles/SimpleChessTournament.dir/main.cpp.o: CMakeFiles/SimpleChessTournament.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/SimpleChessTournament/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SimpleChessTournament.dir/main.cpp.o"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SimpleChessTournament.dir/main.cpp.o -MF CMakeFiles/SimpleChessTournament.dir/main.cpp.o.d -o CMakeFiles/SimpleChessTournament.dir/main.cpp.o -c /home/user/SimpleChessTournament/main.cpp

CMakeFiles/SimpleChessTournament.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SimpleChessTournament.dir/main.cpp.i"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/SimpleChessTournament/main.cpp > CMakeFiles/SimpleChessTournament.dir/main.cpp.i

CMakeFiles/SimpleChessTournament.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SimpleChessTournament.dir/main.cpp.s"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/SimpleChessTournament/main.cpp -o CMakeFiles/SimpleChessTournament.dir/main.cpp.s

CMakeFiles/SimpleChessTournament.dir/mainwindow.cpp.o: CMakeFiles/SimpleChessTournament.dir/flags.make
CMakeFiles/SimpleChessTournament.dir/mainwindow.cpp.o: /home/user/SimpleChessTournament/mainwindow.cpp
CMakeFiles/SimpleChessTournament.dir/mainwindow.cpp.o: CMakeFiles/SimpleChessTournament.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/SimpleChessTournament/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SimpleChessTournament.dir/mainwindow.cpp.o"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SimpleChessTournament.dir/mainwindow.cpp.o -MF CMakeFiles/SimpleChessTournament.dir/mainwindow.cpp.o.d -o CMakeFiles/SimpleChessTournament.dir/mainwindow.cpp.o -c /home/user/SimpleChessTournament/mainwindow.cpp

CMakeFiles/SimpleChessTournament.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SimpleChessTournament.dir/mainwindow.cpp.i"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/SimpleChessTournament/mainwindow.cpp > CMakeFiles/SimpleChessTournament.dir/mainwindow.cpp.i

CMakeFiles/SimpleChessTournament.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SimpleChessTournament.dir/mainwindow.cpp.s"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/SimpleChessTournament/mainwindow.cpp -o CMakeFiles/SimpleChessTournament.dir/mainwindow.cpp.s

CMakeFiles/SimpleChessTournament.dir/player.cpp.o: CMakeFiles/SimpleChessTournament.dir/flags.make
CMakeFiles/SimpleChessTournament.dir/player.cpp.o: /home/user/SimpleChessTournament/player.cpp
CMakeFiles/SimpleChessTournament.dir/player.cpp.o: CMakeFiles/SimpleChessTournament.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/SimpleChessTournament/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/SimpleChessTournament.dir/player.cpp.o"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SimpleChessTournament.dir/player.cpp.o -MF CMakeFiles/SimpleChessTournament.dir/player.cpp.o.d -o CMakeFiles/SimpleChessTournament.dir/player.cpp.o -c /home/user/SimpleChessTournament/player.cpp

CMakeFiles/SimpleChessTournament.dir/player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SimpleChessTournament.dir/player.cpp.i"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/SimpleChessTournament/player.cpp > CMakeFiles/SimpleChessTournament.dir/player.cpp.i

CMakeFiles/SimpleChessTournament.dir/player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SimpleChessTournament.dir/player.cpp.s"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/SimpleChessTournament/player.cpp -o CMakeFiles/SimpleChessTournament.dir/player.cpp.s

CMakeFiles/SimpleChessTournament.dir/chesstournament.cpp.o: CMakeFiles/SimpleChessTournament.dir/flags.make
CMakeFiles/SimpleChessTournament.dir/chesstournament.cpp.o: /home/user/SimpleChessTournament/chesstournament.cpp
CMakeFiles/SimpleChessTournament.dir/chesstournament.cpp.o: CMakeFiles/SimpleChessTournament.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/SimpleChessTournament/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/SimpleChessTournament.dir/chesstournament.cpp.o"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SimpleChessTournament.dir/chesstournament.cpp.o -MF CMakeFiles/SimpleChessTournament.dir/chesstournament.cpp.o.d -o CMakeFiles/SimpleChessTournament.dir/chesstournament.cpp.o -c /home/user/SimpleChessTournament/chesstournament.cpp

CMakeFiles/SimpleChessTournament.dir/chesstournament.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SimpleChessTournament.dir/chesstournament.cpp.i"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/SimpleChessTournament/chesstournament.cpp > CMakeFiles/SimpleChessTournament.dir/chesstournament.cpp.i

CMakeFiles/SimpleChessTournament.dir/chesstournament.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SimpleChessTournament.dir/chesstournament.cpp.s"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/SimpleChessTournament/chesstournament.cpp -o CMakeFiles/SimpleChessTournament.dir/chesstournament.cpp.s

CMakeFiles/SimpleChessTournament.dir/view.cpp.o: CMakeFiles/SimpleChessTournament.dir/flags.make
CMakeFiles/SimpleChessTournament.dir/view.cpp.o: /home/user/SimpleChessTournament/view.cpp
CMakeFiles/SimpleChessTournament.dir/view.cpp.o: CMakeFiles/SimpleChessTournament.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/SimpleChessTournament/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/SimpleChessTournament.dir/view.cpp.o"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SimpleChessTournament.dir/view.cpp.o -MF CMakeFiles/SimpleChessTournament.dir/view.cpp.o.d -o CMakeFiles/SimpleChessTournament.dir/view.cpp.o -c /home/user/SimpleChessTournament/view.cpp

CMakeFiles/SimpleChessTournament.dir/view.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SimpleChessTournament.dir/view.cpp.i"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/SimpleChessTournament/view.cpp > CMakeFiles/SimpleChessTournament.dir/view.cpp.i

CMakeFiles/SimpleChessTournament.dir/view.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SimpleChessTournament.dir/view.cpp.s"
	/usr/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/SimpleChessTournament/view.cpp -o CMakeFiles/SimpleChessTournament.dir/view.cpp.s

# Object files for target SimpleChessTournament
SimpleChessTournament_OBJECTS = \
"CMakeFiles/SimpleChessTournament.dir/SimpleChessTournament_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/SimpleChessTournament.dir/main.cpp.o" \
"CMakeFiles/SimpleChessTournament.dir/mainwindow.cpp.o" \
"CMakeFiles/SimpleChessTournament.dir/player.cpp.o" \
"CMakeFiles/SimpleChessTournament.dir/chesstournament.cpp.o" \
"CMakeFiles/SimpleChessTournament.dir/view.cpp.o"

# External object files for target SimpleChessTournament
SimpleChessTournament_EXTERNAL_OBJECTS =

SimpleChessTournament: CMakeFiles/SimpleChessTournament.dir/SimpleChessTournament_autogen/mocs_compilation.cpp.o
SimpleChessTournament: CMakeFiles/SimpleChessTournament.dir/main.cpp.o
SimpleChessTournament: CMakeFiles/SimpleChessTournament.dir/mainwindow.cpp.o
SimpleChessTournament: CMakeFiles/SimpleChessTournament.dir/player.cpp.o
SimpleChessTournament: CMakeFiles/SimpleChessTournament.dir/chesstournament.cpp.o
SimpleChessTournament: CMakeFiles/SimpleChessTournament.dir/view.cpp.o
SimpleChessTournament: CMakeFiles/SimpleChessTournament.dir/build.make
SimpleChessTournament: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.13
SimpleChessTournament: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.13
SimpleChessTournament: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.13
SimpleChessTournament: CMakeFiles/SimpleChessTournament.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/user/SimpleChessTournament/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable SimpleChessTournament"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SimpleChessTournament.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SimpleChessTournament.dir/build: SimpleChessTournament
.PHONY : CMakeFiles/SimpleChessTournament.dir/build

CMakeFiles/SimpleChessTournament.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SimpleChessTournament.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SimpleChessTournament.dir/clean

CMakeFiles/SimpleChessTournament.dir/depend: SimpleChessTournament_autogen/timestamp
	cd /home/user/SimpleChessTournament/build/Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/SimpleChessTournament /home/user/SimpleChessTournament /home/user/SimpleChessTournament/build/Desktop-Debug /home/user/SimpleChessTournament/build/Desktop-Debug /home/user/SimpleChessTournament/build/Desktop-Debug/CMakeFiles/SimpleChessTournament.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/SimpleChessTournament.dir/depend

