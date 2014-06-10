set(CGL_DUPLICATEROW_SOURCES
	CglDuplicateRow.cpp  CglDuplicateRow.hpp)

set(CGL_DUPLICATEROW_HEADERS CglDuplicateRow.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglDuplicateRow ${CGL_DUPLICATEROW_SOURCES})
target_link_libraries(CglDuplicateRow Cgl)

install(TARGETS CglDuplicateRow DESTINATION lib)
install(FILES ${CGL_DUPLICATEROW_HEADERS} DESTINATION include/coin)
