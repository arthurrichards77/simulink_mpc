/* Include files */

#include "blascompat32.h"
#include "mpcSetpointCvxgen_sfun.h"
#include "c2_mpcSetpointCvxgen.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "mpcSetpointCvxgen_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[23] = { "nargin", "nargout", "x", "xt",
  "A", "B", "d", "Fx", "Fu", "f", "Ff", "ff", "Q", "R", "Qf", "Ef", "Ed", "ef",
  "Fxs", "Fus", "fs", "z", "info" };

/* Function Declarations */
static void initialize_c2_mpcSetpointCvxgen(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance);
static void initialize_params_c2_mpcSetpointCvxgen
  (SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance);
static void enable_c2_mpcSetpointCvxgen(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance);
static void disable_c2_mpcSetpointCvxgen(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_mpcSetpointCvxgen
  (SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_mpcSetpointCvxgen
  (SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance);
static void set_sim_state_c2_mpcSetpointCvxgen
  (SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance, const mxArray *c2_st);
static void finalize_c2_mpcSetpointCvxgen(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance);
static void sf_c2_mpcSetpointCvxgen(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance);
static void initSimStructsc2_mpcSetpointCvxgen
  (SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_b_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_z, const char_T *c2_identifier, real_T c2_y
  [40]);
static void c2_c_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[40]);
static void c2_d_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_info, const char_T *c2_identifier, real_T
  c2_y[4]);
static void c2_e_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[4]);
static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_f_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_g_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_mpcSetpointCvxgen, const
  char_T *c2_identifier);
static uint8_T c2_h_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_mpcSetpointCvxgen(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_is_active_c2_mpcSetpointCvxgen = 0U;
}

static void initialize_params_c2_mpcSetpointCvxgen
  (SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance)
{
}

