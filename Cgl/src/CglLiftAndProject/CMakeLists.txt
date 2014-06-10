set(CGL_LIFTANDPROJECT_SOURCES
	CglLiftAndProject.cpp  CglLiftAndProject.hpp)

set(CGL_LIFTANDPROJECT_HEADERS CglLiftAndProject.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglLiftAndProject ${CGL_LIFTANDPROJECT_SOURCES})
target_link_libraries(CglLiftAndProject Cgl)

install(TARGETS CglLiftAndProject DESTINATION lib)
install(FILES ${CGL_LIFTANDPROJECT_HEADERS} DESTINATION include/coin)
