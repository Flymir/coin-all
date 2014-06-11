set(COINUTILS_MEMPOOL_MAXPOOLED 4096 CACHE INTEGER "Specify the default maximum memory allocation size that is served by the memory pool. If negative then the memory pool is disabled completely. Otherwise its value can e overridden at runtime using the COINUTILS_MEMPOOL_MAXPOOLED environment variable.")
set(COINUTILS_MEMPOOL_OVERRIDE_NEW ON CACHE BOOL "Enables the CoinUtils mempool to override global new/delete.")
set(COINUTILS_PTHREADS ON CACHE BOOL "Thread aware versionof CoinUtils should be compiled.")

add_definitions(-DHAVE_CONFIG_H -DCOINUTILS_BUILD)
configure_file(config.h.build.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
configure_file(config_coinutils.h.build.in ${CMAKE_CURRENT_BINARY_DIR}/config_coinutils.h)

set(COIN_UTILS_SOURCES
	config_default.h 
	CoinUtilsConfig.h 
	Coin_C_defines.h 
	CoinAlloc.cpp CoinAlloc.hpp 
	CoinBuild.cpp CoinBuild.hpp 
	CoinDenseVector.cpp CoinDenseVector.hpp 
	CoinDistance.hpp 
	CoinError.cpp CoinError.hpp 
	CoinFactorization.hpp 
	CoinFactorization1.cpp 
	CoinFactorization2.cpp 
	CoinFactorization3.cpp 
	CoinFactorization4.cpp 
	CoinSimpFactorization.hpp 
	CoinSimpFactorization.cpp 
	CoinDenseFactorization.hpp 
	CoinDenseFactorization.cpp 
	CoinOslFactorization.hpp 
	CoinOslFactorization.cpp 
	CoinOslFactorization2.cpp 
	CoinOslFactorization3.cpp 
	CoinOslC.h 
	CoinFileIO.cpp CoinFileIO.hpp 
	CoinFinite.cpp CoinFinite.hpp 
	CoinFloatEqual.hpp 
	CoinHelperFunctions.hpp 
	CoinIndexedVector.cpp CoinIndexedVector.hpp 
	CoinLpIO.cpp CoinLpIO.hpp 
	CoinMessage.cpp CoinMessage.hpp 
	CoinMessageHandler.cpp CoinMessageHandler.hpp 
	CoinModel.cpp CoinModel.hpp 
	CoinStructuredModel.cpp CoinStructuredModel.hpp 
	CoinModelUseful.cpp CoinModelUseful.hpp 
	CoinModelUseful2.cpp 
	CoinMpsIO.cpp CoinMpsIO.hpp 
	CoinPackedMatrix.cpp CoinPackedMatrix.hpp 
	CoinPackedVector.cpp CoinPackedVector.hpp 
	CoinPackedVectorBase.cpp CoinPackedVectorBase.hpp 
	CoinParam.cpp CoinParamUtils.cpp CoinParam.hpp 
	CoinPostsolveMatrix.cpp 
	CoinPragma.hpp 
	CoinPrePostsolveMatrix.cpp 
	CoinPresolveDoubleton.cpp CoinPresolveDoubleton.hpp 
	CoinPresolveDual.cpp CoinPresolveDual.hpp 
	CoinPresolveDupcol.cpp CoinPresolveDupcol.hpp 
	CoinPresolveEmpty.cpp CoinPresolveEmpty.hpp 
	CoinPresolveFixed.cpp CoinPresolveFixed.hpp 
	CoinPresolveForcing.cpp CoinPresolveForcing.hpp 
	CoinPresolveHelperFunctions.cpp 
	CoinPresolveImpliedFree.cpp CoinPresolveImpliedFree.hpp 
	CoinPresolveIsolated.cpp CoinPresolveIsolated.hpp 
	CoinPresolveMatrix.cpp CoinPresolveMatrix.hpp 
	CoinPresolvePsdebug.cpp CoinPresolvePsdebug.hpp 
	CoinPresolveSingleton.cpp CoinPresolveSingleton.hpp 
	CoinPresolveSubst.cpp CoinPresolveSubst.hpp 
	CoinPresolveTighten.cpp CoinPresolveTighten.hpp 
	CoinPresolveTripleton.cpp CoinPresolveTripleton.hpp 
	CoinPresolveUseless.cpp CoinPresolveUseless.hpp 
	CoinPresolveZeros.cpp CoinPresolveZeros.hpp 
	CoinSearchTree.cpp CoinSearchTree.hpp 
	CoinShallowPackedVector.cpp CoinShallowPackedVector.hpp 
	CoinSignal.hpp 
	CoinSmartPtr.hpp 
	CoinSnapshot.cpp CoinSnapshot.hpp 
	CoinSort.hpp 
	CoinTime.hpp 
	CoinTypes.hpp 
	CoinUtility.hpp 
	CoinWarmStart.hpp 
	CoinWarmStartBasis.cpp CoinWarmStartBasis.hpp 
	CoinWarmStartVector.cpp CoinWarmStartVector.hpp 
	CoinWarmStartDual.cpp CoinWarmStartDual.hpp 
	CoinWarmStartPrimalDual.cpp CoinWarmStartPrimalDual.hpp)

set(COIN_UTILS_HEADERS
	Coin_C_defines.h 
	coin_coinutils_default.h
	CoinAlloc.hpp 
	CoinBuild.hpp 
	CoinDenseVector.hpp 
	CoinDistance.hpp 
	CoinError.hpp 
	CoinFactorization.hpp 
	CoinSimpFactorization.hpp 
	CoinDenseFactorization.hpp 
	CoinOslFactorization.hpp 
	CoinFileIO.hpp 
	CoinFinite.hpp 
	CoinFloatEqual.hpp 
	CoinHelperFunctions.hpp 
	CoinIndexedVector.hpp 
	CoinLpIO.hpp 
	CoinMessage.hpp 
	CoinMessageHandler.hpp 
	CoinModel.hpp 
	CoinStructuredModel.hpp 
	CoinModelUseful.hpp 
	CoinMpsIO.hpp 
	CoinPackedMatrix.hpp 
	CoinPackedVector.hpp 
	CoinPackedVectorBase.hpp 
	CoinParam.hpp 
	CoinPragma.hpp 
	CoinPresolveDoubleton.hpp 
	CoinPresolveDual.hpp 
	CoinPresolveDupcol.hpp 
	CoinPresolveEmpty.hpp 
	CoinPresolveFixed.hpp 
	CoinPresolveForcing.hpp 
	CoinPresolveImpliedFree.hpp 
	CoinPresolveIsolated.hpp 
	CoinPresolveMatrix.hpp 
	CoinPresolvePsdebug.hpp 
	CoinPresolveSingleton.hpp 
	CoinPresolveSubst.hpp 
	CoinPresolveTighten.hpp 
	CoinPresolveTripleton.hpp 
	CoinPresolveUseless.hpp 
	CoinPresolveZeros.hpp 
	CoinSearchTree.hpp 
	CoinShallowPackedVector.hpp 
	CoinSignal.hpp 
	CoinSmartPtr.hpp 
	CoinSnapshot.hpp 
	CoinSort.hpp 
	CoinTime.hpp 
	CoinTypes.hpp 
	CoinUtility.hpp 
	CoinUtilsConfig.h 
	CoinWarmStart.hpp 
	CoinWarmStartBasis.hpp 
	CoinWarmStartVector.hpp 
	CoinWarmStartDual.hpp
	CoinWarmStartPrimalDual.hpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(CoinUtils ${COIN_UTILS_SOURCES})

install(TARGETS CoinUtils DESTINATION lib)
install(FILES ${COIN_UTILS_HEADERS} DESTINATION include/coin)
