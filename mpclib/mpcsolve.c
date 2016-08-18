/*
 * File: mpcsolve.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 18-Aug-2016 10:55:52
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "mpcsolve_outer.h"
#include "mpcsolve.h"
#include "linsolve.h"
#include "norm.h"
#include "rdivide.h"
#include "all.h"
#include "eig.h"
#include "diag.h"
#include "eye.h"
#include "blkdiag.h"

/* Function Declarations */
static void Stil(const double phiInv[1600], double ii, double St[3]);
static void b_eml_xaxpy(int n, double b_a, const double x[16], int ix0, double
  y[4], int iy0);
static double b_eml_xdotc(int n, const double x[9], int ix0, const double y[9],
  int iy0);
static void b_eml_xgesvd(const double A[9], double S[3]);
static double b_eml_xnrm2(int n, const double x[4], int ix0);
static void b_mySymPDinv(const double M[16], boolean_T flagChecking, double
  Minv[16]);
static void c_eml_xaxpy(int n, double b_a, const double x[4], int ix0, double y
  [16], int iy0);
static double c_eml_xnrm2(int n, const double x[9], int ix0);
static void c_mySymPDinv(const double M[9], boolean_T flagChecking, double Minv
  [9]);
static void calcDs(const double z[40], const double Ps[1600], double hs[40],
                   double rho, boolean_T flagNoPade, double ds[40]);
static void calcRp(const double z[40], const double b[32], const double A[9],
                   const double B[3], const double Ef[6], double rp[32]);
static void d_eml_xaxpy(int n, double b_a, int ix0, double y[9], int iy0);
static double d_eml_xnrm2(int n, const double x[3], int ix0);
static void e_eml_xaxpy(int n, double b_a, const double x[9], int ix0, double y
  [3], int iy0);
static void eml_xaxpy(int n, double b_a, int ix0, double y[16], int iy0);
static double eml_xdotc(int n, const double x[16], int ix0, const double y[16],
  int iy0);
static void eml_xgesvd(const double A[16], double S[4]);
static double eml_xnrm2(int n, const double x[16], int ix0);
static void f_eml_xaxpy(int n, double b_a, const double x[3], int ix0, double y
  [9], int iy0);
static void multByC(const double z[40], const double A[9], const double B[3],
                    const double Ef[6], double y[32]);
static void multByP(const double z[40], const double Fx[6], const double Fu[2],
                    const double Ff[12], double y[24]);
static double mySymPDinv(double M);
static double myexp(double u, boolean_T flagNoPade);

/* Function Definitions */

/*
 * Arguments    : const double phiInv[1600]
 *                double ii
 *                double St[3]
 * Return Type  : void
 */
static void Stil(const double phiInv[1600], double ii, double St[3])
{
  double d4;
  int i18;
  int i19;
  d4 = 1.0 + 4.0 * (ii - 1.0);
  i18 = (int)(4.0 * ii + 1.0);
  for (i19 = 0; i19 < 3; i19++) {
    St[i19] = phiInv[((int)(d4 + (1.0 + (double)i19)) + 40 * (i18 - 1)) - 1];
  }
}

/*
 * Arguments    : int n
 *                double b_a
 *                const double x[16]
 *                int ix0
 *                double y[4]
 *                int iy0
 * Return Type  : void
 */
static void b_eml_xaxpy(int n, double b_a, const double x[16], int ix0, double
  y[4], int iy0)
{
  int ix;
  int iy;
  int k;
  if ((n < 1) || (b_a == 0.0)) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += b_a * x[ix];
      ix++;
      iy++;
    }
  }
}

/*
 * Arguments    : int n
 *                const double x[9]
 *                int ix0
 *                const double y[9]
 *                int iy0
 * Return Type  : double
 */
static double b_eml_xdotc(int n, const double x[9], int ix0, const double y[9],
  int iy0)
{
  double d;
  int ix;
  int iy;
  int k;
  d = 0.0;
  if (n < 1) {
  } else {
    ix = ix0;
    iy = iy0;
    for (k = 1; k <= n; k++) {
      d += x[ix - 1] * y[iy - 1];
      ix++;
      iy++;
    }
  }

  return d;
}

/*
 * Arguments    : const double A[9]
 *                double S[3]
 * Return Type  : void
 */
static void b_eml_xgesvd(const double A[9], double S[3])
{
  double b_A[9];
  double s[3];
  double e[3];
  double work[3];
  int i;
  int q;
  int qs;
  boolean_T apply_transform;
  double ztest0;
  double ztest;
  int qjj;
  int m;
  double rt;
  int iter;
  double snorm;
  int32_T exitg3;
  boolean_T exitg2;
  double f;
  double varargin_1[5];
  double mtmp;
  boolean_T exitg1;
  double sqds;
  memcpy(&b_A[0], &A[0], 9U * sizeof(double));
  for (i = 0; i < 3; i++) {
    s[i] = 0.0;
    e[i] = 0.0;
    work[i] = 0.0;
  }

  for (q = 0; q < 2; q++) {
    qs = q + 3 * q;
    apply_transform = false;
    ztest0 = c_eml_xnrm2(3 - q, b_A, qs + 1);
    if (ztest0 > 0.0) {
      apply_transform = true;
      if (b_A[qs] < 0.0) {
        s[q] = -ztest0;
      } else {
        s[q] = ztest0;
      }

      if (fabs(s[q]) >= 1.0020841800044864E-292) {
        ztest = 1.0 / s[q];
        i = (qs - q) + 3;
        for (qjj = qs; qjj + 1 <= i; qjj++) {
          b_A[qjj] *= ztest;
        }
      } else {
        i = (qs - q) + 3;
        for (qjj = qs; qjj + 1 <= i; qjj++) {
          b_A[qjj] /= s[q];
        }
      }

      b_A[qs]++;
      s[q] = -s[q];
    } else {
      s[q] = 0.0;
    }

    for (i = q + 1; i + 1 < 4; i++) {
      qjj = q + 3 * i;
      if (apply_transform) {
        d_eml_xaxpy(3 - q, -(b_eml_xdotc(3 - q, b_A, qs + 1, b_A, qjj + 1) /
                             b_A[q + 3 * q]), qs + 1, b_A, qjj + 1);
      }

      e[i] = b_A[qjj];
    }

    if (q + 1 <= 1) {
      ztest0 = d_eml_xnrm2(2, e, 2);
      if (ztest0 == 0.0) {
        e[0] = 0.0;
      } else {
        if (e[1] < 0.0) {
          ztest = -ztest0;
        } else {
          ztest = ztest0;
        }

        if (e[1] < 0.0) {
          e[0] = -ztest0;
        } else {
          e[0] = ztest0;
        }

        if (fabs(e[0]) >= 1.0020841800044864E-292) {
          ztest = 1.0 / e[0];
          for (qjj = 1; qjj + 1 < 4; qjj++) {
            e[qjj] *= ztest;
          }
        } else {
          for (qjj = 1; qjj + 1 < 4; qjj++) {
            e[qjj] /= ztest;
          }
        }

        e[1]++;
        e[0] = -e[0];
        for (i = 2; i < 4; i++) {
          work[i - 1] = 0.0;
        }

        for (i = 1; i + 1 < 4; i++) {
          e_eml_xaxpy(2, e[i], b_A, 3 * i + 2, work, 2);
        }

        for (i = 1; i + 1 < 4; i++) {
          f_eml_xaxpy(2, -e[i] / e[1], work, 2, b_A, 3 * i + 2);
        }
      }
    }
  }

  m = 1;
  s[2] = b_A[8];
  e[1] = b_A[7];
  e[2] = 0.0;
  for (q = 0; q < 3; q++) {
    ztest = e[q];
    if (s[q] != 0.0) {
      rt = fabs(s[q]);
      ztest0 = s[q] / rt;
      s[q] = rt;
      if (q + 1 < 3) {
        ztest = e[q] / ztest0;
      }
    }

    if ((q + 1 < 3) && (ztest != 0.0)) {
      rt = fabs(ztest);
      ztest0 = ztest;
      ztest = rt;
      s[q + 1] *= rt / ztest0;
    }

    e[q] = ztest;
  }

  iter = 0;
  snorm = 0.0;
  for (i = 0; i < 3; i++) {
    ztest = fabs(s[i]);
    ztest0 = fabs(e[i]);
    if ((ztest >= ztest0) || rtIsNaN(ztest0)) {
      ztest0 = ztest;
    }

    if ((snorm >= ztest0) || rtIsNaN(ztest0)) {
    } else {
      snorm = ztest0;
    }
  }

  while ((m + 2 > 0) && (!(iter >= 75))) {
    i = m;
    do {
      exitg3 = 0;
      q = i + 1;
      if (i + 1 == 0) {
        exitg3 = 1;
      } else {
        ztest0 = fabs(e[i]);
        if ((ztest0 <= 2.2204460492503131E-16 * (fabs(s[i]) + fabs(s[i + 1]))) ||
            (ztest0 <= 1.0020841800044864E-292) || ((iter > 20) && (ztest0 <=
              2.2204460492503131E-16 * snorm))) {
          e[i] = 0.0;
          exitg3 = 1;
        } else {
          i--;
        }
      }
    } while (exitg3 == 0);

    if (i + 1 == m + 1) {
      i = 4;
    } else {
      qs = m + 2;
      qjj = m + 2;
      exitg2 = false;
      while ((!exitg2) && (qjj >= i + 1)) {
        qs = qjj;
        if (qjj == i + 1) {
          exitg2 = true;
        } else {
          ztest0 = 0.0;
          if (qjj < m + 2) {
            ztest0 = fabs(e[qjj - 1]);
          }

          if (qjj > i + 2) {
            ztest0 += fabs(e[qjj - 2]);
          }

          ztest = fabs(s[qjj - 1]);
          if ((ztest <= 2.2204460492503131E-16 * ztest0) || (ztest <=
               1.0020841800044864E-292)) {
            s[qjj - 1] = 0.0;
            exitg2 = true;
          } else {
            qjj--;
          }
        }
      }

      if (qs == i + 1) {
        i = 3;
      } else if (qs == m + 2) {
        i = 1;
      } else {
        i = 2;
        q = qs;
      }
    }

    switch (i) {
     case 1:
      f = e[m];
      e[m] = 0.0;
      for (qjj = m; qjj + 1 >= q + 1; qjj--) {
        ztest0 = s[qjj];
        eml_xrotg(&ztest0, &f, &ztest, &rt);
        s[qjj] = ztest0;
        if (qjj + 1 > q + 1) {
          f = -rt * e[0];
          e[0] *= ztest;
        }
      }
      break;

     case 2:
      f = e[q - 1];
      e[q - 1] = 0.0;
      while (q + 1 <= m + 2) {
        eml_xrotg(&s[q], &f, &ztest, &rt);
        f = -rt * e[q];
        e[q] *= ztest;
        q++;
      }
      break;

     case 3:
      varargin_1[0] = fabs(s[m + 1]);
      varargin_1[1] = fabs(s[m]);
      varargin_1[2] = fabs(e[m]);
      varargin_1[3] = fabs(s[q]);
      varargin_1[4] = fabs(e[q]);
      i = 1;
      mtmp = varargin_1[0];
      if (rtIsNaN(varargin_1[0])) {
        qjj = 2;
        exitg1 = false;
        while ((!exitg1) && (qjj < 6)) {
          i = qjj;
          if (!rtIsNaN(varargin_1[qjj - 1])) {
            mtmp = varargin_1[qjj - 1];
            exitg1 = true;
          } else {
            qjj++;
          }
        }
      }

      if (i < 5) {
        while (i + 1 < 6) {
          if (varargin_1[i] > mtmp) {
            mtmp = varargin_1[i];
          }

          i++;
        }
      }

      f = s[m + 1] / mtmp;
      ztest0 = s[m] / mtmp;
      ztest = e[m] / mtmp;
      sqds = s[q] / mtmp;
      rt = ((ztest0 + f) * (ztest0 - f) + ztest * ztest) / 2.0;
      ztest0 = f * ztest;
      ztest0 *= ztest0;
      if ((rt != 0.0) || (ztest0 != 0.0)) {
        ztest = sqrt(rt * rt + ztest0);
        if (rt < 0.0) {
          ztest = -ztest;
        }

        ztest = ztest0 / (rt + ztest);
      } else {
        ztest = 0.0;
      }

      f = (sqds + f) * (sqds - f) + ztest;
      ztest0 = sqds * (e[q] / mtmp);
      for (qjj = q + 1; qjj <= m + 1; qjj++) {
        eml_xrotg(&f, &ztest0, &ztest, &rt);
        if (qjj > q + 1) {
          e[0] = f;
        }

        f = ztest * s[qjj - 1] + rt * e[qjj - 1];
        e[qjj - 1] = ztest * e[qjj - 1] - rt * s[qjj - 1];
        ztest0 = rt * s[qjj];
        s[qjj] *= ztest;
        s[qjj - 1] = f;
        eml_xrotg(&s[qjj - 1], &ztest0, &ztest, &rt);
        f = ztest * e[qjj - 1] + rt * s[qjj];
        s[qjj] = -rt * e[qjj - 1] + ztest * s[qjj];
        ztest0 = rt * e[qjj];
        e[qjj] *= ztest;
      }

      e[m] = f;
      iter++;
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
      }

      i = q + 1;
      while ((q + 1 < 3) && (s[q] < s[i])) {
        rt = s[q];
        s[q] = s[i];
        s[i] = rt;
        q = i;
        i++;
      }

      iter = 0;
      m--;
      break;
    }
  }

  for (qjj = 0; qjj < 3; qjj++) {
    S[qjj] = s[qjj];
  }
}

