/*
 * File: mpcsolve_outer_rtwutil.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 18-Aug-2016 10:55:52
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "mpcsolve_outer.h"
#include "mpcsolve_outer_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double b_a;
  double b;
  b_a = fabs(u0);
  b = fabs(u1);
  if (b_a < b) {
    b_a /= b;
    y = b * sqrt(b_a * b_a + 1.0);
  } else if (b_a > b) {
    b /= b_a;
    y = b_a * sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = b_a * 1.4142135623730951;
  }

  return y;
}

/*
 * File trailer for mpcsolve_outer_rtwutil.c
 *
 * [EOF]
 */
