add_definitions(-DOSICLP_BUILD)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(OsiClp OsiClpSolverInterface.cpp OsiClpSolverInterface.cpp)
target_link_libraries(OsiClp Osi Clp)

install(TARGETS OsiClp DESTINATION lib)
install(FILES OsiClpSolverInterface.hpp DESTINATION include/coin)
