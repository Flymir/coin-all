set(CGL_REDSPLIT_SOURCES
	CglRedSplit.cpp CglRedSplitParam.cpp CglRedSplitTest.cpp CglRedSplit.hpp CglRedSplitParam.hpp)

set(CGL_REDSPLIT_HEADERS CglRedSplit.hpp CglRedSplitParam.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CglRedSplit ${CGL_REDSPLIT_SOURCES})
target_link_libraries(CglRedSplit Cgl)

install(TARGETS CglRedSplit DESTINATION lib)
install(FILES ${CGL_REDSPLIT_HEADERS} DESTINATION include/coin)
