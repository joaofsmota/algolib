# CMakeList.txt : CMake project for algolib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (algolib  
main.cpp 

algo/algo.h 
"algo/memory/arena_memory.h" 
algo/utils.h
algo/debug.h 

"algo/container/node.h" 
"algo/container/sbst.h" "algo/container/llist.h")

target_link_libraries(algolib user32.lib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET algolib PROPERTY CXX_STANDARD 20)
endif()

if(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")     
    add_definitions(/W4) 
endif()


# TODO: Add tests and install targets if needed.
