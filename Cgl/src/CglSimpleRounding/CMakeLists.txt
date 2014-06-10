set(CGL_SIMPLEROUNDING_SOURCES
	CglSimpleRounding.cpp CglSimpleRoundingTest.cpp CglSimpleRounding.hpp)

set(CGL_SIMPLEROUNDING_HEADERS CglSimpleRounding.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglSimpleRounding ${CGL_SIMPLEROUNDING_SOURCES})
target_link_libraries(CglSimpleRounding Cgl)

install(TARGETS CglSimpleRounding DESTINATION lib)
install(FILES ${CGL_SIMPLEROUNDING_HEADERS} DESTINATION include/coin)
