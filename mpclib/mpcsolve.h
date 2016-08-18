/*
 * File: mpcsolve.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 18-Aug-2016 10:55:52
 */

#ifndef __MPCSOLVE_H__
#define __MPCSOLVE_H__

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
extern void mpcsolve(const double H[1600], const double g[40], const double P
                     [960], const double h[24], const double C[1280], const
                     double b[32], const double z0[40], const double A[9], const
                     double B[3], const double Fx[6], const double Fu[2], const
                     double Ff[12], const double Q[9], double b_R, const double
                     Qf[9], const double opts[6], const double Ps[1600], const
                     double hs[40], const double Ef[6], const double Fxs[12],
                     const double Fus[4], double z[40], double info[4]);

#endif

/*
 * File trailer for mpcsolve.h
 *
 * [EOF]
 */
