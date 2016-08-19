/*
 * File: diag.h
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 18-Aug-2016 17:54:05
 */

#ifndef __DIAG_H__
#define __DIAG_H__

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "mpcsolve_outer_types.h"

/* Function Declarations */
extern void b_diag(const double v[40], double d[1600]);
extern void c_diag(const double v[4], double d[16]);
extern void d_diag(const double v[2], double d[4]);
extern void diag(const double v[1600], double d[40]);

#endif

/*
 * File trailer for diag.h
 *
 * [EOF]
 */
