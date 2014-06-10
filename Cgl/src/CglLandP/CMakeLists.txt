set(CGL_LANDP_SOURCES
	CglLandP.cpp  CglLandP.hpp
	CglLandPTabRow.cpp CglLandPUtils.cpp
        CglLandPMessages.hpp CglLandPMessages.cpp
        CglLandPSimplex.cpp CglLandPSimplex.hpp
        CglLandPValidator.cpp CglLandPValidator.hpp
        CglLandPTest.cpp)

set(CGL_LANDP_HEADERS CglLandP.hpp CglLandPValidator.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/../CglGomory)
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglLandP ${CGL_LANDP_SOURCES})
target_link_libraries(CglLandP Cgl)

install(TARGETS CglLandP DESTINATION lib)
install(FILES ${CGL_LANDP_HEADERS} DESTINATION include/coin)
