set(OSI_VERSION_MAJOR 0 CACHE INTEGER "Osi version major")
set(OSI_VERSION_MINOR 105 CACHE INTEGER "Osi version minor")
set(OSI_VERSION_RELEASE 2 CACHE INTEGER "Osi version revision")
set(OSI_VERSION "${OSI_VERSION_MAJOR}.${OSI_VERSION_MINOR}.${OSI_VERSION_RELEASE}")
set(OSI_CHECKLEVEL 0 CACHE INTEGER "CoinUtils check level")
set(OSI_VERBOSITY 0 CACHE INTEGER "CoinUtils verbosity")

add_subdirectory(src)