static void enable_c2_mpcSetpointCvxgen(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_mpcSetpointCvxgen(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_mpcSetpointCvxgen
  (SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c2_mpcSetpointCvxgen
  (SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real_T c2_u[4];
  const mxArray *c2_b_y = NULL;
  int32_T c2_i1;
  real_T c2_b_u[40];
  const mxArray *c2_c_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_c_u;
  const mxArray *c2_d_y = NULL;
  real_T (*c2_z)[40];
  real_T (*c2_info)[4];
  c2_info = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_z = (real_T (*)[40])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(3), FALSE);
  for (c2_i0 = 0; c2_i0 < 4; c2_i0++) {
    c2_u[c2_i0] = (*c2_info)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  for (c2_i1 = 0; c2_i1 < 40; c2_i1++) {
    c2_b_u[c2_i1] = (*c2_z)[c2_i1];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 1, 40), FALSE);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_mpcSetpointCvxgen;
  c2_c_u = c2_hoistedGlobal;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 2, c2_d_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_mpcSetpointCvxgen
  (SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[4];
  int32_T c2_i2;
  real_T c2_dv1[40];
  int32_T c2_i3;
  real_T (*c2_info)[4];
  real_T (*c2_z)[40];
  c2_info = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_z = (real_T (*)[40])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
                        "info", c2_dv0);
  for (c2_i2 = 0; c2_i2 < 4; c2_i2++) {
    (*c2_info)[c2_i2] = c2_dv0[c2_i2];
  }

  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)), "z",
                        c2_dv1);
  for (c2_i3 = 0; c2_i3 < 40; c2_i3++) {
    (*c2_z)[c2_i3] = c2_dv1[c2_i3];
  }

  chartInstance->c2_is_active_c2_mpcSetpointCvxgen = c2_g_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 2)),
     "is_active_c2_mpcSetpointCvxgen");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_mpcSetpointCvxgen(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_mpcSetpointCvxgen(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance)
{
}

static void sf_c2_mpcSetpointCvxgen(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance)
{
  int32_T c2_i4;
  int32_T c2_i5;
  int32_T c2_i6;
  int32_T c2_i7;
  int32_T c2_i8;
  int32_T c2_i9;
  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_i12;
  int32_T c2_i13;
  int32_T c2_i14;
  int32_T c2_i15;
  int32_T c2_i16;
  int32_T c2_i17;
  int32_T c2_i18;
  int32_T c2_i19;
  int32_T c2_i20;
  int32_T c2_i21;
  int32_T c2_i22;
  int32_T c2_i23;
  real_T c2_hoistedGlobal;
  int32_T c2_i24;
  real_T c2_x[3];
  int32_T c2_i25;
  real_T c2_xt[3];
  int32_T c2_i26;
  real_T c2_A[9];
  int32_T c2_i27;
  real_T c2_B[3];
  int32_T c2_i28;
  real_T c2_d[3];
  int32_T c2_i29;
  real_T c2_Fx[12];
  int32_T c2_i30;
  real_T c2_Fu[4];
  int32_T c2_i31;
  real_T c2_f[4];
  int32_T c2_i32;
  real_T c2_Ff[6];
  int32_T c2_i33;
  real_T c2_ff[2];
  int32_T c2_i34;
  real_T c2_Q[9];
  real_T c2_R;
  int32_T c2_i35;
  real_T c2_Qf[9];
  int32_T c2_i36;
  real_T c2_Ef[6];
  int32_T c2_i37;
  real_T c2_Ed[6];
  int32_T c2_i38;
  real_T c2_ef[6];
  int32_T c2_i39;
  real_T c2_Fxs[6];
  int32_T c2_i40;
  real_T c2_Fus[2];
  int32_T c2_i41;
  real_T c2_fs[2];
  uint32_T c2_debug_family_var_map[23];
  real_T c2_nargin = 19.0;
  real_T c2_nargout = 2.0;
  real_T c2_z[40];
  real_T c2_info[4];
  int32_T c2_i42;
  int32_T c2_i43;
  int32_T c2_i44;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  int32_T c2_i45;
  real_T c2_b_u[3];
  const mxArray *c2_b_y = NULL;
  int32_T c2_i46;
  real_T c2_c_u[9];
  const mxArray *c2_c_y = NULL;
  real_T c2_d_u;
  const mxArray *c2_d_y = NULL;
  int32_T c2_i47;
  real_T c2_e_u[9];
  const mxArray *c2_e_y = NULL;
  int32_T c2_i48;
  real_T c2_f_u[9];
  const mxArray *c2_f_y = NULL;
  int32_T c2_i49;
  real_T c2_g_u[3];
  const mxArray *c2_g_y = NULL;
  int32_T c2_i50;
  real_T c2_h_u[3];
  const mxArray *c2_h_y = NULL;
  int32_T c2_i51;
  real_T c2_i_u[12];
  const mxArray *c2_i_y = NULL;
  int32_T c2_i52;
  real_T c2_j_u[4];
  const mxArray *c2_j_y = NULL;
  int32_T c2_i53;
  real_T c2_k_u[4];
  const mxArray *c2_k_y = NULL;
  int32_T c2_i54;
  real_T c2_l_u[6];
  const mxArray *c2_l_y = NULL;
  int32_T c2_i55;
  real_T c2_m_u[2];
  const mxArray *c2_m_y = NULL;
  int32_T c2_i56;
  real_T c2_n_u[2];
  const mxArray *c2_n_y = NULL;
  int32_T c2_i57;
  real_T c2_o_u[6];
  const mxArray *c2_o_y = NULL;
  int32_T c2_i58;
  real_T c2_p_u[6];
  const mxArray *c2_p_y = NULL;
  int32_T c2_i59;
  real_T c2_q_u[6];
  const mxArray *c2_q_y = NULL;
  int32_T c2_i60;
  real_T c2_r_u[6];
  const mxArray *c2_r_y = NULL;
  int32_T c2_i61;
  real_T c2_s_u[2];
  const mxArray *c2_s_y = NULL;
  const mxArray *c2_m0 = NULL;
  const mxArray *c2_m1 = NULL;
  const mxArray *c2_b_z = NULL;
  const mxArray *c2_b_info = NULL;
  real_T c2_dv2[40];
  int32_T c2_i62;
  real_T c2_dv3[4];
  int32_T c2_i63;
  int32_T c2_i64;
  int32_T c2_i65;
  real_T *c2_b_R;
  real_T (*c2_c_z)[40];
  real_T (*c2_c_info)[4];
  real_T (*c2_b_fs)[2];
  real_T (*c2_b_Fus)[2];
  real_T (*c2_b_Fxs)[6];
  real_T (*c2_b_ef)[6];
  real_T (*c2_b_Ed)[6];
  real_T (*c2_b_Ef)[6];
  real_T (*c2_b_Qf)[9];
  real_T (*c2_b_Q)[9];
  real_T (*c2_b_ff)[2];
  real_T (*c2_b_Ff)[6];
  real_T (*c2_b_f)[4];
  real_T (*c2_b_Fu)[4];
  real_T (*c2_b_Fx)[12];
  real_T (*c2_b_d)[3];
  real_T (*c2_b_B)[3];
  real_T (*c2_b_A)[9];
  real_T (*c2_b_xt)[3];
  real_T (*c2_b_x)[3];
  c2_b_fs = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 18);
  c2_c_info = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_b_Fus = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 17);
  c2_b_Fxs = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 16);
  c2_b_ef = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 15);
  c2_b_Ed = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 14);
  c2_b_Ef = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 13);
  c2_b_Qf = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 12);
  c2_b_R = (real_T *)ssGetInputPortSignal(chartInstance->S, 11);
  c2_b_Q = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 10);
  c2_b_ff = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 9);
  c2_b_Ff = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 8);
  c2_b_f = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 7);
  c2_b_Fu = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 6);
  c2_b_Fx = (real_T (*)[12])ssGetInputPortSignal(chartInstance->S, 5);
  c2_b_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c2_b_B = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c2_b_A = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 2);
  c2_c_z = (real_T (*)[40])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_xt = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c2_b_x = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i4 = 0; c2_i4 < 3; c2_i4++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_x)[c2_i4], 0U);
  }

  for (c2_i5 = 0; c2_i5 < 3; c2_i5++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_xt)[c2_i5], 1U);
  }

  for (c2_i6 = 0; c2_i6 < 40; c2_i6++) {
    _SFD_DATA_RANGE_CHECK((*c2_c_z)[c2_i6], 2U);
  }

  for (c2_i7 = 0; c2_i7 < 9; c2_i7++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_A)[c2_i7], 3U);
  }

  for (c2_i8 = 0; c2_i8 < 3; c2_i8++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_B)[c2_i8], 4U);
  }

  for (c2_i9 = 0; c2_i9 < 3; c2_i9++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_d)[c2_i9], 5U);
  }

  for (c2_i10 = 0; c2_i10 < 12; c2_i10++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_Fx)[c2_i10], 6U);
  }

  for (c2_i11 = 0; c2_i11 < 4; c2_i11++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_Fu)[c2_i11], 7U);
  }

  for (c2_i12 = 0; c2_i12 < 4; c2_i12++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_f)[c2_i12], 8U);
  }

  for (c2_i13 = 0; c2_i13 < 6; c2_i13++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_Ff)[c2_i13], 9U);
  }

  for (c2_i14 = 0; c2_i14 < 2; c2_i14++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_ff)[c2_i14], 10U);
  }

  for (c2_i15 = 0; c2_i15 < 9; c2_i15++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_Q)[c2_i15], 11U);
  }

  _SFD_DATA_RANGE_CHECK(*c2_b_R, 12U);
  for (c2_i16 = 0; c2_i16 < 9; c2_i16++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_Qf)[c2_i16], 13U);
  }

  for (c2_i17 = 0; c2_i17 < 6; c2_i17++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_Ef)[c2_i17], 14U);
  }

  for (c2_i18 = 0; c2_i18 < 6; c2_i18++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_Ed)[c2_i18], 15U);
  }

  for (c2_i19 = 0; c2_i19 < 6; c2_i19++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_ef)[c2_i19], 16U);
  }

  for (c2_i20 = 0; c2_i20 < 6; c2_i20++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_Fxs)[c2_i20], 17U);
  }

  for (c2_i21 = 0; c2_i21 < 2; c2_i21++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_Fus)[c2_i21], 18U);
  }

  for (c2_i22 = 0; c2_i22 < 4; c2_i22++) {
    _SFD_DATA_RANGE_CHECK((*c2_c_info)[c2_i22], 19U);
  }

  for (c2_i23 = 0; c2_i23 < 2; c2_i23++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_fs)[c2_i23], 20U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *c2_b_R;
  for (c2_i24 = 0; c2_i24 < 3; c2_i24++) {
    c2_x[c2_i24] = (*c2_b_x)[c2_i24];
  }

  for (c2_i25 = 0; c2_i25 < 3; c2_i25++) {
    c2_xt[c2_i25] = (*c2_b_xt)[c2_i25];
  }

  for (c2_i26 = 0; c2_i26 < 9; c2_i26++) {
    c2_A[c2_i26] = (*c2_b_A)[c2_i26];
  }

  for (c2_i27 = 0; c2_i27 < 3; c2_i27++) {
    c2_B[c2_i27] = (*c2_b_B)[c2_i27];
  }

  for (c2_i28 = 0; c2_i28 < 3; c2_i28++) {
    c2_d[c2_i28] = (*c2_b_d)[c2_i28];
  }

  for (c2_i29 = 0; c2_i29 < 12; c2_i29++) {
    c2_Fx[c2_i29] = (*c2_b_Fx)[c2_i29];
  }

  for (c2_i30 = 0; c2_i30 < 4; c2_i30++) {
    c2_Fu[c2_i30] = (*c2_b_Fu)[c2_i30];
  }

  for (c2_i31 = 0; c2_i31 < 4; c2_i31++) {
    c2_f[c2_i31] = (*c2_b_f)[c2_i31];
  }

  for (c2_i32 = 0; c2_i32 < 6; c2_i32++) {
    c2_Ff[c2_i32] = (*c2_b_Ff)[c2_i32];
  }

  for (c2_i33 = 0; c2_i33 < 2; c2_i33++) {
    c2_ff[c2_i33] = (*c2_b_ff)[c2_i33];
  }

  for (c2_i34 = 0; c2_i34 < 9; c2_i34++) {
    c2_Q[c2_i34] = (*c2_b_Q)[c2_i34];
  }

  c2_R = c2_hoistedGlobal;
  for (c2_i35 = 0; c2_i35 < 9; c2_i35++) {
    c2_Qf[c2_i35] = (*c2_b_Qf)[c2_i35];
  }

  for (c2_i36 = 0; c2_i36 < 6; c2_i36++) {
    c2_Ef[c2_i36] = (*c2_b_Ef)[c2_i36];
  }

  for (c2_i37 = 0; c2_i37 < 6; c2_i37++) {
    c2_Ed[c2_i37] = (*c2_b_Ed)[c2_i37];
  }

  for (c2_i38 = 0; c2_i38 < 6; c2_i38++) {
    c2_ef[c2_i38] = (*c2_b_ef)[c2_i38];
  }

  for (c2_i39 = 0; c2_i39 < 6; c2_i39++) {
    c2_Fxs[c2_i39] = (*c2_b_Fxs)[c2_i39];
  }

  for (c2_i40 = 0; c2_i40 < 2; c2_i40++) {
    c2_Fus[c2_i40] = (*c2_b_Fus)[c2_i40];
  }

  for (c2_i41 = 0; c2_i41 < 2; c2_i41++) {
    c2_fs[c2_i41] = (*c2_b_fs)[c2_i41];
  }

  sf_debug_symbol_scope_push_eml(0U, 23U, 23U, c2_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 0U, c2_g_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 1U, c2_g_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c2_x, 2U, c2_i_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_xt, 3U, c2_i_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_A, 4U, c2_f_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_B, 5U, c2_i_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_d, 6U, c2_i_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Fx, 7U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Fu, 8U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_f, 9U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Ff, 10U, c2_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_ff, 11U, c2_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Q, 12U, c2_f_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_R, 13U, c2_g_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Qf, 14U, c2_f_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Ef, 15U, c2_e_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Ed, 16U, c2_e_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_ef, 17U, c2_e_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Fxs, 18U, c2_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Fus, 19U, c2_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_fs, 20U, c2_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_z, 21U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_info, 22U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 5);
  for (c2_i42 = 0; c2_i42 < 40; c2_i42++) {
    c2_z[c2_i42] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  for (c2_i43 = 0; c2_i43 < 4; c2_i43++) {
    c2_info[c2_i43] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
  for (c2_i44 = 0; c2_i44 < 3; c2_i44++) {
    c2_u[c2_i44] = c2_x[c2_i44];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  for (c2_i45 = 0; c2_i45 < 3; c2_i45++) {
    c2_b_u[c2_i45] = c2_xt[c2_i45];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  for (c2_i46 = 0; c2_i46 < 9; c2_i46++) {
    c2_c_u[c2_i46] = c2_Q[c2_i46];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 2, 3, 3),
                FALSE);
  c2_d_u = c2_R;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  for (c2_i47 = 0; c2_i47 < 9; c2_i47++) {
    c2_e_u[c2_i47] = c2_Qf[c2_i47];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 3, 3),
                FALSE);
  for (c2_i48 = 0; c2_i48 < 9; c2_i48++) {
    c2_f_u[c2_i48] = c2_A[c2_i48];
  }

  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_f_u, 0, 0U, 1U, 0U, 2, 3, 3),
                FALSE);
  for (c2_i49 = 0; c2_i49 < 3; c2_i49++) {
    c2_g_u[c2_i49] = c2_B[c2_i49];
  }

  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", c2_g_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  for (c2_i50 = 0; c2_i50 < 3; c2_i50++) {
    c2_h_u[c2_i50] = c2_d[c2_i50];
  }

  c2_h_y = NULL;
  sf_mex_assign(&c2_h_y, sf_mex_create("y", c2_h_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  for (c2_i51 = 0; c2_i51 < 12; c2_i51++) {
    c2_i_u[c2_i51] = c2_Fx[c2_i51];
  }

  c2_i_y = NULL;
  sf_mex_assign(&c2_i_y, sf_mex_create("y", c2_i_u, 0, 0U, 1U, 0U, 2, 4, 3),
                FALSE);
  for (c2_i52 = 0; c2_i52 < 4; c2_i52++) {
    c2_j_u[c2_i52] = c2_Fu[c2_i52];
  }

  c2_j_y = NULL;
  sf_mex_assign(&c2_j_y, sf_mex_create("y", c2_j_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  for (c2_i53 = 0; c2_i53 < 4; c2_i53++) {
    c2_k_u[c2_i53] = c2_f[c2_i53];
  }

  c2_k_y = NULL;
  sf_mex_assign(&c2_k_y, sf_mex_create("y", c2_k_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  for (c2_i54 = 0; c2_i54 < 6; c2_i54++) {
    c2_l_u[c2_i54] = c2_Fxs[c2_i54];
  }

  c2_l_y = NULL;
  sf_mex_assign(&c2_l_y, sf_mex_create("y", c2_l_u, 0, 0U, 1U, 0U, 2, 2, 3),
                FALSE);
  for (c2_i55 = 0; c2_i55 < 2; c2_i55++) {
    c2_m_u[c2_i55] = c2_Fus[c2_i55];
  }

  c2_m_y = NULL;
  sf_mex_assign(&c2_m_y, sf_mex_create("y", c2_m_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  for (c2_i56 = 0; c2_i56 < 2; c2_i56++) {
    c2_n_u[c2_i56] = c2_fs[c2_i56];
  }

  c2_n_y = NULL;
  sf_mex_assign(&c2_n_y, sf_mex_create("y", c2_n_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  for (c2_i57 = 0; c2_i57 < 6; c2_i57++) {
    c2_o_u[c2_i57] = c2_Ef[c2_i57];
  }

  c2_o_y = NULL;
  sf_mex_assign(&c2_o_y, sf_mex_create("y", c2_o_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  for (c2_i58 = 0; c2_i58 < 6; c2_i58++) {
    c2_p_u[c2_i58] = c2_Ed[c2_i58];
  }

  c2_p_y = NULL;
  sf_mex_assign(&c2_p_y, sf_mex_create("y", c2_p_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  for (c2_i59 = 0; c2_i59 < 6; c2_i59++) {
    c2_q_u[c2_i59] = c2_ef[c2_i59];
  }

  c2_q_y = NULL;
  sf_mex_assign(&c2_q_y, sf_mex_create("y", c2_q_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  for (c2_i60 = 0; c2_i60 < 6; c2_i60++) {
    c2_r_u[c2_i60] = c2_Ff[c2_i60];
  }

  c2_r_y = NULL;
  sf_mex_assign(&c2_r_y, sf_mex_create("y", c2_r_u, 0, 0U, 1U, 0U, 2, 2, 3),
                FALSE);
  for (c2_i61 = 0; c2_i61 < 2; c2_i61++) {
    c2_s_u[c2_i61] = c2_ff[c2_i61];
  }

  c2_s_y = NULL;
  sf_mex_assign(&c2_s_y, sf_mex_create("y", c2_s_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_call_debug("cvxgenPointMassSolve", 2U, 19U, 14, c2_y, 14, c2_b_y, 14,
                    c2_c_y, 14, c2_d_y, 14, c2_e_y, 14, c2_f_y, 14, c2_g_y, 14,
                    c2_h_y, 14, c2_i_y, 14, c2_j_y, 14, c2_k_y, 14, c2_l_y, 14,
                    c2_m_y, 14, c2_n_y, 14, c2_o_y, 14, c2_p_y, 14, c2_q_y, 14,
                    c2_r_y, 14, c2_s_y, &c2_m1, &c2_m0);
  sf_mex_assign(&c2_b_z, sf_mex_dup(c2_m1), FALSE);
  sf_mex_assign(&c2_b_info, sf_mex_dup(c2_m0), FALSE);
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_z), "z", c2_dv2);
  for (c2_i62 = 0; c2_i62 < 40; c2_i62++) {
    c2_z[c2_i62] = c2_dv2[c2_i62];
  }

  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_info), "info", c2_dv3);
  for (c2_i63 = 0; c2_i63 < 4; c2_i63++) {
    c2_info[c2_i63] = c2_dv3[c2_i63];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -9);
  sf_debug_symbol_scope_pop();
  sf_mex_destroy(&c2_b_z);
  sf_mex_destroy(&c2_b_info);
  sf_mex_destroy(&c2_m0);
  sf_mex_destroy(&c2_m1);
  for (c2_i64 = 0; c2_i64 < 40; c2_i64++) {
    (*c2_c_z)[c2_i64] = c2_z[c2_i64];
  }

  for (c2_i65 = 0; c2_i65 < 4; c2_i65++) {
    (*c2_c_info)[c2_i65] = c2_info[c2_i65];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  sf_debug_check_for_state_inconsistency(_mpcSetpointCvxgenMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc2_mpcSetpointCvxgen
  (SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i66;
  real_T c2_b_inData[4];
  int32_T c2_i67;
  real_T c2_u[4];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i66 = 0; c2_i66 < 4; c2_i66++) {
    c2_b_inData[c2_i66] = (*(real_T (*)[4])c2_inData)[c2_i66];
  }

  for (c2_i67 = 0; c2_i67 < 4; c2_i67++) {
    c2_u[c2_i67] = c2_b_inData[c2_i67];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_info;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[4];
  int32_T c2_i68;
  SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *)chartInstanceVoid;
  c2_info = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_info), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_info);
  for (c2_i68 = 0; c2_i68 < 4; c2_i68++) {
    (*(real_T (*)[4])c2_outData)[c2_i68] = c2_y[c2_i68];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i69;
  real_T c2_b_inData[40];
  int32_T c2_i70;
  real_T c2_u[40];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i69 = 0; c2_i69 < 40; c2_i69++) {
    c2_b_inData[c2_i69] = (*(real_T (*)[40])c2_inData)[c2_i69];
  }

  for (c2_i70 = 0; c2_i70 < 40; c2_i70++) {
    c2_u[c2_i70] = c2_b_inData[c2_i70];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 40), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_z;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[40];
  int32_T c2_i71;
  SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *)chartInstanceVoid;
  c2_z = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_z), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_z);
  for (c2_i71 = 0; c2_i71 < 40; c2_i71++) {
    (*(real_T (*)[40])c2_outData)[c2_i71] = c2_y[c2_i71];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i72;
  real_T c2_b_inData[2];
  int32_T c2_i73;
  real_T c2_u[2];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i72 = 0; c2_i72 < 2; c2_i72++) {
    c2_b_inData[c2_i72] = (*(real_T (*)[2])c2_inData)[c2_i72];
  }

  for (c2_i73 = 0; c2_i73 < 2; c2_i73++) {
    c2_u[c2_i73] = c2_b_inData[c2_i73];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i74;
  int32_T c2_i75;
  int32_T c2_i76;
  real_T c2_b_inData[6];
  int32_T c2_i77;
  int32_T c2_i78;
  int32_T c2_i79;
  real_T c2_u[6];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i74 = 0;
  for (c2_i75 = 0; c2_i75 < 3; c2_i75++) {
    for (c2_i76 = 0; c2_i76 < 2; c2_i76++) {
      c2_b_inData[c2_i76 + c2_i74] = (*(real_T (*)[6])c2_inData)[c2_i76 + c2_i74];
    }

    c2_i74 += 2;
  }

  c2_i77 = 0;
  for (c2_i78 = 0; c2_i78 < 3; c2_i78++) {
    for (c2_i79 = 0; c2_i79 < 2; c2_i79++) {
      c2_u[c2_i79 + c2_i77] = c2_b_inData[c2_i79 + c2_i77];
    }

    c2_i77 += 2;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 2, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i80;
  real_T c2_b_inData[6];
  int32_T c2_i81;
  real_T c2_u[6];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i80 = 0; c2_i80 < 6; c2_i80++) {
    c2_b_inData[c2_i80] = (*(real_T (*)[6])c2_inData)[c2_i80];
  }

  for (c2_i81 = 0; c2_i81 < 6; c2_i81++) {
    c2_u[c2_i81] = c2_b_inData[c2_i81];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i82;
  int32_T c2_i83;
  int32_T c2_i84;
  real_T c2_b_inData[9];
  int32_T c2_i85;
  int32_T c2_i86;
  int32_T c2_i87;
  real_T c2_u[9];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i82 = 0;
  for (c2_i83 = 0; c2_i83 < 3; c2_i83++) {
    for (c2_i84 = 0; c2_i84 < 3; c2_i84++) {
      c2_b_inData[c2_i84 + c2_i82] = (*(real_T (*)[9])c2_inData)[c2_i84 + c2_i82];
    }

    c2_i82 += 3;
  }

  c2_i85 = 0;
  for (c2_i86 = 0; c2_i86 < 3; c2_i86++) {
    for (c2_i87 = 0; c2_i87 < 3; c2_i87++) {
      c2_u[c2_i87 + c2_i85] = c2_b_inData[c2_i87 + c2_i85];
    }

    c2_i85 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i88;
  int32_T c2_i89;
  int32_T c2_i90;
  real_T c2_b_inData[12];
  int32_T c2_i91;
  int32_T c2_i92;
  int32_T c2_i93;
  real_T c2_u[12];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i88 = 0;
  for (c2_i89 = 0; c2_i89 < 3; c2_i89++) {
    for (c2_i90 = 0; c2_i90 < 4; c2_i90++) {
      c2_b_inData[c2_i90 + c2_i88] = (*(real_T (*)[12])c2_inData)[c2_i90 +
        c2_i88];
    }

    c2_i88 += 4;
  }

  c2_i91 = 0;
  for (c2_i92 = 0; c2_i92 < 3; c2_i92++) {
    for (c2_i93 = 0; c2_i93 < 4; c2_i93++) {
      c2_u[c2_i93 + c2_i91] = c2_b_inData[c2_i93 + c2_i91];
    }

    c2_i91 += 4;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 4, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i94;
  real_T c2_b_inData[3];
  int32_T c2_i95;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i94 = 0; c2_i94 < 3; c2_i94++) {
    c2_b_inData[c2_i94] = (*(real_T (*)[3])c2_inData)[c2_i94];
  }

  for (c2_i95 = 0; c2_i95 < 3; c2_i95++) {
    c2_u[c2_i95] = c2_b_inData[c2_i95];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_mpcSetpointCvxgen_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), FALSE);
  return c2_nameCaptureInfo;
}

static void c2_b_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_z, const char_T *c2_identifier, real_T c2_y
  [40])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_z), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_z);
}

static void c2_c_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[40])
{
  real_T c2_dv4[40];
  int32_T c2_i96;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv4, 1, 0, 0U, 1, 0U, 1, 40);
  for (c2_i96 = 0; c2_i96 < 40; c2_i96++) {
    c2_y[c2_i96] = c2_dv4[c2_i96];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_info, const char_T *c2_identifier, real_T
  c2_y[4])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_info), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_info);
}

static void c2_e_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[4])
{
  real_T c2_dv5[4];
  int32_T c2_i97;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv5, 1, 0, 0U, 1, 0U, 1, 4);
  for (c2_i97 = 0; c2_i97 < 4; c2_i97++) {
    c2_y[c2_i97] = c2_dv5[c2_i97];
  }

  sf_mex_destroy(&c2_u);
}

static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_f_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i98;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i98, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i98;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_g_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_mpcSetpointCvxgen, const
  char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_mpcSetpointCvxgen), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_mpcSetpointCvxgen);
  return c2_y;
}

