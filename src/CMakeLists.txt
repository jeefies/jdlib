include_directories(
	${PROJECT_SOURCE_DIR}/include
)

set (SRCD  ${PROJECT_SOURCE_DIR}/src)
set (CMAKE_C_FLAGS ${CFLAGS})

set (SRC
	${SRCD}/jdlib.c
	${SRCD}/jdlist.c
	${SRCD}/jdstr.c
)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_library (jd SHARED ${SRC})
set_target_properties (jd PROPERTIES PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/jdlib.h)
