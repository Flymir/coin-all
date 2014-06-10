set(CGL_GOMORY_SOURCES
	CglGomory.cpp CglGomoryTest.cpp CglGomory.hpp)

set(CGL_GOMORY_HEADERS CglGomory.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglGomory ${CGL_GOMORY_SOURCES})
target_link_libraries(CglGomory Cgl)

install(TARGETS CglGomory DESTINATION lib)
install(FILES ${CGL_GOMORY_HEADERS} DESTINATION include/coin)
