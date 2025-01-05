cmake_minimum_required(VERSION 3.29.2)
project( THorror )

#include_directories( lib/ )
include_directories( src/lib/ )
add_executable( main src/main.cpp )
target_link_libraries(main raylib)