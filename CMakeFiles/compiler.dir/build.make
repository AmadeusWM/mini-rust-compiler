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
CMAKE_COMMAND = /nix/store/yzi080r2c1zn2jzrhcfdv7dmr92yw07l-cmake-3.29.6/bin/cmake

# The command to remove a file.
RM = /nix/store/yzi080r2c1zn2jzrhcfdv7dmr92yw07l-cmake-3.29.6/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/amadeusw/university/master1/compilers/mini-rust-compiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amadeusw/university/master1/compilers/mini-rust-compiler

# Include any dependencies generated for this target.
include CMakeFiles/compiler.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/compiler.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/compiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compiler.dir/flags.make

src/parser/parser.cpp: src/parser/parser.y
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/amadeusw/university/master1/compilers/mini-rust-compiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "[BISON][MyParser] Building parser with bison 3.8.2"
	/nix/store/za1x44ayl8x3dga0ampj1prqsdnq2yxd-bison-3.8.2/bin/bison --defines=/home/amadeusw/university/master1/compilers/mini-rust-compiler/src/parser/parser.h -o /home/amadeusw/university/master1/compilers/mini-rust-compiler/src/parser/parser.cpp /home/amadeusw/university/master1/compilers/mini-rust-compiler/src/parser/parser.y

src/parser/parser.h: src/parser/parser.cpp
	@$(CMAKE_COMMAND) -E touch_nocreate src/parser/parser.h

src/lexer/lexer.cpp: src/lexer/lexer.lex
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/amadeusw/university/master1/compilers/mini-rust-compiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "[FLEX][MyLexer] Building scanner with flex 2.6.4"
	/nix/store/9z7zqgsw0lcn79rdvmak680sjzi5pyzf-flex-2.6.4/bin/flex --header-file=/home/amadeusw/university/master1/compilers/mini-rust-compiler/src/lexer/lexer.h -o/home/amadeusw/university/master1/compilers/mini-rust-compiler/src/lexer/lexer.cpp /home/amadeusw/university/master1/compilers/mini-rust-compiler/src/lexer/lexer.lex

src/lexer/lexer.h: src/lexer/lexer.cpp
	@$(CMAKE_COMMAND) -E touch_nocreate src/lexer/lexer.h

CMakeFiles/compiler.dir/src/main.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/compiler.dir/src/main.cpp.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/amadeusw/university/master1/compilers/mini-rust-compiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/compiler.dir/src/main.cpp.o"
	/nix/store/zznja5f8v3jafffyah1rk46vpfcn38dv-gcc-wrapper-13.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/main.cpp.o -MF CMakeFiles/compiler.dir/src/main.cpp.o.d -o CMakeFiles/compiler.dir/src/main.cpp.o -c /home/amadeusw/university/master1/compilers/mini-rust-compiler/src/main.cpp

CMakeFiles/compiler.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/compiler.dir/src/main.cpp.i"
	/nix/store/zznja5f8v3jafffyah1rk46vpfcn38dv-gcc-wrapper-13.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amadeusw/university/master1/compilers/mini-rust-compiler/src/main.cpp > CMakeFiles/compiler.dir/src/main.cpp.i

CMakeFiles/compiler.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/src/main.cpp.s"
	/nix/store/zznja5f8v3jafffyah1rk46vpfcn38dv-gcc-wrapper-13.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amadeusw/university/master1/compilers/mini-rust-compiler/src/main.cpp -o CMakeFiles/compiler.dir/src/main.cpp.s

CMakeFiles/compiler.dir/src/parser/parser.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/parser/parser.cpp.o: src/parser/parser.cpp
CMakeFiles/compiler.dir/src/parser/parser.cpp.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/amadeusw/university/master1/compilers/mini-rust-compiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/compiler.dir/src/parser/parser.cpp.o"
	/nix/store/zznja5f8v3jafffyah1rk46vpfcn38dv-gcc-wrapper-13.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/parser/parser.cpp.o -MF CMakeFiles/compiler.dir/src/parser/parser.cpp.o.d -o CMakeFiles/compiler.dir/src/parser/parser.cpp.o -c /home/amadeusw/university/master1/compilers/mini-rust-compiler/src/parser/parser.cpp

