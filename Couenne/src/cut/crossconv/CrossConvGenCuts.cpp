/* $Id: CrossConvGenCuts.cpp 490 2011-01-14 16:07:12Z pbelotti $
 *
 * Name:    CrossConvGenCuts.cpp
 * Author:  Pietro Belotti
 * Purpose: Convexification cuts on redundant relationships between auxiliaries
 *
 * (C) Pietro Belotti, 2010.
 * This file is licensed under the Eclipse Public License (EPL)
 */

#include "CglCutGenerator.hpp"
#include "CouenneCrossConv.hpp"

using namespace Couenne;

/// the main CglCutGenerator
void CouenneCrossConv::generateCuts (const OsiSolverInterface &, 
				     OsiCuts &, 
				     const CglTreeInfo) const {

}
