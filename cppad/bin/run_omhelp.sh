#! /bin/bash -e
# $Id: run_omhelp.sh 1766 2010-12-31 17:47:57Z bradbell $
# -----------------------------------------------------------------------------
# CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-10 Bradley M. Bell
#
# CppAD is distributed under multiple licenses. This distribution is under
# the terms of the
#                     Common Public License Version 1.0.
#
# A copy of this license is included in the COPYING file of this distribution.
# Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
# -----------------------------------------------------------------------------
if [ $0 != "bin/run_omhelp.sh" ]
then
	echo "bin/run_omhelp.sh: must be executed from its parent directory"
	exit 1
fi
# -----------------------------------------------------------------------------
#
if [ "$1" != "doc" ] && [ "$1" != "dev" ]
then
	echo "usage: bin/run_omhelp.sh (doc|dev)  (htm|xml|clean) [printable]"
	exit 1
fi
if [ "$2" != "htm" ] && [ "$2" != "xml" ] && [ "$2" != "clean" ]
then
	echo "usage: bin/run_omhelp.sh (doc|dev)  (htm|xml|clean) [printable]"
	exit 1
fi
if [ "$3" != "" ] && [ "$3" != "printable" ]
then
	echo "usage: bin/run_omhelp.sh (doc|dev)  (htm|xml|clean) [printable]"
	exit 1
fi
if [ "$2" == "clean" ]
then
	for target in dev doc
	do
		if [ "$1" == "$target" ]
		then
			echo "rm -rf $target"
			      rm -rf $target
			exit 0
		fi
	done
fi
target="$1"
ext="$2"
#
echo "Building $target/*.$ext $3"
if [ ! -e $target ]
then
	echo "mkdir $target"
	      mkdir $target
fi 
echo "cd $target"
if !  cd $target
then
	echo "Cannot change into ./$target directory"
	echo "Execute bin/run_omhelp.sh $target clean first"
	exit 1
fi
cmd="omhelp ../$target.omh -noframe -debug -l http://www.coin-or.org/CppAD/"
if [ "$ext" == "xml" ]
then
	cmd="$cmd -xml"
fi
if [ "$3" == "printable" ]
then
	cmd="$cmd -printable"
fi
echo "$cmd > ../omhelp.$target.$ext.log"
if !  $cmd > ../omhelp.$target.$ext.log
then
	grep "^OMhelp Error:" ../omhelp.$target.$ext.log
	echo "OMhelp could not build $target/*.$ext documentation."
	echo "See the complete error message in omhelp.$target.$ext.log"
	exit 1
fi
if grep "^OMhelp Warning:" ../omhelp.$target.$ext.log
then
	echo "See the complete warning messages in omhelp.$target.$ext.log."
	exit 1
fi
exit 0
