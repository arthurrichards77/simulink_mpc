/*
 * File: all.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 18-Aug-2016 17:54:05
 */

/* Include files */
#include "rt_nonfinite.h"
#include "mpcsolve_outer.h"
#include "all.h"

/* Function Definitions */

/*
 * Arguments    : const boolean_T x[42]
 * Return Type  : boolean_T
 */
boolean_T all(const boolean_T x[42])
{
  boolean_T y;
  int k;
  boolean_T exitg1;
  y = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 42)) {
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
