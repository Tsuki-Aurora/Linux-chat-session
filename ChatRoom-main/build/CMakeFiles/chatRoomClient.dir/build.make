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
CMAKE_SOURCE_DIR = /home/ddb/文档/Linux课程设计/客户端/ChatRoom-main

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ddb/文档/Linux课程设计/客户端/ChatRoom-main/build

# Include any dependencies generated for this target.
include CMakeFiles/chatRoomClient.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/chatRoomClient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chatRoomClient.dir/flags.make

CMakeFiles/chatRoomClient.dir/src/chatRoomClient.cpp.o: CMakeFiles/chatRoomClient.dir/flags.make
CMakeFiles/chatRoomClient.dir/src/chatRoomClient.cpp.o: ../src/chatRoomClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ddb/文档/Linux课程设计/客户端/ChatRoom-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/chatRoomClient.dir/src/chatRoomClient.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chatRoomClient.dir/src/chatRoomClient.cpp.o -c /home/ddb/文档/Linux课程设计/客户端/ChatRoom-main/src/chatRoomClient.cpp

CMakeFiles/chatRoomClient.dir/src/chatRoomClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chatRoomClient.dir/src/chatRoomClient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ddb/文档/Linux课程设计/客户端/ChatRoom-main/src/chatRoomClient.cpp > CMakeFiles/chatRoomClient.dir/src/chatRoomClient.cpp.i

CMakeFiles/chatRoomClient.dir/src/chatRoomClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chatRoomClient.dir/src/chatRoomClient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ddb/文档/Linux课程设计/客户端/ChatRoom-main/src/chatRoomClient.cpp -o CMakeFiles/chatRoomClient.dir/src/chatRoomClient.cpp.s

# Object files for target chatRoomClient
chatRoomClient_OBJECTS = \
"CMakeFiles/chatRoomClient.dir/src/chatRoomClient.cpp.o"

# External object files for target chatRoomClient
chatRoomClient_EXTERNAL_OBJECTS =

chatRoomClient: CMakeFiles/chatRoomClient.dir/src/chatRoomClient.cpp.o
chatRoomClient: CMakeFiles/chatRoomClient.dir/build.make
chatRoomClient: libcppNetWork.so
chatRoomClient: CMakeFiles/chatRoomClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ddb/文档/Linux课程设计/客户端/ChatRoom-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable chatRoomClient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chatRoomClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chatRoomClient.dir/build: chatRoomClient

.PHONY : CMakeFiles/chatRoomClient.dir/build

CMakeFiles/chatRoomClient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/chatRoomClient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/chatRoomClient.dir/clean

CMakeFiles/chatRoomClient.dir/depend:
	cd /home/ddb/文档/Linux课程设计/客户端/ChatRoom-main/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ddb/文档/Linux课程设计/客户端/ChatRoom-main /home/ddb/文档/Linux课程设计/客户端/ChatRoom-main /home/ddb/文档/Linux课程设计/客户端/ChatRoom-main/build /home/ddb/文档/Linux课程设计/客户端/ChatRoom-main/build /home/ddb/文档/Linux课程设计/客户端/ChatRoom-main/build/CMakeFiles/chatRoomClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/chatRoomClient.dir/depend
