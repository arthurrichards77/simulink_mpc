/*
 * File: rdivide.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 18-Aug-2016 17:54:05
 */

/* Include files */
#include "rt_nonfinite.h"
#include "mpcsolve_outer.h"
#include "rdivide.h"

/* Function Definitions */

/*
 * Arguments    : const double x[20]
 *                const double y[20]
 *                double z[20]
 * Return Type  : void
 */
void b_rdivide(const double x[20], const double y[20], double z[20])
{
  int i;
  for (i = 0; i < 20; i++) {
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
 *                const double y[42]
 *                double z[42]
 * Return Type  : void
 */
void rdivide(double x, const double y[42], double z[42])
{
  int i;
  for (i = 0; i < 42; i++) {
    z[i] = x / y[i];
  }
}

/*
 * File trailer for rdivide.c
 *
 * [EOF]
 */
