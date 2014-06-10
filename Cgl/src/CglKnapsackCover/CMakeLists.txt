set(CGL_KNAPSACKCOVER_SOURCES
	CglKnapsackCover.cpp CglKnapsackCoverTest.cpp CglKnapsackCover.hpp)

set(CGL_KNAPSACKCOVER_HEADERS CglKnapsackCover.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglKnapsackCover ${CGL_KNAPSACKCOVER_SOURCES})
target_link_libraries(CglKnapsackCover Cgl)

install(TARGETS CglKnapsackCover DESTINATION lib)
install(FILES ${CGL_KNAPSACKCOVER_HEADERS} DESTINATION include/coin)
