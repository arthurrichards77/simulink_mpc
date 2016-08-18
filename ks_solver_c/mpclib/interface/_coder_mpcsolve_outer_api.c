/*
 * File: _coder_mpcsolve_outer_api.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 18-Aug-2016 17:54:05
 */

/* Include files */
#include "_coder_mpcsolve_outer_api.h"

/* Function Declarations */
static double (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *x, const
  char *identifier))[3];
static double (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[3];
static double (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *z0,
  const char *identifier))[40];
static double (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[40];
static const mxArray *emlrt_marshallOut(const double u[40]);
static const mxArray *b_emlrt_marshallOut(const double u[4]);
static double (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3];
static double (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[40];

/* Function Definitions */

/*
 * Arguments    : emlrtContext *aContext
 * Return Type  : void
 */
void mpcsolve_outer_initialize(emlrtContext *aContext)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, aContext, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void mpcsolve_outer_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void mpcsolve_outer_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  mpcsolve_outer_xil_terminate();
}

/*
 * Arguments    : const mxArray *prhs[28]
 *                const mxArray *plhs[2]
 * Return Type  : void
 */
void mpcsolve_outer_api(const mxArray *prhs[28], const mxArray *plhs[2])
{
  double (*z)[40];
  double (*info)[4];
  static const unsigned int H[4] = { 2351181072U, 2558581328U, 1822740206U,
    623979943U };

  static const unsigned int g[4] = { 433592848U, 1988963675U, 1702482494U,
    2028523033U };

  static const unsigned int gt[4] = { 2229548090U, 2322324860U, 3175488625U,
    685526564U };

  static const unsigned int P[4] = { 1392021377U, 726679884U, 4227366876U,
    2906608530U };

  static const unsigned int hc[4] = { 1568644990U, 144306006U, 3939953305U,
    2306345396U };

  static const unsigned int hx[4] = { 3126156438U, 1434467859U, 3323069499U,
    4022407162U };

  static const unsigned int C[4] = { 1209760601U, 1393916358U, 453245656U,
    3086367069U };

  static const unsigned int bx[4] = { 3705221035U, 2950102164U, 561834142U,
    1562867264U };

  static const unsigned int bd[4] = { 1169221221U, 589447476U, 4140220015U,
    2539264131U };

  static const unsigned int A[4] = { 3252377601U, 2558021166U, 775994380U,
    156876427U };

  static const unsigned int B[4] = { 2183649557U, 2038898500U, 2606996313U,
    3975201241U };

  static const unsigned int Fx[4] = { 2268724019U, 2189658241U, 325049908U,
    1755698453U };

  static const unsigned int Fu[4] = { 1998970223U, 2119396242U, 3121609449U,
    3858298556U };

  static const unsigned int Ff[4] = { 714859821U, 3988255539U, 2770106662U,
    2941377412U };

  static const unsigned int Q[4] = { 230136502U, 1292556234U, 1029439833U,
    4184769985U };

  static const unsigned int R[4] = { 3632144389U, 1937285253U, 3381811746U,
    1348605447U };

  static const unsigned int Qf[4] = { 230136502U, 1292556234U, 1029439833U,
    4184769985U };

  static const unsigned int opts[4] = { 2954038314U, 1601276418U, 2216252471U,
    3940589274U };

  static const unsigned int Ps[4] = { 2211048435U, 279254089U, 2680384057U,
    327167695U };

  static const unsigned int hcs[4] = { 2184885908U, 62780885U, 2701979729U,
    2349743935U };

  static const unsigned int hxs[4] = { 2077590468U, 3533304137U, 3879363487U,
    1631888928U };

  static const unsigned int Ef[4] = { 3687242169U, 2060032192U, 318129892U,
    4260026607U };

  static const unsigned int Fxs[4] = { 1935004703U, 2358671179U, 4257493458U,
    3616019316U };

  static const unsigned int Fus[4] = { 851795026U, 2400169501U, 1690981980U,
    4140726511U };

  double (*x)[3];
  double (*xt)[3];
  double (*d)[3];
  double (*z0)[40];
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  z = (double (*)[40])mxMalloc(sizeof(double [40]));
  info = (double (*)[4])mxMalloc(sizeof(double [4]));
  prhs[0] = emlrtProtectR2012b(prhs[0], 0, false, -1);
  prhs[1] = emlrtProtectR2012b(prhs[1], 1, false, -1);
  prhs[2] = emlrtProtectR2012b(prhs[2], 2, false, -1);
  prhs[12] = emlrtProtectR2012b(prhs[12], 12, false, -1);

  /* Check constant function inputs */
  emlrtCheckArrayChecksumR2014a(&st, "H", H, prhs[3], false);
  emlrtCheckArrayChecksumR2014a(&st, "g", g, prhs[4], false);
  emlrtCheckArrayChecksumR2014a(&st, "gt", gt, prhs[5], false);
  emlrtCheckArrayChecksumR2014a(&st, "P", P, prhs[6], false);
  emlrtCheckArrayChecksumR2014a(&st, "hc", hc, prhs[7], false);
  emlrtCheckArrayChecksumR2014a(&st, "hx", hx, prhs[8], false);
  emlrtCheckArrayChecksumR2014a(&st, "C", C, prhs[9], false);
  emlrtCheckArrayChecksumR2014a(&st, "bx", bx, prhs[10], false);
  emlrtCheckArrayChecksumR2014a(&st, "bd", bd, prhs[11], false);
  emlrtCheckArrayChecksumR2014a(&st, "A", A, prhs[13], false);
  emlrtCheckArrayChecksumR2014a(&st, "B", B, prhs[14], false);
  emlrtCheckArrayChecksumR2014a(&st, "Fx", Fx, prhs[15], false);
  emlrtCheckArrayChecksumR2014a(&st, "Fu", Fu, prhs[16], false);
  emlrtCheckArrayChecksumR2014a(&st, "Ff", Ff, prhs[17], false);
  emlrtCheckArrayChecksumR2014a(&st, "Q", Q, prhs[18], false);
  emlrtCheckArrayChecksumR2014a(&st, "R", R, prhs[19], false);
  emlrtCheckArrayChecksumR2014a(&st, "Qf", Qf, prhs[20], false);
  emlrtCheckArrayChecksumR2014a(&st, "opts", opts, prhs[21], false);
  emlrtCheckArrayChecksumR2014a(&st, "Ps", Ps, prhs[22], false);
  emlrtCheckArrayChecksumR2014a(&st, "hcs", hcs, prhs[23], false);
  emlrtCheckArrayChecksumR2014a(&st, "hxs", hxs, prhs[24], false);
  emlrtCheckArrayChecksumR2014a(&st, "Ef", Ef, prhs[25], false);
  emlrtCheckArrayChecksumR2014a(&st, "Fxs", Fxs, prhs[26], false);
  emlrtCheckArrayChecksumR2014a(&st, "Fus", Fus, prhs[27], false);

  /* Marshall function inputs */
  x = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "x");
  xt = emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "xt");
  d = emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "d");
  z0 = c_emlrt_marshallIn(&st, emlrtAlias(prhs[12]), "z0");

  /* Invoke the target function */
  mpcsolve_outer(*x, *xt, *d, *z0, *z, *info);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*z);
  plhs[1] = b_emlrt_marshallOut(*info);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *x
 *                const char *identifier
 * Return Type  : double (*)[3]
 */
