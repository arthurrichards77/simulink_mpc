/*
 * File: diag.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 18-Aug-2016 10:55:52
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "mpcsolve_outer.h"
#include "diag.h"

/* Function Definitions */

/*
 * Arguments    : const double v[40]
 *                double d[1600]
 * Return Type  : void
 */
void b_diag(const double v[40], double d[1600])
{
  int j;
  memset(&d[0], 0, 1600U * sizeof(double));
  for (j = 0; j < 40; j++) {
    d[j + 40 * j] = v[j];
  }
}

/*
 * Arguments    : const double v[2]
 *                double d[4]
 * Return Type  : void
 */
void c_diag(const double v[2], double d[4])
{
  int j;
  for (j = 0; j < 4; j++) {
    d[j] = 0.0;
  }

  for (j = 0; j < 2; j++) {
    d[j + (j << 1)] = v[j];
  }
}

/*
 * Arguments    : const double v[4]
 *                double d[16]
 * Return Type  : void
 */
void d_diag(const double v[4], double d[16])
{
  int j;
  memset(&d[0], 0, sizeof(double) << 4);
  for (j = 0; j < 4; j++) {
    d[j + (j << 2)] = v[j];
  }
}

/*
 * Arguments    : const double v[1600]
 *                double d[40]
 * Return Type  : void
 */
void diag(const double v[1600], double d[40])
{
  int j;
  for (j = 0; j < 40; j++) {
    d[j] = v[j * 41];
  }
}

/*
 * Arguments    : const double v[24]
 *                double d[576]
 * Return Type  : void
 */
void e_diag(const double v[24], double d[576])
{
  int j;
  memset(&d[0], 0, 576U * sizeof(double));
  for (j = 0; j < 24; j++) {
    d[j + 24 * j] = v[j];
  }
}

/*
 * File trailer for diag.c
 *
 * [EOF]
 */
