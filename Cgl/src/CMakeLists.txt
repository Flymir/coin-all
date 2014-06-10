add_definitions(-DHAVE_CONFIG_H -DCGL_BUILD -DCOIN_HAS_CGL)
configure_file(config.h.build.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
configure_file(config_cgl.h.build.in ${CMAKE_CURRENT_BINARY_DIR}/config_cgl.h)

set(CGL_SOURCES
	CglConfig.h
	CglCutGenerator.cpp CglCutGenerator.hpp
	CglMessage.cpp CglMessage.hpp
	CglStored.cpp CglStored.hpp
	CglParam.cpp CglParam.hpp
	CglTreeInfo.cpp CglTreeInfo.hpp)

set(CGL_HEADERS
	CglCutGenerator.hpp
	CglMessage.hpp
	CglStored.hpp
	CglParam.hpp
	CglTreeInfo.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(Cgl ${CGL_SOURCES})
target_link_libraries(Cgl OsiVol OsiClp CoinUtils)

install(TARGETS Cgl DESTINATION lib)
install(FILES ${CGL_HEADERS} DESTINATION include/coin)

add_subdirectory(CglAllDifferent)
add_subdirectory(CglClique)
add_subdirectory(CglDuplicateRow)
add_subdirectory(CglFlowCover)
add_subdirectory(CglGomory)
add_subdirectory(CglKnapsackCover)
add_subdirectory(CglLandP)
add_subdirectory(CglLiftAndProject)
add_subdirectory(CglMixedIntegerRounding)
add_subdirectory(CglMixedIntegerRounding2)
add_subdirectory(CglOddHole)
add_subdirectory(CglPreProcess)
add_subdirectory(CglProbing)
add_subdirectory(CglRedSplit)
add_subdirectory(CglResidualCapacity)
add_subdirectory(CglSimpleRounding)
add_subdirectory(CglTwomir)
