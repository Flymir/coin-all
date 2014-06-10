set(CGL_ALLDIFFERENT_SOURCES
	CglAllDifferent.cpp  CglAllDifferent.hpp)

set(CGL_ALLDIFFERENT_HEADERS CglAllDifferent.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglAllDifferent ${CGL_ALLDIFFERENT_SOURCES})
target_link_libraries(CglAllDifferent Cgl)

install(TARGETS CglAllDifferent DESTINATION lib)
install(FILES ${CGL_ALLDIFFERENT_HEADERS} DESTINATION include/coin)
