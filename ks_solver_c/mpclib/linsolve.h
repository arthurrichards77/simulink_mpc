/*
 * File: linsolve.h
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 18-Aug-2016 17:54:05
 */

#ifndef __LINSOLVE_H__
#define __LINSOLVE_H__

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "mpcsolve_outer_types.h"

/* Function Declarations */
extern void b_linsolve(const double A[9], const double B[3], double C[3]);
extern void c_linsolve(const double A[9], const double B[3], double C[3]);
extern void linsolve(const double A[9], const double B[9], double C[9]);

#endif

/*
 * File trailer for linsolve.h
 *
 * [EOF]
 */
