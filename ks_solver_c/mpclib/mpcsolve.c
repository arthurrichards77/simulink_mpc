/*
 * File: mpcsolve.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 18-Aug-2016 17:54:05
 */

/* Include files */
#include "rt_nonfinite.h"
#include "mpcsolve_outer.h"
#include "mpcsolve.h"
#include "linsolve.h"
#include "norm.h"
#include "rdivide.h"
#include "all.h"
#include "diag.h"

/* Function Declarations */
static void b_calcDs(const double z[40], const double Ps[800], const double Fxs
                     [6], const double Fus[2], double hs[20], double rho,
                     boolean_T flagNoPade, const double switches[9], double ds
                     [20]);
static void b_mySymPDinv(const double M[16], double Minv[16]);
static void b_preMultByA(const double M[9], const double A[9], const double
  switches[9], double y[9]);
static void c_mySymPDinv(const double M[9], double Minv[9]);
static void calcDs(const double z[40], const double Ps[800], const double Fxs[6],
                   const double Fus[2], double hs[20], boolean_T flagNoPade,
                   const double switches[9], double ds[20]);
static void multByAT(const double M[9], const double AT[9], const double
                     switches[9], double y[9]);
static void multByC(const double z[40], const double A[9], const double B[3],
                    const double C[1200], const double switches[9], double y[30]);
static void multByCT(const double nu[30], const double CT[1200], const double
                     AT[9], const double BT[3], const double switches[9], double
                     y[40]);
static void multByP(const double z[40], const double P[1680], const double Fx[12],
                    const double Fu[4], const double Ff[6], const double
                    switches[9], double y[42]);
static void multByPsT(const double ds[20], const double PsT[800], const double
                      FxsT[6], const double FusT[2], const double switches[9],
                      double y[40]);
static double mySymPDinv(double M);
static double myexp(double u, boolean_T flagNoPade);
static void preMultByA(const double M[3], const double A[9], const double
  switches[9], double y[3]);

/* Function Definitions */

/*
 * pre-assign to help coder
 * Arguments    : const double z[40]
 *                const double Ps[800]
 *                const double Fxs[6]
 *                const double Fus[2]
 *                double hs[20]
 *                double rho
 *                boolean_T flagNoPade
 *                const double switches[9]
 *                double ds[20]
 * Return Type  : void
 */
static void b_calcDs(const double z[40], const double Ps[800], const double Fxs
                     [6], const double Fus[2], double hs[20], double rho,
                     boolean_T flagNoPade, const double switches[9], double ds
                     [20])
{
  int i25;
  double rs[20];
  int i26;
  int i;
  double b[3];
  double b_Fxs[2];
  double b_rs;
  int i27;

  /*  residuals */
  /*  rs = Ps*z - hs; */
  /*  */
  /*  return Ps*z */
  /*  */
  if (switches[2] == 0.0) {
    for (i25 = 0; i25 < 20; i25++) {
      rs[i25] = 0.0;
      for (i26 = 0; i26 < 40; i26++) {
        rs[i25] += Ps[i25 + 20 * i26] * z[i26];
      }
    }
  } else {
    memset(&rs[0], 0, 20U * sizeof(double));
    for (i = 0; i < 2; i++) {
      rs[i] = Fus[i] * z[0];
    }

    for (i = 0; i < 9; i++) {
      i25 = i << 2;
      for (i26 = 0; i26 < 3; i26++) {
        b[i26] = z[(i26 + i25) + 1];
      }

      i25 = (1 + i) << 1;
      for (i26 = 0; i26 < 2; i26++) {
        b_rs = 0.0;
        for (i27 = 0; i27 < 3; i27++) {
          b_rs += Fxs[i26 + (i27 << 1)] * b[i27];
        }

        b_Fxs[i26] = b_rs + Fus[i26] * z[(1 + i) << 2];
      }

      for (i26 = 0; i26 < 2; i26++) {
        rs[i26 + i25] = b_Fxs[i26];
      }
    }
  }

  for (i25 = 0; i25 < 20; i25++) {
    b_rs = rs[i25] - hs[i25];
    rs[i25] = b_rs;
  }

  for (i = 0; i < 20; i++) {
    if (rs[i] > 0.0) {
      hs[i] = myexp(-rho * rs[i], flagNoPade);
      ds[i] = 1.0 / (1.0 + hs[i]);
    } else {
      hs[i] = myexp(rho * rs[i], flagNoPade);
      ds[i] = hs[i] / (1.0 + hs[i]);
    }
  }
}

/*
 * utility for quick inversion of a symmetric positive definite matrix
 * Arguments    : const double M[16]
 *                double Minv[16]
 * Return Type  : void
 */
static void b_mySymPDinv(const double M[16], double Minv[16])
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
  int i12;
  int kAcol;
  double c;
  int jmax;
  int i;
  double tmp[16];
  static const signed char B[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    1 };

  double b_A[16];
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
          i12 = (j + ((j - 1) << 2)) + 2;
          for (kAcol = j + 2; kAcol <= i12; kAcol += 4) {
            c = -A[ix];
            iy = jj + 1;
            jmax = (kAcol - j) + 2;
            for (i = kAcol; i <= jmax; i++) {
              A[iy] += A[i - 1] * c;
              iy++;
            }

            ix += 4;
          }
        }

        ajj = 1.0 / ajj;
        i12 = (jj - j) + 4;
        for (k = jj + 1; k + 1 <= i12; k++) {
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
    for (i = 1; i <= j; i++) {
      A[(i + (j << 2)) - 1] = 0.0;
    }
  }

  for (j = 0; j < 4; j++) {
    for (i = 0; i < 4; i++) {
      tmp[i + (j << 2)] = B[i + (j << 2)];
    }
  }

  for (j = 0; j < 4; j++) {
    jmax = j << 2;
    for (k = 0; k < 4; k++) {
      kAcol = k << 2;
      if (tmp[k + jmax] != 0.0) {
        tmp[k + jmax] /= A[k + kAcol];
        for (i = k + 1; i + 1 < 5; i++) {
          tmp[i + jmax] -= tmp[k + jmax] * A[i + kAcol];
        }
      }
    }
  }

  for (i12 = 0; i12 < 4; i12++) {
    for (jmax = 0; jmax < 4; jmax++) {
      b_A[jmax + (i12 << 2)] = A[i12 + (jmax << 2)];
      Minv[jmax + (i12 << 2)] = tmp[jmax + (i12 << 2)];
    }
  }

  for (j = 0; j < 4; j++) {
    jmax = j << 2;
    for (k = 3; k > -1; k += -1) {
      kAcol = k << 2;
      if (Minv[k + jmax] != 0.0) {
        Minv[k + jmax] /= b_A[k + kAcol];
        for (i = 0; i + 1 <= k; i++) {
          Minv[i + jmax] -= Minv[k + jmax] * b_A[i + kAcol];
        }
      }
    }
  }

  /*  if flagChecking, */
  /*      checkInv = norm(Minv*M - eye(size(M,1))) */
  /*  else */
  /*      checkInv = 0; */
  /*  end */
}

/*
 * returns A*M
 * Arguments    : const double M[9]
 *                const double A[9]
 *                const double switches[9]
 *                double y[9]
 * Return Type  : void
 */
static void b_preMultByA(const double M[9], const double A[9], const double
  switches[9], double y[9])
{
  int i17;
  int i18;
  int i19;
  int ii;
  if (switches[5] == 0.0) {
    for (i17 = 0; i17 < 3; i17++) {
      for (i18 = 0; i18 < 3; i18++) {
        y[i17 + 3 * i18] = 0.0;
        for (i19 = 0; i19 < 3; i19++) {
          y[i17 + 3 * i18] += A[i17 + 3 * i19] * M[i19 + 3 * i18];
        }
      }
    }
  } else {
    /*  Define n in this instance as a half the number of states (i.e. per axis) */
    memset(&y[0], 0, 9U * sizeof(double));
    for (ii = 0; ii < 2; ii++) {
      i17 = (int)(1.0 + ((1.0 + (double)ii) - 1.0) * 1.5);
      i18 = (int)(1.0 + ((1.0 + (double)ii) - 1.0) * 1.5);
      for (i19 = 0; i19 < 3; i19++) {
        y[(i18 + 3 * i19) - 1] = A[0] * M[(i17 + 3 * i19) - 1];
      }
    }
  }
}

/*
 * utility for quick inversion of a symmetric positive definite matrix
 * Arguments    : const double M[9]
 *                double Minv[9]
 * Return Type  : void
 */
static void c_mySymPDinv(const double M[9], double Minv[9])
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
  int i13;
  int kAcol;
  double c;
  int jmax;
  int i;
  double tmp[9];
  static const double dv22[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

  double b_A[9];
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
          i13 = (j + 3 * (j - 1)) + 2;
          for (kAcol = j + 2; kAcol <= i13; kAcol += 3) {
            c = -A[ix];
            iy = jj + 1;
            jmax = (kAcol - j) + 1;
            for (i = kAcol; i <= jmax; i++) {
              A[iy] += A[i - 1] * c;
              iy++;
            }

            ix += 3;
          }
        }

        ajj = 1.0 / ajj;
        i13 = (jj - j) + 3;
        for (k = jj + 1; k + 1 <= i13; k++) {
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
    for (i = 1; i <= j; i++) {
      A[(i + 3 * j) - 1] = 0.0;
    }
  }

  linsolve(A, dv22, tmp);
  for (i13 = 0; i13 < 3; i13++) {
    for (jmax = 0; jmax < 3; jmax++) {
      b_A[jmax + 3 * i13] = A[i13 + 3 * jmax];
      Minv[jmax + 3 * i13] = tmp[jmax + 3 * i13];
    }
  }

  for (j = 0; j < 3; j++) {
    jmax = 3 * j;
    for (k = 2; k > -1; k += -1) {
      kAcol = 3 * k;
      if (Minv[k + jmax] != 0.0) {
        Minv[k + jmax] /= b_A[k + kAcol];
        for (i = 0; i + 1 <= k; i++) {
          Minv[i + jmax] -= Minv[k + jmax] * b_A[i + kAcol];
        }
      }
    }
  }

  /*  if flagChecking, */
  /*      checkInv = norm(Minv*M - eye(size(M,1))) */
  /*  else */
  /*      checkInv = 0; */
  /*  end */
}