/*
 * Arguments    : int n
 *                const double x[4]
 *                int ix0
 * Return Type  : double
 */
static double b_eml_xnrm2(int n, const double x[4], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  if (n < 1) {
  } else if (n == 1) {
    y = fabs(x[ix0 - 1]);
  } else {
    scale = 2.2250738585072014E-308;
    kend = (ix0 + n) - 1;
    for (k = ix0; k <= kend; k++) {
      absxk = fabs(x[k - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        y = 1.0 + y * t * t;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }
    }

    y = scale * sqrt(y);
  }

  return y;
}

/*
 * utility for quick inversion of a symmetric positive definite matrix
 * Arguments    : const double M[16]
 *                boolean_T flagChecking
 *                double Minv[16]
 * Return Type  : void
 */
static void b_mySymPDinv(const double M[16], boolean_T flagChecking, double
  Minv[16])
{
  double A[16];
  int info;
  int j;
  boolean_T exitg1;
  int jj;
  double ajj;
  int ix;
  int iy;
  int k;
  int i16;
  int jmax;
  double c;
  int kAcol;
  double T[16];
  static const signed char B[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    1 };

  double b_A[16];
  double unusedExpr[4];
  memcpy(&A[0], &M[0], sizeof(double) << 4);
  info = 0;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j + 1 < 5)) {
    jj = j + (j << 2);
    ajj = 0.0;
    if (j < 1) {
    } else {
      ix = j;
      iy = j;
      for (k = 1; k <= j; k++) {
        ajj += A[ix] * A[iy];
        ix += 4;
        iy += 4;
      }
    }

    ajj = A[jj] - ajj;
    if (ajj > 0.0) {
      ajj = sqrt(ajj);
      A[jj] = ajj;
      if (j + 1 < 4) {
        if (j == 0) {
        } else {
          ix = j;
          i16 = (j + ((j - 1) << 2)) + 2;
          for (jmax = j + 2; jmax <= i16; jmax += 4) {
            c = -A[ix];
            iy = jj + 1;
            k = (jmax - j) + 2;
            for (kAcol = jmax; kAcol <= k; kAcol++) {
              A[iy] += A[kAcol - 1] * c;
              iy++;
            }

            ix += 4;
          }
        }

        ajj = 1.0 / ajj;
        i16 = (jj - j) + 4;
        for (k = jj + 1; k + 1 <= i16; k++) {
          A[k] *= ajj;
        }
      }

      j++;
    } else {
      A[jj] = ajj;
      info = j + 1;
      exitg1 = true;
    }
  }

  if (info == 0) {
    jmax = 4;
  } else {
    jmax = info - 1;
  }

  for (j = 1; j + 1 <= jmax; j++) {
    for (info = 1; info <= j; info++) {
      A[(info + (j << 2)) - 1] = 0.0;
    }
  }

  for (j = 0; j < 4; j++) {
    for (info = 0; info < 4; info++) {
      T[info + (j << 2)] = B[info + (j << 2)];
    }
  }

  for (j = 0; j < 4; j++) {
    jmax = j << 2;
    for (k = 0; k < 4; k++) {
      kAcol = k << 2;
      if (T[k + jmax] != 0.0) {
        T[k + jmax] /= A[k + kAcol];
        for (info = k + 1; info + 1 < 5; info++) {
          T[info + jmax] -= T[k + jmax] * A[info + kAcol];
        }
      }
    }
  }

  for (i16 = 0; i16 < 4; i16++) {
    for (k = 0; k < 4; k++) {
      b_A[k + (i16 << 2)] = A[i16 + (k << 2)];
      Minv[k + (i16 << 2)] = T[k + (i16 << 2)];
    }
  }

  for (j = 0; j < 4; j++) {
    jmax = j << 2;
    for (k = 3; k > -1; k += -1) {
      kAcol = k << 2;
      if (Minv[k + jmax] != 0.0) {
        Minv[k + jmax] /= b_A[k + kAcol];
        for (info = 0; info + 1 <= k; info++) {
          Minv[info + jmax] -= Minv[k + jmax] * b_A[info + kAcol];
        }
      }
    }
  }

  if (flagChecking) {
    memset(&A[0], 0, sizeof(double) << 4);
    for (k = 0; k < 4; k++) {
      A[k + (k << 2)] = 1.0;
    }

    for (i16 = 0; i16 < 4; i16++) {
      for (k = 0; k < 4; k++) {
        ajj = 0.0;
        for (jmax = 0; jmax < 4; jmax++) {
          ajj += Minv[i16 + (jmax << 2)] * M[jmax + (k << 2)];
        }

        T[i16 + (k << 2)] = ajj - A[i16 + (k << 2)];
      }
    }

    eml_xgesvd(T, unusedExpr);
  }
}

/*
 * Arguments    : int n
 *                double b_a
 *                const double x[4]
 *                int ix0
 *                double y[16]
 *                int iy0
 * Return Type  : void
 */
static void c_eml_xaxpy(int n, double b_a, const double x[4], int ix0, double y
  [16], int iy0)
{
  int ix;
  int iy;
  int k;
  if ((n < 1) || (b_a == 0.0)) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += b_a * x[ix];
      ix++;
      iy++;
    }
  }
}

/*
 * Arguments    : int n
 *                const double x[9]
 *                int ix0
 * Return Type  : double
 */
static double c_eml_xnrm2(int n, const double x[9], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  if (n < 1) {
  } else if (n == 1) {
    y = fabs(x[ix0 - 1]);
  } else {
    scale = 2.2250738585072014E-308;
    kend = (ix0 + n) - 1;
    for (k = ix0; k <= kend; k++) {
      absxk = fabs(x[k - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        y = 1.0 + y * t * t;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }
    }

    y = scale * sqrt(y);
  }

  return y;
}

/*
 * utility for quick inversion of a symmetric positive definite matrix
 * Arguments    : const double M[9]
 *                boolean_T flagChecking
 *                double Minv[9]
 * Return Type  : void
 */
static void c_mySymPDinv(const double M[9], boolean_T flagChecking, double Minv
  [9])
{
  double A[9];
  int info;
  int j;
  boolean_T exitg1;
  int jj;
  double ajj;
  int ix;
  int iy;
  int k;
  int i17;
  int jmax;
  double c;
  int kAcol;
  double T[9];
  static const double dv28[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

  double b_A[9];
  double unusedExpr[3];
  memcpy(&A[0], &M[0], 9U * sizeof(double));
  info = 0;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j + 1 < 4)) {
    jj = j + j * 3;
    ajj = 0.0;
    if (j < 1) {
    } else {
      ix = j;
      iy = j;
      for (k = 1; k <= j; k++) {
        ajj += A[ix] * A[iy];
        ix += 3;
        iy += 3;
      }
    }

    ajj = A[jj] - ajj;
    if (ajj > 0.0) {
      ajj = sqrt(ajj);
      A[jj] = ajj;
      if (j + 1 < 3) {
        if (j == 0) {
        } else {
          ix = j;
          i17 = (j + 3 * (j - 1)) + 2;
          for (jmax = j + 2; jmax <= i17; jmax += 3) {
            c = -A[ix];
            iy = jj + 1;
            k = (jmax - j) + 1;
            for (kAcol = jmax; kAcol <= k; kAcol++) {
              A[iy] += A[kAcol - 1] * c;
              iy++;
            }

            ix += 3;
          }
        }

        ajj = 1.0 / ajj;
        i17 = (jj - j) + 3;
        for (k = jj + 1; k + 1 <= i17; k++) {
          A[k] *= ajj;
        }
      }

      j++;
    } else {
      A[jj] = ajj;
      info = j + 1;
      exitg1 = true;
    }
  }

  if (info == 0) {
    jmax = 3;
  } else {
    jmax = info - 1;
  }

  for (j = 1; j + 1 <= jmax; j++) {
    for (info = 1; info <= j; info++) {
      A[(info + 3 * j) - 1] = 0.0;
    }
  }

  linsolve(A, dv28, T);
  for (i17 = 0; i17 < 3; i17++) {
    for (k = 0; k < 3; k++) {
      b_A[k + 3 * i17] = A[i17 + 3 * k];
      Minv[k + 3 * i17] = T[k + 3 * i17];
    }
  }

  for (j = 0; j < 3; j++) {
    jmax = 3 * j;
    for (k = 2; k > -1; k += -1) {
      kAcol = 3 * k;
      if (Minv[k + jmax] != 0.0) {
        Minv[k + jmax] /= b_A[k + kAcol];
        for (info = 0; info + 1 <= k; info++) {
          Minv[info + jmax] -= Minv[k + jmax] * b_A[info + kAcol];
        }
      }
    }
  }

  if (flagChecking) {
    memset(&A[0], 0, 9U * sizeof(double));
    for (k = 0; k < 3; k++) {
      A[k + 3 * k] = 1.0;
    }

    for (i17 = 0; i17 < 3; i17++) {
      for (k = 0; k < 3; k++) {
        ajj = 0.0;
        for (jmax = 0; jmax < 3; jmax++) {
          ajj += Minv[i17 + 3 * jmax] * M[jmax + 3 * k];
        }

        T[i17 + 3 * k] = ajj - A[i17 + 3 * k];
      }
    }

    b_eml_xgesvd(T, unusedExpr);
  }
}

/*
 * pre-assign to help coder
 * Arguments    : const double z[40]
 *                const double Ps[1600]
 *                double hs[40]
 *                double rho
 *                boolean_T flagNoPade
 *                double ds[40]
 * Return Type  : void
 */
static void calcDs(const double z[40], const double Ps[1600], double hs[40],
                   double rho, boolean_T flagNoPade, double ds[40])
{
  double rs[40];
  int ii;
  double d5;
  int i21;

  /*  residuals */
  for (ii = 0; ii < 40; ii++) {
    d5 = 0.0;
    for (i21 = 0; i21 < 40; i21++) {
      d5 += Ps[ii + 40 * i21] * z[i21];
    }

    rs[ii] = d5 - hs[ii];
  }

  for (ii = 0; ii < 40; ii++) {
    if (rs[ii] > 0.0) {
      hs[ii] = myexp(-rho * rs[ii], flagNoPade);
      ds[ii] = 1.0 / (1.0 + hs[ii]);
    } else {
      hs[ii] = myexp(rho * rs[ii], flagNoPade);
      ds[ii] = hs[ii] / (1.0 + hs[ii]);
    }
  }
}

/*
 * calculate primal residual Cz-b
 * Arguments    : const double z[40]
 *                const double b[32]
 *                const double A[9]
 *                const double B[3]
 *                const double Ef[6]
 *                double rp[32]
 * Return Type  : void
 */
static void calcRp(const double z[40], const double b[32], const double A[9],
                   const double B[3], const double Ef[6], double rp[32])
{
  int i;
  int i8;
  double b_b[3];
  int i9;
  double b_z[3];
  int i10;
  double d2;
  int i11;
  double b_Ef[2];

  /*  */
  /*  return C*z */
  /*  */
  memset(&rp[0], 0, sizeof(double) << 5);
  for (i = 0; i < 3; i++) {
    rp[i] = z[i + 1] - B[i] * z[0];
  }

  for (i = 0; i < 9; i++) {
    i8 = i << 2;
    for (i9 = 0; i9 < 3; i9++) {
      b_b[i9] = z[(i9 + i8) + 1];
    }

    i8 = 3 * (1 + i);
    i9 = (1 + i) << 2;
    for (i10 = 0; i10 < 3; i10++) {
      d2 = 0.0;
      for (i11 = 0; i11 < 3; i11++) {
        d2 += A[i10 + 3 * i11] * b_b[i11];
      }

      b_z[i10] = (z[(i10 + i9) + 1] - d2) - B[i10] * z[(1 + i) << 2];
    }

    for (i9 = 0; i9 < 3; i9++) {
      rp[i9 + i8] = b_z[i9];
    }
  }

  for (i8 = 0; i8 < 2; i8++) {
    b_Ef[i8] = 0.0;
    for (i9 = 0; i9 < 3; i9++) {
      b_Ef[i8] += Ef[i8 + (i9 << 1)] * z[37 + i9];
    }

    rp[30 + i8] = b_Ef[i8];
  }

  for (i8 = 0; i8 < 32; i8++) {
    rp[i8] -= b[i8];
  }
}

