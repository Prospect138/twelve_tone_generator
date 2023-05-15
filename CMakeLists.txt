cmake_minimum_required(VERSION 3.0.0)
project(12tone VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(12tone midi_track.cpp sequence_generator.cpp main.cpp)

set_target_properties(12tone PROPERTIES
CXX_STANDARD 17 
CXX_STANDARD_REQUIRED ON)
