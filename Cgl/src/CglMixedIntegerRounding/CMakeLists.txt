set(CGL_MIXEDINTEGERROUNDING_SOURCES
	CglMixedIntegerRounding.cpp CglMixedIntegerRoundingTest.cpp CglMixedIntegerRounding.hpp)

set(CGL_MIXEDINTEGERROUNDING_HEADERS CglMixedIntegerRounding.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglMixedIntegerRounding ${CGL_MIXEDINTEGERROUNDING_SOURCES})
target_link_libraries(CglMixedIntegerRounding Cgl)

install(TARGETS CglMixedIntegerRounding DESTINATION lib)
install(FILES ${CGL_MIXEDINTEGERROUNDING_HEADERS} DESTINATION include/coin)
