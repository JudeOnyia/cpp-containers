cmake_minimum_required(VERSION 3.10)

project(containers LANGUAGES CXX)

option(ENABLE_EXTRAS "enable extras" false)
#option(ENABLE_COVERAGE "Enable coverage" false)

include(Sanitizers.cmake)

set(CMAKE_VERBOSE_MAKEFILE true)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

#if (ENABLE_COVERAGE)
#	SET(CMAKE_CXX_FLAGS "-g -DNDEBUG -fno-inline -O0 -coverage")
#	include(CodeCoverage.cmake)
#endif()

if (CMAKE_CXX_COMPILER_ID MATCHES GNU OR
  CMAKE_CXX_COMPILER_ID MATCHES Clang)
	add_compile_options("-pedantic-errors")
endif()

find_package(Catch2 REQUIRED)

include_directories(include)

if(EXISTS ${CMAKE_SOURCE_DIR}/include/ra/sv_set.hpp)
	set(SET_FOUND 1)
else()
	set(SET_FOUND 0)
endif()
if(EXISTS ${CMAKE_SOURCE_DIR}/include/ra/intrusive_list.hpp)
	set(LIST_FOUND 1)
else()
	set(LIST_FOUND 0)
endif()

add_library(ra INTERFACE)
target_include_directories(ra INTERFACE include)
if(SET_FOUND)
	add_executable(test_sv_set app/test_sv_set.cpp)
	target_link_libraries(test_sv_set ra Catch2::Catch2)
endif()
if(LIST_FOUND)
	add_executable(test_intrusive_list app/test_intrusive_list.cpp)
	target_link_libraries(test_intrusive_list ra Catch2::Catch2)
endif()

if (ENABLE_EXTRAS)
	add_executable(demo_sv_set app/demo_sv_set.cpp)
	add_executable(demo_intrusive_list app/demo_intrusive_list.cpp)
	add_executable(simple_intrusive_list app/simple_intrusive_list.cpp)
	add_executable(trivial_intrusive_list app/trivial_intrusive_list.cpp)
	add_executable(trivial_sv_set app/trivial_sv_set.cpp)
	add_executable(sv_set_1 app/sv_set_1.cpp)
	install(TARGETS test_sv_set DESTINATION bin)
	enable_testing()
endif()

#if (ENABLE_COVERAGE)
#	setup_target_for_coverage_lcov(
#	  NAME coverage
#	  EXECUTABLE test_sv_set
#	  DEPENDENCIES test_sv_set
#	)
#endif()
