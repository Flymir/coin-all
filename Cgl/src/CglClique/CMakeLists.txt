set(CGL_CLIQUE_SOURCES
	CglClique.cpp  CglClique.hpp
	CglCliqueHelper.cpp CglCliqueTest.cpp)

set(CGL_CLIQUE_HEADERS CglClique.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglClique ${CGL_CLIQUE_SOURCES})
target_link_libraries(CglClique Cgl)

install(TARGETS CglClique DESTINATION lib)
install(FILES ${CGL_CLIQUE_HEADERS} DESTINATION include/coin)
