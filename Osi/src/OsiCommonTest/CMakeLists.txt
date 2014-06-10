add_definitions(-DHAVE_CONFIG_H -DOSI_BUILD)

set(OSI_COMMON_TESTS_SOURCES
	OsiColCutTest.cpp
	OsiCutsTest.cpp
	OsiRowCutDebuggerTest.cpp
	OsiRowCutTest.cpp
	OsiSimplexAPITest.cpp
	OsiNetlibTest.cpp
	OsiUnitTestUtils.cpp
	OsiSolverInterfaceTest.cpp)

set(OSI_COMMON_TESTS_HEADERS OsiUnitTests.hpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(OsiCommonTests ${OSI_COMMON_TESTS_SOURCES} ${OSI_COMMON_TESTS_HEADERS})

install(TARGETS OsiCommonTests DESTINATION lib)
install(FILES ${OSI_COMMON_TESTS_HEADERS} DESTINATION include/coin)