CMakeFiles/compiler.dir/src/parser/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/compiler.dir/src/parser/parser.cpp.i"
	/nix/store/zznja5f8v3jafffyah1rk46vpfcn38dv-gcc-wrapper-13.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amadeusw/university/master1/compilers/mini-rust-compiler/src/parser/parser.cpp > CMakeFiles/compiler.dir/src/parser/parser.cpp.i

CMakeFiles/compiler.dir/src/parser/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/src/parser/parser.cpp.s"
	/nix/store/zznja5f8v3jafffyah1rk46vpfcn38dv-gcc-wrapper-13.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amadeusw/university/master1/compilers/mini-rust-compiler/src/parser/parser.cpp -o CMakeFiles/compiler.dir/src/parser/parser.cpp.s

CMakeFiles/compiler.dir/src/lexer/lexer.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/lexer/lexer.cpp.o: src/lexer/lexer.cpp
CMakeFiles/compiler.dir/src/lexer/lexer.cpp.o: src/parser/parser.h
CMakeFiles/compiler.dir/src/lexer/lexer.cpp.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/amadeusw/university/master1/compilers/mini-rust-compiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/compiler.dir/src/lexer/lexer.cpp.o"
	/nix/store/zznja5f8v3jafffyah1rk46vpfcn38dv-gcc-wrapper-13.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/lexer/lexer.cpp.o -MF CMakeFiles/compiler.dir/src/lexer/lexer.cpp.o.d -o CMakeFiles/compiler.dir/src/lexer/lexer.cpp.o -c /home/amadeusw/university/master1/compilers/mini-rust-compiler/src/lexer/lexer.cpp

CMakeFiles/compiler.dir/src/lexer/lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/compiler.dir/src/lexer/lexer.cpp.i"
	/nix/store/zznja5f8v3jafffyah1rk46vpfcn38dv-gcc-wrapper-13.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amadeusw/university/master1/compilers/mini-rust-compiler/src/lexer/lexer.cpp > CMakeFiles/compiler.dir/src/lexer/lexer.cpp.i

CMakeFiles/compiler.dir/src/lexer/lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/src/lexer/lexer.cpp.s"
	/nix/store/zznja5f8v3jafffyah1rk46vpfcn38dv-gcc-wrapper-13.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amadeusw/university/master1/compilers/mini-rust-compiler/src/lexer/lexer.cpp -o CMakeFiles/compiler.dir/src/lexer/lexer.cpp.s

# Object files for target compiler
compiler_OBJECTS = \
"CMakeFiles/compiler.dir/src/main.cpp.o" \
"CMakeFiles/compiler.dir/src/parser/parser.cpp.o" \
"CMakeFiles/compiler.dir/src/lexer/lexer.cpp.o"

# External object files for target compiler
compiler_EXTERNAL_OBJECTS =

compiler: CMakeFiles/compiler.dir/src/main.cpp.o
compiler: CMakeFiles/compiler.dir/src/parser/parser.cpp.o
compiler: CMakeFiles/compiler.dir/src/lexer/lexer.cpp.o
compiler: CMakeFiles/compiler.dir/build.make
compiler: /nix/store/9z7zqgsw0lcn79rdvmak680sjzi5pyzf-flex-2.6.4/lib/libfl.so
compiler: CMakeFiles/compiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/amadeusw/university/master1/compilers/mini-rust-compiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable compiler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compiler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compiler.dir/build: compiler
.PHONY : CMakeFiles/compiler.dir/build

CMakeFiles/compiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compiler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compiler.dir/clean

CMakeFiles/compiler.dir/depend: src/lexer/lexer.cpp
CMakeFiles/compiler.dir/depend: src/lexer/lexer.h
CMakeFiles/compiler.dir/depend: src/parser/parser.cpp
CMakeFiles/compiler.dir/depend: src/parser/parser.h
	cd /home/amadeusw/university/master1/compilers/mini-rust-compiler && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amadeusw/university/master1/compilers/mini-rust-compiler /home/amadeusw/university/master1/compilers/mini-rust-compiler /home/amadeusw/university/master1/compilers/mini-rust-compiler /home/amadeusw/university/master1/compilers/mini-rust-compiler /home/amadeusw/university/master1/compilers/mini-rust-compiler/CMakeFiles/compiler.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/compiler.dir/depend