/*
 * pre-assign to help coder
 * Arguments    : const double z[40]
 *                const double Ps[800]
 *                const double Fxs[6]
 *                const double Fus[2]
 *                double hs[20]
 *                boolean_T flagNoPade
 *                const double switches[9]
 *                double ds[20]
 * Return Type  : void
 */
static void calcDs(const double z[40], const double Ps[800], const double Fxs[6],
                   const double Fus[2], double hs[20], boolean_T flagNoPade,
                   const double switches[9], double ds[20])
{
  int i20;
  double rs[20];
  int i21;
  int i;
  double b[3];
  double b_Fxs[2];
  double b_rs;
  int i22;

  /*  residuals */
  /*  rs = Ps*z - hs; */
  /*  */
  /*  return Ps*z */
  /*  */
  if (switches[2] == 0.0) {
    for (i20 = 0; i20 < 20; i20++) {
      rs[i20] = 0.0;
      for (i21 = 0; i21 < 40; i21++) {
        rs[i20] += Ps[i20 + 20 * i21] * z[i21];
      }
    }
  } else {
    memset(&rs[0], 0, 20U * sizeof(double));
    for (i = 0; i < 2; i++) {
      rs[i] = Fus[i] * z[0];
    }

    for (i = 0; i < 9; i++) {
      i20 = i << 2;
      for (i21 = 0; i21 < 3; i21++) {
        b[i21] = z[(i21 + i20) + 1];
      }

      i20 = (1 + i) << 1;
      for (i21 = 0; i21 < 2; i21++) {
        b_rs = 0.0;
        for (i22 = 0; i22 < 3; i22++) {
          b_rs += Fxs[i21 + (i22 << 1)] * b[i22];
        }

        b_Fxs[i21] = b_rs + Fus[i21] * z[(1 + i) << 2];
      }

      for (i21 = 0; i21 < 2; i21++) {
        rs[i21 + i20] = b_Fxs[i21];
      }
    }
  }

  for (i20 = 0; i20 < 20; i20++) {
    b_rs = rs[i20] - hs[i20];
    rs[i20] = b_rs;
  }

  for (i = 0; i < 20; i++) {
    if (rs[i] > 0.0) {
      hs[i] = myexp(-10.0 * rs[i], flagNoPade);
      ds[i] = 1.0 / (1.0 + hs[i]);
    } else {
      hs[i] = myexp(10.0 * rs[i], flagNoPade);
      ds[i] = hs[i] / (1.0 + hs[i]);
    }
  }
}

/*
 * returns M*AT
 * Arguments    : const double M[9]
 *                const double AT[9]
 *                const double switches[9]
 *                double y[9]
 * Return Type  : void
 */
static void multByAT(const double M[9], const double AT[9], const double
                     switches[9], double y[9])
{
  int i14;
  int i15;
  int i16;
  int ii;
  if (switches[6] == 0.0) {
    for (i14 = 0; i14 < 3; i14++) {
      for (i15 = 0; i15 < 3; i15++) {
        y[i14 + 3 * i15] = 0.0;
        for (i16 = 0; i16 < 3; i16++) {
          y[i14 + 3 * i15] += M[i14 + 3 * i16] * AT[i16 + 3 * i15];
        }
      }
    }
  } else {
    /*  Define n in this instance as a half the number of states (i.e. per axis) */
    memset(&y[0], 0, 9U * sizeof(double));
    for (ii = 0; ii < 2; ii++) {
      i14 = (int)(1.0 + ((1.0 + (double)ii) - 1.0) * 1.5);
      i15 = (int)(1.0 + ((1.0 + (double)ii) - 1.0) * 1.5);
      for (i16 = 0; i16 < 3; i16++) {
        y[i16 + 3 * (i15 - 1)] = M[i16 + 3 * (i14 - 1)] * AT[0];
      }
    }
  }
}

/*
 * return C*z
 * Arguments    : const double z[40]
 *                const double A[9]
 *                const double B[3]
 *                const double C[1200]
 *                const double switches[9]
 *                double y[30]
 * Return Type  : void
 */
static void multByC(const double z[40], const double A[9], const double B[3],
                    const double C[1200], const double switches[9], double y[30])
{
  int i;
  int i7;
  double b_y[3];
  int ii;
  double M[3];
  int i8;
  if (switches[0] == 0.0) {
    for (i = 0; i < 30; i++) {
      y[i] = 0.0;
      for (i7 = 0; i7 < 40; i7++) {
        y[i] += C[i + 30 * i7] * z[i7];
      }
    }
  } else {
    memset(&y[0], 0, 30U * sizeof(double));
    for (i = 0; i < 3; i++) {
      y[i] = z[i + 1] - B[i] * z[0];
    }

    for (ii = 0; ii < 9; ii++) {
      /*      y(n*(ii-1)+(1:n)) = z(m+(ii-1)*(n+m)+(1:n)) - A*z(m+(ii-2)*(n+m)+(1:n)) - B*z((ii-1)*(n+m)+(1:m)); */
      i = ii << 2;
      for (i7 = 0; i7 < 3; i7++) {
        M[i7] = z[(i7 + i) + 1];
      }

      /*  */
      /*  returns A*M */
      /*  */
      if (switches[5] == 0.0) {
        for (i = 0; i < 3; i++) {
          b_y[i] = 0.0;
          for (i7 = 0; i7 < 3; i7++) {
            b_y[i] += A[i + 3 * i7] * M[i7];
          }
        }
      } else {
        /*  Define n in this instance as a half the number of states (i.e. per axis) */
        for (i = 0; i < 3; i++) {
          b_y[i] = 0.0;
        }

        for (i = 0; i < 2; i++) {
          b_y[(int)(1.0 + ((1.0 + (double)i) - 1.0) * 1.5) - 1] = A[0] * z[(int)
            (1.0 + ((1.0 + (double)i) - 1.0) * 1.5) + (ii << 2)];
        }
      }

      i = 3 * (1 + ii);
      i7 = (1 + ii) << 2;
      for (i8 = 0; i8 < 3; i8++) {
        y[i8 + i] = (z[(i8 + i7) + 1] - b_y[i8]) - B[i8] * z[(1 + ii) << 2];
      }
    }
  }
}

/*
 * return C'*nu
 *
 *  Where AT = A'
 *        BT = B'
 *        EfT = Ef'
 * Arguments    : const double nu[30]
 *                const double CT[1200]
 *                const double AT[9]
 *                const double BT[3]
 *                const double switches[9]
 *                double y[40]
 * Return Type  : void
 */
static void multByCT(const double nu[30], const double CT[1200], const double
                     AT[9], const double BT[3], const double switches[9], double
                     y[40])
{
  int i9;
  int i;
  double d2;
  double b_y[3];
  int ii;
  double M[3];
  int b_ii;
  if (switches[4] == 0.0) {
    for (i9 = 0; i9 < 40; i9++) {
      y[i9] = 0.0;
      for (i = 0; i < 30; i++) {
        y[i9] += CT[i9 + 40 * i] * nu[i];
      }
    }
  } else {
    memset(&y[0], 0, 40U * sizeof(double));
    d2 = 0.0;
    for (i9 = 0; i9 < 3; i9++) {
      d2 += -BT[i9] * nu[i9];
    }

    y[0] = d2;
    for (ii = 0; ii < 9; ii++) {
      /*      y(m+(1:n)+(ii-2)*(n+m)) = nu((1:n) + (ii-2)*n) - AT*nu((1:n) + (ii-1)*n); */
      i9 = (1 + ii) * 3 - 1;
      for (i = 0; i < 3; i++) {
        M[i] = nu[(i + i9) + 1];
      }

      /*  */
      /*  returns A*M */
      /*  */
      if (switches[5] == 0.0) {
        for (i9 = 0; i9 < 3; i9++) {
          b_y[i9] = 0.0;
          for (i = 0; i < 3; i++) {
            b_y[i9] += AT[i9 + 3 * i] * M[i];
          }
        }
      } else {
        /*  Define n in this instance as a half the number of states (i.e. per axis) */
        for (i = 0; i < 3; i++) {
          b_y[i] = 0.0;
        }

        for (i = 0; i < 2; i++) {
          b_y[(int)(1.0 + ((1.0 + (double)i) - 1.0) * 1.5) - 1] = AT[0] * nu
            [((int)(1.0 + ((1.0 + (double)i) - 1.0) * 1.5) + (1 + ii) * 3) - 1];
        }
      }

      i = ii << 2;
      b_ii = ii * 3 - 1;
      for (i9 = 0; i9 < 3; i9++) {
        y[(i9 + i) + 1] = nu[(i9 + b_ii) + 1] - b_y[i9];
      }

      i9 = (1 + ii) * 3 - 1;
      d2 = 0.0;
      for (i = 0; i < 3; i++) {
        d2 += -BT[i] * nu[(i + i9) + 1];
      }

      y[4 + (ii << 2)] = d2;
    }

    for (i = 0; i < 3; i++) {
      y[i + 37] = nu[i + 27];
    }
  }
}

/*
 * return P*z
 * Arguments    : const double z[40]
 *                const double P[1680]
 *                const double Fx[12]
 *                const double Fu[4]
 *                const double Ff[6]
 *                const double switches[9]
 *                double y[42]
 * Return Type  : void
 */
static void multByP(const double z[40], const double P[1680], const double Fx[12],
                    const double Fu[4], const double Ff[6], const double
                    switches[9], double y[42])
{
  int i4;
  int i5;
  int i;
  double b[3];
  double b_Fx[4];
  double d1;
  int i6;
  double b_Ff[2];
  if (switches[1] == 0.0) {
    for (i4 = 0; i4 < 42; i4++) {
      y[i4] = 0.0;
      for (i5 = 0; i5 < 40; i5++) {
        y[i4] += P[i4 + 42 * i5] * z[i5];
      }
    }
  } else {
    memset(&y[0], 0, 42U * sizeof(double));
    for (i = 0; i < 4; i++) {
      y[i] = Fu[i] * z[0];
    }

    for (i = 0; i < 9; i++) {
      i4 = i << 2;
      for (i5 = 0; i5 < 3; i5++) {
        b[i5] = z[(i5 + i4) + 1];
      }

      i4 = (1 + i) << 2;
      for (i5 = 0; i5 < 4; i5++) {
        d1 = 0.0;
        for (i6 = 0; i6 < 3; i6++) {
          d1 += Fx[i5 + (i6 << 2)] * b[i6];
        }

        b_Fx[i5] = d1 + Fu[i5] * z[(1 + i) << 2];
      }

      for (i5 = 0; i5 < 4; i5++) {
        y[i5 + i4] = b_Fx[i5];
      }
    }

    for (i4 = 0; i4 < 2; i4++) {
      b_Ff[i4] = 0.0;
      for (i5 = 0; i5 < 3; i5++) {
        b_Ff[i4] += Ff[i4 + (i5 << 1)] * z[37 + i5];
      }

      y[40 + i4] = b_Ff[i4];
    }
  }
}

