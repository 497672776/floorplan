# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dec/Code/Final_4/FloorPlan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dec/Code/Final_4/FloorPlan/build

# Include any dependencies generated for this target.
include CMakeFiles/solution.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/solution.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/solution.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/solution.dir/flags.make

CMakeFiles/solution.dir/src/bstartree.cpp.o: CMakeFiles/solution.dir/flags.make
CMakeFiles/solution.dir/src/bstartree.cpp.o: ../src/bstartree.cpp
CMakeFiles/solution.dir/src/bstartree.cpp.o: CMakeFiles/solution.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dec/Code/Final_4/FloorPlan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/solution.dir/src/bstartree.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/solution.dir/src/bstartree.cpp.o -MF CMakeFiles/solution.dir/src/bstartree.cpp.o.d -o CMakeFiles/solution.dir/src/bstartree.cpp.o -c /home/dec/Code/Final_4/FloorPlan/src/bstartree.cpp

CMakeFiles/solution.dir/src/bstartree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/src/bstartree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dec/Code/Final_4/FloorPlan/src/bstartree.cpp > CMakeFiles/solution.dir/src/bstartree.cpp.i

CMakeFiles/solution.dir/src/bstartree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/src/bstartree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dec/Code/Final_4/FloorPlan/src/bstartree.cpp -o CMakeFiles/solution.dir/src/bstartree.cpp.s

CMakeFiles/solution.dir/src/common.cpp.o: CMakeFiles/solution.dir/flags.make
CMakeFiles/solution.dir/src/common.cpp.o: ../src/common.cpp
CMakeFiles/solution.dir/src/common.cpp.o: CMakeFiles/solution.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dec/Code/Final_4/FloorPlan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/solution.dir/src/common.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/solution.dir/src/common.cpp.o -MF CMakeFiles/solution.dir/src/common.cpp.o.d -o CMakeFiles/solution.dir/src/common.cpp.o -c /home/dec/Code/Final_4/FloorPlan/src/common.cpp

CMakeFiles/solution.dir/src/common.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/src/common.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dec/Code/Final_4/FloorPlan/src/common.cpp > CMakeFiles/solution.dir/src/common.cpp.i

CMakeFiles/solution.dir/src/common.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/src/common.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dec/Code/Final_4/FloorPlan/src/common.cpp -o CMakeFiles/solution.dir/src/common.cpp.s

CMakeFiles/solution.dir/src/fileparser.cpp.o: CMakeFiles/solution.dir/flags.make
CMakeFiles/solution.dir/src/fileparser.cpp.o: ../src/fileparser.cpp
CMakeFiles/solution.dir/src/fileparser.cpp.o: CMakeFiles/solution.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dec/Code/Final_4/FloorPlan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/solution.dir/src/fileparser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/solution.dir/src/fileparser.cpp.o -MF CMakeFiles/solution.dir/src/fileparser.cpp.o.d -o CMakeFiles/solution.dir/src/fileparser.cpp.o -c /home/dec/Code/Final_4/FloorPlan/src/fileparser.cpp

CMakeFiles/solution.dir/src/fileparser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/src/fileparser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dec/Code/Final_4/FloorPlan/src/fileparser.cpp > CMakeFiles/solution.dir/src/fileparser.cpp.i

CMakeFiles/solution.dir/src/fileparser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/src/fileparser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dec/Code/Final_4/FloorPlan/src/fileparser.cpp -o CMakeFiles/solution.dir/src/fileparser.cpp.s

CMakeFiles/solution.dir/src/floorplaner.cpp.o: CMakeFiles/solution.dir/flags.make
CMakeFiles/solution.dir/src/floorplaner.cpp.o: ../src/floorplaner.cpp
CMakeFiles/solution.dir/src/floorplaner.cpp.o: CMakeFiles/solution.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dec/Code/Final_4/FloorPlan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/solution.dir/src/floorplaner.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/solution.dir/src/floorplaner.cpp.o -MF CMakeFiles/solution.dir/src/floorplaner.cpp.o.d -o CMakeFiles/solution.dir/src/floorplaner.cpp.o -c /home/dec/Code/Final_4/FloorPlan/src/floorplaner.cpp

CMakeFiles/solution.dir/src/floorplaner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/src/floorplaner.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dec/Code/Final_4/FloorPlan/src/floorplaner.cpp > CMakeFiles/solution.dir/src/floorplaner.cpp.i

