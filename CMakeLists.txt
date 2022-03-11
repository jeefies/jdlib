cmake_minimum_required(VERSION 3.0)

project (JDLib)
set (JDLib_VERSION_MAJOR 1)
set (JDLib_VERSION_MINOR 0)

enable_testing()

add_subdirectory (src)
add_subdirectory (test)

set (CMAKE_INSTALL_PREFIX /usr)

install (TARGETS jd
	EXPORT JDTarget
	LIBRARY DESTINATION lib
	PUBLIC_HEADER DESTINATION include
	)
