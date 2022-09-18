include_directories(
	${PROJECT_SOURCE_DIR}/include
	)

set (CMAKE_C_FLAGS ${CFLAGS})

add_executable (jdlib test.c)
add_executable (jdstr test_jstrs.c)
add_executable (jdlist test_jlist.c)
add_executable (jdhash test_jhash.c)
add_executable (jdstack test_jstack.c)
add_executable (jdqueue test_jqueue.c)
# add_executable (jdbit test_jbit.c)
# add_executable (jdbst test_jbst.c)

target_link_libraries (jdlist jd)
target_link_libraries (jdstr jd)
target_link_libraries (jdlib jd)
target_link_libraries (jdhash jd)
target_link_libraries (jdstack jd)
target_link_libraries (jdqueue jd)
# target_link_libraries (jdbit jd)
# target_link_libraries (jdbst jd)

add_test (NAME jdlist COMMAND jdlist)
add_test (NAME jdstr COMMAND jdstr)
add_test (NAME jdlib COMMAND jdlib)
add_test (NAME jdhash COMMAND jdhash)
add_test (NAME jdstack COMMAND jdstack)
add_test (NAME jdqueue COMMAND jdqueue)
# add_test (NAME jdbit COMMAND jdbit)
# add_test (NAME jdbst COMMAND jdbst)
