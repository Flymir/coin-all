# Copyright (C) 2006 International Business Machines and others.
# All Rights Reserved.
# This file is distributed under the Common Public License.

## $Id: Makefile.am 719 2006-06-01 20:11:40Z andreasw $

# Author:  Andreas Waechter           IBM    2006-04-13

AUTOMAKE_OPTIONS = foreign

########################################################################
#                             libOSAgent                               #
########################################################################

# Name of the library compiled in this directory.
noinst_LTLIBRARIES = libOSAgent.la

# List all source files for this library, including headers
libOSAgent_la_SOURCES = \
	OShL.cpp OShL.h OSSolverAgent.cpp \
	OSSolverAgent.h OSWSUtil.cpp OSWSUtil.h

# This is for libtool (on Windows)
libOSAgent_la_LDFLAGS = $(LT_LDFLAGS)

# Here list all include flags, relative to this "srcdir" directory.  This
# "cygpath" stuff is necessary to compile with native compilers on Windows.
AM_CPPFLAGS = \
	-I`$(CYGPATH_W) $(srcdir)/..` \
	-I`$(CYGPATH_W) $(srcdir)/../OSCommonInterfaces` \
	-I`$(CYGPATH_W) $(srcdir)/../OSUtils` \
	$(OSLIB_CFLAGS)

# This line is necessary to allow VPATH compilation
DEFAULT_INCLUDES = -I. -I`$(CYGPATH_W) $(srcdir)` -I..

########################################################################
#                Headers that need to be installed                     #
########################################################################

# Here list all the header files that are required by a user of the library,
# and that therefore should be installed in 'include/coin'
includecoindir = $(includedir)/coin
includecoin_HEADERS = \
	OShL.h OSSolverAgent.h OSWSUtil.h
