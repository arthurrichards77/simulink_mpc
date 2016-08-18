/*
 * File: eig.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 18-Aug-2016 10:55:52
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "mpcsolve_outer.h"
#include "eig.h"
#include "sqrt.h"
#include "mod.h"
#include "isfinite.h"
#include "mpcsolve_outer_rtwutil.h"

/* Function Declarations */
static void b_eml_matlab_zlartg(const creal_T f, const creal_T g, double *cs,
  creal_T *sn);
static void b_eml_matlab_zlascl(double cfrom, double cto, creal_T A[40]);
static void eml_matlab_zggbal(creal_T A[1600], int *ilo, int *ihi, int rscale[40]);
static void eml_matlab_zgghrd(int ilo, int ihi, creal_T A[1600]);
static void eml_matlab_zhgeqz(const creal_T A[1600], int ilo, int ihi, int *info,
  creal_T alpha1[40], creal_T beta1[40]);
static double eml_matlab_zlangeM(const creal_T x[1600]);
static double eml_matlab_zlanhs(const creal_T A[1600], int ilo, int ihi);
static void eml_matlab_zlartg(const creal_T f, const creal_T g, double *cs,
  creal_T *sn, creal_T *r);
static void eml_matlab_zlascl(double cfrom, double cto, creal_T A[1600]);

/* Function Definitions */

/*
 * Arguments    : const creal_T f
 *                const creal_T g
 *                double *cs
 *                creal_T *sn
 * Return Type  : void
 */
static void b_eml_matlab_zlartg(const creal_T f, const creal_T g, double *cs,
  creal_T *sn)
{
  double scale;
  double f2s;
  double g2;
  double fs_re;
  double fs_im;
  double gs_re;
  double gs_im;
  boolean_T guard1 = false;
  double g2s;
  scale = fabs(f.re);
  f2s = fabs(f.im);
  if (f2s > scale) {
    scale = f2s;
  }

  f2s = fabs(g.re);
  g2 = fabs(g.im);
  if (g2 > f2s) {
    f2s = g2;
  }

  if (f2s > scale) {
    scale = f2s;
  }

  fs_re = f.re;
  fs_im = f.im;
  gs_re = g.re;
  gs_im = g.im;
  guard1 = false;
  if (scale >= 7.4428285367870146E+137) {
    do {
      fs_re *= 1.3435752215134178E-138;
      fs_im *= 1.3435752215134178E-138;
      gs_re *= 1.3435752215134178E-138;
      gs_im *= 1.3435752215134178E-138;
      scale *= 1.3435752215134178E-138;
    } while (!(scale < 7.4428285367870146E+137));

    guard1 = true;
  } else if (scale <= 1.3435752215134178E-138) {
    if ((g.re == 0.0) && (g.im == 0.0)) {
      *cs = 1.0;
      sn->re = 0.0;
      sn->im = 0.0;
    } else {
      do {
        fs_re *= 7.4428285367870146E+137;
        fs_im *= 7.4428285367870146E+137;
        gs_re *= 7.4428285367870146E+137;
        gs_im *= 7.4428285367870146E+137;
        scale *= 7.4428285367870146E+137;
      } while (!(scale > 1.3435752215134178E-138));

      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    scale = fs_re * fs_re + fs_im * fs_im;
    g2 = gs_re * gs_re + gs_im * gs_im;
    f2s = g2;
    if (1.0 > g2) {
      f2s = 1.0;
    }

    if (scale <= f2s * 2.0041683600089728E-292) {
      if ((f.re == 0.0) && (f.im == 0.0)) {
        *cs = 0.0;
        scale = rt_hypotd_snf(gs_re, gs_im);
        sn->re = gs_re / scale;
        sn->im = -gs_im / scale;
      } else {
        g2s = sqrt(g2);
        *cs = rt_hypotd_snf(fs_re, fs_im) / g2s;
        f2s = fabs(f.re);
        g2 = fabs(f.im);
        if (g2 > f2s) {
          f2s = g2;
        }

        if (f2s > 1.0) {
          scale = rt_hypotd_snf(f.re, f.im);
          fs_re = f.re / scale;
          fs_im = f.im / scale;
        } else {
          f2s = 7.4428285367870146E+137 * f.re;
          g2 = 7.4428285367870146E+137 * f.im;
          scale = rt_hypotd_snf(f2s, g2);
          fs_re = f2s / scale;
          fs_im = g2 / scale;
        }

        gs_re /= g2s;
        gs_im = -gs_im / g2s;
        sn->re = fs_re * gs_re - fs_im * gs_im;
        sn->im = fs_re * gs_im + fs_im * gs_re;
      }
    } else {
      f2s = sqrt(1.0 + g2 / scale);
      *cs = 1.0 / f2s;
      scale += g2;
      fs_re = f2s * fs_re / scale;
      fs_im = f2s * fs_im / scale;
      sn->re = fs_re * gs_re - fs_im * -gs_im;
      sn->im = fs_re * -gs_im + fs_im * gs_re;
    }
  }
}

/*
 * Arguments    : double cfrom
 *                double cto
 *                creal_T A[40]
 * Return Type  : void
 */
static void b_eml_matlab_zlascl(double cfrom, double cto, creal_T A[40])
{
  double cfromc;
  double ctoc;
  boolean_T notdone;
  double cfrom1;
  double cto1;
  double mul;
  int i23;
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    cfrom1 = cfromc * 2.0041683600089728E-292;
    cto1 = ctoc / 4.9896007738368E+291;
    if ((fabs(cfrom1) > fabs(ctoc)) && (ctoc != 0.0)) {
      mul = 2.0041683600089728E-292;
      cfromc = cfrom1;
    } else if (fabs(cto1) > fabs(cfromc)) {
      mul = 4.9896007738368E+291;
      ctoc = cto1;
    } else {
      mul = ctoc / cfromc;
      notdone = false;
    }

    for (i23 = 0; i23 < 40; i23++) {
      A[i23].re *= mul;
      A[i23].im *= mul;
    }
  }
}

