add_definitions(-DOSIVOL_BUILD)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(OsiVol OsiVolSolverInterface.cpp OsiVolSolverInterfaceIO.cpp)
target_link_libraries(OsiVol Osi Vol)

install(TARGETS OsiVol DESTINATION lib)
install(FILES OsiVolSolverInterface.hpp DESTINATION include/coin)
