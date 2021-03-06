/* Copyright (C) 2008, 2011 GAMS Development and others
 All Rights Reserved.
 This code is published under the Eclipse Public License.

 $Id: HSLLoader.c 2049 2011-09-20 09:58:03Z stefan $

 Author: Stefan Vigerske
*/

#include "IpoptConfig.h"
#include "LibraryHandler.h"
#include "HSLLoader.h"

#ifdef COIN_HAS_HSL
#include "CoinHslConfig.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include "hsl_ma86d.h"

#define HSLLIBNAME "libhsl." SHAREDLIBEXT

/* Type of Fortran integer translated into C */
typedef FORTRAN_INTEGER_TYPE ipfint;

static soHandle_t HSL_handle=NULL;

void LSL_lateHSLLoad();

typedef void (*voidfun)(void);

voidfun LSL_loadSym (soHandle_t h, const char *symName, char *msgBuf, int msgLen);


typedef void (*ma27id_t)(ipfint* ICNTL, double* CNTL);
typedef void (*ma27ad_t)(ipfint *N, ipfint *NZ, const ipfint *IRN, const ipfint* ICN,
			 ipfint *IW, ipfint* LIW, ipfint* IKEEP, ipfint *IW1,
			 ipfint* NSTEPS, ipfint* IFLAG, ipfint* ICNTL,
			 double* CNTL, ipfint *INFO, double* OPS);
typedef void (*ma27bd_t)(ipfint *N, ipfint *NZ, const ipfint *IRN, const ipfint* ICN,
			 double* A, ipfint* LA, ipfint* IW, ipfint* LIW,
			 ipfint* IKEEP, ipfint* NSTEPS, ipfint* MAXFRT,
			 ipfint* IW1, ipfint* ICNTL, double* CNTL,
			 ipfint* INFO);
typedef void (*ma27cd_t)(ipfint *N, double* A, ipfint* LA, ipfint* IW,
			 ipfint* LIW, double* W, ipfint* MAXFRT,
			 double* RHS, ipfint* IW1, ipfint* NSTEPS,
			 ipfint* ICNTL, double* CNTL);

typedef void (*ma28ad_t)(void* nsize, void* nz, void* rw, void* licn, void* iw,
			 void* lirn, void* iw2, void* pivtol, void* iw3, void* iw4, void* rw2, void* iflag);

typedef void (*ma57id_t) (double    *cntl, ipfint    *icntl);

typedef void (*ma57ad_t) (
    ipfint    *n,     /* Order of matrix. */
    ipfint    *ne,            /* Number of entries. */
    const ipfint    *irn,       /* Matrix nonzero row structure */
    const ipfint    *jcn,       /* Matrix nonzero column structure */
    ipfint    *lkeep,     /* Workspace for the pivot order of lenght 3*n */
    ipfint    *keep,      /* Workspace for the pivot order of lenght 3*n */
    /* Automatically iflag = 0; ikeep pivot order iflag = 1 */
    ipfint    *iwork,     /* Integer work space. */
    ipfint    *icntl,     /* Integer Control parameter of length 30*/
    ipfint    *info,      /* Statistical Information; Integer array of length 20 */
    double    *rinfo);    /* Double Control parameter of length 5 */

typedef void (*ma57bd_t) (
    ipfint    *n,     /* Order of matrix. */
    ipfint    *ne,            /* Number of entries. */
    double    *a,     /* Numerical values. */
    double    *fact,      /* Entries of factors. */
    ipfint    *lfact,     /* Length of array `fact'. */
    ipfint    *ifact,     /* Indexing info for factors. */
    ipfint    *lifact,    /* Length of array `ifact'. */
    ipfint    *lkeep,     /* Length of array `keep'. */
    ipfint    *keep,      /* Integer array. */
    ipfint    *iwork,     /* Workspace of length `n'. */
    ipfint    *icntl,     /* Integer Control parameter of length 20. */
    double    *cntl,      /* Double Control parameter of length 5. */
    ipfint    *info,      /* Statistical Information; Integer array of length 40. */
    double    *rinfo);    /* Statistical Information; Real array of length 20. */

