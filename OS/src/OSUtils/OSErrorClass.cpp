/* $Id: OSErrorClass.cpp 4292 2011-09-21 05:47:18Z kmartin $ */
/** @file ErrorClass.cpp
 *
 * @author  Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin,
 *
 * \remarks
 * Copyright (C) 2005-2011, Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin,
 * Dalhousie University, Northwestern University, and the University of Chicago.
 * All Rights Reserved.
 * This software is licensed under the Eclipse Public License.
 * Please see the accompanying LICENSE file in root directory for terms.
 *
 */


#include "OSErrorClass.h"



ErrorClass::ErrorClass(std::string errormsg_)
{
    errormsg = errormsg_;
}

