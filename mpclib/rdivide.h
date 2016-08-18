/*
 * File: rdivide.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 18-Aug-2016 10:55:52
 */

#ifndef __RDIVIDE_H__
#define __RDIVIDE_H__

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
extern void b_rdivide(const double x[40], const double y[40], double z[40]);
extern void c_rdivide(double x, const double y[40], double z[40]);
extern void rdivide(double x, const double y[24], double z[24]);

#endif

/*
 * File trailer for rdivide.h
 *
 * [EOF]
 */
