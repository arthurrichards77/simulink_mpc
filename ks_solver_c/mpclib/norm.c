/*
 * File: norm.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 18-Aug-2016 17:54:05
 */

/* Include files */
#include "rt_nonfinite.h"
#include "mpcsolve_outer.h"
#include "norm.h"

/* Function Declarations */
static void b_eml_xaxpy(int n, double b_a, const double x[900], int ix0, double
  y[30], int iy0);
static double b_eml_xnrm2(int n, const double x[30], int ix0);
static void b_eml_xscal(int n, double b_a, double x[30], int ix0);
static void c_eml_xaxpy(int n, double b_a, const double x[30], int ix0, double
  y[900], int iy0);
static double eml_div(double x, double y);
static void eml_xaxpy(int n, double b_a, int ix0, double y[900], int iy0);
static double eml_xdotc(int n, const double x[900], int ix0, const double y[900],
  int iy0);
static void eml_xgesvd(const double A[900], double S[30]);
static double eml_xnrm2(int n, const double x[900], int ix0);
static void eml_xrotg(double *b_a, double *b, double *c, double *s);
static void eml_xscal(int n, double b_a, double x[900], int ix0);

/* Function Definitions */

/*
 * Arguments    : int n
 *                double b_a
 *                const double x[900]
 *                int ix0
 *                double y[30]
 *                int iy0
 * Return Type  : void
 */
static void b_eml_xaxpy(int n, double b_a, const double x[900], int ix0, double
  y[30], int iy0)
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
 *                const double x[30]
 *                int ix0
 * Return Type  : double
 */
static double b_eml_xnrm2(int n, const double x[30], int ix0)
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
 *                double x[30]
 *                int ix0
 * Return Type  : void
 */
static void b_eml_xscal(int n, double b_a, double x[30], int ix0)
{
  int i24;
  int k;
  i24 = (ix0 + n) - 1;
  for (k = ix0; k <= i24; k++) {
    x[k - 1] *= b_a;
  }
}

/*
 * Arguments    : int n
 *                double b_a
 *                const double x[30]
 *                int ix0
 *                double y[900]
 *                int iy0
 * Return Type  : void
 */
static void c_eml_xaxpy(int n, double b_a, const double x[30], int ix0, double
  y[900], int iy0)
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
 * Arguments    : double x
 *                double y
 * Return Type  : double
 */
static double eml_div(double x, double y)
{
  return x / y;
}

/*
 * Arguments    : int n
 *                double b_a
 *                int ix0
 *                double y[900]
 *                int iy0
 * Return Type  : void
 */
static void eml_xaxpy(int n, double b_a, int ix0, double y[900], int iy0)
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
 *                const double x[900]
 *                int ix0
 *                const double y[900]
 *                int iy0
 * Return Type  : double
 */