/*
 * Arguments    : int n
 *                double b_a
 *                int ix0
 *                double y[9]
 *                int iy0
 * Return Type  : void
 */
static void d_eml_xaxpy(int n, double b_a, int ix0, double y[9], int iy0)
{
  int ix;
  int iy;
  int k;
  if ((n < 1) || (b_a == 0.0)) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += b_a * y[ix];
      ix++;
      iy++;
    }
  }
}

/*
 * Arguments    : int n
 *                const double x[3]
 *                int ix0
 * Return Type  : double
 */
static double d_eml_xnrm2(int n, const double x[3], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  if (n < 1) {
  } else if (n == 1) {
    y = fabs(x[ix0 - 1]);
  } else {
    scale = 2.2250738585072014E-308;
    kend = (ix0 + n) - 1;
    for (k = ix0; k <= kend; k++) {
      absxk = fabs(x[k - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        y = 1.0 + y * t * t;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }
    }

    y = scale * sqrt(y);
  }

  return y;
}

/*
 * Arguments    : int n
 *                double b_a
 *                const double x[9]
 *                int ix0
 *                double y[3]
 *                int iy0
 * Return Type  : void
 */
static void e_eml_xaxpy(int n, double b_a, const double x[9], int ix0, double y
  [3], int iy0)
{
  int ix;
  int iy;
  int k;
  if ((n < 1) || (b_a == 0.0)) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += b_a * x[ix];
      ix++;
      iy++;
    }
  }
}

/*
 * Arguments    : int n
 *                double b_a
 *                int ix0
 *                double y[16]
 *                int iy0
 * Return Type  : void
 */
static void eml_xaxpy(int n, double b_a, int ix0, double y[16], int iy0)
{
  int ix;
  int iy;
  int k;
  if ((n < 1) || (b_a == 0.0)) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += b_a * y[ix];
      ix++;
      iy++;
    }
  }
}

/*
 * Arguments    : int n
 *                const double x[16]
 *                int ix0
 *                const double y[16]
 *                int iy0
 * Return Type  : double
 */
static double eml_xdotc(int n, const double x[16], int ix0, const double y[16],
  int iy0)
{
  double d;
  int ix;
  int iy;
  int k;
  d = 0.0;
  if (n < 1) {
  } else {
    ix = ix0;
    iy = iy0;
    for (k = 1; k <= n; k++) {
      d += x[ix - 1] * y[iy - 1];
      ix++;
      iy++;
    }
  }

  return d;
}

/*
 * Arguments    : const double A[16]
 *                double S[4]
 * Return Type  : void
 */
static void eml_xgesvd(const double A[16], double S[4])
{
  double b_A[16];
  double s[4];
  double e[4];
  double work[4];
  int i;
  int q;
  int qs;
  boolean_T apply_transform;
  double ztest0;
  int qjj;
  int m;
  double ztest;
  double rt;
  int iter;
  double snorm;
  int32_T exitg3;
  boolean_T exitg2;
  double f;
  double varargin_1[5];
  double mtmp;
  boolean_T exitg1;
  double sqds;
  memcpy(&b_A[0], &A[0], sizeof(double) << 4);
  for (i = 0; i < 4; i++) {
    s[i] = 0.0;
    e[i] = 0.0;
    work[i] = 0.0;
  }

  for (q = 0; q < 3; q++) {
    qs = q + (q << 2);
    apply_transform = false;
    ztest0 = eml_xnrm2(4 - q, b_A, qs + 1);
    if (ztest0 > 0.0) {
      apply_transform = true;
      if (b_A[qs] < 0.0) {
        s[q] = -ztest0;
      } else {
        s[q] = ztest0;
      }

      if (fabs(s[q]) >= 1.0020841800044864E-292) {
        ztest0 = 1.0 / s[q];
        i = (qs - q) + 4;
        for (qjj = qs; qjj + 1 <= i; qjj++) {
          b_A[qjj] *= ztest0;
        }
      } else {
        i = (qs - q) + 4;
        for (qjj = qs; qjj + 1 <= i; qjj++) {
          b_A[qjj] /= s[q];
        }
      }

      b_A[qs]++;
      s[q] = -s[q];
    } else {
      s[q] = 0.0;
    }

    for (i = q + 1; i + 1 < 5; i++) {
      qjj = q + (i << 2);
      if (apply_transform) {
        eml_xaxpy(4 - q, -(eml_xdotc(4 - q, b_A, qs + 1, b_A, qjj + 1) / b_A[q +
                           (q << 2)]), qs + 1, b_A, qjj + 1);
      }

      e[i] = b_A[qjj];
    }

    if (q + 1 <= 2) {
      ztest0 = b_eml_xnrm2(3 - q, e, q + 2);
      if (ztest0 == 0.0) {
        e[q] = 0.0;
      } else {
        if (e[q + 1] < 0.0) {
          e[q] = -ztest0;
        } else {
          e[q] = ztest0;
        }

        ztest0 = e[q];
        if (fabs(e[q]) >= 1.0020841800044864E-292) {
          ztest0 = 1.0 / e[q];
          for (qjj = q + 1; qjj + 1 < 5; qjj++) {
            e[qjj] *= ztest0;
          }
        } else {
          for (qjj = q + 1; qjj + 1 < 5; qjj++) {
            e[qjj] /= ztest0;
          }
        }

        e[q + 1]++;
        e[q] = -e[q];
        for (i = q + 1; i + 1 < 5; i++) {
          work[i] = 0.0;
        }

        for (i = q + 1; i + 1 < 5; i++) {
          b_eml_xaxpy(3 - q, e[i], b_A, (q + (i << 2)) + 2, work, q + 2);
        }

        for (i = q + 1; i + 1 < 5; i++) {
          c_eml_xaxpy(3 - q, -e[i] / e[q + 1], work, q + 2, b_A, (q + (i << 2))
                      + 2);
        }
      }
    }
  }

  m = 2;
  s[3] = b_A[15];
  e[2] = b_A[14];
  e[3] = 0.0;
  for (q = 0; q < 4; q++) {
    ztest = e[q];
    if (s[q] != 0.0) {
      rt = fabs(s[q]);
      ztest0 = s[q] / rt;
      s[q] = rt;
      if (q + 1 < 4) {
        ztest = e[q] / ztest0;
      }
    }

    if ((q + 1 < 4) && (ztest != 0.0)) {
      rt = fabs(ztest);
      ztest0 = ztest;
      ztest = rt;
      s[q + 1] *= rt / ztest0;
    }

    e[q] = ztest;
  }

  iter = 0;
  snorm = 0.0;
  for (i = 0; i < 4; i++) {
    ztest0 = fabs(s[i]);
    ztest = fabs(e[i]);
    if ((ztest0 >= ztest) || rtIsNaN(ztest)) {
    } else {
      ztest0 = ztest;
    }

    if ((snorm >= ztest0) || rtIsNaN(ztest0)) {
    } else {
      snorm = ztest0;
    }
  }

  while ((m + 2 > 0) && (!(iter >= 75))) {
    i = m;
    do {
      exitg3 = 0;
      q = i + 1;
      if (i + 1 == 0) {
        exitg3 = 1;
      } else {
        ztest0 = fabs(e[i]);
        if ((ztest0 <= 2.2204460492503131E-16 * (fabs(s[i]) + fabs(s[i + 1]))) ||
            (ztest0 <= 1.0020841800044864E-292) || ((iter > 20) && (ztest0 <=
              2.2204460492503131E-16 * snorm))) {
          e[i] = 0.0;
          exitg3 = 1;
        } else {
          i--;
        }
      }
    } while (exitg3 == 0);

    if (i + 1 == m + 1) {
      i = 4;
    } else {
      qs = m + 2;
      qjj = m + 2;
      exitg2 = false;
      while ((!exitg2) && (qjj >= i + 1)) {
        qs = qjj;
        if (qjj == i + 1) {
          exitg2 = true;
        } else {
          ztest0 = 0.0;
          if (qjj < m + 2) {
            ztest0 = fabs(e[qjj - 1]);
          }

          if (qjj > i + 2) {
            ztest0 += fabs(e[qjj - 2]);
          }

          ztest = fabs(s[qjj - 1]);
          if ((ztest <= 2.2204460492503131E-16 * ztest0) || (ztest <=
               1.0020841800044864E-292)) {
            s[qjj - 1] = 0.0;
            exitg2 = true;
          } else {
            qjj--;
          }
        }
      }

      if (qs == i + 1) {
        i = 3;
      } else if (qs == m + 2) {
        i = 1;
      } else {
        i = 2;
        q = qs;
      }
    }

    switch (i) {
     case 1:
      f = e[m];
      e[m] = 0.0;
      for (qjj = m; qjj + 1 >= q + 1; qjj--) {
        ztest0 = s[qjj];
        eml_xrotg(&ztest0, &f, &ztest, &rt);
        s[qjj] = ztest0;
        if (qjj + 1 > q + 1) {
          f = -rt * e[qjj - 1];
          e[qjj - 1] *= ztest;
        }
      }
      break;

     case 2:
      f = e[q - 1];
      e[q - 1] = 0.0;
      while (q + 1 <= m + 2) {
        eml_xrotg(&s[q], &f, &ztest, &rt);
        f = -rt * e[q];
        e[q] *= ztest;
        q++;
      }
      break;

     case 3:
      varargin_1[0] = fabs(s[m + 1]);
      varargin_1[1] = fabs(s[m]);
      varargin_1[2] = fabs(e[m]);
      varargin_1[3] = fabs(s[q]);
      varargin_1[4] = fabs(e[q]);
      i = 1;
      mtmp = varargin_1[0];
      if (rtIsNaN(varargin_1[0])) {
        qjj = 2;
        exitg1 = false;
        while ((!exitg1) && (qjj < 6)) {
          i = qjj;
          if (!rtIsNaN(varargin_1[qjj - 1])) {
            mtmp = varargin_1[qjj - 1];
            exitg1 = true;
          } else {
            qjj++;
          }
        }
      }

      if (i < 5) {
        while (i + 1 < 6) {
          if (varargin_1[i] > mtmp) {
            mtmp = varargin_1[i];
          }

          i++;
        }
      }

      f = s[m + 1] / mtmp;
      ztest0 = s[m] / mtmp;
      ztest = e[m] / mtmp;
      sqds = s[q] / mtmp;
      rt = ((ztest0 + f) * (ztest0 - f) + ztest * ztest) / 2.0;
      ztest0 = f * ztest;
      ztest0 *= ztest0;
      if ((rt != 0.0) || (ztest0 != 0.0)) {
        ztest = sqrt(rt * rt + ztest0);
        if (rt < 0.0) {
          ztest = -ztest;
        }

        ztest = ztest0 / (rt + ztest);
      } else {
        ztest = 0.0;
      }

      f = (sqds + f) * (sqds - f) + ztest;
      ztest0 = sqds * (e[q] / mtmp);
      for (qjj = q + 1; qjj <= m + 1; qjj++) {
        eml_xrotg(&f, &ztest0, &ztest, &rt);
        if (qjj > q + 1) {
          e[qjj - 2] = f;
        }

        f = ztest * s[qjj - 1] + rt * e[qjj - 1];
        e[qjj - 1] = ztest * e[qjj - 1] - rt * s[qjj - 1];
        ztest0 = rt * s[qjj];
        s[qjj] *= ztest;
        s[qjj - 1] = f;
        eml_xrotg(&s[qjj - 1], &ztest0, &ztest, &rt);
        f = ztest * e[qjj - 1] + rt * s[qjj];
        s[qjj] = -rt * e[qjj - 1] + ztest * s[qjj];
        ztest0 = rt * e[qjj];
        e[qjj] *= ztest;
      }

      e[m] = f;
      iter++;
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
      }

      i = q + 1;
      while ((q + 1 < 4) && (s[q] < s[i])) {
        rt = s[q];
        s[q] = s[i];
        s[i] = rt;
        q = i;
        i++;
      }

      iter = 0;
      m--;
      break;
    }
  }

  for (qjj = 0; qjj < 4; qjj++) {
    S[qjj] = s[qjj];
  }
}

/*
 * Arguments    : int n
 *                const double x[16]
 *                int ix0
 * Return Type  : double
 */