/*
 * return Ps'*ds
 *
 *  Where FxsT = Fxs'
 *        FusT = Fus'
 * Arguments    : const double ds[20]
 *                const double PsT[800]
 *                const double FxsT[6]
 *                const double FusT[2]
 *                const double switches[9]
 *                double y[40]
 * Return Type  : void
 */
static void multByPsT(const double ds[20], const double PsT[800], const double
                      FxsT[6], const double FusT[2], const double switches[9],
                      double y[40])
{
  int i10;
  int i11;
  double d3;
  int ii;
  double b[2];
  int b_ii;
  double b_FxsT[3];
  if (switches[3] == 0.0) {
    for (i10 = 0; i10 < 40; i10++) {
      y[i10] = 0.0;
      for (i11 = 0; i11 < 20; i11++) {
        y[i10] += PsT[i10 + 40 * i11] * ds[i11];
      }
    }
  } else {
    memset(&y[0], 0, 40U * sizeof(double));
    d3 = 0.0;
    for (i10 = 0; i10 < 2; i10++) {
      d3 += FusT[i10] * ds[i10];
    }

    y[0] = d3;
    for (ii = 0; ii < 9; ii++) {
      i10 = ((1 + ii) << 1) - 1;
      for (i11 = 0; i11 < 2; i11++) {
        b[i11] = ds[(i11 + i10) + 1];
      }

      b_ii = ii << 2;
      for (i10 = 0; i10 < 3; i10++) {
        b_FxsT[i10] = 0.0;
        for (i11 = 0; i11 < 2; i11++) {
          b_FxsT[i10] += FxsT[i10 + 3 * i11] * b[i11];
        }
      }

      for (i10 = 0; i10 < 3; i10++) {
        y[(i10 + b_ii) + 1] = b_FxsT[i10];
      }

      i10 = ((1 + ii) << 1) - 1;
      d3 = 0.0;
      for (i11 = 0; i11 < 2; i11++) {
        d3 += FusT[i11] * ds[(i11 + i10) + 1];
      }

      y[4 + (ii << 2)] = d3;
    }
  }
}

/*
 * utility for quick inversion of a symmetric positive definite matrix
 * Arguments    : double M
 * Return Type  : double
 */
