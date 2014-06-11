add_definitions(-DHAVE_CONFIG_H -DCLP_BUILD -DCOIN_HAS_CLP)
configure_file(config.h.build.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
configure_file(config_clp.h.build.in ${CMAKE_CURRENT_BINARY_DIR}/config_clp.h)

add_subdirectory(OsiClp)

set(CLP_SOURCES
	ClpConfig.h
	ClpCholeskyBase.cpp ClpCholeskyBase.hpp
	ClpCholeskyDense.cpp ClpCholeskyDense.hpp
	ClpConstraint.cpp ClpConstraint.hpp
	ClpConstraintLinear.cpp ClpConstraintLinear.hpp
	ClpConstraintQuadratic.cpp ClpConstraintQuadratic.hpp
	Clp_C_Interface.cpp Clp_C_Interface.h
	ClpDualRowDantzig.cpp ClpDualRowDantzig.hpp
	ClpDualRowPivot.cpp ClpDualRowPivot.hpp
	ClpDualRowSteepest.cpp ClpDualRowSteepest.hpp
	ClpDummyMatrix.cpp ClpDummyMatrix.hpp
	ClpDynamicExampleMatrix.cpp ClpDynamicExampleMatrix.hpp
	ClpDynamicMatrix.cpp ClpDynamicMatrix.hpp
	ClpEventHandler.cpp ClpEventHandler.hpp
	ClpFactorization.cpp ClpFactorization.hpp 
	ClpGubDynamicMatrix.cpp ClpGubDynamicMatrix.hpp 
	ClpGubMatrix.cpp ClpGubMatrix.hpp 
	ClpHelperFunctions.cpp ClpHelperFunctions.hpp 
	ClpInterior.cpp ClpInterior.hpp 
	ClpLinearObjective.cpp ClpLinearObjective.hpp 
	ClpMatrixBase.cpp ClpMatrixBase.hpp 
	ClpMessage.cpp ClpMessage.hpp 
	ClpModel.cpp ClpModel.hpp 
	ClpNetworkBasis.cpp ClpNetworkBasis.hpp 
	ClpNetworkMatrix.cpp ClpNetworkMatrix.hpp 
	ClpNonLinearCost.cpp ClpNonLinearCost.hpp 
	ClpNode.cpp ClpNode.hpp 
	ClpObjective.cpp ClpObjective.hpp 
	ClpPackedMatrix.cpp ClpPackedMatrix.hpp 
	ClpParameters.hpp 
	ClpPlusMinusOneMatrix.cpp ClpPlusMinusOneMatrix.hpp 
	ClpPredictorCorrector.cpp ClpPredictorCorrector.hpp 
	ClpPdco.cpp ClpPdco.hpp 
	ClpPdcoBase.cpp ClpPdcoBase.hpp 
	ClpLsqr.cpp ClpLsqr.hpp 
	ClpPresolve.cpp ClpPresolve.hpp 
	ClpPrimalColumnDantzig.cpp ClpPrimalColumnDantzig.hpp 
	ClpPrimalColumnPivot.cpp ClpPrimalColumnPivot.hpp 
	ClpPrimalColumnSteepest.cpp ClpPrimalColumnSteepest.hpp 
	ClpQuadraticObjective.cpp ClpQuadraticObjective.hpp 
	ClpSimplex.cpp ClpSimplex.hpp 
	ClpSimplexDual.cpp ClpSimplexDual.hpp 
	ClpSimplexNonlinear.cpp ClpSimplexNonlinear.hpp 
	ClpSimplexOther.cpp ClpSimplexOther.hpp 
	ClpSimplexPrimal.cpp ClpSimplexPrimal.hpp 
	ClpSolve.cpp ClpSolve.hpp 
	Idiot.cpp Idiot.hpp 
	IdiSolve.cpp)

set(CLP_HEADERS
	Clp_C_Interface.h 
	ClpConfig.h
	config_clp_default.h
	ClpCholeskyBase.hpp 
	ClpCholeskyDense.hpp 
	ClpConstraint.hpp 
	ClpConstraintLinear.hpp 
	ClpConstraintQuadratic.hpp 
	ClpDualRowDantzig.hpp 
	ClpDualRowPivot.hpp 
	ClpDualRowSteepest.hpp 
	ClpDummyMatrix.hpp 
	ClpDynamicExampleMatrix.hpp 
	ClpDynamicMatrix.hpp 
	ClpEventHandler.hpp 
	ClpFactorization.hpp 
	ClpGubDynamicMatrix.hpp 
	ClpGubMatrix.hpp 
	ClpInterior.hpp 
	ClpLinearObjective.hpp 
	ClpMatrixBase.hpp 
	ClpMessage.hpp 
	ClpModel.hpp 
	ClpNetworkMatrix.hpp 
	ClpNonLinearCost.hpp 
	ClpNode.hpp 
	ClpObjective.hpp 
	ClpPackedMatrix.hpp 
	ClpPdcoBase.hpp 
	ClpPlusMinusOneMatrix.hpp 
	ClpParameters.hpp 
	ClpPresolve.hpp 
	ClpPrimalColumnDantzig.hpp 
	ClpPrimalColumnPivot.hpp 
	ClpPrimalColumnSteepest.hpp 
	ClpQuadraticObjective.hpp 
	ClpSimplex.hpp 
	ClpSimplexNonlinear.hpp 
	ClpSimplexOther.hpp 
	ClpSimplexPrimal.hpp 
	ClpSolve.hpp 
	CbcOrClpParam.hpp 
	Idiot.hpp)

set(clpp_SOURCES
	ClpMain.cpp 
	CbcOrClpParam.cpp CbcOrClpParam.hpp
	MyEventHandler.cpp MyEventHandler.hpp
	MyMessageHandler.cpp MyMessageHandler.hpp
	unitTest.cpp)

find_path(LAPACKE_INCLUDE_DIR lapacke.h)
find_library(LAPACK_LIBRARY NAMES lapack)
find_library(BLAS_LIBRARY NAMES blas)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${LAPACKE_INCLUDE_DIR})

add_library(Clp ${CLP_SOURCES})
target_link_libraries(Clp CoinUtils)
add_executable(clp ${clpp_SOURCES})
target_link_libraries(clp Clp ${LAPACK_LIBRARY} ${BLAS_LIBRARY})

install(TARGETS Clp DESTINATION lib)
install(TARGETS clp DESTINATION bin)
install(FILES ${CLP_HEADERS} DESTINATION include/coin)
