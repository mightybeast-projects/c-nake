cmake_minimum_required(VERSION 3.12)

add_subdirectory(lib/unity)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    src/*.tests.c
) 
 
add_executable(c-nake-core-tests ${SOURCE_FILES})

target_link_libraries(c-nake-core-tests PRIVATE
    c-nake-core
    unity
)

file(GLOB_RECURSE INCLUDE_DIRS LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

foreach(dir ${INCLUDE_DIRS})
	if(IS_DIRECTORY ${dir})
		target_include_directories(c-nake-core-tests PUBLIC ${dir})
	endif()
endforeach()