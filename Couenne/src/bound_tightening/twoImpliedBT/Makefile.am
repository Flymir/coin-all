# $Id: Makefile.am 624 2011-06-09 15:21:30Z stefan $
#
# Copyright (C) 2006 International Business Machines and others.
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.

# Author: Pietro Belotti, from a template by Pierre Bonami

AUTOMAKE_OPTIONS = foreign

noinst_LTLIBRARIES = libCouenneTwoImplied.la

# List all source files for this library, including headers
libCouenneTwoImplied_la_SOURCES = \
	TwoImpliedConstructors.cpp \
	TwoImpliedIneqCombine.cpp \
	TwoImpliedGenCuts.cpp 

# This is for libtool
libCouenneTwoImplied_la_LDFLAGS = $(LT_LDFLAGS)

# Here list all include flags, relative to this "srcdir" directory.  This
# "cygpath" stuff is necessary to compile with native compilers on Windows
AM_CPPFLAGS = $(COUENNELIB_CFLAGS) \
	-I`$(CYGPATH_W) $(srcdir)/../..` \
	-I`$(CYGPATH_W) $(srcdir)/../../expression` \
	-I`$(CYGPATH_W) $(srcdir)/../../branch` \
	-I`$(CYGPATH_W) $(srcdir)/../../problem` \
	-I`$(CYGPATH_W) $(srcdir)/../../bound_tightening`

# This line is necessary to allow VPATH compilation
DEFAULT_INCLUDES = -I. -I`$(CYGPATH_W) $(srcdir)` -I$(top_builddir)/src
