# Copyright (C) 2006 International Business Machines and others.
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.

## $Id: Makefile.am 1041 2011-08-14 10:55:03Z stefan $

# Author:  Andreas Waechter           IBM    2006-04-13

AUTOMAKE_OPTIONS = foreign

########################################################################
#                       libCglKnapsackCover                            #
########################################################################

# Name of the library compiled in this directory.  We don't want it to be
# installed since it will be collected into the libCgl library
noinst_LTLIBRARIES = libCglKnapsackCover.la

# List all source files for this library, including headers
libCglKnapsackCover_la_SOURCES = CglKnapsackCover.cpp CglKnapsackCover.hpp CglKnapsackCoverTest.cpp

# This is for libtool (on Windows)
libCglKnapsackCover_la_LDFLAGS = $(LT_LDFLAGS)

# Here list all include flags, relative to this "srcdir" directory.  This
# "cygpath" stuff is necessary to compile with native compilers on Windows.
AM_CPPFLAGS = -I`$(CYGPATH_W) $(srcdir)/..` $(COINUTILS_CFLAGS) $(OSI_CFLAGS)
	

# This line is necessary to allow VPATH compilation
DEFAULT_INCLUDES = -I. -I`$(CYGPATH_W) $(srcdir)` -I..

########################################################################
#                Headers that need to be installed                     #
########################################################################

# Here list all the header files that are required by a user of the library,
# and that therefore should be installed in 'include/coin'
includecoindir = $(includedir)/coin
includecoin_HEADERS = CglKnapsackCover.hpp
