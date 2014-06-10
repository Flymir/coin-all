set(CGL_RESIDUALCAPACITY_SOURCES
	CglResidualCapacity.cpp CglResidualCapacityTest.cpp CglResidualCapacity.hpp)

set(CGL_RESIDUALCAPACITY_HEADERS CglResidualCapacity.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglResidualCapacity ${CGL_RESIDUALCAPACITY_SOURCES})
target_link_libraries(CglResidualCapacity Cgl)

install(TARGETS CglResidualCapacity DESTINATION lib)
install(FILES ${CGL_RESIDUALCAPACITY_HEADERS} DESTINATION include/coin)
