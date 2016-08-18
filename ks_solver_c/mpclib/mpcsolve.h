/*
 * File: mpcsolve.h
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 18-Aug-2016 17:54:05
 */

#ifndef __MPCSOLVE_H__
#define __MPCSOLVE_H__

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "mpcsolve_outer_types.h"

/* Function Declarations */
extern void mpcsolve(const double H[1600], const double g[40], const double P
                     [1680], const double h[42], const double C[1200], const
                     double b[30], const double z0[40], const double A[9], const
                     double B[3], const double Fx[12], const double Fu[4], const
                     double Ff[6], const double Q[9], double b_R, const double
                     Qf[9], const double opts[7], const double Ps[800], const
                     double hs[20], const double Fxs[6], const double Fus[2],
                     double z[40], double info[4]);

#endif

/*
 * File trailer for mpcsolve.h
 *
 * [EOF]
 */
