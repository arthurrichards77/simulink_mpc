/*
 * File: rdivide.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 18-Aug-2016 10:55:52
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "mpcsolve_outer.h"
#include "rdivide.h"

/* Function Definitions */

/*
 * Arguments    : const double x[40]
 *                const double y[40]
 *                double z[40]
 * Return Type  : void
 */
void b_rdivide(const double x[40], const double y[40], double z[40])
{
  int i;
  for (i = 0; i < 40; i++) {
    z[i] = x[i] / y[i];
  }
}

/*
 * Arguments    : double x
 *                const double y[40]
 *                double z[40]
 * Return Type  : void
 */
void c_rdivide(double x, const double y[40], double z[40])
{
  int i;
  for (i = 0; i < 40; i++) {
    z[i] = x / y[i];
  }
}

/*
 * Arguments    : double x
 *                const double y[24]
 *                double z[24]
 * Return Type  : void
 */
void rdivide(double x, const double y[24], double z[24])
{
  int i;
  for (i = 0; i < 24; i++) {
    z[i] = x / y[i];
  }
}

/*
 * File trailer for rdivide.c
 *
 * [EOF]
 */