static double eml_xdotc(int n, const double x[900], int ix0, const double y[900],
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
 * Arguments    : const double A[900]
 *                double S[30]
 * Return Type  : void
 */
static void eml_xgesvd(const double A[900], double S[30])
{
  double b_A[900];
  double s[30];
  double e[30];
  double work[30];
  int i;
  int q;
  double ztest0;
  int qs;
  int qjj;
  int m;
  double rt;
  double ztest;
  int iter;
  double tiny;
  double snorm;
  int32_T exitg3;
  boolean_T exitg2;
  double f;
  double varargin_1[5];
  double mtmp;
  boolean_T exitg1;
  double sqds;
  memcpy(&b_A[0], &A[0], 900U * sizeof(double));
  for (i = 0; i < 30; i++) {
    s[i] = 0.0;
    e[i] = 0.0;
    work[i] = 0.0;
  }

  for (q = 0; q < 29; q++) {
    i = q + 30 * q;
    ztest0 = eml_xnrm2(30 - q, b_A, i + 1);
    if (ztest0 > 0.0) {
      if (b_A[i] < 0.0) {
        s[q] = -ztest0;
      } else {
        s[q] = ztest0;
      }

      eml_xscal(30 - q, eml_div(1.0, s[q]), b_A, i + 1);
      b_A[i]++;
      s[q] = -s[q];
    } else {
      s[q] = 0.0;
    }

    for (qs = q + 1; qs + 1 < 31; qs++) {
      qjj = q + 30 * qs;
      if (s[q] != 0.0) {
        eml_xaxpy(30 - q, -eml_div(eml_xdotc(30 - q, b_A, i + 1, b_A, qjj + 1),
                   b_A[q + 30 * q]), i + 1, b_A, qjj + 1);
      }

      e[qs] = b_A[qjj];
    }

    if (q + 1 <= 28) {
      ztest0 = b_eml_xnrm2(29 - q, e, q + 2);
      if (ztest0 == 0.0) {
        e[q] = 0.0;
      } else {
        if (e[q + 1] < 0.0) {
          e[q] = -ztest0;
        } else {
          e[q] = ztest0;
        }

        b_eml_xscal(29 - q, eml_div(1.0, e[q]), e, q + 2);
        e[q + 1]++;
      }

      e[q] = -e[q];
      if (e[q] != 0.0) {
        for (i = q + 1; i + 1 < 31; i++) {
          work[i] = 0.0;
        }

        for (qs = q + 1; qs + 1 < 31; qs++) {
          b_eml_xaxpy(29 - q, e[qs], b_A, (q + 30 * qs) + 2, work, q + 2);
        }

        for (qs = q + 1; qs + 1 < 31; qs++) {
          c_eml_xaxpy(29 - q, eml_div(-e[qs], e[q + 1]), work, q + 2, b_A, (q +
            30 * qs) + 2);
        }
      }
    }
  }

  m = 28;
  s[29] = b_A[899];
  e[28] = b_A[898];
  e[29] = 0.0;
  for (q = 0; q < 30; q++) {
    ztest0 = e[q];
    if (s[q] != 0.0) {
      rt = fabs(s[q]);
      ztest = eml_div(s[q], rt);
      s[q] = rt;
      if (q + 1 < 30) {
        ztest0 = eml_div(e[q], ztest);
      }
    }

    if ((q + 1 < 30) && (ztest0 != 0.0)) {
      rt = fabs(ztest0);
      ztest = eml_div(rt, ztest0);
      ztest0 = rt;
      s[q + 1] *= ztest;
    }

    e[q] = ztest0;
  }

  iter = 0;
  tiny = eml_div(2.2250738585072014E-308, 2.2204460492503131E-16);
  snorm = 0.0;
  for (i = 0; i < 30; i++) {
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
            (ztest0 <= tiny) || ((iter > 20) && (ztest0 <=
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
          if ((ztest <= 2.2204460492503131E-16 * ztest0) || (ztest <= tiny)) {
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
      for (i = m; i + 1 >= q + 1; i--) {
        ztest0 = s[i];
        eml_xrotg(&ztest0, &f, &ztest, &rt);
        s[i] = ztest0;
        if (i + 1 > q + 1) {
          f = -rt * e[i - 1];
          e[i - 1] *= ztest;
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
        qs = 2;
        exitg1 = false;
        while ((!exitg1) && (qs < 6)) {
          i = qs;
          if (!rtIsNaN(varargin_1[qs - 1])) {
            mtmp = varargin_1[qs - 1];
            exitg1 = true;
          } else {
            qs++;
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

      f = eml_div(s[m + 1], mtmp);
      ztest0 = eml_div(s[m], mtmp);
      ztest = eml_div(e[m], mtmp);
      sqds = eml_div(s[q], mtmp);
      rt = eml_div((ztest0 + f) * (ztest0 - f) + ztest * ztest, 2.0);
      ztest0 = f * ztest;
      ztest0 *= ztest0;
      ztest = 0.0;
      if ((rt != 0.0) || (ztest0 != 0.0)) {
        ztest = sqrt(rt * rt + ztest0);
        if (rt < 0.0) {
          ztest = -ztest;
        }

        ztest = eml_div(ztest0, rt + ztest);
      }

      f = (sqds + f) * (sqds - f) + ztest;
      ztest0 = sqds * eml_div(e[q], mtmp);
      for (i = q + 1; i <= m + 1; i++) {
        eml_xrotg(&f, &ztest0, &ztest, &rt);
        if (i > q + 1) {
          e[i - 2] = f;
        }

        f = ztest * s[i - 1] + rt * e[i - 1];
        e[i - 1] = ztest * e[i - 1] - rt * s[i - 1];
        ztest0 = rt * s[i];
        s[i] *= ztest;
        s[i - 1] = f;
        eml_xrotg(&s[i - 1], &ztest0, &ztest, &rt);
        f = ztest * e[i - 1] + rt * s[i];
        s[i] = -rt * e[i - 1] + ztest * s[i];
        ztest0 = rt * e[i];
        e[i] *= ztest;
      }

      e[m] = f;
      iter++;
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
      }

      i = q + 1;
      while ((q + 1 < 30) && (s[q] < s[i])) {
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

  memcpy(&S[0], &s[0], 30U * sizeof(double));
}

/*
 * Arguments    : int n
 *                const double x[900]
 *                int ix0
 * Return Type  : double
 */
static double eml_xnrm2(int n, const double x[900], int ix0)
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
 * Arguments    : double *b_a
 *                double *b
 *                double *c
 *                double *s
 * Return Type  : void
 */
static void eml_xrotg(double *b_a, double *b, double *c, double *s)
{
  double roe;
  double absa;
  double absb;
  double scale;
  double ads;
  double bds;
  roe = *b;
  absa = fabs(*b_a);
  absb = fabs(*b);
  if (absa > absb) {
    roe = *b_a;
  }

  scale = absa + absb;
  if (scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    ads = 0.0;
    scale = 0.0;
  } else {
    ads = absa / scale;
    bds = absb / scale;
    ads = scale * sqrt(ads * ads + bds * bds);
    if (roe < 0.0) {
      ads = -ads;
    }

    *c = *b_a / ads;
    *s = *b / ads;
    if (absa > absb) {
      scale = *s;
    } else if (*c != 0.0) {
      scale = 1.0 / *c;
    } else {
      scale = 1.0;
    }
  }

  *b_a = ads;
  *b = scale;
}

/*
 * Arguments    : int n
 *                double b_a
 *                double x[900]
 *                int ix0
 * Return Type  : void
 */
static void eml_xscal(int n, double b_a, double x[900], int ix0)
{
  int i23;
  int k;
  i23 = (ix0 + n) - 1;
  for (k = ix0; k <= i23; k++) {
    x[k - 1] *= b_a;
  }
}

/*
 * Arguments    : const double x[40]
 * Return Type  : double
 */
double b_norm(const double x[40])
{
  double y;
  double scale;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 2.2250738585072014E-308;
  for (k = 0; k < 40; k++) {
    absxk = fabs(x[k]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

/*
 * Arguments    : const double x[2]
 * Return Type  : double
 */
double c_norm(const double x[2])
{
  double y;
  double scale;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 2.2250738585072014E-308;
  for (k = 0; k < 2; k++) {
    absxk = fabs(x[k]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

/*
 * Arguments    : const double x[900]
 * Return Type  : double
 */
double d_norm(const double x[900])
{
  double U[30];
  eml_xgesvd(x, U);
  return U[0];
}

/*
 * Arguments    : const double x[30]
 * Return Type  : double
 */
double norm(const double x[30])
{
  double y;
  double scale;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 2.2250738585072014E-308;
  for (k = 0; k < 30; k++) {
    absxk = fabs(x[k]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

/*
 * File trailer for norm.c
 *
 * [EOF]
 */