CMakeFiles/solution.dir/src/floorplaner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/src/floorplaner.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dec/Code/Final_4/FloorPlan/src/floorplaner.cpp -o CMakeFiles/solution.dir/src/floorplaner.cpp.s

CMakeFiles/solution.dir/src/main.cpp.o: CMakeFiles/solution.dir/flags.make
CMakeFiles/solution.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/solution.dir/src/main.cpp.o: CMakeFiles/solution.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dec/Code/Final_4/FloorPlan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/solution.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/solution.dir/src/main.cpp.o -MF CMakeFiles/solution.dir/src/main.cpp.o.d -o CMakeFiles/solution.dir/src/main.cpp.o -c /home/dec/Code/Final_4/FloorPlan/src/main.cpp

CMakeFiles/solution.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dec/Code/Final_4/FloorPlan/src/main.cpp > CMakeFiles/solution.dir/src/main.cpp.i

CMakeFiles/solution.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dec/Code/Final_4/FloorPlan/src/main.cpp -o CMakeFiles/solution.dir/src/main.cpp.s

CMakeFiles/solution.dir/src/polish.cpp.o: CMakeFiles/solution.dir/flags.make
CMakeFiles/solution.dir/src/polish.cpp.o: ../src/polish.cpp
CMakeFiles/solution.dir/src/polish.cpp.o: CMakeFiles/solution.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dec/Code/Final_4/FloorPlan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/solution.dir/src/polish.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/solution.dir/src/polish.cpp.o -MF CMakeFiles/solution.dir/src/polish.cpp.o.d -o CMakeFiles/solution.dir/src/polish.cpp.o -c /home/dec/Code/Final_4/FloorPlan/src/polish.cpp

CMakeFiles/solution.dir/src/polish.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/src/polish.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dec/Code/Final_4/FloorPlan/src/polish.cpp > CMakeFiles/solution.dir/src/polish.cpp.i

CMakeFiles/solution.dir/src/polish.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/src/polish.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dec/Code/Final_4/FloorPlan/src/polish.cpp -o CMakeFiles/solution.dir/src/polish.cpp.s

CMakeFiles/solution.dir/src/sequencepair.cpp.o: CMakeFiles/solution.dir/flags.make
CMakeFiles/solution.dir/src/sequencepair.cpp.o: ../src/sequencepair.cpp
CMakeFiles/solution.dir/src/sequencepair.cpp.o: CMakeFiles/solution.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dec/Code/Final_4/FloorPlan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/solution.dir/src/sequencepair.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/solution.dir/src/sequencepair.cpp.o -MF CMakeFiles/solution.dir/src/sequencepair.cpp.o.d -o CMakeFiles/solution.dir/src/sequencepair.cpp.o -c /home/dec/Code/Final_4/FloorPlan/src/sequencepair.cpp

CMakeFiles/solution.dir/src/sequencepair.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/src/sequencepair.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dec/Code/Final_4/FloorPlan/src/sequencepair.cpp > CMakeFiles/solution.dir/src/sequencepair.cpp.i

CMakeFiles/solution.dir/src/sequencepair.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/src/sequencepair.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dec/Code/Final_4/FloorPlan/src/sequencepair.cpp -o CMakeFiles/solution.dir/src/sequencepair.cpp.s

CMakeFiles/solution.dir/src/size.cpp.o: CMakeFiles/solution.dir/flags.make
CMakeFiles/solution.dir/src/size.cpp.o: ../src/size.cpp
CMakeFiles/solution.dir/src/size.cpp.o: CMakeFiles/solution.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dec/Code/Final_4/FloorPlan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/solution.dir/src/size.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/solution.dir/src/size.cpp.o -MF CMakeFiles/solution.dir/src/size.cpp.o.d -o CMakeFiles/solution.dir/src/size.cpp.o -c /home/dec/Code/Final_4/FloorPlan/src/size.cpp

CMakeFiles/solution.dir/src/size.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/src/size.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dec/Code/Final_4/FloorPlan/src/size.cpp > CMakeFiles/solution.dir/src/size.cpp.i

CMakeFiles/solution.dir/src/size.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/src/size.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dec/Code/Final_4/FloorPlan/src/size.cpp -o CMakeFiles/solution.dir/src/size.cpp.s

