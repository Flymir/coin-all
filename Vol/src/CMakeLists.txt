add_definitions(-DVOL_BUILD)

add_subdirectory(OsiVol)

add_library(Vol VolVolume.cpp VolVolume.hpp)

install(TARGETS Vol DESTINATION lib)
install(FILES VolVolume.hpp DESTINATION include/coin)