static uint8_T c2_h_emlrt_marshallIn(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_mpcSetpointCvxgenInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_mpcSetpointCvxgen_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2442567288U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2936861315U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2642235341U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1671665330U);
}

mxArray *sf_c2_mpcSetpointCvxgen_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("lQV3CeYat1UIdSjKaUmrjB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,19,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(3);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(3);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,11,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,11,"type",mxType);
    }

    mxSetField(mxData,11,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,13,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,13,"type",mxType);
    }

    mxSetField(mxData,13,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,14,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,14,"type",mxType);
    }

    mxSetField(mxData,14,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,15,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,15,"type",mxType);
    }

    mxSetField(mxData,15,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(3);
      mxSetField(mxData,16,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,16,"type",mxType);
    }

    mxSetField(mxData,16,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,17,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,17,"type",mxType);
    }

    mxSetField(mxData,17,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,18,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,18,"type",mxType);
    }

    mxSetField(mxData,18,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(40);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c2_mpcSetpointCvxgen(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[21],T\"info\",},{M[1],M[5],T\"z\",},{M[8],M[0],T\"is_active_c2_mpcSetpointCvxgen\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_mpcSetpointCvxgen_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
    chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_mpcSetpointCvxgenMachineNumber_,
           2,
           1,
           1,
           21,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_mpcSetpointCvxgenMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (_mpcSetpointCvxgenMachineNumber_,chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_mpcSetpointCvxgenMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"x");
          _SFD_SET_DATA_PROPS(1,1,1,0,"xt");
          _SFD_SET_DATA_PROPS(2,2,0,1,"z");
          _SFD_SET_DATA_PROPS(3,1,1,0,"A");
          _SFD_SET_DATA_PROPS(4,1,1,0,"B");
          _SFD_SET_DATA_PROPS(5,1,1,0,"d");
          _SFD_SET_DATA_PROPS(6,1,1,0,"Fx");
          _SFD_SET_DATA_PROPS(7,1,1,0,"Fu");
          _SFD_SET_DATA_PROPS(8,1,1,0,"f");
          _SFD_SET_DATA_PROPS(9,1,1,0,"Ff");
          _SFD_SET_DATA_PROPS(10,1,1,0,"ff");
          _SFD_SET_DATA_PROPS(11,1,1,0,"Q");
          _SFD_SET_DATA_PROPS(12,1,1,0,"R");
          _SFD_SET_DATA_PROPS(13,1,1,0,"Qf");
          _SFD_SET_DATA_PROPS(14,1,1,0,"Ef");
          _SFD_SET_DATA_PROPS(15,1,1,0,"Ed");
          _SFD_SET_DATA_PROPS(16,1,1,0,"ef");
          _SFD_SET_DATA_PROPS(17,1,1,0,"Fxs");
          _SFD_SET_DATA_PROPS(18,1,1,0,"Fus");
          _SFD_SET_DATA_PROPS(19,2,0,1,"info");
          _SFD_SET_DATA_PROPS(20,1,1,0,"fs");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,296);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_i_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_i_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 40;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_i_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_i_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_h_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_g_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(16,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(17,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(18,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(19,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(20,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T *c2_R;
          real_T (*c2_x)[3];
          real_T (*c2_xt)[3];
          real_T (*c2_z)[40];
          real_T (*c2_A)[9];
          real_T (*c2_B)[3];
          real_T (*c2_d)[3];
          real_T (*c2_Fx)[12];
          real_T (*c2_Fu)[4];
          real_T (*c2_f)[4];
          real_T (*c2_Ff)[6];
          real_T (*c2_ff)[2];
          real_T (*c2_Q)[9];
          real_T (*c2_Qf)[9];
          real_T (*c2_Ef)[6];
          real_T (*c2_Ed)[6];
          real_T (*c2_ef)[6];
          real_T (*c2_Fxs)[6];
          real_T (*c2_Fus)[2];
          real_T (*c2_info)[4];
          real_T (*c2_fs)[2];
          c2_fs = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 18);
          c2_info = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
          c2_Fus = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 17);
          c2_Fxs = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 16);
          c2_ef = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 15);
          c2_Ed = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 14);
          c2_Ef = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 13);
          c2_Qf = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 12);
          c2_R = (real_T *)ssGetInputPortSignal(chartInstance->S, 11);
          c2_Q = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 10);
          c2_ff = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 9);
          c2_Ff = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 8);
          c2_f = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 7);
          c2_Fu = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 6);
          c2_Fx = (real_T (*)[12])ssGetInputPortSignal(chartInstance->S, 5);
          c2_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
          c2_B = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
          c2_A = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 2);
          c2_z = (real_T (*)[40])ssGetOutputPortSignal(chartInstance->S, 1);
          c2_xt = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c2_x = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_x);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_xt);
          _SFD_SET_DATA_VALUE_PTR(2U, *c2_z);
          _SFD_SET_DATA_VALUE_PTR(3U, *c2_A);
          _SFD_SET_DATA_VALUE_PTR(4U, *c2_B);
          _SFD_SET_DATA_VALUE_PTR(5U, *c2_d);
          _SFD_SET_DATA_VALUE_PTR(6U, *c2_Fx);
          _SFD_SET_DATA_VALUE_PTR(7U, *c2_Fu);
          _SFD_SET_DATA_VALUE_PTR(8U, *c2_f);
          _SFD_SET_DATA_VALUE_PTR(9U, *c2_Ff);
          _SFD_SET_DATA_VALUE_PTR(10U, *c2_ff);
          _SFD_SET_DATA_VALUE_PTR(11U, *c2_Q);
          _SFD_SET_DATA_VALUE_PTR(12U, c2_R);
          _SFD_SET_DATA_VALUE_PTR(13U, *c2_Qf);
          _SFD_SET_DATA_VALUE_PTR(14U, *c2_Ef);
          _SFD_SET_DATA_VALUE_PTR(15U, *c2_Ed);
          _SFD_SET_DATA_VALUE_PTR(16U, *c2_ef);
          _SFD_SET_DATA_VALUE_PTR(17U, *c2_Fxs);
          _SFD_SET_DATA_VALUE_PTR(18U, *c2_Fus);
          _SFD_SET_DATA_VALUE_PTR(19U, *c2_info);
          _SFD_SET_DATA_VALUE_PTR(20U, *c2_fs);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration
        (_mpcSetpointCvxgenMachineNumber_,chartInstance->chartNumber,
         chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization()
{
  return "Xr8rVksnpPU5DJqlTwAQVB";
}

static void sf_opaque_initialize_c2_mpcSetpointCvxgen(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_mpcSetpointCvxgenInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_mpcSetpointCvxgen((SFc2_mpcSetpointCvxgenInstanceStruct*)
    chartInstanceVar);
  initialize_c2_mpcSetpointCvxgen((SFc2_mpcSetpointCvxgenInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_mpcSetpointCvxgen(void *chartInstanceVar)
{
  enable_c2_mpcSetpointCvxgen((SFc2_mpcSetpointCvxgenInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c2_mpcSetpointCvxgen(void *chartInstanceVar)
{
  disable_c2_mpcSetpointCvxgen((SFc2_mpcSetpointCvxgenInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_mpcSetpointCvxgen(void *chartInstanceVar)
{
  sf_c2_mpcSetpointCvxgen((SFc2_mpcSetpointCvxgenInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_mpcSetpointCvxgen(SimStruct*
  S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_mpcSetpointCvxgen
    ((SFc2_mpcSetpointCvxgenInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_mpcSetpointCvxgen();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c2_mpcSetpointCvxgen(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_mpcSetpointCvxgen();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_mpcSetpointCvxgen((SFc2_mpcSetpointCvxgenInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_mpcSetpointCvxgen(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_mpcSetpointCvxgen(S);
}

static void sf_opaque_set_sim_state_c2_mpcSetpointCvxgen(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c2_mpcSetpointCvxgen(S, st);
}

static void sf_opaque_terminate_c2_mpcSetpointCvxgen(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_mpcSetpointCvxgenInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_mpcSetpointCvxgen((SFc2_mpcSetpointCvxgenInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_mpcSetpointCvxgen_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_mpcSetpointCvxgen((SFc2_mpcSetpointCvxgenInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_mpcSetpointCvxgen(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_mpcSetpointCvxgen((SFc2_mpcSetpointCvxgenInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_mpcSetpointCvxgen(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_mpcSetpointCvxgen_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,2,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 10, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 11, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 12, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 13, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 14, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 15, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 16, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 17, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 18, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,19);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,2);
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3101483911U));
  ssSetChecksum1(S,(1558898712U));
  ssSetChecksum2(S,(1669594998U));
  ssSetChecksum3(S,(458567527U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_mpcSetpointCvxgen(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_mpcSetpointCvxgen(SimStruct *S)
{
  SFc2_mpcSetpointCvxgenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointCvxgenInstanceStruct *)malloc(sizeof
    (SFc2_mpcSetpointCvxgenInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_mpcSetpointCvxgenInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_mpcSetpointCvxgen;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_mpcSetpointCvxgen;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_mpcSetpointCvxgen;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_mpcSetpointCvxgen;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_mpcSetpointCvxgen;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_mpcSetpointCvxgen;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_mpcSetpointCvxgen;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_mpcSetpointCvxgen;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_mpcSetpointCvxgen;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_mpcSetpointCvxgen;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_mpcSetpointCvxgen;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_mpcSetpointCvxgen_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_mpcSetpointCvxgen(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_mpcSetpointCvxgen(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_mpcSetpointCvxgen(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_mpcSetpointCvxgen_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
