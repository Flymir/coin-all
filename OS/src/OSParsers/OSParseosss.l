/* $Id: OSParseosss.l 4381 2011-11-09 09:10:35Z kmartin $ */
/** @file OSParseosss.l
 * 
 * @author  Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 *
 * \remarks
 * Copyright (C) 2005-2011, Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin,
 * Northwestern University, Dalhousie University and the University of Chicago.
 * All Rights Reserved.
 * This software is licensed under the Eclipse Public License. 
 * Please see the accompanying LICENSE file in root directory for terms.
 * 
 */

%{


#include <iostream>
#include "OSConfig.h"


#ifdef HAVE_CSTRING
# include <cstring>
#else
# ifdef HAVE_STRING_H
#  include <string.h>
# else
#  error "don't have header file for string"
# endif
#endif

#ifdef HAVE_CSTDIO
# include <cstdio>
#else
# ifdef HAVE_STDIO_H
#  include <stdio.h>
# else
#  error "don't have header file for stdio"
# endif
#endif
#include "OSErrorClass.h"
#include <sstream>   
#include "OSOptionsStruc.h" 


using std::cout;
using std::endl;
using std::ostringstream;

//#define PARSERDEBUG
#ifdef PARSERDEBUG
	#define YY_PRINT  printf("Found option:  %s\n", yytext);
#else     
	#define YY_PRINT  ;
#endif


#ifdef WIN_
  #define YY_NO_UNISTD_H
  #include <io.h>
  #include <process.h>
  #ifdef USE_OLD_UNISTD
     #include<sys/unistd.h>  
  #endif
#endif


#define YY_EXTRA_TYPE struct osOptionsStruc*

void setyyextra( osOptionsStruc *osoptions, void* scanner);

 /*
 * INPUTS:
 * -osil xxx.osil (file name on local machine of optimization instance, 
 *       this is "" by default, however if this remains "" a problem
 * 		 instance must be specified in the osol file)
 * -osol xxx.osol (file name on local machine of solver options, 
 *       default default value is "")
 * -osrl xxx.osrl (file name on local machine where the optimization 
 *       result is put, default is "")
 * -serviceLocation location URL (the URL  of the server that is called 
 *       remotely if the problem not solved locally, default is "")
 * -serviceMethod  (send, solve, kill, knock, getJobID, retrieve, 
 *       default value is solve)
 * -osplInput xxx.ospl  (Not used for now -- ignore)
 * -osplOutput xxx.ospl (Not used for now -- ignore)
 * -mps xxxx.mps (converts mps format to osil and has same effect as -osil)
 * -nl xxxx.nl (converts nl format to osil and has same effect as -osil)
 * -solver solverName (the name of the solver to be invoked)
 * -browser path location to browser e.g. 
 *       /Applications/Firefox.app/Contents/MacOS/firefox (default is "")
 * -config pathToConfigFile is the path to a configure file with the problem 
 * 	     parameters
 * -insList xxx.dat (used only for LINDO, file location on local 
 *       machine of LINDO instruction list)
*/


%}
%option nounput
%option reentrant
%option yylineno
%option prefix="osss"
%option noyywrap   



