set(CGL_PREPROCESS_SOURCES
	CglPreProcess.cpp  CglPreProcess.hpp)

set(CGL_PREPROCESS_HEADERS CglPreProcess.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/../CglProbing)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/../CglDuplicateRow)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/../CglClique)
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglPreProcess ${CGL_PREPROCESS_SOURCES})
target_link_libraries(CglPreProcess Cgl)

install(TARGETS CglPreProcess DESTINATION lib)
install(FILES ${CGL_PREPROCESS_HEADERS} DESTINATION include/coin)
