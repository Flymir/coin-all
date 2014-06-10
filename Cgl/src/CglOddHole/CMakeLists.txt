set(CGL_ODDHOLE_SOURCES
	CglOddHole.cpp CglOddHoleTest.cpp CglOddHole.hpp)

set(CGL_ODDHOLE_HEADERS CglOddHole.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglOddHole ${CGL_ODDHOLE_SOURCES})
target_link_libraries(CglOddHole Cgl)

install(TARGETS CglOddHole DESTINATION lib)
install(FILES ${CGL_ODDHOLE_HEADERS} DESTINATION include/coin)