static double mySymPDinv(double M)
{
  double Minv;
  double A;
  if (M > 0.0) {
    A = sqrt(M);
  } else {
    A = M;
  }

  Minv = 1.0 / A / A;

  /*  if flagChecking, */
  /*      checkInv = norm(Minv*M - eye(size(M,1))) */
  /*  else */
  /*      checkInv = 0; */
  /*  end */
  return Minv;
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
 * returns A*M
 * Arguments    : const double M[3]
 *                const double A[9]
 *                const double switches[9]
 *                double y[3]
 * Return Type  : void
 */
static void preMultByA(const double M[3], const double A[9], const double
  switches[9], double y[3])
{
  int i;
  int i3;
  if (switches[5] == 0.0) {
    for (i = 0; i < 3; i++) {
      y[i] = 0.0;
      for (i3 = 0; i3 < 3; i3++) {
        y[i] += A[i + 3 * i3] * M[i3];
      }
    }
  } else {
    /*  Define n in this instance as a half the number of states (i.e. per axis) */
    for (i = 0; i < 3; i++) {
      y[i] = 0.0;
    }

    for (i = 0; i < 2; i++) {
      y[(int)(1.0 + ((1.0 + (double)i) - 1.0) * 1.5) - 1] = A[0] * M[(int)(1.0 +
        ((1.0 + (double)i) - 1.0) * 1.5) - 1];
    }
  }
}

/*
 * check_d, checkRp, checkPhiInv, checkY, checkBeta, checkL, check_t, check_dnu, checkNewton, checkInv
 * Arguments    : const double H[1600]
 *                const double g[40]
 *                const double P[1680]
 *                const double h[42]
 *                const double C[1200]
 *                const double b[30]
 *                const double z0[40]
 *                const double A[9]
 *                const double B[3]
 *                const double Fx[12]
 *                const double Fu[4]
 *                const double Ff[6]
 *                const double Q[9]
 *                double b_R
 *                const double Qf[9]
 *                const double opts[7]
 *                const double Ps[800]
 *                const double hs[20]
 *                const double Fxs[6]
 *                const double Fus[2]
 *                double z[40]
 *                double info[4]
 * Return Type  : void
 */
void mpcsolve(const double H[1600], const double g[40], const double P[1680],
              const double h[42], const double C[1200], const double b[30],
              const double z0[40], const double A[9], const double B[3], const
              double Fx[12], const double Fu[4], const double Ff[6], const
              double Q[9], double b_R, const double Qf[9], const double opts[7],
              const double Ps[800], const double hs[20], const double Fxs[6],
              const double Fus[2], double z[40], double info[4])
{
  double kappa;
  boolean_T flagPhiIsDiag;
  boolean_T flagUseSoftCons;
  boolean_T flagChecking;
  boolean_T flagNoPade;
  int jmax;
  double switches[9];
  int i1;
  static const signed char b_a[9] = { 1, 1, 1, 1, 1, 0, 0, 0, 0 };

  double kappaPt[1680];
  double kappaPtSq[1680];
  int i2;
  double rhoPstSq[800];
  double dv16[1600];
  double diagTwoH[40];
  double blkQR[16];
  double FxsT[6];
  double AT[9];
  double CT[1200];
  double PsT[800];
  double es[20];
  double esNew[20];
  double dz[40];
  double dhats[20];
  double St[3];
  int i;
  boolean_T b_P[42];
  double rpMagNew;
  int initSolChoice;
  double nu[30];
  double iFar[42];
  double b_h[42];
  double d[42];
  double rp[30];
  double rpMag;
  double dv17[30];
  double diagPhi[40];
  double rd[40];
  double ds[20];
  double rdMag;
  double b_rdMag[2];
  double rMag;
  double iterCount;
  int kk;
  boolean_T exitg1;
  double b_diagPhi[40];
  double dv18[40];
  double phiInv[1600];
  double b_d[4];
  double blkInv[16];
  double b_b[4];
  double ajj;
  int ii;
  int j;
  double b_Fx[16];
  double b_kappa[16];
  double c_kappa[16];
  double b_Fxs[8];
  double dv19[8];
  double dv20[8];
  double dv21[16];
  int ix;
  double c_Fx[16];
  double d_kappa[6];
  double L[9];
  double tmp[9];
  double Y[900];
  double b_A[9];
  int iy;
  int jj;
  double c_A[9];
  int b_info;
  double b_Y[9];
  double b_St[3];
  double d_A[9];
  double e_A[9];
  double b_C[1200];
  double c_Y[900];
  double rhs[30];
  double b_L[900];
  boolean_T exitg5;
  boolean_T exitg4;
  double t[30];
  double dnu[30];
  boolean_T exitg3;
  double b_z[40];
  double s;
  double zNew[40];
  double b_nu[30];
  double rdNew[40];
  double rdMagNew[2];
  double gradRmag;
  boolean_T exitg2;
  double b_rdMagNew[2];
  double rMagNew;

  /*  Switches - Structural exploitations */
  /*  1 - xC */
  /*  2 - xP */
  /*  3 - xPs */
  /*  4 - xPs' */
  /*  5 - xC' */
  /*  6 - Ax */
  /*  7 - xA' */
  /*  8 - Bx */
  /*  9 - xB' */
  /*  ,check_d, checkRp, checkPhiInv, checkY, checkBeta, checkL, check_t, check_dnu, checkNewton, checkInv */
  /*  sizes */
  /*  number of states in system */
  /*  number of inputs to system */
  /*  number of decision variables in z */
  /*  number of equalities in Cz=b */
  /*  number of inequalities Pz<=h */
  /*  number of soft constraints Ps*z<=hs (if possible) */
  /*  number of inequalities per time step, Fx*x + Fu*u <= f */
  /*  ells = size(Fxs,1); % number of soft constraints per time step, Fxs*x + Fus*u <= fs */
  /*  number of terminal inequalities */
  /*  check for terminal equality cons */
  /*  important to take T (the horizon) from here */
  /*  if you pass it in as a signal, code generator gets upset */
  /*  as it thinks its matrices could vary in size */
  /*  number of soft constraints per time step, Fxs*x + Fus*u <= fs */
  /*  list of slack variables */
  /* % barrier settings */
  /*  single fixed barrier weight */
  kappa = 0.005;

  /*  fixed parameter for KS-function */
  /*  default - no outer iterations */
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

  /*  option 6 - disable the use of sparse matrix structure if >0 */
  jmax = 1 - (opts[5] > 0.0);
  for (i1 = 0; i1 < 9; i1++) {
    switches[i1] = b_a[i1] * jmax;
  }

  /*  option 7 - optional setting of barrier weight kappa from outside */
  if (opts[6] > 0.0) {
    kappa = opts[6];
  }

  /*  option 8 - number of outer barrier weight iterations */
  /*  option 9 - norm tolerance for early stopping */
  /*  effectively use all iters */
  /*  option 10 - optional setting of KS parameter from outside */
  /* % precalculations */
  /*  preform to avoid later work */
  for (i1 = 0; i1 < 42; i1++) {
    for (i2 = 0; i2 < 40; i2++) {
      kappaPt[i2 + 40 * i1] = kappa * P[i1 + 42 * i2];
      kappaPtSq[i2 + 40 * i1] = kappaPt[i2 + 40 * i1] * P[i1 + 42 * i2];
    }
  }

  for (i1 = 0; i1 < 20; i1++) {
    for (i2 = 0; i2 < 40; i2++) {
      rhoPstSq[i2 + 40 * i1] = 10.0 * Ps[i1 + 20 * i2] * Ps[i1 + 20 * i2];
    }
  }

  for (i1 = 0; i1 < 1600; i1++) {
    dv16[i1] = 2.0 * H[i1];
  }

  diag(dv16, diagTwoH);

  /*  helpful to avoid lots of blkdiag calls later */
  /*  blkQR = blkdiag(Q,R); % can't call blkQR in embedded matlab 2011b */
  memset(&blkQR[0], 0, sizeof(double) << 4);
  for (i1 = 0; i1 < 3; i1++) {
    for (i2 = 0; i2 < 3; i2++) {
      blkQR[i2 + (i1 << 2)] = Q[i2 + 3 * i1];
    }
  }

  blkQR[15] = b_R;
  for (i1 = 0; i1 < 2; i1++) {
    for (i2 = 0; i2 < 3; i2++) {
      FxsT[i2 + 3 * i1] = Fxs[i1 + (i2 << 1)];
    }
  }

  for (i1 = 0; i1 < 3; i1++) {
    for (i2 = 0; i2 < 3; i2++) {
      AT[i2 + 3 * i1] = A[i1 + 3 * i2];
    }
  }

  for (i1 = 0; i1 < 30; i1++) {
    for (i2 = 0; i2 < 40; i2++) {
      CT[i2 + 40 * i1] = C[i1 + 30 * i2];
    }
  }

  for (i1 = 0; i1 < 20; i1++) {
    for (i2 = 0; i2 < 40; i2++) {
      PsT[i2 + 40 * i1] = Ps[i1 + 20 * i2];
    }

    /*  pre-allocate for KS residuals */
    es[i1] = hs[i1];
    esNew[i1] = hs[i1];
  }

  /*  pre-assignment to keep coder happy */
  memset(&dz[0], 0, 40U * sizeof(double));
  memset(&dhats[0], 0, 20U * sizeof(double));

  /* % form initial solution */
  /*  form the tail of the previous solution */
  /*  plus a step of zero control on the end */
  /*  hack - catch the slack case */
  /*  no slacks - ok for zeros at end */
  preMultByA(*(double (*)[3])&z0[37], A, switches, St);
  memcpy(&z[0], &z0[4], 36U * sizeof(double));
  z[36] = 0.0;
  for (i = 0; i < 3; i++) {
    z[i + 37] = St[i];
  }

  /* A*z0(nz - n + (1:n))]; */
  /*  check if tail works as an initializer */
  for (i1 = 0; i1 < 42; i1++) {
    rpMagNew = 0.0;
    for (i2 = 0; i2 < 40; i2++) {
      rpMagNew += P[i1 + 42 * i2] * z[i2];
    }

    b_P[i1] = (rpMagNew < h[i1]);
  }

  if (all(b_P)) {
    /*  tail is feasible */
    initSolChoice = 1;
  } else {
    /*  show the problem */
    /* P*zTail-h */
    /*  try fiddling with the slack variables */
    /*  catch just the slack case */
    /*  now check if that worked */
    for (i1 = 0; i1 < 42; i1++) {
      rpMagNew = 0.0;
      for (i2 = 0; i2 < 40; i2++) {
        rpMagNew += P[i1 + 42 * i2] * z[i2];
      }

      b_P[i1] = (rpMagNew < h[i1]);
    }

    if (all(b_P)) {
      /*  worked */
      initSolChoice = 4;
    } else {
      for (i1 = 0; i1 < 42; i1++) {
        rpMagNew = 0.0;
        for (i2 = 0; i2 < 40; i2++) {
          rpMagNew += P[i1 + 42 * i2] * z0[i2];
        }

        b_P[i1] = (rpMagNew < h[i1]);
      }

      if (all(b_P)) {
        /*  try last solution unchanged */
        memcpy(&z[0], &z0[0], 40U * sizeof(double));
        initSolChoice = 2;
      } else {
        for (i = 0; i < 42; i++) {
          b_P[i] = (0.0 < h[i]);
        }

        if (all(b_P)) {
          /*  in this case, start with zeros */
          memset(&z[0], 0, 40U * sizeof(double));
          initSolChoice = 3;
        } else {
          /*  out of ideas - zeros anyway, plus a bit for slacks */
          for (i = 0; i < 40; i++) {
            z[i] = 0.0001;
          }

          initSolChoice = 0;
        }
      }
    }
  }

  /*  if checking enabled, display solution choice */
  /* % initialization */
  /*  initial lagrange multipliers */
  memset(&nu[0], 0, 30U * sizeof(double));

  /*  precalculate d */
  multByP(z, P, Fx, Fu, Ff, switches, iFar);
  for (i = 0; i < 42; i++) {
    b_h[i] = h[i] - iFar[i];
  }

  rdivide(1.0, b_h, d);

  /*  calculate residuals for first iteration */
  /*  calculate primal residual Cz-b */
  multByC(z, A, B, C, switches, rp);
  for (i1 = 0; i1 < 30; i1++) {
    rp[i1] -= b[i1];
  }

  /* C*z - b; */
  rpMag = norm(rp);
  memset(&dv17[0], 0, 30U * sizeof(double));
  multByCT(dv17, CT, AT, B, switches, diagPhi);
  for (i1 = 0; i1 < 40; i1++) {
    rpMagNew = 0.0;
    for (i2 = 0; i2 < 42; i2++) {
      rpMagNew += kappaPt[i1 + 40 * i2] * d[i2];
    }

    rd[i1] = ((diagTwoH[i1] * z[i1] + g[i1]) + rpMagNew) + diagPhi[i1];
  }

  /* C'*nu; */
  /*  checkCT = max(abs(multByCT(nu,AT,BT,EfT,T,n,m,ellef) - C'*nu)) */
  /*  optional soft constraint info */
  if (flagUseSoftCons) {
    /*  evaluate soft version of d */
    calcDs(z, Ps, Fxs, Fus, es, flagNoPade, switches, ds);

    /*  add to residual */
    multByPsT(ds, PsT, FxsT, Fus, switches, diagPhi);
    for (i1 = 0; i1 < 40; i1++) {
      rd[i1] += diagPhi[i1];
    }

    /* Ps'*ds; */
  }

  rdMag = b_norm(rd);
  b_rdMag[0] = rdMag;
  b_rdMag[1] = rpMag;
  rMag = c_norm(b_rdMag);

  /* % outer loop with varying barrier weights */
  iterCount = 0.0;

  /*     %% main solution loop for Newton's method */
  kk = 0;
  exitg1 = false;
  while ((!exitg1) && (kk <= (int)opts[1] - 1)) {
    /*  check the P multiplier */
    /*  check residual calc */
    /*  if using soft cons with KS */
    if (flagUseSoftCons) {
      /*  need the "d-hat" for the second derivatives of the KS functions */
      for (i = 0; i < 20; i++) {
        ds[i] = (1.0 + es[i]) * (1.0 + es[i]);
      }

      b_rdivide(es, ds, dhats);
    }

    /*  first form inverse of Phi */
    if (flagPhiIsDiag) {
      /*  form the diagonals of Phi */
      for (i1 = 0; i1 < 42; i1++) {
        b_h[i1] = d[i1] * d[i1];
      }

      for (i1 = 0; i1 < 40; i1++) {
        rpMagNew = 0.0;
        for (i2 = 0; i2 < 42; i2++) {
          rpMagNew += kappaPtSq[i1 + 40 * i2] * b_h[i2];
        }

        diagPhi[i1] = diagTwoH[i1] + rpMagNew;
      }

      /*  plus soft cons if used */
      if (flagUseSoftCons) {
        for (i1 = 0; i1 < 40; i1++) {
          rpMagNew = 0.0;
          for (i2 = 0; i2 < 20; i2++) {
            rpMagNew += rhoPstSq[i1 + 40 * i2] * dhats[i2];
          }

          diagPhi[i1] += rpMagNew;
        }
      }

      /*  "invert" it */
      memcpy(&b_diagPhi[0], &diagPhi[0], 40U * sizeof(double));
      c_rdivide(1.0, b_diagPhi, dv18);
      b_diag(dv18, phiInv);
    } else {
      /*  preallocate to avoid slowdown */
      memset(&phiInv[0], 0, 1600U * sizeof(double));

      /*  build the blocks of Phi inverse */
      if (flagUseSoftCons) {
        for (i = 0; i < 4; i++) {
          b_d[i] = d[i] * d[i];
        }

        c_diag(b_d, blkInv);
        d_diag(*(double (*)[2])&dhats[0], b_b);
        rpMagNew = 0.0;
        for (i1 = 0; i1 < 4; i1++) {
          b_d[i1] = 0.0;
          for (i2 = 0; i2 < 4; i2++) {
            b_d[i1] += kappa * Fu[i2] * blkInv[i2 + (i1 << 2)];
          }

          rpMagNew += b_d[i1] * Fu[i1];
        }

        ajj = 0.0;
        for (i1 = 0; i1 < 2; i1++) {
          b_rdMag[i1] = 0.0;
          for (i2 = 0; i2 < 2; i2++) {
            b_rdMag[i1] += 10.0 * Fus[i2] * b_b[i2 + (i1 << 1)];
          }

          ajj += b_rdMag[i1] * Fus[i1];
        }

        phiInv[0] = mySymPDinv((2.0 * b_R + rpMagNew) + ajj);
      } else {
        for (i = 0; i < 4; i++) {
          b_d[i] = d[i] * d[i];
        }

        c_diag(b_d, blkInv);
        rpMagNew = 0.0;
        for (i1 = 0; i1 < 4; i1++) {
          b_d[i1] = 0.0;
          for (i2 = 0; i2 < 4; i2++) {
            b_d[i1] += kappa * Fu[i2] * blkInv[i2 + (i1 << 2)];
          }

          rpMagNew += b_d[i1] * Fu[i1];
        }

        phiInv[0] = mySymPDinv(2.0 * b_R + rpMagNew);
      }

      for (ii = 0; ii < 9; ii++) {
        if (flagUseSoftCons) {
          i1 = ((1 + ii) << 2) - 1;
          i2 = ((1 + ii) << 2) - 1;
          for (j = 0; j < 4; j++) {
            b_d[j] = d[(j + i1) + 1] * d[(j + i2) + 1];
          }

          c_diag(b_d, blkInv);
          i1 = ((1 + ii) << 1) - 1;
          for (i2 = 0; i2 < 2; i2++) {
            b_rdMag[i2] = dhats[(i2 + i1) + 1];
          }

          d_diag(b_rdMag, b_b);
          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 3; i2++) {
              b_Fx[i2 + (i1 << 2)] = Fx[i1 + (i2 << 2)];
            }

            b_Fx[3 + (i1 << 2)] = Fu[i1];
            for (i2 = 0; i2 < 4; i2++) {
              b_kappa[i2 + (i1 << 2)] = kappa * b_Fx[i2 + (i1 << 2)];
            }
          }

          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 4; i2++) {
              c_kappa[i1 + (i2 << 2)] = 0.0;
              for (j = 0; j < 4; j++) {
                c_kappa[i1 + (i2 << 2)] += b_kappa[i1 + (j << 2)] * blkInv[j +
                  (i2 << 2)];
              }
            }
          }

          for (i1 = 0; i1 < 3; i1++) {
            for (i2 = 0; i2 < 4; i2++) {
              b_Fx[i2 + (i1 << 2)] = Fx[i2 + (i1 << 2)];
            }
          }

          for (i1 = 0; i1 < 4; i1++) {
            b_Fx[12 + i1] = Fu[i1];
          }

          for (i1 = 0; i1 < 2; i1++) {
            for (i2 = 0; i2 < 3; i2++) {
              b_Fxs[i2 + (i1 << 2)] = Fxs[i1 + (i2 << 1)];
            }

            b_Fxs[3 + (i1 << 2)] = Fus[i1];
            for (i2 = 0; i2 < 4; i2++) {
              dv19[i2 + (i1 << 2)] = 10.0 * b_Fxs[i2 + (i1 << 2)];
            }
          }

          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 2; i2++) {
              dv20[i1 + (i2 << 2)] = 0.0;
              for (j = 0; j < 2; j++) {
                dv20[i1 + (i2 << 2)] += dv19[i1 + (j << 2)] * b_b[j + (i2 << 1)];
              }
            }
          }

          for (i1 = 0; i1 < 3; i1++) {
            for (i2 = 0; i2 < 2; i2++) {
              b_Fxs[i2 + (i1 << 1)] = Fxs[i2 + (i1 << 1)];
            }
          }

          for (i1 = 0; i1 < 2; i1++) {
            b_Fxs[6 + i1] = Fus[i1];
          }

          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 4; i2++) {
              rpMagNew = 0.0;
              for (j = 0; j < 4; j++) {
                rpMagNew += c_kappa[i1 + (j << 2)] * b_Fx[j + (i2 << 2)];
              }

              dv21[i1 + (i2 << 2)] = 2.0 * blkQR[i1 + (i2 << 2)] + rpMagNew;
            }
          }

          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 4; i2++) {
              b_kappa[i1 + (i2 << 2)] = 0.0;
              for (j = 0; j < 2; j++) {
                b_kappa[i1 + (i2 << 2)] += dv20[i1 + (j << 2)] * b_Fxs[j + (i2 <<
                  1)];
              }
            }
          }

          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 4; i2++) {
              c_kappa[i2 + (i1 << 2)] = dv21[i2 + (i1 << 2)] + b_kappa[i2 + (i1 <<
                2)];
            }
          }

          b_mySymPDinv(c_kappa, blkInv);
        } else {
          i1 = ((1 + ii) << 2) - 1;
          i2 = ((1 + ii) << 2) - 1;
          for (j = 0; j < 4; j++) {
            b_d[j] = d[(j + i1) + 1] * d[(j + i2) + 1];
            for (ix = 0; ix < 3; ix++) {
              c_Fx[ix + (j << 2)] = Fx[j + (ix << 2)];
            }

            c_Fx[3 + (j << 2)] = Fu[j];
            for (ix = 0; ix < 4; ix++) {
              b_kappa[ix + (j << 2)] = kappa * c_Fx[ix + (j << 2)];
            }
          }

          c_diag(b_d, blkInv);
          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 4; i2++) {
              c_kappa[i1 + (i2 << 2)] = 0.0;
              for (j = 0; j < 4; j++) {
                c_kappa[i1 + (i2 << 2)] += b_kappa[i1 + (j << 2)] * blkInv[j +
                  (i2 << 2)];
              }
            }
          }

          for (i1 = 0; i1 < 3; i1++) {
            for (i2 = 0; i2 < 4; i2++) {
              b_Fx[i2 + (i1 << 2)] = Fx[i2 + (i1 << 2)];
            }
          }

          for (i1 = 0; i1 < 4; i1++) {
            b_Fx[12 + i1] = Fu[i1];
          }

          for (i1 = 0; i1 < 4; i1++) {
            for (i2 = 0; i2 < 4; i2++) {
              rpMagNew = 0.0;
              for (j = 0; j < 4; j++) {
                rpMagNew += c_kappa[i1 + (j << 2)] * b_Fx[j + (i2 << 2)];
              }

              dv21[i1 + (i2 << 2)] = 2.0 * blkQR[i1 + (i2 << 2)] + rpMagNew;
            }
          }

          b_mySymPDinv(dv21, blkInv);
        }

        i1 = ii << 2;
        i2 = ii << 2;
        for (j = 0; j < 4; j++) {
          for (ix = 0; ix < 4; ix++) {
            phiInv[((ix + i1) + 40 * ((j + i2) + 1)) + 1] = blkInv[ix + (j << 2)];
          }
        }

        /*  [Q-tilde S-tilde; S-tilde' R-tilde] */
      }

      for (i = 0; i < 2; i++) {
        b_rdMag[i] = d[i + 40] * d[i + 40];
      }

      d_diag(b_rdMag, b_b);
      for (i1 = 0; i1 < 3; i1++) {
        for (i2 = 0; i2 < 2; i2++) {
          d_kappa[i1 + 3 * i2] = 0.0;
          for (j = 0; j < 2; j++) {
            d_kappa[i1 + 3 * i2] += kappa * Ff[j + (i1 << 1)] * b_b[j + (i2 << 1)];
          }
        }
      }

      for (i1 = 0; i1 < 3; i1++) {
        for (i2 = 0; i2 < 3; i2++) {
          rpMagNew = 0.0;
          for (j = 0; j < 2; j++) {
            rpMagNew += d_kappa[i1 + 3 * j] * Ff[j + (i2 << 1)];
          }

          L[i1 + 3 * i2] = 2.0 * Qf[i1 + 3 * i2] + rpMagNew;
        }
      }

      c_mySymPDinv(L, tmp);
      for (i1 = 0; i1 < 3; i1++) {
        for (i2 = 0; i2 < 3; i2++) {
          phiInv[(i2 + 40 * (37 + i1)) + 37] = tmp[i2 + 3 * i1];
        }
      }
    }

    /*  check phi inverted correctly */
    /*  preallocate Y */
    memset(&Y[0], 0, 900U * sizeof(double));

    /*  form the block elements of Y = C*phiInv*C' */
    /*  some functions to get block terms Q,R and S out of phi-inverse easily */
    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 3; i2++) {
        Y[i1 + 30 * i2] = B[i1] * phiInv[0] * B[i2] + phiInv[(i1 + 40 * (1 + i2))
          + 1];
      }
    }

    for (ii = 0; ii < 10; ii++) {
      if (1 + ii < 10) {
        /*              Y((ii-1)*n+(1:n),ii*n+(1:n)) = -Qtil(phiInv,ii,n,m)*A' - Stil(phiInv,ii,n,m)*B'; %Yabove(:,:,ii) */
        /*  some functions to get block terms Q,R and S out of phi-inverse easily */
        i1 = ii << 2;
        i2 = ii << 2;
        j = ii << 2;
        ix = (1 + ii) << 2;
        for (iy = 0; iy < 3; iy++) {
          for (jj = 0; jj < 3; jj++) {
            b_A[jj + 3 * iy] = phiInv[((jj + i1) + 40 * ((iy + i2) + 1)) + 1];
          }

          St[iy] = phiInv[((iy + j) + 40 * ix) + 1];
        }

        memcpy(&c_A[0], &b_A[0], 9U * sizeof(double));
        multByAT(c_A, AT, switches, b_A);
        i = ii * 3;
        i1 = (1 + ii) * 3;
        for (i2 = 0; i2 < 3; i2++) {
          for (j = 0; j < 3; j++) {
            Y[(i2 + i) + 30 * (j + i1)] = -b_A[i2 + 3 * j] - St[i2] * B[j];
          }
        }

        /* Yabove(:,:,ii) */
        i1 = (1 + ii) * 3;
        i = ii * 3;
        i2 = (1 + ii) * 3;
        b_info = ii * 3;
        for (j = 0; j < 3; j++) {
          for (ix = 0; ix < 3; ix++) {
            b_Y[ix + 3 * j] = Y[(j + b_info) + 30 * (ix + i2)];
          }
        }

        for (i2 = 0; i2 < 3; i2++) {
          for (j = 0; j < 3; j++) {
            Y[(j + i1) + 30 * (i2 + i)] = b_Y[j + 3 * i2];
          }
        }
      }

      if (1 + ii > 1) {
        /*              tmp = A*Stil(phiInv,ii-1,n,m)*B'; */
        i1 = (ii - 1) << 2;
        i2 = ii << 2;
        for (j = 0; j < 3; j++) {
          b_St[j] = phiInv[((j + i1) + 40 * i2) + 1];
        }

        preMultByA(b_St, A, switches, St);

        /*              Y((ii-1)*n+(1:n),(ii-1)*n+(1:n)) = A*Qtil(phiInv,ii-1,n,m)*A' + tmp + tmp' + B*Rtil(phiInv,ii-1,n,m)*B' + Qtil(phiInv,ii,n,m); */
        /*              Y((ii-1)*n+(1:n),(ii-1)*n+(1:n)) = preMultByA(Qtil(phiInv,ii-1,n,m),A)*A' + tmp + tmp' + B*Rtil(phiInv,ii-1,n,m)*B' + Qtil(phiInv,ii,n,m); */
        /*  some functions to get block terms Q,R and S out of phi-inverse easily */
        i1 = (ii - 1) << 2;
        i2 = (ii - 1) << 2;

        /*  some functions to get block terms Q,R and S out of phi-inverse easily */
        j = ii << 2;
        ix = ii << 2;
        for (iy = 0; iy < 3; iy++) {
          for (jj = 0; jj < 3; jj++) {
            tmp[iy + 3 * jj] = St[iy] * B[jj];
            b_A[jj + 3 * iy] = phiInv[((jj + i1) + 40 * ((iy + i2) + 1)) + 1];
            b_Y[jj + 3 * iy] = phiInv[((jj + j) + 40 * ((iy + ix) + 1)) + 1];
          }
        }

        memcpy(&d_A[0], &b_A[0], 9U * sizeof(double));
        b_preMultByA(d_A, A, switches, b_A);
        memcpy(&e_A[0], &b_A[0], 9U * sizeof(double));
        multByAT(e_A, AT, switches, b_A);
        i = ii * 3;
        b_info = ii * 3;
        for (i1 = 0; i1 < 3; i1++) {
          for (i2 = 0; i2 < 3; i2++) {
            Y[(i1 + i) + 30 * (i2 + b_info)] = (((b_A[i1 + 3 * i2] + tmp[i1 + 3 *
              i2]) + tmp[i2 + 3 * i1]) + B[i1] * phiInv[(ii << 2) + 40 * (ii <<
              2)] * B[i2]) + b_Y[i1 + 3 * i2];
          }
        }
      }
    }

    /*      % -------- DO ALL THE Y STUFF AGAIN -------- % */
    /*  */
    /*      % preallocate Y */
    /*      Y2 = zeros(ne); */
    /*  */
    /*      % form the block elements of Y = C*phiInv*C' */
    /*      Y2(1:n,1:n) = B*Rtil(phiInv,0,n,m)*B' + Qtil(phiInv,1,n,m); */
    /*      for ii=1:T, */
    /*          if ii<T, */
    /*              Y2((ii-1)*n+(1:n),ii*n+(1:n)) = -Qtil(phiInv,ii,n,m)*A' - Stil(phiInv,ii,n,m)*B'; %Yabove(:,:,ii) */
    /*              Y2(ii*n+(1:n),(ii-1)*n+(1:n)) = Y2((ii-1)*n+(1:n),ii*n+(1:n))'; */
    /*          end */
    /*          if ii>1, */
    /*              tmp = A*Stil(phiInv,ii-1,n,m)*B'; */
    /*              Y2((ii-1)*n+(1:n),(ii-1)*n+(1:n)) = A*Qtil(phiInv,ii-1,n,m)*A' + tmp + tmp' + B*Rtil(phiInv,ii-1,n,m)*B' + Qtil(phiInv,ii,n,m); */
    /*          end */
    /*      end */
    /*  */
    /*      % -------- DO ALL THE Y STUFF AGAIN -------- % */
    /*  add terms for terminal equality cons */
    /*  now check that Y was constructed correctly */
    if (flagChecking) {
      for (i1 = 0; i1 < 30; i1++) {
        for (i2 = 0; i2 < 40; i2++) {
          b_C[i1 + 30 * i2] = 0.0;
          for (j = 0; j < 40; j++) {
            b_C[i1 + 30 * i2] += C[i1 + 30 * j] * phiInv[j + 40 * i2];
          }
        }
      }

      for (i1 = 0; i1 < 30; i1++) {
        for (i2 = 0; i2 < 30; i2++) {
          rpMagNew = 0.0;
          for (j = 0; j < 40; j++) {
            rpMagNew += b_C[i1 + 30 * j] * C[i2 + 30 * j];
          }

          c_Y[i1 + 30 * i2] = Y[i1 + 30 * i2] - rpMagNew;
        }
      }

      d_norm(c_Y);
    }

    /*  now form PhiInv * rd in preparation for making the RHS (-beta) */
    memset(&diagPhi[0], 0, 40U * sizeof(double));
    diagPhi[0] = phiInv[0] * rd[0];
    for (ii = 0; ii < 9; ii++) {
      /*  some functions to get block terms Q,R and S out of phi-inverse easily */
      i1 = ii << 2;
      i2 = ii << 2;
      j = ii << 2;
      ix = (1 + ii) << 2;
      iy = ii << 2;
      jj = (1 + ii) << 2;
      for (jmax = 0; jmax < 3; jmax++) {
        for (i = 0; i < 3; i++) {
          b_A[i + 3 * jmax] = phiInv[((i + i1) + 40 * ((jmax + i2) + 1)) + 1];
        }

        St[jmax] = phiInv[((jmax + j) + 40 * ix) + 1];
        b_St[jmax] = phiInv[((jmax + iy) + 40 * jj) + 1];
      }

      i1 = ii << 2;
      for (i2 = 0; i2 < 4; i2++) {
        b_b[i2] = rd[(i2 + i1) + 1];
      }

      i1 = ii << 2;
      for (i2 = 0; i2 < 3; i2++) {
        for (j = 0; j < 3; j++) {
          b_kappa[j + (i2 << 2)] = b_A[j + 3 * i2];
        }
      }

      for (i2 = 0; i2 < 3; i2++) {
        b_kappa[12 + i2] = St[i2];
      }

      for (i2 = 0; i2 < 3; i2++) {
        b_kappa[3 + (i2 << 2)] = b_St[i2];
      }

      b_kappa[15] = phiInv[((1 + ii) << 2) + 40 * ((1 + ii) << 2)];
      for (i2 = 0; i2 < 4; i2++) {
        diagPhi[(i2 + i1) + 1] = 0.0;
        for (j = 0; j < 4; j++) {
          diagPhi[(i2 + i1) + 1] += b_kappa[i2 + (j << 2)] * b_b[j];
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
    multByC(diagPhi, A, B, C, switches, rhs);
    for (i1 = 0; i1 < 30; i1++) {
      rhs[i1] = rp[i1] - rhs[i1];
    }

    /*  check it */
    /*  now find the blocks of the lower triangular Cholesky factorization of Y */
    memset(&b_L[0], 0, 900U * sizeof(double));

    /*  another function to get n x n square block elements */
    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_A[i2 + 3 * i1] = Y[i2 + 30 * i1];
      }
    }

    b_info = 0;
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
          ajj += b_A[ix] * b_A[iy];
          ix += 3;
          iy += 3;
        }
      }

      ajj = b_A[jj] - ajj;
      if (ajj > 0.0) {
        ajj = sqrt(ajj);
        b_A[jj] = ajj;
        if (j + 1 < 3) {
          if (j == 0) {
          } else {
            ix = j;
            i1 = (j + 3 * (j - 1)) + 2;
            for (jmax = j + 2; jmax <= i1; jmax += 3) {
              rpMagNew = -b_A[ix];
              iy = jj + 1;
              i2 = (jmax - j) + 1;
              for (i = jmax; i <= i2; i++) {
                b_A[iy] += b_A[i - 1] * rpMagNew;
                iy++;
              }

              ix += 3;
            }
          }

          ajj = 1.0 / ajj;
          i1 = (jj - j) + 3;
          for (jmax = jj + 1; jmax + 1 <= i1; jmax++) {
            b_A[jmax] *= ajj;
          }
        }

        j++;
      } else {
        b_A[jj] = ajj;
        b_info = j + 1;
        exitg5 = true;
      }
    }

    if (b_info == 0) {
      jmax = 3;
    } else {
      jmax = b_info - 1;
    }

    for (j = 1; j + 1 <= jmax; j++) {
      for (i = 1; i <= j; i++) {
        b_A[(i + 3 * j) - 1] = 0.0;
      }
    }

    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 3; i2++) {
        b_L[i2 + 30 * i1] = b_A[i2 + 3 * i1];
      }
    }

    for (ii = 0; ii < 9; ii++) {
      /*  another function to get n x n square block elements */
      i = ii * 3;
      b_info = ii * 3;

      /*  another function to get n x n square block elements */
      jmax = ii * 3;
      i1 = (1 + ii) * 3;
      for (i2 = 0; i2 < 3; i2++) {
        for (j = 0; j < 3; j++) {
          tmp[j + 3 * i2] = b_L[(j + i) + 30 * (i2 + b_info)];
          b_Y[j + 3 * i2] = Y[(j + jmax) + 30 * (i2 + i1)];
        }
      }

      linsolve(tmp, b_Y, b_A);
      i1 = (1 + ii) * 3;
      i = ii * 3;
      for (i2 = 0; i2 < 3; i2++) {
        for (j = 0; j < 3; j++) {
          b_L[(j + i1) + 30 * (i2 + i)] = b_A[i2 + 3 * j];
        }
      }

      /*  another function to get n x n square block elements */
      i1 = (1 + ii) * 3;
      i2 = (1 + ii) * 3;

      /*  another function to get n x n square block elements */
      j = (1 + ii) * 3;
      i = ii * 3;

      /*  another function to get n x n square block elements */
      ix = (1 + ii) * 3;
      b_info = ii * 3;
      for (iy = 0; iy < 3; iy++) {
        for (jj = 0; jj < 3; jj++) {
          tmp[jj + 3 * iy] = Y[(jj + i1) + 30 * (iy + i2)];
          b_Y[jj + 3 * iy] = b_L[(jj + j) + 30 * (iy + i)];
          L[jj + 3 * iy] = b_L[(jj + ix) + 30 * (iy + b_info)];
        }
      }

      for (i1 = 0; i1 < 3; i1++) {
        for (i2 = 0; i2 < 3; i2++) {
          rpMagNew = 0.0;
          for (j = 0; j < 3; j++) {
            rpMagNew += b_Y[i1 + 3 * j] * L[i2 + 3 * j];
          }

          b_A[i1 + 3 * i2] = tmp[i1 + 3 * i2] - rpMagNew;
        }
      }

      b_info = 0;
      j = 0;
      exitg4 = false;
      while ((!exitg4) && (j + 1 < 4)) {
        jj = j + j * 3;
        ajj = 0.0;
        if (j < 1) {
        } else {
          ix = j;
          iy = j;
          for (jmax = 1; jmax <= j; jmax++) {
            ajj += b_A[ix] * b_A[iy];
            ix += 3;
            iy += 3;
          }
        }

        ajj = b_A[jj] - ajj;
        if (ajj > 0.0) {
          ajj = sqrt(ajj);
          b_A[jj] = ajj;
          if (j + 1 < 3) {
            if (j == 0) {
            } else {
              ix = j;
              i1 = (j + 3 * (j - 1)) + 2;
              for (jmax = j + 2; jmax <= i1; jmax += 3) {
                rpMagNew = -b_A[ix];
                iy = jj + 1;
                i2 = (jmax - j) + 1;
                for (i = jmax; i <= i2; i++) {
                  b_A[iy] += b_A[i - 1] * rpMagNew;
                  iy++;
                }

                ix += 3;
              }
            }

            ajj = 1.0 / ajj;
            i1 = (jj - j) + 3;
            for (jmax = jj + 1; jmax + 1 <= i1; jmax++) {
              b_A[jmax] *= ajj;
            }
          }

          j++;
        } else {
          b_A[jj] = ajj;
          b_info = j + 1;
          exitg4 = true;
        }
      }

      if (b_info == 0) {
        jmax = 3;
      } else {
        jmax = b_info - 1;
      }

      for (j = 1; j + 1 <= jmax; j++) {
        for (i = 1; i <= j; i++) {
          b_A[(i + 3 * j) - 1] = 0.0;
        }
      }

      i1 = (1 + ii) * 3;
      i2 = (1 + ii) * 3;
      for (j = 0; j < 3; j++) {
        for (ix = 0; ix < 3; ix++) {
          b_L[(ix + i1) + 30 * (j + i2)] = b_A[ix + 3 * j];
        }
      }
    }

    /*  and the extra bits for terminal equality cons */
    /*  now check the thing */
    if (flagChecking) {
      for (i1 = 0; i1 < 30; i1++) {
        for (i2 = 0; i2 < 30; i2++) {
          rpMagNew = 0.0;
          for (j = 0; j < 30; j++) {
            rpMagNew += b_L[i1 + 30 * j] * b_L[i2 + 30 * j];
          }

          c_Y[i1 + 30 * i2] = rpMagNew - Y[i1 + 30 * i2];
        }
      }

      d_norm(c_Y);
    }

    /*  solve (L*L')*dnu=rhs: part one: solve for t=L'*dnu */
    memset(&t[0], 0, 30U * sizeof(double));

    /*  another function to get n x n square block elements */
    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 3; i2++) {
        L[i2 + 3 * i1] = b_L[i2 + 30 * i1];
      }
    }

    b_linsolve(L, *(double (*)[3])&rhs[0], St);
    for (i = 0; i < 3; i++) {
      t[i] = St[i];
    }

    for (ii = 0; ii < 9; ii++) {
      /*  another function to get n x n square block elements */
      i1 = (1 + ii) * 3;
      i2 = (1 + ii) * 3;

      /*  another function to get n x n square block elements */
      j = (1 + ii) * 3;
      i = ii * 3;
      b_info = ii * 3 - 1;
      for (ix = 0; ix < 3; ix++) {
        for (iy = 0; iy < 3; iy++) {
          tmp[iy + 3 * ix] = b_L[(iy + i1) + 30 * (ix + i2)];
          b_Y[iy + 3 * ix] = b_L[(iy + j) + 30 * (ix + i)];
        }

        St[ix] = t[(ix + b_info) + 1];
      }

      i1 = (1 + ii) * 3 - 1;
      for (i2 = 0; i2 < 3; i2++) {
        rpMagNew = 0.0;
        for (j = 0; j < 3; j++) {
          rpMagNew += b_Y[i2 + 3 * j] * St[j];
        }

        b_St[i2] = rhs[(i2 + i1) + 1] - rpMagNew;
      }

      b_linsolve(tmp, b_St, St);
      for (i = 0; i < 3; i++) {
        t[i + (1 + ii) * 3] = St[i];
      }
    }

    /*  final elements for terminal equalities */
    /*  check solve process */
    /*  now solve part two: L'*dnu = t; */
    memset(&dnu[0], 0, 30U * sizeof(double));

    /*  different start for terminal equality case */
    /*  another function to get n x n square block elements */
    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 3; i2++) {
        L[i2 + 3 * i1] = b_L[(i1 + 30 * (27 + i2)) + 27];
      }
    }

    c_linsolve(L, *(double (*)[3])&t[27], St);
    for (i = 0; i < 3; i++) {
      dnu[i + 27] = St[i];
    }

    for (ii = 0; ii < 9; ii++) {
      /*  another function to get n x n square block elements */
      i1 = (8 - ii) * 3;
      i2 = (8 - ii) * 3;

      /*  another function to get n x n square block elements */
      j = (9 - ii) * 3;
      ix = (8 - ii) * 3;
      iy = (9 - ii) * 3 - 1;
      for (jj = 0; jj < 3; jj++) {
        for (jmax = 0; jmax < 3; jmax++) {
          tmp[jmax + 3 * jj] = b_L[(jmax + i1) + 30 * (jj + i2)];
          b_Y[jmax + 3 * jj] = b_L[(jmax + j) + 30 * (jj + ix)];
        }

        St[jj] = dnu[(jj + iy) + 1];
      }

      for (i1 = 0; i1 < 3; i1++) {
        for (i2 = 0; i2 < 3; i2++) {
          L[i2 + 3 * i1] = tmp[i1 + 3 * i2];
        }
      }

      i1 = (8 - ii) * 3 - 1;
      for (i2 = 0; i2 < 3; i2++) {
        rpMagNew = 0.0;
        for (j = 0; j < 3; j++) {
          rpMagNew += b_Y[j + 3 * i2] * St[j];
        }

        b_St[i2] = t[(i2 + i1) + 1] - rpMagNew;
      }

      c_linsolve(L, b_St, St);
      for (i = 0; i < 3; i++) {
        dnu[i + (8 - ii) * 3] = St[i];
      }
    }

    /*  check the whole solve worked */
    /*      % ------------------ DOUBLE THE LINSOLVE -------------------- % */
    /*  */
    /*  */
    /*      % now find the blocks of the lower triangular Cholesky factorization of Y */
    /*      L2 = zeros(ne); */
    /*      L2(1:n,1:n) = chol(getSqBlk(Y,1,1,n),'lower'); */
    /*      for ii=2:T, */
    /*          L2((ii-1)*n+(1:n),(ii-2)*n+(1:n)) = linsolve(getSqBlk(L2,ii-1,ii-1,n),getSqBlk(Y,ii-1,ii,n),struct('LT',true))'; */
    /*          L2((ii-1)*n+(1:n),(ii-1)*n+(1:n)) = chol(getSqBlk(Y,ii,ii,n) - getSqBlk(L2,ii,ii-1,n)*getSqBlk(L2,ii,ii-1,n)','lower'); */
    /*      end */
    /*  */
    /*      % and the extra bits for terminal equality cons */
    /*      if ellef>0, */
    /*          L2(T*n+(1:ellef),(T-1)*n+(1:n)) = linsolve(getSqBlk(L2,T,T,n),Y((T-1)*n+(1:n),T*n+(1:ellef)),struct('LT',true))'; */
    /*          L2(T*n+(1:ellef),T*n+(1:ellef)) = chol(Y(T*n+(1:ellef),T*n+(1:ellef)) - L2(T*n+(1:ellef),(T-1)*n+(1:n))*L2(T*n+(1:ellef),(T-1)*n+(1:n))','lower'); */
    /*      end */
    /*  */
    /*      % solve (L*L')*dnu=rhs: part one: solve for t=L'*dnu */
    /*      t2 = zeros(ne,1); */
    /*      t2(1:n) = linsolve(getSqBlk(L2,1,1,n),rhs(1:n),struct('LT',true)); */
    /*      for ii=1:(T-1), */
    /*          t2(ii*n + (1:n)) = linsolve(getSqBlk(L2,ii+1,ii+1,n),rhs(ii*n + (1:n)) - getSqBlk(L2,ii+1,ii,n)*t2((ii-1)*n + (1:n)),struct('LT',true)); */
    /*      end */
    /*      % final elements for terminal equalities */
    /*      if ellef>0, */
    /*          t2(T*n + (1:ellef)) = linsolve(L2(T*n+(1:ellef),T*n+(1:ellef)),rhs(T*n + (1:ellef)) - L2(T*n+(1:ellef),(T-1)*n+(1:n))*t2((T-1)*n + (1:n)),struct('LT',true)); */
    /*      end */
    /*  */
    /*      % now solve part two: L'*dnu = t; */
    /*      dnu2 = zeros(ne,1); */
    /*      % different start for terminal equality case */
    /*      if ellef>0, */
    /*          dnu2(T*n + (1:ellef)) = linsolve(L2(T*n+(1:ellef),T*n+(1:ellef))',t2(T*n + (1:ellef)),struct('UT',true)); */
    /*          dnu2((T-1)*n + (1:n)) = linsolve(getSqBlk(L2,T,T,n)',t2((T-1)*n + (1:n)) - L2(T*n+(1:ellef),(T-1)*n+(1:n))'*dnu2(T*n + (1:ellef)),struct('UT',true)); */
    /*      else */
    /*          dnu2((T-1)*n + (1:n)) = linsolve(getSqBlk(L2,T,T,n)',t2((T-1)*n + (1:n)),struct('UT',true)); */
    /*      end */
    /*      for ii=(T-1):-1:1, */
    /*          dnu2((ii-1)*n + (1:n)) = linsolve(getSqBlk(L2,ii,ii,n)',t2((ii-1)*n + (1:n)) - getSqBlk(L2,ii+1,ii,n)'*dnu2((ii)*n + (1:n)),struct('UT',true)); */
    /*      end */
    /*  */
    /*      % ------------------ END OF DOUBLE THE LINSOLVE ---------------% */
    /*  going to need -(rd + C'*dnu) in next bit */
    /*  check computation of Newton step */
    /*  now solve for dz */
    if (flagPhiIsDiag) {
      /*  solve for dz assuming PhiInv diagonal */
      diag(phiInv, dz);
      multByCT(dnu, CT, AT, B, switches, diagPhi);
      for (i1 = 0; i1 < 40; i1++) {
        dz[i1] *= -rd[i1] - diagPhi[i1];
      }

      /* C'*dnu); */
    } else {
      /*  form the vector to be multiplied, for shorthand */
      multByCT(dnu, CT, AT, B, switches, diagPhi);
      for (i1 = 0; i1 < 40; i1++) {
        diagPhi[i1] = -rd[i1] - diagPhi[i1];
      }

      /* C'*dnu); */
      /*  now form PhiInv * rd in preparation for making the RHS (-beta) */
      dz[0] = phiInv[0] * diagPhi[0];
      for (ii = 0; ii < 9; ii++) {
        /*  some functions to get block terms Q,R and S out of phi-inverse easily */
        i1 = ii << 2;
        i2 = ii << 2;
        j = ii << 2;
        ix = (1 + ii) << 2;
        iy = ii << 2;
        jj = (1 + ii) << 2;
        for (jmax = 0; jmax < 3; jmax++) {
          for (i = 0; i < 3; i++) {
            b_A[i + 3 * jmax] = phiInv[((i + i1) + 40 * ((jmax + i2) + 1)) + 1];
          }

          St[jmax] = phiInv[((jmax + j) + 40 * ix) + 1];
          b_St[jmax] = phiInv[((jmax + iy) + 40 * jj) + 1];
        }

        i1 = ii << 2;
        for (i2 = 0; i2 < 4; i2++) {
          b_b[i2] = diagPhi[(i2 + i1) + 1];
        }

        i1 = ii << 2;
        for (i2 = 0; i2 < 3; i2++) {
          for (j = 0; j < 3; j++) {
            b_kappa[j + (i2 << 2)] = b_A[j + 3 * i2];
          }
        }

        for (i2 = 0; i2 < 3; i2++) {
          b_kappa[12 + i2] = St[i2];
        }

        for (i2 = 0; i2 < 3; i2++) {
          b_kappa[3 + (i2 << 2)] = b_St[i2];
        }

        b_kappa[15] = phiInv[((1 + ii) << 2) + 40 * ((1 + ii) << 2)];
        for (i2 = 0; i2 < 4; i2++) {
          dz[(i2 + i1) + 1] = 0.0;
          for (j = 0; j < 4; j++) {
            dz[(i2 + i1) + 1] += b_kappa[i2 + (j << 2)] * b_b[j];
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
    /*  line search */
    ajj = 1.0;

    /*  part 1 - reduce until feasible */
    jj = 0;
    exitg3 = false;
    while ((!exitg3) && (jj < 10)) {
      for (i = 0; i < 40; i++) {
        b_z[i] = z[i] + ajj * dz[i];
      }

      multByP(b_z, P, Fx, Fu, Ff, switches, iFar);
      for (i1 = 0; i1 < 42; i1++) {
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
    s = ajj / 100.0;
    for (i = 0; i < 40; i++) {
      zNew[i] = z[i] + s * dz[i];
    }

    multByP(zNew, P, Fx, Fu, Ff, switches, iFar);

    /*  new residuals */
    for (i1 = 0; i1 < 42; i1++) {
      b_h[i1] = h[i1] - iFar[i1];
    }

    rdivide(1.0, b_h, iFar);
    for (i = 0; i < 30; i++) {
      b_nu[i] = nu[i] + s * dnu[i];
    }

    multByCT(b_nu, CT, AT, B, switches, diagPhi);
    for (i1 = 0; i1 < 40; i1++) {
      rpMagNew = 0.0;
      for (i2 = 0; i2 < 42; i2++) {
        rpMagNew += kappaPt[i1 + 40 * i2] * iFar[i2];
      }

      rdNew[i1] = ((diagTwoH[i1] * zNew[i1] + g[i1]) + rpMagNew) + diagPhi[i1];
    }

    /* C'*nuNew; */
    if (flagUseSoftCons) {
      memcpy(&esNew[0], &hs[0], 20U * sizeof(double));
      b_calcDs(zNew, Ps, Fxs, Fus, esNew, 10.0, flagNoPade, switches, ds);
      multByPsT(ds, PsT, FxsT, Fus, switches, diagPhi);
      for (i1 = 0; i1 < 40; i1++) {
        rdNew[i1] += diagPhi[i1];
      }

      /* Ps'*dsNew; */
      /*          checkPsT = max(abs(multByPsT(dsNew,FxsT,FusT,T,n,m,ells) - Ps'*dsNew)) */
    }

    /*  calculate primal residual Cz-b */
    multByC(zNew, A, B, C, switches, rhs);
    for (i1 = 0; i1 < 30; i1++) {
      rhs[i1] -= b[i1];
    }

    rdMagNew[0] = b_norm(rdNew);
    rdMagNew[1] = norm(rhs);
    gradRmag = 100.0 * (c_norm(rdMagNew) - rMag);

    /*      % Fix for doubling backtracking operation */
    /*      z2 = z; */
    /*      nu2 = nu; */
    /*      rMag2 = rMag; */
    /*      dsNew2 = dsNew; */
    /*      esNew2 = esNew; */
    /*      rdNew2 = rdNew; */
    /*      rpNew2 = rpNew; */
    /*      rpMagNew2 = rpMagNew; */
    /*      rdMagNew2 = rdMagNew; */
    /*      rMagNew2 = rMagNew; */
    /*  part 3 - backtracking */
    s = ajj;
    jj = 0;
    exitg2 = false;
    while ((!exitg2) && (jj < 10)) {
      for (i = 0; i < 40; i++) {
        zNew[i] = z[i] + s * dz[i];
      }

      for (i = 0; i < 30; i++) {
        t[i] = nu[i] + s * dnu[i];
      }

      multByP(zNew, P, Fx, Fu, Ff, switches, iFar);

      /*  new residuals */
      for (i1 = 0; i1 < 42; i1++) {
        b_h[i1] = h[i1] - iFar[i1];
      }

      rdivide(1.0, b_h, iFar);
      multByCT(t, CT, AT, B, switches, diagPhi);
      for (i1 = 0; i1 < 40; i1++) {
        rpMagNew = 0.0;
        for (i2 = 0; i2 < 42; i2++) {
          rpMagNew += kappaPt[i1 + 40 * i2] * iFar[i2];
        }

        rdNew[i1] = ((diagTwoH[i1] * zNew[i1] + g[i1]) + rpMagNew) + diagPhi[i1];
      }

      /* C'*nuNew; */
      if (flagUseSoftCons) {
        memcpy(&esNew[0], &hs[0], 20U * sizeof(double));
        b_calcDs(zNew, Ps, Fxs, Fus, esNew, 10.0, flagNoPade, switches, ds);
        multByPsT(ds, PsT, FxsT, Fus, switches, diagPhi);
        for (i1 = 0; i1 < 40; i1++) {
          rdNew[i1] += diagPhi[i1];
        }

        /* Ps'*dsNew; */
      }

      /*  calculate primal residual Cz-b */
      multByC(zNew, A, B, C, switches, rhs);
      for (i1 = 0; i1 < 30; i1++) {
        rhs[i1] -= b[i1];
      }

      ajj = b_norm(rdNew);
      rpMagNew = norm(rhs);
      b_rdMagNew[0] = ajj;
      b_rdMagNew[1] = rpMagNew;
      rMagNew = c_norm(b_rdMagNew);

      /*  test */
      if (rMagNew < rMag + 0.5 * s * gradRmag) {
        /*  update */
        memcpy(&z[0], &zNew[0], 40U * sizeof(double));
        memcpy(&nu[0], &t[0], 30U * sizeof(double));
        memcpy(&d[0], &iFar[0], 42U * sizeof(double));
        memcpy(&rd[0], &rdNew[0], 40U * sizeof(double));
        memcpy(&rp[0], &rhs[0], 30U * sizeof(double));
        rpMag = rpMagNew;
        rdMag = ajj;
        rMag = rMagNew;
        if (flagUseSoftCons) {
          memcpy(&es[0], &esNew[0], 20U * sizeof(double));
        }

        /*  do nothing */
        /*  lineSearchPass=[kk jj s norm(rdNew) norm(rpNew)] */
        exitg2 = true;
      } else {
        /* covg = false */
        s *= 0.7;
        jj++;
      }
    }

    /*      % DO PART 3 AGAIN */
    /*      % part 3 - backtracking */
    /*      s = sMax; */
    /*      for jj=1:10, */
    /*          zNew2 = z2 + s*dz; */
    /*          nuNew2 = nu2 + s*dnu; */
    /*          iNew2 = h - multByP(zNew2,Fx,Fu,Ff,T,n,m,ell,ellf); */
    /*  */
    /*          % new residuals */
    /*          dNew2 = 1./iNew2; */
    /*          rdNew2 = diagTwoH.*zNew2 + g + kappaPt*dNew2 + C'*nuNew2; */
    /*          if flagUseSoftCons, */
    /*              [dsNew2,esNew2] = calcDs(zNew2,Ps,hs,rho,flagNoPade); */
    /*              rdNew2 = rdNew2 + Ps'*dsNew2; */
    /*          end */
    /*          rpNew2 = calcRp(zNew2,b,A,B,Ef,T,n,m,ellef); */
    /*          rdMagNew2 = norm(rdNew2); */
    /*          rpMagNew2 = norm(rpNew2); */
    /*          rMagNew2 = norm([rdMagNew2;rpMagNew2]); */
    /*  */
    /*          % test */
    /*          if rMagNew2 < rMag2 + 0.5*s*gradRmag, */
    /*  */
    /*              % update */
    /*              z2 = zNew2; */
    /*              nu2 = nuNew2; */
    /*              d2 = dNew2; */
    /*              rd2 = rdNew2; */
    /*              rp2 = rpNew2; */
    /*              rpMag2 = rpMagNew2; */
    /*              rdMag2 = rdMagNew2; */
    /*              rMag2 = rMagNew2; */
    /*  */
    /*              if flagUseSoftCons, */
    /*  */
    /*                  ds2 = dsNew2; */
    /*                  es2 = esNew2; */
    /*  */
    /*              end */
    /*  */
    /*              % do nothing */
    /*              % lineSearchPass=[kk jj s norm(rdNew) norm(rpNew)] */
    /*              break */
    /*  */
    /*          else */
    /*  */
    /*              %covg = false */
    /*              s = s*0.7; */
    /*  */
    /*          end */
    /*      end */
    /*      % END OF DO PART 3 AGAIN */
    /*  optional early termination */
    if (rMag < 0.0) {
      exitg1 = true;
    } else {
      iterCount++;
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

  /*  iteration count */
}

/*
 * File trailer for mpcsolve.c
 *
 * [EOF]
 */
