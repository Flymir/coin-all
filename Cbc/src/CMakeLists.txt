add_definitions(-DHAVE_CONFIG_H -DCBC_BUILD -DCOIN_HAS_CBC -DCOIN_NO_CLP_MESSAGE -DUSE_CBCCONFIG)
configure_file(config.h.build.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
configure_file(config_cbc.h.build.in ${CMAKE_CURRENT_BINARY_DIR}/config_cbc.h)

add_subdirectory(OsiCbc)

set(CBC_SOURCES
	Cbc_C_Interface.cpp Cbc_C_Interface.h 
	CbcConfig.h 
	CbcBranchActual.hpp 
	CbcBranchAllDifferent.cpp CbcBranchAllDifferent.hpp 
	CbcBranchBase.hpp 
	CbcBranchCut.cpp CbcBranchCut.hpp 
	CbcBranchDecision.cpp CbcBranchDecision.hpp 
	CbcBranchDefaultDecision.cpp CbcBranchDefaultDecision.hpp 
	CbcBranchDynamic.cpp CbcBranchDynamic.hpp 
	CbcBranchingObject.cpp CbcBranchingObject.hpp 
	CbcBranchLotsize.cpp CbcBranchLotsize.hpp 
	CbcBranchToFixLots.cpp CbcBranchToFixLots.hpp 
	CbcCompareActual.hpp 
	CbcCompareBase.hpp 
	CbcCompareDefault.cpp CbcCompareDefault.hpp 
	CbcCompareDepth.cpp CbcCompareDepth.hpp 
	CbcCompareEstimate.cpp CbcCompareEstimate.hpp 
	CbcCompareObjective.cpp CbcCompareObjective.hpp 
	CbcConsequence.cpp CbcConsequence.hpp 
	CbcClique.cpp CbcClique.hpp 
	CbcCompare.hpp 
	CbcCountRowCut.cpp CbcCountRowCut.hpp 
	CbcCutGenerator.cpp CbcCutGenerator.hpp 
	CbcCutModifier.cpp CbcCutModifier.hpp 
	CbcCutSubsetModifier.cpp CbcCutSubsetModifier.hpp 
	CbcDummyBranchingObject.cpp CbcDummyBranchingObject.hpp 
	CbcEventHandler.cpp CbcEventHandler.hpp 
	CbcFathom.cpp CbcFathom.hpp 
	CbcFathomDynamicProgramming.cpp CbcFathomDynamicProgramming.hpp 
	CbcFeasibilityBase.hpp 
	CbcFixVariable.cpp CbcFixVariable.hpp 
	CbcFullNodeInfo.cpp CbcFullNodeInfo.hpp 
	CbcFollowOn.cpp CbcFollowOn.hpp 
	CbcGeneral.cpp CbcGeneral.hpp 
	CbcGeneralDepth.cpp CbcGeneralDepth.hpp 
	CbcHeuristic.cpp CbcHeuristic.hpp 
	CbcHeuristicDINS.cpp CbcHeuristicDINS.hpp 
	CbcHeuristicDive.cpp CbcHeuristicDive.hpp 
	CbcHeuristicDiveCoefficient.cpp CbcHeuristicDiveCoefficient.hpp 
	CbcHeuristicDiveFractional.cpp CbcHeuristicDiveFractional.hpp 
	CbcHeuristicDiveGuided.cpp CbcHeuristicDiveGuided.hpp 
	CbcHeuristicDiveLineSearch.cpp CbcHeuristicDiveLineSearch.hpp 
	CbcHeuristicDivePseudoCost.cpp CbcHeuristicDivePseudoCost.hpp 
	CbcHeuristicDiveVectorLength.cpp CbcHeuristicDiveVectorLength.hpp 
	CbcHeuristicFPump.cpp CbcHeuristicFPump.hpp 
	CbcHeuristicGreedy.cpp CbcHeuristicGreedy.hpp 
	CbcHeuristicLocal.cpp CbcHeuristicLocal.hpp 
	CbcHeuristicPivotAndFix.cpp CbcHeuristicPivotAndFix.hpp 
	CbcHeuristicRandRound.cpp CbcHeuristicRandRound.hpp 
	CbcHeuristicRENS.cpp CbcHeuristicRENS.hpp 
	CbcHeuristicRINS.cpp CbcHeuristicRINS.hpp 
	CbcHeuristicVND.cpp CbcHeuristicVND.hpp 
	CbcMessage.cpp CbcMessage.hpp 
	CbcModel.cpp CbcModel.hpp 
	CbcNode.cpp CbcNode.hpp 
	CbcNodeInfo.cpp CbcNodeInfo.hpp 
	CbcNWay.cpp CbcNWay.hpp 
	CbcObject.cpp CbcObject.hpp 
	CbcObjectUpdateData.cpp CbcObjectUpdateData.hpp 
	CbcPartialNodeInfo.cpp CbcPartialNodeInfo.hpp 
	CbcSimpleInteger.cpp CbcSimpleInteger.hpp 
	CbcSimpleIntegerDynamicPseudoCost.cpp 
        CbcSimpleIntegerDynamicPseudoCost.hpp 
	CbcSimpleIntegerPseudoCost.cpp 
        CbcSimpleIntegerPseudoCost.hpp 
	CbcSOS.cpp CbcSOS.hpp 
	CbcStatistics.cpp CbcStatistics.hpp 
	CbcStrategy.cpp CbcStrategy.hpp 
	CbcSubProblem.cpp CbcSubProblem.hpp 
	CbcThread.cpp CbcThread.hpp 
	CbcTree.cpp CbcTree.hpp 
	CbcTreeLocal.cpp CbcTreeLocal.hpp
)

set(CBCSOLVER_SOURCES
	CbcCbcParam.cpp 
	Cbc_ampl.cpp Cbc_ampl.h 
	CbcLinked.cpp CbcLinked.hpp CbcLinkedUtils.cpp 
	unitTestClp.cpp CbcSolver.cpp 
	CbcSolverHeuristics.cpp CbcSolverHeuristics.hpp 
	CbcSolverAnalyze.cpp CbcSolverAnalyze.hpp 
	CbcSolverExpandKnapsack.cpp CbcSolverExpandKnapsack.hpp
)

set(CBC_HEADERS
	Cbc_C_Interface.h 
	CbcBranchActual.hpp 
	CbcBranchAllDifferent.hpp 
	CbcBranchBase.hpp 
	CbcBranchDynamic.hpp 
	CbcBranchCut.hpp 
        CbcBranchDecision.hpp 
	CbcBranchDefaultDecision.hpp 
	CbcBranchingObject.hpp 
	CbcBranchLotsize.hpp 
	CbcBranchToFixLots.hpp 
	CbcCompareActual.hpp 
	CbcCompareBase.hpp 
	CbcCompareDefault.hpp 
	CbcCompareDepth.hpp 
	CbcCompareEstimate.hpp 
	CbcCompareObjective.hpp 
	CbcConsequence.hpp 
	CbcClique.hpp 
	CbcCompare.hpp 
	CbcCutGenerator.hpp 
	CbcCutModifier.hpp 
	CbcCutSubsetModifier.hpp 
	CbcDummyBranchingObject.hpp 
	CbcFathom.hpp 
	CbcEventHandler.hpp 
	CbcFeasibilityBase.hpp 
	CbcFixVariable.hpp 
	CbcFollowOn.hpp 
	CbcFullNodeInfo.hpp 
	CbcGeneral.hpp 
	CbcGeneralDepth.hpp 
	CbcHeuristic.hpp 
	CbcHeuristicDINS.hpp 
	CbcHeuristicDive.hpp 
	CbcHeuristicDiveCoefficient.hpp 
	CbcHeuristicDiveFractional.hpp 
	CbcHeuristicDiveGuided.hpp 
	CbcHeuristicDiveLineSearch.hpp 
	CbcHeuristicDivePseudoCost.hpp 
	CbcHeuristicDiveVectorLength.hpp 
	CbcHeuristicFPump.hpp 
	CbcHeuristicGreedy.hpp 
	CbcHeuristicLocal.hpp 
	CbcHeuristicPivotAndFix.hpp 
	CbcHeuristicRandRound.hpp 
	CbcHeuristicRENS.hpp 
	CbcHeuristicRINS.hpp 
	CbcHeuristicVND.hpp 
	CbcMessage.hpp 
	CbcModel.hpp 
	CbcNode.hpp 
	CbcNodeInfo.hpp 
	CbcNWay.hpp 
        CbcObject.hpp 
	CbcObjectUpdateData.hpp 
	CbcPartialNodeInfo.hpp 
	CbcSimpleInteger.hpp 
	CbcSimpleIntegerDynamicPseudoCost.hpp 
	CbcSimpleIntegerPseudoCost.hpp 
	CbcStrategy.hpp 
	CbcSolver.hpp 
	CbcSOS.hpp 
	CbcSubProblem.hpp 
	CbcTree.hpp 
	CbcLinked.hpp 
	CbcTreeLocal.hpp 
	ClpConstraintAmpl.hpp 
	ClpAmplObjective.hpp)

set(CBCP_SOURCES CoinSolve.cpp)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

add_library(CbcSolver ${CBCSOLVER_SOURCES})
target_link_libraries(CbcSolver CoinUtils CglResidualCapacity CglLandP CglRedSplit)
add_library(Cbc ${CBC_SOURCES})
target_link_libraries(Cbc CbcSolver Cgl CglPreProcess CglDuplicateRow CglProbing CglGomory CglMixedIntegerRounding2 CglClique CglFlowCover CglKnapsackCover CglTwomir)
add_executable(cbc ${CBCP_SOURCES})
target_link_libraries(cbc Cbc CbcSolver OsiClp)

install(TARGETS Cbc DESTINATION lib)
install(TARGETS CbcSolver DESTINATION lib)
install(TARGETS cbc DESTINATION bin)
install(FILES ${CBC_HEADERS} DESTINATION include/coin)
