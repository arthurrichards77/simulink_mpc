/*
 * File: blkdiag.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 18-Aug-2016 10:55:52
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "mpcsolve_outer.h"
#include "blkdiag.h"

/* Function Definitions */

/*
 * Arguments    : const double varargin_1[9]
 *                double varargin_2
 *                double y[16]
 * Return Type  : void
 */
void blkdiag(const double varargin_1[9], double varargin_2, double y[16])
{
  int i3;
  int i4;
  memset(&y[0], 0, sizeof(double) << 4);
  for (i3 = 0; i3 < 3; i3++) {
    for (i4 = 0; i4 < 3; i4++) {
      y[i4 + (i3 << 2)] = varargin_1[i4 + 3 * i3];
    }
  }

  y[15] = varargin_2;
}

/*
 * File trailer for blkdiag.c
 *
 * [EOF]
 */
