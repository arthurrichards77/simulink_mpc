/*
 * File: linsolve.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 18-Aug-2016 10:55:52
 */

#ifndef __LINSOLVE_H__
#define __LINSOLVE_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "mpcsolve_outer_types.h"

/* Function Declarations */
extern void b_linsolve(const double A[9], const double B[6], double C[6]);
extern void c_linsolve(const double A[9], const double B[3], double C[3]);
extern void d_linsolve(const double A[4], const double B[2], double C[2]);
extern void e_linsolve(const double A[4], const double B[2], double C[2]);
extern void f_linsolve(const double A[9], const double B[3], double C[3]);
extern void linsolve(const double A[9], const double B[9], double C[9]);

#endif

/*
 * File trailer for linsolve.h
 *
 * [EOF]
 */
