include_directories(
	${PROJECT_SOURCE_DIR}/include
)

set (SRCD  ${PROJECT_SOURCE_DIR}/src)
set (CMAKE_C_FLAGS ${CFLAGS})

set (SRC
	${SRCD}/jdlib.c
	${SRCD}/jdlist.c
	${SRCD}/jdstr.c
	${SRCD}/jdhashtable.c
	${SRCD}/jdbinary_search_tree.c
	${SRCD}/jdstack.c
)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

if (ENABLE_STATIC)
	add_library (jd_static STATIC ${SRC})
else()
	add_library (jd SHARED ${SRC})
endif()

set_target_properties (jd PROPERTIES PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/jdlib.h)
