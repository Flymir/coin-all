dnl $Id: configure.ac 2116 2011-10-16 00:31:12Z bradbell $
dnl ---------------------------------------------------------------------------
dnl CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-11 Bradley M. Bell
dnl
dnl CppAD is distributed under multiple licenses. This distribution is under
dnl the terms of the
dnl                     Common Public License Version 1.0.
dnl 
dnl A copy of this license is included in the COPYING file of this distribution.
dnl Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
dnl ---------------------------------------------------------------------------
dnl
dnl Process this file with autoconf to produce a configure script.
dnl   package     version              bug-report
AC_INIT(CppAD, 20110101.5, cppad@list.coin-or.org)
AC_SUBST(PACKAGE_URL, "http://www.coin-or.org/CppAD")
AC_SUBST(PACKAGE_DESCRIPTION, "Differentiation of C++ Algorithms")

dnl By defalut disable maintainer mode when running configure;
dnl --enable-maintainer-mode will enable it.
dnl This avoids the autoconf and automake tools being launched by make
AM_MAINTAINER_MODE

dnl Set the default install prefix to the installers home directory
dnl cygwin begin delete:
AC_PREFIX_DEFAULT(${HOME})
dnl cygwin end delete:
dnl cygwin replace: AC_PREFIX_DEFAULT(/usr)

dnl --------------------------------------------------------------------------
dnl Check for programs

AC_CHECK_PROG(have_pkg_config, [pkg-config], [yes], [no])
AM_CONDITIONAL(CppAD_PKG_CONFIG, test "$have_pkg_config" = "yes")

