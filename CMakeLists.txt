# Definition of options "ENABLE_ASAN" and "ENABLE_LSAN" for sanitizers 
include(Sanitizers.cmake)

# Specify Minimum Required Version
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

# Specify Project and Language
project(cpp_containers LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

# Set Include Directory
include_directories(include)

# Add Executable Program
add_executable(test_sv_set app/test_sv_set.cpp)
add_executable(test_intrusive_list app/test_intrusive_list.cpp)
