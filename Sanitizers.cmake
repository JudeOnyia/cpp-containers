# The ENABLE_ASAN option sets the Address Sanitizer
option(ENABLE_ASAN "Enable Asan" false)

if(ENABLE_ASAN)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
	message("Enabled Address Sanitizer")
endif()

# The ENABLE_LSAN option sets the Leak Sanitizer
option(ENABLE_LSAN "Enable Lsan" false)

if(ENABLE_LSAN)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=leak")
	message("Enabled Leak Sanitizer")
endif()
