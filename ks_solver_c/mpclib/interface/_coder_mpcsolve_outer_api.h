/* 
 * File: _coder_mpcsolve_outer_api.h 
 *  
 * MATLAB Coder version            : 2.6 
 * C/C++ source code generated on  : 18-Aug-2016 17:54:05 
 */

#ifndef ___CODER_MPCSOLVE_OUTER_API_H__
#define ___CODER_MPCSOLVE_OUTER_API_H__
/* Include files */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Function Declarations */
extern void mpcsolve_outer_initialize(emlrtContext *aContext);
extern void mpcsolve_outer_terminate(void);
extern void mpcsolve_outer_atexit(void);
extern void mpcsolve_outer_api(const mxArray *prhs[28], const mxArray *plhs[2]);
extern void mpcsolve_outer(double x[3], double xt[3], double d[3], double z0[40], double z[40], double info[4]);
extern void mpcsolve_outer_xil_terminate(void);

#endif
/* 
 * File trailer for _coder_mpcsolve_outer_api.h 
 *  
 * [EOF] 
 */
