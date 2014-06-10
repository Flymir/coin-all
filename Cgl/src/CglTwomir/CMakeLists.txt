set(CGL_TWOMIR_SOURCES
	CglTwomir.cpp CglTwomirTest.cpp CglTwomir.hpp)

set(CGL_TWOMIR_HEADERS CglTwomir.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglTwomir ${CGL_TWOMIR_SOURCES})
target_link_libraries(CglTwomir Cgl)

install(TARGETS CglTwomir DESTINATION lib)
install(FILES ${CGL_TWOMIR_HEADERS} DESTINATION include/coin)