typedef void (*ma57cd_t) (
    ipfint    *job,       /* Solution job.  Solve for... */
    ipfint    *n,         /* Order of matrix. */
    double    *fact,      /* Entries of factors. */
    ipfint    *lfact,     /* Length of array `fact'. */
    ipfint    *ifact,     /* Indexing info for factors. */
    ipfint    *lifact,    /* Length of array `ifact'. */
    ipfint    *nrhs,      /* Number of right hand sides. */
    double    *rhs,       /* Numerical Values. */
    ipfint    *lrhs,      /* Leading dimensions of `rhs'. */
    double    *work,      /* Real workspace. */
    ipfint    *lwork,     /* Length of `work', >= N*NRHS. */
    ipfint    *iwork,     /* Integer array of length `n'. */
    ipfint    *icntl,     /* Integer Control parameter array of length 20. */
    ipfint    *info);     /* Statistical Information; Integer array of length 40. */

typedef void (*ma57ed_t) (
    ipfint    *n,
    ipfint    *ic,        /* 0: copy real array.  >=1:  copy integer array. */
    ipfint    *keep,
    double    *fact,
    ipfint    *lfact,
    double    *newfac,
    ipfint    *lnew,
    ipfint    *ifact,
    ipfint    *lifact,
    ipfint    *newifc,
    ipfint    *linew,
    ipfint    *info);

typedef void (*mc19ad_t)(ipfint *N, ipfint *NZ, double* A, ipfint *IRN, ipfint* ICN, float* R, float* C, float* W);

typedef void (*ma86_default_control_t)(struct ma86_control *control);
typedef void (*ma86_analyse_t)(const int n, const int ptr[], const int row[],
   int order[], void **keep, const struct ma86_control *control,
   struct ma86_info *info);
typedef void (*ma86_factor_t)(const int n, const int ptr[], const int row[],
   const ma86pkgtype_d_ val[], const int order[], void **keep,
   const struct ma86_control *control, struct ma86_info *info,
   const ma86pkgtype_d_ scale[]);
typedef void (*ma86_factor_solve_t)(const int n, const int ptr[],
   const int row[], const ma86pkgtype_d_ val[], const int order[], void **keep,
   const struct ma86_control *control, struct ma86_info *info, const int nrhs,
   const int ldx, ma86pkgtype_d_ x[], const ma86pkgtype_d_ scale[]);
typedef void (*ma86_solve_t)(const int job, const int nrhs, const int ldx,
   ma86pkgtype_d_ *x, const int order[], void **keep,
   const struct ma86_control *control, struct ma86_info *info,
   const ma86pkgtype_d_ scale[]);
typedef void (*ma86_finalise_t)(void **keep,
   const struct ma86_control *control);

#ifndef COINHSL_HAS_MA27
static ma27id_t func_ma27id=NULL;
static ma27ad_t func_ma27ad=NULL;
static ma27bd_t func_ma27bd=NULL;
static ma27cd_t func_ma27cd=NULL;

