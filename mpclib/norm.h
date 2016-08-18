/*
 * File: norm.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 18-Aug-2016 10:55:52
 */

#ifndef __NORM_H__
#define __NORM_H__

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
extern double b_norm(const double x[40]);
extern double c_norm(const double x[2]);
extern double d_norm(const double x[1600]);
extern double e_norm(const double x[1024]);
extern void eml_xrotg(double *b_a, double *b, double *c, double *s);
extern double norm(const double x[32]);

#endif

/*
 * File trailer for norm.h
 *
 * [EOF]
 */
