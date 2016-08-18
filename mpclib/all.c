/*
 * File: all.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 18-Aug-2016 10:55:52
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "mpcsolve_outer.h"
#include "all.h"

/* Function Definitions */

/*
 * Arguments    : const boolean_T x[24]
 * Return Type  : boolean_T
 */
boolean_T all(const boolean_T x[24])
{
  boolean_T y;
  int k;
  boolean_T exitg1;
  y = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 24)) {
    if (x[k] == 0) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  return y;
}

/*
 * File trailer for all.c
 *
 * [EOF]
 */
