set(CGL_PROBING_SOURCES
	CglProbing.cpp CglProbingTest.cpp CglProbing.hpp)

set(CGL_PROBING_HEADERS CglProbing.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglProbing ${CGL_PROBING_SOURCES})
target_link_libraries(CglProbing Cgl)

install(TARGETS CglProbing DESTINATION lib)
install(FILES ${CGL_PROBING_HEADERS} DESTINATION include/coin)