static double (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *x, const
  char *identifier))[3]
{
  double (*y)[3];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = b_emlrt_marshallIn(sp, emlrtAlias(x), &thisId);
  emlrtDestroyArray(&x);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : double (*)[3]
 */
  static double (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[3]
{
  double (*y)[3];
  y = e_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *z0
 *                const char *identifier
 * Return Type  : double (*)[40]
 */
static double (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *z0,
  const char *identifier))[40]
{
  double (*y)[40];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = d_emlrt_marshallIn(sp, emlrtAlias(z0), &thisId);
  emlrtDestroyArray(&z0);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : double (*)[40]
 */
  static double (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[40]
{
  double (*y)[40];
  y = f_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const double u[40]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const double u[40])
{
  const mxArray *y;
  static const int iv0[1] = { 0 };

  const mxArray *m0;
  static const int iv1[1] = { 40 };

  y = NULL;
  m0 = emlrtCreateNumericArray(1, iv0, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m0, (void *)u);
  emlrtSetDimensions((mxArray *)m0, iv1, 1);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const double u[4]
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const double u[4])
{
  const mxArray *y;
  static const int iv2[1] = { 0 };

  const mxArray *m1;
  static const int iv3[1] = { 4 };

  y = NULL;
  m1 = emlrtCreateNumericArray(1, iv2, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m1, (void *)u);
  emlrtSetDimensions((mxArray *)m1, iv3, 1);
  emlrtAssign(&y, m1);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : double (*)[3]
 */
static double (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3]
{
  double (*ret)[3];
  int iv4[1];
  iv4[0] = 3;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, iv4);
  ret = (double (*)[3])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : double (*)[40]
 */
  static double (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[40]
{
  double (*ret)[40];
  int iv5[1];
  iv5[0] = 40;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, iv5);
  ret = (double (*)[40])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * File trailer for _coder_mpcsolve_outer_api.c
 *
 * [EOF]
 */
