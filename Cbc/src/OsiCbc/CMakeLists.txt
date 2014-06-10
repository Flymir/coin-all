add_definitions(-DOSICBC_BUILD)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(OsiCbc OsiCbcSolverInterface.cpp OsiCbcSolverInterface.cpp)
target_link_libraries(OsiCbc Osi Cbc)

install(TARGETS OsiCbc DESTINATION lib)
install(FILES OsiCbcSolverInterface.hpp DESTINATION include/coin)