static double eml_xnrm2(int n, const double x[16], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  if (n < 1) {
  } else if (n == 1) {
    y = fabs(x[ix0 - 1]);
  } else {
    scale = 2.2250738585072014E-308;
    kend = (ix0 + n) - 1;
    for (k = ix0; k <= kend; k++) {
      absxk = fabs(x[k - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        y = 1.0 + y * t * t;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }
    }

    y = scale * sqrt(y);
  }

  return y;
}

/*
 * Arguments    : int n
 *                double b_a
 *                const double x[3]
 *                int ix0
 *                double y[9]
 *                int iy0
 * Return Type  : void
 */
static void f_eml_xaxpy(int n, double b_a, const double x[3], int ix0, double y
  [9], int iy0)
{
  int ix;
  int iy;
  int k;
  if ((n < 1) || (b_a == 0.0)) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += b_a * x[ix];
      ix++;
      iy++;
    }
  }
}

/*
 * return C*z
 * Arguments    : const double z[40]
 *                const double A[9]
 *                const double B[3]
 *                const double Ef[6]
 *                double y[32]
 * Return Type  : void
 */
static void multByC(const double z[40], const double A[9], const double B[3],
                    const double Ef[6], double y[32])
{
  int i;
  int i12;
  double b[3];
  int i13;
  double b_z[3];
  int i14;
  double d3;
  int i15;
  double b_Ef[2];
  memset(&y[0], 0, sizeof(double) << 5);
  for (i = 0; i < 3; i++) {
    y[i] = z[i + 1] - B[i] * z[0];
  }

  for (i = 0; i < 9; i++) {
    i12 = i << 2;
    for (i13 = 0; i13 < 3; i13++) {
      b[i13] = z[(i13 + i12) + 1];
    }

    i12 = 3 * (1 + i);
    i13 = (1 + i) << 2;
    for (i14 = 0; i14 < 3; i14++) {
      d3 = 0.0;
      for (i15 = 0; i15 < 3; i15++) {
        d3 += A[i14 + 3 * i15] * b[i15];
      }

      b_z[i14] = (z[(i14 + i13) + 1] - d3) - B[i14] * z[(1 + i) << 2];
    }

    for (i13 = 0; i13 < 3; i13++) {
      y[i13 + i12] = b_z[i13];
    }
  }

  for (i12 = 0; i12 < 2; i12++) {
    b_Ef[i12] = 0.0;
    for (i13 = 0; i13 < 3; i13++) {
      b_Ef[i12] += Ef[i12 + (i13 << 1)] * z[37 + i13];
    }

    y[30 + i12] = b_Ef[i12];
  }
}

/*
 * return P*z
 * Arguments    : const double z[40]
 *                const double Fx[6]
 *                const double Fu[2]
 *                const double Ff[12]
 *                double y[24]
 * Return Type  : void
 */
static void multByP(const double z[40], const double Fx[6], const double Fu[2],
                    const double Ff[12], double y[24])
{
  int i;
  int i5;
  double b[3];
  int i6;
  double b_Fx[2];
  double d1;
  int i7;
  double b_Ff[4];
  memset(&y[0], 0, 24U * sizeof(double));
  for (i = 0; i < 2; i++) {
    y[i] = Fu[i] * z[0];
  }

  for (i = 0; i < 9; i++) {
    i5 = i << 2;
    for (i6 = 0; i6 < 3; i6++) {
      b[i6] = z[(i6 + i5) + 1];
    }

    i5 = (1 + i) << 1;
    for (i6 = 0; i6 < 2; i6++) {
      d1 = 0.0;
      for (i7 = 0; i7 < 3; i7++) {
        d1 += Fx[i6 + (i7 << 1)] * b[i7];
      }

      b_Fx[i6] = d1 + Fu[i6] * z[(1 + i) << 2];
    }

    for (i6 = 0; i6 < 2; i6++) {
      y[i6 + i5] = b_Fx[i6];
    }
  }

  for (i5 = 0; i5 < 4; i5++) {
    b_Ff[i5] = 0.0;
    for (i6 = 0; i6 < 3; i6++) {
      b_Ff[i5] += Ff[i5 + (i6 << 2)] * z[37 + i6];
    }

    y[20 + i5] = b_Ff[i5];
  }
}

/*
 * utility for quick inversion of a symmetric positive definite matrix
 * Arguments    : double M
 * Return Type  : double
 */
static double mySymPDinv(double M)
{
  double A;
  if (M > 0.0) {
    A = sqrt(M);
  } else {
    A = M;
  }

  return 1.0 / A / A;
}

/*
 * use built in exponential
 * Arguments    : double u
 *                boolean_T flagNoPade
 * Return Type  : double
 */
static double myexp(double u, boolean_T flagNoPade)
{
  double y;
  double di;
  double ds;
  int ii;
  if (flagNoPade) {
    y = exp(u);
  } else {
    /*  use pade approximant */
    di = 1.0;
    ds = 1.0;
    for (ii = 0; ii < 3; ii++) {
      di = -1.0 / (1.0 + (double)ii) * di * u;
      ds += di;
    }

    y = 1.0 / ds;
  }

  return y;
}

/*
 * sizes
 * Arguments    : const double H[1600]
 *                const double g[40]
 *                const double P[960]
 *                const double h[24]
 *                const double C[1280]
 *                const double b[32]
 *                const double z0[40]
 *                const double A[9]
 *                const double B[3]
 *                const double Fx[6]
 *                const double Fu[2]
 *                const double Ff[12]
 *                const double Q[9]
 *                double b_R
 *                const double Qf[9]
 *                const double opts[6]
 *                const double Ps[1600]
 *                const double hs[40]
 *                const double Ef[6]
 *                const double Fxs[12]
 *                const double Fus[4]
 *                double z[40]
 *                double info[4]
 * Return Type  : void
 */
