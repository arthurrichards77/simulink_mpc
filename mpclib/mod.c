/*
 * File: mod.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 18-Aug-2016 10:55:52
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "mpcsolve_outer.h"
#include "mod.h"

/* Function Definitions */

/*
 * Arguments    : int x
 * Return Type  : int
 */
int b_mod(int x)
{
  return x - x / 10 * 10;
}

/*
 * File trailer for mod.c
 *
 * [EOF]
 */
