add_definitions(-DHAVE_CONFIG_H -DOSI_BUILD)
configure_file(config.h.build.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
configure_file(config_osi.h.build.in ${CMAKE_CURRENT_BINARY_DIR}/config_osi.h)

set(OSI_SOURCES
	OsiConfig.h
	OsiAuxInfo.cpp OsiAuxInfo.hpp
	OsiBranchingObject.cpp OsiBranchingObject.hpp
	OsiChooseVariable.cpp OsiChooseVariable.hpp
	OsiColCut.cpp OsiColCut.hpp
	OsiCollections.hpp
	OsiCut.cpp OsiCut.hpp
	OsiCuts.cpp OsiCuts.hpp
	OsiNames.cpp
	OsiPresolve.cpp OsiPresolve.hpp
	OsiRowCut.cpp OsiRowCut.hpp
	OsiRowCutDebugger.cpp OsiRowCutDebugger.hpp
	OsiSolverBranch.cpp OsiSolverBranch.hpp
	OsiSolverInterface.cpp OsiSolverInterface.hpp
	OsiSolverParameters.hpp)

set(OSI_HEADERS
	OsiAuxInfo.hpp
	OsiBranchingObject.hpp
	OsiChooseVariable.hpp
	OsiColCut.hpp
	OsiCollections.hpp
	OsiCut.hpp
	OsiCuts.hpp
	OsiPresolve.hpp
	OsiRowCut.hpp
	OsiRowCutDebugger.hpp
	OsiSolverBranch.hpp
	OsiSolverInterface.hpp
	OsiSolverParameters.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(Osi ${OSI_SOURCES} ${OSI_HEADERS})
target_link_libraries(Osi CoinUtils)

install(TARGETS Osi DESTINATION lib)
install(FILES ${OSI_HEADERS} DESTINATION include/coin)
