set(CGL_FLOWCOVER_SOURCES
	CglFlowCover.cpp CglFlowCoverTest.cpp CglFlowCover.hpp)

set(CGL_FLOWCOVER_HEADERS CglFlowCover.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglFlowCover ${CGL_FLOWCOVER_SOURCES})
target_link_libraries(CglFlowCover Cgl)

install(TARGETS CglFlowCover DESTINATION lib)
install(FILES ${CGL_FLOWCOVER_HEADERS} DESTINATION include/coin)
