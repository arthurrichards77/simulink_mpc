/*
 * File: _coder_mpcsolve_outer_api.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 18-Aug-2016 10:55:52
 */

/* Include Files */
#include "_coder_mpcsolve_outer_api.h"

/* Function Declarations */
static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *x, const
  char_T *identifier))[3];
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[3];
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *z0,
  const char_T *identifier))[40];
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[40];
static const mxArray *emlrt_marshallOut(const real_T u[40]);
static const mxArray *b_emlrt_marshallOut(const real_T u[4]);
static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3];
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
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
  real_T (*z)[40];
  real_T (*info)[4];
  static const uint32_T H[4] = { 2304440110U, 3621613059U, 3179103689U,
    2301931535U };

  static const uint32_T g[4] = { 433592848U, 1988963675U, 1702482494U,
    2028523033U };

  static const uint32_T gt[4] = { 2229548090U, 2322324860U, 3175488625U,
    685526564U };

  static const uint32_T P[4] = { 130744406U, 3803608504U, 2613355848U,
    820168967U };

  static const uint32_T hc[4] = { 3214298876U, 3098304012U, 3290972552U,
    621278850U };

  static const uint32_T hx[4] = { 3997995059U, 137396527U, 901400716U,
    115257582U };

  static const uint32_T C[4] = { 4090389873U, 206946458U, 2323895730U,
    3853742374U };

  static const uint32_T bx[4] = { 2031214983U, 382488288U, 3236943645U,
    868003649U };

  static const uint32_T bd[4] = { 1560590242U, 1576762721U, 4061634560U,
    2196932803U };

  static const uint32_T A[4] = { 3252377601U, 2558021166U, 775994380U,
    156876427U };

  static const uint32_T B[4] = { 2183649557U, 2038898500U, 2606996313U,
    3975201241U };

  static const uint32_T Fx[4] = { 485751947U, 938137285U, 2114453799U,
    2503317186U };

  static const uint32_T Fu[4] = { 2600207821U, 2211293212U, 500182784U,
    4121587958U };

  static const uint32_T Ff[4] = { 1991005488U, 352415487U, 2706501771U,
    2402791105U };

  static const uint32_T Q[4] = { 230136502U, 1292556234U, 1029439833U,
    4184769985U };

  static const uint32_T R[4] = { 3182040586U, 2756417662U, 1631241856U,
    2484635320U };

  static const uint32_T Qf[4] = { 230136502U, 1292556234U, 1029439833U,
    4184769985U };

  static const uint32_T opts[4] = { 1997206409U, 3328618002U, 3394552093U,
    1584234070U };

  static const uint32_T Ps[4] = { 2297526243U, 3616665573U, 4269893422U,
    1244977782U };

  static const uint32_T hcs[4] = { 1496288190U, 1069197138U, 2459740255U,
    2467541182U };

  static const uint32_T hxs[4] = { 2908566876U, 659426123U, 3243010503U,
    256795541U };

  static const uint32_T Ef[4] = { 3088033067U, 2773075570U, 952241795U,
    1230516860U };

  static const uint32_T Fxs[4] = { 60664867U, 270938626U, 3779300814U,
    3615244956U };

  static const uint32_T Fus[4] = { 1048186946U, 4226937186U, 225685878U,
    4173886835U };

  real_T (*x)[3];
  real_T (*xt)[3];
  real_T (*d)[3];
  real_T (*z0)[40];
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  z = (real_T (*)[40])mxMalloc(sizeof(real_T [40]));
  info = (real_T (*)[4])mxMalloc(sizeof(real_T [4]));
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
 *                const char_T *identifier
 * Return Type  : real_T (*)[3]
 */
static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *x, const
  char_T *identifier))[3]
{
  real_T (*y)[3];
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
 * Return Type  : real_T (*)[3]
 */
  static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[3]
{
  real_T (*y)[3];
  y = e_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *z0
 *                const char_T *identifier
 * Return Type  : real_T (*)[40]
 */
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *z0,
  const char_T *identifier))[40]
{
  real_T (*y)[40];
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
 * Return Type  : real_T (*)[40]
 */
  static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[40]
{
  real_T (*y)[40];
  y = f_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const real_T u[40]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real_T u[40])
{
  const mxArray *y;
  static const int32_T iv0[1] = { 0 };

  const mxArray *m0;
  static const int32_T iv1[1] = { 40 };

  y = NULL;
  m0 = emlrtCreateNumericArray(1, iv0, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m0, (void *)u);
  emlrtSetDimensions((mxArray *)m0, iv1, 1);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const real_T u[4]
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const real_T u[4])
{
  const mxArray *y;
  static const int32_T iv2[1] = { 0 };

  const mxArray *m1;
  static const int32_T iv3[1] = { 4 };

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
 * Return Type  : real_T (*)[3]
 */
static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3]
{
  real_T (*ret)[3];
  int32_T iv4[1];
  iv4[0] = 3;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, iv4);
  ret = (real_T (*)[3])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[40]
 */
  static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[40]
{
  real_T (*ret)[40];
  int32_T iv5[1];
  iv5[0] = 40;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, iv5);
  ret = (real_T (*)[40])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * File trailer for _coder_mpcsolve_outer_api.c
 *
 * [EOF]
 */
