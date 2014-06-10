set(CGL_MIXEDINTEGERROUNDING2_SOURCES
	CglMixedIntegerRounding2.cpp CglMixedIntegerRounding2Test.cpp CglMixedIntegerRounding2.hpp)

set(CGL_MIXEDINTEGERROUNDING2_HEADERS CglMixedIntegerRounding2.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglMixedIntegerRounding2 ${CGL_MIXEDINTEGERROUNDING2_SOURCES})
target_link_libraries(CglMixedIntegerRounding2 Cgl)

install(TARGETS CglMixedIntegerRounding2 DESTINATION lib)
install(FILES ${CGL_MIXEDINTEGERROUNDING2_HEADERS} DESTINATION include/coin)