void mpcsolve(const double H[1600], const double g[40], const double P[960],
              const double h[24], const double C[1280], const double b[32],
              const double z0[40], const double A[9], const double B[3], const
              double Fx[6], const double Fu[2], const double Ff[12], const
              double Q[9], double b_R, const double Qf[9], const double opts[6],
              const double Ps[1600], const double hs[40], const double Ef[6],
              const double Fxs[12], const double Fus[4], double z[40], double
              info[4])
{
  boolean_T flagPhiIsDiag;
  boolean_T flagUseSoftCons;
  boolean_T flagChecking;
  boolean_T flagNoPade;
  double kappaPt[960];
  double kappaPtSq[960];
  int i1;
  int i2;
  double rhoPstSq[1600];
  double phi[1600];
  double diagTwoH[40];
  double blkQR[16];
  double es[40];
  double esNew[40];
  double dz[40];
  int i;
  double b_phi[1600];
  double dhats[40];
  double b_A[3];
  boolean_T b_P[24];
  double rpMagNew;
  int initSolChoice;
  double nu[32];
  double iFar[24];
  double iNew[24];
  double d[24];
  double rp[32];
  double rpMag;
  double b_diagTwoH[40];
  double b_C[40];
  double rd[40];
  double diagPhi[40];
  double rdMag;
  double b_rdMag[2];
  double rMag;
  double iterCount;
  int kk;
  boolean_T exitg1;
  double dv17[40];
  double phiInv[1600];
  double b_b[4];
  double blkInv[16];
  double ajj;
  int ii;
  int j;
  double b_dhats[4];
  double b_Fx[8];
  double dv18[8];
  double dv19[8];
  double b_Fxs[16];
  double dv20[16];
  double dv21[16];
  double c_Fx[8];
  int b_ii;
  int ix;
  double dv22[12];
  double tmp[9];
  double Y[9];
  double c_b[576];
  double d_b[576];
  double dv23[960];
  double dv24[960];
  double dv25[40];
  double e_b[1600];
  double b_Y[1024];
  double f_b[3];
  double c_A[9];
  int iy;
  double c_Y[9];
  int jj;
  double d_Y[6];
  double c_C[1280];
  double e_Y[1024];
  double rhs[32];
  double L[1024];
  boolean_T exitg6;
  int jmax;
  boolean_T exitg5;
  double dv26[6];
  boolean_T exitg4;
  double t[32];
  double b_rhs[2];
  double dnu[32];
  double rdNew[40];
  creal_T unusedExpr[40];
  boolean_T exitg3;
  double s;
  double b_nu[32];
  double rdMagNew[2];
  double dv27[32];
  double gradRmag;
  boolean_T exitg2;
  double b_rdMagNew[2];
  double rMagNew;

  /*  number of states in system */
  /*  number of inputs to system */
  /*  number of decision variables in z */
  /*  number of equalities in Cz=b */
  /*  number of inequalities Pz<=h */
  /*  number of soft constraints Ps*z<=hs (if possible) */
  /*  number of inequalities per time step, Fx*x + Fu*u <= f */
  /*  number of soft constraints per time step, Fxs*x + Fus*u <= fs */
  /*  number of terminal inequalities */
  /*  number of terminal equalities */
  /*  important to take T (the horizon) from here */
  /*  if you pass it in as a signal, code generator gets upset */
  /*  as it thinks its matrices could vary in size */
  /*  list of slack variables */
  /* % process options */
  /*  number of options passed in */
  /*  option 1 - assume Phi is diagonal if > 0 */
  flagPhiIsDiag = (opts[0] > 0.0);

  /*  turns on or off assumptions about diagonal Phi */
  /*  option 2 - set number of Newton iterations */
  /*  option 3 - use KS function for soft constraints if >0 */
  flagUseSoftCons = (opts[2] > 0.0);

  /*  option 4 - enable massive amount of checking (slow) if >0 */
  flagChecking = (opts[3] > 0.0);

  /*  option 5 - disable the Pade approximation if >0 */
  flagNoPade = (opts[4] > 0.0);

  /*  option 6 - norm tolerance for early stopping */
  /* % settings */
  /*  single fixed barrier weight */
  /*  fixed parameter for KS-function */
  /* % precalculations */
  /*  preform to avoid later work */
  for (i1 = 0; i1 < 24; i1++) {
    for (i2 = 0; i2 < 40; i2++) {
      kappaPt[i2 + 40 * i1] = 0.002 * P[i1 + 24 * i2];
      kappaPtSq[i2 + 40 * i1] = kappaPt[i2 + 40 * i1] * P[i1 + 24 * i2];
    }
  }

  for (i1 = 0; i1 < 40; i1++) {
    for (i2 = 0; i2 < 40; i2++) {
      rhoPstSq[i2 + 40 * i1] = 10.0 * Ps[i1 + 40 * i2] * Ps[i1 + 40 * i2];
    }
  }

  for (i1 = 0; i1 < 1600; i1++) {
    phi[i1] = 2.0 * H[i1];
  }

  diag(phi, diagTwoH);

  /*  helpful to avoid lots of blkdiag calls later */
  blkdiag(Q, b_R, blkQR);

  /*  pre-allocate for KS residuals */
  for (i = 0; i < 40; i++) {
    es[i] = hs[i];
    esNew[i] = hs[i];

    /*  pre-assignment to keep coder happy */
    dz[i] = 0.0;
  }

  memset(&b_phi[0], 0, 1600U * sizeof(double));
  memset(&dhats[0], 0, 40U * sizeof(double));

  /* % form initial solution */
  /*  form the tail of the previous solution */
  /*  plus a step of zero control on the end */
  /*  hack - catch the slack case */
  /*  no slacks - ok for zeros at end */
  for (i1 = 0; i1 < 3; i1++) {
    b_A[i1] = 0.0;
    for (i2 = 0; i2 < 3; i2++) {
      b_A[i1] += A[i1 + 3 * i2] * z0[37 + i2];
    }
  }

  memcpy(&z[0], &z0[4], 36U * sizeof(double));
  z[36] = 0.0;
  for (i1 = 0; i1 < 3; i1++) {
    z[i1 + 37] = b_A[i1];
  }

  /*  check if tail works as an initializer */
  for (i1 = 0; i1 < 24; i1++) {
    rpMagNew = 0.0;
    for (i2 = 0; i2 < 40; i2++) {
      rpMagNew += P[i1 + 24 * i2] * z[i2];
    }

    b_P[i1] = (rpMagNew < h[i1]);
  }

  if (all(b_P)) {
    /*  tail is feasible */
    initSolChoice = 1;
  } else {
    /*  try fiddling with the slack variables */
    /*  catch just the slack case */
    /*  now check if that worked */
    for (i1 = 0; i1 < 24; i1++) {
      rpMagNew = 0.0;
      for (i2 = 0; i2 < 40; i2++) {
        rpMagNew += P[i1 + 24 * i2] * z[i2];
      }

      b_P[i1] = (rpMagNew < h[i1]);
    }

    if (all(b_P)) {
      /*  worked */
      initSolChoice = 4;
    } else {
      for (i1 = 0; i1 < 24; i1++) {
        rpMagNew = 0.0;
        for (i2 = 0; i2 < 40; i2++) {
          rpMagNew += P[i1 + 24 * i2] * z0[i2];
        }

        b_P[i1] = (rpMagNew < h[i1]);
      }

      if (all(b_P)) {
        /*  try last solution unchanged */
        memcpy(&z[0], &z0[0], 40U * sizeof(double));
        initSolChoice = 2;
      } else {
        for (i = 0; i < 24; i++) {
          b_P[i] = (0.0 < h[i]);
        }

        if (all(b_P)) {
          /*  in this case, start with zeros */
          memset(&z[0], 0, 40U * sizeof(double));
          initSolChoice = 3;
        } else {
          /*  out of ideas - zeros anyway */
          memset(&z[0], 0, 40U * sizeof(double));
          initSolChoice = 0;
        }
      }
    }
  }

  /* % initialization */
  /*  initial lagrange multipliers */
  memset(&nu[0], 0, sizeof(double) << 5);

  /*  precalculate d */
  multByP(z, Fx, Fu, Ff, iFar);
  for (i = 0; i < 24; i++) {
    iNew[i] = h[i] - iFar[i];
  }

  rdivide(1.0, iNew, d);

  /*  calculate residuals for first iteration */
  calcRp(z, b, A, B, Ef, rp);

  /* C*z - b; */
  rpMag = norm(rp);
  for (i1 = 0; i1 < 40; i1++) {
    rpMagNew = 0.0;
    for (i2 = 0; i2 < 24; i2++) {
      rpMagNew += kappaPt[i1 + 40 * i2] * d[i2];
    }

    b_diagTwoH[i1] = (diagTwoH[i1] * z[i1] + g[i1]) + rpMagNew;
  }

  for (i1 = 0; i1 < 40; i1++) {
    b_C[i1] = 0.0;
    for (i2 = 0; i2 < 32; i2++) {
      b_C[i1] += C[i2 + (i1 << 5)] * 0.0;
    }

    rd[i1] = b_diagTwoH[i1] + b_C[i1];
  }

  /*  optional soft constraint info */
  if (flagUseSoftCons) {
    /*  evaluate soft version of d */
    calcDs(z, Ps, es, 10.0, flagNoPade, diagPhi);

    /*  add to residual */
    for (i1 = 0; i1 < 40; i1++) {
      rpMagNew = 0.0;
      for (i2 = 0; i2 < 40; i2++) {
        rpMagNew += Ps[i2 + 40 * i1] * diagPhi[i2];
      }

      rd[i1] += rpMagNew;
    }
  }

  rdMag = b_norm(rd);
  b_rdMag[0] = rdMag;
  b_rdMag[1] = rpMag;
  rMag = c_norm(b_rdMag);

  /* % main solution loop for Newton's method */
  iterCount = opts[1];
  kk = 0;
  exitg1 = false;
  while ((!exitg1) && (kk <= (int)opts[1] - 1)) {
    /*  check the P multiplier */
    /*  check residual calc */
    /*  if using soft cons with KS */
    if (flagUseSoftCons) {
      /*  need the "d-hat" for the second derivatives of the KS functions */
      for (i = 0; i < 40; i++) {
        b_diagTwoH[i] = (1.0 + es[i]) * (1.0 + es[i]);
      }

      b_rdivide(es, b_diagTwoH, dhats);
    }

    /*  first form inverse of Phi */
    if (flagPhiIsDiag) {
      /*  form the diagonals of Phi */
      for (i1 = 0; i1 < 24; i1++) {
        iNew[i1] = d[i1] * d[i1];
      }

      for (i1 = 0; i1 < 40; i1++) {
        rpMagNew = 0.0;
        for (i2 = 0; i2 < 24; i2++) {
          rpMagNew += kappaPtSq[i1 + 40 * i2] * iNew[i2];
        }

        diagPhi[i1] = diagTwoH[i1] + rpMagNew;
      }

      /*  plus soft cons if used */
      if (flagUseSoftCons) {
        for (i1 = 0; i1 < 40; i1++) {
          rpMagNew = 0.0;
          for (i2 = 0; i2 < 40; i2++) {
            rpMagNew += rhoPstSq[i1 + 40 * i2] * dhats[i2];
          }

          diagPhi[i1] += rpMagNew;
        }
      }

      /*  "invert" it */
      c_rdivide(1.0, diagPhi, dv17);
      b_diag(dv17, phiInv);
    } else {
      /*  preallocate to avoid slowdown */
      memset(&phiInv[0], 0, 1600U * sizeof(double));

      /*  build the blocks of Phi inverse */
      if (flagUseSoftCons) {
        for (i = 0; i < 2; i++) {
          b_rdMag[i] = d[i] * d[i];
        }

        c_diag(b_rdMag, b_b);
        d_diag(*(double (*)[4])&dhats[0], blkInv);
        rpMagNew = 0.0;
        for (i1 = 0; i1 < 2; i1++) {
          b_rdMag[i1] = 0.0;
          for (i2 = 0; i2 < 2; i2++) {
            b_rdMag[i1] += 0.002 * Fu[i2] * b_b[i2 + (i1 << 1)];
          }

          rpMagNew += b_rdMag[i1] * Fu[i1];
        }

        ajj = 0.0;
        for (i1 = 0; i1 < 4; i1++) {
          b_b[i1] = 0.0;
          for (i2 = 0; i2 < 4; i2++) {
            b_b[i1] += 10.0 * Fus[i2] * blkInv[i2 + (i1 << 2)];
          }

          ajj += b_b[i1] * Fus[i1];
        }

        phiInv[0] = mySymPDinv((2.0 * b_R + rpMagNew) + ajj);
      } else {
        for (i = 0; i < 2; i++) {
          b_rdMag[i] = d[i] * d[i];
        }

        c_diag(b_rdMag, b_b);
        rpMagNew = 0.0;
        for (i1 = 0; i1 < 2; i1++) {
          b_rdMag[i1] = 0.0;
          for (i2 = 0; i2 < 2; i2++) {
            b_rdMag[i1] += 0.002 * Fu[i2] * b_b[i2 + (i1 << 1)];
          }

          rpMagNew += b_rdMag[i1] * Fu[i1];
        }

        phiInv[0] = mySymPDinv(2.0 * b_R + rpMagNew);
      }

      for (ii = 0; ii < 9; ii++) {
        if (flagUseSoftCons) {
          i1 = ((1 + ii) << 1) - 1;
          i2 = ((1 + ii) << 1) - 1;
          for (j = 0; j < 2; j++) {
            b_rdMag[j] = d[(j + i1) + 1] * d[(j + i2) + 1];
          }

          c_diag(b_rdMag, b_b);
          i1 = ((1 + ii) << 2) - 1;
          for (i2 = 0; i2 < 4; i2++) {
            b_dhats[i2] = dhats[(i2 + i1) + 1];
          }

          d_diag(b_dhats, blkInv);
          for (i1 = 0; i1 < 2; i1++) {
            for (i2 = 0; i2 < 3; i2++) {
              b_Fx[i2 + (i1 << 2)] = Fx[i1 + (i2 << 1)];
            }

            b_Fx[3 + (i1 << 2)] = Fu[i1];
            for (i2 = 0; i2 < 4; i2++) {
              dv18[i2 + (i1 << 2)] = 0.002 * b_Fx[i2 + (i1 << 2)];
            }
          }

          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 2; i2++) {
              dv19[i1 + (i2 << 2)] = 0.0;
              for (j = 0; j < 2; j++) {
                dv19[i1 + (i2 << 2)] += dv18[i1 + (j << 2)] * b_b[j + (i2 << 1)];
              }
            }
          }

          for (i1 = 0; i1 < 3; i1++) {
            for (i2 = 0; i2 < 2; i2++) {
              b_Fx[i2 + (i1 << 1)] = Fx[i2 + (i1 << 1)];
            }
          }

          for (i1 = 0; i1 < 2; i1++) {
            b_Fx[6 + i1] = Fu[i1];
          }

          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 3; i2++) {
              b_Fxs[i2 + (i1 << 2)] = Fxs[i1 + (i2 << 2)];
            }

            b_Fxs[3 + (i1 << 2)] = Fus[i1];
            for (i2 = 0; i2 < 4; i2++) {
              dv20[i2 + (i1 << 2)] = 10.0 * b_Fxs[i2 + (i1 << 2)];
            }
          }

          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 4; i2++) {
              dv21[i1 + (i2 << 2)] = 0.0;
              for (j = 0; j < 4; j++) {
                dv21[i1 + (i2 << 2)] += dv20[i1 + (j << 2)] * blkInv[j + (i2 <<
                  2)];
              }
            }
          }

          for (i1 = 0; i1 < 3; i1++) {
            for (i2 = 0; i2 < 4; i2++) {
              b_Fxs[i2 + (i1 << 2)] = Fxs[i2 + (i1 << 2)];
            }
          }

          for (i1 = 0; i1 < 4; i1++) {
            b_Fxs[12 + i1] = Fus[i1];
          }

          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 4; i2++) {
              rpMagNew = 0.0;
              for (j = 0; j < 2; j++) {
                rpMagNew += dv19[i1 + (j << 2)] * b_Fx[j + (i2 << 1)];
              }

              dv20[i1 + (i2 << 2)] = 2.0 * blkQR[i1 + (i2 << 2)] + rpMagNew;
            }
          }

          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 4; i2++) {
              blkInv[i1 + (i2 << 2)] = 0.0;
              for (j = 0; j < 4; j++) {
                blkInv[i1 + (i2 << 2)] += dv21[i1 + (j << 2)] * b_Fxs[j + (i2 <<
                  2)];
              }
            }
          }

          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 4; i2++) {
              dv21[i2 + (i1 << 2)] = dv20[i2 + (i1 << 2)] + blkInv[i2 + (i1 << 2)];
            }
          }

          b_mySymPDinv(dv21, flagChecking, blkInv);
        } else {
          i1 = ((1 + ii) << 1) - 1;
          i2 = ((1 + ii) << 1) - 1;
          for (j = 0; j < 2; j++) {
            b_rdMag[j] = d[(j + i1) + 1] * d[(j + i2) + 1];
            for (i = 0; i < 3; i++) {
              c_Fx[i + (j << 2)] = Fx[j + (i << 1)];
            }

            c_Fx[3 + (j << 2)] = Fu[j];
            for (i = 0; i < 4; i++) {
              dv18[i + (j << 2)] = 0.002 * c_Fx[i + (j << 2)];
            }
          }

          c_diag(b_rdMag, b_b);
          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 2; i2++) {
              dv19[i1 + (i2 << 2)] = 0.0;
              for (j = 0; j < 2; j++) {
                dv19[i1 + (i2 << 2)] += dv18[i1 + (j << 2)] * b_b[j + (i2 << 1)];
              }
            }
          }

          for (i1 = 0; i1 < 3; i1++) {
            for (i2 = 0; i2 < 2; i2++) {
              b_Fx[i2 + (i1 << 1)] = Fx[i2 + (i1 << 1)];
            }
          }

          for (i1 = 0; i1 < 2; i1++) {
            b_Fx[6 + i1] = Fu[i1];
          }

          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 4; i2++) {
              rpMagNew = 0.0;
              for (j = 0; j < 2; j++) {
                rpMagNew += dv19[i1 + (j << 2)] * b_Fx[j + (i2 << 1)];
              }

              dv20[i1 + (i2 << 2)] = 2.0 * blkQR[i1 + (i2 << 2)] + rpMagNew;
            }
          }

          b_mySymPDinv(dv20, flagChecking, blkInv);
        }

        b_ii = ii << 2;
        ix = ii << 2;
        for (i1 = 0; i1 < 4; i1++) {
          for (i2 = 0; i2 < 4; i2++) {
            phiInv[((i2 + b_ii) + 40 * ((i1 + ix) + 1)) + 1] = blkInv[i2 + (i1 <<
              2)];
          }
        }

        /*  [Q-tilde S-tilde; S-tilde' R-tilde] */
      }

      for (i = 0; i < 4; i++) {
        b_b[i] = d[i + 20] * d[i + 20];
      }

      d_diag(b_b, blkInv);
      for (i1 = 0; i1 < 3; i1++) {
        for (i2 = 0; i2 < 4; i2++) {
          dv22[i1 + 3 * i2] = 0.0;
          for (j = 0; j < 4; j++) {
            dv22[i1 + 3 * i2] += 0.002 * Ff[j + (i1 << 2)] * blkInv[j + (i2 << 2)];
          }
        }
      }

      for (i1 = 0; i1 < 3; i1++) {
        for (i2 = 0; i2 < 3; i2++) {
          rpMagNew = 0.0;
          for (j = 0; j < 4; j++) {
            rpMagNew += dv22[i1 + 3 * j] * Ff[j + (i2 << 2)];
          }

          tmp[i1 + 3 * i2] = 2.0 * Qf[i1 + 3 * i2] + rpMagNew;
        }
      }

      c_mySymPDinv(tmp, flagChecking, Y);
      for (i1 = 0; i1 < 3; i1++) {
        for (i2 = 0; i2 < 3; i2++) {
          phiInv[(i2 + 40 * (37 + i1)) + 37] = Y[i2 + 3 * i1];
        }
      }
    }

    /*  check phi inverted correctly */
    if (flagChecking) {
      e_diag(d, c_b);
      e_diag(d, d_b);
      for (i1 = 0; i1 < 40; i1++) {
        for (i2 = 0; i2 < 24; i2++) {
          dv23[i1 + 40 * i2] = 0.0;
          for (j = 0; j < 24; j++) {
            dv23[i1 + 40 * i2] += 0.002 * P[j + 24 * i1] * c_b[j + 24 * i2];
          }
        }

        for (i2 = 0; i2 < 24; i2++) {
          dv24[i1 + 40 * i2] = 0.0;
          for (j = 0; j < 24; j++) {
            dv24[i1 + 40 * i2] += dv23[i1 + 40 * j] * d_b[j + 24 * i2];
          }
        }
      }

      for (i1 = 0; i1 < 40; i1++) {
        for (i2 = 0; i2 < 40; i2++) {
          rpMagNew = 0.0;
          for (j = 0; j < 24; j++) {
            rpMagNew += dv24[i1 + 40 * j] * P[j + 24 * i2];
          }

          b_phi[i1 + 40 * i2] = 2.0 * H[i1 + 40 * i2] + rpMagNew;
        }
      }

      if (flagUseSoftCons) {
        for (i = 0; i < 40; i++) {
          b_diagTwoH[i] = (1.0 + es[i]) * (1.0 + es[i]);
        }

        b_rdivide(es, b_diagTwoH, dv25);
        b_diag(dv25, e_b);
        for (i1 = 0; i1 < 40; i1++) {
          for (i2 = 0; i2 < 40; i2++) {
            phi[i1 + 40 * i2] = 0.0;
            for (j = 0; j < 40; j++) {
              phi[i1 + 40 * i2] += 10.0 * Ps[j + 40 * i1] * e_b[j + 40 * i2];
            }
          }
        }

        for (i1 = 0; i1 < 40; i1++) {
          for (i2 = 0; i2 < 40; i2++) {
            rpMagNew = 0.0;
            for (j = 0; j < 40; j++) {
              rpMagNew += phi[i1 + 40 * j] * Ps[j + 40 * i2];
            }

            b_phi[i1 + 40 * i2] += rpMagNew;
          }
        }
      }

      eye(e_b);
      for (i1 = 0; i1 < 40; i1++) {
        for (i2 = 0; i2 < 40; i2++) {
          rpMagNew = 0.0;
          for (j = 0; j < 40; j++) {
            rpMagNew += b_phi[i1 + 40 * j] * phiInv[j + 40 * i2];
          }

          phi[i1 + 40 * i2] = rpMagNew - e_b[i1 + 40 * i2];
        }
      }

      d_norm(phi);

      /* checkPhiInv = (phi*phiInv - eye(nz)) */
    }

    /*  preallocate Y */
    memset(&b_Y[0], 0, sizeof(double) << 10);

    /*  form the block elements of Y = C*phiInv*C' */
    /*  some functions to get block terms Q,R and S out of phi-inverse easily */
    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_Y[i1 + (i2 << 5)] = B[i1] * phiInv[0] * B[i2] + phiInv[(i1 + 40 * (1 +
          i2)) + 1];
      }
    }

    for (ii = 0; ii < 10; ii++) {
      if (1 + ii < 10) {
        /*  some functions to get block terms Q,R and S out of phi-inverse easily */
        i1 = ii << 2;
        i2 = ii << 2;
        Stil(phiInv, 1.0 + (double)ii, f_b);
        b_ii = ii * 3;
        j = (1 + ii) * 3;
        for (i = 0; i < 3; i++) {
          for (iy = 0; iy < 3; iy++) {
            c_A[iy + 3 * i] = phiInv[((iy + i1) + 40 * ((i + i2) + 1)) + 1];
            Y[iy + 3 * i] = -c_A[iy + 3 * i];
          }
        }

        for (i1 = 0; i1 < 3; i1++) {
          for (i2 = 0; i2 < 3; i2++) {
            c_A[i1 + 3 * i2] = 0.0;
            for (i = 0; i < 3; i++) {
              c_A[i1 + 3 * i2] += Y[i1 + 3 * i] * A[i2 + 3 * i];
            }

            tmp[i1 + 3 * i2] = f_b[i1] * B[i2];
          }
        }

        for (i1 = 0; i1 < 3; i1++) {
          for (i2 = 0; i2 < 3; i2++) {
            b_Y[(i2 + b_ii) + ((i1 + j) << 5)] = c_A[i2 + 3 * i1] - tmp[i2 + 3 *
              i1];
          }
        }

        /* Yabove(:,:,ii) */
        i1 = (1 + ii) * 3;
        b_ii = ii * 3;
        i2 = (1 + ii) * 3;
        ix = ii * 3;
        for (j = 0; j < 3; j++) {
          for (i = 0; i < 3; i++) {
            c_Y[i + 3 * j] = b_Y[(j + ix) + ((i + i2) << 5)];
          }
        }

        for (i2 = 0; i2 < 3; i2++) {
          for (j = 0; j < 3; j++) {
            b_Y[(j + i1) + ((i2 + b_ii) << 5)] = c_Y[j + 3 * i2];
          }
        }
      }

      if (1 + ii > 1) {
        Stil(phiInv, (1.0 + (double)ii) - 1.0, f_b);

        /*  some functions to get block terms Q,R and S out of phi-inverse easily */
        i1 = (ii - 1) << 2;
        i2 = (ii - 1) << 2;

        /*  some functions to get block terms Q,R and S out of phi-inverse easily */
        j = ii << 2;
        i = ii << 2;
        for (iy = 0; iy < 3; iy++) {
          b_A[iy] = 0.0;
          for (jj = 0; jj < 3; jj++) {
            b_A[iy] += A[iy + 3 * jj] * f_b[jj];
          }

          for (jj = 0; jj < 3; jj++) {
            tmp[iy + 3 * jj] = b_A[iy] * B[jj];
            c_A[jj + 3 * iy] = phiInv[((jj + i1) + 40 * ((iy + i2) + 1)) + 1];
            c_Y[jj + 3 * iy] = phiInv[((jj + j) + 40 * ((iy + i) + 1)) + 1];
          }
        }

        b_ii = ii * 3;
        ix = ii * 3;
        for (i1 = 0; i1 < 3; i1++) {
          for (i2 = 0; i2 < 3; i2++) {
            Y[i1 + 3 * i2] = 0.0;
            for (j = 0; j < 3; j++) {
              Y[i1 + 3 * i2] += A[i1 + 3 * j] * c_A[j + 3 * i2];
            }
          }
        }

        for (i1 = 0; i1 < 3; i1++) {
          for (i2 = 0; i2 < 3; i2++) {
            rpMagNew = 0.0;
            for (j = 0; j < 3; j++) {
              rpMagNew += Y[i1 + 3 * j] * A[i2 + 3 * j];
            }

            c_A[i1 + 3 * i2] = (rpMagNew + tmp[i1 + 3 * i2]) + tmp[i2 + 3 * i1];
          }
        }

        for (i1 = 0; i1 < 3; i1++) {
          for (i2 = 0; i2 < 3; i2++) {
            tmp[i1 + 3 * i2] = B[i1] * phiInv[(ii << 2) + 40 * (ii << 2)] * B[i2];
          }
        }

        for (i1 = 0; i1 < 3; i1++) {
          for (i2 = 0; i2 < 3; i2++) {
            b_Y[(i2 + b_ii) + ((i1 + ix) << 5)] = (c_A[i2 + 3 * i1] + tmp[i2 + 3
              * i1]) + c_Y[i2 + 3 * i1];
          }
        }
      }
    }

    /*  add terms for terminal equality cons */
    /*  some functions to get block terms Q,R and S out of phi-inverse easily */
    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 2; i2++) {
        b_Y[(i1 + ((30 + i2) << 5)) + 27] = 0.0;
        for (j = 0; j < 3; j++) {
          b_Y[(i1 + ((30 + i2) << 5)) + 27] += phiInv[(i1 + 40 * (37 + j)) + 37]
            * Ef[i2 + (j << 1)];
        }

        d_Y[i2 + (i1 << 1)] = b_Y[(i1 + ((30 + i2) << 5)) + 27];
      }
    }

    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 2; i2++) {
        b_Y[(i2 + ((27 + i1) << 5)) + 30] = d_Y[i2 + (i1 << 1)];
      }
    }

    for (i1 = 0; i1 < 2; i1++) {
      for (i2 = 0; i2 < 2; i2++) {
        b_b[i1 + (i2 << 1)] = 0.0;
        for (j = 0; j < 3; j++) {
          b_b[i1 + (i2 << 1)] += Ef[i1 + (j << 1)] * b_Y[(j + ((30 + i2) << 5))
            + 27];
        }
      }
    }

    for (i1 = 0; i1 < 2; i1++) {
      for (i2 = 0; i2 < 2; i2++) {
        b_Y[(i2 + ((30 + i1) << 5)) + 30] = b_b[i2 + (i1 << 1)];
      }
    }

    /*  now check that Y was constructed correctly */
    if (flagChecking) {
      for (i1 = 0; i1 < 32; i1++) {
        for (i2 = 0; i2 < 40; i2++) {
          c_C[i1 + (i2 << 5)] = 0.0;
          for (j = 0; j < 40; j++) {
            c_C[i1 + (i2 << 5)] += C[i1 + (j << 5)] * phiInv[j + 40 * i2];
          }
        }
      }

      for (i1 = 0; i1 < 32; i1++) {
        for (i2 = 0; i2 < 32; i2++) {
          rpMagNew = 0.0;
          for (j = 0; j < 40; j++) {
            rpMagNew += c_C[i1 + (j << 5)] * C[i2 + (j << 5)];
          }

          e_Y[i1 + (i2 << 5)] = b_Y[i1 + (i2 << 5)] - rpMagNew;
        }
      }

      e_norm(e_Y);
    }

    /*  now form PhiInv * rd in preparation for making the RHS (-beta) */
    memset(&diagPhi[0], 0, 40U * sizeof(double));
    diagPhi[0] = phiInv[0] * rd[0];
    for (ii = 0; ii < 9; ii++) {
      /*  some functions to get block terms Q,R and S out of phi-inverse easily */
      i1 = ii << 2;
      i2 = ii << 2;
      Stil(phiInv, 1.0 + (double)ii, f_b);
      Stil(phiInv, 1.0 + (double)ii, b_A);
      for (j = 0; j < 3; j++) {
        for (i = 0; i < 3; i++) {
          c_A[i + 3 * j] = phiInv[((i + i1) + 40 * ((j + i2) + 1)) + 1];
          blkInv[i + (j << 2)] = c_A[i + 3 * j];
        }
      }

      for (i1 = 0; i1 < 3; i1++) {
        blkInv[12 + i1] = f_b[i1];
      }

      for (i1 = 0; i1 < 3; i1++) {
        blkInv[3 + (i1 << 2)] = b_A[i1];
      }

      blkInv[15] = phiInv[((1 + ii) << 2) + 40 * ((1 + ii) << 2)];
      b_ii = ii << 2;
      for (i1 = 0; i1 < 4; i1++) {
        b_b[i1] = rd[(i1 + b_ii) + 1];
      }

      b_ii = ii << 2;
      for (i1 = 0; i1 < 4; i1++) {
        diagPhi[(i1 + b_ii) + 1] = 0.0;
        for (i2 = 0; i2 < 4; i2++) {
          diagPhi[(i1 + b_ii) + 1] += blkInv[i1 + (i2 << 2)] * b_b[i2];
        }
      }
    }

    /*  some functions to get block terms Q,R and S out of phi-inverse easily */
    for (i1 = 0; i1 < 3; i1++) {
      diagPhi[37 + i1] = 0.0;
      for (i2 = 0; i2 < 3; i2++) {
        diagPhi[37 + i1] += phiInv[(i1 + 40 * (37 + i2)) + 37] * rd[37 + i2];
      }
    }

    /*  and the RHS, -beta = rp - C*phiInv*rd */
    multByC(diagPhi, A, B, Ef, rhs);
    for (i1 = 0; i1 < 32; i1++) {
      rhs[i1] = rp[i1] - rhs[i1];
    }

    /*  check it */
    /*  now find the blocks of the lower triangular Cholesky factorization of Y */
    memset(&L[0], 0, sizeof(double) << 10);

    /*  another function to get n x n square block elements */
    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 3; i2++) {
        c_A[i2 + 3 * i1] = b_Y[i2 + (i1 << 5)];
      }
    }

    b_ii = 0;
    j = 0;
    exitg6 = false;
    while ((!exitg6) && (j + 1 < 4)) {
      jj = j + j * 3;
      ajj = 0.0;
      if (j < 1) {
      } else {
        ix = j;
        iy = j;
        for (jmax = 1; jmax <= j; jmax++) {
          ajj += c_A[ix] * c_A[iy];
          ix += 3;
          iy += 3;
        }
      }

      ajj = c_A[jj] - ajj;
      if (ajj > 0.0) {
        ajj = sqrt(ajj);
        c_A[jj] = ajj;
        if (j + 1 < 3) {
          if (j == 0) {
          } else {
            ix = j;
            i1 = (j + 3 * (j - 1)) + 2;
            for (jmax = j + 2; jmax <= i1; jmax += 3) {
              rpMagNew = -c_A[ix];
              iy = jj + 1;
              i2 = (jmax - j) + 1;
              for (i = jmax; i <= i2; i++) {
                c_A[iy] += c_A[i - 1] * rpMagNew;
                iy++;
              }

              ix += 3;
            }
          }

          ajj = 1.0 / ajj;
          i1 = (jj - j) + 3;
          for (jmax = jj + 1; jmax + 1 <= i1; jmax++) {
            c_A[jmax] *= ajj;
          }
        }

        j++;
      } else {
        c_A[jj] = ajj;
        b_ii = j + 1;
        exitg6 = true;
      }
    }

    if (b_ii == 0) {
      jmax = 3;
    } else {
      jmax = b_ii - 1;
    }

    for (j = 1; j + 1 <= jmax; j++) {
      for (i = 1; i <= j; i++) {
        c_A[(i + 3 * j) - 1] = 0.0;
      }
    }

    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 3; i2++) {
        L[i2 + (i1 << 5)] = c_A[i2 + 3 * i1];
      }
    }

    for (ii = 0; ii < 9; ii++) {
      /*  another function to get n x n square block elements */
      b_ii = ii * 3;
      ix = ii * 3;

      /*  another function to get n x n square block elements */
      jmax = ii * 3;
      i1 = (1 + ii) * 3;
      for (i2 = 0; i2 < 3; i2++) {
        for (j = 0; j < 3; j++) {
          c_Y[j + 3 * i2] = L[(j + b_ii) + ((i2 + ix) << 5)];
          Y[j + 3 * i2] = b_Y[(j + jmax) + ((i2 + i1) << 5)];
        }
      }

      linsolve(c_Y, Y, c_A);
      i1 = (1 + ii) * 3;
      b_ii = ii * 3;
      for (i2 = 0; i2 < 3; i2++) {
        for (j = 0; j < 3; j++) {
          L[(j + i1) + ((i2 + b_ii) << 5)] = c_A[i2 + 3 * j];
        }
      }

      /*  another function to get n x n square block elements */
      i1 = (1 + ii) * 3;
      i2 = (1 + ii) * 3;

      /*  another function to get n x n square block elements */
      j = (1 + ii) * 3;
      b_ii = ii * 3;

      /*  another function to get n x n square block elements */
      i = (1 + ii) * 3;
      ix = ii * 3;
      for (iy = 0; iy < 3; iy++) {
        for (jj = 0; jj < 3; jj++) {
          c_Y[jj + 3 * iy] = b_Y[(jj + i1) + ((iy + i2) << 5)];
          Y[jj + 3 * iy] = L[(jj + j) + ((iy + b_ii) << 5)];
          tmp[jj + 3 * iy] = L[(jj + i) + ((iy + ix) << 5)];
        }
      }

      for (i1 = 0; i1 < 3; i1++) {
        for (i2 = 0; i2 < 3; i2++) {
          rpMagNew = 0.0;
          for (j = 0; j < 3; j++) {
            rpMagNew += Y[i1 + 3 * j] * tmp[i2 + 3 * j];
          }

          c_A[i1 + 3 * i2] = c_Y[i1 + 3 * i2] - rpMagNew;
        }
      }

      b_ii = 0;
      j = 0;
      exitg5 = false;
      while ((!exitg5) && (j + 1 < 4)) {
        jj = j + j * 3;
        ajj = 0.0;
        if (j < 1) {
        } else {
          ix = j;
          iy = j;
          for (jmax = 1; jmax <= j; jmax++) {
            ajj += c_A[ix] * c_A[iy];
            ix += 3;
            iy += 3;
          }
        }

        ajj = c_A[jj] - ajj;
        if (ajj > 0.0) {
          ajj = sqrt(ajj);
          c_A[jj] = ajj;
          if (j + 1 < 3) {
            if (j == 0) {
            } else {
              ix = j;
              i1 = (j + 3 * (j - 1)) + 2;
              for (jmax = j + 2; jmax <= i1; jmax += 3) {
                rpMagNew = -c_A[ix];
                iy = jj + 1;
                i2 = (jmax - j) + 1;
                for (i = jmax; i <= i2; i++) {
                  c_A[iy] += c_A[i - 1] * rpMagNew;
                  iy++;
                }

                ix += 3;
              }
            }

            ajj = 1.0 / ajj;
            i1 = (jj - j) + 3;
            for (jmax = jj + 1; jmax + 1 <= i1; jmax++) {
              c_A[jmax] *= ajj;
            }
          }

          j++;
        } else {
          c_A[jj] = ajj;
          b_ii = j + 1;
          exitg5 = true;
        }
      }

      if (b_ii == 0) {
        jmax = 3;
      } else {
        jmax = b_ii - 1;
      }

      for (j = 1; j + 1 <= jmax; j++) {
        for (i = 1; i <= j; i++) {
          c_A[(i + 3 * j) - 1] = 0.0;
        }
      }

      i1 = (1 + ii) * 3;
      i2 = (1 + ii) * 3;
      for (j = 0; j < 3; j++) {
        for (i = 0; i < 3; i++) {
          L[(i + i1) + ((j + i2) << 5)] = c_A[i + 3 * j];
        }
      }
    }

    /*  and the extra bits for terminal equality cons */
    /*  another function to get n x n square block elements */
    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 3; i2++) {
        tmp[i2 + 3 * i1] = L[(i2 + ((27 + i1) << 5)) + 27];
      }
    }

    for (i1 = 0; i1 < 2; i1++) {
      for (i2 = 0; i2 < 3; i2++) {
        d_Y[i2 + 3 * i1] = b_Y[(i2 + ((30 + i1) << 5)) + 27];
      }
    }

    b_linsolve(tmp, d_Y, dv26);
    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 2; i2++) {
        L[(i2 + ((27 + i1) << 5)) + 30] = dv26[i1 + 3 * i2];
      }
    }

    for (i1 = 0; i1 < 2; i1++) {
      for (i2 = 0; i2 < 2; i2++) {
        rpMagNew = 0.0;
        for (j = 0; j < 3; j++) {
          rpMagNew += L[(i1 + ((27 + j) << 5)) + 30] * L[(i2 + ((27 + j) << 5))
            + 30];
        }

        b_b[i1 + (i2 << 1)] = b_Y[(i1 + ((30 + i2) << 5)) + 30] - rpMagNew;
      }
    }

    b_ii = 0;
    j = 0;
    exitg4 = false;
    while ((!exitg4) && (j + 1 < 3)) {
      jj = j + (j << 1);
      ajj = 0.0;
      if (j < 1) {
      } else {
        ix = j;
        iy = j;
        jmax = 1;
        while (jmax <= j) {
          ajj += b_b[ix] * b_b[iy];
          ix += 2;
          iy += 2;
          jmax = 2;
        }
      }

      ajj = b_b[jj] - ajj;
      if (ajj > 0.0) {
        ajj = sqrt(ajj);
        b_b[jj] = ajj;
        if (j + 1 < 2) {
          ajj = 1.0 / ajj;
          for (jmax = jj + 1; jmax + 1 <= jj + 2; jmax++) {
            b_b[jmax] *= ajj;
          }
        }

        j++;
      } else {
        b_b[jj] = ajj;
        b_ii = j + 1;
        exitg4 = true;
      }
    }

    if (b_ii == 0) {
      jmax = 2;
    } else {
      jmax = b_ii - 1;
    }

    j = 2;
    while (j <= jmax) {
      b_b[2] = 0.0;
      j = 3;
    }

    for (i1 = 0; i1 < 2; i1++) {
      for (i2 = 0; i2 < 2; i2++) {
        L[(i2 + ((30 + i1) << 5)) + 30] = b_b[i2 + (i1 << 1)];
      }
    }

    /*  now check the thing */
    if (flagChecking) {
      for (i1 = 0; i1 < 32; i1++) {
        for (i2 = 0; i2 < 32; i2++) {
          rpMagNew = 0.0;
          for (j = 0; j < 32; j++) {
            rpMagNew += L[i1 + (j << 5)] * L[i2 + (j << 5)];
          }

          e_Y[i1 + (i2 << 5)] = rpMagNew - b_Y[i1 + (i2 << 5)];
        }
      }

      e_norm(e_Y);
    }

    /*  solve (L*L')*dnu=rhs: part one: solve for t=L'*dnu */
    memset(&t[0], 0, sizeof(double) << 5);

    /*  another function to get n x n square block elements */
    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 3; i2++) {
        tmp[i2 + 3 * i1] = L[i2 + (i1 << 5)];
      }
    }

    c_linsolve(tmp, *(double (*)[3])&rhs[0], f_b);
    for (i = 0; i < 3; i++) {
      t[i] = f_b[i];
    }

    for (ii = 0; ii < 9; ii++) {
      /*  another function to get n x n square block elements */
      i1 = (1 + ii) * 3;
      i2 = (1 + ii) * 3;

      /*  another function to get n x n square block elements */
      j = (1 + ii) * 3;
      b_ii = ii * 3;
      ix = ii * 3 - 1;
      for (i = 0; i < 3; i++) {
        for (iy = 0; iy < 3; iy++) {
          c_Y[iy + 3 * i] = L[(iy + i1) + ((i + i2) << 5)];
          Y[iy + 3 * i] = L[(iy + j) + ((i + b_ii) << 5)];
        }

        f_b[i] = t[(i + ix) + 1];
      }

      i1 = (1 + ii) * 3 - 1;
      for (i2 = 0; i2 < 3; i2++) {
        rpMagNew = 0.0;
        for (j = 0; j < 3; j++) {
          rpMagNew += Y[i2 + 3 * j] * f_b[j];
        }

        b_A[i2] = rhs[(i2 + i1) + 1] - rpMagNew;
      }

      c_linsolve(c_Y, b_A, f_b);
      for (i = 0; i < 3; i++) {
        t[i + (1 + ii) * 3] = f_b[i];
      }
    }

    /*  final elements for terminal equalities */
    for (i1 = 0; i1 < 2; i1++) {
      for (i2 = 0; i2 < 2; i2++) {
        b_b[i2 + (i1 << 1)] = L[(i2 + ((30 + i1) << 5)) + 30];
      }
    }

    for (i1 = 0; i1 < 2; i1++) {
      rpMagNew = 0.0;
      for (i2 = 0; i2 < 3; i2++) {
        rpMagNew += L[(i1 + ((27 + i2) << 5)) + 30] * t[27 + i2];
      }

      b_rhs[i1] = rhs[30 + i1] - rpMagNew;
    }

    d_linsolve(b_b, b_rhs, b_rdMag);
    for (i = 0; i < 2; i++) {
      t[i + 30] = b_rdMag[i];
    }

    /*  check solve process */
    /*  now solve part two: L'*dnu = t; */
    memset(&dnu[0], 0, sizeof(double) << 5);

    /*  different start for terminal equality case */
    for (i1 = 0; i1 < 2; i1++) {
      for (i2 = 0; i2 < 2; i2++) {
        b_b[i2 + (i1 << 1)] = L[(i1 + ((30 + i2) << 5)) + 30];
      }
    }

    e_linsolve(b_b, *(double (*)[2])&t[30], b_rdMag);
    for (i = 0; i < 2; i++) {
      dnu[i + 30] = b_rdMag[i];
    }

    /*  another function to get n x n square block elements */
    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 3; i2++) {
        tmp[i2 + 3 * i1] = L[(i1 + ((27 + i2) << 5)) + 27];
      }
    }

    for (i1 = 0; i1 < 3; i1++) {
      rpMagNew = 0.0;
      for (i2 = 0; i2 < 2; i2++) {
        rpMagNew += L[(i2 + ((27 + i1) << 5)) + 30] * dnu[30 + i2];
      }

      b_A[i1] = t[27 + i1] - rpMagNew;
    }

    f_linsolve(tmp, b_A, f_b);
    for (i = 0; i < 3; i++) {
      dnu[i + 27] = f_b[i];
    }

    for (ii = 0; ii < 9; ii++) {
      /*  another function to get n x n square block elements */
      i1 = (8 - ii) * 3;
      i2 = (8 - ii) * 3;

      /*  another function to get n x n square block elements */
      j = (9 - ii) * 3;
      i = (8 - ii) * 3;
      iy = (9 - ii) * 3 - 1;
      for (jj = 0; jj < 3; jj++) {
        for (jmax = 0; jmax < 3; jmax++) {
          c_Y[jmax + 3 * jj] = L[(jmax + i1) + ((jj + i2) << 5)];
          Y[jmax + 3 * jj] = L[(jmax + j) + ((jj + i) << 5)];
        }

        f_b[jj] = dnu[(jj + iy) + 1];
      }

      for (i1 = 0; i1 < 3; i1++) {
        for (i2 = 0; i2 < 3; i2++) {
          tmp[i2 + 3 * i1] = c_Y[i1 + 3 * i2];
        }
      }

      i1 = (8 - ii) * 3 - 1;
      for (i2 = 0; i2 < 3; i2++) {
        rpMagNew = 0.0;
        for (j = 0; j < 3; j++) {
          rpMagNew += Y[j + 3 * i2] * f_b[j];
        }

        b_A[i2] = t[(i2 + i1) + 1] - rpMagNew;
      }

      f_linsolve(tmp, b_A, f_b);
      for (i = 0; i < 3; i++) {
        dnu[i + (8 - ii) * 3] = f_b[i];
      }
    }

    /*  check the whole solve worked */
    /*  now solve for dz */
    if (flagPhiIsDiag) {
      /*  solve for dz assuming PhiInv diagonal */
      diag(phiInv, rdNew);
      for (i1 = 0; i1 < 40; i1++) {
        rpMagNew = 0.0;
        for (i2 = 0; i2 < 32; i2++) {
          rpMagNew += C[i2 + (i1 << 5)] * dnu[i2];
        }

        b_diagTwoH[i1] = -rd[i1] - rpMagNew;
      }

      for (i1 = 0; i1 < 40; i1++) {
        dz[i1] = rdNew[i1] * b_diagTwoH[i1];
      }
    } else {
      /*  form the vector to be multiplied, for shorthand */
      for (i1 = 0; i1 < 40; i1++) {
        rpMagNew = 0.0;
        for (i2 = 0; i2 < 32; i2++) {
          rpMagNew += C[i2 + (i1 << 5)] * dnu[i2];
        }

        diagPhi[i1] = -rd[i1] - rpMagNew;
      }

      /*  now form PhiInv * rd in preparation for making the RHS (-beta) */
      dz[0] = phiInv[164] * diagPhi[0];
      for (ii = 0; ii < 9; ii++) {
        /*  some functions to get block terms Q,R and S out of phi-inverse easily */
        i1 = ii << 2;
        i2 = ii << 2;
        Stil(phiInv, 1.0 + (double)ii, f_b);
        Stil(phiInv, 1.0 + (double)ii, b_A);
        for (j = 0; j < 3; j++) {
          for (i = 0; i < 3; i++) {
            c_A[i + 3 * j] = phiInv[((i + i1) + 40 * ((j + i2) + 1)) + 1];
            blkInv[i + (j << 2)] = c_A[i + 3 * j];
          }
        }

        for (i1 = 0; i1 < 3; i1++) {
          blkInv[12 + i1] = f_b[i1];
        }

        for (i1 = 0; i1 < 3; i1++) {
          blkInv[3 + (i1 << 2)] = b_A[i1];
        }

        blkInv[15] = phiInv[((1 + ii) << 2) + 40 * ((1 + ii) << 2)];
        b_ii = ii << 2;
        for (i1 = 0; i1 < 4; i1++) {
          b_b[i1] = diagPhi[(i1 + b_ii) + 1];
        }

        b_ii = ii << 2;
        for (i1 = 0; i1 < 4; i1++) {
          dz[(i1 + b_ii) + 1] = 0.0;
          for (i2 = 0; i2 < 4; i2++) {
            dz[(i1 + b_ii) + 1] += blkInv[i1 + (i2 << 2)] * b_b[i2];
          }
        }
      }

      /*  some functions to get block terms Q,R and S out of phi-inverse easily */
      for (i1 = 0; i1 < 3; i1++) {
        dz[37 + i1] = 0.0;
        for (i2 = 0; i2 < 3; i2++) {
          dz[37 + i1] += phiInv[(i1 + 40 * (37 + i2)) + 37] * diagPhi[37 + i2];
        }
      }
    }

    /*  check computation of Newton step */
    if (flagChecking) {
      eig(b_phi, unusedExpr);
    }

    /*  line search */
    ajj = 1.0;

    /*  part 1 - reduce until feasible */
    jj = 0;
    exitg3 = false;
    while ((!exitg3) && (jj < 10)) {
      for (i = 0; i < 40; i++) {
        b_diagTwoH[i] = z[i] + ajj * dz[i];
      }

      multByP(b_diagTwoH, Fx, Fu, Ff, iFar);
      for (i1 = 0; i1 < 24; i1++) {
        b_P[i1] = (h[i1] - iFar[i1] > 0.0);
      }

      if (all(b_P)) {
        exitg3 = true;
      } else {
        ajj *= 0.5;
        jj++;
      }
    }

    /*  part 2 take a tiny step just to get the slope */
    s = ajj / 100000.0;
    for (i = 0; i < 40; i++) {
      diagPhi[i] = z[i] + s * dz[i];
    }

    multByP(diagPhi, Fx, Fu, Ff, iNew);
    for (i1 = 0; i1 < 24; i1++) {
      iNew[i1] = h[i1] - iNew[i1];
    }

    /*  new residuals */
    rdivide(1.0, iNew, iFar);
    for (i1 = 0; i1 < 32; i1++) {
      b_nu[i1] = nu[i1] + s * dnu[i1];
    }

    for (i1 = 0; i1 < 40; i1++) {
      rpMagNew = 0.0;
      for (i2 = 0; i2 < 24; i2++) {
        rpMagNew += kappaPt[i1 + 40 * i2] * iFar[i2];
      }

      b_diagTwoH[i1] = (diagTwoH[i1] * diagPhi[i1] + g[i1]) + rpMagNew;
    }

    for (i1 = 0; i1 < 40; i1++) {
      b_C[i1] = 0.0;
      for (i2 = 0; i2 < 32; i2++) {
        b_C[i1] += C[i2 + (i1 << 5)] * b_nu[i2];
      }

      rdNew[i1] = b_diagTwoH[i1] + b_C[i1];
    }

    if (flagUseSoftCons) {
      memcpy(&esNew[0], &hs[0], 40U * sizeof(double));
      calcDs(diagPhi, Ps, esNew, 10.0, flagNoPade, b_diagTwoH);
      for (i1 = 0; i1 < 40; i1++) {
        rpMagNew = 0.0;
        for (i2 = 0; i2 < 40; i2++) {
          rpMagNew += Ps[i2 + 40 * i1] * b_diagTwoH[i2];
        }

        rdNew[i1] += rpMagNew;
      }
    }

    rdMagNew[0] = b_norm(rdNew);
    calcRp(diagPhi, b, A, B, Ef, dv27);
    rdMagNew[1] = norm(dv27);
    gradRmag = 100000.0 * (c_norm(rdMagNew) - rMag);

    /*  debug - plot the darned thing */
    /*      dbgii=0; */
    /*      for s = linspace(-1.5*sMax,1.5*sMax,100), */
    /*          dbgii = dbgii+1; */
    /*          zNew = z + s*dz; */
    /*          nuNew = nu + s*dnu; */
    /*          iNew = h - multByP(zNew,Fx,Fu,Ff,T,n,m,ell,ellf); */
    /*          % new residuals */
    /*          dNew = 1./iNew; */
    /*          rdNew = diagTwoH.*zNew + g + kappaPt*dNew + C'*nuNew; */
    /*          if flagUseSoftCons, */
    /*              [dsNew,esNew] = calcDs(zNew,Ps,hs,rho,flagNoPade); */
    /*              rdNew = rdNew + Ps'*dsNew; */
    /*          end */
    /*          rpNew = calcRp(zNew,b,A,B,Ef,T,n,m,ellef); */
    /*          rdMagNew = norm(rdNew); */
    /*          rpMagNew = norm(rpNew); */
    /*          rMagNew = norm([rdMagNew;rpMagNew]); */
    /*          dbgs(dbgii)=s; */
    /*          dbgr(dbgii,:)=[rdNew' rpNew']; */
    /*      end */
    /*      figure(kk) */
    /*      plot(dbgs,dbgr) */
    /*  part 3 - backtracking */
    s = ajj;
    jj = 0;
    exitg2 = false;
    while ((!exitg2) && (jj < 20)) {
      for (i = 0; i < 40; i++) {
        diagPhi[i] = z[i] + s * dz[i];
      }

      for (i = 0; i < 32; i++) {
        t[i] = nu[i] + s * dnu[i];
      }

      multByP(diagPhi, Fx, Fu, Ff, iNew);
      for (i1 = 0; i1 < 24; i1++) {
        iNew[i1] = h[i1] - iNew[i1];
      }

      /*  new residuals */
      rdivide(1.0, iNew, iFar);
      for (i1 = 0; i1 < 40; i1++) {
        rpMagNew = 0.0;
        for (i2 = 0; i2 < 24; i2++) {
          rpMagNew += kappaPt[i1 + 40 * i2] * iFar[i2];
        }

        b_diagTwoH[i1] = (diagTwoH[i1] * diagPhi[i1] + g[i1]) + rpMagNew;
      }

      for (i1 = 0; i1 < 40; i1++) {
        b_C[i1] = 0.0;
        for (i2 = 0; i2 < 32; i2++) {
          b_C[i1] += C[i2 + (i1 << 5)] * t[i2];
        }

        rdNew[i1] = b_diagTwoH[i1] + b_C[i1];
      }

      if (flagUseSoftCons) {
        memcpy(&esNew[0], &hs[0], 40U * sizeof(double));
        calcDs(diagPhi, Ps, esNew, 10.0, flagNoPade, b_diagTwoH);
        for (i1 = 0; i1 < 40; i1++) {
          rpMagNew = 0.0;
          for (i2 = 0; i2 < 40; i2++) {
            rpMagNew += Ps[i2 + 40 * i1] * b_diagTwoH[i2];
          }

          rdNew[i1] += rpMagNew;
        }
      }

      calcRp(diagPhi, b, A, B, Ef, rhs);
      ajj = b_norm(rdNew);
      rpMagNew = norm(rhs);
      b_rdMagNew[0] = ajj;
      b_rdMagNew[1] = rpMagNew;
      rMagNew = c_norm(b_rdMagNew);

      /* [kk jj rMagNew  (rMag + 0.4*s*gradRmag)] */
      /*  test */
      if (rMagNew < rMag + 0.6 * s * gradRmag) {
        /*  update */
        memcpy(&z[0], &diagPhi[0], 40U * sizeof(double));
        memcpy(&nu[0], &t[0], sizeof(double) << 5);
        memcpy(&d[0], &iFar[0], 24U * sizeof(double));
        memcpy(&rd[0], &rdNew[0], 40U * sizeof(double));
        memcpy(&rp[0], &rhs[0], sizeof(double) << 5);
        rpMag = rpMagNew;
        rdMag = ajj;
        rMag = rMagNew;
        if (flagUseSoftCons) {
          memcpy(&es[0], &esNew[0], 40U * sizeof(double));
        }

        /*  do nothing */
        /*  lineSearchPass=[kk jj s rpMagNew rdMagNew] */
        exitg2 = true;
      } else {
        /* covg = false */
        s *= 0.6;
        jj++;
      }
    }

    /*  optional early termination */
    if (rMag < opts[5]) {
      iterCount = 1.0 + (double)kk;
      exitg1 = true;
    } else {
      kk++;
    }
  }

  /*  information for output */
  /*  primal residual, i.e. norm(C*z-b) */
  /*  dual residual, i.e. grad z */
  /*  which initial solution did I use? */
  info[0] = rpMag;
  info[1] = rdMag;
  info[2] = initSolChoice;
  info[3] = iterCount;

  /*  how many Newton iterations did I need? */
}

/*
 * File trailer for mpcsolve.c
 *
 * [EOF]
 */