AC_CHECK_PROG(have_ar, [ar], [yes], [no])
AM_CONDITIONAL(CppAD_HAVE_AR, test "$have_ar" = "yes")
if test "$have_ar" = "no"; then
	AC_MSG_WARN(
	[cannot build any libraries because ar is missing, speed/* is not used] 
	)
fi

dnl ----------------------------------------------------------------------
AC_MSG_NOTICE([*** Check command line arguments that are longer used ****])

if test "$CPP_ERROR_WARN" != "" ; then
    AC_MSG_ERROR([The CPP_ERROR_WARN configure option is now CXX_FLAGS])
fi
dnl
AC_ARG_WITH(SpeedExample, AC_HELP_STRING(
	[--with-SpeedExample], [is not necessary, see install instructions.]),
	[SpeedExample="yes"], [SpeedExample="no"]
)
if test "$SpeedExample" = "yes" ; then
    AC_MSG_ERROR([--with-SpeedExample not necessary, see install instructions.])
fi
dnl
AC_ARG_WITH(profiling, AC_HELP_STRING(
	[--with-profiling], [is not necessary, see install instructions.]),
	[profiling="yes"], [profiling="no"]
)
if test "$profiling" = "yes" ; then
    AC_MSG_ERROR([--with-profiling not necessary, see install instructions.])
fi
dnl 
AC_ARG_WITH(Speed, AC_HELP_STRING(
	[--with-Speed], [is not necessary, see install instructions.]),
	[Speed="yes"], [Speed="no"]
)
if test "$Speed" = "yes" ; then
    AC_MSG_ERROR([--with-Speed not necessary, see install instructions.])
fi
dnl 
AC_ARG_WITH(Introduction, AC_HELP_STRING(
	[--with-Introduction], [is not necessary, see install instructions.]),
	[Introduction="yes"], [Introduction="no"]
)
if test "$Introduction" = "yes" ; then
    AC_MSG_ERROR([--with-Introduction not necessary, see install instructions.])
fi
dnl 
AC_ARG_WITH(Example, AC_HELP_STRING(
	[--with-Example], [is not necessary, see install instructions.]),
	[Example="yes"], [Example="no"]
)
if test "$Example" = "yes" ; then
    AC_MSG_ERROR([--with-Example not necessary, see install instructions.])
fi
dnl 
AC_ARG_WITH(TestMore, AC_HELP_STRING(
	[--with-TestMore], [is not necessary, see install instructions.]),
	[TestMore="yes"], [TestMore="no"]
)
if test "$TestMore" = "yes" ; then
    AC_MSG_ERROR([--with-TestMore not necessary, see install instructions.])
fi
dnl 
AC_ARG_WITH(PrintFor, AC_HELP_STRING(
	[--with-PrintFor], [is not necessary, see install instructions.]),
	[PrintFor="yes"], [PrintFor="no"]
)
if test "$PrintFor" = "yes" ; then
    AC_MSG_ERROR([--with-PrintFor not necessary, see install instructions.])
fi
dnl --------------------------------------------------------------------------
AC_MSG_NOTICE([******  Check command line arguments that are used ***********])
dnl the prefix directory corresponding to CppAD -------------------------
dnl The following seems to work but NONE is not in autoconf specifications
AC_MSG_CHECKING([--prefix])
if test "$prefix" = "NONE" ; then
	AC_MSG_RESULT([$HOME])
else
	AC_MSG_RESULT([$prefix])
fi

dnl Are we installing the documentation -----------------------------------
dnl cygwin begin delete:
AC_MSG_CHECKING([--with-Documentation])
AC_ARG_WITH(Documentation, 
	AC_HELP_STRING([--with-Documentation], [default is no]),
	[Documentation="yes"],
	[Documentation="no"]
)
AM_CONDITIONAL(CppAD_DOCUMENTATION, test "$Documentation" = "yes")
AC_MSG_RESULT([$Documentation])
dnl cygwin end delete:
dnl cygwin replace: AM_CONDITIONAL(CppAD_DOCUMENTATION, test "yes" = "yes")

dnl Are we using standard vectors ----------------------------------------
AC_MSG_CHECKING([--with-stdvector])
AC_ARG_WITH(stdvector, 
	AC_HELP_STRING([--with-stdvector], [default is no]),
	[stdvector="yes"],
	[stdvector="no"]
)
if test "$stdvector" = "yes" ; then
	AC_DEFINE(CPPAD_STDVECTOR, 1, [is CPPAD_TEST_VECTOR == std::vector])
else
	AC_DEFINE(CPPAD_STDVECTOR, 0, [is CPPAD_TEST_VECTOR == std::vector])
fi
AC_MSG_RESULT([$stdvector])

dnl The postfix directiory corresponding to CppAD ------------------------
AC_MSG_CHECKING([POSTFIX_DIR])
AC_ARG_VAR(POSTFIX_DIR, 
	[postfix directory for CppAD installation]
)
AM_CONDITIONAL(CppAD_POSTFIX, test "$POSTFIX_DIR" != "")
if test "$POSTFIX_DIR" != "" ; then
	AC_MSG_RESULT([$POSTFIX_DIR])
else
	AC_MSG_RESULT([no])
fi

dnl The prefix corresponding to the installation of Adolc ---------------
AC_MSG_CHECKING([ADOLC_DIR])
AC_ARG_VAR(ADOLC_DIR, 
	[value of configure prefix directory during Adolc install]
)
AM_CONDITIONAL(CppAD_ADOLC, test "$ADOLC_DIR" != "")
if test "$ADOLC_DIR" != "" ; then
	AC_MSG_RESULT([$ADOLC_DIR])
	if test "$have_ar" = "no"; then
		AC_MSG_ERROR([ar is missing and ADOLC_DIR is present])
	fi
else
	AC_MSG_RESULT([no])
fi

dnl The directory corresponding to the installation of FADBAD -----------
AC_MSG_CHECKING([FADBAD_DIR])
AC_ARG_VAR(FADBAD_DIR,
	[parent directory directly above FADBAD++ directory]
)
AM_CONDITIONAL(CppAD_FADBAD, test "$FADBAD_DIR" != "")
if test "$FADBAD_DIR" != "" ; then
	AC_MSG_RESULT([$FADBAD_DIR])
	if test "$have_ar" = "no"; then
		AC_MSG_ERROR([ar is missing and FADBAD_DIR is present])
	fi
else
	AC_MSG_RESULT([no])
fi

dnl The directory corresponding to the installation of SACADO -----------
AC_MSG_CHECKING([SACADO_DIR])
AC_ARG_VAR(SACADO_DIR,
	[value of the configure prefix directory during Sacado install]
)
AM_CONDITIONAL(CppAD_SACADO, test "$SACADO_DIR" != "")
if test "$SACADO_DIR" != "" ; then
	AC_MSG_RESULT([$SACADO_DIR])
	if test "$have_ar" = "no"; then
		AC_MSG_ERROR([ar is missing and SACADO_DIR is present])
	fi
else
	AC_MSG_RESULT([no])
fi

dnl The directory corresponding to the installation of IPOPT -----------
AC_MSG_CHECKING([IPOPT_DIR])
AC_ARG_VAR(IPOPT_DIR,
	[value of the configure prefix directory during Ipopt install]
)
AM_CONDITIONAL(CppAD_IPOPT_CPPAD, test "$IPOPT_DIR" != "")
if test "$IPOPT_DIR" != "" ; then
	AC_MSG_RESULT([$IPOPT_DIR])
	if test "$have_ar" = "no"; then
		AC_MSG_ERROR([ar is missing and IPOPT_DIR is present])
	fi
else
	AC_MSG_RESULT([no])
fi

dnl The directory corresponding to the installation of BOOST ------------
AC_MSG_CHECKING([BOOST_DIR])
AC_ARG_VAR(BOOST_DIR,
	[parent directory directly above boost directory]
)
AM_CONDITIONAL(CppAD_BOOSTVECTOR, test "$BOOST_DIR" != "")
if test "$BOOST_DIR" != "" ; then
	AC_DEFINE(CPPAD_BOOSTVECTOR, 1, 
	[is CPPAD_TEST_VECTOR = boost vector (overriden if _MSC_VER defined)]
	)
	AC_MSG_RESULT([$BOOST_DIR])
else
	AC_DEFINE(CPPAD_BOOSTVECTOR, 0, 
	[is CPPAD_TEST_VECTOR = boost vector (overriden if _MSC_VER defined)]
	)
	AC_MSG_RESULT([no])
fi

dnl The C++ compiler flags CXX_FLAGS -------------------------------------
AC_SUBST(CXXFLAGS, "")
#
AC_MSG_CHECKING([CXX_FLAGS])
AC_ARG_VAR(CXX_FLAGS,
	[ CXXFLAGS is ignored, use CXX_FLAGS for compiler flags]
)
if test "$CXX_FLAGS" != "" ; then
	AC_MSG_RESULT([$CXX_FLAGS]) 
	cxx_flags_fadbad=`echo "$CXX_FLAGS" | sed -e 's|-Wshadow||'`
else
	AC_MSG_RESULT([no])
	cxx_flags_fadbad=""
fi 
AC_SUBST(CXX_FLAGS_FADBAD, "$cxx_flags_fadbad")
AC_MSG_NOTICE([********** End Checking Command Line arguments ***************])

dnl Check which definition we are using for CPPAD_TEST_VECTOR
if test "$stdvector$BOOST_DIR" = "no" ; then
	AC_DEFINE(CPPAD_CPPADVECTOR, 1, [is CPPAD_TEST_VECTOR == CppAD::vector])
else 
	AC_DEFINE(CPPAD_CPPADVECTOR, 0, [is CPPAD_TEST_VECTOR == CppAD::vector])
fi

dnl the gettimeofday check automatically generates a yes / no configure msg
AC_CHECK_FUNC(
	gettimeofday,
	[gettimeofday="yes"],
	[gettimeofday="no"]
)
if test "$gettimeofday" = "yes" ; then
	AC_DEFINE(CPPAD_GETTIMEOFDAY, 1, 
	[does system support gettimeofday (overriden if _MSC_VER defined)]
	)
else
	AC_DEFINE(CPPAD_GETTIMEOFDAY, 0, 
	[does system support gettimeofday (overriden if _MSC_VER defined)]
	)
fi

dnl Run any macros required for proper operation of generated makefiles
dnl nostdinc: Do not define standard include directories in generated makefiles
AM_INIT_AUTOMAKE(nostdinc)

dnl Use LIBTOOL for cppad_ipopt ?
dnl AC_PROG_LIBTOOL

dnl Determine if ranlib is present and where it is if present (set RANLIB)
AC_PROG_RANLIB

dnl AC_PROG_CXX([compiler-search-list]) outputs CXX as C++ compiler to use
AC_PROG_CXX
AC_MSG_CHECKING([whether using Microsoft C++ compiler])
AM_CONDITIONAL(CppAD_MS_COMPILER, test "$CXX" == "cl" || test "$CXX" == "icl")
if test "$CXX" == "cl" || test "$CXX" == "icl"; then
	AC_MSG_RESULT([yes])
else
	AC_MSG_RESULT([no])
fi


dnl Have configure check source directory to see if cppad/CppAD.h is there
AC_CONFIG_SRCDIR(cppad/CppAD.h)

dnl Use config.h instead of make file command line arguments
AC_CONFIG_HEADER(cppad/config.h)

dnl AC_PROG_CP outputs CPP as command to run C preprocessor
AC_PROG_CPP

dnl Do nothing if complier supports inline, otherwise try to find a subsitute
dnl definition or, if cannot, define inline as empty
AC_C_INLINE

dnl determine FCLIBS, flags necessary for linking C++ with modern fortran
AC_FC_LIBRARY_LDFLAGS

dnl absolute path corresponding to top_builddig and top_srcdir in makefile.am
dnl (used by cppad-uninstalled.pc.in).
abs_top_builddir=`pwd`
AC_SUBST(ABS_TOP_BUILDDIR, "$abs_top_builddir")
abs_top_srcdir=`cd $srcdir ; pwd`
AC_SUBST(ABS_TOP_SRCDIR, "$abs_top_srcdir")
dnl --------------------------------------------------------------------------
dnl Check for C libraries

dnl check for pthread library
AC_SUBST(PTHREAD_LIB, "")
AC_CHECK_LIB(
	[pthread],
	[pthread_create],
	[PTHREAD_LIB="-lpthread"],
	[PTHREAD_LIB=""]
)

dnl check for dl library
AC_SUBST(DL_LIB, "")
AC_CHECK_LIB(
	[dl],
	[dlopen],
	[DL_LIB="-ldl"],
	[DL_LIB=""]
)

dnl --------------------------------------------------------------------------
dnl Determine link line for ipopt
AC_SUBST(CPPAD_IPOPT_LIBS, "-L $IPOPT_DIR/lib -lipopt")
if test "$have_pkg_config" == "yes"; then
	dnl set CPPAD_IPOPT_LIBS
	export PKG_CONFIG_PATH="$IPOPT_DIR/lib/pkgconfig"
	if pkg-config --libs ipopt >& /dev/null ; then
		CPPAD_IPOPT_LIBS=`pkg-config --libs ipopt`
	else
		dnl check for blas library
		AC_LANG_PUSH([Fortran])
		AC_CHECK_LIB(
			[blas],
			[ddot],
			[CPPAD_IPOPT_LIBS="$CPPAD_IPOPT_LIBS -lblas"],
		)
		dnl check for lapack library
		AC_CHECK_LIB(
			[lapack],
			[dgesv],
			[CPPAD_IPOPT_LIBS="$CPPAD_IPOPT_LIBS -llapack"],
		)
		AC_LANG_POP([Fortran])
	fi
else
	dnl check for blas library
	AC_LANG_PUSH([Fortran])
	AC_CHECK_LIB(
		[blas],
		[ddot],
		[CPPAD_IPOPT_LIBS="$CPPAD_IPOPT_LIBS -lblas"],
	)
	dnl check for lapack library
	AC_CHECK_LIB(
		[lapack],
		[dgesv],
		[CPPAD_IPOPT_LIBS="$CPPAD_IPOPT_LIBS -llapack"],
	)
	AC_LANG_POP([Fortran])
fi
AC_MSG_RESULT([cppad_ipopt_nlp libraries: $CPPAD_IPOPT_LIBS])
dnl -----------------------------------------------------------------------
dnl AC_CONFIG_FILES(file-list) for each file in the list, configure will 
dnl read file.in, do its substitutions, and create file
AC_CONFIG_FILES([ 
	cppad/configure.hpp
	doxyfile
	doc.omh
	example/test_one.sh
	omh/install_unix.omh
	omh/install_windows.omh
	pkgconfig/cppad.pc
	pkgconfig/cppad-uninstalled.pc
	test_more/test_one.sh

	makefile
	example/makefile 
	cppad_ipopt/src/makefile
	cppad_ipopt/example/makefile
	cppad_ipopt/speed/makefile
	cppad_ipopt/test/makefile
	introduction/get_started/makefile 
	introduction/exp_apx/makefile
	print_for/makefile
	speed/adolc/makefile
	speed/cppad/makefile 
	speed/double/makefile 
	speed/example/makefile
	speed/fadbad/makefile
	speed/profile/makefile
	speed/sacado/makefile
	speed/src/makefile
	test_more/makefile 
])
AC_OUTPUT_COMMANDS([chmod +x example/test_one.sh])
AC_OUTPUT_COMMANDS([chmod +x test_more/test_one.sh])
dnl END AC_CONFIG_FILES 
dnl the comment line above is used by ./new_stable.sh


dnl create all the requested output files
AC_OUTPUT
