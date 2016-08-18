/*
 * File: eye.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 18-Aug-2016 10:55:52
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "mpcsolve_outer.h"
#include "eye.h"

/* Function Definitions */

/*
 * Arguments    : double I[1600]
 * Return Type  : void
 */
void eye(double I[1600])
{
  int k;
  memset(&I[0], 0, 1600U * sizeof(double));
  for (k = 0; k < 40; k++) {
    I[k + 40 * k] = 1.0;
  }
}

/*
 * File trailer for eye.c
 *
 * [EOF]
 */
