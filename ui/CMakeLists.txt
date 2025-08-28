add_subdirectory(lib/raylib)

#ui-lib
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

add_library(c-nake-ui STATIC
    ${CORE_SOURCES}
)

target_link_libraries(c-nake-ui PRIVATE
	raylib
	c-nake-core
)
 
target_include_directories(c-nake-ui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

file(GLOB_RECURSE INCLUDE_DIRS LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

foreach(dir ${INCLUDE_DIRS})
	if(IS_DIRECTORY ${dir})
		target_include_directories(c-nake-ui PUBLIC ${dir})
	endif()
endforeach()

#game
add_executable(c-nake-game
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
)

target_link_libraries(c-nake-game PRIVATE
	c-nake-ui
	c-nake-core
	raylib
)