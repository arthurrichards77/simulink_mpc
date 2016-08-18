/*
 * File: linsolve.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 18-Aug-2016 17:54:05
 */

/* Include files */
#include "rt_nonfinite.h"
#include "mpcsolve_outer.h"
#include "linsolve.h"

/* Function Definitions */

/*
 * Arguments    : const double A[9]
 *                const double B[3]
 *                double C[3]
 * Return Type  : void
 */
void b_linsolve(const double A[9], const double B[3], double C[3])
{
  int i;
  int j;
  int jjA;
  int ix;
  for (i = 0; i < 3; i++) {
    C[i] = B[i];
  }

  for (j = 0; j < 3; j++) {
    jjA = j + j * 3;
    C[j] /= A[jjA];
    for (i = 1; i <= 2 - j; i++) {
      ix = j + i;
      C[ix] -= C[j] * A[jjA + i];
    }
  }
}

/*
 * Arguments    : const double A[9]
 *                const double B[3]
 *                double C[3]
 * Return Type  : void
 */
void c_linsolve(const double A[9], const double B[3], double C[3])
{
  int i;
  int j;
  int jjA;
  int ix;
  for (i = 0; i < 3; i++) {
    C[i] = B[i];
  }

  for (j = 2; j > -1; j += -1) {
    jjA = j + j * 3;
    C[j] /= A[jjA];
    for (i = 1; i <= j; i++) {
      ix = j - i;
      C[ix] -= C[j] * A[jjA - i];
    }
  }
}

/*
 * Arguments    : const double A[9]
 *                const double B[9]
 *                double C[9]
 * Return Type  : void
 */
void linsolve(const double A[9], const double B[9], double C[9])
{
  int j;
  int i;
  int jBcol;
  int k;
  int kAcol;
  for (j = 0; j < 3; j++) {
    for (i = 0; i < 3; i++) {
      C[i + 3 * j] = B[i + 3 * j];
    }
  }

  for (j = 0; j < 3; j++) {
    jBcol = 3 * j;
    for (k = 0; k < 3; k++) {
      kAcol = 3 * k;
      if (C[k + jBcol] != 0.0) {
        C[k + jBcol] /= A[k + kAcol];
        for (i = k + 1; i + 1 < 4; i++) {
          C[i + jBcol] -= C[k + jBcol] * A[i + kAcol];
        }
      }
    }
  }
}

/*
 * File trailer for linsolve.c
 *
 * [EOF]
 */