void F77_FUNC(ma27id,MA27ID)(ipfint* ICNTL, double* CNTL)
{
  if (func_ma27id==NULL) LSL_lateHSLLoad();
  if (func_ma27id==NULL) {
    fprintf(stderr, "HSL routine MA27ID not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma27id(ICNTL, CNTL);
}

void F77_FUNC(ma27ad,MA27AD)(ipfint *N, ipfint *NZ, const ipfint *IRN, const ipfint* ICN,
                             ipfint *IW, ipfint* LIW, ipfint* IKEEP, ipfint *IW1,
                             ipfint* NSTEPS, ipfint* IFLAG, ipfint* ICNTL,
                             double* CNTL, ipfint *INFO, double* OPS) {
  if (func_ma27ad==NULL) LSL_lateHSLLoad();
  if (func_ma27ad==NULL) {
    fprintf(stderr, "HSL routine MA27AD not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma27ad(N, NZ, IRN, ICN, IW, LIW, IKEEP, IW1, NSTEPS, IFLAG, ICNTL, CNTL, INFO, OPS);	
}

void F77_FUNC(ma27bd,MA27BD)(ipfint *N, ipfint *NZ, const ipfint *IRN, const ipfint* ICN,
                             double* A, ipfint* LA, ipfint* IW, ipfint* LIW,
                             ipfint* IKEEP, ipfint* NSTEPS, ipfint* MAXFRT,
                             ipfint* IW1, ipfint* ICNTL, double* CNTL,
                             ipfint* INFO) {
  if (func_ma27bd==NULL) LSL_lateHSLLoad();
  if (func_ma27bd==NULL) {
    fprintf(stderr, "HSL routine MA27BD not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma27bd(N, NZ, IRN, ICN, A, LA, IW, LIW, IKEEP, NSTEPS, MAXFRT, IW1, ICNTL, CNTL, INFO);
}

void F77_FUNC(ma27cd,MA27CD)(ipfint *N, double* A, ipfint* LA, ipfint* IW,
                             ipfint* LIW, double* W, ipfint* MAXFRT,
                             double* RHS, ipfint* IW1, ipfint* NSTEPS,
                             ipfint* ICNTL, double* CNTL) {
  if (func_ma27cd==NULL) LSL_lateHSLLoad();
  if (func_ma27cd==NULL) {
    fprintf(stderr, "HSL routine MA27CD not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma27cd(N, A, LA, IW, LIW, W, MAXFRT, RHS, IW1, NSTEPS, ICNTL, CNTL);
}

#endif

#ifndef COINHSL_HAS_MA28

static ma28ad_t func_ma28ad=NULL;

void F77_FUNC(ma28ad,MA28AD)(void* nsize, void* nz, void* rw, void* licn, void* iw,
		                         void* lirn, void* iw2, void* pivtol, void* iw3, void* iw4, void* rw2, void* iflag) {
  if (func_ma28ad==NULL) LSL_lateHSLLoad();
  if (func_ma28ad==NULL) {
    fprintf(stderr, "HSL routine MA28AD not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma28ad(nsize, nz, rw, licn, iw, lirn, iw2, pivtol, iw3, iw4, rw2, iflag);
}
#endif

#ifndef COINHSL_HAS_MA57

static ma57id_t func_ma57id=NULL;
static ma57ad_t func_ma57ad=NULL;
static ma57bd_t func_ma57bd=NULL;
static ma57cd_t func_ma57cd=NULL;
static ma57ed_t func_ma57ed=NULL;

void  F77_FUNC (ma57id, MA57ID) (double    *cntl,  ipfint    *icntl) {
  if (func_ma57id==NULL) LSL_lateHSLLoad();
  if (func_ma57id==NULL) {
    fprintf(stderr, "HSL routine MA57ID not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma57id(cntl, icntl);
}

void  F77_FUNC (ma57ad, MA57AD) (
    ipfint    *n,     /* Order of matrix. */
    ipfint    *ne,            /* Number of entries. */
    const ipfint    *irn,       /* Matrix nonzero row structure */
    const ipfint    *jcn,       /* Matrix nonzero column structure */
    ipfint    *lkeep,     /* Workspace for the pivot order of lenght 3*n */
    ipfint    *keep,      /* Workspace for the pivot order of lenght 3*n */
    ipfint    *iwork,     /* Integer work space. */
    ipfint    *icntl,     /* Integer Control parameter of length 30*/
    ipfint    *info,      /* Statistical Information; Integer array of length 20 */
    double    *rinfo)    /* Double Control parameter of length 5 */ {
  if (func_ma57ad==NULL) LSL_lateHSLLoad();
  if (func_ma57ad==NULL) {
    fprintf(stderr, "HSL routine MA57AD not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma57ad(n, ne, irn, jcn, lkeep, keep, iwork, icntl, info, rinfo);
}

void  F77_FUNC (ma57bd, MA57BD) (
    ipfint    *n,     /* Order of matrix. */
    ipfint    *ne,            /* Number of entries. */
    double    *a,     /* Numerical values. */
    double    *fact,      /* Entries of factors. */
    ipfint    *lfact,     /* Length of array `fact'. */
    ipfint    *ifact,     /* Indexing info for factors. */
    ipfint    *lifact,    /* Length of array `ifact'. */
    ipfint    *lkeep,     /* Length of array `keep'. */
    ipfint    *keep,      /* Integer array. */
    ipfint    *iwork,     /* Workspace of length `n'. */
    ipfint    *icntl,     /* Integer Control parameter of length 20. */
    double    *cntl,      /* Double Control parameter of length 5. */
    ipfint    *info,      /* Statistical Information; Integer array of length 40. */
    double    *rinfo)    /* Statistical Information; Real array of length 20. */ {
  if (func_ma57bd==NULL) LSL_lateHSLLoad();
  if (func_ma57bd==NULL) {
    fprintf(stderr, "HSL routine MA57BD not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma57bd(n, ne, a, fact, lfact, ifact, lifact, lkeep, keep, iwork, icntl, cntl, info, rinfo);	
}

void  F77_FUNC (ma57cd, MA57CD) (
    ipfint    *job,       /* Solution job.  Solve for... */
    ipfint    *n,         /* Order of matrix. */
    double    *fact,      /* Entries of factors. */
    ipfint    *lfact,     /* Length of array `fact'. */
    ipfint    *ifact,     /* Indexing info for factors. */
    ipfint    *lifact,    /* Length of array `ifact'. */
    ipfint    *nrhs,      /* Number of right hand sides. */
    double    *rhs,       /* Numerical Values. */
    ipfint    *lrhs,      /* Leading dimensions of `rhs'. */
    double    *work,      /* Real workspace. */
    ipfint    *lwork,     /* Length of `work', >= N*NRHS. */
    ipfint    *iwork,     /* Integer array of length `n'. */
    ipfint    *icntl,     /* Integer Control parameter array of length 20. */
    ipfint    *info)     /* Statistical Information; Integer array of length 40. */ {
  if (func_ma57cd==NULL) LSL_lateHSLLoad();
  if (func_ma57cd==NULL) {
    fprintf(stderr, "HSL routine MA57CD not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma57cd(job, n, fact, lfact, ifact, lifact, nrhs, rhs, lrhs, work, lwork, iwork, icntl, info);    
}

void  F77_FUNC (ma57ed, MA57ED) (
    ipfint    *n,
    ipfint    *ic,        /* 0: copy real array.  >=1:  copy integer array. */
    ipfint    *keep,
    double    *fact,
    ipfint    *lfact,
    double    *newfac,
    ipfint    *lnew,
    ipfint    *ifact,
    ipfint    *lifact,
    ipfint    *newifc,
    ipfint    *linew,
    ipfint    *info) {
  if (func_ma57ed==NULL) LSL_lateHSLLoad();
  if (func_ma57ed==NULL) {
    fprintf(stderr, "HSL routine MA57ED not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma57ed(n, ic, keep, fact, lfact, newfac, lnew, ifact, lifact, newifc, linew, info);
}
#endif

#ifndef COINHSL_HAS_MA86

static ma86_default_control_t func_ma86_default_control=NULL;
static ma86_analyse_t func_ma86_analyse=NULL;
static ma86_factor_t func_ma86_factor=NULL;
static ma86_factor_solve_t func_ma86_factor_solve=NULL;
static ma86_solve_t func_ma86_solve=NULL;
static ma86_finalise_t func_ma86_finalise=NULL;

void ma86_default_control(struct ma86_control *control) {
  if (func_ma86_default_control==NULL) LSL_lateHSLLoad();
  if (func_ma86_default_control==NULL) {
    fprintf(stderr, "HSL routine ma86_default_control not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma86_default_control(control);
}

void ma86_analyse(const int n, const int ptr[], const int row[], int order[],
      void **keep, const struct ma86_control *control, struct ma86_info *info) {
  if (func_ma86_analyse==NULL) LSL_lateHSLLoad();
  if (func_ma86_analyse==NULL) {
    fprintf(stderr, "HSL routine ma86_analyse not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma86_analyse(n, ptr, row, order, keep, control, info);
}

void ma86_factor(const int n, const int ptr[], const int row[],
      const ma86pkgtype_d_ val[], const int order[], void **keep,
      const struct ma86_control *control, struct ma86_info *info,
      const ma86pkgtype_d_ scale[]) {
  if (func_ma86_factor==NULL) LSL_lateHSLLoad();
  if (func_ma86_factor==NULL) {
    fprintf(stderr, "HSL routine ma86_factor not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma86_factor(n, ptr, row, val, order, keep, control, info, scale);
}

void ma86_factor_solve(const int n, const int ptr[], const int row[],
      const ma86pkgtype_d_ val[], const int order[], void **keep,
      const struct ma86_control *control, struct ma86_info *info,
      const int nrhs, const int ldx, ma86pkgtype_d_ x[],
      const ma86pkgtype_d_ scale[]) {
  if (func_ma86_factor_solve==NULL) LSL_lateHSLLoad();
  if (func_ma86_factor_solve==NULL) {
    fprintf(stderr, "HSL routine ma86_factor_solve not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma86_factor_solve(n, ptr, row, val, order, keep, control, info, nrhs,
      ldx, x, scale);
}

void ma86_solve(const int job, const int nrhs, const int ldx, ma86pkgtype_d_ *x,
      const int order[], void **keep, const struct ma86_control *control,
      struct ma86_info *info, const ma86pkgtype_d_ scale[]) {
  if (func_ma86_solve==NULL) LSL_lateHSLLoad();
  if (func_ma86_solve==NULL) {
    fprintf(stderr, "HSL routine ma86_solve not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma86_solve(job, nrhs, ldx, x, order, keep, control, info, scale);
}

void ma86_finalise(void **keep, const struct ma86_control *control) {
  if (func_ma86_finalise==NULL) LSL_lateHSLLoad();
  if (func_ma86_finalise==NULL) {
    fprintf(stderr, "HSL routine ma86_finalise not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_ma86_finalise(keep, control);
}
#endif

#ifndef COINHSL_HAS_MC19

static mc19ad_t func_mc19ad=NULL;

void F77_FUNC(mc19ad,MC19AD)(ipfint *N, ipfint *NZ, double* A, ipfint *IRN,
                             ipfint* ICN, float* R, float* C, float* W) {
  if (func_mc19ad==NULL) LSL_lateHSLLoad();
  if (func_mc19ad==NULL) {
    fprintf(stderr, "HSL routine MC19AD not found in " HSLLIBNAME ".\nAbort...\n");
    exit(EXIT_FAILURE);
  }
  func_mc19ad(N, NZ, A, IRN, ICN, R, C, W);
}
#endif

int LSL_loadHSL(const char* libname, char* msgbuf, int msglen) {
  /* load HSL library */
  if (libname) {
    HSL_handle=LSL_loadLib(libname, msgbuf, msglen);
  } else { /* try a default library name */
    HSL_handle=LSL_loadLib(HSLLIBNAME, msgbuf, msglen); 
  }
  if (HSL_handle==NULL)
    return 1;
	
  /* load HSL functions */
#ifndef COINHSL_HAS_MA27
  func_ma27id=(ma27id_t)LSL_loadSym(HSL_handle, "ma27id", msgbuf, msglen);
  func_ma27ad=(ma27ad_t)LSL_loadSym(HSL_handle, "ma27ad", msgbuf, msglen);
  func_ma27bd=(ma27bd_t)LSL_loadSym(HSL_handle, "ma27bd", msgbuf, msglen);
  func_ma27cd=(ma27cd_t)LSL_loadSym(HSL_handle, "ma27cd", msgbuf, msglen);
#endif

#ifndef COINHSL_HAS_MA28
  func_ma28ad=(ma28ad_t)LSL_loadSym(HSL_handle, "ma28ad", msgbuf, msglen);
#endif

#ifndef COINHSL_HAS_MA57
  func_ma57id=(ma57id_t)LSL_loadSym(HSL_handle, "ma57id", msgbuf, msglen);
  func_ma57ad=(ma57ad_t)LSL_loadSym(HSL_handle, "ma57ad", msgbuf, msglen);
  func_ma57bd=(ma57bd_t)LSL_loadSym(HSL_handle, "ma57bd", msgbuf, msglen);
  func_ma57cd=(ma57cd_t)LSL_loadSym(HSL_handle, "ma57cd", msgbuf, msglen);
  func_ma57ed=(ma57ed_t)LSL_loadSym(HSL_handle, "ma57ed", msgbuf, msglen);
#endif

#ifndef COINHSL_HAS_MA86
  func_ma86_default_control=(ma86_default_control_t)LSL_loadSym(HSL_handle, "ma86_default_control_d", msgbuf, msglen);
  func_ma86_analyse=(ma86_analyse_t)LSL_loadSym(HSL_handle, "ma86_analyse_d", msgbuf, msglen);
  func_ma86_factor=(ma86_factor_t)LSL_loadSym(HSL_handle, "ma86_factor_d", msgbuf, msglen);
  func_ma86_factor_solve=(ma86_factor_solve_t)LSL_loadSym(HSL_handle, "ma86_factor_solve_d", msgbuf, msglen);
  func_ma86_solve=(ma86_solve_t)LSL_loadSym(HSL_handle, "ma86_solve_d", msgbuf, msglen);
  func_ma86_finalise=(ma86_finalise_t)LSL_loadSym(HSL_handle, "ma86_finalise_d", msgbuf, msglen);
#endif

#ifndef COINHSL_HAS_MC19
  func_mc19ad=(mc19ad_t)LSL_loadSym(HSL_handle, "mc19ad", msgbuf, msglen);
#endif

  return 0;
}

int LSL_unloadHSL() {
  int rc;
	
  if (HSL_handle==NULL)
    return 0;

  rc = LSL_unloadLib(HSL_handle);
  HSL_handle=NULL;
	
#ifndef COINHSL_HAS_MA27
  func_ma27id=NULL;
  func_ma27ad=NULL;
  func_ma27bd=NULL;
  func_ma27cd=NULL;
#endif

#ifndef COINHSL_HAS_MA28
  func_ma28ad=NULL;
#endif

#ifndef COINHSL_HAS_MA57
  func_ma57id=NULL;
  func_ma57ad=NULL;
  func_ma57bd=NULL;
  func_ma57cd=NULL;
  func_ma57ed=NULL;
#endif

#ifndef COINHSL_HAS_MA86
  func_ma86_default_control=NULL;
  func_ma86_analyse=NULL;
  func_ma86_factor=NULL;
  func_ma86_factor_solve=NULL;
  func_ma86_solve=NULL;
  func_ma86_finalise=NULL;
#endif

#ifndef COINHSL_HAS_MC19
  func_mc19ad=NULL;
#endif

  return rc;
}

int LSL_isHSLLoaded() {
  return HSL_handle!=NULL;
}

int LSL_isMA27available() {
#ifndef COINHSL_HAS_MA27
	return HSL_handle!=NULL && func_ma27id!=NULL && func_ma27ad!=NULL && func_ma27bd!=NULL && func_ma27cd!=NULL;
#else
	return 0;
#endif
}

int LSL_isMA28available() {
#ifndef COINHSL_HAS_MA28
	return HSL_handle!=NULL && func_ma28ad!=NULL;
#else
	return 0;
#endif
}

int LSL_isMA57available() {
#ifndef COINHSL_HAS_MA57
	return HSL_handle!=NULL && func_ma57id!=NULL && func_ma57ad!=NULL && func_ma57bd!=NULL && func_ma57cd!=NULL && func_ma57ed!=NULL;
#else
	return 0;
#endif
}

int LSL_isMA86available() {
#ifndef COINHSL_HAS_MA86
	return HSL_handle!=NULL && func_ma86_default_control!=NULL && func_ma86_analyse!=NULL && func_ma86_factor!=NULL && func_ma86_factor_solve!=NULL && func_ma86_solve!=NULL && func_ma86_finalise!=NULL;
#else
	return 0;
#endif
}


int LSL_isMC19available() {
#ifndef COINHSL_HAS_MC19
	return HSL_handle!=NULL && func_mc19ad!=NULL;
#else
	return 0;
#endif
}

void LSL_lateHSLLoad() {
  char buffer[512];
  int rc;

  sprintf(buffer, "Error unknown.");
  rc = LSL_loadHSL(NULL, buffer, 512);
  if (rc!=0) {
    fprintf(stderr, "Error loading HSL dynamic library " HSLLIBNAME ": %s\nThis executable was not compiled with the HSL routine you specified.\nYou need to compile the HSL dynamic library to use deferred loading of the linear solver.\nAbort...\n", buffer);
    exit(EXIT_FAILURE);
  }
}

char* LSL_HSLLibraryName() {
  static char name[] = HSLLIBNAME;
  return name;
}