/*
 * Arguments    : creal_T A[1600]
 *                int *ilo
 *                int *ihi
 *                int rscale[40]
 * Return Type  : void
 */
static void eml_matlab_zggbal(creal_T A[1600], int *ilo, int *ihi, int rscale[40])
{
  int32_T exitg2;
  int i;
  int j;
  boolean_T found;
  int ii;
  boolean_T exitg5;
  int nzcount;
  int jj;
  boolean_T exitg6;
  boolean_T guard2 = false;
  double atmp_re;
  double atmp_im;
  int32_T exitg1;
  boolean_T exitg3;
  boolean_T exitg4;
  boolean_T guard1 = false;
  memset(&rscale[0], 0, 40U * sizeof(int));
  *ilo = 1;
  *ihi = 40;
  do {
    exitg2 = 0;
    i = 0;
    j = 0;
    found = false;
    ii = *ihi;
    exitg5 = false;
    while ((!exitg5) && (ii > 0)) {
      nzcount = 0;
      i = ii;
      j = *ihi;
      jj = 1;
      exitg6 = false;
      while ((!exitg6) && (jj <= *ihi)) {
        guard2 = false;
        if ((A[(ii + 40 * (jj - 1)) - 1].re != 0.0) || (A[(ii + 40 * (jj - 1)) -
             1].im != 0.0) || (ii == jj)) {
          if (nzcount == 0) {
            j = jj;
            nzcount = 1;
            guard2 = true;
          } else {
            nzcount = 2;
            exitg6 = true;
          }
        } else {
          guard2 = true;
        }

        if (guard2) {
          jj++;
        }
      }

      if (nzcount < 2) {
        found = true;
        exitg5 = true;
      } else {
        ii--;
      }
    }

    if (!found) {
      exitg2 = 2;
    } else {
      if (i != *ihi) {
        for (ii = 0; ii < 40; ii++) {
          atmp_re = A[(i + 40 * ii) - 1].re;
          atmp_im = A[(i + 40 * ii) - 1].im;
          A[(i + 40 * ii) - 1] = A[(*ihi + 40 * ii) - 1];
          A[(*ihi + 40 * ii) - 1].re = atmp_re;
          A[(*ihi + 40 * ii) - 1].im = atmp_im;
        }
      }

      if (j != *ihi) {
        for (ii = 0; ii + 1 <= *ihi; ii++) {
          atmp_re = A[ii + 40 * (j - 1)].re;
          atmp_im = A[ii + 40 * (j - 1)].im;
          A[ii + 40 * (j - 1)] = A[ii + 40 * (*ihi - 1)];
          A[ii + 40 * (*ihi - 1)].re = atmp_re;
          A[ii + 40 * (*ihi - 1)].im = atmp_im;
        }
      }

      rscale[*ihi - 1] = j;
      (*ihi)--;
      if (*ihi == 1) {
        rscale[0] = 1;
        exitg2 = 1;
      }
    }
  } while (exitg2 == 0);

  if (exitg2 == 1) {
  } else {
    do {
      exitg1 = 0;
      i = 0;
      j = 0;
      found = false;
      jj = *ilo;
      exitg3 = false;
      while ((!exitg3) && (jj <= *ihi)) {
        nzcount = 0;
        i = *ihi;
        j = jj;
        ii = *ilo;
        exitg4 = false;
        while ((!exitg4) && (ii <= *ihi)) {
          guard1 = false;
          if ((A[(ii + 40 * (jj - 1)) - 1].re != 0.0) || (A[(ii + 40 * (jj - 1))
               - 1].im != 0.0) || (ii == jj)) {
            if (nzcount == 0) {
              i = ii;
              nzcount = 1;
              guard1 = true;
            } else {
              nzcount = 2;
              exitg4 = true;
            }
          } else {
            guard1 = true;
          }

          if (guard1) {
            ii++;
          }
        }

        if (nzcount < 2) {
          found = true;
          exitg3 = true;
        } else {
          jj++;
        }
      }

      if (!found) {
        exitg1 = 1;
      } else {
        if (i != *ilo) {
          for (ii = *ilo - 1; ii + 1 < 41; ii++) {
            atmp_re = A[(i + 40 * ii) - 1].re;
            atmp_im = A[(i + 40 * ii) - 1].im;
            A[(i + 40 * ii) - 1] = A[(*ilo + 40 * ii) - 1];
            A[(*ilo + 40 * ii) - 1].re = atmp_re;
            A[(*ilo + 40 * ii) - 1].im = atmp_im;
          }
        }

        if (j != *ilo) {
          for (ii = 0; ii + 1 <= *ihi; ii++) {
            atmp_re = A[ii + 40 * (j - 1)].re;
            atmp_im = A[ii + 40 * (j - 1)].im;
            A[ii + 40 * (j - 1)] = A[ii + 40 * (*ilo - 1)];
            A[ii + 40 * (*ilo - 1)].re = atmp_re;
            A[ii + 40 * (*ilo - 1)].im = atmp_im;
          }
        }

        rscale[*ilo - 1] = j;
        (*ilo)++;
        if (*ilo == *ihi) {
          rscale[*ilo - 1] = *ilo;
          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

/*
 * Arguments    : int ilo
 *                int ihi
 *                creal_T A[1600]
 * Return Type  : void
 */
static void eml_matlab_zgghrd(int ilo, int ihi, creal_T A[1600])
{
  int jcol;
  int jrow;
  creal_T s;
  double c;
  int j;
  double stemp_re;
  double stemp_im;
  double A_im;
  double A_re;
  if (ihi < ilo + 2) {
  } else {
    for (jcol = ilo - 1; jcol + 1 < ihi - 1; jcol++) {
      for (jrow = ihi - 1; jrow + 1 > jcol + 2; jrow--) {
        eml_matlab_zlartg(A[(jrow + 40 * jcol) - 1], A[jrow + 40 * jcol], &c, &s,
                          &A[(jrow + 40 * jcol) - 1]);
        A[jrow + 40 * jcol].re = 0.0;
        A[jrow + 40 * jcol].im = 0.0;
        for (j = jcol + 1; j + 1 <= ihi; j++) {
          stemp_re = c * A[(jrow + 40 * j) - 1].re + (s.re * A[jrow + 40 * j].re
            - s.im * A[jrow + 40 * j].im);
          stemp_im = c * A[(jrow + 40 * j) - 1].im + (s.re * A[jrow + 40 * j].im
            + s.im * A[jrow + 40 * j].re);
          A_im = A[(jrow + 40 * j) - 1].im;
          A_re = A[(jrow + 40 * j) - 1].re;
          A[jrow + 40 * j].re = c * A[jrow + 40 * j].re - (s.re * A[(jrow + 40 *
            j) - 1].re + s.im * A[(jrow + 40 * j) - 1].im);
          A[jrow + 40 * j].im = c * A[jrow + 40 * j].im - (s.re * A_im - s.im *
            A_re);
          A[(jrow + 40 * j) - 1].re = stemp_re;
          A[(jrow + 40 * j) - 1].im = stemp_im;
        }

        s.re = -s.re;
        s.im = -s.im;
        for (j = ilo - 1; j + 1 <= ihi; j++) {
          stemp_re = c * A[j + 40 * jrow].re + (s.re * A[j + 40 * (jrow - 1)].re
            - s.im * A[j + 40 * (jrow - 1)].im);
          stemp_im = c * A[j + 40 * jrow].im + (s.re * A[j + 40 * (jrow - 1)].im
            + s.im * A[j + 40 * (jrow - 1)].re);
          A_im = A[j + 40 * jrow].im;
          A_re = A[j + 40 * jrow].re;
          A[j + 40 * (jrow - 1)].re = c * A[j + 40 * (jrow - 1)].re - (s.re *
            A[j + 40 * jrow].re + s.im * A[j + 40 * jrow].im);
          A[j + 40 * (jrow - 1)].im = c * A[j + 40 * (jrow - 1)].im - (s.re *
            A_im - s.im * A_re);
          A[j + 40 * jrow].re = stemp_re;
          A[j + 40 * jrow].im = stemp_im;
        }
      }
    }
  }
}

/*
 * Arguments    : const creal_T A[1600]
 *                int ilo
 *                int ihi
 *                int *info
 *                creal_T alpha1[40]
 *                creal_T beta1[40]
 * Return Type  : void
 */
static void eml_matlab_zhgeqz(const creal_T A[1600], int ilo, int ihi, int *info,
  creal_T alpha1[40], creal_T beta1[40])
{
  creal_T b_A[1600];
  int i;
  double eshift_re;
  double eshift_im;
  creal_T ctemp;
  double rho_re;
  double rho_im;
  double anorm;
  double temp;
  double b_atol;
  double sigma2_re;
  double ascale;
  boolean_T failed;
  int j;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  int ifirst;
  int istart;
  int ilast;
  int ilastm1;
  int ifrstm;
  int ilastm;
  int iiter;
  boolean_T goto60;
  boolean_T goto70;
  boolean_T goto90;
  int jiter;
  int32_T exitg1;
  boolean_T exitg3;
  boolean_T ilazro;
  boolean_T b_guard1 = false;
  creal_T t1;
  creal_T d;
  boolean_T exitg2;
  double temp2;
  double tempr;
  int x;
  memcpy(&b_A[0], &A[0], 1600U * sizeof(creal_T));
  *info = 0;
  for (i = 0; i < 40; i++) {
    alpha1[i].re = 0.0;
    alpha1[i].im = 0.0;
    beta1[i].re = 1.0;
    beta1[i].im = 0.0;
  }

  eshift_re = 0.0;
  eshift_im = 0.0;
  ctemp.re = 0.0;
  ctemp.im = 0.0;
  rho_re = 0.0;
  rho_im = 0.0;
  anorm = eml_matlab_zlanhs(A, ilo, ihi);
  temp = 2.2204460492503131E-16 * anorm;
  b_atol = 2.2250738585072014E-308;
  if (temp > 2.2250738585072014E-308) {
    b_atol = temp;
  }

  sigma2_re = 2.2250738585072014E-308;
  if (anorm > 2.2250738585072014E-308) {
    sigma2_re = anorm;
  }

  ascale = 1.0 / sigma2_re;
  failed = true;
  for (j = ihi; j + 1 < 41; j++) {
    alpha1[j] = A[j + 40 * j];
  }

  guard1 = false;
  guard2 = false;
  if (ihi >= ilo) {
    ifirst = ilo;
    istart = ilo;
    ilast = ihi - 1;
    ilastm1 = ihi - 2;
    ifrstm = ilo;
    ilastm = ihi;
    iiter = 0;
    goto60 = false;
    goto70 = false;
    goto90 = false;
    jiter = 1;
    do {
      exitg1 = 0;
      if (jiter <= 30 * ((ihi - ilo) + 1)) {
        if (ilast + 1 == ilo) {
          goto60 = true;
        } else if (fabs(b_A[ilast + 40 * ilastm1].re) + fabs(b_A[ilast + 40 *
                    ilastm1].im) <= b_atol) {
          b_A[ilast + 40 * ilastm1].re = 0.0;
          b_A[ilast + 40 * ilastm1].im = 0.0;
          goto60 = true;
        } else {
          j = ilastm1;
          exitg3 = false;
          while ((!exitg3) && (j + 1 >= ilo)) {
            if (j + 1 == ilo) {
              ilazro = true;
            } else if (fabs(b_A[j + 40 * (j - 1)].re) + fabs(b_A[j + 40 * (j - 1)]
                        .im) <= b_atol) {
              b_A[j + 40 * (j - 1)].re = 0.0;
              b_A[j + 40 * (j - 1)].im = 0.0;
              ilazro = true;
            } else {
              ilazro = false;
            }

            if (ilazro) {
              ifirst = j + 1;
              goto70 = true;
              exitg3 = true;
            } else {
              j--;
            }
          }
        }

        if (goto60 || goto70) {
          ilazro = true;
        } else {
          ilazro = false;
        }

        if (!ilazro) {
          for (i = 0; i < 40; i++) {
            alpha1[i].re = rtNaN;
            alpha1[i].im = 0.0;
            beta1[i].re = rtNaN;
            beta1[i].im = 0.0;
          }

          *info = 1;
          exitg1 = 1;
        } else {
          b_guard1 = false;
          if (goto60) {
            goto60 = false;
            alpha1[ilast] = b_A[ilast + 40 * ilast];
            ilast = ilastm1;
            ilastm1--;
            if (ilast + 1 < ilo) {
              failed = false;
              guard2 = true;
              exitg1 = 1;
            } else {
              iiter = 0;
              eshift_re = 0.0;
              eshift_im = 0.0;
              ilastm = ilast + 1;
              if (ifrstm > ilast + 1) {
                ifrstm = ilo;
              }

              b_guard1 = true;
            }
          } else {
            if (goto70) {
              goto70 = false;
              iiter++;
              ifrstm = ifirst;
              if (b_mod(iiter) != 0) {
                temp = -(b_A[ilast + 40 * ilast].re - b_A[ilastm1 + 40 * ilastm1]
                         .re);
                sigma2_re = -(b_A[ilast + 40 * ilast].im - b_A[ilastm1 + 40 *
                              ilastm1].im);
                if (sigma2_re == 0.0) {
                  t1.re = temp / 2.0;
                  t1.im = 0.0;
                } else if (temp == 0.0) {
                  t1.re = 0.0;
                  t1.im = sigma2_re / 2.0;
                } else {
                  t1.re = temp / 2.0;
                  t1.im = sigma2_re / 2.0;
                }

                d.re = (t1.re * t1.re - t1.im * t1.im) + (b_A[ilastm1 + 40 *
                  ilast].re * b_A[ilast + 40 * ilastm1].re - b_A[ilastm1 + 40 *
                  ilast].im * b_A[ilast + 40 * ilastm1].im);
                d.im = (t1.re * t1.im + t1.im * t1.re) + (b_A[ilastm1 + 40 *
                  ilast].re * b_A[ilast + 40 * ilastm1].im + b_A[ilastm1 + 40 *
                  ilast].im * b_A[ilast + 40 * ilastm1].re);
                b_sqrt(&d);
                rho_re = b_A[ilastm1 + 40 * ilastm1].re - (t1.re - d.re);
                rho_im = b_A[ilastm1 + 40 * ilastm1].im - (t1.im - d.im);
                sigma2_re = b_A[ilastm1 + 40 * ilastm1].re - (t1.re + d.re);
                anorm = b_A[ilastm1 + 40 * ilastm1].im - (t1.im + d.im);
                if (rt_hypotd_snf(rho_re - b_A[ilast + 40 * ilast].re, rho_im -
                                  b_A[ilast + 40 * ilast].im) <= rt_hypotd_snf
                    (sigma2_re - b_A[ilast + 40 * ilast].re, anorm - b_A[ilast +
                     40 * ilast].im)) {
                  sigma2_re = rho_re;
                  anorm = rho_im;
                  rho_re = t1.re - d.re;
                  rho_im = t1.im - d.im;
                } else {
                  rho_re = t1.re + d.re;
                  rho_im = t1.im + d.im;
                }
              } else {
                eshift_re += b_A[ilast + 40 * ilastm1].re;
                eshift_im += b_A[ilast + 40 * ilastm1].im;
                sigma2_re = eshift_re;
                anorm = eshift_im;
              }

              j = ilastm1;
              i = ilastm1 + 1;
              exitg2 = false;
              while ((!exitg2) && (j + 1 > ifirst)) {
                istart = j + 1;
                ctemp.re = b_A[j + 40 * j].re - sigma2_re;
                ctemp.im = b_A[j + 40 * j].im - anorm;
                temp = ascale * (fabs(ctemp.re) + fabs(ctemp.im));
                temp2 = ascale * (fabs(b_A[i + 40 * j].re) + fabs(b_A[i + 40 * j]
                  .im));
                tempr = temp;
                if (temp2 > temp) {
                  tempr = temp2;
                }

                if ((tempr < 1.0) && (tempr != 0.0)) {
                  temp /= tempr;
                  temp2 /= tempr;
                }

                if ((fabs(b_A[j + 40 * (j - 1)].re) + fabs(b_A[j + 40 * (j - 1)]
                      .im)) * temp2 <= temp * b_atol) {
                  goto90 = true;
                  exitg2 = true;
                } else {
                  i = j;
                  j--;
                }
              }

              if (!goto90) {
                istart = ifirst;
                if (ifirst == ilastm1 + 1) {
                  ctemp.re = rho_re;
                  ctemp.im = rho_im;
                } else {
                  ctemp.re = b_A[(ifirst + 40 * (ifirst - 1)) - 1].re -
                    sigma2_re;
                  ctemp.im = b_A[(ifirst + 40 * (ifirst - 1)) - 1].im - anorm;
                }

                goto90 = true;
              }
            }

            if (goto90) {
              goto90 = false;
              b_eml_matlab_zlartg(ctemp, b_A[istart + 40 * (istart - 1)], &temp,
                                  &t1);
              j = istart;
              i = istart - 2;
              while (j < ilast + 1) {
                if (j > istart) {
                  eml_matlab_zlartg(b_A[(j + 40 * i) - 1], b_A[j + 40 * i],
                                    &temp, &t1, &b_A[(j + 40 * i) - 1]);
                  b_A[j + 40 * i].re = 0.0;
                  b_A[j + 40 * i].im = 0.0;
                }

                for (i = j - 1; i + 1 <= ilastm; i++) {
                  d.re = temp * b_A[(j + 40 * i) - 1].re + (t1.re * b_A[j + 40 *
                    i].re - t1.im * b_A[j + 40 * i].im);
                  d.im = temp * b_A[(j + 40 * i) - 1].im + (t1.re * b_A[j + 40 *
                    i].im + t1.im * b_A[j + 40 * i].re);
                  sigma2_re = b_A[(j + 40 * i) - 1].im;
                  anorm = b_A[(j + 40 * i) - 1].re;
                  b_A[j + 40 * i].re = temp * b_A[j + 40 * i].re - (t1.re * b_A
                    [(j + 40 * i) - 1].re + t1.im * b_A[(j + 40 * i) - 1].im);
                  b_A[j + 40 * i].im = temp * b_A[j + 40 * i].im - (t1.re *
                    sigma2_re - t1.im * anorm);
                  b_A[(j + 40 * i) - 1] = d;
                }

                t1.re = -t1.re;
                t1.im = -t1.im;
                x = j;
                if (ilast + 1 < j + 2) {
                  x = ilast - 1;
                }

                for (i = ifrstm - 1; i + 1 <= x + 2; i++) {
                  d.re = temp * b_A[i + 40 * j].re + (t1.re * b_A[i + 40 * (j -
                    1)].re - t1.im * b_A[i + 40 * (j - 1)].im);
                  d.im = temp * b_A[i + 40 * j].im + (t1.re * b_A[i + 40 * (j -
                    1)].im + t1.im * b_A[i + 40 * (j - 1)].re);
                  sigma2_re = b_A[i + 40 * j].im;
                  anorm = b_A[i + 40 * j].re;
                  b_A[i + 40 * (j - 1)].re = temp * b_A[i + 40 * (j - 1)].re -
                    (t1.re * b_A[i + 40 * j].re + t1.im * b_A[i + 40 * j].im);
                  b_A[i + 40 * (j - 1)].im = temp * b_A[i + 40 * (j - 1)].im -
                    (t1.re * sigma2_re - t1.im * anorm);
                  b_A[i + 40 * j] = d;
                }

                i = j - 1;
                j++;
              }
            }

            b_guard1 = true;
          }

          if (b_guard1) {
            jiter++;
          }
        }
      } else {
        guard2 = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  } else {
    guard1 = true;
  }

  if (guard2) {
    if (failed) {
      *info = ilast + 1;
      for (i = 0; i + 1 <= ilast + 1; i++) {
        alpha1[i].re = rtNaN;
        alpha1[i].im = 0.0;
        beta1[i].re = rtNaN;
        beta1[i].im = 0.0;
      }
    } else {
      guard1 = true;
    }
  }

  if (guard1) {
    for (j = 0; j + 1 < ilo; j++) {
      alpha1[j] = b_A[j + 40 * j];
    }
  }
}

/*
 * Arguments    : const creal_T x[1600]
 * Return Type  : double
 */
static double eml_matlab_zlangeM(const creal_T x[1600])
{
  double y;
  int k;
  boolean_T exitg1;
  double absxk;
  y = 0.0;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 1600)) {
    absxk = rt_hypotd_snf(x[k].re, x[k].im);
    if (rtIsNaN(absxk)) {
      y = rtNaN;
      exitg1 = true;
    } else {
      if (absxk > y) {
        y = absxk;
      }

      k++;
    }
  }

  return y;
}

/*
 * Arguments    : const creal_T A[1600]
 *                int ilo
 *                int ihi
 * Return Type  : double
 */
static double eml_matlab_zlanhs(const creal_T A[1600], int ilo, int ihi)
{
  double f;
  double scale;
  double sumsq;
  boolean_T firstNonZero;
  int j;
  int i20;
  int i;
  double reAij;
  double imAij;
  double temp2;
  f = 0.0;
  if (ilo > ihi) {
  } else {
    scale = 0.0;
    sumsq = 0.0;
    firstNonZero = true;
    for (j = ilo; j <= ihi; j++) {
      i20 = j + 1;
      if (ihi < j + 1) {
        i20 = ihi;
      }

      for (i = ilo; i <= i20; i++) {
        reAij = A[(i + 40 * (j - 1)) - 1].re;
        imAij = A[(i + 40 * (j - 1)) - 1].im;
        if (reAij != 0.0) {
          reAij = fabs(reAij);
          if (firstNonZero) {
            sumsq = 1.0;
            scale = reAij;
            firstNonZero = false;
          } else if (scale < reAij) {
            temp2 = scale / reAij;
            sumsq = 1.0 + sumsq * temp2 * temp2;
            scale = reAij;
          } else {
            temp2 = reAij / scale;
            sumsq += temp2 * temp2;
          }
        }

        if (imAij != 0.0) {
          reAij = fabs(imAij);
          if (firstNonZero) {
            sumsq = 1.0;
            scale = reAij;
            firstNonZero = false;
          } else if (scale < reAij) {
            temp2 = scale / reAij;
            sumsq = 1.0 + sumsq * temp2 * temp2;
            scale = reAij;
          } else {
            temp2 = reAij / scale;
            sumsq += temp2 * temp2;
          }
        }
      }
    }

    f = scale * sqrt(sumsq);
  }

  return f;
}

/*
 * Arguments    : const creal_T f
 *                const creal_T g
 *                double *cs
 *                creal_T *sn
 *                creal_T *r
 * Return Type  : void
 */
static void eml_matlab_zlartg(const creal_T f, const creal_T g, double *cs,
  creal_T *sn, creal_T *r)
{
  double scale;
  double f2s;
  double g2;
  double fs_re;
  double fs_im;
  double gs_re;
  double gs_im;
  int count;
  int rescaledir;
  boolean_T guard1 = false;
  double g2s;
  scale = fabs(f.re);
  f2s = fabs(f.im);
  if (f2s > scale) {
    scale = f2s;
  }

  f2s = fabs(g.re);
  g2 = fabs(g.im);
  if (g2 > f2s) {
    f2s = g2;
  }

  if (f2s > scale) {
    scale = f2s;
  }

  fs_re = f.re;
  fs_im = f.im;
  gs_re = g.re;
  gs_im = g.im;
  count = 0;
  rescaledir = 0;
  guard1 = false;
  if (scale >= 7.4428285367870146E+137) {
    do {
      count++;
      fs_re *= 1.3435752215134178E-138;
      fs_im *= 1.3435752215134178E-138;
      gs_re *= 1.3435752215134178E-138;
      gs_im *= 1.3435752215134178E-138;
      scale *= 1.3435752215134178E-138;
    } while (!(scale < 7.4428285367870146E+137));

    rescaledir = 1;
    guard1 = true;
  } else if (scale <= 1.3435752215134178E-138) {
    if ((g.re == 0.0) && (g.im == 0.0)) {
      *cs = 1.0;
      sn->re = 0.0;
      sn->im = 0.0;
      *r = f;
    } else {
      do {
        count++;
        fs_re *= 7.4428285367870146E+137;
        fs_im *= 7.4428285367870146E+137;
        gs_re *= 7.4428285367870146E+137;
        gs_im *= 7.4428285367870146E+137;
        scale *= 7.4428285367870146E+137;
      } while (!(scale > 1.3435752215134178E-138));

      rescaledir = -1;
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    scale = fs_re * fs_re + fs_im * fs_im;
    g2 = gs_re * gs_re + gs_im * gs_im;
    f2s = g2;
    if (1.0 > g2) {
      f2s = 1.0;
    }

    if (scale <= f2s * 2.0041683600089728E-292) {
      if ((f.re == 0.0) && (f.im == 0.0)) {
        *cs = 0.0;
        r->re = rt_hypotd_snf(g.re, g.im);
        r->im = 0.0;
        f2s = rt_hypotd_snf(gs_re, gs_im);
        sn->re = gs_re / f2s;
        sn->im = -gs_im / f2s;
      } else {
        g2s = sqrt(g2);
        *cs = rt_hypotd_snf(fs_re, fs_im) / g2s;
        f2s = fabs(f.re);
        g2 = fabs(f.im);
        if (g2 > f2s) {
          f2s = g2;
        }

        if (f2s > 1.0) {
          f2s = rt_hypotd_snf(f.re, f.im);
          fs_re = f.re / f2s;
          fs_im = f.im / f2s;
        } else {
          g2 = 7.4428285367870146E+137 * f.re;
          scale = 7.4428285367870146E+137 * f.im;
          f2s = rt_hypotd_snf(g2, scale);
          fs_re = g2 / f2s;
          fs_im = scale / f2s;
        }

        gs_re /= g2s;
        gs_im = -gs_im / g2s;
        sn->re = fs_re * gs_re - fs_im * gs_im;
        sn->im = fs_re * gs_im + fs_im * gs_re;
        r->re = *cs * f.re + (sn->re * g.re - sn->im * g.im);
        r->im = *cs * f.im + (sn->re * g.im + sn->im * g.re);
      }
    } else {
      f2s = sqrt(1.0 + g2 / scale);
      r->re = f2s * fs_re;
      r->im = f2s * fs_im;
      *cs = 1.0 / f2s;
      f2s = scale + g2;
      g2 = r->re / f2s;
      f2s = r->im / f2s;
      sn->re = g2 * gs_re - f2s * -gs_im;
      sn->im = g2 * -gs_im + f2s * gs_re;
      if (rescaledir > 0) {
        for (rescaledir = 1; rescaledir <= count; rescaledir++) {
          r->re *= 7.4428285367870146E+137;
          r->im *= 7.4428285367870146E+137;
        }
      } else {
        if (rescaledir < 0) {
          for (rescaledir = 1; rescaledir <= count; rescaledir++) {
            r->re *= 1.3435752215134178E-138;
            r->im *= 1.3435752215134178E-138;
          }
        }
      }
    }
  }
}

/*
 * Arguments    : double cfrom
 *                double cto
 *                creal_T A[1600]
 * Return Type  : void
 */
static void eml_matlab_zlascl(double cfrom, double cto, creal_T A[1600])
{
  double cfromc;
  double ctoc;
  boolean_T notdone;
  double cfrom1;
  double cto1;
  double mul;
  int i22;
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    cfrom1 = cfromc * 2.0041683600089728E-292;
    cto1 = ctoc / 4.9896007738368E+291;
    if ((fabs(cfrom1) > fabs(ctoc)) && (ctoc != 0.0)) {
      mul = 2.0041683600089728E-292;
      cfromc = cfrom1;
    } else if (fabs(cto1) > fabs(cfromc)) {
      mul = 4.9896007738368E+291;
      ctoc = cto1;
    } else {
      mul = ctoc / cfromc;
      notdone = false;
    }

    for (i22 = 0; i22 < 1600; i22++) {
      A[i22].re *= mul;
      A[i22].im *= mul;
    }
  }
}

/*
 * Arguments    : const double A[1600]
 *                creal_T V[40]
 * Return Type  : void
 */
void eig(const double A[1600], creal_T V[40])
{
  static creal_T b_A[1600];
  int i;
  double anrm;
  creal_T beta1[40];
  boolean_T ilascl;
  double anrmto;
  int rscale[40];
  int ihi;
  int info;
  double V_re;
  double V_im;
  double brm;
  for (i = 0; i < 1600; i++) {
    b_A[i].re = A[i];
    b_A[i].im = 0.0;
  }

  anrm = eml_matlab_zlangeM(b_A);
  if (!b_isfinite(anrm)) {
    for (i = 0; i < 40; i++) {
      V[i].re = rtNaN;
      V[i].im = 0.0;
      beta1[i].re = rtNaN;
      beta1[i].im = 0.0;
    }
  } else {
    ilascl = false;
    anrmto = anrm;
    if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
      anrmto = 6.7178761075670888E-139;
      ilascl = true;
    } else {
      if (anrm > 1.4885657073574029E+138) {
        anrmto = 1.4885657073574029E+138;
        ilascl = true;
      }
    }

    if (ilascl) {
      eml_matlab_zlascl(anrm, anrmto, b_A);
    }

    eml_matlab_zggbal(b_A, &i, &ihi, rscale);
    eml_matlab_zgghrd(i, ihi, b_A);
    eml_matlab_zhgeqz(b_A, i, ihi, &info, V, beta1);
    if ((info != 0) || (!ilascl)) {
    } else {
      b_eml_matlab_zlascl(anrmto, anrm, V);
    }
  }

  for (i = 0; i < 40; i++) {
    V_re = V[i].re;
    V_im = V[i].im;
    if (beta1[i].im == 0.0) {
      if (V[i].im == 0.0) {
        V[i].re /= beta1[i].re;
        V[i].im = 0.0;
      } else if (V[i].re == 0.0) {
        V[i].re = 0.0;
        V[i].im = V_im / beta1[i].re;
      } else {
        V[i].re /= beta1[i].re;
        V[i].im = V_im / beta1[i].re;
      }
    } else if (beta1[i].re == 0.0) {
      if (V[i].re == 0.0) {
        V[i].re = V[i].im / beta1[i].im;
        V[i].im = 0.0;
      } else if (V[i].im == 0.0) {
        V[i].re = 0.0;
        V[i].im = -(V_re / beta1[i].im);
      } else {
        V[i].re = V[i].im / beta1[i].im;
        V[i].im = -(V_re / beta1[i].im);
      }
    } else {
      brm = fabs(beta1[i].re);
      anrm = fabs(beta1[i].im);
      if (brm > anrm) {
        anrm = beta1[i].im / beta1[i].re;
        anrmto = beta1[i].re + anrm * beta1[i].im;
        V[i].re = (V[i].re + anrm * V[i].im) / anrmto;
        V[i].im = (V_im - anrm * V_re) / anrmto;
      } else if (anrm == brm) {
        if (beta1[i].re > 0.0) {
          anrm = 0.5;
        } else {
          anrm = -0.5;
        }

        if (beta1[i].im > 0.0) {
          anrmto = 0.5;
        } else {
          anrmto = -0.5;
        }

        V[i].re = (V[i].re * anrm + V[i].im * anrmto) / brm;
        V[i].im = (V_im * anrm - V_re * anrmto) / brm;
      } else {
        anrm = beta1[i].re / beta1[i].im;
        anrmto = beta1[i].im + anrm * beta1[i].re;
        V[i].re = (anrm * V[i].re + V[i].im) / anrmto;
        V[i].im = (anrm * V_im - V_re) / anrmto;
      }
    }
  }
}

/*
 * File trailer for eig.c
 *
 * [EOF]
 */
