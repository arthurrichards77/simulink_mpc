/*
 * File: isfinite.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 18-Aug-2016 10:55:52
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "mpcsolve_outer.h"
#include "isfinite.h"

/* Function Definitions */

/*
 * Arguments    : double x
 * Return Type  : boolean_T
 */
boolean_T b_isfinite(double x)
{
  return (!rtIsInf(x)) && (!rtIsNaN(x));
}

/*
 * File trailer for isfinite.c
 *
 * [EOF]
 */
