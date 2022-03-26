include_directories(
	${PROJECT_SOURCE_DIR}/include
	)

set (CMAKE_C_FLAGS ${CFLAGS})

add_executable (jdlist test_jlist.c)
add_executable (jdstr test_jstrs.c)
add_executable (jdhash test_jhash.c)
add_executable (jdlib test.c)

target_link_libraries (jdlist jd)
target_link_libraries (jdstr jd)
target_link_libraries (jdlib jd)
target_link_libraries (jdhash jd)

add_test (NAME jdlist COMMAND jdlist)
add_test (NAME jdstr COMMAND jdstr)
add_test (NAME jdlib COMMAND jdlib)
add_test (NAME jdhash COMMAND jdhash)
