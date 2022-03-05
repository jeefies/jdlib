include_directories(
	${PROJECT_SOURCE_DIR}/include
)

set (SRCD  ${PROJECT_SOURCE_DIR}/src)

set (SRC
	${SRCD}/jdlib.c
	${SRCD}/jdlist.c
	${SRCD}/jdstr.c
)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_library(jd SHARED ${SRC})