xmlwhitespace ([ \t\r\n])
optionValue ([-a-zA-Z./~:_0-9$\?+\\!@#&*()]+|\"[^"\n]*\")
serviceMethod (solve|send|kill|retrieve|knock|getJobID)
browserState (on|off)
%% 

{xmlwhitespace}*
  


(-config{xmlwhitespace}+{optionValue}) {
	YY_PRINT  
	//char *ch = strdup(yytext);
	char *ch = yytext;
	// move past -config
	ch+=7;
	for(; isspace(*ch); ch++);
	std::string str(  ch);
	yyextra->configFile = str;

}



(config{xmlwhitespace}+{optionValue}) {
	YY_PRINT  
	//char *ch = strdup(yytext);
	char *ch = yytext;
	// move past -config
	ch+=6;
	for(; isspace(*ch); ch++);
	std::string str(  ch);
	yyextra->configFile = str;

}


(config{xmlwhitespace}+) {
	YY_PRINT  
	//char *ch = strdup(yytext);
	char *ch = yytext;
	// move past -config
	ch+=6;
	for(; isspace(*ch); ch++);
	std::string str(  ch);
	yyextra->configFile = str;

}


(--help) {
	YY_PRINT  
	yyextra->invokeHelp = true;

}
			 
 (help) {
    YY_PRINT  
    yyextra->invokeHelp = true;
 
 }

(-h) {
	YY_PRINT
	yyextra->invokeHelp = true;
	
}


			 
(--printModel) {
    YY_PRINT  
    yyextra->printModel = true;
 
 }

			 
 (printModel) {
    YY_PRINT  
    yyextra->printModel = true;
 
 }

			 
 (version) {
	YY_PRINT  
	yyextra->writeVersion = true;
}


(--version) {
	YY_PRINT  
	yyextra->writeVersion = true;
}

(-v) {
	YY_PRINT 
	yyextra->writeVersion = true;
}
			 
			 
(quit) {
   YY_PRINT  
   yyextra->quit = true;
 
}


(-osil{xmlwhitespace}+{optionValue}) {
	//if(yyextra->osilFile == ""){
		YY_PRINT  
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -osil
		ch+=5;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->osilFile = str;
	//} 
}
			 

			 
			 
 (osil{xmlwhitespace}+{optionValue}) {
	// if(yyextra->osilFile == ""){
		 YY_PRINT  
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past osil
		 ch+=4;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->osilFile = str;
	// } 
 }
	 
			 
 (osil{xmlwhitespace}+) {
	// if(yyextra->osilFile == ""){
		 YY_PRINT  
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past osil
		 ch+=4;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->osilFile = str;
	// } 
 }

(-osrl{xmlwhitespace}+{optionValue}) {
	//if(yyextra->osrlFile == ""){
		YY_PRINT 
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -osrl
		ch+=5;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->osrlFile = str;
	//}  
}  
			 
 (osrl{xmlwhitespace}+{optionValue}) {
	 //if(yyextra->osrlFile == ""){
		 YY_PRINT 
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -osrl
		 ch+=4;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->osrlFile = str;
	 //}  
 } 			 
			 
			 
 (osrl{xmlwhitespace}+) {
	// if(yyextra->osrlFile == ""){
		 YY_PRINT 
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -osrl
		 ch+=4;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->osrlFile = str;
	// }  
 }			 
			 


(-insList{xmlwhitespace}+{optionValue}) {
	//if(yyextra->insListFile == ""){
		YY_PRINT
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -insList
		ch+=8;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->insListFile = str;
	//}  
}  
			 
			 
			 
 (insList{xmlwhitespace}+{optionValue}) {
	 //if(yyextra->insListFile == ""){
		 YY_PRINT
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -insList
		 ch+=7;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->insListFile = str;
	// }  
 }
			 
			 
 (insList{xmlwhitespace}+) {
	// if(yyextra->insListFile == ""){
		 YY_PRINT
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -insList
		 ch+=7;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->insListFile = str;
	// }  
 }
			 

(-osol{xmlwhitespace}+{optionValue}) {
	//if(yyextra->osolFile == ""){
		YY_PRINT 
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -osol
		ch+=5;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->osolFile = str;  
	//}
}
			 
			 
			 
(osol{xmlwhitespace}+{optionValue}) {
	//if(yyextra->osolFile == ""){
		 YY_PRINT 
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -osol
		 ch+=4;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->osolFile = str;  
	//}
}
			 
			 
 (osol{xmlwhitespace}+) {
	 //if(yyextra->osolFile == ""){
		 YY_PRINT 
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -osol
		 ch+=4;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->osolFile = str;  
	// }
 }



(-osplInput{xmlwhitespace}+{optionValue}) {
	//if(yyextra->osplInputFile == ""){
		YY_PRINT 
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -osplInput
		ch+=10;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->osplInputFile = str;  
	//}
}
			 
			 
 (osplInput{xmlwhitespace}+{optionValue}) {
	// if(yyextra->osplInputFile == ""){
		 YY_PRINT 
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -osplInput
		 ch+=9;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->osplInputFile = str;  
	// }
}
			 
 (osplInput{xmlwhitespace}+) {
	// if(yyextra->osplInputFile == ""){
		 YY_PRINT 
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -osplInput
		 ch+=9;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->osplInputFile = str;  
	// }
}

(-osplOutput{xmlwhitespace}+{optionValue}) {
	//if(yyextra->osplOutputFile == ""){
		YY_PRINT 
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -osplInput
		ch+=11;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->osplOutputFile = str;  
	//}
}

(-printRow{xmlwhitespace}+{optionValue}) {
	//if(yyextra->printRow == ""){
		YY_PRINT 
		//yyextra->printRowNumberAsString = strdup(yytext);
		yyextra->printRowNumberAsString =  yytext;
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -printRow
		ch+=8;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->printRowNumberAsString = str; 
	//}
}
			 
		 
 (printRow{xmlwhitespace}+{optionValue}) {
	//if(yyextra->printRow == ""){
		YY_PRINT 
		//yyextra->printRowNumberAsString = strdup(yytext);
		yyextra->printRowNumberAsString =  yytext;
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -printRow
		ch+=8;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->printRowNumberAsString = str; 
	//}
}
			 
 (printRow{xmlwhitespace}+) {
	//if(yyextra->printRow == ""){
		YY_PRINT 
		//yyextra->printRowNumberAsString = strdup(yytext);
		yyextra->printRowNumberAsString =  yytext;
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -printRow
		ch+=8;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->printRowNumberAsString = str; 
	//}
}

(-serviceMethod{xmlwhitespace}+{serviceMethod}) {
	//if(yyextra->serviceMethod == ""){
		YY_PRINT
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -serviceMethod
		ch+=14;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->serviceMethod = str; 
	//}
}
			 
 (serviceMethod{xmlwhitespace}+{serviceMethod}) {
	// if(yyextra->serviceMethod == ""){
		 YY_PRINT
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -serviceMethod
		 ch+=13;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->serviceMethod = str; 
	// }
}
			 
 (serviceMethod{xmlwhitespace}+) {
	// if(yyextra->serviceMethod == ""){
		 YY_PRINT
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -serviceMethod
		 ch+=13;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->serviceMethod = str; 
	// }
}

(-serviceLocation{xmlwhitespace}+{optionValue}) {
	//if(yyextra->serviceLocation == ""){
		YY_PRINT 
		//yyextra->serviceLocation = strdup(yytext);
		yyextra->serviceLocation =  yytext;
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -serviceLocation
		ch+=16;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->serviceLocation = str; 
	//}
}
			 
			 
			 
 (serviceLocation{xmlwhitespace}+{optionValue}) {
	// if(yyextra->serviceLocation == ""){
		 YY_PRINT 
		 //yyextra->serviceLocation = strdup(yytext);
		 yyextra->serviceLocation =  yytext;
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -serviceLocation
		 ch+=15;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->serviceLocation = str; 
	// }
}
			 
			 
 (serviceLocation{xmlwhitespace}+) {
	// if(yyextra->serviceLocation == ""){
		 YY_PRINT 
		 //yyextra->serviceLocation = strdup(yytext);
		 yyextra->serviceLocation =  yytext;
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -serviceLocation
		 ch+=15;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->serviceLocation = str; 
	// }
}
			 

(-mps{xmlwhitespace}+{optionValue}) {
	//if(yyextra->mpsFile == ""){
		YY_PRINT 
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -mps
		ch+=4;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->mpsFile = str; 
	//}
}
			 
			 
			 
			 
 (mps{xmlwhitespace}+{optionValue}) {
	// if(yyextra->mpsFile == ""){
		 YY_PRINT 
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -mps
		 ch+=3;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->mpsFile = str; 
	// }
}
			 
			 
			 
 (mps{xmlwhitespace}+) {
	// if(yyextra->mpsFile == ""){
		 YY_PRINT 
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -mps
		 ch+=3;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->mpsFile = str; 
	// }
}

(-nl{xmlwhitespace}+{optionValue}) {
	//if(yyextra->nlFile == ""){
		YY_PRINT
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -nl
		ch+=3;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->nlFile = str; 
	//} 
}
			 
			 
			 
			 
 (nl{xmlwhitespace}+{optionValue}) {
	// if(yyextra->nlFile == ""){
		 YY_PRINT
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -nl
		 ch+=2;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->nlFile = str; 
	// } 
}
			 
			 
 (nl{xmlwhitespace}+) {
	// if(yyextra->nlFile == ""){
		 YY_PRINT
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -nl
		 ch+=2;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->nlFile = str; 
	// } 
}
			 



(-dat{xmlwhitespace}+{optionValue}) {
	//if(yyextra->gamsControlFile == ""){
		YY_PRINT
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -dat
		ch+=4;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->gamsControlFile = str;
	//} 
}
			 
			 
			 
 (dat{xmlwhitespace}+{optionValue}) {
	// if(yyextra->gamsControlFile == ""){
		 YY_PRINT
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -dat
		 ch+=3;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->gamsControlFile = str;
	// } 
}
			 
 (dat{xmlwhitespace}+) {
	 //if(yyextra->gamsControlFile == ""){
		 YY_PRINT
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -dat
		 ch+=3;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->gamsControlFile = str;
	// } 
}

(-solver{xmlwhitespace}+{optionValue}) {
	//if(yyextra->solverName == ""){
		YY_PRINT 
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -solver
		ch+=7;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->solverName = str;
	//} 
}
			 
			 
 (solver{xmlwhitespace}+{optionValue}) {
	 //if(yyextra->solverName == ""){
		 YY_PRINT 
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -solver
		 ch+=6;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->solverName = str;
	// } 
}
			 
 (solver{xmlwhitespace}+) {
	// if(yyextra->solverName == ""){
		 YY_PRINT 
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -solver
		 ch+=6;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->solverName = str;
	// } 
}
 
(-browser{xmlwhitespace}+{optionValue}) {
	//if(yyextra->browser == ""){
		YY_PRINT  
		//char *ch = strdup(yytext);
		char *ch = yytext;
		// move past -browser
		ch+=8;
		for(; isspace(*ch); ch++);
		std::string str(  ch);
		yyextra->browser = str; 
	//}
}
			 
			 
 (browser{xmlwhitespace}+{optionValue}) {
	// if(yyextra->browser == ""){
		 YY_PRINT  
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -browser
		 ch+=7;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->browser = str; 
	// }
}
			 
			 
 (browser{xmlwhitespace}+) {
	// if(yyextra->browser == ""){
		 YY_PRINT  
		 //char *ch = strdup(yytext);
		 char *ch = yytext;
		 // move past -browser
		 ch+=7;
		 for(; isspace(*ch); ch++);
		 std::string str(  ch);
		 yyextra->browser = str; 
	// }
}

. {
	std::string error;
	std::ostringstream outStr;
	outStr << "encountered a spurious character in the lexer" << endl;
	outStr << "Please make sure your options are spelled correctly" << endl;
	outStr << "Type OSSolverService -h or OSSolverService --help for valid commands" << endl;
	outStr << "The first character is: ";
	outStr <<  yytext;
	outStr << endl;
	//outStr << "See line number: " << yylineno << endl;  
	error = outStr.str();
	throw ErrorClass( error);  
}
%%

void setyyextra(osOptionsStruc *osoptions, void* scanner){
	osssset_extra(osoptions, scanner);
}