CMakeFiles/solution.dir/src/slicingnode.cpp.o: CMakeFiles/solution.dir/flags.make
CMakeFiles/solution.dir/src/slicingnode.cpp.o: ../src/slicingnode.cpp
CMakeFiles/solution.dir/src/slicingnode.cpp.o: CMakeFiles/solution.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dec/Code/Final_4/FloorPlan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/solution.dir/src/slicingnode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/solution.dir/src/slicingnode.cpp.o -MF CMakeFiles/solution.dir/src/slicingnode.cpp.o.d -o CMakeFiles/solution.dir/src/slicingnode.cpp.o -c /home/dec/Code/Final_4/FloorPlan/src/slicingnode.cpp

CMakeFiles/solution.dir/src/slicingnode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/src/slicingnode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dec/Code/Final_4/FloorPlan/src/slicingnode.cpp > CMakeFiles/solution.dir/src/slicingnode.cpp.i

CMakeFiles/solution.dir/src/slicingnode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/src/slicingnode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dec/Code/Final_4/FloorPlan/src/slicingnode.cpp -o CMakeFiles/solution.dir/src/slicingnode.cpp.s

CMakeFiles/solution.dir/src/slicingtree.cpp.o: CMakeFiles/solution.dir/flags.make
CMakeFiles/solution.dir/src/slicingtree.cpp.o: ../src/slicingtree.cpp
CMakeFiles/solution.dir/src/slicingtree.cpp.o: CMakeFiles/solution.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dec/Code/Final_4/FloorPlan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/solution.dir/src/slicingtree.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/solution.dir/src/slicingtree.cpp.o -MF CMakeFiles/solution.dir/src/slicingtree.cpp.o.d -o CMakeFiles/solution.dir/src/slicingtree.cpp.o -c /home/dec/Code/Final_4/FloorPlan/src/slicingtree.cpp

CMakeFiles/solution.dir/src/slicingtree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/src/slicingtree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dec/Code/Final_4/FloorPlan/src/slicingtree.cpp > CMakeFiles/solution.dir/src/slicingtree.cpp.i

CMakeFiles/solution.dir/src/slicingtree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/src/slicingtree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dec/Code/Final_4/FloorPlan/src/slicingtree.cpp -o CMakeFiles/solution.dir/src/slicingtree.cpp.s

# Object files for target solution
solution_OBJECTS = \
"CMakeFiles/solution.dir/src/bstartree.cpp.o" \
"CMakeFiles/solution.dir/src/common.cpp.o" \
"CMakeFiles/solution.dir/src/fileparser.cpp.o" \
"CMakeFiles/solution.dir/src/floorplaner.cpp.o" \
"CMakeFiles/solution.dir/src/main.cpp.o" \
"CMakeFiles/solution.dir/src/polish.cpp.o" \
"CMakeFiles/solution.dir/src/sequencepair.cpp.o" \
"CMakeFiles/solution.dir/src/size.cpp.o" \
"CMakeFiles/solution.dir/src/slicingnode.cpp.o" \
"CMakeFiles/solution.dir/src/slicingtree.cpp.o"

# External object files for target solution
solution_EXTERNAL_OBJECTS =

solution: CMakeFiles/solution.dir/src/bstartree.cpp.o
solution: CMakeFiles/solution.dir/src/common.cpp.o
solution: CMakeFiles/solution.dir/src/fileparser.cpp.o
solution: CMakeFiles/solution.dir/src/floorplaner.cpp.o
solution: CMakeFiles/solution.dir/src/main.cpp.o
solution: CMakeFiles/solution.dir/src/polish.cpp.o
solution: CMakeFiles/solution.dir/src/sequencepair.cpp.o
solution: CMakeFiles/solution.dir/src/size.cpp.o
solution: CMakeFiles/solution.dir/src/slicingnode.cpp.o
solution: CMakeFiles/solution.dir/src/slicingtree.cpp.o
solution: CMakeFiles/solution.dir/build.make
solution: CMakeFiles/solution.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dec/Code/Final_4/FloorPlan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable solution"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/solution.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/solution.dir/build: solution
.PHONY : CMakeFiles/solution.dir/build

CMakeFiles/solution.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/solution.dir/cmake_clean.cmake
.PHONY : CMakeFiles/solution.dir/clean

CMakeFiles/solution.dir/depend:
	cd /home/dec/Code/Final_4/FloorPlan/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dec/Code/Final_4/FloorPlan /home/dec/Code/Final_4/FloorPlan /home/dec/Code/Final_4/FloorPlan/build /home/dec/Code/Final_4/FloorPlan/build /home/dec/Code/Final_4/FloorPlan/build/CMakeFiles/solution.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/solution.dir/depend

