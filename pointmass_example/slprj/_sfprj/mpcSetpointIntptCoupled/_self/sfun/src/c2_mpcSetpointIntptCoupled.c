/* Include files */

#include "blascompat32.h"
#include "mpcSetpointIntptCoupled_sfun.h"
#include "c2_mpcSetpointIntptCoupled.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "mpcSetpointIntptCoupled_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[112] = { "check_d", "checkRp",
  "checkPhiInv", "checkY", "checkBeta", "checkL", "check_t", "check_dnu",
  "checkNewton", "checkInv", "totBackTracks", "n", "m", "nz", "ne", "ni", "ns",
  "ell", "ellf", "ellef", "T", "ells", "kappa", "rho", "numBarrIters", "nop",
  "flagPhiIsDiag", "numNewtonIters", "flagUseSoftCons", "flagChecking",
  "flagNoPade", "switches", "kappaPt", "kappaPtSq", "rhoPstSq", "diagTwoH",
  "blkQR", "FxsT", "FusT", "AT", "BT", "CT", "EfT", "PsT", "es", "ds", "dsNew",
  "esNew", "dz", "phi", "dhats", "zTail", "initSolChoice", "nu", "d", "rp",
  "rpMag", "rd", "checkPsT", "rdMag", "rMag", "diagPhi", "phiInv", "blkInv", "Y",
  "tmp", "PhiInvRd", "rhs", "L", "t", "dnu", "v", "checkV", "sMax", "zFar",
  "iFar", "s", "zNew", "nuNew", "iNew", "dNew", "rdNew", "rpNew", "rdMagNew",
  "rpMagNew", "rMagNew", "gradRmag", "nargin", "nargout", "H", "g", "P", "h",
  "C", "b", "z0", "A", "B", "Fx", "Fu", "Ff", "Q", "R", "Qf", "opts", "Ps", "hs",
  "Ef", "Fxs", "Fus", "z", "info" };

static const char * c2_b_debug_family_names[7] = { "n", "nargin", "nargout", "M",
  "A", "switches", "y" };

static const char * c2_c_debug_family_names[14] = { "T", "n", "m", "ell", "ellf",
  "nargin", "nargout", "z", "P", "Fx", "Fu", "Ff", "switches", "y" };

static const char * c2_d_debug_family_names[13] = { "T", "n", "m", "ellef",
  "nargin", "nargout", "z", "A", "B", "C", "Ef", "switches", "y" };

static const char * c2_e_debug_family_names[14] = { "T", "n", "m", "ellef",
  "nargin", "nargout", "z", "b", "A", "B", "C", "Ef", "switches", "rp" };

static const char * c2_f_debug_family_names[13] = { "T", "n", "m", "ellef",
  "nargin", "nargout", "nu", "CT", "AT", "BT", "EfT", "switches", "y" };

static const char * c2_g_debug_family_names[12] = { "T", "n", "m", "ells",
  "nargin", "nargout", "z", "Ps", "Fxs", "Fus", "switches", "y" };

static const char * c2_h_debug_family_names[7] = { "di", "ds", "nargin",
  "nargout", "u", "flagNoPade", "y" };

static const char * c2_i_debug_family_names[18] = { "rs", "checkPs", "T", "n",
  "m", "ells", "rho", "nargin", "nargout", "z", "Ps", "Fxs", "Fus", "hs",
  "flagNoPade", "switches", "ds", "es" };

static const char * c2_j_debug_family_names[12] = { "T", "n", "m", "ells",
  "nargin", "nargout", "ds", "PsT", "FxsT", "FusT", "switches", "y" };

static const char * c2_k_debug_family_names[6] = { "cholM", "tmp", "nargin",
  "nargout", "M", "Minv" };

static const char * c2_l_debug_family_names[6] = { "cholM", "tmp", "nargin",
  "nargout", "M", "Minv" };

static const char * c2_m_debug_family_names[6] = { "cholM", "tmp", "nargin",
  "nargout", "M", "Minv" };

static const char * c2_n_debug_family_names[7] = { "ii", "n", "m", "nargin",
  "nargout", "phiInv", "Rt" };

static const char * c2_o_debug_family_names[7] = { "ii", "n", "m", "nargin",
  "nargout", "phiInv", "Qt" };

static const char * c2_p_debug_family_names[7] = { "n", "m", "nargin", "nargout",
  "phiInv", "ii", "Qt" };

static const char * c2_q_debug_family_names[7] = { "n", "nargin", "nargout", "M",
  "AT", "switches", "y" };

static const char * c2_r_debug_family_names[7] = { "n", "m", "nargin", "nargout",
  "phiInv", "ii", "St" };

static const char * c2_s_debug_family_names[7] = { "n", "nargin", "nargout", "M",
  "A", "switches", "y" };

static const char * c2_t_debug_family_names[7] = { "n", "m", "nargin", "nargout",
  "phiInv", "ii", "Rt" };

static const char * c2_u_debug_family_names[7] = { "ii", "jj", "n", "nargin",
  "nargout", "U", "Y" };

static const char * c2_v_debug_family_names[7] = { "n", "nargin", "nargout", "U",
  "ii", "jj", "Y" };

static const char * c2_w_debug_family_names[18] = { "rs", "checkPs", "T", "n",
  "m", "ells", "nargin", "nargout", "z", "Ps", "Fxs", "Fus", "hs", "rho",
  "flagNoPade", "switches", "ds", "es" };

/* Function Declarations */
static void initialize_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void initialize_params_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void enable_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void disable_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void set_sim_state_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, const mxArray
   *c2_st);
static void finalize_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void sf_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void c2_chartstep_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void initSimStructsc2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_info, const char_T *c2_identifier, real_T
  c2_y[4]);
static void c2_b_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[4]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_c_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_z, const char_T *c2_identifier, real_T c2_y
  [40]);
static void c2_d_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[40]);
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
static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_l_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_m_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_e_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_f_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[32]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_g_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[44]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_n_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_h_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[1024]);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_i_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[9]);
static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_o_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_j_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[16]);
static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_k_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[1600]);
static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_p_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_l_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[6]);
static void c2_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_q_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_m_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[1280]);
static void c2_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_r_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_n_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3]);
static void c2_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_s_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_o_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[4]);
static void c2_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_t_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_p_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[12]);
static void c2_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_u_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_q_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[1760]);
static void c2_o_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_v_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_r_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[9]);
static void c2_p_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_w_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static boolean_T c2_s_emlrt_marshallIn
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, const mxArray
   *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_q_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_t_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3]);
static void c2_r_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_u_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[12]);
static void c2_s_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_v_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[1760]);
static void c2_t_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_w_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[6]);
static void c2_u_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_x_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[1280]);
static void c2_v_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[276]);
static void c2_b_info_helper(c2_ResolvedFunctionInfo c2_info[276]);
static void c2_c_info_helper(c2_ResolvedFunctionInfo c2_info[276]);
static void c2_d_info_helper(c2_ResolvedFunctionInfo c2_info[276]);
static void c2_e_info_helper(c2_ResolvedFunctionInfo c2_info[276]);
static real_T c2_eml_div(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x, real_T c2_y);
static void c2_diag(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                    real_T c2_v[1600], real_T c2_d[40]);
static real_T c2_abs(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                     real_T c2_x);
static void c2_eml_realmin(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_realmax(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void c2_preMultByA(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_M[3], real_T c2_A[9], real_T c2_switches[9], real_T
  c2_y[3]);
static void c2_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_b_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[40], real_T c2_C[44], real_T
  c2_b_C[44]);
static boolean_T c2_all(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, boolean_T c2_x[44]);
static void c2_multByP(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
  real_T c2_z[40], real_T c2_P[1760], real_T c2_Fx[12], real_T c2_Fu[4], real_T
  c2_Ff[12], real_T c2_switches[9], real_T c2_y[44]);
static void c2_c_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_rdivide(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
  real_T c2_x, real_T c2_y[44], real_T c2_z[44]);
static void c2_d_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_b_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[40], real_T c2_C[32], real_T
  c2_b_C[32]);
static void c2_calcRp(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_z[40], real_T c2_b[32], real_T c2_A[9], real_T
                      c2_B[3], real_T c2_C[1280], real_T c2_Ef[6], real_T
                      c2_switches[9], real_T c2_rp[32]);
static void c2_multByC(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
  real_T c2_z[40], real_T c2_A[9], real_T c2_B[3], real_T c2_C[1280], real_T
  c2_Ef[6], real_T c2_switches[9], real_T c2_y[32]);
static void c2_e_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static real_T c2_norm(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_x[32]);
static void c2_realmin(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void c2_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void c2_f_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_c_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[44], real_T c2_C[40], real_T
  c2_b_C[40]);
static void c2_g_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_d_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[32], real_T c2_C[40], real_T
  c2_b_C[40]);
static void c2_multByCT(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_nu[32], real_T c2_CT[1280], real_T c2_AT[9], real_T
  c2_BT[3], real_T c2_EfT[6], real_T c2_switches[9], real_T c2_y[40]);
static void c2_h_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_b_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void c2_i_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_j_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_e_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1600], real_T c2_B[40], real_T c2_C[40], real_T
  c2_b_C[40]);
static void c2_calcDs(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_z[40], real_T c2_Ps[1600], real_T c2_Fxs[12],
                      real_T c2_Fus[4], real_T c2_hs[40], boolean_T
                      c2_flagNoPade, real_T c2_switches[9], real_T c2_ds[40],
                      real_T c2_es[40]);
static void c2_multByPs(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_z[40], real_T c2_Ps[1600], real_T c2_Fxs[12], real_T
  c2_Fus[4], real_T c2_switches[9], real_T c2_y[40]);
static real_T c2_myexp(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
  real_T c2_u, boolean_T c2_flagNoPade);
static void c2_multByPsT(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_ds[40], real_T c2_PsT[1600], real_T c2_FxsT[12],
  real_T c2_FusT[4], real_T c2_switches[9], real_T c2_y[40]);
static void c2_k_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_c_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void c2_l_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static real_T c2_b_norm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x[40]);
static void c2_d_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static real_T c2_c_norm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x[2]);
static void c2_e_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static real_T c2_d_norm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x[44]);
static void c2_f_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void c2_b_rdivide(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x[40], real_T c2_y[40], real_T c2_z[40]);
static void c2_c_rdivide(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x, real_T c2_y[40], real_T c2_z[40]);
static void c2_b_diag(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_v[40], real_T c2_d[1600]);
static void c2_c_diag(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_v[4], real_T c2_d[16]);
static void c2_m_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static real_T c2_mySymPDinv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_M);
static real_T c2_chol(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_A);
static void c2_eml_error(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_n_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_b_eml_error(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_g_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, int32_T c2_b);
static void c2_h_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, int32_T c2_b);
static void c2_isVariableSizing(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_below_threshold(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static boolean_T c2_is_singular_triangular_matrix
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, real_T c2_A);
static void c2_eml_warning(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_o_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_b_mySymPDinv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_M[16], real_T c2_Minv[16]);
static void c2_eml_matlab_zpotrf(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[16], real_T c2_b_A[16], int32_T *c2_info);
static void c2_eml_xgemv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_ia0, int32_T c2_ix0,
  real_T c2_y[16], int32_T c2_iy0, real_T c2_b_y[16]);
static void c2_i_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, int32_T c2_a,
   int32_T c2_b);
static void c2_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[16], real_T c2_B[16], real_T c2_C[16]);
static void c2_b_below_threshold(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_p_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static boolean_T c2_b_is_singular_triangular_matrix
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, real_T c2_A[16]);
static void c2_b_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[16], real_T c2_B[16], real_T c2_C[16]);
static void c2_j_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void c2_q_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_r_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_c_mySymPDinv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_M[9], real_T c2_Minv[9]);
static void c2_b_chol(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_A[9], real_T c2_b_A[9]);
static void c2_s_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_b_eml_matlab_zpotrf(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_b_A[9], int32_T *c2_info);
static void c2_b_eml_xgemv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_ia0, int32_T c2_ix0,
  real_T c2_y[9], int32_T c2_iy0, real_T c2_b_y[9]);
static void c2_c_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_B[9], real_T c2_C[9]);
static void c2_c_below_threshold(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_t_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static boolean_T c2_c_is_singular_triangular_matrix
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, real_T c2_A[9]);
static void c2_d_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_B[9], real_T c2_C[9]);
static void c2_k_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static void c2_d_diag(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_v[44], real_T c2_d[1936]);
static void c2_u_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_f_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[1936], real_T c2_C[1760],
  real_T c2_b_C[1760]);
static void c2_v_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_g_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[1760], real_T c2_C[1600],
  real_T c2_b_C[1600]);
static void c2_w_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_h_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1600], real_T c2_B[1600], real_T c2_C[1600],
  real_T c2_b_C[1600]);
static void c2_eye(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                   real_T c2_I[1600]);
static void c2_eps(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance);
static real_T c2_Rtil(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_phiInv[1600]);
static void c2_Qtil(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                    real_T c2_phiInv[1600], real_T c2_Qt[9]);
static void c2_b_Qtil(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_phiInv[1600], real_T c2_ii, real_T c2_Qt[9]);
static void c2_multByAT(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_M[9], real_T c2_AT[9], real_T c2_switches[9], real_T
  c2_y[9]);
static void c2_Stil(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                    real_T c2_phiInv[1600], real_T c2_ii, real_T c2_St[3]);
static void c2_b_preMultByA(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_M[9], real_T c2_A[9], real_T c2_switches[9], real_T
  c2_y[9]);
static real_T c2_b_Rtil(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_phiInv[1600], real_T c2_ii);
static void c2_x_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_y_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_ab_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_i_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[1600], real_T c2_C[1280],
  real_T c2_b_C[1280]);
static void c2_bb_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_j_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[1280], real_T c2_C[1024],
  real_T c2_b_C[1024]);
static void c2_cb_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static real_T c2_e_norm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x[1024]);
static void c2_c_eml_error(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_eml_matlab_zsvdc(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1024], real_T c2_S[32]);
static real_T c2_eml_xnrm2(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[1024], int32_T c2_ix0);
static void c2_eml_xscal(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[1024], int32_T c2_ix0,
  real_T c2_b_x[1024]);
static real_T c2_eml_xdotc(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[1024], int32_T c2_ix0, real_T c2_y
  [1024], int32_T c2_iy0);
static void c2_db_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_eml_xaxpy(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, int32_T c2_ix0, real_T c2_y[1024],
  int32_T c2_iy0, real_T c2_b_y[1024]);
static real_T c2_b_eml_xnrm2(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[32], int32_T c2_ix0);
static void c2_b_eml_xscal(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[32], int32_T c2_ix0,
  real_T c2_b_x[32]);
static void c2_b_eml_xaxpy(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[1024], int32_T c2_ix0,
  real_T c2_y[32], int32_T c2_iy0, real_T c2_b_y[32]);
static void c2_c_eml_xaxpy(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[32], int32_T c2_ix0,
  real_T c2_y[1024], int32_T c2_iy0, real_T c2_b_y[1024]);
static void c2_d_eml_error(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_l_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, int32_T c2_a);
static void c2_m_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, int32_T c2_a,
   int32_T c2_b);
static real_T c2_sqrt(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_x);
static void c2_e_eml_error(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_eml_xrotg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_a, real_T c2_b, real_T *c2_b_a, real_T *c2_b_b,
  real_T *c2_c, real_T *c2_s);
static void c2_eb_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_getSqBlk(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_U[1024], real_T c2_Y[9]);
static void c2_b_getSqBlk(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_U[1024], real_T c2_ii, real_T c2_jj, real_T c2_Y[9]);
static void c2_e_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_B[6], real_T c2_C[6]);
static void c2_eml_xtrsm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_B[6], real_T c2_b_B[6]);
static void c2_c_chol(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_A[4], real_T c2_b_A[4]);
static void c2_c_eml_matlab_zpotrf(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[4], real_T c2_b_A[4], int32_T *c2_info);
static void c2_c_eml_xgemv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_ia0, int32_T c2_ix0,
  real_T c2_y[4], int32_T c2_iy0, real_T c2_b_y[4]);
static void c2_k_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1024], real_T c2_B[1024], real_T c2_C[1024],
  real_T c2_b_C[1024]);
static void c2_f_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_B[3], real_T c2_C[3]);
static void c2_d_below_threshold(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_g_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[4], real_T c2_B[2], real_T c2_C[2]);
static void c2_fb_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_e_below_threshold(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static boolean_T c2_d_is_singular_triangular_matrix
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, real_T c2_A[4]);
static void c2_gb_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_l_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1024], real_T c2_B[32], real_T c2_C[32], real_T
  c2_b_C[32]);
static void c2_h_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[4], real_T c2_B[2], real_T c2_C[2]);
static void c2_i_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_B[3], real_T c2_C[3]);
static void c2_hb_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);
static void c2_m_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[5184], real_T c2_B[72], real_T c2_C[72], real_T
  c2_b_C[72]);
static real_T c2_f_norm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x[72]);
static void c2_b_calcDs(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_z[40], real_T c2_Ps[1600], real_T c2_Fxs[12], real_T
  c2_Fus[4], real_T c2_hs[40], real_T c2_rho, boolean_T c2_flagNoPade, real_T
  c2_switches[9], real_T c2_ds[40], real_T c2_es[40]);
static const mxArray *c2_x_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_y_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct *
  chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_w_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_ab_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_mpcSetpointIntptCoupled,
  const char_T *c2_identifier);
static uint8_T c2_bb_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_n_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[40], real_T c2_C[44]);
static void c2_o_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[40], real_T c2_C[32]);
static void c2_p_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[44], real_T c2_C[40]);
static void c2_q_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[32], real_T c2_C[40]);
static void c2_r_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1600], real_T c2_B[40], real_T c2_C[40]);
static void c2_d_chol(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T *c2_A);
static int32_T c2_d_eml_matlab_zpotrf(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[16]);
static void c2_d_eml_xgemv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_ia0, int32_T c2_ix0,
  real_T c2_y[16], int32_T c2_iy0);
static void c2_e_chol(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_A[9]);
static int32_T c2_e_eml_matlab_zpotrf(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9]);
static void c2_e_eml_xgemv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_ia0, int32_T c2_ix0,
  real_T c2_y[9], int32_T c2_iy0);
static void c2_s_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[1936], real_T c2_C[1760]);
static void c2_t_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[1760], real_T c2_C[1600]);
static void c2_u_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1600], real_T c2_B[1600], real_T c2_C[1600]);
static void c2_v_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[1600], real_T c2_C[1280]);
static void c2_w_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[1280], real_T c2_C[1024]);
static void c2_c_eml_xscal(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[1024], int32_T c2_ix0);
static void c2_d_eml_xaxpy(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, int32_T c2_ix0, real_T c2_y[1024],
  int32_T c2_iy0);
static void c2_d_eml_xscal(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[32], int32_T c2_ix0);
static void c2_e_eml_xaxpy(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[1024], int32_T c2_ix0,
  real_T c2_y[32], int32_T c2_iy0);
static void c2_f_eml_xaxpy(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[32], int32_T c2_ix0,
  real_T c2_y[1024], int32_T c2_iy0);
static void c2_b_sqrt(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T *c2_x);
static void c2_b_eml_xrotg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T *c2_a, real_T *c2_b, real_T *c2_c, real_T *c2_s);
static void c2_b_eml_xtrsm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_B[6]);
static void c2_f_chol(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_A[4]);
static int32_T c2_f_eml_matlab_zpotrf(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[4]);
static void c2_f_eml_xgemv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_ia0, int32_T c2_ix0,
  real_T c2_y[4], int32_T c2_iy0);
static void c2_x_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1024], real_T c2_B[1024], real_T c2_C[1024]);
static void c2_y_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1024], real_T c2_B[32], real_T c2_C[32]);
static void c2_ab_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[5184], real_T c2_B[72], real_T c2_C[72]);
static void init_dsm_address_info(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_is_active_c2_mpcSetpointIntptCoupled = 0U;
}

static void initialize_params_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
}

static void enable_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
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
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_mpcSetpointIntptCoupled;
  c2_c_u = c2_hoistedGlobal;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 2, c2_d_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, const mxArray
   *c2_st)
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
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)), "info",
                      c2_dv0);
  for (c2_i2 = 0; c2_i2 < 4; c2_i2++) {
    (*c2_info)[c2_i2] = c2_dv0[c2_i2];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)), "z",
                        c2_dv1);
  for (c2_i3 = 0; c2_i3 < 40; c2_i3++) {
    (*c2_z)[c2_i3] = c2_dv1[c2_i3];
  }

  chartInstance->c2_is_active_c2_mpcSetpointIntptCoupled =
    c2_ab_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 2)),
    "is_active_c2_mpcSetpointIntptCoupled");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_mpcSetpointIntptCoupled(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
}

static void sf_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
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
  int32_T c2_i24;
  int32_T c2_i25;
  real_T *c2_R;
  real_T (*c2_Fus)[4];
  real_T (*c2_Fxs)[12];
  real_T (*c2_Ef)[6];
  real_T (*c2_hs)[40];
  real_T (*c2_Ps)[1600];
  real_T (*c2_opts)[8];
  real_T (*c2_info)[4];
  real_T (*c2_Qf)[9];
  real_T (*c2_Q)[9];
  real_T (*c2_Ff)[12];
  real_T (*c2_Fu)[4];
  real_T (*c2_Fx)[12];
  real_T (*c2_B)[3];
  real_T (*c2_A)[9];
  real_T (*c2_z0)[40];
  real_T (*c2_b)[32];
  real_T (*c2_C)[1280];
  real_T (*c2_h)[44];
  real_T (*c2_P)[1760];
  real_T (*c2_g)[40];
  real_T (*c2_z)[40];
  real_T (*c2_H)[1600];
  c2_Fus = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 20);
  c2_Fxs = (real_T (*)[12])ssGetInputPortSignal(chartInstance->S, 19);
  c2_Ef = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 18);
  c2_hs = (real_T (*)[40])ssGetInputPortSignal(chartInstance->S, 17);
  c2_Ps = (real_T (*)[1600])ssGetInputPortSignal(chartInstance->S, 16);
  c2_opts = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 15);
  c2_info = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_Qf = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 14);
  c2_R = (real_T *)ssGetInputPortSignal(chartInstance->S, 13);
  c2_Q = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 12);
  c2_Ff = (real_T (*)[12])ssGetInputPortSignal(chartInstance->S, 11);
  c2_Fu = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 10);
  c2_Fx = (real_T (*)[12])ssGetInputPortSignal(chartInstance->S, 9);
  c2_B = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 8);
  c2_A = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 7);
  c2_z0 = (real_T (*)[40])ssGetInputPortSignal(chartInstance->S, 6);
  c2_b = (real_T (*)[32])ssGetInputPortSignal(chartInstance->S, 5);
  c2_C = (real_T (*)[1280])ssGetInputPortSignal(chartInstance->S, 4);
  c2_h = (real_T (*)[44])ssGetInputPortSignal(chartInstance->S, 3);
  c2_P = (real_T (*)[1760])ssGetInputPortSignal(chartInstance->S, 2);
  c2_g = (real_T (*)[40])ssGetInputPortSignal(chartInstance->S, 1);
  c2_z = (real_T (*)[40])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_H = (real_T (*)[1600])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i4 = 0; c2_i4 < 1600; c2_i4++) {
    _SFD_DATA_RANGE_CHECK((*c2_H)[c2_i4], 0U);
  }

  for (c2_i5 = 0; c2_i5 < 40; c2_i5++) {
    _SFD_DATA_RANGE_CHECK((*c2_z)[c2_i5], 1U);
  }

  for (c2_i6 = 0; c2_i6 < 40; c2_i6++) {
    _SFD_DATA_RANGE_CHECK((*c2_g)[c2_i6], 2U);
  }

  for (c2_i7 = 0; c2_i7 < 1760; c2_i7++) {
    _SFD_DATA_RANGE_CHECK((*c2_P)[c2_i7], 3U);
  }

  for (c2_i8 = 0; c2_i8 < 44; c2_i8++) {
    _SFD_DATA_RANGE_CHECK((*c2_h)[c2_i8], 4U);
  }

  for (c2_i9 = 0; c2_i9 < 1280; c2_i9++) {
    _SFD_DATA_RANGE_CHECK((*c2_C)[c2_i9], 5U);
  }

  for (c2_i10 = 0; c2_i10 < 32; c2_i10++) {
    _SFD_DATA_RANGE_CHECK((*c2_b)[c2_i10], 6U);
  }

  for (c2_i11 = 0; c2_i11 < 40; c2_i11++) {
    _SFD_DATA_RANGE_CHECK((*c2_z0)[c2_i11], 7U);
  }

  for (c2_i12 = 0; c2_i12 < 9; c2_i12++) {
    _SFD_DATA_RANGE_CHECK((*c2_A)[c2_i12], 8U);
  }

  for (c2_i13 = 0; c2_i13 < 3; c2_i13++) {
    _SFD_DATA_RANGE_CHECK((*c2_B)[c2_i13], 9U);
  }

  for (c2_i14 = 0; c2_i14 < 12; c2_i14++) {
    _SFD_DATA_RANGE_CHECK((*c2_Fx)[c2_i14], 10U);
  }

  for (c2_i15 = 0; c2_i15 < 4; c2_i15++) {
    _SFD_DATA_RANGE_CHECK((*c2_Fu)[c2_i15], 11U);
  }

  for (c2_i16 = 0; c2_i16 < 12; c2_i16++) {
    _SFD_DATA_RANGE_CHECK((*c2_Ff)[c2_i16], 12U);
  }

  for (c2_i17 = 0; c2_i17 < 9; c2_i17++) {
    _SFD_DATA_RANGE_CHECK((*c2_Q)[c2_i17], 13U);
  }

  _SFD_DATA_RANGE_CHECK(*c2_R, 14U);
  for (c2_i18 = 0; c2_i18 < 9; c2_i18++) {
    _SFD_DATA_RANGE_CHECK((*c2_Qf)[c2_i18], 15U);
  }

  for (c2_i19 = 0; c2_i19 < 4; c2_i19++) {
    _SFD_DATA_RANGE_CHECK((*c2_info)[c2_i19], 16U);
  }

  for (c2_i20 = 0; c2_i20 < 8; c2_i20++) {
    _SFD_DATA_RANGE_CHECK((*c2_opts)[c2_i20], 17U);
  }

  for (c2_i21 = 0; c2_i21 < 1600; c2_i21++) {
    _SFD_DATA_RANGE_CHECK((*c2_Ps)[c2_i21], 18U);
  }

  for (c2_i22 = 0; c2_i22 < 40; c2_i22++) {
    _SFD_DATA_RANGE_CHECK((*c2_hs)[c2_i22], 19U);
  }

  for (c2_i23 = 0; c2_i23 < 6; c2_i23++) {
    _SFD_DATA_RANGE_CHECK((*c2_Ef)[c2_i23], 20U);
  }

  for (c2_i24 = 0; c2_i24 < 12; c2_i24++) {
    _SFD_DATA_RANGE_CHECK((*c2_Fxs)[c2_i24], 21U);
  }

  for (c2_i25 = 0; c2_i25 < 4; c2_i25++) {
    _SFD_DATA_RANGE_CHECK((*c2_Fus)[c2_i25], 22U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_mpcSetpointIntptCoupled(chartInstance);
  sf_debug_check_for_state_inconsistency(_mpcSetpointIntptCoupledMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c2_chartstep_c2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
  real_T c2_hoistedGlobal;
  int32_T c2_i26;
  static real_T c2_H[1600];
  int32_T c2_i27;
  real_T c2_g[40];
  int32_T c2_i28;
  static real_T c2_P[1760];
  int32_T c2_i29;
  real_T c2_h[44];
  int32_T c2_i30;
  static real_T c2_C[1280];
  int32_T c2_i31;
  real_T c2_b[32];
  int32_T c2_i32;
  real_T c2_z0[40];
  int32_T c2_i33;
  real_T c2_A[9];
  int32_T c2_i34;
  real_T c2_B[3];
  int32_T c2_i35;
  real_T c2_Fx[12];
  int32_T c2_i36;
  real_T c2_Fu[4];
  int32_T c2_i37;
  real_T c2_Ff[12];
  int32_T c2_i38;
  real_T c2_Q[9];
  real_T c2_R;
  int32_T c2_i39;
  real_T c2_Qf[9];
  int32_T c2_i40;
  real_T c2_opts[8];
  int32_T c2_i41;
  static real_T c2_Ps[1600];
  int32_T c2_i42;
  real_T c2_hs[40];
  int32_T c2_i43;
  real_T c2_Ef[6];
  int32_T c2_i44;
  real_T c2_Fxs[12];
  int32_T c2_i45;
  real_T c2_Fus[4];
  uint32_T c2_debug_family_var_map[112];
  real_T c2_check_d;
  real_T c2_checkRp;
  real_T c2_checkPhiInv;
  real_T c2_checkY;
  real_T c2_checkBeta;
  real_T c2_checkL;
  real_T c2_check_t;
  real_T c2_check_dnu;
  real_T c2_checkNewton;
  real_T c2_checkInv;
  real_T c2_totBackTracks;
  real_T c2_n;
  real_T c2_m;
  real_T c2_nz;
  real_T c2_ne;
  real_T c2_ni;
  real_T c2_ns;
  real_T c2_ell;
  real_T c2_ellf;
  real_T c2_ellef;
  real_T c2_T;
  real_T c2_ells;
  real_T c2_kappa;
  real_T c2_rho;
  real_T c2_numBarrIters;
  real_T c2_nop;
  boolean_T c2_flagPhiIsDiag;
  real_T c2_numNewtonIters;
  boolean_T c2_flagUseSoftCons;
  boolean_T c2_flagChecking;
  boolean_T c2_flagNoPade;
  real_T c2_switches[9];
  static real_T c2_kappaPt[1760];
  static real_T c2_kappaPtSq[1760];
  static real_T c2_rhoPstSq[1600];
  real_T c2_diagTwoH[40];
  real_T c2_blkQR[16];
  real_T c2_FxsT[12];
  real_T c2_FusT[4];
  real_T c2_AT[9];
  real_T c2_BT[3];
  static real_T c2_CT[1280];
  real_T c2_EfT[6];
  static real_T c2_PsT[1600];
  real_T c2_es[40];
  real_T c2_ds[40];
  real_T c2_dsNew[40];
  real_T c2_esNew[40];
  real_T c2_dz[40];
  static real_T c2_phi[1600];
  real_T c2_dhats[40];
  real_T c2_zTail[40];
  real_T c2_initSolChoice;
  real_T c2_nu[32];
  real_T c2_d[44];
  real_T c2_rp[32];
  real_T c2_rpMag;
  real_T c2_rd[40];
  real_T c2_checkPsT;
  real_T c2_rdMag;
  real_T c2_rMag;
  real_T c2_diagPhi[40];
  static real_T c2_phiInv[1600];
  real_T c2_blkInv[16];
  static real_T c2_Y[1024];
  real_T c2_tmp[9];
  real_T c2_PhiInvRd[40];
  real_T c2_rhs[32];
  static real_T c2_L[1024];
  real_T c2_t[32];
  real_T c2_dnu[32];
  real_T c2_v[40];
  real_T c2_checkV;
  real_T c2_sMax;
  real_T c2_zFar[40];
  real_T c2_iFar[44];
  real_T c2_s;
  real_T c2_zNew[40];
  real_T c2_nuNew[32];
  real_T c2_iNew[44];
  real_T c2_dNew[44];
  real_T c2_rdNew[40];
  real_T c2_rpNew[32];
  real_T c2_rdMagNew;
  real_T c2_rpMagNew;
  real_T c2_rMagNew;
  real_T c2_gradRmag;
  real_T c2_nargin = 21.0;
  real_T c2_nargout = 2.0;
  real_T c2_z[40];
  real_T c2_info[4];
  real_T c2_b_b;
  int32_T c2_i46;
  static real_T c2_a[9] = { 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };

  real_T c2_b_a;
  int32_T c2_i47;
  int32_T c2_i48;
  int32_T c2_i49;
  int32_T c2_i50;
  static real_T c2_c_b[1760];
  int32_T c2_i51;
  int32_T c2_i52;
  int32_T c2_i53;
  int32_T c2_i54;
  int32_T c2_i55;
  int32_T c2_i56;
  int32_T c2_i57;
  int32_T c2_i58;
  int32_T c2_i59;
  static real_T c2_d_b[1600];
  int32_T c2_i60;
  int32_T c2_i61;
  int32_T c2_i62;
  int32_T c2_i63;
  int32_T c2_i64;
  int32_T c2_i65;
  int32_T c2_i66;
  int32_T c2_i67;
  static real_T c2_e_b[1600];
  real_T c2_dv2[40];
  int32_T c2_i68;
  int32_T c2_i69;
  int32_T c2_i70;
  int32_T c2_i71;
  int32_T c2_i72;
  int32_T c2_i73;
  int32_T c2_i74;
  int32_T c2_i75;
  int32_T c2_i76;
  int32_T c2_i77;
  int32_T c2_i78;
  int32_T c2_i79;
  int32_T c2_i80;
  int32_T c2_i81;
  int32_T c2_i82;
  int32_T c2_i83;
  int32_T c2_i84;
  int32_T c2_i85;
  int32_T c2_i86;
  int32_T c2_i87;
  int32_T c2_i88;
  int32_T c2_i89;
  int32_T c2_i90;
  int32_T c2_i91;
  int32_T c2_i92;
  int32_T c2_i93;
  int32_T c2_i94;
  int32_T c2_i95;
  int32_T c2_i96;
  int32_T c2_i97;
  int32_T c2_i98;
  int32_T c2_i99;
  int32_T c2_i100;
  int32_T c2_i101;
  int32_T c2_i102;
  real_T c2_b_nz;
  int32_T c2_i103;
  real_T c2_b_z0[3];
  int32_T c2_i104;
  real_T c2_b_A[9];
  int32_T c2_i105;
  real_T c2_b_switches[9];
  real_T c2_c_a[3];
  int32_T c2_i106;
  int32_T c2_i107;
  int32_T c2_i108;
  static real_T c2_d_a[1760];
  int32_T c2_i109;
  real_T c2_f_b[40];
  int32_T c2_i110;
  real_T c2_y[44];
  int32_T c2_i111;
  static real_T c2_e_a[1760];
  int32_T c2_i112;
  real_T c2_g_b[40];
  int32_T c2_i113;
  boolean_T c2_b_y[44];
  int32_T c2_i114;
  int32_T c2_i115;
  int32_T c2_i116;
  int32_T c2_i117;
  int32_T c2_i118;
  int32_T c2_i119;
  static real_T c2_f_a[1760];
  int32_T c2_i120;
  real_T c2_h_b[40];
  int32_T c2_i121;
  boolean_T c2_c_y[44];
  int32_T c2_i122;
  int32_T c2_i123;
  int32_T c2_i124;
  int32_T c2_i125;
  static real_T c2_g_a[1760];
  int32_T c2_i126;
  real_T c2_i_b[40];
  int32_T c2_i127;
  boolean_T c2_d_y[44];
  int32_T c2_i128;
  int32_T c2_i129;
  boolean_T c2_bv0[44];
  int32_T c2_i130;
  int32_T c2_i131;
  real_T c2_u;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i132;
  int32_T c2_i133;
  real_T c2_b_z[40];
  int32_T c2_i134;
  static real_T c2_b_P[1760];
  int32_T c2_i135;
  real_T c2_b_Fx[12];
  int32_T c2_i136;
  real_T c2_b_Fu[4];
  int32_T c2_i137;
  real_T c2_b_Ff[12];
  int32_T c2_i138;
  real_T c2_c_switches[9];
  int32_T c2_i139;
  real_T c2_b_h[44];
  real_T c2_dv3[44];
  int32_T c2_i140;
  int32_T c2_i141;
  real_T c2_c_z[40];
  int32_T c2_i142;
  real_T c2_j_b[32];
  int32_T c2_i143;
  real_T c2_c_A[9];
  int32_T c2_i144;
  real_T c2_b_B[3];
  int32_T c2_i145;
  static real_T c2_b_C[1280];
  int32_T c2_i146;
  real_T c2_b_Ef[6];
  int32_T c2_i147;
  real_T c2_d_switches[9];
  real_T c2_dv4[32];
  int32_T c2_i148;
  int32_T c2_i149;
  real_T c2_b_rp[32];
  int32_T c2_i150;
  int32_T c2_i151;
  int32_T c2_i152;
  real_T c2_f_y[40];
  int32_T c2_i153;
  static real_T c2_k_b[1760];
  int32_T c2_i154;
  real_T c2_g_y[44];
  int32_T c2_i155;
  real_T c2_dv5[32];
  int32_T c2_i156;
  static real_T c2_b_CT[1280];
  int32_T c2_i157;
  real_T c2_b_AT[9];
  int32_T c2_i158;
  real_T c2_b_BT[3];
  int32_T c2_i159;
  real_T c2_b_EfT[6];
  int32_T c2_i160;
  real_T c2_e_switches[9];
  real_T c2_dv6[40];
  int32_T c2_i161;
  int32_T c2_i162;
  real_T c2_d_z[40];
  int32_T c2_i163;
  static real_T c2_b_Ps[1600];
  int32_T c2_i164;
  real_T c2_b_Fxs[12];
  int32_T c2_i165;
  real_T c2_b_Fus[4];
  int32_T c2_i166;
  real_T c2_b_hs[40];
  int32_T c2_i167;
  real_T c2_f_switches[9];
  int32_T c2_i168;
  int32_T c2_i169;
  int32_T c2_i170;
  real_T c2_b_ds[40];
  int32_T c2_i171;
  static real_T c2_b_PsT[1600];
  int32_T c2_i172;
  real_T c2_b_FxsT[12];
  int32_T c2_i173;
  real_T c2_b_FusT[4];
  int32_T c2_i174;
  real_T c2_g_switches[9];
  int32_T c2_i175;
  int32_T c2_i176;
  real_T c2_b_rd[40];
  real_T c2_b_rdMag[2];
  int32_T c2_i177;
  int32_T c2_loop_ub;
  int32_T c2_ww;
  int32_T c2_i178;
  int32_T c2_b_loop_ub;
  int32_T c2_kk;
  int32_T c2_i179;
  int32_T c2_i180;
  int32_T c2_i181;
  int32_T c2_i182;
  static real_T c2_h_a[1760];
  int32_T c2_i183;
  real_T c2_l_b[40];
  int32_T c2_i184;
  real_T c2_c_h[44];
  int32_T c2_i185;
  real_T c2_b_d[44];
  real_T c2_b_u;
  const mxArray *c2_h_y = NULL;
  int32_T c2_i186;
  static real_T c2_i_a[1280];
  int32_T c2_i187;
  int32_T c2_i188;
  real_T c2_i_y[32];
  int32_T c2_i189;
  static real_T c2_j_a[1280];
  int32_T c2_i190;
  real_T c2_m_b[40];
  int32_T c2_i191;
  real_T c2_j_y[32];
  real_T c2_c_u;
  const mxArray *c2_k_y = NULL;
  int32_T c2_i192;
  real_T c2_b_es[40];
  int32_T c2_i193;
  real_T c2_dv7[40];
  real_T c2_dv8[40];
  int32_T c2_i194;
  int32_T c2_i195;
  int32_T c2_i196;
  int32_T c2_i197;
  int32_T c2_i198;
  static real_T c2_n_b[1760];
  int32_T c2_i199;
  real_T c2_l_y[44];
  int32_T c2_i200;
  int32_T c2_i201;
  static real_T c2_k_a[1600];
  int32_T c2_i202;
  int32_T c2_i203;
  int32_T c2_i204;
  static real_T c2_l_a[1600];
  int32_T c2_i205;
  real_T c2_o_b[40];
  int32_T c2_i206;
  int32_T c2_i207;
  real_T c2_b_diagPhi[40];
  int32_T c2_i208;
  real_T c2_dv9[40];
  static real_T c2_dv10[1600];
  int32_T c2_i209;
  int32_T c2_i210;
  real_T c2_p_b;
  real_T c2_m_y;
  real_T c2_m_a;
  int32_T c2_i211;
  real_T c2_q_b[4];
  int32_T c2_i212;
  int32_T c2_i213;
  real_T c2_c_d[4];
  real_T c2_r_b[16];
  int32_T c2_i214;
  int32_T c2_i215;
  real_T c2_n_y[4];
  int32_T c2_i216;
  int32_T c2_i217;
  real_T c2_s_b[4];
  real_T c2_o_y;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_n_a;
  int32_T c2_i218;
  int32_T c2_i219;
  int32_T c2_i220;
  real_T c2_b_dhats[4];
  int32_T c2_i221;
  int32_T c2_i222;
  int32_T c2_i223;
  int32_T c2_i224;
  real_T c2_p_y;
  int32_T c2_c_k;
  int32_T c2_d_k;
  real_T c2_t_b;
  real_T c2_q_y;
  real_T c2_o_a;
  int32_T c2_i225;
  int32_T c2_i226;
  int32_T c2_i227;
  real_T c2_d_d[4];
  int32_T c2_i228;
  int32_T c2_i229;
  int32_T c2_i230;
  int32_T c2_i231;
  real_T c2_r_y;
  int32_T c2_e_k;
  int32_T c2_f_k;
  int32_T c2_ii;
  real_T c2_b_ii;
  int32_T c2_i232;
  int32_T c2_i233;
  real_T c2_p_a;
  int32_T c2_i234;
  int32_T c2_i235;
  int32_T c2_i236;
  int32_T c2_i237;
  real_T c2_u_b[16];
  int32_T c2_i238;
  int32_T c2_i239;
  int32_T c2_i240;
  real_T c2_q_a;
  real_T c2_s_y;
  real_T c2_r_a;
  real_T c2_t_y;
  int32_T c2_i241;
  real_T c2_e_d[4];
  real_T c2_v_b[16];
  int32_T c2_i242;
  int32_T c2_i243;
  int32_T c2_i244;
  real_T c2_u_y[16];
  int32_T c2_i245;
  int32_T c2_i246;
  int32_T c2_i247;
  int32_T c2_i248;
  int32_T c2_i249;
  int32_T c2_i250;
  int32_T c2_i251;
  int32_T c2_i252;
  int32_T c2_i253;
  real_T c2_v_y[16];
  int32_T c2_i254;
  int32_T c2_i255;
  real_T c2_s_a;
  int32_T c2_i256;
  int32_T c2_i257;
  int32_T c2_i258;
  int32_T c2_i259;
  int32_T c2_i260;
  int32_T c2_i261;
  int32_T c2_i262;
  real_T c2_t_a;
  real_T c2_w_y;
  int32_T c2_i263;
  real_T c2_c_dhats[4];
  int32_T c2_i264;
  int32_T c2_i265;
  int32_T c2_i266;
  int32_T c2_i267;
  int32_T c2_i268;
  int32_T c2_i269;
  int32_T c2_i270;
  int32_T c2_i271;
  int32_T c2_i272;
  int32_T c2_i273;
  int32_T c2_i274;
  int32_T c2_i275;
  int32_T c2_i276;
  int32_T c2_i277;
  int32_T c2_i278;
  real_T c2_w_b[16];
  real_T c2_dv11[16];
  int32_T c2_i279;
  int32_T c2_i280;
  int32_T c2_i281;
  real_T c2_u_a;
  int32_T c2_i282;
  int32_T c2_i283;
  int32_T c2_i284;
  int32_T c2_i285;
  int32_T c2_i286;
  int32_T c2_i287;
  int32_T c2_i288;
  real_T c2_v_a;
  real_T c2_x_y;
  real_T c2_w_a;
  real_T c2_y_y;
  int32_T c2_i289;
  real_T c2_f_d[4];
  int32_T c2_i290;
  int32_T c2_i291;
  int32_T c2_i292;
  int32_T c2_i293;
  int32_T c2_i294;
  int32_T c2_i295;
  int32_T c2_i296;
  int32_T c2_i297;
  int32_T c2_i298;
  int32_T c2_i299;
  int32_T c2_i300;
  int32_T c2_i301;
  int32_T c2_i302;
  int32_T c2_i303;
  int32_T c2_i304;
  real_T c2_x_b[16];
  real_T c2_dv12[16];
  int32_T c2_i305;
  real_T c2_x_a;
  real_T c2_ab_y;
  real_T c2_y_a;
  real_T c2_bb_y;
  real_T c2_b_m;
  real_T c2_c_m;
  int32_T c2_i306;
  int32_T c2_i307;
  int32_T c2_i308;
  real_T c2_y_b[9];
  int32_T c2_i309;
  real_T c2_ab_a;
  int32_T c2_i310;
  int32_T c2_i311;
  int32_T c2_i312;
  int32_T c2_i313;
  real_T c2_ab_b[12];
  int32_T c2_i314;
  int32_T c2_i315;
  real_T c2_g_d[4];
  int32_T c2_i316;
  int32_T c2_i317;
  int32_T c2_i318;
  int32_T c2_i319;
  real_T c2_cb_y[12];
  int32_T c2_i320;
  int32_T c2_i321;
  int32_T c2_i322;
  real_T c2_bb_b[12];
  int32_T c2_i323;
  int32_T c2_i324;
  int32_T c2_i325;
  int32_T c2_i326;
  real_T c2_db_y[9];
  int32_T c2_i327;
  int32_T c2_i328;
  int32_T c2_i329;
  real_T c2_cb_b[9];
  real_T c2_dv13[9];
  real_T c2_c_nz;
  real_T c2_d_nz;
  int32_T c2_i330;
  int32_T c2_i331;
  int32_T c2_i332;
  int32_T c2_i333;
  real_T c2_bb_a;
  int32_T c2_i334;
  int32_T c2_i335;
  int32_T c2_i336;
  int32_T c2_i337;
  int32_T c2_i338;
  int32_T c2_i339;
  real_T c2_h_d[44];
  static real_T c2_db_b[1936];
  int32_T c2_i340;
  static real_T c2_eb_y[1760];
  int32_T c2_i341;
  static real_T c2_eb_b[1760];
  int32_T c2_i342;
  static real_T c2_fb_b[1936];
  int32_T c2_i343;
  real_T c2_i_d[44];
  int32_T c2_i344;
  int32_T c2_i345;
  static real_T c2_fb_y[1760];
  int32_T c2_i346;
  static real_T c2_gb_b[1936];
  int32_T c2_i347;
  int32_T c2_i348;
  static real_T c2_gb_y[1600];
  int32_T c2_i349;
  static real_T c2_hb_b[1760];
  int32_T c2_i350;
  static real_T c2_cb_a[1760];
  int32_T c2_i351;
  real_T c2_db_a;
  int32_T c2_i352;
  int32_T c2_i353;
  int32_T c2_i354;
  int32_T c2_i355;
  int32_T c2_i356;
  int32_T c2_i357;
  real_T c2_c_es[40];
  int32_T c2_i358;
  real_T c2_dv14[40];
  int32_T c2_i359;
  real_T c2_dv15[40];
  int32_T c2_i360;
  int32_T c2_i361;
  static real_T c2_ib_b[1600];
  int32_T c2_i362;
  static real_T c2_eb_a[1600];
  int32_T c2_i363;
  int32_T c2_i364;
  int32_T c2_i365;
  static real_T c2_hb_y[1600];
  int32_T c2_i366;
  static real_T c2_jb_b[1600];
  int32_T c2_i367;
  int32_T c2_i368;
  int32_T c2_i369;
  int32_T c2_i370;
  int32_T c2_i371;
  static real_T c2_fb_a[1600];
  int32_T c2_i372;
  static real_T c2_kb_b[1600];
  int32_T c2_i373;
  int32_T c2_ix;
  int32_T c2_iy;
  int32_T c2_i;
  int32_T c2_gb_a;
  int32_T c2_ixstart;
  int32_T c2_hb_a;
  int32_T c2_ixstop;
  real_T c2_mtmp;
  real_T c2_x;
  boolean_T c2_lb_b;
  int32_T c2_ib_a;
  int32_T c2_i374;
  int32_T c2_b_ix;
  int32_T c2_c_ix;
  real_T c2_b_x;
  boolean_T c2_mb_b;
  int32_T c2_jb_a;
  int32_T c2_i375;
  int32_T c2_d_ix;
  real_T c2_kb_a;
  real_T c2_nb_b;
  boolean_T c2_p;
  real_T c2_b_mtmp;
  int32_T c2_lb_a;
  real_T c2_maxval[40];
  int32_T c2_mb_a;
  int32_T c2_b_ixstart;
  real_T c2_c_mtmp;
  real_T c2_c_x;
  boolean_T c2_ob_b;
  int32_T c2_e_ix;
  int32_T c2_f_ix;
  real_T c2_d_x;
  boolean_T c2_pb_b;
  int32_T c2_nb_a;
  int32_T c2_i376;
  int32_T c2_g_ix;
  real_T c2_ob_a;
  real_T c2_qb_b;
  boolean_T c2_b_p;
  real_T c2_d_mtmp;
  real_T c2_d_u;
  const mxArray *c2_ib_y = NULL;
  int32_T c2_i377;
  int32_T c2_i378;
  int32_T c2_i379;
  static real_T c2_b_phiInv[1600];
  real_T c2_rb_b;
  int32_T c2_i380;
  int32_T c2_i381;
  real_T c2_sb_b[3];
  int32_T c2_i382;
  int32_T c2_i383;
  int32_T c2_i384;
  int32_T c2_i385;
  static real_T c2_c_phiInv[1600];
  real_T c2_dv16[9];
  int32_T c2_i386;
  int32_T c2_i387;
  int32_T c2_i388;
  int32_T c2_i389;
  int32_T c2_c_ii;
  real_T c2_pb_a;
  real_T c2_jb_y;
  real_T c2_qb_a;
  real_T c2_kb_y;
  int32_T c2_i390;
  static real_T c2_d_phiInv[1600];
  int32_T c2_i391;
  int32_T c2_i392;
  int32_T c2_i393;
  int32_T c2_i394;
  int32_T c2_i395;
  static real_T c2_e_phiInv[1600];
  int32_T c2_i396;
  real_T c2_dv17[9];
  int32_T c2_i397;
  real_T c2_c_AT[9];
  int32_T c2_i398;
  real_T c2_h_switches[9];
  int32_T c2_i399;
  int32_T c2_i400;
  real_T c2_rb_a;
  real_T c2_lb_y;
  real_T c2_sb_a;
  real_T c2_mb_y;
  real_T c2_tb_a;
  real_T c2_nb_y;
  real_T c2_ub_a;
  real_T c2_ob_y;
  int32_T c2_i401;
  int32_T c2_i402;
  real_T c2_b_Y[9];
  int32_T c2_i403;
  int32_T c2_i404;
  int32_T c2_i405;
  static real_T c2_f_phiInv[1600];
  int32_T c2_i406;
  real_T c2_vb_a[3];
  int32_T c2_i407;
  real_T c2_d_A[9];
  int32_T c2_i408;
  real_T c2_i_switches[9];
  int32_T c2_i409;
  int32_T c2_i410;
  int32_T c2_i411;
  int32_T c2_i412;
  real_T c2_wb_a;
  real_T c2_pb_y;
  real_T c2_xb_a;
  real_T c2_qb_y;
  int32_T c2_i413;
  int32_T c2_i414;
  static real_T c2_g_phiInv[1600];
  real_T c2_tb_b;
  int32_T c2_i415;
  int32_T c2_i416;
  int32_T c2_i417;
  int32_T c2_i418;
  int32_T c2_i419;
  int32_T c2_i420;
  static real_T c2_h_phiInv[1600];
  int32_T c2_i421;
  real_T c2_dv18[9];
  int32_T c2_i422;
  real_T c2_e_A[9];
  int32_T c2_i423;
  real_T c2_j_switches[9];
  int32_T c2_i424;
  real_T c2_dv19[9];
  int32_T c2_i425;
  real_T c2_d_AT[9];
  int32_T c2_i426;
  real_T c2_k_switches[9];
  int32_T c2_i427;
  static real_T c2_i_phiInv[1600];
  int32_T c2_i428;
  int32_T c2_i429;
  int32_T c2_i430;
  static real_T c2_j_phiInv[1600];
  real_T c2_yb_a[9];
  int32_T c2_i431;
  int32_T c2_i432;
  int32_T c2_i433;
  int32_T c2_i434;
  real_T c2_ub_b[6];
  int32_T c2_i435;
  int32_T c2_i436;
  int32_T c2_i437;
  real_T c2_rb_y[6];
  int32_T c2_i438;
  int32_T c2_i439;
  int32_T c2_i440;
  int32_T c2_i441;
  int32_T c2_i442;
  int32_T c2_i443;
  int32_T c2_i444;
  int32_T c2_i445;
  int32_T c2_i446;
  int32_T c2_i447;
  real_T c2_c_Y[6];
  int32_T c2_i448;
  int32_T c2_i449;
  int32_T c2_i450;
  int32_T c2_i451;
  int32_T c2_i452;
  real_T c2_ac_a[6];
  int32_T c2_i453;
  int32_T c2_i454;
  int32_T c2_i455;
  int32_T c2_i456;
  int32_T c2_i457;
  int32_T c2_i458;
  int32_T c2_i459;
  int32_T c2_i460;
  real_T c2_sb_y[4];
  int32_T c2_i461;
  int32_T c2_i462;
  int32_T c2_i463;
  int32_T c2_i464;
  int32_T c2_i465;
  int32_T c2_i466;
  int32_T c2_i467;
  int32_T c2_i468;
  int32_T c2_i469;
  static real_T c2_tb_y[1280];
  int32_T c2_i470;
  static real_T c2_bc_a[1280];
  int32_T c2_i471;
  static real_T c2_vb_b[1600];
  int32_T c2_i472;
  int32_T c2_i473;
  int32_T c2_i474;
  int32_T c2_i475;
  static real_T c2_wb_b[1280];
  int32_T c2_i476;
  static real_T c2_ub_y[1024];
  int32_T c2_i477;
  static real_T c2_vb_y[1280];
  int32_T c2_i478;
  static real_T c2_xb_b[1280];
  int32_T c2_i479;
  static real_T c2_d_Y[1024];
  real_T c2_e_u;
  const mxArray *c2_wb_y = NULL;
  int32_T c2_i480;
  int32_T c2_i481;
  static real_T c2_k_phiInv[1600];
  real_T c2_cc_a;
  real_T c2_yb_b;
  real_T c2_xb_y;
  int32_T c2_d_ii;
  int32_T c2_i482;
  static real_T c2_l_phiInv[1600];
  real_T c2_dc_a;
  real_T c2_yb_y;
  real_T c2_ec_a;
  real_T c2_ac_y;
  int32_T c2_i483;
  static real_T c2_m_phiInv[1600];
  int32_T c2_i484;
  static real_T c2_n_phiInv[1600];
  real_T c2_bc_y[3];
  int32_T c2_i485;
  static real_T c2_o_phiInv[1600];
  real_T c2_d0;
  int32_T c2_i486;
  int32_T c2_i487;
  int32_T c2_i488;
  int32_T c2_i489;
  int32_T c2_i490;
  int32_T c2_i491;
  int32_T c2_i492;
  real_T c2_d_m;
  int32_T c2_i493;
  int32_T c2_i494;
  real_T c2_cc_y[4];
  int32_T c2_i495;
  int32_T c2_i496;
  real_T c2_e_m;
  int32_T c2_i497;
  int32_T c2_i498;
  static real_T c2_p_phiInv[1600];
  real_T c2_f_m;
  int32_T c2_i499;
  int32_T c2_i500;
  int32_T c2_i501;
  int32_T c2_i502;
  real_T c2_g_m;
  int32_T c2_i503;
  int32_T c2_i504;
  real_T c2_b_PhiInvRd[40];
  int32_T c2_i505;
  real_T c2_f_A[9];
  int32_T c2_i506;
  real_T c2_c_B[3];
  int32_T c2_i507;
  static real_T c2_c_C[1280];
  int32_T c2_i508;
  real_T c2_c_Ef[6];
  int32_T c2_i509;
  real_T c2_l_switches[9];
  int32_T c2_i510;
  int32_T c2_i511;
  int32_T c2_i512;
  int32_T c2_i513;
  int32_T c2_i514;
  static real_T c2_fc_a[1280];
  int32_T c2_i515;
  static real_T c2_ac_b[1600];
  int32_T c2_i516;
  int32_T c2_i517;
  int32_T c2_i518;
  static real_T c2_dc_y[1280];
  int32_T c2_i519;
  real_T c2_bc_b[40];
  int32_T c2_i520;
  real_T c2_b_rhs[32];
  real_T c2_f_u;
  const mxArray *c2_ec_y = NULL;
  int32_T c2_i521;
  int32_T c2_i522;
  static real_T c2_e_Y[1024];
  int32_T c2_i523;
  real_T c2_dv20[9];
  real_T c2_dv21[9];
  int32_T c2_i524;
  int32_T c2_i525;
  int32_T c2_i526;
  int32_T c2_i527;
  int32_T c2_e_ii;
  real_T c2_gc_a;
  real_T c2_fc_y;
  real_T c2_hc_a;
  real_T c2_gc_y;
  int32_T c2_i528;
  static real_T c2_b_L[1024];
  int32_T c2_i529;
  static real_T c2_f_Y[1024];
  int32_T c2_i530;
  real_T c2_dv22[9];
  int32_T c2_i531;
  real_T c2_cc_b[9];
  int32_T c2_i532;
  int32_T c2_i533;
  real_T c2_ic_a;
  real_T c2_hc_y;
  real_T c2_jc_a;
  real_T c2_ic_y;
  int32_T c2_i534;
  static real_T c2_c_L[1024];
  int32_T c2_i535;
  static real_T c2_d_L[1024];
  int32_T c2_i536;
  int32_T c2_i537;
  int32_T c2_i538;
  int32_T c2_i539;
  int32_T c2_i540;
  int32_T c2_i541;
  int32_T c2_i542;
  int32_T c2_i543;
  int32_T c2_i544;
  int32_T c2_i545;
  static real_T c2_g_Y[1024];
  int32_T c2_i546;
  real_T c2_dv23[9];
  real_T c2_dv24[9];
  int32_T c2_i547;
  int32_T c2_i548;
  int32_T c2_i549;
  static real_T c2_e_L[1024];
  int32_T c2_i550;
  real_T c2_dv25[9];
  int32_T c2_i551;
  int32_T c2_i552;
  int32_T c2_i553;
  int32_T c2_i554;
  real_T c2_h_Y[6];
  int32_T c2_i555;
  int32_T c2_i556;
  int32_T c2_i557;
  int32_T c2_i558;
  int32_T c2_i559;
  int32_T c2_i560;
  int32_T c2_i561;
  int32_T c2_i562;
  int32_T c2_i563;
  int32_T c2_i564;
  int32_T c2_i565;
  int32_T c2_i566;
  int32_T c2_i567;
  int32_T c2_i568;
  int32_T c2_i569;
  int32_T c2_i570;
  int32_T c2_i571;
  int32_T c2_i572;
  int32_T c2_i573;
  int32_T c2_i574;
  int32_T c2_i575;
  int32_T c2_i576;
  real_T c2_i_Y[4];
  real_T c2_dv26[4];
  int32_T c2_i577;
  int32_T c2_i578;
  int32_T c2_i579;
  int32_T c2_i580;
  int32_T c2_i581;
  static real_T c2_kc_a[1024];
  int32_T c2_i582;
  int32_T c2_i583;
  int32_T c2_i584;
  int32_T c2_i585;
  real_T c2_dc_b[1024];
  int32_T c2_i586;
  int32_T c2_i587;
  real_T c2_lc_a[1024];
  int32_T c2_i588;
  real_T c2_ec_b[1024];
  int32_T c2_i589;
  real_T c2_jc_y[1024];
  real_T c2_g_u;
  const mxArray *c2_kc_y = NULL;
  int32_T c2_i590;
  int32_T c2_i591;
  real_T c2_f_L[1024];
  int32_T c2_i592;
  real_T c2_dv27[9];
  int32_T c2_i593;
  real_T c2_c_rhs[3];
  int32_T c2_i594;
  int32_T c2_f_ii;
  real_T c2_mc_a;
  real_T c2_lc_y;
  real_T c2_nc_a;
  real_T c2_mc_y;
  real_T c2_oc_a;
  real_T c2_nc_y;
  int32_T c2_i595;
  real_T c2_g_L[1024];
  int32_T c2_i596;
  int32_T c2_i597;
  int32_T c2_i598;
  int32_T c2_i599;
  int32_T c2_i600;
  real_T c2_h_L[1024];
  int32_T c2_i601;
  real_T c2_dv28[9];
  int32_T c2_i602;
  real_T c2_d_rhs[3];
  int32_T c2_i603;
  int32_T c2_i604;
  int32_T c2_i605;
  int32_T c2_i606;
  int32_T c2_i607;
  int32_T c2_i608;
  int32_T c2_i609;
  real_T c2_oc_y[2];
  int32_T c2_i610;
  int32_T c2_i611;
  int32_T c2_i612;
  int32_T c2_i613;
  int32_T c2_i614;
  int32_T c2_i615;
  real_T c2_i_L[4];
  int32_T c2_i616;
  real_T c2_e_rhs[2];
  int32_T c2_i617;
  int32_T c2_i618;
  int32_T c2_i619;
  real_T c2_fc_b[32];
  int32_T c2_i620;
  int32_T c2_i621;
  real_T c2_pc_a[1024];
  int32_T c2_i622;
  real_T c2_gc_b[32];
  int32_T c2_i623;
  real_T c2_pc_y[32];
  real_T c2_h_u;
  const mxArray *c2_qc_y = NULL;
  int32_T c2_i624;
  int32_T c2_i625;
  int32_T c2_i626;
  int32_T c2_i627;
  int32_T c2_i628;
  real_T c2_j_L[4];
  int32_T c2_i629;
  real_T c2_b_t[2];
  int32_T c2_i630;
  int32_T c2_i631;
  int32_T c2_i632;
  int32_T c2_i633;
  int32_T c2_i634;
  int32_T c2_i635;
  int32_T c2_i636;
  int32_T c2_i637;
  int32_T c2_i638;
  int32_T c2_i639;
  real_T c2_k_L[1024];
  int32_T c2_i640;
  int32_T c2_i641;
  int32_T c2_i642;
  int32_T c2_i643;
  real_T c2_dv29[9];
  int32_T c2_i644;
  real_T c2_c_t[3];
  int32_T c2_i645;
  int32_T c2_g_ii;
  real_T c2_qc_a;
  real_T c2_rc_y;
  real_T c2_rc_a;
  real_T c2_sc_y;
  real_T c2_sc_a;
  real_T c2_tc_y;
  int32_T c2_i646;
  real_T c2_l_L[1024];
  int32_T c2_i647;
  int32_T c2_i648;
  int32_T c2_i649;
  int32_T c2_i650;
  int32_T c2_i651;
  int32_T c2_i652;
  int32_T c2_i653;
  int32_T c2_i654;
  int32_T c2_i655;
  real_T c2_m_L[1024];
  int32_T c2_i656;
  int32_T c2_i657;
  int32_T c2_i658;
  int32_T c2_i659;
  real_T c2_dv30[9];
  int32_T c2_i660;
  real_T c2_d_t[3];
  int32_T c2_i661;
  int32_T c2_i662;
  int32_T c2_i663;
  int32_T c2_i664;
  int32_T c2_i665;
  real_T c2_tc_a[1024];
  int32_T c2_i666;
  real_T c2_hc_b[32];
  int32_T c2_i667;
  real_T c2_uc_y[32];
  real_T c2_i_u;
  const mxArray *c2_vc_y = NULL;
  int32_T c2_i668;
  real_T c2_b_dnu[32];
  int32_T c2_i669;
  static real_T c2_c_CT[1280];
  int32_T c2_i670;
  real_T c2_e_AT[9];
  int32_T c2_i671;
  real_T c2_c_BT[3];
  int32_T c2_i672;
  real_T c2_c_EfT[6];
  int32_T c2_i673;
  real_T c2_m_switches[9];
  int32_T c2_i674;
  int32_T c2_i675;
  int32_T c2_i676;
  int32_T c2_i677;
  int32_T c2_i678;
  int32_T c2_i679;
  int32_T c2_i680;
  int32_T c2_i681;
  static real_T c2_ic_b[1280];
  int32_T c2_i682;
  real_T c2_jc_b[32];
  int32_T c2_i683;
  real_T c2_b_v[40];
  real_T c2_j_u;
  const mxArray *c2_wc_y = NULL;
  int32_T c2_i684;
  static real_T c2_q_phiInv[1600];
  int32_T c2_i685;
  real_T c2_c_dnu[32];
  int32_T c2_i686;
  static real_T c2_d_CT[1280];
  int32_T c2_i687;
  real_T c2_f_AT[9];
  int32_T c2_i688;
  real_T c2_d_BT[3];
  int32_T c2_i689;
  real_T c2_d_EfT[6];
  int32_T c2_i690;
  real_T c2_n_switches[9];
  int32_T c2_i691;
  int32_T c2_i692;
  real_T c2_d_dnu[32];
  int32_T c2_i693;
  static real_T c2_e_CT[1280];
  int32_T c2_i694;
  real_T c2_g_AT[9];
  int32_T c2_i695;
  real_T c2_e_BT[3];
  int32_T c2_i696;
  real_T c2_e_EfT[6];
  int32_T c2_i697;
  real_T c2_o_switches[9];
  int32_T c2_i698;
  int32_T c2_i699;
  static real_T c2_r_phiInv[1600];
  real_T c2_uc_a;
  real_T c2_kc_b;
  real_T c2_xc_y;
  int32_T c2_h_ii;
  int32_T c2_i700;
  static real_T c2_s_phiInv[1600];
  real_T c2_vc_a;
  real_T c2_yc_y;
  real_T c2_wc_a;
  real_T c2_ad_y;
  int32_T c2_i701;
  static real_T c2_t_phiInv[1600];
  int32_T c2_i702;
  static real_T c2_u_phiInv[1600];
  int32_T c2_i703;
  static real_T c2_v_phiInv[1600];
  real_T c2_d1;
  int32_T c2_i704;
  int32_T c2_i705;
  int32_T c2_i706;
  int32_T c2_i707;
  int32_T c2_i708;
  int32_T c2_i709;
  int32_T c2_i710;
  real_T c2_h_m;
  int32_T c2_i711;
  int32_T c2_i712;
  int32_T c2_i713;
  int32_T c2_i714;
  real_T c2_i_m;
  int32_T c2_i715;
  int32_T c2_i716;
  static real_T c2_w_phiInv[1600];
  real_T c2_j_m;
  int32_T c2_i717;
  int32_T c2_i718;
  int32_T c2_i719;
  int32_T c2_i720;
  real_T c2_k_m;
  int32_T c2_i721;
  int32_T c2_i722;
  int32_T c2_i723;
  int32_T c2_i724;
  int32_T c2_i725;
  static real_T c2_xc_a[5184];
  int32_T c2_i726;
  int32_T c2_i727;
  int32_T c2_i728;
  int32_T c2_i729;
  int32_T c2_i730;
  int32_T c2_i731;
  int32_T c2_i732;
  int32_T c2_i733;
  int32_T c2_i734;
  int32_T c2_i735;
  int32_T c2_i736;
  int32_T c2_i737;
  real_T c2_lc_b[72];
  int32_T c2_i738;
  int32_T c2_i739;
  real_T c2_bd_y[72];
  int32_T c2_i740;
  static real_T c2_yc_a[5184];
  int32_T c2_i741;
  real_T c2_mc_b[72];
  int32_T c2_i742;
  real_T c2_c_rd[72];
  int32_T c2_i743;
  int32_T c2_i744;
  real_T c2_cd_y[72];
  real_T c2_k_u;
  const mxArray *c2_dd_y = NULL;
  int32_T c2_jj;
  real_T c2_ad_a;
  int32_T c2_i745;
  int32_T c2_i746;
  int32_T c2_i747;
  int32_T c2_i748;
  real_T c2_b_zFar[40];
  int32_T c2_i749;
  static real_T c2_c_P[1760];
  int32_T c2_i750;
  real_T c2_c_Fx[12];
  int32_T c2_i751;
  real_T c2_c_Fu[4];
  int32_T c2_i752;
  real_T c2_c_Ff[12];
  int32_T c2_i753;
  real_T c2_p_switches[9];
  int32_T c2_i754;
  int32_T c2_i755;
  boolean_T c2_b_iFar[44];
  real_T c2_bd_a;
  real_T c2_g_A;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_cd_a;
  int32_T c2_i756;
  int32_T c2_i757;
  int32_T c2_i758;
  real_T c2_dd_a;
  int32_T c2_i759;
  int32_T c2_i760;
  int32_T c2_i761;
  int32_T c2_i762;
  real_T c2_b_zNew[40];
  int32_T c2_i763;
  static real_T c2_d_P[1760];
  int32_T c2_i764;
  real_T c2_d_Fx[12];
  int32_T c2_i765;
  real_T c2_d_Fu[4];
  int32_T c2_i766;
  real_T c2_d_Ff[12];
  int32_T c2_i767;
  real_T c2_q_switches[9];
  int32_T c2_i768;
  int32_T c2_i769;
  real_T c2_b_iNew[44];
  real_T c2_dv31[44];
  int32_T c2_i770;
  int32_T c2_i771;
  int32_T c2_i772;
  int32_T c2_i773;
  int32_T c2_i774;
  static real_T c2_nc_b[1760];
  int32_T c2_i775;
  real_T c2_ed_y[44];
  int32_T c2_i776;
  real_T c2_b_nuNew[32];
  int32_T c2_i777;
  static real_T c2_f_CT[1280];
  int32_T c2_i778;
  real_T c2_h_AT[9];
  int32_T c2_i779;
  real_T c2_f_BT[3];
  int32_T c2_i780;
  real_T c2_f_EfT[6];
  int32_T c2_i781;
  real_T c2_r_switches[9];
  int32_T c2_i782;
  int32_T c2_i783;
  real_T c2_c_zNew[40];
  int32_T c2_i784;
  static real_T c2_c_Ps[1600];
  int32_T c2_i785;
  real_T c2_c_Fxs[12];
  int32_T c2_i786;
  real_T c2_c_Fus[4];
  int32_T c2_i787;
  real_T c2_c_hs[40];
  int32_T c2_i788;
  real_T c2_s_switches[9];
  int32_T c2_i789;
  int32_T c2_i790;
  int32_T c2_i791;
  real_T c2_b_dsNew[40];
  int32_T c2_i792;
  static real_T c2_c_PsT[1600];
  int32_T c2_i793;
  real_T c2_c_FxsT[12];
  int32_T c2_i794;
  real_T c2_c_FusT[4];
  int32_T c2_i795;
  real_T c2_t_switches[9];
  int32_T c2_i796;
  int32_T c2_i797;
  real_T c2_d_zNew[40];
  int32_T c2_i798;
  real_T c2_oc_b[32];
  int32_T c2_i799;
  real_T c2_h_A[9];
  int32_T c2_i800;
  real_T c2_d_B[3];
  int32_T c2_i801;
  static real_T c2_d_C[1280];
  int32_T c2_i802;
  real_T c2_d_Ef[6];
  int32_T c2_i803;
  real_T c2_u_switches[9];
  real_T c2_dv32[32];
  int32_T c2_i804;
  int32_T c2_i805;
  real_T c2_b_rdNew[40];
  int32_T c2_i806;
  real_T c2_b_rpNew[32];
  real_T c2_b_rdMagNew[2];
  real_T c2_pc_b;
  real_T c2_b_jj;
  int32_T c2_c_jj;
  real_T c2_ed_a;
  int32_T c2_i807;
  int32_T c2_i808;
  int32_T c2_i809;
  real_T c2_fd_a;
  int32_T c2_i810;
  int32_T c2_i811;
  int32_T c2_i812;
  int32_T c2_i813;
  real_T c2_e_zNew[40];
  int32_T c2_i814;
  static real_T c2_e_P[1760];
  int32_T c2_i815;
  real_T c2_e_Fx[12];
  int32_T c2_i816;
  real_T c2_e_Fu[4];
  int32_T c2_i817;
  real_T c2_e_Ff[12];
  int32_T c2_i818;
  real_T c2_v_switches[9];
  int32_T c2_i819;
  int32_T c2_i820;
  real_T c2_c_iNew[44];
  real_T c2_dv33[44];
  int32_T c2_i821;
  int32_T c2_i822;
  int32_T c2_i823;
  int32_T c2_i824;
  int32_T c2_i825;
  static real_T c2_qc_b[1760];
  int32_T c2_i826;
  real_T c2_fd_y[44];
  int32_T c2_i827;
  real_T c2_c_nuNew[32];
  int32_T c2_i828;
  static real_T c2_g_CT[1280];
  int32_T c2_i829;
  real_T c2_i_AT[9];
  int32_T c2_i830;
  real_T c2_g_BT[3];
  int32_T c2_i831;
  real_T c2_g_EfT[6];
  int32_T c2_i832;
  real_T c2_w_switches[9];
  int32_T c2_i833;
  int32_T c2_i834;
  real_T c2_f_zNew[40];
  int32_T c2_i835;
  static real_T c2_d_Ps[1600];
  int32_T c2_i836;
  real_T c2_d_Fxs[12];
  int32_T c2_i837;
  real_T c2_d_Fus[4];
  int32_T c2_i838;
  real_T c2_d_hs[40];
  int32_T c2_i839;
  real_T c2_x_switches[9];
  int32_T c2_i840;
  int32_T c2_i841;
  int32_T c2_i842;
  real_T c2_c_dsNew[40];
  int32_T c2_i843;
  static real_T c2_d_PsT[1600];
  int32_T c2_i844;
  real_T c2_d_FxsT[12];
  int32_T c2_i845;
  real_T c2_d_FusT[4];
  int32_T c2_i846;
  real_T c2_y_switches[9];
  int32_T c2_i847;
  int32_T c2_i848;
  real_T c2_g_zNew[40];
  int32_T c2_i849;
  real_T c2_rc_b[32];
  int32_T c2_i850;
  real_T c2_i_A[9];
  int32_T c2_i851;
  real_T c2_e_B[3];
  int32_T c2_i852;
  static real_T c2_e_C[1280];
  int32_T c2_i853;
  real_T c2_e_Ef[6];
  int32_T c2_i854;
  real_T c2_ab_switches[9];
  real_T c2_dv34[32];
  int32_T c2_i855;
  int32_T c2_i856;
  real_T c2_c_rdNew[40];
  int32_T c2_i857;
  real_T c2_c_rpNew[32];
  real_T c2_c_rdMagNew[2];
  real_T c2_sc_b;
  real_T c2_gd_y;
  real_T c2_gd_a;
  real_T c2_tc_b;
  real_T c2_hd_y;
  int32_T c2_i858;
  int32_T c2_i859;
  int32_T c2_i860;
  int32_T c2_i861;
  int32_T c2_i862;
  int32_T c2_i863;
  int32_T c2_i864;
  real_T c2_hd_a;
  real_T c2_id_a;
  real_T c2_jd_a;
  int32_T c2_i865;
  int32_T c2_i866;
  real_T *c2_b_R;
  real_T (*c2_e_z)[40];
  real_T (*c2_b_info)[4];
  real_T (*c2_e_Fus)[4];
  real_T (*c2_e_Fxs)[12];
  real_T (*c2_f_Ef)[6];
  real_T (*c2_e_hs)[40];
  real_T (*c2_e_Ps)[1600];
  real_T (*c2_b_opts)[8];
  real_T (*c2_b_Qf)[9];
  real_T (*c2_b_Q)[9];
  real_T (*c2_f_Ff)[12];
  real_T (*c2_f_Fu)[4];
  real_T (*c2_f_Fx)[12];
  real_T (*c2_f_B)[3];
  real_T (*c2_j_A)[9];
  real_T (*c2_c_z0)[40];
  real_T (*c2_uc_b)[32];
  real_T (*c2_f_C)[1280];
  real_T (*c2_d_h)[44];
  real_T (*c2_f_P)[1760];
  real_T (*c2_b_g)[40];
  real_T (*c2_b_H)[1600];
  int32_T exitg1;
  int32_T exitg2;
  boolean_T exitg3;
  boolean_T exitg4;
  c2_e_Fus = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 20);
  c2_e_Fxs = (real_T (*)[12])ssGetInputPortSignal(chartInstance->S, 19);
  c2_f_Ef = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 18);
  c2_e_hs = (real_T (*)[40])ssGetInputPortSignal(chartInstance->S, 17);
  c2_e_Ps = (real_T (*)[1600])ssGetInputPortSignal(chartInstance->S, 16);
  c2_b_opts = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 15);
  c2_b_info = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_b_Qf = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 14);
  c2_b_R = (real_T *)ssGetInputPortSignal(chartInstance->S, 13);
  c2_b_Q = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 12);
  c2_f_Ff = (real_T (*)[12])ssGetInputPortSignal(chartInstance->S, 11);
  c2_f_Fu = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 10);
  c2_f_Fx = (real_T (*)[12])ssGetInputPortSignal(chartInstance->S, 9);
  c2_f_B = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 8);
  c2_j_A = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 7);
  c2_c_z0 = (real_T (*)[40])ssGetInputPortSignal(chartInstance->S, 6);
  c2_uc_b = (real_T (*)[32])ssGetInputPortSignal(chartInstance->S, 5);
  c2_f_C = (real_T (*)[1280])ssGetInputPortSignal(chartInstance->S, 4);
  c2_d_h = (real_T (*)[44])ssGetInputPortSignal(chartInstance->S, 3);
  c2_f_P = (real_T (*)[1760])ssGetInputPortSignal(chartInstance->S, 2);
  c2_b_g = (real_T (*)[40])ssGetInputPortSignal(chartInstance->S, 1);
  c2_e_z = (real_T (*)[40])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_H = (real_T (*)[1600])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *c2_b_R;
  for (c2_i26 = 0; c2_i26 < 1600; c2_i26++) {
    c2_H[c2_i26] = (*c2_b_H)[c2_i26];
  }

  for (c2_i27 = 0; c2_i27 < 40; c2_i27++) {
    c2_g[c2_i27] = (*c2_b_g)[c2_i27];
  }

  for (c2_i28 = 0; c2_i28 < 1760; c2_i28++) {
    c2_P[c2_i28] = (*c2_f_P)[c2_i28];
  }

  for (c2_i29 = 0; c2_i29 < 44; c2_i29++) {
    c2_h[c2_i29] = (*c2_d_h)[c2_i29];
  }

  for (c2_i30 = 0; c2_i30 < 1280; c2_i30++) {
    c2_C[c2_i30] = (*c2_f_C)[c2_i30];
  }

  for (c2_i31 = 0; c2_i31 < 32; c2_i31++) {
    c2_b[c2_i31] = (*c2_uc_b)[c2_i31];
  }

  for (c2_i32 = 0; c2_i32 < 40; c2_i32++) {
    c2_z0[c2_i32] = (*c2_c_z0)[c2_i32];
  }

  for (c2_i33 = 0; c2_i33 < 9; c2_i33++) {
    c2_A[c2_i33] = (*c2_j_A)[c2_i33];
  }

  for (c2_i34 = 0; c2_i34 < 3; c2_i34++) {
    c2_B[c2_i34] = (*c2_f_B)[c2_i34];
  }

  for (c2_i35 = 0; c2_i35 < 12; c2_i35++) {
    c2_Fx[c2_i35] = (*c2_f_Fx)[c2_i35];
  }

  for (c2_i36 = 0; c2_i36 < 4; c2_i36++) {
    c2_Fu[c2_i36] = (*c2_f_Fu)[c2_i36];
  }

  for (c2_i37 = 0; c2_i37 < 12; c2_i37++) {
    c2_Ff[c2_i37] = (*c2_f_Ff)[c2_i37];
  }

  for (c2_i38 = 0; c2_i38 < 9; c2_i38++) {
    c2_Q[c2_i38] = (*c2_b_Q)[c2_i38];
  }

  c2_R = c2_hoistedGlobal;
  for (c2_i39 = 0; c2_i39 < 9; c2_i39++) {
    c2_Qf[c2_i39] = (*c2_b_Qf)[c2_i39];
  }

  for (c2_i40 = 0; c2_i40 < 8; c2_i40++) {
    c2_opts[c2_i40] = (*c2_b_opts)[c2_i40];
  }

  for (c2_i41 = 0; c2_i41 < 1600; c2_i41++) {
    c2_Ps[c2_i41] = (*c2_e_Ps)[c2_i41];
  }

  for (c2_i42 = 0; c2_i42 < 40; c2_i42++) {
    c2_hs[c2_i42] = (*c2_e_hs)[c2_i42];
  }

  for (c2_i43 = 0; c2_i43 < 6; c2_i43++) {
    c2_Ef[c2_i43] = (*c2_f_Ef)[c2_i43];
  }

  for (c2_i44 = 0; c2_i44 < 12; c2_i44++) {
    c2_Fxs[c2_i44] = (*c2_e_Fxs)[c2_i44];
  }

  for (c2_i45 = 0; c2_i45 < 4; c2_i45++) {
    c2_Fus[c2_i45] = (*c2_e_Fus)[c2_i45];
  }

  sf_debug_symbol_scope_push_eml(0U, 112U, 112U, c2_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c2_check_d, 0U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_checkRp, 1U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_checkPhiInv, 2U,
    c2_h_sf_marshallOut, c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_checkY, 3U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_checkBeta, 4U,
    c2_h_sf_marshallOut, c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_checkL, 5U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_check_t, 6U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_check_dnu, 7U,
    c2_h_sf_marshallOut, c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_checkNewton, 8U,
    c2_h_sf_marshallOut, c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_checkInv, 9U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_totBackTracks, 10U,
    c2_h_sf_marshallOut, c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c2_n, 11U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_m, 12U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_nz, 13U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_ne, 14U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_ni, 15U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c2_ns, 16U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_ell, 17U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_ellf, 18U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_ellef, 19U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_T, 20U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_ells, 21U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_kappa, 22U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c2_rho, 23U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_numBarrIters, 24U,
    c2_h_sf_marshallOut, c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c2_nop, 25U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_flagPhiIsDiag, 26U,
    c2_w_sf_marshallOut, c2_q_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_numNewtonIters, 27U,
    c2_h_sf_marshallOut, c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_flagUseSoftCons, 28U,
    c2_w_sf_marshallOut, c2_q_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_flagChecking, 29U,
    c2_w_sf_marshallOut, c2_q_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_flagNoPade, 30U,
    c2_w_sf_marshallOut, c2_q_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_switches, 31U, c2_v_sf_marshallOut,
    c2_p_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_kappaPt, 32U, c2_u_sf_marshallOut,
    c2_o_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_kappaPtSq, 33U,
    c2_u_sf_marshallOut, c2_o_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_rhoPstSq, 34U, c2_e_sf_marshallOut,
    c2_i_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_diagTwoH, 35U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_blkQR, 36U, c2_o_sf_marshallOut,
    c2_h_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_FxsT, 37U, c2_t_sf_marshallOut,
    c2_n_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_FusT, 38U, c2_s_sf_marshallOut,
    c2_m_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_AT, 39U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_BT, 40U, c2_r_sf_marshallOut,
    c2_l_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_CT, 41U, c2_q_sf_marshallOut,
    c2_k_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_EfT, 42U, c2_p_sf_marshallOut,
    c2_j_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_PsT, 43U, c2_e_sf_marshallOut,
    c2_i_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_es, 44U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_ds, 45U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_dsNew, 46U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_esNew, 47U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_dz, 48U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_phi, 49U, c2_e_sf_marshallOut,
    c2_i_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_dhats, 50U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_zTail, 51U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_initSolChoice, 52U,
    c2_h_sf_marshallOut, c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c2_nu, 53U, c2_j_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_d, 54U, c2_l_sf_marshallOut,
    c2_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_rp, 55U, c2_j_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_rpMag, 56U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_rd, 57U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_checkPsT, 58U,
    c2_h_sf_marshallOut, c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_rdMag, 59U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_rMag, 60U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_diagPhi, 61U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_phiInv, 62U, c2_e_sf_marshallOut,
    c2_i_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_blkInv, 63U, c2_o_sf_marshallOut,
    c2_h_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Y, 64U, c2_n_sf_marshallOut,
    c2_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_tmp, 65U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_PhiInvRd, 66U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_rhs, 67U, c2_j_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_L, 68U, c2_n_sf_marshallOut,
    c2_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_t, 69U, c2_j_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_dnu, 70U, c2_j_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_v, 71U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_checkV, 72U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_sMax, 73U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_zFar, 74U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_iFar, 75U, c2_l_sf_marshallOut,
    c2_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_s, 76U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_zNew, 77U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_nuNew, 78U, c2_j_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_iNew, 79U, c2_l_sf_marshallOut,
    c2_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_dNew, 80U, c2_l_sf_marshallOut,
    c2_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_rdNew, 81U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_rpNew, 82U, c2_j_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_rdMagNew, 83U,
    c2_h_sf_marshallOut, c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_rpMagNew, 84U,
    c2_h_sf_marshallOut, c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_rMagNew, 85U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_gradRmag, 86U,
    c2_h_sf_marshallOut, c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 87U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 88U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c2_H, 89U, c2_e_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_g, 90U, c2_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_P, 91U, c2_m_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_h, 92U, c2_l_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_C, 93U, c2_k_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_b, 94U, c2_j_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_z0, 95U, c2_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_A, 96U, c2_g_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_B, 97U, c2_i_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Fx, 98U, c2_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Fu, 99U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Ff, 100U, c2_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Q, 101U, c2_g_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_R, 102U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Qf, 103U, c2_g_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_opts, 104U, c2_f_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Ps, 105U, c2_e_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_hs, 106U, c2_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Ef, 107U, c2_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Fxs, 108U, c2_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_Fus, 109U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_z, 110U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_info, 111U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 17);
  c2_check_d = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 18);
  c2_checkRp = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 19);
  c2_checkPhiInv = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 20);
  c2_checkY = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 21);
  c2_checkBeta = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 22);
  c2_checkL = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 23);
  c2_check_t = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 24);
  c2_check_dnu = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 25);
  c2_checkNewton = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 26);
  c2_checkInv = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
  c2_totBackTracks = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 31);
  c2_n = 3.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 32);
  c2_m = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 33);
  c2_nz = 40.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 34);
  c2_ne = 32.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 35);
  c2_ni = 44.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 36);
  c2_ns = 40.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 37);
  c2_ell = 4.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 39);
  c2_ellf = 4.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 42);
  CV_EML_IF(0, 1, 0, 3.0 == c2_n);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
  c2_ellef = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 51);
  c2_T = 10.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 53);
  c2_ells = 4.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 56);
  CV_EML_IF(0, 1, 1, c2_m == 3.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 58);
  CV_EML_IF(0, 1, 2, c2_m == 2.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 65);
  c2_kappa = 0.005;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 68);
  c2_rho = 10.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 71);
  c2_numBarrIters = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 76);
  c2_nop = 8.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 79);
  CV_EML_IF(0, 1, 3, c2_nop >= 1.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 80);
  c2_flagPhiIsDiag = (c2_opts[0] > 0.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 86);
  CV_EML_IF(0, 1, 4, c2_nop >= 2.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 87);
  c2_numNewtonIters = c2_opts[1];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 93);
  CV_EML_IF(0, 1, 5, c2_nop >= 3.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 94);
  c2_flagUseSoftCons = (c2_opts[2] > 0.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 100);
  CV_EML_IF(0, 1, 6, c2_nop >= 4.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 101);
  c2_flagChecking = (c2_opts[3] > 0.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 107);
  CV_EML_IF(0, 1, 7, c2_nop >= 5.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 108);
  c2_flagNoPade = (c2_opts[4] > 0.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 114);
  CV_EML_IF(0, 1, 8, c2_nop >= 6.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 115);
  c2_b_b = 1.0 - (real_T)(c2_opts[5] > 0.0);
  for (c2_i46 = 0; c2_i46 < 9; c2_i46++) {
    c2_switches[c2_i46] = c2_a[c2_i46] * c2_b_b;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 121);
  CV_EML_IF(0, 1, 9, c2_nop >= 7.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 122);
  if (CV_EML_IF(0, 1, 10, c2_opts[6] > 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 123);
    c2_kappa = c2_opts[6];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 128U);
  CV_EML_IF(0, 1, 11, c2_nop >= 8.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 129U);
  if (CV_EML_IF(0, 1, 12, c2_opts[7] > 1.0)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 130U);
    c2_numBarrIters = c2_opts[7];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 137U);
  c2_b_a = c2_kappa;
  c2_i47 = 0;
  for (c2_i48 = 0; c2_i48 < 44; c2_i48++) {
    c2_i49 = 0;
    for (c2_i50 = 0; c2_i50 < 40; c2_i50++) {
      c2_c_b[c2_i50 + c2_i47] = c2_P[c2_i49 + c2_i48];
      c2_i49 += 44;
    }

    c2_i47 += 40;
  }

  for (c2_i51 = 0; c2_i51 < 1760; c2_i51++) {
    c2_kappaPt[c2_i51] = c2_b_a * c2_c_b[c2_i51];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 138U);
  c2_i52 = 0;
  for (c2_i53 = 0; c2_i53 < 44; c2_i53++) {
    c2_i54 = 0;
    for (c2_i55 = 0; c2_i55 < 40; c2_i55++) {
      c2_kappaPtSq[c2_i55 + c2_i52] = c2_kappaPt[c2_i55 + c2_i52] * c2_P[c2_i54
        + c2_i53];
      c2_i54 += 44;
    }

    c2_i52 += 40;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 139U);
  c2_i56 = 0;
  for (c2_i57 = 0; c2_i57 < 40; c2_i57++) {
    c2_i58 = 0;
    for (c2_i59 = 0; c2_i59 < 40; c2_i59++) {
      c2_d_b[c2_i59 + c2_i56] = c2_Ps[c2_i58 + c2_i57];
      c2_i58 += 40;
    }

    c2_i56 += 40;
  }

  for (c2_i60 = 0; c2_i60 < 1600; c2_i60++) {
    c2_d_b[c2_i60] *= 10.0;
  }

  c2_i61 = 0;
  for (c2_i62 = 0; c2_i62 < 40; c2_i62++) {
    c2_i63 = 0;
    for (c2_i64 = 0; c2_i64 < 40; c2_i64++) {
      c2_rhoPstSq[c2_i64 + c2_i61] = c2_d_b[c2_i64 + c2_i61] * c2_Ps[c2_i63 +
        c2_i62];
      c2_i63 += 40;
    }

    c2_i61 += 40;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 140U);
  for (c2_i65 = 0; c2_i65 < 1600; c2_i65++) {
    c2_d_b[c2_i65] = c2_H[c2_i65];
  }

  for (c2_i66 = 0; c2_i66 < 1600; c2_i66++) {
    c2_d_b[c2_i66] *= 2.0;
  }

  for (c2_i67 = 0; c2_i67 < 1600; c2_i67++) {
    c2_e_b[c2_i67] = c2_d_b[c2_i67];
  }

  c2_diag(chartInstance, c2_e_b, c2_dv2);
  for (c2_i68 = 0; c2_i68 < 40; c2_i68++) {
    c2_diagTwoH[c2_i68] = c2_dv2[c2_i68];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 143U);
  for (c2_i69 = 0; c2_i69 < 16; c2_i69++) {
    c2_blkQR[c2_i69] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 144U);
  c2_i70 = 0;
  c2_i71 = 0;
  for (c2_i72 = 0; c2_i72 < 3; c2_i72++) {
    for (c2_i73 = 0; c2_i73 < 3; c2_i73++) {
      c2_blkQR[c2_i73 + c2_i70] = c2_Q[c2_i73 + c2_i71];
    }

    c2_i70 += 4;
    c2_i71 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 145U);
  c2_realmax(chartInstance);
  c2_realmax(chartInstance);
  c2_blkQR[15] = c2_R;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 146U);
  c2_i74 = 0;
  for (c2_i75 = 0; c2_i75 < 4; c2_i75++) {
    c2_i76 = 0;
    for (c2_i77 = 0; c2_i77 < 3; c2_i77++) {
      c2_FxsT[c2_i77 + c2_i74] = c2_Fxs[c2_i76 + c2_i75];
      c2_i76 += 4;
    }

    c2_i74 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 147U);
  for (c2_i78 = 0; c2_i78 < 4; c2_i78++) {
    c2_FusT[c2_i78] = c2_Fus[c2_i78];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 148U);
  c2_i79 = 0;
  for (c2_i80 = 0; c2_i80 < 3; c2_i80++) {
    c2_i81 = 0;
    for (c2_i82 = 0; c2_i82 < 3; c2_i82++) {
      c2_AT[c2_i82 + c2_i79] = c2_A[c2_i81 + c2_i80];
      c2_i81 += 3;
    }

    c2_i79 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 149U);
  for (c2_i83 = 0; c2_i83 < 3; c2_i83++) {
    c2_BT[c2_i83] = c2_B[c2_i83];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 150U);
  c2_i84 = 0;
  for (c2_i85 = 0; c2_i85 < 32; c2_i85++) {
    c2_i86 = 0;
    for (c2_i87 = 0; c2_i87 < 40; c2_i87++) {
      c2_CT[c2_i87 + c2_i84] = c2_C[c2_i86 + c2_i85];
      c2_i86 += 32;
    }

    c2_i84 += 40;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 151U);
  c2_i88 = 0;
  for (c2_i89 = 0; c2_i89 < 2; c2_i89++) {
    c2_i90 = 0;
    for (c2_i91 = 0; c2_i91 < 3; c2_i91++) {
      c2_EfT[c2_i91 + c2_i88] = c2_Ef[c2_i90 + c2_i89];
      c2_i90 += 2;
    }

    c2_i88 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 152U);
  c2_i92 = 0;
  for (c2_i93 = 0; c2_i93 < 40; c2_i93++) {
    c2_i94 = 0;
    for (c2_i95 = 0; c2_i95 < 40; c2_i95++) {
      c2_PsT[c2_i95 + c2_i92] = c2_Ps[c2_i94 + c2_i93];
      c2_i94 += 40;
    }

    c2_i92 += 40;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 155U);
  for (c2_i96 = 0; c2_i96 < 40; c2_i96++) {
    c2_es[c2_i96] = c2_hs[c2_i96];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 156U);
  for (c2_i97 = 0; c2_i97 < 40; c2_i97++) {
    c2_ds[c2_i97] = c2_hs[c2_i97];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 157U);
  for (c2_i98 = 0; c2_i98 < 40; c2_i98++) {
    c2_dsNew[c2_i98] = c2_ds[c2_i98];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 158U);
  for (c2_i99 = 0; c2_i99 < 40; c2_i99++) {
    c2_esNew[c2_i99] = c2_es[c2_i99];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 161U);
  for (c2_i100 = 0; c2_i100 < 40; c2_i100++) {
    c2_dz[c2_i100] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 162U);
  for (c2_i101 = 0; c2_i101 < 1600; c2_i101++) {
    c2_phi[c2_i101] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 163U);
  for (c2_i102 = 0; c2_i102 < 40; c2_i102++) {
    c2_dhats[c2_i102] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 169U);
  CV_EML_IF(0, 1, 13, c2_m == 1.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 171U);
  c2_realmax(chartInstance);
  c2_b_nz = c2_nz - c2_n;
  for (c2_i103 = 0; c2_i103 < 3; c2_i103++) {
    c2_b_z0[c2_i103] = c2_z0[_SFD_EML_ARRAY_BOUNDS_CHECK("z0", (int32_T)
      _SFD_INTEGER_CHECK("nz - n + (1:n)", c2_b_nz + (1.0 + (real_T)c2_i103)), 1,
      40, 1, 0) - 1];
  }

  for (c2_i104 = 0; c2_i104 < 9; c2_i104++) {
    c2_b_A[c2_i104] = c2_A[c2_i104];
  }

  for (c2_i105 = 0; c2_i105 < 9; c2_i105++) {
    c2_b_switches[c2_i105] = c2_switches[c2_i105];
  }

  c2_preMultByA(chartInstance, c2_b_z0, c2_b_A, c2_b_switches, c2_c_a);
  for (c2_i106 = 0; c2_i106 < 36; c2_i106++) {
    c2_zTail[c2_i106] = c2_z0[c2_i106 + 4];
  }

  c2_zTail[36] = 0.0;
  for (c2_i107 = 0; c2_i107 < 3; c2_i107++) {
    c2_zTail[c2_i107 + 37] = c2_c_a[c2_i107];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 179U);
  for (c2_i108 = 0; c2_i108 < 1760; c2_i108++) {
    c2_d_a[c2_i108] = c2_P[c2_i108];
  }

  for (c2_i109 = 0; c2_i109 < 40; c2_i109++) {
    c2_f_b[c2_i109] = c2_zTail[c2_i109];
  }

  c2_b_eml_scalar_eg(chartInstance);
  c2_b_eml_scalar_eg(chartInstance);
  for (c2_i110 = 0; c2_i110 < 44; c2_i110++) {
    c2_y[c2_i110] = 0.0;
  }

  for (c2_i111 = 0; c2_i111 < 1760; c2_i111++) {
    c2_e_a[c2_i111] = c2_d_a[c2_i111];
  }

  for (c2_i112 = 0; c2_i112 < 40; c2_i112++) {
    c2_g_b[c2_i112] = c2_f_b[c2_i112];
  }

  c2_n_eml_xgemm(chartInstance, c2_e_a, c2_g_b, c2_y);
  for (c2_i113 = 0; c2_i113 < 44; c2_i113++) {
    c2_b_y[c2_i113] = (c2_y[c2_i113] < c2_h[c2_i113]);
  }

  if (CV_EML_IF(0, 1, 14, c2_all(chartInstance, c2_b_y))) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 182U);
    for (c2_i114 = 0; c2_i114 < 40; c2_i114++) {
      c2_z[c2_i114] = c2_zTail[c2_i114];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 183U);
    c2_initSolChoice = 1.0;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 191U);
    for (c2_i115 = 0; c2_i115 < 40; c2_i115++) {
      c2_z[c2_i115] = c2_zTail[c2_i115];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 194U);
    CV_EML_IF(0, 1, 15, c2_m > 1.0);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 199U);
    for (c2_i116 = 0; c2_i116 < 1760; c2_i116++) {
      c2_d_a[c2_i116] = c2_P[c2_i116];
    }

    for (c2_i117 = 0; c2_i117 < 40; c2_i117++) {
      c2_f_b[c2_i117] = c2_z[c2_i117];
    }

    c2_b_eml_scalar_eg(chartInstance);
    c2_b_eml_scalar_eg(chartInstance);
    for (c2_i118 = 0; c2_i118 < 44; c2_i118++) {
      c2_y[c2_i118] = 0.0;
    }

    for (c2_i119 = 0; c2_i119 < 1760; c2_i119++) {
      c2_f_a[c2_i119] = c2_d_a[c2_i119];
    }

    for (c2_i120 = 0; c2_i120 < 40; c2_i120++) {
      c2_h_b[c2_i120] = c2_f_b[c2_i120];
    }

    c2_n_eml_xgemm(chartInstance, c2_f_a, c2_h_b, c2_y);
    for (c2_i121 = 0; c2_i121 < 44; c2_i121++) {
      c2_c_y[c2_i121] = (c2_y[c2_i121] < c2_h[c2_i121]);
    }

    if (CV_EML_IF(0, 1, 16, c2_all(chartInstance, c2_c_y))) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 202U);
      c2_initSolChoice = 4.0;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 204U);
      for (c2_i122 = 0; c2_i122 < 1760; c2_i122++) {
        c2_d_a[c2_i122] = c2_P[c2_i122];
      }

      for (c2_i123 = 0; c2_i123 < 40; c2_i123++) {
        c2_f_b[c2_i123] = c2_z0[c2_i123];
      }

      c2_b_eml_scalar_eg(chartInstance);
      c2_b_eml_scalar_eg(chartInstance);
      for (c2_i124 = 0; c2_i124 < 44; c2_i124++) {
        c2_y[c2_i124] = 0.0;
      }

      for (c2_i125 = 0; c2_i125 < 1760; c2_i125++) {
        c2_g_a[c2_i125] = c2_d_a[c2_i125];
      }

      for (c2_i126 = 0; c2_i126 < 40; c2_i126++) {
        c2_i_b[c2_i126] = c2_f_b[c2_i126];
      }

      c2_n_eml_xgemm(chartInstance, c2_g_a, c2_i_b, c2_y);
      for (c2_i127 = 0; c2_i127 < 44; c2_i127++) {
        c2_d_y[c2_i127] = (c2_y[c2_i127] < c2_h[c2_i127]);
      }

      if (CV_EML_IF(0, 1, 17, c2_all(chartInstance, c2_d_y))) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 207U);
        for (c2_i128 = 0; c2_i128 < 40; c2_i128++) {
          c2_z[c2_i128] = c2_z0[c2_i128];
        }

        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 208U);
        c2_initSolChoice = 2.0;
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 210U);
        for (c2_i129 = 0; c2_i129 < 44; c2_i129++) {
          c2_bv0[c2_i129] = (0.0 < c2_h[c2_i129]);
        }

        if (CV_EML_IF(0, 1, 18, c2_all(chartInstance, c2_bv0))) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 213U);
          for (c2_i130 = 0; c2_i130 < 40; c2_i130++) {
            c2_z[c2_i130] = 0.0;
          }

          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 214U);
          c2_initSolChoice = 3.0;
        } else {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 219U);
          for (c2_i131 = 0; c2_i131 < 40; c2_i131++) {
            c2_z[c2_i131] = 0.0001;
          }

          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 220U);
          c2_initSolChoice = 0.0;
        }
      }
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 227U);
  if (CV_EML_IF(0, 1, 19, c2_flagChecking)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 228U);
    sf_mex_printf("%s =\\n", "initSolChoice");
    c2_u = c2_initSolChoice;
    c2_e_y = NULL;
    sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
    sf_mex_call_debug("disp", 0U, 1U, 14, c2_e_y);
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 234U);
  for (c2_i132 = 0; c2_i132 < 32; c2_i132++) {
    c2_nu[c2_i132] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 237U);
  for (c2_i133 = 0; c2_i133 < 40; c2_i133++) {
    c2_b_z[c2_i133] = c2_z[c2_i133];
  }

  for (c2_i134 = 0; c2_i134 < 1760; c2_i134++) {
    c2_b_P[c2_i134] = c2_P[c2_i134];
  }

  for (c2_i135 = 0; c2_i135 < 12; c2_i135++) {
    c2_b_Fx[c2_i135] = c2_Fx[c2_i135];
  }

  for (c2_i136 = 0; c2_i136 < 4; c2_i136++) {
    c2_b_Fu[c2_i136] = c2_Fu[c2_i136];
  }

  for (c2_i137 = 0; c2_i137 < 12; c2_i137++) {
    c2_b_Ff[c2_i137] = c2_Ff[c2_i137];
  }

  for (c2_i138 = 0; c2_i138 < 9; c2_i138++) {
    c2_c_switches[c2_i138] = c2_switches[c2_i138];
  }

  c2_multByP(chartInstance, c2_b_z, c2_b_P, c2_b_Fx, c2_b_Fu, c2_b_Ff,
             c2_c_switches, c2_y);
  for (c2_i139 = 0; c2_i139 < 44; c2_i139++) {
    c2_b_h[c2_i139] = c2_h[c2_i139] - c2_y[c2_i139];
  }

  c2_rdivide(chartInstance, 1.0, c2_b_h, c2_dv3);
  for (c2_i140 = 0; c2_i140 < 44; c2_i140++) {
    c2_d[c2_i140] = c2_dv3[c2_i140];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 240U);
  for (c2_i141 = 0; c2_i141 < 40; c2_i141++) {
    c2_c_z[c2_i141] = c2_z[c2_i141];
  }

  for (c2_i142 = 0; c2_i142 < 32; c2_i142++) {
    c2_j_b[c2_i142] = c2_b[c2_i142];
  }

  for (c2_i143 = 0; c2_i143 < 9; c2_i143++) {
    c2_c_A[c2_i143] = c2_A[c2_i143];
  }

  for (c2_i144 = 0; c2_i144 < 3; c2_i144++) {
    c2_b_B[c2_i144] = c2_B[c2_i144];
  }

  for (c2_i145 = 0; c2_i145 < 1280; c2_i145++) {
    c2_b_C[c2_i145] = c2_C[c2_i145];
  }

  for (c2_i146 = 0; c2_i146 < 6; c2_i146++) {
    c2_b_Ef[c2_i146] = c2_Ef[c2_i146];
  }

  for (c2_i147 = 0; c2_i147 < 9; c2_i147++) {
    c2_d_switches[c2_i147] = c2_switches[c2_i147];
  }

  c2_calcRp(chartInstance, c2_c_z, c2_j_b, c2_c_A, c2_b_B, c2_b_C, c2_b_Ef,
            c2_d_switches, c2_dv4);
  for (c2_i148 = 0; c2_i148 < 32; c2_i148++) {
    c2_rp[c2_i148] = c2_dv4[c2_i148];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 241U);
  for (c2_i149 = 0; c2_i149 < 32; c2_i149++) {
    c2_b_rp[c2_i149] = c2_rp[c2_i149];
  }

  c2_rpMag = c2_norm(chartInstance, c2_b_rp);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 242U);
  for (c2_i150 = 0; c2_i150 < 1760; c2_i150++) {
    c2_c_b[c2_i150] = c2_kappaPt[c2_i150];
  }

  for (c2_i151 = 0; c2_i151 < 44; c2_i151++) {
    c2_y[c2_i151] = c2_d[c2_i151];
  }

  c2_f_eml_scalar_eg(chartInstance);
  c2_f_eml_scalar_eg(chartInstance);
  for (c2_i152 = 0; c2_i152 < 40; c2_i152++) {
    c2_f_y[c2_i152] = 0.0;
  }

  for (c2_i153 = 0; c2_i153 < 1760; c2_i153++) {
    c2_k_b[c2_i153] = c2_c_b[c2_i153];
  }

  for (c2_i154 = 0; c2_i154 < 44; c2_i154++) {
    c2_g_y[c2_i154] = c2_y[c2_i154];
  }

  c2_p_eml_xgemm(chartInstance, c2_k_b, c2_g_y, c2_f_y);
  for (c2_i155 = 0; c2_i155 < 32; c2_i155++) {
    c2_dv5[c2_i155] = 0.0;
  }

  for (c2_i156 = 0; c2_i156 < 1280; c2_i156++) {
    c2_b_CT[c2_i156] = c2_CT[c2_i156];
  }

  for (c2_i157 = 0; c2_i157 < 9; c2_i157++) {
    c2_b_AT[c2_i157] = c2_AT[c2_i157];
  }

  for (c2_i158 = 0; c2_i158 < 3; c2_i158++) {
    c2_b_BT[c2_i158] = c2_BT[c2_i158];
  }

  for (c2_i159 = 0; c2_i159 < 6; c2_i159++) {
    c2_b_EfT[c2_i159] = c2_EfT[c2_i159];
  }

  for (c2_i160 = 0; c2_i160 < 9; c2_i160++) {
    c2_e_switches[c2_i160] = c2_switches[c2_i160];
  }

  c2_multByCT(chartInstance, c2_dv5, c2_b_CT, c2_b_AT, c2_b_BT, c2_b_EfT,
              c2_e_switches, c2_dv6);
  for (c2_i161 = 0; c2_i161 < 40; c2_i161++) {
    c2_rd[c2_i161] = ((c2_diagTwoH[c2_i161] * c2_z[c2_i161] + c2_g[c2_i161]) +
                      c2_f_y[c2_i161]) + c2_dv6[c2_i161];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 247U);
  if (CV_EML_IF(0, 1, 20, c2_flagUseSoftCons)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 250U);
    for (c2_i162 = 0; c2_i162 < 40; c2_i162++) {
      c2_d_z[c2_i162] = c2_z[c2_i162];
    }

    for (c2_i163 = 0; c2_i163 < 1600; c2_i163++) {
      c2_b_Ps[c2_i163] = c2_Ps[c2_i163];
    }

    for (c2_i164 = 0; c2_i164 < 12; c2_i164++) {
      c2_b_Fxs[c2_i164] = c2_Fxs[c2_i164];
    }

    for (c2_i165 = 0; c2_i165 < 4; c2_i165++) {
      c2_b_Fus[c2_i165] = c2_Fus[c2_i165];
    }

    for (c2_i166 = 0; c2_i166 < 40; c2_i166++) {
      c2_b_hs[c2_i166] = c2_hs[c2_i166];
    }

    for (c2_i167 = 0; c2_i167 < 9; c2_i167++) {
      c2_f_switches[c2_i167] = c2_switches[c2_i167];
    }

    c2_calcDs(chartInstance, c2_d_z, c2_b_Ps, c2_b_Fxs, c2_b_Fus, c2_b_hs,
              c2_flagNoPade, c2_f_switches, c2_f_b, c2_f_y);
    for (c2_i168 = 0; c2_i168 < 40; c2_i168++) {
      c2_ds[c2_i168] = c2_f_b[c2_i168];
    }

    for (c2_i169 = 0; c2_i169 < 40; c2_i169++) {
      c2_es[c2_i169] = c2_f_y[c2_i169];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 253U);
    for (c2_i170 = 0; c2_i170 < 40; c2_i170++) {
      c2_b_ds[c2_i170] = c2_ds[c2_i170];
    }

    for (c2_i171 = 0; c2_i171 < 1600; c2_i171++) {
      c2_b_PsT[c2_i171] = c2_PsT[c2_i171];
    }

    for (c2_i172 = 0; c2_i172 < 12; c2_i172++) {
      c2_b_FxsT[c2_i172] = c2_FxsT[c2_i172];
    }

    for (c2_i173 = 0; c2_i173 < 4; c2_i173++) {
      c2_b_FusT[c2_i173] = c2_FusT[c2_i173];
    }

    for (c2_i174 = 0; c2_i174 < 9; c2_i174++) {
      c2_g_switches[c2_i174] = c2_switches[c2_i174];
    }

    c2_multByPsT(chartInstance, c2_b_ds, c2_b_PsT, c2_b_FxsT, c2_b_FusT,
                 c2_g_switches, c2_dv6);
    for (c2_i175 = 0; c2_i175 < 40; c2_i175++) {
      c2_rd[c2_i175] += c2_dv6[c2_i175];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, MAX_uint8_T);
    CV_EML_IF(0, 1, 21, FALSE);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 258);
    c2_checkPsT = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 263);
  for (c2_i176 = 0; c2_i176 < 40; c2_i176++) {
    c2_b_rd[c2_i176] = c2_rd[c2_i176];
  }

  c2_rdMag = c2_b_norm(chartInstance, c2_b_rd);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 264);
  c2_b_rdMag[0] = c2_rdMag;
  c2_b_rdMag[1] = c2_rpMag;
  c2_rMag = c2_c_norm(chartInstance, c2_b_rdMag);
  c2_i177 = (int32_T)c2_numBarrIters;
  sf_debug_for_loop_vector_check(1.0, 1.0, c2_numBarrIters, mxDOUBLE_CLASS,
    c2_i177);
  c2_loop_ub = c2_i177;
  c2_ww = 0;
  while (c2_ww <= c2_loop_ub - 1) {
    CV_EML_FOR(0, 1, 0, 1);
    c2_i178 = (int32_T)c2_numNewtonIters;
    sf_debug_for_loop_vector_check(1.0, 1.0, c2_numNewtonIters, mxDOUBLE_CLASS,
      c2_i178);
    c2_b_loop_ub = c2_i178;
    c2_kk = 0;
    while (c2_kk <= c2_b_loop_ub - 1) {
      CV_EML_FOR(0, 1, 1, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 273);
      if (CV_EML_IF(0, 1, 22, c2_flagChecking)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 274);
        for (c2_i179 = 0; c2_i179 < 1760; c2_i179++) {
          c2_d_a[c2_i179] = c2_P[c2_i179];
        }

        for (c2_i180 = 0; c2_i180 < 40; c2_i180++) {
          c2_f_b[c2_i180] = c2_z[c2_i180];
        }

        c2_b_eml_scalar_eg(chartInstance);
        c2_b_eml_scalar_eg(chartInstance);
        for (c2_i181 = 0; c2_i181 < 44; c2_i181++) {
          c2_y[c2_i181] = 0.0;
        }

        for (c2_i182 = 0; c2_i182 < 1760; c2_i182++) {
          c2_h_a[c2_i182] = c2_d_a[c2_i182];
        }

        for (c2_i183 = 0; c2_i183 < 40; c2_i183++) {
          c2_l_b[c2_i183] = c2_f_b[c2_i183];
        }

        c2_n_eml_xgemm(chartInstance, c2_h_a, c2_l_b, c2_y);
        for (c2_i184 = 0; c2_i184 < 44; c2_i184++) {
          c2_c_h[c2_i184] = c2_h[c2_i184] - c2_y[c2_i184];
        }

        c2_rdivide(chartInstance, 1.0, c2_c_h, c2_y);
        for (c2_i185 = 0; c2_i185 < 44; c2_i185++) {
          c2_b_d[c2_i185] = c2_d[c2_i185] - c2_y[c2_i185];
        }

        c2_check_d = c2_d_norm(chartInstance, c2_b_d);
        sf_mex_printf("%s =\\n", "check_d");
        c2_b_u = c2_check_d;
        c2_h_y = NULL;
        sf_mex_assign(&c2_h_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0),
                      FALSE);
        sf_mex_call_debug("disp", 0U, 1U, 14, c2_h_y);
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 276);
        c2_check_d = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 280);
      if (CV_EML_IF(0, 1, 23, c2_flagChecking)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 281);
        for (c2_i186 = 0; c2_i186 < 1280; c2_i186++) {
          c2_i_a[c2_i186] = c2_C[c2_i186];
        }

        for (c2_i187 = 0; c2_i187 < 40; c2_i187++) {
          c2_f_b[c2_i187] = c2_z[c2_i187];
        }

        c2_d_eml_scalar_eg(chartInstance);
        c2_d_eml_scalar_eg(chartInstance);
        for (c2_i188 = 0; c2_i188 < 32; c2_i188++) {
          c2_i_y[c2_i188] = 0.0;
        }

        for (c2_i189 = 0; c2_i189 < 1280; c2_i189++) {
          c2_j_a[c2_i189] = c2_i_a[c2_i189];
        }

        for (c2_i190 = 0; c2_i190 < 40; c2_i190++) {
          c2_m_b[c2_i190] = c2_f_b[c2_i190];
        }

        c2_o_eml_xgemm(chartInstance, c2_j_a, c2_m_b, c2_i_y);
        for (c2_i191 = 0; c2_i191 < 32; c2_i191++) {
          c2_j_y[c2_i191] = (c2_i_y[c2_i191] - c2_b[c2_i191]) - c2_rp[c2_i191];
        }

        c2_checkRp = c2_norm(chartInstance, c2_j_y);
        sf_mex_printf("%s =\\n", "checkRp");
        c2_c_u = c2_checkRp;
        c2_k_y = NULL;
        sf_mex_assign(&c2_k_y, sf_mex_create("y", &c2_c_u, 0, 0U, 0U, 0U, 0),
                      FALSE);
        sf_mex_call_debug("disp", 0U, 1U, 14, c2_k_y);
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 283);
        c2_checkRp = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 287);
      if (CV_EML_IF(0, 1, 24, c2_flagUseSoftCons)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 289);
        for (c2_i192 = 0; c2_i192 < 40; c2_i192++) {
          c2_b_es[c2_i192] = c2_es[c2_i192];
        }

        for (c2_i193 = 0; c2_i193 < 40; c2_i193++) {
          c2_dv7[c2_i193] = (1.0 + c2_es[c2_i193]) * (1.0 + c2_es[c2_i193]);
        }

        c2_b_rdivide(chartInstance, c2_b_es, c2_dv7, c2_dv8);
        for (c2_i194 = 0; c2_i194 < 40; c2_i194++) {
          c2_dhats[c2_i194] = c2_dv8[c2_i194];
        }
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 293);
      if (CV_EML_IF(0, 1, 25, c2_flagPhiIsDiag)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 296);
        for (c2_i195 = 0; c2_i195 < 1760; c2_i195++) {
          c2_c_b[c2_i195] = c2_kappaPtSq[c2_i195];
        }

        for (c2_i196 = 0; c2_i196 < 44; c2_i196++) {
          c2_y[c2_i196] = c2_d[c2_i196] * c2_d[c2_i196];
        }

        c2_f_eml_scalar_eg(chartInstance);
        c2_f_eml_scalar_eg(chartInstance);
        for (c2_i197 = 0; c2_i197 < 40; c2_i197++) {
          c2_f_y[c2_i197] = 0.0;
        }

        for (c2_i198 = 0; c2_i198 < 1760; c2_i198++) {
          c2_n_b[c2_i198] = c2_c_b[c2_i198];
        }

        for (c2_i199 = 0; c2_i199 < 44; c2_i199++) {
          c2_l_y[c2_i199] = c2_y[c2_i199];
        }

        c2_p_eml_xgemm(chartInstance, c2_n_b, c2_l_y, c2_f_y);
        for (c2_i200 = 0; c2_i200 < 40; c2_i200++) {
          c2_diagPhi[c2_i200] = c2_diagTwoH[c2_i200] + c2_f_y[c2_i200];
        }

        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 299);
        if (CV_EML_IF(0, 1, 26, c2_flagUseSoftCons)) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 300);
          for (c2_i201 = 0; c2_i201 < 1600; c2_i201++) {
            c2_k_a[c2_i201] = c2_rhoPstSq[c2_i201];
          }

          for (c2_i202 = 0; c2_i202 < 40; c2_i202++) {
            c2_f_b[c2_i202] = c2_dhats[c2_i202];
          }

          c2_j_eml_scalar_eg(chartInstance);
          c2_j_eml_scalar_eg(chartInstance);
          for (c2_i203 = 0; c2_i203 < 40; c2_i203++) {
            c2_f_y[c2_i203] = 0.0;
          }

          for (c2_i204 = 0; c2_i204 < 1600; c2_i204++) {
            c2_l_a[c2_i204] = c2_k_a[c2_i204];
          }

          for (c2_i205 = 0; c2_i205 < 40; c2_i205++) {
            c2_o_b[c2_i205] = c2_f_b[c2_i205];
          }

          c2_r_eml_xgemm(chartInstance, c2_l_a, c2_o_b, c2_f_y);
          for (c2_i206 = 0; c2_i206 < 40; c2_i206++) {
            c2_diagPhi[c2_i206] += c2_f_y[c2_i206];
          }
        }

        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 304);
        for (c2_i207 = 0; c2_i207 < 40; c2_i207++) {
          c2_b_diagPhi[c2_i207] = c2_diagPhi[c2_i207];
        }

        c2_c_rdivide(chartInstance, 1.0, c2_b_diagPhi, c2_dv6);
        for (c2_i208 = 0; c2_i208 < 40; c2_i208++) {
          c2_dv9[c2_i208] = c2_dv6[c2_i208];
        }

        c2_b_diag(chartInstance, c2_dv9, c2_dv10);
        for (c2_i209 = 0; c2_i209 < 1600; c2_i209++) {
          c2_phiInv[c2_i209] = c2_dv10[c2_i209];
        }
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 309);
        for (c2_i210 = 0; c2_i210 < 1600; c2_i210++) {
          c2_phiInv[c2_i210] = 0.0;
        }

        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 312);
        if (CV_EML_IF(0, 1, 27, c2_flagUseSoftCons)) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 313);
          c2_p_b = c2_R;
          c2_m_y = 2.0 * c2_p_b;
          c2_m_a = c2_kappa;
          for (c2_i211 = 0; c2_i211 < 4; c2_i211++) {
            c2_q_b[c2_i211] = c2_Fu[c2_i211];
          }

          for (c2_i212 = 0; c2_i212 < 4; c2_i212++) {
            c2_q_b[c2_i212] *= c2_m_a;
          }

          for (c2_i213 = 0; c2_i213 < 4; c2_i213++) {
            c2_c_d[c2_i213] = c2_d[c2_i213] * c2_d[c2_i213];
          }

          c2_c_diag(chartInstance, c2_c_d, c2_r_b);
          c2_m_eml_scalar_eg(chartInstance);
          c2_m_eml_scalar_eg(chartInstance);
          c2_i214 = 0;
          for (c2_i215 = 0; c2_i215 < 4; c2_i215++) {
            c2_n_y[c2_i215] = 0.0;
            for (c2_i216 = 0; c2_i216 < 4; c2_i216++) {
              c2_n_y[c2_i215] += c2_q_b[c2_i216] * c2_r_b[c2_i216 + c2_i214];
            }

            c2_i214 += 4;
          }

          for (c2_i217 = 0; c2_i217 < 4; c2_i217++) {
            c2_s_b[c2_i217] = c2_Fu[c2_i217];
          }

          c2_k_eml_scalar_eg(chartInstance);
          c2_k_eml_scalar_eg(chartInstance);
          c2_o_y = 0.0;
          c2_c_eml_int_forloop_overflow_check(chartInstance);
          for (c2_k = 1; c2_k < 5; c2_k++) {
            c2_b_k = c2_k;
            c2_o_y += c2_n_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 4, 1, 0) - 1] *
              c2_s_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
              ("", (real_T)c2_b_k), 1, 4, 1, 0) - 1];
          }

          c2_n_a = c2_rho;
          for (c2_i218 = 0; c2_i218 < 4; c2_i218++) {
            c2_q_b[c2_i218] = c2_Fus[c2_i218];
          }

          for (c2_i219 = 0; c2_i219 < 4; c2_i219++) {
            c2_q_b[c2_i219] *= c2_n_a;
          }

          for (c2_i220 = 0; c2_i220 < 4; c2_i220++) {
            c2_b_dhats[c2_i220] = c2_dhats[c2_i220];
          }

          c2_c_diag(chartInstance, c2_b_dhats, c2_r_b);
          c2_m_eml_scalar_eg(chartInstance);
          c2_m_eml_scalar_eg(chartInstance);
          c2_i221 = 0;
          for (c2_i222 = 0; c2_i222 < 4; c2_i222++) {
            c2_n_y[c2_i222] = 0.0;
            for (c2_i223 = 0; c2_i223 < 4; c2_i223++) {
              c2_n_y[c2_i222] += c2_q_b[c2_i223] * c2_r_b[c2_i223 + c2_i221];
            }

            c2_i221 += 4;
          }

          for (c2_i224 = 0; c2_i224 < 4; c2_i224++) {
            c2_s_b[c2_i224] = c2_Fus[c2_i224];
          }

          c2_k_eml_scalar_eg(chartInstance);
          c2_k_eml_scalar_eg(chartInstance);
          c2_p_y = 0.0;
          c2_c_eml_int_forloop_overflow_check(chartInstance);
          for (c2_c_k = 1; c2_c_k < 5; c2_c_k++) {
            c2_d_k = c2_c_k;
            c2_p_y += c2_n_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c2_d_k), 1, 4, 1, 0) - 1] *
              c2_s_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
              ("", (real_T)c2_d_k), 1, 4, 1, 0) - 1];
          }

          c2_phiInv[0] = c2_mySymPDinv(chartInstance, (c2_m_y + c2_o_y) + c2_p_y);
        } else {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 315);
          c2_t_b = c2_R;
          c2_q_y = 2.0 * c2_t_b;
          c2_o_a = c2_kappa;
          for (c2_i225 = 0; c2_i225 < 4; c2_i225++) {
            c2_q_b[c2_i225] = c2_Fu[c2_i225];
          }

          for (c2_i226 = 0; c2_i226 < 4; c2_i226++) {
            c2_q_b[c2_i226] *= c2_o_a;
          }

          for (c2_i227 = 0; c2_i227 < 4; c2_i227++) {
            c2_d_d[c2_i227] = c2_d[c2_i227] * c2_d[c2_i227];
          }

          c2_c_diag(chartInstance, c2_d_d, c2_r_b);
          c2_m_eml_scalar_eg(chartInstance);
          c2_m_eml_scalar_eg(chartInstance);
          c2_i228 = 0;
          for (c2_i229 = 0; c2_i229 < 4; c2_i229++) {
            c2_n_y[c2_i229] = 0.0;
            for (c2_i230 = 0; c2_i230 < 4; c2_i230++) {
              c2_n_y[c2_i229] += c2_q_b[c2_i230] * c2_r_b[c2_i230 + c2_i228];
            }

            c2_i228 += 4;
          }

          for (c2_i231 = 0; c2_i231 < 4; c2_i231++) {
            c2_s_b[c2_i231] = c2_Fu[c2_i231];
          }

          c2_k_eml_scalar_eg(chartInstance);
          c2_k_eml_scalar_eg(chartInstance);
          c2_r_y = 0.0;
          c2_c_eml_int_forloop_overflow_check(chartInstance);
          for (c2_e_k = 1; c2_e_k < 5; c2_e_k++) {
            c2_f_k = c2_e_k;
            c2_r_y += c2_n_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c2_f_k), 1, 4, 1, 0) - 1] *
              c2_s_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
              ("", (real_T)c2_f_k), 1, 4, 1, 0) - 1];
          }

          c2_phiInv[0] = c2_mySymPDinv(chartInstance, c2_q_y + c2_r_y);
        }

        c2_ii = 0;
        while (c2_ii < 9) {
          c2_b_ii = 1.0 + (real_T)c2_ii;
          CV_EML_FOR(0, 1, 2, 1);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 318);
          if (CV_EML_IF(0, 1, 28, c2_flagUseSoftCons)) {
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 319);
            c2_realmax(chartInstance);
            c2_realmax(chartInstance);
            c2_realmax(chartInstance);
            for (c2_i232 = 0; c2_i232 < 16; c2_i232++) {
              c2_r_b[c2_i232] = c2_blkQR[c2_i232];
            }

            for (c2_i233 = 0; c2_i233 < 16; c2_i233++) {
              c2_r_b[c2_i233] *= 2.0;
            }

            c2_p_a = c2_kappa;
            c2_i234 = 0;
            for (c2_i235 = 0; c2_i235 < 4; c2_i235++) {
              c2_i236 = 0;
              for (c2_i237 = 0; c2_i237 < 3; c2_i237++) {
                c2_u_b[c2_i237 + c2_i234] = c2_Fx[c2_i236 + c2_i235];
                c2_i236 += 4;
              }

              c2_i234 += 4;
            }

            c2_i238 = 0;
            for (c2_i239 = 0; c2_i239 < 4; c2_i239++) {
              c2_u_b[c2_i238 + 3] = c2_Fu[c2_i239];
              c2_i238 += 4;
            }

            for (c2_i240 = 0; c2_i240 < 16; c2_i240++) {
              c2_u_b[c2_i240] *= c2_p_a;
            }

            c2_q_a = c2_b_ii;
            c2_s_y = c2_q_a * 4.0;
            c2_r_a = c2_b_ii;
            c2_t_y = c2_r_a * 4.0;
            for (c2_i241 = 0; c2_i241 < 4; c2_i241++) {
              c2_e_d[c2_i241] = c2_d[_SFD_EML_ARRAY_BOUNDS_CHECK("d", (int32_T)
                _SFD_INTEGER_CHECK("ii*ell + (1:ell)", c2_s_y + (1.0 + (real_T)
                c2_i241)), 1, 44, 1, 0) - 1] * c2_d[_SFD_EML_ARRAY_BOUNDS_CHECK(
                "d", (int32_T)_SFD_INTEGER_CHECK("ii*ell + (1:ell)", c2_t_y +
                (1.0 + (real_T)c2_i241)), 1, 44, 1, 0) - 1];
            }

            c2_c_diag(chartInstance, c2_e_d, c2_v_b);
            c2_o_eml_scalar_eg(chartInstance);
            c2_o_eml_scalar_eg(chartInstance);
            for (c2_i242 = 0; c2_i242 < 4; c2_i242++) {
              c2_i243 = 0;
              for (c2_i244 = 0; c2_i244 < 4; c2_i244++) {
                c2_u_y[c2_i243 + c2_i242] = 0.0;
                c2_i245 = 0;
                for (c2_i246 = 0; c2_i246 < 4; c2_i246++) {
                  c2_u_y[c2_i243 + c2_i242] += c2_u_b[c2_i245 + c2_i242] *
                    c2_v_b[c2_i246 + c2_i243];
                  c2_i245 += 4;
                }

                c2_i243 += 4;
              }
            }

            c2_i247 = 0;
            for (c2_i248 = 0; c2_i248 < 3; c2_i248++) {
              for (c2_i249 = 0; c2_i249 < 4; c2_i249++) {
                c2_u_b[c2_i249 + c2_i247] = c2_Fx[c2_i249 + c2_i247];
              }

              c2_i247 += 4;
            }

            for (c2_i250 = 0; c2_i250 < 4; c2_i250++) {
              c2_u_b[c2_i250 + 12] = c2_Fu[c2_i250];
            }

            c2_o_eml_scalar_eg(chartInstance);
            c2_o_eml_scalar_eg(chartInstance);
            for (c2_i251 = 0; c2_i251 < 4; c2_i251++) {
              c2_i252 = 0;
              for (c2_i253 = 0; c2_i253 < 4; c2_i253++) {
                c2_v_y[c2_i252 + c2_i251] = 0.0;
                c2_i254 = 0;
                for (c2_i255 = 0; c2_i255 < 4; c2_i255++) {
                  c2_v_y[c2_i252 + c2_i251] += c2_u_y[c2_i254 + c2_i251] *
                    c2_u_b[c2_i255 + c2_i252];
                  c2_i254 += 4;
                }

                c2_i252 += 4;
              }
            }

            c2_s_a = c2_rho;
            c2_i256 = 0;
            for (c2_i257 = 0; c2_i257 < 4; c2_i257++) {
              c2_i258 = 0;
              for (c2_i259 = 0; c2_i259 < 3; c2_i259++) {
                c2_u_b[c2_i259 + c2_i256] = c2_Fxs[c2_i258 + c2_i257];
                c2_i258 += 4;
              }

              c2_i256 += 4;
            }

            c2_i260 = 0;
            for (c2_i261 = 0; c2_i261 < 4; c2_i261++) {
              c2_u_b[c2_i260 + 3] = c2_Fus[c2_i261];
              c2_i260 += 4;
            }

            for (c2_i262 = 0; c2_i262 < 16; c2_i262++) {
              c2_u_b[c2_i262] *= c2_s_a;
            }

            c2_t_a = c2_b_ii;
            c2_w_y = c2_t_a * 4.0;
            for (c2_i263 = 0; c2_i263 < 4; c2_i263++) {
              c2_c_dhats[c2_i263] = c2_dhats[_SFD_EML_ARRAY_BOUNDS_CHECK("dhats",
                (int32_T)_SFD_INTEGER_CHECK("ii*ells + (1:ells)", c2_w_y + (1.0
                + (real_T)c2_i263)), 1, 40, 1, 0) - 1];
            }

            c2_c_diag(chartInstance, c2_c_dhats, c2_v_b);
            c2_o_eml_scalar_eg(chartInstance);
            c2_o_eml_scalar_eg(chartInstance);
            for (c2_i264 = 0; c2_i264 < 4; c2_i264++) {
              c2_i265 = 0;
              for (c2_i266 = 0; c2_i266 < 4; c2_i266++) {
                c2_u_y[c2_i265 + c2_i264] = 0.0;
                c2_i267 = 0;
                for (c2_i268 = 0; c2_i268 < 4; c2_i268++) {
                  c2_u_y[c2_i265 + c2_i264] += c2_u_b[c2_i267 + c2_i264] *
                    c2_v_b[c2_i268 + c2_i265];
                  c2_i267 += 4;
                }

                c2_i265 += 4;
              }
            }

            c2_i269 = 0;
            for (c2_i270 = 0; c2_i270 < 3; c2_i270++) {
              for (c2_i271 = 0; c2_i271 < 4; c2_i271++) {
                c2_u_b[c2_i271 + c2_i269] = c2_Fxs[c2_i271 + c2_i269];
              }

              c2_i269 += 4;
            }

            for (c2_i272 = 0; c2_i272 < 4; c2_i272++) {
              c2_u_b[c2_i272 + 12] = c2_Fus[c2_i272];
            }

            c2_o_eml_scalar_eg(chartInstance);
            c2_o_eml_scalar_eg(chartInstance);
            for (c2_i273 = 0; c2_i273 < 4; c2_i273++) {
              c2_i274 = 0;
              for (c2_i275 = 0; c2_i275 < 4; c2_i275++) {
                c2_v_b[c2_i274 + c2_i273] = 0.0;
                c2_i276 = 0;
                for (c2_i277 = 0; c2_i277 < 4; c2_i277++) {
                  c2_v_b[c2_i274 + c2_i273] += c2_u_y[c2_i276 + c2_i273] *
                    c2_u_b[c2_i277 + c2_i274];
                  c2_i276 += 4;
                }

                c2_i274 += 4;
              }
            }

            for (c2_i278 = 0; c2_i278 < 16; c2_i278++) {
              c2_w_b[c2_i278] = (c2_r_b[c2_i278] + c2_v_y[c2_i278]) +
                c2_v_b[c2_i278];
            }

            c2_b_mySymPDinv(chartInstance, c2_w_b, c2_dv11);
            for (c2_i279 = 0; c2_i279 < 16; c2_i279++) {
              c2_blkInv[c2_i279] = c2_dv11[c2_i279];
            }
          } else {
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 322);
            c2_realmax(chartInstance);
            c2_realmax(chartInstance);
            for (c2_i280 = 0; c2_i280 < 16; c2_i280++) {
              c2_r_b[c2_i280] = c2_blkQR[c2_i280];
            }

            for (c2_i281 = 0; c2_i281 < 16; c2_i281++) {
              c2_r_b[c2_i281] *= 2.0;
            }

            c2_u_a = c2_kappa;
            c2_i282 = 0;
            for (c2_i283 = 0; c2_i283 < 4; c2_i283++) {
              c2_i284 = 0;
              for (c2_i285 = 0; c2_i285 < 3; c2_i285++) {
                c2_u_b[c2_i285 + c2_i282] = c2_Fx[c2_i284 + c2_i283];
                c2_i284 += 4;
              }

              c2_i282 += 4;
            }

            c2_i286 = 0;
            for (c2_i287 = 0; c2_i287 < 4; c2_i287++) {
              c2_u_b[c2_i286 + 3] = c2_Fu[c2_i287];
              c2_i286 += 4;
            }

            for (c2_i288 = 0; c2_i288 < 16; c2_i288++) {
              c2_u_b[c2_i288] *= c2_u_a;
            }

            c2_v_a = c2_b_ii;
            c2_x_y = c2_v_a * 4.0;
            c2_w_a = c2_b_ii;
            c2_y_y = c2_w_a * 4.0;
            for (c2_i289 = 0; c2_i289 < 4; c2_i289++) {
              c2_f_d[c2_i289] = c2_d[_SFD_EML_ARRAY_BOUNDS_CHECK("d", (int32_T)
                _SFD_INTEGER_CHECK("ii*ell + (1:ell)", c2_x_y + (1.0 + (real_T)
                c2_i289)), 1, 44, 1, 0) - 1] * c2_d[_SFD_EML_ARRAY_BOUNDS_CHECK(
                "d", (int32_T)_SFD_INTEGER_CHECK("ii*ell + (1:ell)", c2_y_y +
                (1.0 + (real_T)c2_i289)), 1, 44, 1, 0) - 1];
            }

            c2_c_diag(chartInstance, c2_f_d, c2_v_b);
            c2_o_eml_scalar_eg(chartInstance);
            c2_o_eml_scalar_eg(chartInstance);
            for (c2_i290 = 0; c2_i290 < 4; c2_i290++) {
              c2_i291 = 0;
              for (c2_i292 = 0; c2_i292 < 4; c2_i292++) {
                c2_u_y[c2_i291 + c2_i290] = 0.0;
                c2_i293 = 0;
                for (c2_i294 = 0; c2_i294 < 4; c2_i294++) {
                  c2_u_y[c2_i291 + c2_i290] += c2_u_b[c2_i293 + c2_i290] *
                    c2_v_b[c2_i294 + c2_i291];
                  c2_i293 += 4;
                }

                c2_i291 += 4;
              }
            }

            c2_i295 = 0;
            for (c2_i296 = 0; c2_i296 < 3; c2_i296++) {
              for (c2_i297 = 0; c2_i297 < 4; c2_i297++) {
                c2_u_b[c2_i297 + c2_i295] = c2_Fx[c2_i297 + c2_i295];
              }

              c2_i295 += 4;
            }

            for (c2_i298 = 0; c2_i298 < 4; c2_i298++) {
              c2_u_b[c2_i298 + 12] = c2_Fu[c2_i298];
            }

            c2_o_eml_scalar_eg(chartInstance);
            c2_o_eml_scalar_eg(chartInstance);
            for (c2_i299 = 0; c2_i299 < 4; c2_i299++) {
              c2_i300 = 0;
              for (c2_i301 = 0; c2_i301 < 4; c2_i301++) {
                c2_v_y[c2_i300 + c2_i299] = 0.0;
                c2_i302 = 0;
                for (c2_i303 = 0; c2_i303 < 4; c2_i303++) {
                  c2_v_y[c2_i300 + c2_i299] += c2_u_y[c2_i302 + c2_i299] *
                    c2_u_b[c2_i303 + c2_i300];
                  c2_i302 += 4;
                }

                c2_i300 += 4;
              }
            }

            for (c2_i304 = 0; c2_i304 < 16; c2_i304++) {
              c2_x_b[c2_i304] = c2_r_b[c2_i304] + c2_v_y[c2_i304];
            }

            c2_b_mySymPDinv(chartInstance, c2_x_b, c2_dv12);
            for (c2_i305 = 0; c2_i305 < 16; c2_i305++) {
              c2_blkInv[c2_i305] = c2_dv12[c2_i305];
            }
          }

          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 324);
          c2_realmax(chartInstance);
          c2_realmax(chartInstance);
          c2_x_a = c2_b_ii - 1.0;
          c2_ab_y = c2_x_a * 4.0;
          c2_y_a = c2_b_ii - 1.0;
          c2_bb_y = c2_y_a * 4.0;
          c2_b_m = c2_m + c2_ab_y;
          c2_c_m = c2_m + c2_bb_y;
          for (c2_i306 = 0; c2_i306 < 4; c2_i306++) {
            for (c2_i307 = 0; c2_i307 < 4; c2_i307++) {
              c2_phiInv[(_SFD_EML_ARRAY_BOUNDS_CHECK("phiInv", (int32_T)
                          _SFD_INTEGER_CHECK("m+(ii-1)*(n+m)+(1:(n+m))", c2_b_m
                + (1.0 + (real_T)c2_i307)), 1, 40, 1, 0) + 40 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("phiInv", (int32_T)
                _SFD_INTEGER_CHECK("m+(ii-1)*(n+m)+(1:(n+m))", c2_c_m + (1.0 +
                (real_T)c2_i306)), 1, 40, 2, 0) - 1)) - 1] = c2_blkInv[c2_i307 +
                (c2_i306 << 2)];
            }
          }

          c2_ii++;
          sf_mex_listen_for_ctrl_c(chartInstance->S);
        }

        CV_EML_FOR(0, 1, 2, 0);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 326);
        c2_realmax(chartInstance);
        c2_realmax(chartInstance);
        c2_realmax(chartInstance);
        c2_realmax(chartInstance);
        for (c2_i308 = 0; c2_i308 < 9; c2_i308++) {
          c2_y_b[c2_i308] = c2_Qf[c2_i308];
        }

        for (c2_i309 = 0; c2_i309 < 9; c2_i309++) {
          c2_y_b[c2_i309] *= 2.0;
        }

        c2_ab_a = c2_kappa;
        c2_i310 = 0;
        for (c2_i311 = 0; c2_i311 < 4; c2_i311++) {
          c2_i312 = 0;
          for (c2_i313 = 0; c2_i313 < 3; c2_i313++) {
            c2_ab_b[c2_i313 + c2_i310] = c2_Ff[c2_i312 + c2_i311];
            c2_i312 += 4;
          }

          c2_i310 += 3;
        }

        for (c2_i314 = 0; c2_i314 < 12; c2_i314++) {
          c2_ab_b[c2_i314] *= c2_ab_a;
        }

        for (c2_i315 = 0; c2_i315 < 4; c2_i315++) {
          c2_g_d[c2_i315] = c2_d[c2_i315 + 40] * c2_d[c2_i315 + 40];
        }

        c2_c_diag(chartInstance, c2_g_d, c2_r_b);
        c2_q_eml_scalar_eg(chartInstance);
        c2_q_eml_scalar_eg(chartInstance);
        for (c2_i316 = 0; c2_i316 < 3; c2_i316++) {
          c2_i317 = 0;
          c2_i318 = 0;
          for (c2_i319 = 0; c2_i319 < 4; c2_i319++) {
            c2_cb_y[c2_i317 + c2_i316] = 0.0;
            c2_i320 = 0;
            for (c2_i321 = 0; c2_i321 < 4; c2_i321++) {
              c2_cb_y[c2_i317 + c2_i316] += c2_ab_b[c2_i320 + c2_i316] *
                c2_r_b[c2_i321 + c2_i318];
              c2_i320 += 3;
            }

            c2_i317 += 3;
            c2_i318 += 4;
          }
        }

        for (c2_i322 = 0; c2_i322 < 12; c2_i322++) {
          c2_bb_b[c2_i322] = c2_Ff[c2_i322];
        }

        c2_r_eml_scalar_eg(chartInstance);
        c2_r_eml_scalar_eg(chartInstance);
        for (c2_i323 = 0; c2_i323 < 3; c2_i323++) {
          c2_i324 = 0;
          c2_i325 = 0;
          for (c2_i326 = 0; c2_i326 < 3; c2_i326++) {
            c2_db_y[c2_i324 + c2_i323] = 0.0;
            c2_i327 = 0;
            for (c2_i328 = 0; c2_i328 < 4; c2_i328++) {
              c2_db_y[c2_i324 + c2_i323] += c2_cb_y[c2_i327 + c2_i323] *
                c2_bb_b[c2_i328 + c2_i325];
              c2_i327 += 3;
            }

            c2_i324 += 3;
            c2_i325 += 4;
          }
        }

        for (c2_i329 = 0; c2_i329 < 9; c2_i329++) {
          c2_cb_b[c2_i329] = c2_y_b[c2_i329] + c2_db_y[c2_i329];
        }

        c2_c_mySymPDinv(chartInstance, c2_cb_b, c2_dv13);
        c2_c_nz = c2_nz - c2_n;
        c2_d_nz = c2_nz - c2_n;
        for (c2_i330 = 0; c2_i330 < 3; c2_i330++) {
          for (c2_i331 = 0; c2_i331 < 3; c2_i331++) {
            c2_phiInv[(_SFD_EML_ARRAY_BOUNDS_CHECK("phiInv", (int32_T)
                        _SFD_INTEGER_CHECK("nz-n+(1:n)", c2_c_nz + (1.0 +
              (real_T)c2_i331)), 1, 40, 1, 0) + 40 *
                       (_SFD_EML_ARRAY_BOUNDS_CHECK("phiInv", (int32_T)
              _SFD_INTEGER_CHECK("nz-n+(1:n)", c2_d_nz + (1.0 + (real_T)c2_i330)),
              1, 40, 2, 0) - 1)) - 1] = c2_dv13[c2_i331 + 3 * c2_i330];
          }
        }
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 331);
      if (CV_EML_IF(0, 1, 29, c2_flagChecking)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 332);
        for (c2_i332 = 0; c2_i332 < 1600; c2_i332++) {
          c2_d_b[c2_i332] = c2_H[c2_i332];
        }

        for (c2_i333 = 0; c2_i333 < 1600; c2_i333++) {
          c2_d_b[c2_i333] *= 2.0;
        }

        c2_bb_a = c2_kappa;
        c2_i334 = 0;
        for (c2_i335 = 0; c2_i335 < 44; c2_i335++) {
          c2_i336 = 0;
          for (c2_i337 = 0; c2_i337 < 40; c2_i337++) {
            c2_c_b[c2_i337 + c2_i334] = c2_P[c2_i336 + c2_i335];
            c2_i336 += 44;
          }

          c2_i334 += 40;
        }

        for (c2_i338 = 0; c2_i338 < 1760; c2_i338++) {
          c2_c_b[c2_i338] *= c2_bb_a;
        }

        for (c2_i339 = 0; c2_i339 < 44; c2_i339++) {
          c2_h_d[c2_i339] = c2_d[c2_i339];
        }

        c2_d_diag(chartInstance, c2_h_d, c2_db_b);
        c2_u_eml_scalar_eg(chartInstance);
        c2_u_eml_scalar_eg(chartInstance);
        for (c2_i340 = 0; c2_i340 < 1760; c2_i340++) {
          c2_eb_y[c2_i340] = 0.0;
        }

        for (c2_i341 = 0; c2_i341 < 1760; c2_i341++) {
          c2_eb_b[c2_i341] = c2_c_b[c2_i341];
        }

        for (c2_i342 = 0; c2_i342 < 1936; c2_i342++) {
          c2_fb_b[c2_i342] = c2_db_b[c2_i342];
        }

        c2_s_eml_xgemm(chartInstance, c2_eb_b, c2_fb_b, c2_eb_y);
        for (c2_i343 = 0; c2_i343 < 44; c2_i343++) {
          c2_i_d[c2_i343] = c2_d[c2_i343];
        }

        c2_d_diag(chartInstance, c2_i_d, c2_db_b);
        c2_u_eml_scalar_eg(chartInstance);
        c2_u_eml_scalar_eg(chartInstance);
        for (c2_i344 = 0; c2_i344 < 1760; c2_i344++) {
          c2_c_b[c2_i344] = 0.0;
        }

        for (c2_i345 = 0; c2_i345 < 1760; c2_i345++) {
          c2_fb_y[c2_i345] = c2_eb_y[c2_i345];
        }

        for (c2_i346 = 0; c2_i346 < 1936; c2_i346++) {
          c2_gb_b[c2_i346] = c2_db_b[c2_i346];
        }

        c2_s_eml_xgemm(chartInstance, c2_fb_y, c2_gb_b, c2_c_b);
        for (c2_i347 = 0; c2_i347 < 1760; c2_i347++) {
          c2_d_a[c2_i347] = c2_P[c2_i347];
        }

        c2_v_eml_scalar_eg(chartInstance);
        c2_v_eml_scalar_eg(chartInstance);
        for (c2_i348 = 0; c2_i348 < 1600; c2_i348++) {
          c2_gb_y[c2_i348] = 0.0;
        }

        for (c2_i349 = 0; c2_i349 < 1760; c2_i349++) {
          c2_hb_b[c2_i349] = c2_c_b[c2_i349];
        }

        for (c2_i350 = 0; c2_i350 < 1760; c2_i350++) {
          c2_cb_a[c2_i350] = c2_d_a[c2_i350];
        }

        c2_t_eml_xgemm(chartInstance, c2_hb_b, c2_cb_a, c2_gb_y);
        for (c2_i351 = 0; c2_i351 < 1600; c2_i351++) {
          c2_phi[c2_i351] = c2_d_b[c2_i351] + c2_gb_y[c2_i351];
        }

        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 333);
        if (CV_EML_IF(0, 1, 30, c2_flagUseSoftCons)) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 334);
          c2_db_a = c2_rho;
          c2_i352 = 0;
          for (c2_i353 = 0; c2_i353 < 40; c2_i353++) {
            c2_i354 = 0;
            for (c2_i355 = 0; c2_i355 < 40; c2_i355++) {
              c2_d_b[c2_i355 + c2_i352] = c2_Ps[c2_i354 + c2_i353];
              c2_i354 += 40;
            }

            c2_i352 += 40;
          }

          for (c2_i356 = 0; c2_i356 < 1600; c2_i356++) {
            c2_d_b[c2_i356] *= c2_db_a;
          }

          for (c2_i357 = 0; c2_i357 < 40; c2_i357++) {
            c2_c_es[c2_i357] = c2_es[c2_i357];
          }

          for (c2_i358 = 0; c2_i358 < 40; c2_i358++) {
            c2_dv14[c2_i358] = (1.0 + c2_es[c2_i358]) * (1.0 + c2_es[c2_i358]);
          }

          c2_b_rdivide(chartInstance, c2_c_es, c2_dv14, c2_dv6);
          for (c2_i359 = 0; c2_i359 < 40; c2_i359++) {
            c2_dv15[c2_i359] = c2_dv6[c2_i359];
          }

          c2_b_diag(chartInstance, c2_dv15, c2_k_a);
          c2_w_eml_scalar_eg(chartInstance);
          c2_w_eml_scalar_eg(chartInstance);
          for (c2_i360 = 0; c2_i360 < 1600; c2_i360++) {
            c2_gb_y[c2_i360] = 0.0;
          }

          for (c2_i361 = 0; c2_i361 < 1600; c2_i361++) {
            c2_ib_b[c2_i361] = c2_d_b[c2_i361];
          }

          for (c2_i362 = 0; c2_i362 < 1600; c2_i362++) {
            c2_eb_a[c2_i362] = c2_k_a[c2_i362];
          }

          c2_u_eml_xgemm(chartInstance, c2_ib_b, c2_eb_a, c2_gb_y);
          for (c2_i363 = 0; c2_i363 < 1600; c2_i363++) {
            c2_d_b[c2_i363] = c2_Ps[c2_i363];
          }

          c2_w_eml_scalar_eg(chartInstance);
          c2_w_eml_scalar_eg(chartInstance);
          for (c2_i364 = 0; c2_i364 < 1600; c2_i364++) {
            c2_k_a[c2_i364] = 0.0;
          }

          for (c2_i365 = 0; c2_i365 < 1600; c2_i365++) {
            c2_hb_y[c2_i365] = c2_gb_y[c2_i365];
          }

          for (c2_i366 = 0; c2_i366 < 1600; c2_i366++) {
            c2_jb_b[c2_i366] = c2_d_b[c2_i366];
          }

          c2_u_eml_xgemm(chartInstance, c2_hb_y, c2_jb_b, c2_k_a);
          for (c2_i367 = 0; c2_i367 < 1600; c2_i367++) {
            c2_phi[c2_i367] += c2_k_a[c2_i367];
          }
        }

        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 337);
        for (c2_i368 = 0; c2_i368 < 1600; c2_i368++) {
          c2_k_a[c2_i368] = c2_phi[c2_i368];
        }

        for (c2_i369 = 0; c2_i369 < 1600; c2_i369++) {
          c2_d_b[c2_i369] = c2_phiInv[c2_i369];
        }

        c2_w_eml_scalar_eg(chartInstance);
        c2_w_eml_scalar_eg(chartInstance);
        for (c2_i370 = 0; c2_i370 < 1600; c2_i370++) {
          c2_gb_y[c2_i370] = 0.0;
        }

        for (c2_i371 = 0; c2_i371 < 1600; c2_i371++) {
          c2_fb_a[c2_i371] = c2_k_a[c2_i371];
        }

        for (c2_i372 = 0; c2_i372 < 1600; c2_i372++) {
          c2_kb_b[c2_i372] = c2_d_b[c2_i372];
        }

        c2_u_eml_xgemm(chartInstance, c2_fb_a, c2_kb_b, c2_gb_y);
        c2_eye(chartInstance, c2_k_a);
        for (c2_i373 = 0; c2_i373 < 1600; c2_i373++) {
          c2_gb_y[c2_i373] -= c2_k_a[c2_i373];
        }

        c2_ix = -39;
        c2_iy = 0;
        c2_d_eml_int_forloop_overflow_check(chartInstance);
        for (c2_i = 1; c2_i < 41; c2_i++) {
          c2_gb_a = c2_ix + 40;
          c2_ix = c2_gb_a;
          c2_ixstart = c2_ix;
          c2_hb_a = c2_ixstart + 39;
          c2_ixstop = c2_hb_a;
          c2_mtmp = c2_gb_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_ixstart), 1, 1600, 1, 0) - 1];
          c2_x = c2_mtmp;
          c2_lb_b = muDoubleScalarIsNaN(c2_x);
          if (c2_lb_b) {
            c2_ib_a = c2_ixstart + 1;
            c2_i374 = c2_ib_a;
            c2_i_eml_int_forloop_overflow_check(chartInstance, c2_i374,
              c2_ixstop);
            c2_b_ix = c2_i374;
            exitg4 = FALSE;
            while ((exitg4 == 0U) && (c2_b_ix <= c2_ixstop)) {
              c2_c_ix = c2_b_ix;
              c2_ixstart = c2_c_ix;
              c2_b_x = c2_gb_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_c_ix), 1, 1600, 1, 0) - 1];
              c2_mb_b = muDoubleScalarIsNaN(c2_b_x);
              if (!c2_mb_b) {
                c2_mtmp = c2_gb_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_c_ix), 1, 1600, 1, 0) - 1];
                exitg4 = TRUE;
              } else {
                c2_b_ix++;
              }
            }
          }

          if (c2_ixstart < c2_ixstop) {
            c2_jb_a = c2_ixstart + 1;
            c2_i375 = c2_jb_a;
            c2_i_eml_int_forloop_overflow_check(chartInstance, c2_i375,
              c2_ixstop);
            for (c2_d_ix = c2_i375; c2_d_ix <= c2_ixstop; c2_d_ix++) {
              c2_c_ix = c2_d_ix;
              c2_kb_a = c2_gb_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_c_ix), 1, 1600, 1, 0) - 1];
              c2_nb_b = c2_mtmp;
              c2_p = (c2_kb_a > c2_nb_b);
              if (c2_p) {
                c2_mtmp = c2_gb_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_c_ix), 1, 1600, 1, 0) - 1];
              }
            }
          }

          c2_b_mtmp = c2_mtmp;
          c2_lb_a = c2_iy + 1;
          c2_iy = c2_lb_a;
          c2_maxval[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
            "", (real_T)c2_iy), 1, 40, 1, 0) - 1] = c2_b_mtmp;
          _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_iy), 1, 40, 1, 0);
          c2_mb_a = c2_ix;
          c2_ix = c2_mb_a;
        }

        c2_b_ixstart = 1;
        c2_c_mtmp = c2_maxval[0];
        c2_c_x = c2_c_mtmp;
        c2_ob_b = muDoubleScalarIsNaN(c2_c_x);
        if (c2_ob_b) {
          c2_i_eml_int_forloop_overflow_check(chartInstance, 2, 40);
          c2_e_ix = 2;
          exitg3 = FALSE;
          while ((exitg3 == 0U) && (c2_e_ix < 41)) {
            c2_f_ix = c2_e_ix;
            c2_b_ixstart = c2_f_ix;
            c2_d_x = c2_maxval[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c2_f_ix), 1, 40, 1, 0) - 1];
            c2_pb_b = muDoubleScalarIsNaN(c2_d_x);
            if (!c2_pb_b) {
              c2_c_mtmp = c2_maxval[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_f_ix), 1, 40, 1, 0) - 1];
              exitg3 = TRUE;
            } else {
              c2_e_ix++;
            }
          }
        }

        if (c2_b_ixstart < 40) {
          c2_nb_a = c2_b_ixstart + 1;
          c2_i376 = c2_nb_a;
          c2_i_eml_int_forloop_overflow_check(chartInstance, c2_i376, 40);
          for (c2_g_ix = c2_i376; c2_g_ix < 41; c2_g_ix++) {
            c2_f_ix = c2_g_ix;
            c2_ob_a = c2_maxval[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c2_f_ix), 1, 40, 1, 0) - 1];
            c2_qb_b = c2_c_mtmp;
            c2_b_p = (c2_ob_a > c2_qb_b);
            if (c2_b_p) {
              c2_c_mtmp = c2_maxval[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_f_ix), 1, 40, 1, 0) - 1];
            }
          }
        }

        c2_d_mtmp = c2_c_mtmp;
        c2_checkPhiInv = c2_d_mtmp;
        sf_mex_printf("%s =\\n", "checkPhiInv");
        c2_d_u = c2_checkPhiInv;
        c2_ib_y = NULL;
        sf_mex_assign(&c2_ib_y, sf_mex_create("y", &c2_d_u, 0, 0U, 0U, 0U, 0),
                      FALSE);
        sf_mex_call_debug("disp", 0U, 1U, 14, c2_ib_y);
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 339);
        c2_checkPhiInv = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 343);
      for (c2_i377 = 0; c2_i377 < 1024; c2_i377++) {
        c2_Y[c2_i377] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 346);
      for (c2_i378 = 0; c2_i378 < 3; c2_i378++) {
        c2_c_a[c2_i378] = c2_B[c2_i378];
      }

      for (c2_i379 = 0; c2_i379 < 1600; c2_i379++) {
        c2_b_phiInv[c2_i379] = c2_phiInv[c2_i379];
      }

      c2_rb_b = c2_Rtil(chartInstance, c2_b_phiInv);
      for (c2_i380 = 0; c2_i380 < 3; c2_i380++) {
        c2_c_a[c2_i380] *= c2_rb_b;
      }

      for (c2_i381 = 0; c2_i381 < 3; c2_i381++) {
        c2_sb_b[c2_i381] = c2_B[c2_i381];
      }

      c2_i382 = 0;
      for (c2_i383 = 0; c2_i383 < 3; c2_i383++) {
        for (c2_i384 = 0; c2_i384 < 3; c2_i384++) {
          c2_db_y[c2_i384 + c2_i382] = c2_c_a[c2_i384] * c2_sb_b[c2_i383];
        }

        c2_i382 += 3;
      }

      for (c2_i385 = 0; c2_i385 < 1600; c2_i385++) {
        c2_c_phiInv[c2_i385] = c2_phiInv[c2_i385];
      }

      c2_Qtil(chartInstance, c2_c_phiInv, c2_dv16);
      c2_i386 = 0;
      c2_i387 = 0;
      for (c2_i388 = 0; c2_i388 < 3; c2_i388++) {
        for (c2_i389 = 0; c2_i389 < 3; c2_i389++) {
          c2_Y[c2_i389 + c2_i386] = c2_db_y[c2_i389 + c2_i387] + c2_dv16[c2_i389
            + c2_i387];
        }

        c2_i386 += 32;
        c2_i387 += 3;
      }

      c2_c_ii = 0;
      while (c2_c_ii < 10) {
        c2_b_ii = 1.0 + (real_T)c2_c_ii;
        CV_EML_FOR(0, 1, 3, 1);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 348);
        if (CV_EML_IF(0, 1, 31, c2_b_ii < c2_T)) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 350);
          c2_realmax(chartInstance);
          c2_realmax(chartInstance);
          c2_pb_a = c2_b_ii - 1.0;
          c2_jb_y = c2_pb_a * 3.0;
          c2_qb_a = c2_b_ii;
          c2_kb_y = c2_qb_a * 3.0;
          for (c2_i390 = 0; c2_i390 < 1600; c2_i390++) {
            c2_d_phiInv[c2_i390] = c2_phiInv[c2_i390];
          }

          c2_Stil(chartInstance, c2_d_phiInv, c2_b_ii, c2_c_a);
          for (c2_i391 = 0; c2_i391 < 3; c2_i391++) {
            c2_sb_b[c2_i391] = c2_B[c2_i391];
          }

          c2_i392 = 0;
          for (c2_i393 = 0; c2_i393 < 3; c2_i393++) {
            for (c2_i394 = 0; c2_i394 < 3; c2_i394++) {
              c2_db_y[c2_i394 + c2_i392] = c2_c_a[c2_i394] * c2_sb_b[c2_i393];
            }

            c2_i392 += 3;
          }

          for (c2_i395 = 0; c2_i395 < 1600; c2_i395++) {
            c2_e_phiInv[c2_i395] = c2_phiInv[c2_i395];
          }

          c2_b_Qtil(chartInstance, c2_e_phiInv, c2_b_ii, c2_dv16);
          for (c2_i396 = 0; c2_i396 < 9; c2_i396++) {
            c2_dv17[c2_i396] = c2_dv16[c2_i396];
          }

          for (c2_i397 = 0; c2_i397 < 9; c2_i397++) {
            c2_c_AT[c2_i397] = c2_AT[c2_i397];
          }

          for (c2_i398 = 0; c2_i398 < 9; c2_i398++) {
            c2_h_switches[c2_i398] = c2_switches[c2_i398];
          }

          c2_multByAT(chartInstance, c2_dv17, c2_c_AT, c2_h_switches, c2_dv16);
          for (c2_i399 = 0; c2_i399 < 3; c2_i399++) {
            for (c2_i400 = 0; c2_i400 < 3; c2_i400++) {
              c2_Y[(_SFD_EML_ARRAY_BOUNDS_CHECK("Y", (int32_T)_SFD_INTEGER_CHECK
                     ("(ii-1)*n+(1:n)", c2_jb_y + (1.0 + (real_T)c2_i400)), 1,
                     32, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("Y", (int32_T)
                       _SFD_INTEGER_CHECK("ii*n+(1:n)", c2_kb_y + (1.0 + (real_T)
                         c2_i399)), 1, 32, 2, 0) - 1) << 5)) - 1] =
                -c2_dv16[c2_i400 + 3 * c2_i399] - c2_db_y[c2_i400 + 3 * c2_i399];
            }
          }

          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 351);
          c2_realmax(chartInstance);
          c2_realmax(chartInstance);
          c2_realmax(chartInstance);
          c2_realmax(chartInstance);
          c2_rb_a = c2_b_ii;
          c2_lb_y = c2_rb_a * 3.0;
          c2_sb_a = c2_b_ii - 1.0;
          c2_mb_y = c2_sb_a * 3.0;
          c2_tb_a = c2_b_ii - 1.0;
          c2_nb_y = c2_tb_a * 3.0;
          c2_ub_a = c2_b_ii;
          c2_ob_y = c2_ub_a * 3.0;
          for (c2_i401 = 0; c2_i401 < 3; c2_i401++) {
            for (c2_i402 = 0; c2_i402 < 3; c2_i402++) {
              c2_b_Y[c2_i402 + 3 * c2_i401] = c2_Y[(_SFD_EML_ARRAY_BOUNDS_CHECK(
                "Y", (int32_T)_SFD_INTEGER_CHECK("(ii-1)*n+(1:n)", c2_nb_y +
                (1.0 + (real_T)c2_i401)), 1, 32, 1, 0) +
                ((_SFD_EML_ARRAY_BOUNDS_CHECK("Y", (int32_T)_SFD_INTEGER_CHECK(
                "ii*n+(1:n)", c2_ob_y + (1.0 + (real_T)c2_i402)), 1, 32, 2, 0) -
                  1) << 5)) - 1];
            }
          }

          for (c2_i403 = 0; c2_i403 < 3; c2_i403++) {
            for (c2_i404 = 0; c2_i404 < 3; c2_i404++) {
              c2_Y[(_SFD_EML_ARRAY_BOUNDS_CHECK("Y", (int32_T)_SFD_INTEGER_CHECK
                     ("ii*n+(1:n)", c2_lb_y + (1.0 + (real_T)c2_i404)), 1, 32, 1,
                     0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("Y", (int32_T)
                       _SFD_INTEGER_CHECK("(ii-1)*n+(1:n)", c2_mb_y + (1.0 +
                         (real_T)c2_i403)), 1, 32, 2, 0) - 1) << 5)) - 1] =
                c2_b_Y[c2_i404 + 3 * c2_i403];
            }
          }
        }

        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 353);
        if (CV_EML_IF(0, 1, 32, c2_b_ii > 1.0)) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 355);
          for (c2_i405 = 0; c2_i405 < 1600; c2_i405++) {
            c2_f_phiInv[c2_i405] = c2_phiInv[c2_i405];
          }

          c2_Stil(chartInstance, c2_f_phiInv, c2_b_ii - 1.0, c2_c_a);
          for (c2_i406 = 0; c2_i406 < 3; c2_i406++) {
            c2_vb_a[c2_i406] = c2_c_a[c2_i406];
          }

          for (c2_i407 = 0; c2_i407 < 9; c2_i407++) {
            c2_d_A[c2_i407] = c2_A[c2_i407];
          }

          for (c2_i408 = 0; c2_i408 < 9; c2_i408++) {
            c2_i_switches[c2_i408] = c2_switches[c2_i408];
          }

          c2_preMultByA(chartInstance, c2_vb_a, c2_d_A, c2_i_switches, c2_c_a);
          for (c2_i409 = 0; c2_i409 < 3; c2_i409++) {
            c2_sb_b[c2_i409] = c2_B[c2_i409];
          }

          c2_i410 = 0;
          for (c2_i411 = 0; c2_i411 < 3; c2_i411++) {
            for (c2_i412 = 0; c2_i412 < 3; c2_i412++) {
              c2_tmp[c2_i412 + c2_i410] = c2_c_a[c2_i412] * c2_sb_b[c2_i411];
            }

            c2_i410 += 3;
          }

          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 358);
          c2_realmax(chartInstance);
          c2_realmax(chartInstance);
          c2_wb_a = c2_b_ii - 1.0;
          c2_pb_y = c2_wb_a * 3.0;
          c2_xb_a = c2_b_ii - 1.0;
          c2_qb_y = c2_xb_a * 3.0;
          for (c2_i413 = 0; c2_i413 < 3; c2_i413++) {
            c2_c_a[c2_i413] = c2_B[c2_i413];
          }

          for (c2_i414 = 0; c2_i414 < 1600; c2_i414++) {
            c2_g_phiInv[c2_i414] = c2_phiInv[c2_i414];
          }

          c2_tb_b = c2_b_Rtil(chartInstance, c2_g_phiInv, c2_b_ii - 1.0);
          for (c2_i415 = 0; c2_i415 < 3; c2_i415++) {
            c2_c_a[c2_i415] *= c2_tb_b;
          }

          for (c2_i416 = 0; c2_i416 < 3; c2_i416++) {
            c2_sb_b[c2_i416] = c2_B[c2_i416];
          }

          c2_i417 = 0;
          for (c2_i418 = 0; c2_i418 < 3; c2_i418++) {
            for (c2_i419 = 0; c2_i419 < 3; c2_i419++) {
              c2_db_y[c2_i419 + c2_i417] = c2_c_a[c2_i419] * c2_sb_b[c2_i418];
            }

            c2_i417 += 3;
          }

          for (c2_i420 = 0; c2_i420 < 1600; c2_i420++) {
            c2_h_phiInv[c2_i420] = c2_phiInv[c2_i420];
          }

          c2_b_Qtil(chartInstance, c2_h_phiInv, c2_b_ii - 1.0, c2_dv16);
          for (c2_i421 = 0; c2_i421 < 9; c2_i421++) {
            c2_dv18[c2_i421] = c2_dv16[c2_i421];
          }

          for (c2_i422 = 0; c2_i422 < 9; c2_i422++) {
            c2_e_A[c2_i422] = c2_A[c2_i422];
          }

          for (c2_i423 = 0; c2_i423 < 9; c2_i423++) {
            c2_j_switches[c2_i423] = c2_switches[c2_i423];
          }

          c2_b_preMultByA(chartInstance, c2_dv18, c2_e_A, c2_j_switches, c2_dv16);
          for (c2_i424 = 0; c2_i424 < 9; c2_i424++) {
            c2_dv19[c2_i424] = c2_dv16[c2_i424];
          }

          for (c2_i425 = 0; c2_i425 < 9; c2_i425++) {
            c2_d_AT[c2_i425] = c2_AT[c2_i425];
          }

          for (c2_i426 = 0; c2_i426 < 9; c2_i426++) {
            c2_k_switches[c2_i426] = c2_switches[c2_i426];
          }

          c2_multByAT(chartInstance, c2_dv19, c2_d_AT, c2_k_switches, c2_dv16);
          for (c2_i427 = 0; c2_i427 < 1600; c2_i427++) {
            c2_i_phiInv[c2_i427] = c2_phiInv[c2_i427];
          }

          c2_b_Qtil(chartInstance, c2_i_phiInv, c2_b_ii, c2_y_b);
          for (c2_i428 = 0; c2_i428 < 3; c2_i428++) {
            for (c2_i429 = 0; c2_i429 < 3; c2_i429++) {
              c2_Y[(_SFD_EML_ARRAY_BOUNDS_CHECK("Y", (int32_T)_SFD_INTEGER_CHECK
                     ("(ii-1)*n+(1:n)", c2_pb_y + (1.0 + (real_T)c2_i429)), 1,
                     32, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("Y", (int32_T)
                       _SFD_INTEGER_CHECK("(ii-1)*n+(1:n)", c2_qb_y + (1.0 +
                         (real_T)c2_i428)), 1, 32, 2, 0) - 1) << 5)) - 1] =
                (((c2_dv16[c2_i429 + 3 * c2_i428] + c2_tmp[c2_i429 + 3 * c2_i428])
                  + c2_tmp[c2_i428 + 3 * c2_i429]) + c2_db_y[c2_i429 + 3 *
                 c2_i428]) + c2_y_b[c2_i429 + 3 * c2_i428];
            }
          }
        }

        c2_c_ii++;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }

      CV_EML_FOR(0, 1, 3, 0);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 383);
      CV_EML_IF(0, 1, 33, c2_ellef > 0.0);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 384);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      for (c2_i430 = 0; c2_i430 < 1600; c2_i430++) {
        c2_j_phiInv[c2_i430] = c2_phiInv[c2_i430];
      }

      c2_b_Qtil(chartInstance, c2_j_phiInv, 10.0, c2_yb_a);
      c2_i431 = 0;
      for (c2_i432 = 0; c2_i432 < 2; c2_i432++) {
        c2_i433 = 0;
        for (c2_i434 = 0; c2_i434 < 3; c2_i434++) {
          c2_ub_b[c2_i434 + c2_i431] = c2_Ef[c2_i433 + c2_i432];
          c2_i433 += 2;
        }

        c2_i431 += 3;
      }

      c2_x_eml_scalar_eg(chartInstance);
      c2_x_eml_scalar_eg(chartInstance);
      for (c2_i435 = 0; c2_i435 < 3; c2_i435++) {
        c2_i436 = 0;
        for (c2_i437 = 0; c2_i437 < 2; c2_i437++) {
          c2_rb_y[c2_i436 + c2_i435] = 0.0;
          c2_i438 = 0;
          for (c2_i439 = 0; c2_i439 < 3; c2_i439++) {
            c2_rb_y[c2_i436 + c2_i435] += c2_yb_a[c2_i438 + c2_i435] *
              c2_ub_b[c2_i439 + c2_i436];
            c2_i438 += 3;
          }

          c2_i436 += 3;
        }
      }

      c2_i440 = 0;
      c2_i441 = 0;
      for (c2_i442 = 0; c2_i442 < 2; c2_i442++) {
        for (c2_i443 = 0; c2_i443 < 3; c2_i443++) {
          c2_Y[(c2_i443 + c2_i440) + 987] = c2_rb_y[c2_i443 + c2_i441];
        }

        c2_i440 += 32;
        c2_i441 += 3;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 385);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_i444 = 0;
      for (c2_i445 = 0; c2_i445 < 3; c2_i445++) {
        c2_i446 = 0;
        for (c2_i447 = 0; c2_i447 < 2; c2_i447++) {
          c2_c_Y[c2_i447 + c2_i444] = c2_Y[(c2_i446 + c2_i445) + 987];
          c2_i446 += 32;
        }

        c2_i444 += 2;
      }

      c2_i448 = 0;
      c2_i449 = 0;
      for (c2_i450 = 0; c2_i450 < 3; c2_i450++) {
        for (c2_i451 = 0; c2_i451 < 2; c2_i451++) {
          c2_Y[(c2_i451 + c2_i448) + 894] = c2_c_Y[c2_i451 + c2_i449];
        }

        c2_i448 += 32;
        c2_i449 += 2;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 386);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      for (c2_i452 = 0; c2_i452 < 6; c2_i452++) {
        c2_ac_a[c2_i452] = c2_Ef[c2_i452];
      }

      c2_i453 = 0;
      c2_i454 = 0;
      for (c2_i455 = 0; c2_i455 < 2; c2_i455++) {
        for (c2_i456 = 0; c2_i456 < 3; c2_i456++) {
          c2_ub_b[c2_i456 + c2_i453] = c2_Y[(c2_i456 + c2_i454) + 987];
        }

        c2_i453 += 3;
        c2_i454 += 32;
      }

      c2_y_eml_scalar_eg(chartInstance);
      c2_y_eml_scalar_eg(chartInstance);
      for (c2_i457 = 0; c2_i457 < 2; c2_i457++) {
        c2_i458 = 0;
        c2_i459 = 0;
        for (c2_i460 = 0; c2_i460 < 2; c2_i460++) {
          c2_sb_y[c2_i458 + c2_i457] = 0.0;
          c2_i461 = 0;
          for (c2_i462 = 0; c2_i462 < 3; c2_i462++) {
            c2_sb_y[c2_i458 + c2_i457] += c2_ac_a[c2_i461 + c2_i457] *
              c2_ub_b[c2_i462 + c2_i459];
            c2_i461 += 2;
          }

          c2_i458 += 2;
          c2_i459 += 3;
        }
      }

      c2_i463 = 0;
      c2_i464 = 0;
      for (c2_i465 = 0; c2_i465 < 2; c2_i465++) {
        for (c2_i466 = 0; c2_i466 < 2; c2_i466++) {
          c2_Y[(c2_i466 + c2_i463) + 990] = c2_sb_y[c2_i466 + c2_i464];
        }

        c2_i463 += 32;
        c2_i464 += 2;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 390);
      if (CV_EML_IF(0, 1, 34, c2_flagChecking)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 391);
        for (c2_i467 = 0; c2_i467 < 1280; c2_i467++) {
          c2_i_a[c2_i467] = c2_C[c2_i467];
        }

        for (c2_i468 = 0; c2_i468 < 1600; c2_i468++) {
          c2_d_b[c2_i468] = c2_phiInv[c2_i468];
        }

        c2_ab_eml_scalar_eg(chartInstance);
        c2_ab_eml_scalar_eg(chartInstance);
        for (c2_i469 = 0; c2_i469 < 1280; c2_i469++) {
          c2_tb_y[c2_i469] = 0.0;
        }

        for (c2_i470 = 0; c2_i470 < 1280; c2_i470++) {
          c2_bc_a[c2_i470] = c2_i_a[c2_i470];
        }

        for (c2_i471 = 0; c2_i471 < 1600; c2_i471++) {
          c2_vb_b[c2_i471] = c2_d_b[c2_i471];
        }

        c2_v_eml_xgemm(chartInstance, c2_bc_a, c2_vb_b, c2_tb_y);
        c2_i472 = 0;
        for (c2_i473 = 0; c2_i473 < 32; c2_i473++) {
          c2_i474 = 0;
          for (c2_i475 = 0; c2_i475 < 40; c2_i475++) {
            c2_wb_b[c2_i475 + c2_i472] = c2_C[c2_i474 + c2_i473];
            c2_i474 += 32;
          }

          c2_i472 += 40;
        }

        c2_bb_eml_scalar_eg(chartInstance);
        c2_bb_eml_scalar_eg(chartInstance);
        for (c2_i476 = 0; c2_i476 < 1024; c2_i476++) {
          c2_ub_y[c2_i476] = 0.0;
        }

        for (c2_i477 = 0; c2_i477 < 1280; c2_i477++) {
          c2_vb_y[c2_i477] = c2_tb_y[c2_i477];
        }

        for (c2_i478 = 0; c2_i478 < 1280; c2_i478++) {
          c2_xb_b[c2_i478] = c2_wb_b[c2_i478];
        }

        c2_w_eml_xgemm(chartInstance, c2_vb_y, c2_xb_b, c2_ub_y);
        for (c2_i479 = 0; c2_i479 < 1024; c2_i479++) {
          c2_d_Y[c2_i479] = c2_Y[c2_i479] - c2_ub_y[c2_i479];
        }

        c2_checkY = c2_e_norm(chartInstance, c2_d_Y);
        sf_mex_printf("%s =\\n", "checkY");
        c2_e_u = c2_checkY;
        c2_wb_y = NULL;
        sf_mex_assign(&c2_wb_y, sf_mex_create("y", &c2_e_u, 0, 0U, 0U, 0U, 0),
                      FALSE);
        sf_mex_call_debug("disp", 0U, 1U, 14, c2_wb_y);
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 393);
        c2_checkY = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 397);
      for (c2_i480 = 0; c2_i480 < 40; c2_i480++) {
        c2_PhiInvRd[c2_i480] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 398);
      for (c2_i481 = 0; c2_i481 < 1600; c2_i481++) {
        c2_k_phiInv[c2_i481] = c2_phiInv[c2_i481];
      }

      c2_cc_a = c2_Rtil(chartInstance, c2_k_phiInv);
      c2_yb_b = c2_rd[0];
      c2_xb_y = c2_cc_a * c2_yb_b;
      c2_PhiInvRd[0] = c2_xb_y;
      c2_d_ii = 0;
      while (c2_d_ii < 9) {
        c2_b_ii = 1.0 + (real_T)c2_d_ii;
        CV_EML_FOR(0, 1, 4, 1);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 400);
        c2_realmax(chartInstance);
        c2_realmax(chartInstance);
        for (c2_i482 = 0; c2_i482 < 1600; c2_i482++) {
          c2_l_phiInv[c2_i482] = c2_phiInv[c2_i482];
        }

        c2_Stil(chartInstance, c2_l_phiInv, c2_b_ii, c2_c_a);
        c2_dc_a = c2_b_ii - 1.0;
        c2_yb_y = c2_dc_a * 4.0;
        c2_ec_a = c2_b_ii - 1.0;
        c2_ac_y = c2_ec_a * 4.0;
        for (c2_i483 = 0; c2_i483 < 1600; c2_i483++) {
          c2_m_phiInv[c2_i483] = c2_phiInv[c2_i483];
        }

        c2_b_Qtil(chartInstance, c2_m_phiInv, c2_b_ii, c2_dv16);
        for (c2_i484 = 0; c2_i484 < 1600; c2_i484++) {
          c2_n_phiInv[c2_i484] = c2_phiInv[c2_i484];
        }

        c2_Stil(chartInstance, c2_n_phiInv, c2_b_ii, c2_bc_y);
        for (c2_i485 = 0; c2_i485 < 1600; c2_i485++) {
          c2_o_phiInv[c2_i485] = c2_phiInv[c2_i485];
        }

        c2_d0 = c2_b_Rtil(chartInstance, c2_o_phiInv, c2_b_ii);
        c2_i486 = 0;
        c2_i487 = 0;
        for (c2_i488 = 0; c2_i488 < 3; c2_i488++) {
          for (c2_i489 = 0; c2_i489 < 3; c2_i489++) {
            c2_v_b[c2_i489 + c2_i486] = c2_dv16[c2_i489 + c2_i487];
          }

          c2_i486 += 4;
          c2_i487 += 3;
        }

        for (c2_i490 = 0; c2_i490 < 3; c2_i490++) {
          c2_v_b[c2_i490 + 12] = c2_c_a[c2_i490];
        }

        c2_i491 = 0;
        for (c2_i492 = 0; c2_i492 < 3; c2_i492++) {
          c2_v_b[c2_i491 + 3] = c2_bc_y[c2_i492];
          c2_i491 += 4;
        }

        c2_v_b[15] = c2_d0;
        c2_d_m = c2_m + c2_ac_y;
        for (c2_i493 = 0; c2_i493 < 4; c2_i493++) {
          c2_s_b[c2_i493] = c2_rd[_SFD_EML_ARRAY_BOUNDS_CHECK("rd", (int32_T)
            _SFD_INTEGER_CHECK("m + (ii-1)*(m+n) + (1:(m+n))", c2_d_m + (1.0 +
            (real_T)c2_i493)), 1, 40, 1, 0) - 1];
        }

        c2_eb_eml_scalar_eg(chartInstance);
        c2_eb_eml_scalar_eg(chartInstance);
        for (c2_i494 = 0; c2_i494 < 4; c2_i494++) {
          c2_cc_y[c2_i494] = 0.0;
          c2_i495 = 0;
          for (c2_i496 = 0; c2_i496 < 4; c2_i496++) {
            c2_cc_y[c2_i494] += c2_v_b[c2_i495 + c2_i494] * c2_s_b[c2_i496];
            c2_i495 += 4;
          }
        }

        c2_e_m = c2_m + c2_yb_y;
        for (c2_i497 = 0; c2_i497 < 4; c2_i497++) {
          c2_PhiInvRd[_SFD_EML_ARRAY_BOUNDS_CHECK("PhiInvRd", (int32_T)
            _SFD_INTEGER_CHECK("m + (ii-1)*(m+n) + (1:(m+n))", c2_e_m + (1.0 +
            (real_T)c2_i497)), 1, 40, 1, 0) - 1] = c2_cc_y[c2_i497];
        }

        c2_d_ii++;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }

      CV_EML_FOR(0, 1, 4, 0);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 402);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      for (c2_i498 = 0; c2_i498 < 1600; c2_i498++) {
        c2_p_phiInv[c2_i498] = c2_phiInv[c2_i498];
      }

      c2_b_Qtil(chartInstance, c2_p_phiInv, 10.0, c2_yb_a);
      c2_f_m = c2_m + 36.0;
      for (c2_i499 = 0; c2_i499 < 3; c2_i499++) {
        c2_c_a[c2_i499] = c2_rd[_SFD_EML_ARRAY_BOUNDS_CHECK("rd", (int32_T)
          _SFD_INTEGER_CHECK("m + (T-1)*(m+n) +(1:n)", c2_f_m + (1.0 + (real_T)
          c2_i499)), 1, 40, 1, 0) - 1];
      }

      c2_eml_scalar_eg(chartInstance);
      c2_eml_scalar_eg(chartInstance);
      for (c2_i500 = 0; c2_i500 < 3; c2_i500++) {
        c2_bc_y[c2_i500] = 0.0;
        c2_i501 = 0;
        for (c2_i502 = 0; c2_i502 < 3; c2_i502++) {
          c2_bc_y[c2_i500] += c2_yb_a[c2_i501 + c2_i500] * c2_c_a[c2_i502];
          c2_i501 += 3;
        }
      }

      c2_g_m = c2_m + 36.0;
      for (c2_i503 = 0; c2_i503 < 3; c2_i503++) {
        c2_PhiInvRd[_SFD_EML_ARRAY_BOUNDS_CHECK("PhiInvRd", (int32_T)
          _SFD_INTEGER_CHECK("m + (T-1)*(m+n) +(1:n)", c2_g_m + (1.0 + (real_T)
          c2_i503)), 1, 40, 1, 0) - 1] = c2_bc_y[c2_i503];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 405);
      for (c2_i504 = 0; c2_i504 < 40; c2_i504++) {
        c2_b_PhiInvRd[c2_i504] = c2_PhiInvRd[c2_i504];
      }

      for (c2_i505 = 0; c2_i505 < 9; c2_i505++) {
        c2_f_A[c2_i505] = c2_A[c2_i505];
      }

      for (c2_i506 = 0; c2_i506 < 3; c2_i506++) {
        c2_c_B[c2_i506] = c2_B[c2_i506];
      }

      for (c2_i507 = 0; c2_i507 < 1280; c2_i507++) {
        c2_c_C[c2_i507] = c2_C[c2_i507];
      }

      for (c2_i508 = 0; c2_i508 < 6; c2_i508++) {
        c2_c_Ef[c2_i508] = c2_Ef[c2_i508];
      }

      for (c2_i509 = 0; c2_i509 < 9; c2_i509++) {
        c2_l_switches[c2_i509] = c2_switches[c2_i509];
      }

      c2_multByC(chartInstance, c2_b_PhiInvRd, c2_f_A, c2_c_B, c2_c_C, c2_c_Ef,
                 c2_l_switches, c2_i_y);
      for (c2_i510 = 0; c2_i510 < 32; c2_i510++) {
        c2_rhs[c2_i510] = c2_rp[c2_i510] - c2_i_y[c2_i510];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 408);
      if (CV_EML_IF(0, 1, 35, c2_flagChecking)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 409);
        for (c2_i511 = 0; c2_i511 < 1280; c2_i511++) {
          c2_i_a[c2_i511] = c2_C[c2_i511];
        }

        for (c2_i512 = 0; c2_i512 < 1600; c2_i512++) {
          c2_d_b[c2_i512] = c2_phiInv[c2_i512];
        }

        c2_ab_eml_scalar_eg(chartInstance);
        c2_ab_eml_scalar_eg(chartInstance);
        for (c2_i513 = 0; c2_i513 < 1280; c2_i513++) {
          c2_tb_y[c2_i513] = 0.0;
        }

        for (c2_i514 = 0; c2_i514 < 1280; c2_i514++) {
          c2_fc_a[c2_i514] = c2_i_a[c2_i514];
        }

        for (c2_i515 = 0; c2_i515 < 1600; c2_i515++) {
          c2_ac_b[c2_i515] = c2_d_b[c2_i515];
        }

        c2_v_eml_xgemm(chartInstance, c2_fc_a, c2_ac_b, c2_tb_y);
        for (c2_i516 = 0; c2_i516 < 40; c2_i516++) {
          c2_f_b[c2_i516] = c2_rd[c2_i516];
        }

        c2_d_eml_scalar_eg(chartInstance);
        c2_d_eml_scalar_eg(chartInstance);
        for (c2_i517 = 0; c2_i517 < 32; c2_i517++) {
          c2_i_y[c2_i517] = 0.0;
        }

        for (c2_i518 = 0; c2_i518 < 1280; c2_i518++) {
          c2_dc_y[c2_i518] = c2_tb_y[c2_i518];
        }

        for (c2_i519 = 0; c2_i519 < 40; c2_i519++) {
          c2_bc_b[c2_i519] = c2_f_b[c2_i519];
        }

        c2_o_eml_xgemm(chartInstance, c2_dc_y, c2_bc_b, c2_i_y);
        for (c2_i520 = 0; c2_i520 < 32; c2_i520++) {
          c2_b_rhs[c2_i520] = c2_rhs[c2_i520] - (c2_rp[c2_i520] - c2_i_y[c2_i520]);
        }

        c2_checkBeta = c2_norm(chartInstance, c2_b_rhs);
        sf_mex_printf("%s =\\n", "checkBeta");
        c2_f_u = c2_checkBeta;
        c2_ec_y = NULL;
        sf_mex_assign(&c2_ec_y, sf_mex_create("y", &c2_f_u, 0, 0U, 0U, 0U, 0),
                      FALSE);
        sf_mex_call_debug("disp", 0U, 1U, 14, c2_ec_y);
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 411);
        c2_checkBeta = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 415);
      for (c2_i521 = 0; c2_i521 < 1024; c2_i521++) {
        c2_L[c2_i521] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 416);
      for (c2_i522 = 0; c2_i522 < 1024; c2_i522++) {
        c2_e_Y[c2_i522] = c2_Y[c2_i522];
      }

      c2_getSqBlk(chartInstance, c2_e_Y, c2_dv16);
      for (c2_i523 = 0; c2_i523 < 9; c2_i523++) {
        c2_dv20[c2_i523] = c2_dv16[c2_i523];
      }

      c2_b_chol(chartInstance, c2_dv20, c2_dv21);
      c2_i524 = 0;
      c2_i525 = 0;
      for (c2_i526 = 0; c2_i526 < 3; c2_i526++) {
        for (c2_i527 = 0; c2_i527 < 3; c2_i527++) {
          c2_L[c2_i527 + c2_i524] = c2_dv21[c2_i527 + c2_i525];
        }

        c2_i524 += 32;
        c2_i525 += 3;
      }

      c2_e_ii = 0;
      while (c2_e_ii < 9) {
        c2_b_ii = 2.0 + (real_T)c2_e_ii;
        CV_EML_FOR(0, 1, 5, 1);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 418);
        c2_realmax(chartInstance);
        c2_realmax(chartInstance);
        c2_gc_a = c2_b_ii - 1.0;
        c2_fc_y = c2_gc_a * 3.0;
        c2_hc_a = c2_b_ii - 2.0;
        c2_gc_y = c2_hc_a * 3.0;
        for (c2_i528 = 0; c2_i528 < 1024; c2_i528++) {
          c2_b_L[c2_i528] = c2_L[c2_i528];
        }

        c2_b_getSqBlk(chartInstance, c2_b_L, c2_b_ii - 1.0, c2_b_ii - 1.0,
                      c2_dv16);
        for (c2_i529 = 0; c2_i529 < 1024; c2_i529++) {
          c2_f_Y[c2_i529] = c2_Y[c2_i529];
        }

        c2_b_getSqBlk(chartInstance, c2_f_Y, c2_b_ii - 1.0, c2_b_ii, c2_y_b);
        for (c2_i530 = 0; c2_i530 < 9; c2_i530++) {
          c2_dv22[c2_i530] = c2_dv16[c2_i530];
        }

        for (c2_i531 = 0; c2_i531 < 9; c2_i531++) {
          c2_cc_b[c2_i531] = c2_y_b[c2_i531];
        }

        c2_c_linsolve(chartInstance, c2_dv22, c2_cc_b, c2_dv16);
        for (c2_i532 = 0; c2_i532 < 3; c2_i532++) {
          for (c2_i533 = 0; c2_i533 < 3; c2_i533++) {
            c2_L[(_SFD_EML_ARRAY_BOUNDS_CHECK("L", (int32_T)_SFD_INTEGER_CHECK(
                    "(ii-1)*n+(1:n)", c2_fc_y + (1.0 + (real_T)c2_i533)), 1, 32,
                   1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("L", (int32_T)
                     _SFD_INTEGER_CHECK("(ii-2)*n+(1:n)", c2_gc_y + (1.0 +
                       (real_T)c2_i532)), 1, 32, 2, 0) - 1) << 5)) - 1] =
              c2_dv16[c2_i532 + 3 * c2_i533];
          }
        }

        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 419);
        c2_realmax(chartInstance);
        c2_realmax(chartInstance);
        c2_ic_a = c2_b_ii - 1.0;
        c2_hc_y = c2_ic_a * 3.0;
        c2_jc_a = c2_b_ii - 1.0;
        c2_ic_y = c2_jc_a * 3.0;
        for (c2_i534 = 0; c2_i534 < 1024; c2_i534++) {
          c2_c_L[c2_i534] = c2_L[c2_i534];
        }

        c2_b_getSqBlk(chartInstance, c2_c_L, c2_b_ii, c2_b_ii - 1.0, c2_yb_a);
        for (c2_i535 = 0; c2_i535 < 1024; c2_i535++) {
          c2_d_L[c2_i535] = c2_L[c2_i535];
        }

        c2_b_getSqBlk(chartInstance, c2_d_L, c2_b_ii, c2_b_ii - 1.0, c2_dv16);
        c2_i536 = 0;
        for (c2_i537 = 0; c2_i537 < 3; c2_i537++) {
          c2_i538 = 0;
          for (c2_i539 = 0; c2_i539 < 3; c2_i539++) {
            c2_y_b[c2_i539 + c2_i536] = c2_dv16[c2_i538 + c2_i537];
            c2_i538 += 3;
          }

          c2_i536 += 3;
        }

        c2_s_eml_scalar_eg(chartInstance);
        c2_s_eml_scalar_eg(chartInstance);
        for (c2_i540 = 0; c2_i540 < 3; c2_i540++) {
          c2_i541 = 0;
          for (c2_i542 = 0; c2_i542 < 3; c2_i542++) {
            c2_db_y[c2_i541 + c2_i540] = 0.0;
            c2_i543 = 0;
            for (c2_i544 = 0; c2_i544 < 3; c2_i544++) {
              c2_db_y[c2_i541 + c2_i540] += c2_yb_a[c2_i543 + c2_i540] *
                c2_y_b[c2_i544 + c2_i541];
              c2_i543 += 3;
            }

            c2_i541 += 3;
          }
        }

        for (c2_i545 = 0; c2_i545 < 1024; c2_i545++) {
          c2_g_Y[c2_i545] = c2_Y[c2_i545];
        }

        c2_b_getSqBlk(chartInstance, c2_g_Y, c2_b_ii, c2_b_ii, c2_dv16);
        for (c2_i546 = 0; c2_i546 < 9; c2_i546++) {
          c2_dv23[c2_i546] = c2_dv16[c2_i546] - c2_db_y[c2_i546];
        }

        c2_b_chol(chartInstance, c2_dv23, c2_dv24);
        for (c2_i547 = 0; c2_i547 < 3; c2_i547++) {
          for (c2_i548 = 0; c2_i548 < 3; c2_i548++) {
            c2_L[(_SFD_EML_ARRAY_BOUNDS_CHECK("L", (int32_T)_SFD_INTEGER_CHECK(
                    "(ii-1)*n+(1:n)", c2_hc_y + (1.0 + (real_T)c2_i548)), 1, 32,
                   1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("L", (int32_T)
                     _SFD_INTEGER_CHECK("(ii-1)*n+(1:n)", c2_ic_y + (1.0 +
                       (real_T)c2_i547)), 1, 32, 2, 0) - 1) << 5)) - 1] =
              c2_dv24[c2_i548 + 3 * c2_i547];
          }
        }

        c2_e_ii++;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }

      CV_EML_FOR(0, 1, 5, 0);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 423);
      CV_EML_IF(0, 1, 36, c2_ellef > 0.0);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 424);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      for (c2_i549 = 0; c2_i549 < 1024; c2_i549++) {
        c2_e_L[c2_i549] = c2_L[c2_i549];
      }

      c2_b_getSqBlk(chartInstance, c2_e_L, 10.0, 10.0, c2_dv16);
      for (c2_i550 = 0; c2_i550 < 9; c2_i550++) {
        c2_dv25[c2_i550] = c2_dv16[c2_i550];
      }

      c2_i551 = 0;
      c2_i552 = 0;
      for (c2_i553 = 0; c2_i553 < 2; c2_i553++) {
        for (c2_i554 = 0; c2_i554 < 3; c2_i554++) {
          c2_h_Y[c2_i554 + c2_i551] = c2_Y[(c2_i554 + c2_i552) + 987];
        }

        c2_i551 += 3;
        c2_i552 += 32;
      }

      c2_e_linsolve(chartInstance, c2_dv25, c2_h_Y, c2_ub_b);
      c2_i555 = 0;
      for (c2_i556 = 0; c2_i556 < 3; c2_i556++) {
        c2_i557 = 0;
        for (c2_i558 = 0; c2_i558 < 2; c2_i558++) {
          c2_L[(c2_i558 + c2_i555) + 894] = c2_ub_b[c2_i557 + c2_i556];
          c2_i557 += 3;
        }

        c2_i555 += 32;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 425);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_i559 = 0;
      c2_i560 = 0;
      for (c2_i561 = 0; c2_i561 < 3; c2_i561++) {
        for (c2_i562 = 0; c2_i562 < 2; c2_i562++) {
          c2_ac_a[c2_i562 + c2_i559] = c2_L[(c2_i562 + c2_i560) + 894];
        }

        c2_i559 += 2;
        c2_i560 += 32;
      }

      c2_i563 = 0;
      for (c2_i564 = 0; c2_i564 < 2; c2_i564++) {
        c2_i565 = 0;
        for (c2_i566 = 0; c2_i566 < 3; c2_i566++) {
          c2_ub_b[c2_i566 + c2_i563] = c2_L[(c2_i565 + c2_i564) + 894];
          c2_i565 += 32;
        }

        c2_i563 += 3;
      }

      c2_y_eml_scalar_eg(chartInstance);
      c2_y_eml_scalar_eg(chartInstance);
      for (c2_i567 = 0; c2_i567 < 2; c2_i567++) {
        c2_i568 = 0;
        c2_i569 = 0;
        for (c2_i570 = 0; c2_i570 < 2; c2_i570++) {
          c2_sb_y[c2_i568 + c2_i567] = 0.0;
          c2_i571 = 0;
          for (c2_i572 = 0; c2_i572 < 3; c2_i572++) {
            c2_sb_y[c2_i568 + c2_i567] += c2_ac_a[c2_i571 + c2_i567] *
              c2_ub_b[c2_i572 + c2_i569];
            c2_i571 += 2;
          }

          c2_i568 += 2;
          c2_i569 += 3;
        }
      }

      c2_i573 = 0;
      c2_i574 = 0;
      for (c2_i575 = 0; c2_i575 < 2; c2_i575++) {
        for (c2_i576 = 0; c2_i576 < 2; c2_i576++) {
          c2_i_Y[c2_i576 + c2_i573] = c2_Y[(c2_i576 + c2_i574) + 990] -
            c2_sb_y[c2_i576 + c2_i573];
        }

        c2_i573 += 2;
        c2_i574 += 32;
      }

      c2_c_chol(chartInstance, c2_i_Y, c2_dv26);
      c2_i577 = 0;
      c2_i578 = 0;
      for (c2_i579 = 0; c2_i579 < 2; c2_i579++) {
        for (c2_i580 = 0; c2_i580 < 2; c2_i580++) {
          c2_L[(c2_i580 + c2_i577) + 990] = c2_dv26[c2_i580 + c2_i578];
        }

        c2_i577 += 32;
        c2_i578 += 2;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 429);
      if (CV_EML_IF(0, 1, 37, c2_flagChecking)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 430);
        for (c2_i581 = 0; c2_i581 < 1024; c2_i581++) {
          c2_kc_a[c2_i581] = c2_L[c2_i581];
        }

        c2_i582 = 0;
        for (c2_i583 = 0; c2_i583 < 32; c2_i583++) {
          c2_i584 = 0;
          for (c2_i585 = 0; c2_i585 < 32; c2_i585++) {
            c2_dc_b[c2_i585 + c2_i582] = c2_L[c2_i584 + c2_i583];
            c2_i584 += 32;
          }

          c2_i582 += 32;
        }

        c2_db_eml_scalar_eg(chartInstance);
        c2_db_eml_scalar_eg(chartInstance);
        for (c2_i586 = 0; c2_i586 < 1024; c2_i586++) {
          c2_ub_y[c2_i586] = 0.0;
        }

        for (c2_i587 = 0; c2_i587 < 1024; c2_i587++) {
          c2_lc_a[c2_i587] = c2_kc_a[c2_i587];
        }

        for (c2_i588 = 0; c2_i588 < 1024; c2_i588++) {
          c2_ec_b[c2_i588] = c2_dc_b[c2_i588];
        }

        c2_x_eml_xgemm(chartInstance, c2_lc_a, c2_ec_b, c2_ub_y);
        for (c2_i589 = 0; c2_i589 < 1024; c2_i589++) {
          c2_jc_y[c2_i589] = c2_ub_y[c2_i589] - c2_Y[c2_i589];
        }

        c2_checkL = c2_e_norm(chartInstance, c2_jc_y);
        sf_mex_printf("%s =\\n", "checkL");
        c2_g_u = c2_checkL;
        c2_kc_y = NULL;
        sf_mex_assign(&c2_kc_y, sf_mex_create("y", &c2_g_u, 0, 0U, 0U, 0U, 0),
                      FALSE);
        sf_mex_call_debug("disp", 0U, 1U, 14, c2_kc_y);
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 432);
        c2_checkL = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 436);
      for (c2_i590 = 0; c2_i590 < 32; c2_i590++) {
        c2_t[c2_i590] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 437);
      for (c2_i591 = 0; c2_i591 < 1024; c2_i591++) {
        c2_f_L[c2_i591] = c2_L[c2_i591];
      }

      c2_getSqBlk(chartInstance, c2_f_L, c2_dv16);
      for (c2_i592 = 0; c2_i592 < 9; c2_i592++) {
        c2_dv27[c2_i592] = c2_dv16[c2_i592];
      }

      for (c2_i593 = 0; c2_i593 < 3; c2_i593++) {
        c2_c_rhs[c2_i593] = c2_rhs[c2_i593];
      }

      c2_f_linsolve(chartInstance, c2_dv27, c2_c_rhs, c2_c_a);
      for (c2_i594 = 0; c2_i594 < 3; c2_i594++) {
        c2_t[c2_i594] = c2_c_a[c2_i594];
      }

      c2_f_ii = 0;
      while (c2_f_ii < 9) {
        c2_b_ii = 1.0 + (real_T)c2_f_ii;
        CV_EML_FOR(0, 1, 6, 1);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 439);
        c2_realmax(chartInstance);
        c2_realmax(chartInstance);
        c2_realmax(chartInstance);
        c2_mc_a = c2_b_ii;
        c2_lc_y = c2_mc_a * 3.0;
        c2_nc_a = c2_b_ii;
        c2_mc_y = c2_nc_a * 3.0;
        c2_oc_a = c2_b_ii - 1.0;
        c2_nc_y = c2_oc_a * 3.0;
        for (c2_i595 = 0; c2_i595 < 1024; c2_i595++) {
          c2_g_L[c2_i595] = c2_L[c2_i595];
        }

        c2_b_getSqBlk(chartInstance, c2_g_L, c2_b_ii + 1.0, c2_b_ii, c2_yb_a);
        for (c2_i596 = 0; c2_i596 < 3; c2_i596++) {
          c2_c_a[c2_i596] = c2_t[_SFD_EML_ARRAY_BOUNDS_CHECK("t", (int32_T)
            _SFD_INTEGER_CHECK("(ii-1)*n + (1:n)", c2_nc_y + (1.0 + (real_T)
            c2_i596)), 1, 32, 1, 0) - 1];
        }

        c2_eml_scalar_eg(chartInstance);
        c2_eml_scalar_eg(chartInstance);
        for (c2_i597 = 0; c2_i597 < 3; c2_i597++) {
          c2_bc_y[c2_i597] = 0.0;
          c2_i598 = 0;
          for (c2_i599 = 0; c2_i599 < 3; c2_i599++) {
            c2_bc_y[c2_i597] += c2_yb_a[c2_i598 + c2_i597] * c2_c_a[c2_i599];
            c2_i598 += 3;
          }
        }

        for (c2_i600 = 0; c2_i600 < 1024; c2_i600++) {
          c2_h_L[c2_i600] = c2_L[c2_i600];
        }

        c2_b_getSqBlk(chartInstance, c2_h_L, c2_b_ii + 1.0, c2_b_ii + 1.0,
                      c2_dv16);
        for (c2_i601 = 0; c2_i601 < 9; c2_i601++) {
          c2_dv28[c2_i601] = c2_dv16[c2_i601];
        }

        for (c2_i602 = 0; c2_i602 < 3; c2_i602++) {
          c2_d_rhs[c2_i602] = c2_rhs[_SFD_EML_ARRAY_BOUNDS_CHECK("rhs", (int32_T)
            _SFD_INTEGER_CHECK("ii*n + (1:n)", c2_mc_y + (1.0 + (real_T)c2_i602)),
            1, 32, 1, 0) - 1] - c2_bc_y[c2_i602];
        }

        c2_f_linsolve(chartInstance, c2_dv28, c2_d_rhs, c2_c_a);
        for (c2_i603 = 0; c2_i603 < 3; c2_i603++) {
          c2_t[_SFD_EML_ARRAY_BOUNDS_CHECK("t", (int32_T)_SFD_INTEGER_CHECK(
            "ii*n + (1:n)", c2_lc_y + (1.0 + (real_T)c2_i603)), 1, 32, 1, 0) - 1]
            = c2_c_a[c2_i603];
        }

        c2_f_ii++;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }

      CV_EML_FOR(0, 1, 6, 0);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 442);
      CV_EML_IF(0, 1, 38, c2_ellef > 0.0);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 443);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_i604 = 0;
      c2_i605 = 0;
      for (c2_i606 = 0; c2_i606 < 3; c2_i606++) {
        for (c2_i607 = 0; c2_i607 < 2; c2_i607++) {
          c2_ac_a[c2_i607 + c2_i604] = c2_L[(c2_i607 + c2_i605) + 894];
        }

        c2_i604 += 2;
        c2_i605 += 32;
      }

      for (c2_i608 = 0; c2_i608 < 3; c2_i608++) {
        c2_c_a[c2_i608] = c2_t[c2_i608 + 27];
      }

      c2_e_eml_scalar_eg(chartInstance);
      c2_e_eml_scalar_eg(chartInstance);
      for (c2_i609 = 0; c2_i609 < 2; c2_i609++) {
        c2_oc_y[c2_i609] = 0.0;
        c2_i610 = 0;
        for (c2_i611 = 0; c2_i611 < 3; c2_i611++) {
          c2_oc_y[c2_i609] += c2_ac_a[c2_i610 + c2_i609] * c2_c_a[c2_i611];
          c2_i610 += 2;
        }
      }

      c2_i612 = 0;
      c2_i613 = 0;
      for (c2_i614 = 0; c2_i614 < 2; c2_i614++) {
        for (c2_i615 = 0; c2_i615 < 2; c2_i615++) {
          c2_i_L[c2_i615 + c2_i612] = c2_L[(c2_i615 + c2_i613) + 990];
        }

        c2_i612 += 2;
        c2_i613 += 32;
      }

      for (c2_i616 = 0; c2_i616 < 2; c2_i616++) {
        c2_e_rhs[c2_i616] = c2_rhs[c2_i616 + 30] - c2_oc_y[c2_i616];
      }

      c2_g_linsolve(chartInstance, c2_i_L, c2_e_rhs, c2_oc_y);
      for (c2_i617 = 0; c2_i617 < 2; c2_i617++) {
        c2_t[c2_i617 + 30] = c2_oc_y[c2_i617];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 447);
      if (CV_EML_IF(0, 1, 39, c2_flagChecking)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 448);
        for (c2_i618 = 0; c2_i618 < 1024; c2_i618++) {
          c2_kc_a[c2_i618] = c2_L[c2_i618];
        }

        for (c2_i619 = 0; c2_i619 < 32; c2_i619++) {
          c2_fc_b[c2_i619] = c2_t[c2_i619];
        }

        c2_gb_eml_scalar_eg(chartInstance);
        c2_gb_eml_scalar_eg(chartInstance);
        for (c2_i620 = 0; c2_i620 < 32; c2_i620++) {
          c2_i_y[c2_i620] = 0.0;
        }

        for (c2_i621 = 0; c2_i621 < 1024; c2_i621++) {
          c2_pc_a[c2_i621] = c2_kc_a[c2_i621];
        }

        for (c2_i622 = 0; c2_i622 < 32; c2_i622++) {
          c2_gc_b[c2_i622] = c2_fc_b[c2_i622];
        }

        c2_y_eml_xgemm(chartInstance, c2_pc_a, c2_gc_b, c2_i_y);
        for (c2_i623 = 0; c2_i623 < 32; c2_i623++) {
          c2_pc_y[c2_i623] = c2_i_y[c2_i623] - c2_rhs[c2_i623];
        }

        c2_check_t = c2_norm(chartInstance, c2_pc_y);
        sf_mex_printf("%s =\\n", "check_t");
        c2_h_u = c2_check_t;
        c2_qc_y = NULL;
        sf_mex_assign(&c2_qc_y, sf_mex_create("y", &c2_h_u, 0, 0U, 0U, 0U, 0),
                      FALSE);
        sf_mex_call_debug("disp", 0U, 1U, 14, c2_qc_y);
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 450);
        c2_check_t = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 454);
      for (c2_i624 = 0; c2_i624 < 32; c2_i624++) {
        c2_dnu[c2_i624] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 456);
      CV_EML_IF(0, 1, 40, c2_ellef > 0.0);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 457);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_i625 = 0;
      for (c2_i626 = 0; c2_i626 < 2; c2_i626++) {
        c2_i627 = 0;
        for (c2_i628 = 0; c2_i628 < 2; c2_i628++) {
          c2_j_L[c2_i628 + c2_i625] = c2_L[(c2_i627 + c2_i626) + 990];
          c2_i627 += 32;
        }

        c2_i625 += 2;
      }

      for (c2_i629 = 0; c2_i629 < 2; c2_i629++) {
        c2_b_t[c2_i629] = c2_t[c2_i629 + 30];
      }

      c2_h_linsolve(chartInstance, c2_j_L, c2_b_t, c2_oc_y);
      for (c2_i630 = 0; c2_i630 < 2; c2_i630++) {
        c2_dnu[c2_i630 + 30] = c2_oc_y[c2_i630];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 458);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_i631 = 0;
      for (c2_i632 = 0; c2_i632 < 2; c2_i632++) {
        c2_i633 = 0;
        for (c2_i634 = 0; c2_i634 < 3; c2_i634++) {
          c2_ub_b[c2_i634 + c2_i631] = c2_L[(c2_i633 + c2_i632) + 894];
          c2_i633 += 32;
        }

        c2_i631 += 3;
      }

      for (c2_i635 = 0; c2_i635 < 2; c2_i635++) {
        c2_oc_y[c2_i635] = c2_dnu[c2_i635 + 30];
      }

      c2_i_eml_scalar_eg(chartInstance);
      c2_i_eml_scalar_eg(chartInstance);
      for (c2_i636 = 0; c2_i636 < 3; c2_i636++) {
        c2_bc_y[c2_i636] = 0.0;
        c2_i637 = 0;
        for (c2_i638 = 0; c2_i638 < 2; c2_i638++) {
          c2_bc_y[c2_i636] += c2_ub_b[c2_i637 + c2_i636] * c2_oc_y[c2_i638];
          c2_i637 += 3;
        }
      }

      for (c2_i639 = 0; c2_i639 < 1024; c2_i639++) {
        c2_k_L[c2_i639] = c2_L[c2_i639];
      }

      c2_b_getSqBlk(chartInstance, c2_k_L, 10.0, 10.0, c2_dv16);
      c2_i640 = 0;
      for (c2_i641 = 0; c2_i641 < 3; c2_i641++) {
        c2_i642 = 0;
        for (c2_i643 = 0; c2_i643 < 3; c2_i643++) {
          c2_dv29[c2_i643 + c2_i640] = c2_dv16[c2_i642 + c2_i641];
          c2_i642 += 3;
        }

        c2_i640 += 3;
      }

      for (c2_i644 = 0; c2_i644 < 3; c2_i644++) {
        c2_c_t[c2_i644] = c2_t[c2_i644 + 27] - c2_bc_y[c2_i644];
      }

      c2_i_linsolve(chartInstance, c2_dv29, c2_c_t, c2_c_a);
      for (c2_i645 = 0; c2_i645 < 3; c2_i645++) {
        c2_dnu[c2_i645 + 27] = c2_c_a[c2_i645];
      }

      c2_g_ii = 0;
      while (c2_g_ii < 9) {
        c2_b_ii = 9.0 + -(real_T)c2_g_ii;
        CV_EML_FOR(0, 1, 7, 1);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 463);
        c2_realmax(chartInstance);
        c2_realmax(chartInstance);
        c2_realmax(chartInstance);
        c2_qc_a = c2_b_ii - 1.0;
        c2_rc_y = c2_qc_a * 3.0;
        c2_rc_a = c2_b_ii - 1.0;
        c2_sc_y = c2_rc_a * 3.0;
        c2_sc_a = c2_b_ii;
        c2_tc_y = c2_sc_a * 3.0;
        for (c2_i646 = 0; c2_i646 < 1024; c2_i646++) {
          c2_l_L[c2_i646] = c2_L[c2_i646];
        }

        c2_b_getSqBlk(chartInstance, c2_l_L, c2_b_ii + 1.0, c2_b_ii, c2_dv16);
        c2_i647 = 0;
        for (c2_i648 = 0; c2_i648 < 3; c2_i648++) {
          c2_i649 = 0;
          for (c2_i650 = 0; c2_i650 < 3; c2_i650++) {
            c2_yb_a[c2_i650 + c2_i647] = c2_dv16[c2_i649 + c2_i648];
            c2_i649 += 3;
          }

          c2_i647 += 3;
        }

        for (c2_i651 = 0; c2_i651 < 3; c2_i651++) {
          c2_c_a[c2_i651] = c2_dnu[_SFD_EML_ARRAY_BOUNDS_CHECK("dnu", (int32_T)
            _SFD_INTEGER_CHECK("(ii)*n + (1:n)", c2_tc_y + (1.0 + (real_T)
            c2_i651)), 1, 32, 1, 0) - 1];
        }

        c2_eml_scalar_eg(chartInstance);
        c2_eml_scalar_eg(chartInstance);
        for (c2_i652 = 0; c2_i652 < 3; c2_i652++) {
          c2_bc_y[c2_i652] = 0.0;
          c2_i653 = 0;
          for (c2_i654 = 0; c2_i654 < 3; c2_i654++) {
            c2_bc_y[c2_i652] += c2_yb_a[c2_i653 + c2_i652] * c2_c_a[c2_i654];
            c2_i653 += 3;
          }
        }

        for (c2_i655 = 0; c2_i655 < 1024; c2_i655++) {
          c2_m_L[c2_i655] = c2_L[c2_i655];
        }

        c2_b_getSqBlk(chartInstance, c2_m_L, c2_b_ii, c2_b_ii, c2_dv16);
        c2_i656 = 0;
        for (c2_i657 = 0; c2_i657 < 3; c2_i657++) {
          c2_i658 = 0;
          for (c2_i659 = 0; c2_i659 < 3; c2_i659++) {
            c2_dv30[c2_i659 + c2_i656] = c2_dv16[c2_i658 + c2_i657];
            c2_i658 += 3;
          }

          c2_i656 += 3;
        }

        for (c2_i660 = 0; c2_i660 < 3; c2_i660++) {
          c2_d_t[c2_i660] = c2_t[_SFD_EML_ARRAY_BOUNDS_CHECK("t", (int32_T)
            _SFD_INTEGER_CHECK("(ii-1)*n + (1:n)", c2_sc_y + (1.0 + (real_T)
            c2_i660)), 1, 32, 1, 0) - 1] - c2_bc_y[c2_i660];
        }

        c2_i_linsolve(chartInstance, c2_dv30, c2_d_t, c2_c_a);
        for (c2_i661 = 0; c2_i661 < 3; c2_i661++) {
          c2_dnu[_SFD_EML_ARRAY_BOUNDS_CHECK("dnu", (int32_T)_SFD_INTEGER_CHECK(
            "(ii-1)*n + (1:n)", c2_rc_y + (1.0 + (real_T)c2_i661)), 1, 32, 1, 0)
            - 1] = c2_c_a[c2_i661];
        }

        c2_g_ii++;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }

      CV_EML_FOR(0, 1, 7, 0);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 467);
      if (CV_EML_IF(0, 1, 41, c2_flagChecking)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 468);
        for (c2_i662 = 0; c2_i662 < 1024; c2_i662++) {
          c2_kc_a[c2_i662] = c2_Y[c2_i662];
        }

        for (c2_i663 = 0; c2_i663 < 32; c2_i663++) {
          c2_fc_b[c2_i663] = c2_dnu[c2_i663];
        }

        c2_gb_eml_scalar_eg(chartInstance);
        c2_gb_eml_scalar_eg(chartInstance);
        for (c2_i664 = 0; c2_i664 < 32; c2_i664++) {
          c2_i_y[c2_i664] = 0.0;
        }

        for (c2_i665 = 0; c2_i665 < 1024; c2_i665++) {
          c2_tc_a[c2_i665] = c2_kc_a[c2_i665];
        }

        for (c2_i666 = 0; c2_i666 < 32; c2_i666++) {
          c2_hc_b[c2_i666] = c2_fc_b[c2_i666];
        }

        c2_y_eml_xgemm(chartInstance, c2_tc_a, c2_hc_b, c2_i_y);
        for (c2_i667 = 0; c2_i667 < 32; c2_i667++) {
          c2_uc_y[c2_i667] = c2_i_y[c2_i667] - c2_rhs[c2_i667];
        }

        c2_check_dnu = c2_norm(chartInstance, c2_uc_y);
        sf_mex_printf("%s =\\n", "check_dnu");
        c2_i_u = c2_check_dnu;
        c2_vc_y = NULL;
        sf_mex_assign(&c2_vc_y, sf_mex_create("y", &c2_i_u, 0, 0U, 0U, 0U, 0),
                      FALSE);
        sf_mex_call_debug("disp", 0U, 1U, 14, c2_vc_y);
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 470);
        c2_check_dnu = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 517);
      for (c2_i668 = 0; c2_i668 < 32; c2_i668++) {
        c2_b_dnu[c2_i668] = c2_dnu[c2_i668];
      }

      for (c2_i669 = 0; c2_i669 < 1280; c2_i669++) {
        c2_c_CT[c2_i669] = c2_CT[c2_i669];
      }

      for (c2_i670 = 0; c2_i670 < 9; c2_i670++) {
        c2_e_AT[c2_i670] = c2_AT[c2_i670];
      }

      for (c2_i671 = 0; c2_i671 < 3; c2_i671++) {
        c2_c_BT[c2_i671] = c2_BT[c2_i671];
      }

      for (c2_i672 = 0; c2_i672 < 6; c2_i672++) {
        c2_c_EfT[c2_i672] = c2_EfT[c2_i672];
      }

      for (c2_i673 = 0; c2_i673 < 9; c2_i673++) {
        c2_m_switches[c2_i673] = c2_switches[c2_i673];
      }

      c2_multByCT(chartInstance, c2_b_dnu, c2_c_CT, c2_e_AT, c2_c_BT, c2_c_EfT,
                  c2_m_switches, c2_dv6);
      for (c2_i674 = 0; c2_i674 < 40; c2_i674++) {
        c2_v[c2_i674] = -c2_rd[c2_i674] - c2_dv6[c2_i674];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 520);
      if (CV_EML_IF(0, 1, 42, c2_flagChecking)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 523);
        c2_i675 = 0;
        for (c2_i676 = 0; c2_i676 < 32; c2_i676++) {
          c2_i677 = 0;
          for (c2_i678 = 0; c2_i678 < 40; c2_i678++) {
            c2_wb_b[c2_i678 + c2_i675] = c2_C[c2_i677 + c2_i676];
            c2_i677 += 32;
          }

          c2_i675 += 40;
        }

        for (c2_i679 = 0; c2_i679 < 32; c2_i679++) {
          c2_fc_b[c2_i679] = c2_dnu[c2_i679];
        }

        c2_g_eml_scalar_eg(chartInstance);
        c2_g_eml_scalar_eg(chartInstance);
        for (c2_i680 = 0; c2_i680 < 40; c2_i680++) {
          c2_f_y[c2_i680] = 0.0;
        }

        for (c2_i681 = 0; c2_i681 < 1280; c2_i681++) {
          c2_ic_b[c2_i681] = c2_wb_b[c2_i681];
        }

        for (c2_i682 = 0; c2_i682 < 32; c2_i682++) {
          c2_jc_b[c2_i682] = c2_fc_b[c2_i682];
        }

        c2_q_eml_xgemm(chartInstance, c2_ic_b, c2_jc_b, c2_f_y);
        for (c2_i683 = 0; c2_i683 < 40; c2_i683++) {
          c2_b_v[c2_i683] = c2_v[c2_i683] - (-c2_rd[c2_i683] - c2_f_y[c2_i683]);
        }

        c2_checkV = c2_b_norm(chartInstance, c2_b_v);
        sf_mex_printf("%s =\\n", "checkV");
        c2_j_u = c2_checkV;
        c2_wc_y = NULL;
        sf_mex_assign(&c2_wc_y, sf_mex_create("y", &c2_j_u, 0, 0U, 0U, 0U, 0),
                      FALSE);
        sf_mex_call_debug("disp", 0U, 1U, 14, c2_wc_y);
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 525);
        c2_checkV = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 529);
      if (CV_EML_IF(0, 1, 43, c2_flagPhiIsDiag)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 532);
        for (c2_i684 = 0; c2_i684 < 1600; c2_i684++) {
          c2_q_phiInv[c2_i684] = c2_phiInv[c2_i684];
        }

        c2_diag(chartInstance, c2_q_phiInv, c2_dv6);
        for (c2_i685 = 0; c2_i685 < 32; c2_i685++) {
          c2_c_dnu[c2_i685] = c2_dnu[c2_i685];
        }

        for (c2_i686 = 0; c2_i686 < 1280; c2_i686++) {
          c2_d_CT[c2_i686] = c2_CT[c2_i686];
        }

        for (c2_i687 = 0; c2_i687 < 9; c2_i687++) {
          c2_f_AT[c2_i687] = c2_AT[c2_i687];
        }

        for (c2_i688 = 0; c2_i688 < 3; c2_i688++) {
          c2_d_BT[c2_i688] = c2_BT[c2_i688];
        }

        for (c2_i689 = 0; c2_i689 < 6; c2_i689++) {
          c2_d_EfT[c2_i689] = c2_EfT[c2_i689];
        }

        for (c2_i690 = 0; c2_i690 < 9; c2_i690++) {
          c2_n_switches[c2_i690] = c2_switches[c2_i690];
        }

        c2_multByCT(chartInstance, c2_c_dnu, c2_d_CT, c2_f_AT, c2_d_BT, c2_d_EfT,
                    c2_n_switches, c2_f_b);
        for (c2_i691 = 0; c2_i691 < 40; c2_i691++) {
          c2_dz[c2_i691] = c2_dv6[c2_i691] * (-c2_rd[c2_i691] - c2_f_b[c2_i691]);
        }
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 537);
        for (c2_i692 = 0; c2_i692 < 32; c2_i692++) {
          c2_d_dnu[c2_i692] = c2_dnu[c2_i692];
        }

        for (c2_i693 = 0; c2_i693 < 1280; c2_i693++) {
          c2_e_CT[c2_i693] = c2_CT[c2_i693];
        }

        for (c2_i694 = 0; c2_i694 < 9; c2_i694++) {
          c2_g_AT[c2_i694] = c2_AT[c2_i694];
        }

        for (c2_i695 = 0; c2_i695 < 3; c2_i695++) {
          c2_e_BT[c2_i695] = c2_BT[c2_i695];
        }

        for (c2_i696 = 0; c2_i696 < 6; c2_i696++) {
          c2_e_EfT[c2_i696] = c2_EfT[c2_i696];
        }

        for (c2_i697 = 0; c2_i697 < 9; c2_i697++) {
          c2_o_switches[c2_i697] = c2_switches[c2_i697];
        }

        c2_multByCT(chartInstance, c2_d_dnu, c2_e_CT, c2_g_AT, c2_e_BT, c2_e_EfT,
                    c2_o_switches, c2_dv6);
        for (c2_i698 = 0; c2_i698 < 40; c2_i698++) {
          c2_v[c2_i698] = -c2_rd[c2_i698] - c2_dv6[c2_i698];
        }

        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 540);
        for (c2_i699 = 0; c2_i699 < 1600; c2_i699++) {
          c2_r_phiInv[c2_i699] = c2_phiInv[c2_i699];
        }

        c2_uc_a = c2_Rtil(chartInstance, c2_r_phiInv);
        c2_kc_b = c2_v[0];
        c2_xc_y = c2_uc_a * c2_kc_b;
        c2_dz[0] = c2_xc_y;
        c2_h_ii = 0;
        while (c2_h_ii < 9) {
          c2_b_ii = 1.0 + (real_T)c2_h_ii;
          CV_EML_FOR(0, 1, 8, 1);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 542);
          c2_realmax(chartInstance);
          c2_realmax(chartInstance);
          for (c2_i700 = 0; c2_i700 < 1600; c2_i700++) {
            c2_s_phiInv[c2_i700] = c2_phiInv[c2_i700];
          }

          c2_Stil(chartInstance, c2_s_phiInv, c2_b_ii, c2_c_a);
          c2_vc_a = c2_b_ii - 1.0;
          c2_yc_y = c2_vc_a * 4.0;
          c2_wc_a = c2_b_ii - 1.0;
          c2_ad_y = c2_wc_a * 4.0;
          for (c2_i701 = 0; c2_i701 < 1600; c2_i701++) {
            c2_t_phiInv[c2_i701] = c2_phiInv[c2_i701];
          }

          c2_b_Qtil(chartInstance, c2_t_phiInv, c2_b_ii, c2_dv16);
          for (c2_i702 = 0; c2_i702 < 1600; c2_i702++) {
            c2_u_phiInv[c2_i702] = c2_phiInv[c2_i702];
          }

          c2_Stil(chartInstance, c2_u_phiInv, c2_b_ii, c2_bc_y);
          for (c2_i703 = 0; c2_i703 < 1600; c2_i703++) {
            c2_v_phiInv[c2_i703] = c2_phiInv[c2_i703];
          }

          c2_d1 = c2_b_Rtil(chartInstance, c2_v_phiInv, c2_b_ii);
          c2_i704 = 0;
          c2_i705 = 0;
          for (c2_i706 = 0; c2_i706 < 3; c2_i706++) {
            for (c2_i707 = 0; c2_i707 < 3; c2_i707++) {
              c2_v_b[c2_i707 + c2_i704] = c2_dv16[c2_i707 + c2_i705];
            }

            c2_i704 += 4;
            c2_i705 += 3;
          }

          for (c2_i708 = 0; c2_i708 < 3; c2_i708++) {
            c2_v_b[c2_i708 + 12] = c2_c_a[c2_i708];
          }

          c2_i709 = 0;
          for (c2_i710 = 0; c2_i710 < 3; c2_i710++) {
            c2_v_b[c2_i709 + 3] = c2_bc_y[c2_i710];
            c2_i709 += 4;
          }

          c2_v_b[15] = c2_d1;
          c2_h_m = c2_m + c2_ad_y;
          for (c2_i711 = 0; c2_i711 < 4; c2_i711++) {
            c2_s_b[c2_i711] = c2_v[_SFD_EML_ARRAY_BOUNDS_CHECK("v", (int32_T)
              _SFD_INTEGER_CHECK("m + (ii-1)*(m+n) + (1:(m+n))", c2_h_m + (1.0 +
              (real_T)c2_i711)), 1, 40, 1, 0) - 1];
          }

          c2_eb_eml_scalar_eg(chartInstance);
          c2_eb_eml_scalar_eg(chartInstance);
          for (c2_i712 = 0; c2_i712 < 4; c2_i712++) {
            c2_cc_y[c2_i712] = 0.0;
            c2_i713 = 0;
            for (c2_i714 = 0; c2_i714 < 4; c2_i714++) {
              c2_cc_y[c2_i712] += c2_v_b[c2_i713 + c2_i712] * c2_s_b[c2_i714];
              c2_i713 += 4;
            }
          }

          c2_i_m = c2_m + c2_yc_y;
          for (c2_i715 = 0; c2_i715 < 4; c2_i715++) {
            c2_dz[_SFD_EML_ARRAY_BOUNDS_CHECK("dz", (int32_T)_SFD_INTEGER_CHECK(
              "m + (ii-1)*(m+n) + (1:(m+n))", c2_i_m + (1.0 + (real_T)c2_i715)),
              1, 40, 1, 0) - 1] = c2_cc_y[c2_i715];
          }

          c2_h_ii++;
          sf_mex_listen_for_ctrl_c(chartInstance->S);
        }

        CV_EML_FOR(0, 1, 8, 0);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 544);
        c2_realmax(chartInstance);
        c2_realmax(chartInstance);
        for (c2_i716 = 0; c2_i716 < 1600; c2_i716++) {
          c2_w_phiInv[c2_i716] = c2_phiInv[c2_i716];
        }

        c2_b_Qtil(chartInstance, c2_w_phiInv, 10.0, c2_yb_a);
        c2_j_m = c2_m + 36.0;
        for (c2_i717 = 0; c2_i717 < 3; c2_i717++) {
          c2_c_a[c2_i717] = c2_v[_SFD_EML_ARRAY_BOUNDS_CHECK("v", (int32_T)
            _SFD_INTEGER_CHECK("m + (T-1)*(m+n) +(1:n)", c2_j_m + (1.0 + (real_T)
            c2_i717)), 1, 40, 1, 0) - 1];
        }

        c2_eml_scalar_eg(chartInstance);
        c2_eml_scalar_eg(chartInstance);
        for (c2_i718 = 0; c2_i718 < 3; c2_i718++) {
          c2_bc_y[c2_i718] = 0.0;
          c2_i719 = 0;
          for (c2_i720 = 0; c2_i720 < 3; c2_i720++) {
            c2_bc_y[c2_i718] += c2_yb_a[c2_i719 + c2_i718] * c2_c_a[c2_i720];
            c2_i719 += 3;
          }
        }

        c2_k_m = c2_m + 36.0;
        for (c2_i721 = 0; c2_i721 < 3; c2_i721++) {
          c2_dz[_SFD_EML_ARRAY_BOUNDS_CHECK("dz", (int32_T)_SFD_INTEGER_CHECK(
            "m + (T-1)*(m+n) +(1:n)", c2_k_m + (1.0 + (real_T)c2_i721)), 1, 40,
            1, 0) - 1] = c2_bc_y[c2_i721];
        }
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 549);
      if (CV_EML_IF(0, 1, 44, c2_flagChecking)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 551);
        c2_i722 = 0;
        c2_i723 = 0;
        for (c2_i724 = 0; c2_i724 < 40; c2_i724++) {
          for (c2_i725 = 0; c2_i725 < 40; c2_i725++) {
            c2_xc_a[c2_i725 + c2_i722] = c2_phi[c2_i725 + c2_i723];
          }

          c2_i722 += 72;
          c2_i723 += 40;
        }

        c2_i726 = 0;
        for (c2_i727 = 0; c2_i727 < 32; c2_i727++) {
          c2_i728 = 0;
          for (c2_i729 = 0; c2_i729 < 40; c2_i729++) {
            c2_xc_a[(c2_i729 + c2_i726) + 2880] = c2_C[c2_i728 + c2_i727];
            c2_i728 += 32;
          }

          c2_i726 += 72;
        }

        c2_i730 = 0;
        c2_i731 = 0;
        for (c2_i732 = 0; c2_i732 < 40; c2_i732++) {
          for (c2_i733 = 0; c2_i733 < 32; c2_i733++) {
            c2_xc_a[(c2_i733 + c2_i730) + 40] = c2_C[c2_i733 + c2_i731];
          }

          c2_i730 += 72;
          c2_i731 += 32;
        }

        c2_i734 = 0;
        for (c2_i735 = 0; c2_i735 < 32; c2_i735++) {
          for (c2_i736 = 0; c2_i736 < 32; c2_i736++) {
            c2_xc_a[(c2_i736 + c2_i734) + 2920] = 0.0;
          }

          c2_i734 += 72;
        }

        for (c2_i737 = 0; c2_i737 < 40; c2_i737++) {
          c2_lc_b[c2_i737] = c2_dz[c2_i737];
        }

        for (c2_i738 = 0; c2_i738 < 32; c2_i738++) {
          c2_lc_b[c2_i738 + 40] = c2_dnu[c2_i738];
        }

        c2_hb_eml_scalar_eg(chartInstance);
        c2_hb_eml_scalar_eg(chartInstance);
        for (c2_i739 = 0; c2_i739 < 72; c2_i739++) {
          c2_bd_y[c2_i739] = 0.0;
        }

        for (c2_i740 = 0; c2_i740 < 5184; c2_i740++) {
          c2_yc_a[c2_i740] = c2_xc_a[c2_i740];
        }

        for (c2_i741 = 0; c2_i741 < 72; c2_i741++) {
          c2_mc_b[c2_i741] = c2_lc_b[c2_i741];
        }

        c2_ab_eml_xgemm(chartInstance, c2_yc_a, c2_mc_b, c2_bd_y);
        for (c2_i742 = 0; c2_i742 < 40; c2_i742++) {
          c2_c_rd[c2_i742] = c2_rd[c2_i742];
        }

        for (c2_i743 = 0; c2_i743 < 32; c2_i743++) {
          c2_c_rd[c2_i743 + 40] = c2_rp[c2_i743];
        }

        for (c2_i744 = 0; c2_i744 < 72; c2_i744++) {
          c2_cd_y[c2_i744] = c2_bd_y[c2_i744] + c2_c_rd[c2_i744];
        }

        c2_checkNewton = c2_f_norm(chartInstance, c2_cd_y);
        sf_mex_printf("%s =\\n", "checkNewton");
        c2_k_u = c2_checkNewton;
        c2_dd_y = NULL;
        sf_mex_assign(&c2_dd_y, sf_mex_create("y", &c2_k_u, 0, 0U, 0U, 0U, 0),
                      FALSE);
        sf_mex_call_debug("disp", 0U, 1U, 14, c2_dd_y);
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 553);
        c2_checkNewton = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 557);
      c2_sMax = 1.0;
      c2_jj = 0;
      do {
        exitg2 = 0;
        if (c2_jj < 10) {
          CV_EML_FOR(0, 1, 9, 1);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 562);
          c2_ad_a = c2_sMax;
          for (c2_i745 = 0; c2_i745 < 40; c2_i745++) {
            c2_f_b[c2_i745] = c2_dz[c2_i745];
          }

          for (c2_i746 = 0; c2_i746 < 40; c2_i746++) {
            c2_f_b[c2_i746] *= c2_ad_a;
          }

          for (c2_i747 = 0; c2_i747 < 40; c2_i747++) {
            c2_zFar[c2_i747] = c2_z[c2_i747] + c2_f_b[c2_i747];
          }

          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 563);
          for (c2_i748 = 0; c2_i748 < 40; c2_i748++) {
            c2_b_zFar[c2_i748] = c2_zFar[c2_i748];
          }

          for (c2_i749 = 0; c2_i749 < 1760; c2_i749++) {
            c2_c_P[c2_i749] = c2_P[c2_i749];
          }

          for (c2_i750 = 0; c2_i750 < 12; c2_i750++) {
            c2_c_Fx[c2_i750] = c2_Fx[c2_i750];
          }

          for (c2_i751 = 0; c2_i751 < 4; c2_i751++) {
            c2_c_Fu[c2_i751] = c2_Fu[c2_i751];
          }

          for (c2_i752 = 0; c2_i752 < 12; c2_i752++) {
            c2_c_Ff[c2_i752] = c2_Ff[c2_i752];
          }

          for (c2_i753 = 0; c2_i753 < 9; c2_i753++) {
            c2_p_switches[c2_i753] = c2_switches[c2_i753];
          }

          c2_multByP(chartInstance, c2_b_zFar, c2_c_P, c2_c_Fx, c2_c_Fu, c2_c_Ff,
                     c2_p_switches, c2_y);
          for (c2_i754 = 0; c2_i754 < 44; c2_i754++) {
            c2_iFar[c2_i754] = c2_h[c2_i754] - c2_y[c2_i754];
          }

          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 565);
          for (c2_i755 = 0; c2_i755 < 44; c2_i755++) {
            c2_b_iFar[c2_i755] = (c2_iFar[c2_i755] > 0.0);
          }

          if (CV_EML_IF(0, 1, 45, c2_all(chartInstance, c2_b_iFar))) {
            exitg2 = 1;
          } else {
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 569);
            c2_bd_a = c2_sMax;
            c2_sMax = c2_bd_a * 0.5;
            c2_jj++;
            sf_mex_listen_for_ctrl_c(chartInstance->S);
          }
        } else {
          CV_EML_FOR(0, 1, 9, 0);
          exitg2 = 1;
        }
      } while (exitg2 == 0U);

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 574);
      c2_g_A = c2_sMax;
      c2_e_x = c2_g_A;
      c2_f_x = c2_e_x;
      c2_s = c2_f_x / 100.0;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 575);
      c2_cd_a = c2_s;
      for (c2_i756 = 0; c2_i756 < 40; c2_i756++) {
        c2_f_b[c2_i756] = c2_dz[c2_i756];
      }

      for (c2_i757 = 0; c2_i757 < 40; c2_i757++) {
        c2_f_b[c2_i757] *= c2_cd_a;
      }

      for (c2_i758 = 0; c2_i758 < 40; c2_i758++) {
        c2_zNew[c2_i758] = c2_z[c2_i758] + c2_f_b[c2_i758];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 576);
      c2_dd_a = c2_s;
      for (c2_i759 = 0; c2_i759 < 32; c2_i759++) {
        c2_fc_b[c2_i759] = c2_dnu[c2_i759];
      }

      for (c2_i760 = 0; c2_i760 < 32; c2_i760++) {
        c2_fc_b[c2_i760] *= c2_dd_a;
      }

      for (c2_i761 = 0; c2_i761 < 32; c2_i761++) {
        c2_nuNew[c2_i761] = c2_nu[c2_i761] + c2_fc_b[c2_i761];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 577);
      for (c2_i762 = 0; c2_i762 < 40; c2_i762++) {
        c2_b_zNew[c2_i762] = c2_zNew[c2_i762];
      }

      for (c2_i763 = 0; c2_i763 < 1760; c2_i763++) {
        c2_d_P[c2_i763] = c2_P[c2_i763];
      }

      for (c2_i764 = 0; c2_i764 < 12; c2_i764++) {
        c2_d_Fx[c2_i764] = c2_Fx[c2_i764];
      }

      for (c2_i765 = 0; c2_i765 < 4; c2_i765++) {
        c2_d_Fu[c2_i765] = c2_Fu[c2_i765];
      }

      for (c2_i766 = 0; c2_i766 < 12; c2_i766++) {
        c2_d_Ff[c2_i766] = c2_Ff[c2_i766];
      }

      for (c2_i767 = 0; c2_i767 < 9; c2_i767++) {
        c2_q_switches[c2_i767] = c2_switches[c2_i767];
      }

      c2_multByP(chartInstance, c2_b_zNew, c2_d_P, c2_d_Fx, c2_d_Fu, c2_d_Ff,
                 c2_q_switches, c2_y);
      for (c2_i768 = 0; c2_i768 < 44; c2_i768++) {
        c2_iNew[c2_i768] = c2_h[c2_i768] - c2_y[c2_i768];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 579);
      for (c2_i769 = 0; c2_i769 < 44; c2_i769++) {
        c2_b_iNew[c2_i769] = c2_iNew[c2_i769];
      }

      c2_rdivide(chartInstance, 1.0, c2_b_iNew, c2_dv31);
      for (c2_i770 = 0; c2_i770 < 44; c2_i770++) {
        c2_dNew[c2_i770] = c2_dv31[c2_i770];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 580);
      for (c2_i771 = 0; c2_i771 < 1760; c2_i771++) {
        c2_c_b[c2_i771] = c2_kappaPt[c2_i771];
      }

      for (c2_i772 = 0; c2_i772 < 44; c2_i772++) {
        c2_y[c2_i772] = c2_dNew[c2_i772];
      }

      c2_f_eml_scalar_eg(chartInstance);
      c2_f_eml_scalar_eg(chartInstance);
      for (c2_i773 = 0; c2_i773 < 40; c2_i773++) {
        c2_f_y[c2_i773] = 0.0;
      }

      for (c2_i774 = 0; c2_i774 < 1760; c2_i774++) {
        c2_nc_b[c2_i774] = c2_c_b[c2_i774];
      }

      for (c2_i775 = 0; c2_i775 < 44; c2_i775++) {
        c2_ed_y[c2_i775] = c2_y[c2_i775];
      }

      c2_p_eml_xgemm(chartInstance, c2_nc_b, c2_ed_y, c2_f_y);
      for (c2_i776 = 0; c2_i776 < 32; c2_i776++) {
        c2_b_nuNew[c2_i776] = c2_nuNew[c2_i776];
      }

      for (c2_i777 = 0; c2_i777 < 1280; c2_i777++) {
        c2_f_CT[c2_i777] = c2_CT[c2_i777];
      }

      for (c2_i778 = 0; c2_i778 < 9; c2_i778++) {
        c2_h_AT[c2_i778] = c2_AT[c2_i778];
      }

      for (c2_i779 = 0; c2_i779 < 3; c2_i779++) {
        c2_f_BT[c2_i779] = c2_BT[c2_i779];
      }

      for (c2_i780 = 0; c2_i780 < 6; c2_i780++) {
        c2_f_EfT[c2_i780] = c2_EfT[c2_i780];
      }

      for (c2_i781 = 0; c2_i781 < 9; c2_i781++) {
        c2_r_switches[c2_i781] = c2_switches[c2_i781];
      }

      c2_multByCT(chartInstance, c2_b_nuNew, c2_f_CT, c2_h_AT, c2_f_BT, c2_f_EfT,
                  c2_r_switches, c2_dv6);
      for (c2_i782 = 0; c2_i782 < 40; c2_i782++) {
        c2_rdNew[c2_i782] = ((c2_diagTwoH[c2_i782] * c2_zNew[c2_i782] +
                              c2_g[c2_i782]) + c2_f_y[c2_i782]) + c2_dv6[c2_i782];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 581);
      if (CV_EML_IF(0, 1, 46, c2_flagUseSoftCons)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 582);
        for (c2_i783 = 0; c2_i783 < 40; c2_i783++) {
          c2_c_zNew[c2_i783] = c2_zNew[c2_i783];
        }

        for (c2_i784 = 0; c2_i784 < 1600; c2_i784++) {
          c2_c_Ps[c2_i784] = c2_Ps[c2_i784];
        }

        for (c2_i785 = 0; c2_i785 < 12; c2_i785++) {
          c2_c_Fxs[c2_i785] = c2_Fxs[c2_i785];
        }

        for (c2_i786 = 0; c2_i786 < 4; c2_i786++) {
          c2_c_Fus[c2_i786] = c2_Fus[c2_i786];
        }

        for (c2_i787 = 0; c2_i787 < 40; c2_i787++) {
          c2_c_hs[c2_i787] = c2_hs[c2_i787];
        }

        for (c2_i788 = 0; c2_i788 < 9; c2_i788++) {
          c2_s_switches[c2_i788] = c2_switches[c2_i788];
        }

        c2_b_calcDs(chartInstance, c2_c_zNew, c2_c_Ps, c2_c_Fxs, c2_c_Fus,
                    c2_c_hs, c2_rho, c2_flagNoPade, c2_s_switches, c2_f_b,
                    c2_f_y);
        for (c2_i789 = 0; c2_i789 < 40; c2_i789++) {
          c2_dsNew[c2_i789] = c2_f_b[c2_i789];
        }

        for (c2_i790 = 0; c2_i790 < 40; c2_i790++) {
          c2_esNew[c2_i790] = c2_f_y[c2_i790];
        }

        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 583);
        for (c2_i791 = 0; c2_i791 < 40; c2_i791++) {
          c2_b_dsNew[c2_i791] = c2_dsNew[c2_i791];
        }

        for (c2_i792 = 0; c2_i792 < 1600; c2_i792++) {
          c2_c_PsT[c2_i792] = c2_PsT[c2_i792];
        }

        for (c2_i793 = 0; c2_i793 < 12; c2_i793++) {
          c2_c_FxsT[c2_i793] = c2_FxsT[c2_i793];
        }

        for (c2_i794 = 0; c2_i794 < 4; c2_i794++) {
          c2_c_FusT[c2_i794] = c2_FusT[c2_i794];
        }

        for (c2_i795 = 0; c2_i795 < 9; c2_i795++) {
          c2_t_switches[c2_i795] = c2_switches[c2_i795];
        }

        c2_multByPsT(chartInstance, c2_b_dsNew, c2_c_PsT, c2_c_FxsT, c2_c_FusT,
                     c2_t_switches, c2_dv6);
        for (c2_i796 = 0; c2_i796 < 40; c2_i796++) {
          c2_rdNew[c2_i796] += c2_dv6[c2_i796];
        }
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 587);
      for (c2_i797 = 0; c2_i797 < 40; c2_i797++) {
        c2_d_zNew[c2_i797] = c2_zNew[c2_i797];
      }

      for (c2_i798 = 0; c2_i798 < 32; c2_i798++) {
        c2_oc_b[c2_i798] = c2_b[c2_i798];
      }

      for (c2_i799 = 0; c2_i799 < 9; c2_i799++) {
        c2_h_A[c2_i799] = c2_A[c2_i799];
      }

      for (c2_i800 = 0; c2_i800 < 3; c2_i800++) {
        c2_d_B[c2_i800] = c2_B[c2_i800];
      }

      for (c2_i801 = 0; c2_i801 < 1280; c2_i801++) {
        c2_d_C[c2_i801] = c2_C[c2_i801];
      }

      for (c2_i802 = 0; c2_i802 < 6; c2_i802++) {
        c2_d_Ef[c2_i802] = c2_Ef[c2_i802];
      }

      for (c2_i803 = 0; c2_i803 < 9; c2_i803++) {
        c2_u_switches[c2_i803] = c2_switches[c2_i803];
      }

      c2_calcRp(chartInstance, c2_d_zNew, c2_oc_b, c2_h_A, c2_d_B, c2_d_C,
                c2_d_Ef, c2_u_switches, c2_dv32);
      for (c2_i804 = 0; c2_i804 < 32; c2_i804++) {
        c2_rpNew[c2_i804] = c2_dv32[c2_i804];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 588);
      for (c2_i805 = 0; c2_i805 < 40; c2_i805++) {
        c2_b_rdNew[c2_i805] = c2_rdNew[c2_i805];
      }

      c2_rdMagNew = c2_b_norm(chartInstance, c2_b_rdNew);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 589);
      for (c2_i806 = 0; c2_i806 < 32; c2_i806++) {
        c2_b_rpNew[c2_i806] = c2_rpNew[c2_i806];
      }

      c2_rpMagNew = c2_norm(chartInstance, c2_b_rpNew);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 590);
      c2_b_rdMagNew[0] = c2_rdMagNew;
      c2_b_rdMagNew[1] = c2_rpMagNew;
      c2_rMagNew = c2_c_norm(chartInstance, c2_b_rdMagNew);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 591);
      c2_pc_b = c2_rMagNew - c2_rMag;
      c2_gradRmag = 100.0 * c2_pc_b;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 606);
      c2_s = c2_sMax;
      c2_b_jj = 1.0;
      c2_c_jj = 0;
      do {
        exitg1 = 0;
        if (c2_c_jj < 10) {
          c2_b_jj = 1.0 + (real_T)c2_c_jj;
          CV_EML_FOR(0, 1, 10, 1);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 609);
          c2_ed_a = c2_s;
          for (c2_i807 = 0; c2_i807 < 40; c2_i807++) {
            c2_f_b[c2_i807] = c2_dz[c2_i807];
          }

          for (c2_i808 = 0; c2_i808 < 40; c2_i808++) {
            c2_f_b[c2_i808] *= c2_ed_a;
          }

          for (c2_i809 = 0; c2_i809 < 40; c2_i809++) {
            c2_zNew[c2_i809] = c2_z[c2_i809] + c2_f_b[c2_i809];
          }

          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 610);
          c2_fd_a = c2_s;
          for (c2_i810 = 0; c2_i810 < 32; c2_i810++) {
            c2_fc_b[c2_i810] = c2_dnu[c2_i810];
          }

          for (c2_i811 = 0; c2_i811 < 32; c2_i811++) {
            c2_fc_b[c2_i811] *= c2_fd_a;
          }

          for (c2_i812 = 0; c2_i812 < 32; c2_i812++) {
            c2_nuNew[c2_i812] = c2_nu[c2_i812] + c2_fc_b[c2_i812];
          }

          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 611);
          for (c2_i813 = 0; c2_i813 < 40; c2_i813++) {
            c2_e_zNew[c2_i813] = c2_zNew[c2_i813];
          }

          for (c2_i814 = 0; c2_i814 < 1760; c2_i814++) {
            c2_e_P[c2_i814] = c2_P[c2_i814];
          }

          for (c2_i815 = 0; c2_i815 < 12; c2_i815++) {
            c2_e_Fx[c2_i815] = c2_Fx[c2_i815];
          }

          for (c2_i816 = 0; c2_i816 < 4; c2_i816++) {
            c2_e_Fu[c2_i816] = c2_Fu[c2_i816];
          }

          for (c2_i817 = 0; c2_i817 < 12; c2_i817++) {
            c2_e_Ff[c2_i817] = c2_Ff[c2_i817];
          }

          for (c2_i818 = 0; c2_i818 < 9; c2_i818++) {
            c2_v_switches[c2_i818] = c2_switches[c2_i818];
          }

          c2_multByP(chartInstance, c2_e_zNew, c2_e_P, c2_e_Fx, c2_e_Fu, c2_e_Ff,
                     c2_v_switches, c2_y);
          for (c2_i819 = 0; c2_i819 < 44; c2_i819++) {
            c2_iNew[c2_i819] = c2_h[c2_i819] - c2_y[c2_i819];
          }

          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 614);
          for (c2_i820 = 0; c2_i820 < 44; c2_i820++) {
            c2_c_iNew[c2_i820] = c2_iNew[c2_i820];
          }

          c2_rdivide(chartInstance, 1.0, c2_c_iNew, c2_dv33);
          for (c2_i821 = 0; c2_i821 < 44; c2_i821++) {
            c2_dNew[c2_i821] = c2_dv33[c2_i821];
          }

          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 615);
          for (c2_i822 = 0; c2_i822 < 1760; c2_i822++) {
            c2_c_b[c2_i822] = c2_kappaPt[c2_i822];
          }

          for (c2_i823 = 0; c2_i823 < 44; c2_i823++) {
            c2_y[c2_i823] = c2_dNew[c2_i823];
          }

          c2_f_eml_scalar_eg(chartInstance);
          c2_f_eml_scalar_eg(chartInstance);
          for (c2_i824 = 0; c2_i824 < 40; c2_i824++) {
            c2_f_y[c2_i824] = 0.0;
          }

          for (c2_i825 = 0; c2_i825 < 1760; c2_i825++) {
            c2_qc_b[c2_i825] = c2_c_b[c2_i825];
          }

          for (c2_i826 = 0; c2_i826 < 44; c2_i826++) {
            c2_fd_y[c2_i826] = c2_y[c2_i826];
          }

          c2_p_eml_xgemm(chartInstance, c2_qc_b, c2_fd_y, c2_f_y);
          for (c2_i827 = 0; c2_i827 < 32; c2_i827++) {
            c2_c_nuNew[c2_i827] = c2_nuNew[c2_i827];
          }

          for (c2_i828 = 0; c2_i828 < 1280; c2_i828++) {
            c2_g_CT[c2_i828] = c2_CT[c2_i828];
          }

          for (c2_i829 = 0; c2_i829 < 9; c2_i829++) {
            c2_i_AT[c2_i829] = c2_AT[c2_i829];
          }

          for (c2_i830 = 0; c2_i830 < 3; c2_i830++) {
            c2_g_BT[c2_i830] = c2_BT[c2_i830];
          }

          for (c2_i831 = 0; c2_i831 < 6; c2_i831++) {
            c2_g_EfT[c2_i831] = c2_EfT[c2_i831];
          }

          for (c2_i832 = 0; c2_i832 < 9; c2_i832++) {
            c2_w_switches[c2_i832] = c2_switches[c2_i832];
          }

          c2_multByCT(chartInstance, c2_c_nuNew, c2_g_CT, c2_i_AT, c2_g_BT,
                      c2_g_EfT, c2_w_switches, c2_dv6);
          for (c2_i833 = 0; c2_i833 < 40; c2_i833++) {
            c2_rdNew[c2_i833] = ((c2_diagTwoH[c2_i833] * c2_zNew[c2_i833] +
                                  c2_g[c2_i833]) + c2_f_y[c2_i833]) +
              c2_dv6[c2_i833];
          }

          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 616);
          if (CV_EML_IF(0, 1, 47, c2_flagUseSoftCons)) {
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 617);
            for (c2_i834 = 0; c2_i834 < 40; c2_i834++) {
              c2_f_zNew[c2_i834] = c2_zNew[c2_i834];
            }

            for (c2_i835 = 0; c2_i835 < 1600; c2_i835++) {
              c2_d_Ps[c2_i835] = c2_Ps[c2_i835];
            }

            for (c2_i836 = 0; c2_i836 < 12; c2_i836++) {
              c2_d_Fxs[c2_i836] = c2_Fxs[c2_i836];
            }

            for (c2_i837 = 0; c2_i837 < 4; c2_i837++) {
              c2_d_Fus[c2_i837] = c2_Fus[c2_i837];
            }

            for (c2_i838 = 0; c2_i838 < 40; c2_i838++) {
              c2_d_hs[c2_i838] = c2_hs[c2_i838];
            }

            for (c2_i839 = 0; c2_i839 < 9; c2_i839++) {
              c2_x_switches[c2_i839] = c2_switches[c2_i839];
            }

            c2_b_calcDs(chartInstance, c2_f_zNew, c2_d_Ps, c2_d_Fxs, c2_d_Fus,
                        c2_d_hs, c2_rho, c2_flagNoPade, c2_x_switches, c2_f_b,
                        c2_f_y);
            for (c2_i840 = 0; c2_i840 < 40; c2_i840++) {
              c2_dsNew[c2_i840] = c2_f_b[c2_i840];
            }

            for (c2_i841 = 0; c2_i841 < 40; c2_i841++) {
              c2_esNew[c2_i841] = c2_f_y[c2_i841];
            }

            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 618);
            for (c2_i842 = 0; c2_i842 < 40; c2_i842++) {
              c2_c_dsNew[c2_i842] = c2_dsNew[c2_i842];
            }

            for (c2_i843 = 0; c2_i843 < 1600; c2_i843++) {
              c2_d_PsT[c2_i843] = c2_PsT[c2_i843];
            }

            for (c2_i844 = 0; c2_i844 < 12; c2_i844++) {
              c2_d_FxsT[c2_i844] = c2_FxsT[c2_i844];
            }

            for (c2_i845 = 0; c2_i845 < 4; c2_i845++) {
              c2_d_FusT[c2_i845] = c2_FusT[c2_i845];
            }

            for (c2_i846 = 0; c2_i846 < 9; c2_i846++) {
              c2_y_switches[c2_i846] = c2_switches[c2_i846];
            }

            c2_multByPsT(chartInstance, c2_c_dsNew, c2_d_PsT, c2_d_FxsT,
                         c2_d_FusT, c2_y_switches, c2_dv6);
            for (c2_i847 = 0; c2_i847 < 40; c2_i847++) {
              c2_rdNew[c2_i847] += c2_dv6[c2_i847];
            }
          }

          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 620);
          for (c2_i848 = 0; c2_i848 < 40; c2_i848++) {
            c2_g_zNew[c2_i848] = c2_zNew[c2_i848];
          }

          for (c2_i849 = 0; c2_i849 < 32; c2_i849++) {
            c2_rc_b[c2_i849] = c2_b[c2_i849];
          }

          for (c2_i850 = 0; c2_i850 < 9; c2_i850++) {
            c2_i_A[c2_i850] = c2_A[c2_i850];
          }

          for (c2_i851 = 0; c2_i851 < 3; c2_i851++) {
            c2_e_B[c2_i851] = c2_B[c2_i851];
          }

          for (c2_i852 = 0; c2_i852 < 1280; c2_i852++) {
            c2_e_C[c2_i852] = c2_C[c2_i852];
          }

          for (c2_i853 = 0; c2_i853 < 6; c2_i853++) {
            c2_e_Ef[c2_i853] = c2_Ef[c2_i853];
          }

          for (c2_i854 = 0; c2_i854 < 9; c2_i854++) {
            c2_ab_switches[c2_i854] = c2_switches[c2_i854];
          }

          c2_calcRp(chartInstance, c2_g_zNew, c2_rc_b, c2_i_A, c2_e_B, c2_e_C,
                    c2_e_Ef, c2_ab_switches, c2_dv34);
          for (c2_i855 = 0; c2_i855 < 32; c2_i855++) {
            c2_rpNew[c2_i855] = c2_dv34[c2_i855];
          }

          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 621);
          for (c2_i856 = 0; c2_i856 < 40; c2_i856++) {
            c2_c_rdNew[c2_i856] = c2_rdNew[c2_i856];
          }

          c2_rdMagNew = c2_b_norm(chartInstance, c2_c_rdNew);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 622);
          for (c2_i857 = 0; c2_i857 < 32; c2_i857++) {
            c2_c_rpNew[c2_i857] = c2_rpNew[c2_i857];
          }

          c2_rpMagNew = c2_norm(chartInstance, c2_c_rpNew);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 623);
          c2_c_rdMagNew[0] = c2_rdMagNew;
          c2_c_rdMagNew[1] = c2_rpMagNew;
          c2_rMagNew = c2_c_norm(chartInstance, c2_c_rdMagNew);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 626);
          c2_sc_b = c2_s;
          c2_gd_y = 0.5 * c2_sc_b;
          c2_gd_a = c2_gd_y;
          c2_tc_b = c2_gradRmag;
          c2_hd_y = c2_gd_a * c2_tc_b;
          if (CV_EML_IF(0, 1, 48, c2_rMagNew < c2_rMag + c2_hd_y)) {
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 629);
            for (c2_i858 = 0; c2_i858 < 40; c2_i858++) {
              c2_z[c2_i858] = c2_zNew[c2_i858];
            }

            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 630);
            for (c2_i859 = 0; c2_i859 < 32; c2_i859++) {
              c2_nu[c2_i859] = c2_nuNew[c2_i859];
            }

            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 631);
            for (c2_i860 = 0; c2_i860 < 44; c2_i860++) {
              c2_d[c2_i860] = c2_dNew[c2_i860];
            }

            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 632);
            for (c2_i861 = 0; c2_i861 < 40; c2_i861++) {
              c2_rd[c2_i861] = c2_rdNew[c2_i861];
            }

            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 633);
            for (c2_i862 = 0; c2_i862 < 32; c2_i862++) {
              c2_rp[c2_i862] = c2_rpNew[c2_i862];
            }

            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 634);
            c2_rpMag = c2_rpMagNew;
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 635);
            c2_rdMag = c2_rdMagNew;
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 636);
            c2_rMag = c2_rMagNew;
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 638);
            if (CV_EML_IF(0, 1, 49, c2_flagUseSoftCons)) {
              _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 640);
              for (c2_i863 = 0; c2_i863 < 40; c2_i863++) {
                c2_ds[c2_i863] = c2_dsNew[c2_i863];
              }

              _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 641);
              for (c2_i864 = 0; c2_i864 < 40; c2_i864++) {
                c2_es[c2_i864] = c2_esNew[c2_i864];
              }
            }

            exitg1 = 1;
          } else {
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 652);
            c2_hd_a = c2_s;
            c2_s = c2_hd_a * 0.7;
            c2_c_jj++;
            sf_mex_listen_for_ctrl_c(chartInstance->S);
          }
        } else {
          CV_EML_FOR(0, 1, 10, 0);
          exitg1 = 1;
        }
      } while (exitg1 == 0U);

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 711);
      c2_totBackTracks += c2_b_jj;
      c2_kk++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 1, 0);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 715);
    c2_id_a = c2_kappa;
    c2_kappa = c2_id_a * 0.2;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 716);
    c2_jd_a = c2_rho;
    c2_rho = c2_jd_a * 5.0;
    c2_ww++;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 721);
  c2_info[0] = c2_rpMag;
  c2_info[1] = c2_rdMag;
  c2_info[2] = c2_initSolChoice;
  c2_info[3] = c2_totBackTracks;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -721);
  sf_debug_symbol_scope_pop();
  for (c2_i865 = 0; c2_i865 < 40; c2_i865++) {
    (*c2_e_z)[c2_i865] = c2_z[c2_i865];
  }

  for (c2_i866 = 0; c2_i866 < 4; c2_i866++) {
    (*c2_b_info)[c2_i866] = c2_info[c2_i866];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_mpcSetpointIntptCoupled
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i867;
  real_T c2_b_inData[4];
  int32_T c2_i868;
  real_T c2_u[4];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i867 = 0; c2_i867 < 4; c2_i867++) {
    c2_b_inData[c2_i867] = (*(real_T (*)[4])c2_inData)[c2_i867];
  }

  for (c2_i868 = 0; c2_i868 < 4; c2_i868++) {
    c2_u[c2_i868] = c2_b_inData[c2_i868];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_info, const char_T *c2_identifier, real_T
  c2_y[4])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_info), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_info);
}

static void c2_b_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[4])
{
  real_T c2_dv35[4];
  int32_T c2_i869;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv35, 1, 0, 0U, 1, 0U, 1, 4);
  for (c2_i869 = 0; c2_i869 < 4; c2_i869++) {
    c2_y[c2_i869] = c2_dv35[c2_i869];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_info;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[4];
  int32_T c2_i870;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_info = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_info), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_info);
  for (c2_i870 = 0; c2_i870 < 4; c2_i870++) {
    (*(real_T (*)[4])c2_outData)[c2_i870] = c2_y[c2_i870];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i871;
  real_T c2_b_inData[40];
  int32_T c2_i872;
  real_T c2_u[40];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i871 = 0; c2_i871 < 40; c2_i871++) {
    c2_b_inData[c2_i871] = (*(real_T (*)[40])c2_inData)[c2_i871];
  }

  for (c2_i872 = 0; c2_i872 < 40; c2_i872++) {
    c2_u[c2_i872] = c2_b_inData[c2_i872];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 40), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_c_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_z, const char_T *c2_identifier, real_T c2_y
  [40])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_z), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_z);
}

static void c2_d_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[40])
{
  real_T c2_dv36[40];
  int32_T c2_i873;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv36, 1, 0, 0U, 1, 0U, 1, 40);
  for (c2_i873 = 0; c2_i873 < 40; c2_i873++) {
    c2_y[c2_i873] = c2_dv36[c2_i873];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_z;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[40];
  int32_T c2_i874;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_z = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_z), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_z);
  for (c2_i874 = 0; c2_i874 < 40; c2_i874++) {
    (*(real_T (*)[40])c2_outData)[c2_i874] = c2_y[c2_i874];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i875;
  int32_T c2_i876;
  int32_T c2_i877;
  real_T c2_b_inData[12];
  int32_T c2_i878;
  int32_T c2_i879;
  int32_T c2_i880;
  real_T c2_u[12];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i875 = 0;
  for (c2_i876 = 0; c2_i876 < 3; c2_i876++) {
    for (c2_i877 = 0; c2_i877 < 4; c2_i877++) {
      c2_b_inData[c2_i877 + c2_i875] = (*(real_T (*)[12])c2_inData)[c2_i877 +
        c2_i875];
    }

    c2_i875 += 4;
  }

  c2_i878 = 0;
  for (c2_i879 = 0; c2_i879 < 3; c2_i879++) {
    for (c2_i880 = 0; c2_i880 < 4; c2_i880++) {
      c2_u[c2_i880 + c2_i878] = c2_b_inData[c2_i880 + c2_i878];
    }

    c2_i878 += 4;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 4, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i881;
  int32_T c2_i882;
  int32_T c2_i883;
  real_T c2_b_inData[6];
  int32_T c2_i884;
  int32_T c2_i885;
  int32_T c2_i886;
  real_T c2_u[6];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i881 = 0;
  for (c2_i882 = 0; c2_i882 < 3; c2_i882++) {
    for (c2_i883 = 0; c2_i883 < 2; c2_i883++) {
      c2_b_inData[c2_i883 + c2_i881] = (*(real_T (*)[6])c2_inData)[c2_i883 +
        c2_i881];
    }

    c2_i881 += 2;
  }

  c2_i884 = 0;
  for (c2_i885 = 0; c2_i885 < 3; c2_i885++) {
    for (c2_i886 = 0; c2_i886 < 2; c2_i886++) {
      c2_u[c2_i886 + c2_i884] = c2_b_inData[c2_i886 + c2_i884];
    }

    c2_i884 += 2;
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
  int32_T c2_i887;
  int32_T c2_i888;
  int32_T c2_i889;
  real_T c2_b_inData[1600];
  int32_T c2_i890;
  int32_T c2_i891;
  int32_T c2_i892;
  real_T c2_u[1600];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i887 = 0;
  for (c2_i888 = 0; c2_i888 < 40; c2_i888++) {
    for (c2_i889 = 0; c2_i889 < 40; c2_i889++) {
      c2_b_inData[c2_i889 + c2_i887] = (*(real_T (*)[1600])c2_inData)[c2_i889 +
        c2_i887];
    }

    c2_i887 += 40;
  }

  c2_i890 = 0;
  for (c2_i891 = 0; c2_i891 < 40; c2_i891++) {
    for (c2_i892 = 0; c2_i892 < 40; c2_i892++) {
      c2_u[c2_i892 + c2_i890] = c2_b_inData[c2_i892 + c2_i890];
    }

    c2_i890 += 40;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 40, 40), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i893;
  real_T c2_b_inData[8];
  int32_T c2_i894;
  real_T c2_u[8];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i893 = 0; c2_i893 < 8; c2_i893++) {
    c2_b_inData[c2_i893] = (*(real_T (*)[8])c2_inData)[c2_i893];
  }

  for (c2_i894 = 0; c2_i894 < 8; c2_i894++) {
    c2_u[c2_i894] = c2_b_inData[c2_i894];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 8), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i895;
  int32_T c2_i896;
  int32_T c2_i897;
  real_T c2_b_inData[9];
  int32_T c2_i898;
  int32_T c2_i899;
  int32_T c2_i900;
  real_T c2_u[9];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i895 = 0;
  for (c2_i896 = 0; c2_i896 < 3; c2_i896++) {
    for (c2_i897 = 0; c2_i897 < 3; c2_i897++) {
      c2_b_inData[c2_i897 + c2_i895] = (*(real_T (*)[9])c2_inData)[c2_i897 +
        c2_i895];
    }

    c2_i895 += 3;
  }

  c2_i898 = 0;
  for (c2_i899 = 0; c2_i899 < 3; c2_i899++) {
    for (c2_i900 = 0; c2_i900 < 3; c2_i900++) {
      c2_u[c2_i900 + c2_i898] = c2_b_inData[c2_i900 + c2_i898];
    }

    c2_i898 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i901;
  real_T c2_b_inData[3];
  int32_T c2_i902;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i901 = 0; c2_i901 < 3; c2_i901++) {
    c2_b_inData[c2_i901] = (*(real_T (*)[3])c2_inData)[c2_i901];
  }

  for (c2_i902 = 0; c2_i902 < 3; c2_i902++) {
    c2_u[c2_i902] = c2_b_inData[c2_i902];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i903;
  real_T c2_b_inData[32];
  int32_T c2_i904;
  real_T c2_u[32];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i903 = 0; c2_i903 < 32; c2_i903++) {
    c2_b_inData[c2_i903] = (*(real_T (*)[32])c2_inData)[c2_i903];
  }

  for (c2_i904 = 0; c2_i904 < 32; c2_i904++) {
    c2_u[c2_i904] = c2_b_inData[c2_i904];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 32), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i905;
  int32_T c2_i906;
  int32_T c2_i907;
  real_T c2_b_inData[1280];
  int32_T c2_i908;
  int32_T c2_i909;
  int32_T c2_i910;
  real_T c2_u[1280];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i905 = 0;
  for (c2_i906 = 0; c2_i906 < 40; c2_i906++) {
    for (c2_i907 = 0; c2_i907 < 32; c2_i907++) {
      c2_b_inData[c2_i907 + c2_i905] = (*(real_T (*)[1280])c2_inData)[c2_i907 +
        c2_i905];
    }

    c2_i905 += 32;
  }

  c2_i908 = 0;
  for (c2_i909 = 0; c2_i909 < 40; c2_i909++) {
    for (c2_i910 = 0; c2_i910 < 32; c2_i910++) {
      c2_u[c2_i910 + c2_i908] = c2_b_inData[c2_i910 + c2_i908];
    }

    c2_i908 += 32;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 32, 40), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_l_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i911;
  real_T c2_b_inData[44];
  int32_T c2_i912;
  real_T c2_u[44];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i911 = 0; c2_i911 < 44; c2_i911++) {
    c2_b_inData[c2_i911] = (*(real_T (*)[44])c2_inData)[c2_i911];
  }

  for (c2_i912 = 0; c2_i912 < 44; c2_i912++) {
    c2_u[c2_i912] = c2_b_inData[c2_i912];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 44), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_m_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i913;
  int32_T c2_i914;
  int32_T c2_i915;
  real_T c2_b_inData[1760];
  int32_T c2_i916;
  int32_T c2_i917;
  int32_T c2_i918;
  real_T c2_u[1760];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i913 = 0;
  for (c2_i914 = 0; c2_i914 < 40; c2_i914++) {
    for (c2_i915 = 0; c2_i915 < 44; c2_i915++) {
      c2_b_inData[c2_i915 + c2_i913] = (*(real_T (*)[1760])c2_inData)[c2_i915 +
        c2_i913];
    }

    c2_i913 += 44;
  }

  c2_i916 = 0;
  for (c2_i917 = 0; c2_i917 < 40; c2_i917++) {
    for (c2_i918 = 0; c2_i918 < 44; c2_i918++) {
      c2_u[c2_i918 + c2_i916] = c2_b_inData[c2_i918 + c2_i916];
    }

    c2_i916 += 44;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 44, 40), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_e_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d2;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d2, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d2;
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
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_f_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[32])
{
  real_T c2_dv37[32];
  int32_T c2_i919;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv37, 1, 0, 0U, 1, 0U, 1, 32);
  for (c2_i919 = 0; c2_i919 < 32; c2_i919++) {
    c2_y[c2_i919] = c2_dv37[c2_i919];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_rpNew;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[32];
  int32_T c2_i920;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_rpNew = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_rpNew), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_rpNew);
  for (c2_i920 = 0; c2_i920 < 32; c2_i920++) {
    (*(real_T (*)[32])c2_outData)[c2_i920] = c2_y[c2_i920];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_g_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[44])
{
  real_T c2_dv38[44];
  int32_T c2_i921;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv38, 1, 0, 0U, 1, 0U, 1, 44);
  for (c2_i921 = 0; c2_i921 < 44; c2_i921++) {
    c2_y[c2_i921] = c2_dv38[c2_i921];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_dNew;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[44];
  int32_T c2_i922;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_dNew = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_dNew), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_dNew);
  for (c2_i922 = 0; c2_i922 < 44; c2_i922++) {
    (*(real_T (*)[44])c2_outData)[c2_i922] = c2_y[c2_i922];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_n_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i923;
  int32_T c2_i924;
  int32_T c2_i925;
  real_T c2_b_inData[1024];
  int32_T c2_i926;
  int32_T c2_i927;
  int32_T c2_i928;
  real_T c2_u[1024];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i923 = 0;
  for (c2_i924 = 0; c2_i924 < 32; c2_i924++) {
    for (c2_i925 = 0; c2_i925 < 32; c2_i925++) {
      c2_b_inData[c2_i925 + c2_i923] = (*(real_T (*)[1024])c2_inData)[c2_i925 +
        c2_i923];
    }

    c2_i923 += 32;
  }

  c2_i926 = 0;
  for (c2_i927 = 0; c2_i927 < 32; c2_i927++) {
    for (c2_i928 = 0; c2_i928 < 32; c2_i928++) {
      c2_u[c2_i928 + c2_i926] = c2_b_inData[c2_i928 + c2_i926];
    }

    c2_i926 += 32;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 32, 32), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_h_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[1024])
{
  real_T c2_dv39[1024];
  int32_T c2_i929;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv39, 1, 0, 0U, 1, 0U, 2, 32,
                32);
  for (c2_i929 = 0; c2_i929 < 1024; c2_i929++) {
    c2_y[c2_i929] = c2_dv39[c2_i929];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_L;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[1024];
  int32_T c2_i930;
  int32_T c2_i931;
  int32_T c2_i932;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_L = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_L), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_L);
  c2_i930 = 0;
  for (c2_i931 = 0; c2_i931 < 32; c2_i931++) {
    for (c2_i932 = 0; c2_i932 < 32; c2_i932++) {
      (*(real_T (*)[1024])c2_outData)[c2_i932 + c2_i930] = c2_y[c2_i932 +
        c2_i930];
    }

    c2_i930 += 32;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_i_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[9])
{
  real_T c2_dv40[9];
  int32_T c2_i933;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv40, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c2_i933 = 0; c2_i933 < 9; c2_i933++) {
    c2_y[c2_i933] = c2_dv40[c2_i933];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_tmp;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[9];
  int32_T c2_i934;
  int32_T c2_i935;
  int32_T c2_i936;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_tmp = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_tmp), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_tmp);
  c2_i934 = 0;
  for (c2_i935 = 0; c2_i935 < 3; c2_i935++) {
    for (c2_i936 = 0; c2_i936 < 3; c2_i936++) {
      (*(real_T (*)[9])c2_outData)[c2_i936 + c2_i934] = c2_y[c2_i936 + c2_i934];
    }

    c2_i934 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_o_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i937;
  int32_T c2_i938;
  int32_T c2_i939;
  real_T c2_b_inData[16];
  int32_T c2_i940;
  int32_T c2_i941;
  int32_T c2_i942;
  real_T c2_u[16];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i937 = 0;
  for (c2_i938 = 0; c2_i938 < 4; c2_i938++) {
    for (c2_i939 = 0; c2_i939 < 4; c2_i939++) {
      c2_b_inData[c2_i939 + c2_i937] = (*(real_T (*)[16])c2_inData)[c2_i939 +
        c2_i937];
    }

    c2_i937 += 4;
  }

  c2_i940 = 0;
  for (c2_i941 = 0; c2_i941 < 4; c2_i941++) {
    for (c2_i942 = 0; c2_i942 < 4; c2_i942++) {
      c2_u[c2_i942 + c2_i940] = c2_b_inData[c2_i942 + c2_i940];
    }

    c2_i940 += 4;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 4, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_j_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[16])
{
  real_T c2_dv41[16];
  int32_T c2_i943;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv41, 1, 0, 0U, 1, 0U, 2, 4, 4);
  for (c2_i943 = 0; c2_i943 < 16; c2_i943++) {
    c2_y[c2_i943] = c2_dv41[c2_i943];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_blkInv;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[16];
  int32_T c2_i944;
  int32_T c2_i945;
  int32_T c2_i946;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_blkInv = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_blkInv), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_blkInv);
  c2_i944 = 0;
  for (c2_i945 = 0; c2_i945 < 4; c2_i945++) {
    for (c2_i946 = 0; c2_i946 < 4; c2_i946++) {
      (*(real_T (*)[16])c2_outData)[c2_i946 + c2_i944] = c2_y[c2_i946 + c2_i944];
    }

    c2_i944 += 4;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_k_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[1600])
{
  real_T c2_dv42[1600];
  int32_T c2_i947;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv42, 1, 0, 0U, 1, 0U, 2, 40,
                40);
  for (c2_i947 = 0; c2_i947 < 1600; c2_i947++) {
    c2_y[c2_i947] = c2_dv42[c2_i947];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_phiInv;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[1600];
  int32_T c2_i948;
  int32_T c2_i949;
  int32_T c2_i950;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_phiInv = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_phiInv), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_phiInv);
  c2_i948 = 0;
  for (c2_i949 = 0; c2_i949 < 40; c2_i949++) {
    for (c2_i950 = 0; c2_i950 < 40; c2_i950++) {
      (*(real_T (*)[1600])c2_outData)[c2_i950 + c2_i948] = c2_y[c2_i950 +
        c2_i948];
    }

    c2_i948 += 40;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_p_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i951;
  int32_T c2_i952;
  int32_T c2_i953;
  real_T c2_b_inData[6];
  int32_T c2_i954;
  int32_T c2_i955;
  int32_T c2_i956;
  real_T c2_u[6];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i951 = 0;
  for (c2_i952 = 0; c2_i952 < 2; c2_i952++) {
    for (c2_i953 = 0; c2_i953 < 3; c2_i953++) {
      c2_b_inData[c2_i953 + c2_i951] = (*(real_T (*)[6])c2_inData)[c2_i953 +
        c2_i951];
    }

    c2_i951 += 3;
  }

  c2_i954 = 0;
  for (c2_i955 = 0; c2_i955 < 2; c2_i955++) {
    for (c2_i956 = 0; c2_i956 < 3; c2_i956++) {
      c2_u[c2_i956 + c2_i954] = c2_b_inData[c2_i956 + c2_i954];
    }

    c2_i954 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 2), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_l_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[6])
{
  real_T c2_dv43[6];
  int32_T c2_i957;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv43, 1, 0, 0U, 1, 0U, 2, 3, 2);
  for (c2_i957 = 0; c2_i957 < 6; c2_i957++) {
    c2_y[c2_i957] = c2_dv43[c2_i957];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_EfT;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[6];
  int32_T c2_i958;
  int32_T c2_i959;
  int32_T c2_i960;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_EfT = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_EfT), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_EfT);
  c2_i958 = 0;
  for (c2_i959 = 0; c2_i959 < 2; c2_i959++) {
    for (c2_i960 = 0; c2_i960 < 3; c2_i960++) {
      (*(real_T (*)[6])c2_outData)[c2_i960 + c2_i958] = c2_y[c2_i960 + c2_i958];
    }

    c2_i958 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_q_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i961;
  int32_T c2_i962;
  int32_T c2_i963;
  real_T c2_b_inData[1280];
  int32_T c2_i964;
  int32_T c2_i965;
  int32_T c2_i966;
  real_T c2_u[1280];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i961 = 0;
  for (c2_i962 = 0; c2_i962 < 32; c2_i962++) {
    for (c2_i963 = 0; c2_i963 < 40; c2_i963++) {
      c2_b_inData[c2_i963 + c2_i961] = (*(real_T (*)[1280])c2_inData)[c2_i963 +
        c2_i961];
    }

    c2_i961 += 40;
  }

  c2_i964 = 0;
  for (c2_i965 = 0; c2_i965 < 32; c2_i965++) {
    for (c2_i966 = 0; c2_i966 < 40; c2_i966++) {
      c2_u[c2_i966 + c2_i964] = c2_b_inData[c2_i966 + c2_i964];
    }

    c2_i964 += 40;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 40, 32), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_m_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[1280])
{
  real_T c2_dv44[1280];
  int32_T c2_i967;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv44, 1, 0, 0U, 1, 0U, 2, 40,
                32);
  for (c2_i967 = 0; c2_i967 < 1280; c2_i967++) {
    c2_y[c2_i967] = c2_dv44[c2_i967];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_CT;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[1280];
  int32_T c2_i968;
  int32_T c2_i969;
  int32_T c2_i970;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_CT = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_CT), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_CT);
  c2_i968 = 0;
  for (c2_i969 = 0; c2_i969 < 32; c2_i969++) {
    for (c2_i970 = 0; c2_i970 < 40; c2_i970++) {
      (*(real_T (*)[1280])c2_outData)[c2_i970 + c2_i968] = c2_y[c2_i970 +
        c2_i968];
    }

    c2_i968 += 40;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_r_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i971;
  real_T c2_b_inData[3];
  int32_T c2_i972;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i971 = 0; c2_i971 < 3; c2_i971++) {
    c2_b_inData[c2_i971] = (*(real_T (*)[3])c2_inData)[c2_i971];
  }

  for (c2_i972 = 0; c2_i972 < 3; c2_i972++) {
    c2_u[c2_i972] = c2_b_inData[c2_i972];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_n_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3])
{
  real_T c2_dv45[3];
  int32_T c2_i973;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv45, 1, 0, 0U, 1, 0U, 2, 1, 3);
  for (c2_i973 = 0; c2_i973 < 3; c2_i973++) {
    c2_y[c2_i973] = c2_dv45[c2_i973];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_BT;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[3];
  int32_T c2_i974;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_BT = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_BT), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_BT);
  for (c2_i974 = 0; c2_i974 < 3; c2_i974++) {
    (*(real_T (*)[3])c2_outData)[c2_i974] = c2_y[c2_i974];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_s_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i975;
  real_T c2_b_inData[4];
  int32_T c2_i976;
  real_T c2_u[4];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i975 = 0; c2_i975 < 4; c2_i975++) {
    c2_b_inData[c2_i975] = (*(real_T (*)[4])c2_inData)[c2_i975];
  }

  for (c2_i976 = 0; c2_i976 < 4; c2_i976++) {
    c2_u[c2_i976] = c2_b_inData[c2_i976];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_o_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[4])
{
  real_T c2_dv46[4];
  int32_T c2_i977;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv46, 1, 0, 0U, 1, 0U, 2, 1, 4);
  for (c2_i977 = 0; c2_i977 < 4; c2_i977++) {
    c2_y[c2_i977] = c2_dv46[c2_i977];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_FusT;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[4];
  int32_T c2_i978;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_FusT = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_FusT), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_FusT);
  for (c2_i978 = 0; c2_i978 < 4; c2_i978++) {
    (*(real_T (*)[4])c2_outData)[c2_i978] = c2_y[c2_i978];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_t_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i979;
  int32_T c2_i980;
  int32_T c2_i981;
  real_T c2_b_inData[12];
  int32_T c2_i982;
  int32_T c2_i983;
  int32_T c2_i984;
  real_T c2_u[12];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i979 = 0;
  for (c2_i980 = 0; c2_i980 < 4; c2_i980++) {
    for (c2_i981 = 0; c2_i981 < 3; c2_i981++) {
      c2_b_inData[c2_i981 + c2_i979] = (*(real_T (*)[12])c2_inData)[c2_i981 +
        c2_i979];
    }

    c2_i979 += 3;
  }

  c2_i982 = 0;
  for (c2_i983 = 0; c2_i983 < 4; c2_i983++) {
    for (c2_i984 = 0; c2_i984 < 3; c2_i984++) {
      c2_u[c2_i984 + c2_i982] = c2_b_inData[c2_i984 + c2_i982];
    }

    c2_i982 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_p_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[12])
{
  real_T c2_dv47[12];
  int32_T c2_i985;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv47, 1, 0, 0U, 1, 0U, 2, 3, 4);
  for (c2_i985 = 0; c2_i985 < 12; c2_i985++) {
    c2_y[c2_i985] = c2_dv47[c2_i985];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_FxsT;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[12];
  int32_T c2_i986;
  int32_T c2_i987;
  int32_T c2_i988;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_FxsT = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_FxsT), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_FxsT);
  c2_i986 = 0;
  for (c2_i987 = 0; c2_i987 < 4; c2_i987++) {
    for (c2_i988 = 0; c2_i988 < 3; c2_i988++) {
      (*(real_T (*)[12])c2_outData)[c2_i988 + c2_i986] = c2_y[c2_i988 + c2_i986];
    }

    c2_i986 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_u_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i989;
  int32_T c2_i990;
  int32_T c2_i991;
  real_T c2_b_inData[1760];
  int32_T c2_i992;
  int32_T c2_i993;
  int32_T c2_i994;
  real_T c2_u[1760];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i989 = 0;
  for (c2_i990 = 0; c2_i990 < 44; c2_i990++) {
    for (c2_i991 = 0; c2_i991 < 40; c2_i991++) {
      c2_b_inData[c2_i991 + c2_i989] = (*(real_T (*)[1760])c2_inData)[c2_i991 +
        c2_i989];
    }

    c2_i989 += 40;
  }

  c2_i992 = 0;
  for (c2_i993 = 0; c2_i993 < 44; c2_i993++) {
    for (c2_i994 = 0; c2_i994 < 40; c2_i994++) {
      c2_u[c2_i994 + c2_i992] = c2_b_inData[c2_i994 + c2_i992];
    }

    c2_i992 += 40;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 40, 44), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_q_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[1760])
{
  real_T c2_dv48[1760];
  int32_T c2_i995;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv48, 1, 0, 0U, 1, 0U, 2, 40,
                44);
  for (c2_i995 = 0; c2_i995 < 1760; c2_i995++) {
    c2_y[c2_i995] = c2_dv48[c2_i995];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_o_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_kappaPtSq;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[1760];
  int32_T c2_i996;
  int32_T c2_i997;
  int32_T c2_i998;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_kappaPtSq = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_kappaPtSq), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_kappaPtSq);
  c2_i996 = 0;
  for (c2_i997 = 0; c2_i997 < 44; c2_i997++) {
    for (c2_i998 = 0; c2_i998 < 40; c2_i998++) {
      (*(real_T (*)[1760])c2_outData)[c2_i998 + c2_i996] = c2_y[c2_i998 +
        c2_i996];
    }

    c2_i996 += 40;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_v_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i999;
  real_T c2_b_inData[9];
  int32_T c2_i1000;
  real_T c2_u[9];
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i999 = 0; c2_i999 < 9; c2_i999++) {
    c2_b_inData[c2_i999] = (*(real_T (*)[9])c2_inData)[c2_i999];
  }

  for (c2_i1000 = 0; c2_i1000 < 9; c2_i1000++) {
    c2_u[c2_i1000] = c2_b_inData[c2_i1000];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 9), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_r_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[9])
{
  real_T c2_dv49[9];
  int32_T c2_i1001;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv49, 1, 0, 0U, 1, 0U, 2, 1, 9);
  for (c2_i1001 = 0; c2_i1001 < 9; c2_i1001++) {
    c2_y[c2_i1001] = c2_dv49[c2_i1001];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_p_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_switches;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[9];
  int32_T c2_i1002;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_switches = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_switches), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_switches);
  for (c2_i1002 = 0; c2_i1002 < 9; c2_i1002++) {
    (*(real_T (*)[9])c2_outData)[c2_i1002] = c2_y[c2_i1002];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_w_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  boolean_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(boolean_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 11, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static boolean_T c2_s_emlrt_marshallIn
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, const mxArray
   *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  boolean_T c2_y;
  boolean_T c2_b0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_b0, 1, 11, 0U, 0, 0U, 0);
  c2_y = c2_b0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_q_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_flagNoPade;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  boolean_T c2_y;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_flagNoPade = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_s_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_flagNoPade),
    &c2_thisId);
  sf_mex_destroy(&c2_flagNoPade);
  *(boolean_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_t_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3])
{
  real_T c2_dv50[3];
  int32_T c2_i1003;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv50, 1, 0, 0U, 1, 0U, 1, 3);
  for (c2_i1003 = 0; c2_i1003 < 3; c2_i1003++) {
    c2_y[c2_i1003] = c2_dv50[c2_i1003];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_r_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_y;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[3];
  int32_T c2_i1004;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_y = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_t_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_y), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_y);
  for (c2_i1004 = 0; c2_i1004 < 3; c2_i1004++) {
    (*(real_T (*)[3])c2_outData)[c2_i1004] = c2_b_y[c2_i1004];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_u_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[12])
{
  real_T c2_dv51[12];
  int32_T c2_i1005;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv51, 1, 0, 0U, 1, 0U, 2, 4, 3);
  for (c2_i1005 = 0; c2_i1005 < 12; c2_i1005++) {
    c2_y[c2_i1005] = c2_dv51[c2_i1005];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_s_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_Ff;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[12];
  int32_T c2_i1006;
  int32_T c2_i1007;
  int32_T c2_i1008;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_Ff = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_u_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Ff), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_Ff);
  c2_i1006 = 0;
  for (c2_i1007 = 0; c2_i1007 < 3; c2_i1007++) {
    for (c2_i1008 = 0; c2_i1008 < 4; c2_i1008++) {
      (*(real_T (*)[12])c2_outData)[c2_i1008 + c2_i1006] = c2_y[c2_i1008 +
        c2_i1006];
    }

    c2_i1006 += 4;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_v_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[1760])
{
  real_T c2_dv52[1760];
  int32_T c2_i1009;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv52, 1, 0, 0U, 1, 0U, 2, 44,
                40);
  for (c2_i1009 = 0; c2_i1009 < 1760; c2_i1009++) {
    c2_y[c2_i1009] = c2_dv52[c2_i1009];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_t_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_P;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[1760];
  int32_T c2_i1010;
  int32_T c2_i1011;
  int32_T c2_i1012;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_P = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_v_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_P), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_P);
  c2_i1010 = 0;
  for (c2_i1011 = 0; c2_i1011 < 40; c2_i1011++) {
    for (c2_i1012 = 0; c2_i1012 < 44; c2_i1012++) {
      (*(real_T (*)[1760])c2_outData)[c2_i1012 + c2_i1010] = c2_y[c2_i1012 +
        c2_i1010];
    }

    c2_i1010 += 44;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_w_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[6])
{
  real_T c2_dv53[6];
  int32_T c2_i1013;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv53, 1, 0, 0U, 1, 0U, 2, 2, 3);
  for (c2_i1013 = 0; c2_i1013 < 6; c2_i1013++) {
    c2_y[c2_i1013] = c2_dv53[c2_i1013];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_u_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_Ef;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[6];
  int32_T c2_i1014;
  int32_T c2_i1015;
  int32_T c2_i1016;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_Ef = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_w_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Ef), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_Ef);
  c2_i1014 = 0;
  for (c2_i1015 = 0; c2_i1015 < 3; c2_i1015++) {
    for (c2_i1016 = 0; c2_i1016 < 2; c2_i1016++) {
      (*(real_T (*)[6])c2_outData)[c2_i1016 + c2_i1014] = c2_y[c2_i1016 +
        c2_i1014];
    }

    c2_i1014 += 2;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_x_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[1280])
{
  real_T c2_dv54[1280];
  int32_T c2_i1017;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv54, 1, 0, 0U, 1, 0U, 2, 32,
                40);
  for (c2_i1017 = 0; c2_i1017 < 1280; c2_i1017++) {
    c2_y[c2_i1017] = c2_dv54[c2_i1017];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_v_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_C;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[1280];
  int32_T c2_i1018;
  int32_T c2_i1019;
  int32_T c2_i1020;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_C = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_x_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_C), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_C);
  c2_i1018 = 0;
  for (c2_i1019 = 0; c2_i1019 < 40; c2_i1019++) {
    for (c2_i1020 = 0; c2_i1020 < 32; c2_i1020++) {
      (*(real_T (*)[1280])c2_outData)[c2_i1020 + c2_i1018] = c2_y[c2_i1020 +
        c2_i1018];
    }

    c2_i1018 += 32;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_mpcSetpointIntptCoupled_get_eml_resolved_functions_info
  (void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[276];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i1021;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  c2_b_info_helper(c2_info);
  c2_c_info_helper(c2_info);
  c2_d_info_helper(c2_info);
  c2_e_info_helper(c2_info);
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 276), FALSE);
  for (c2_i1021 = 0; c2_i1021 < 276; c2_i1021++) {
    c2_r0 = &c2_info[c2_i1021];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context", "nameCaptureInfo",
                    c2_i1021);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name", "nameCaptureInfo", c2_i1021);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c2_i1021);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved", "nameCaptureInfo",
                    c2_i1021);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i1021);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i1021);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c2_i1021);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c2_i1021);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[276])
{
  c2_info[0].context = "";
  c2_info[0].name = "length";
  c2_info[0].dominantType = "double";
  c2_info[0].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/length.m";
  c2_info[0].fileTimeLo = 1303149806U;
  c2_info[0].fileTimeHi = 0U;
  c2_info[0].mFileTimeLo = 0U;
  c2_info[0].mFileTimeHi = 0U;
  c2_info[1].context = "";
  c2_info[1].name = "mrdivide";
  c2_info[1].dominantType = "double";
  c2_info[1].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[1].fileTimeLo = 1325127738U;
  c2_info[1].fileTimeHi = 0U;
  c2_info[1].mFileTimeLo = 1319733566U;
  c2_info[1].mFileTimeHi = 0U;
  c2_info[2].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[2].name = "rdivide";
  c2_info[2].dominantType = "double";
  c2_info[2].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[2].fileTimeLo = 1286822444U;
  c2_info[2].fileTimeHi = 0U;
  c2_info[2].mFileTimeLo = 0U;
  c2_info[2].mFileTimeHi = 0U;
  c2_info[3].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[3].name = "eml_div";
  c2_info[3].dominantType = "double";
  c2_info[3].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[3].fileTimeLo = 1313351410U;
  c2_info[3].fileTimeHi = 0U;
  c2_info[3].mFileTimeLo = 0U;
  c2_info[3].mFileTimeHi = 0U;
  c2_info[4].context = "";
  c2_info[4].name = "mtimes";
  c2_info[4].dominantType = "double";
  c2_info[4].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[4].fileTimeLo = 1289523292U;
  c2_info[4].fileTimeHi = 0U;
  c2_info[4].mFileTimeLo = 0U;
  c2_info[4].mFileTimeHi = 0U;
  c2_info[5].context = "";
  c2_info[5].name = "diag";
  c2_info[5].dominantType = "double";
  c2_info[5].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/diag.m";
  c2_info[5].fileTimeLo = 1286822286U;
  c2_info[5].fileTimeHi = 0U;
  c2_info[5].mFileTimeLo = 0U;
  c2_info[5].mFileTimeHi = 0U;
  c2_info[6].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/diag.m";
  c2_info[6].name = "eml_index_class";
  c2_info[6].dominantType = "";
  c2_info[6].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[6].fileTimeLo = 1286822378U;
  c2_info[6].fileTimeHi = 0U;
  c2_info[6].mFileTimeLo = 0U;
  c2_info[6].mFileTimeHi = 0U;
  c2_info[7].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/diag.m";
  c2_info[7].name = "eml_index_plus";
  c2_info[7].dominantType = "int32";
  c2_info[7].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[7].fileTimeLo = 1286822378U;
  c2_info[7].fileTimeHi = 0U;
  c2_info[7].mFileTimeLo = 0U;
  c2_info[7].mFileTimeHi = 0U;
  c2_info[8].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[8].name = "eml_index_class";
  c2_info[8].dominantType = "";
  c2_info[8].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[8].fileTimeLo = 1286822378U;
  c2_info[8].fileTimeHi = 0U;
  c2_info[8].mFileTimeLo = 0U;
  c2_info[8].mFileTimeHi = 0U;
  c2_info[9].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/diag.m";
  c2_info[9].name = "eml_index_times";
  c2_info[9].dominantType = "int32";
  c2_info[9].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[9].fileTimeLo = 1286822380U;
  c2_info[9].fileTimeHi = 0U;
  c2_info[9].mFileTimeLo = 0U;
  c2_info[9].mFileTimeHi = 0U;
  c2_info[10].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[10].name = "eml_index_class";
  c2_info[10].dominantType = "";
  c2_info[10].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[10].fileTimeLo = 1286822378U;
  c2_info[10].fileTimeHi = 0U;
  c2_info[10].mFileTimeLo = 0U;
  c2_info[10].mFileTimeHi = 0U;
  c2_info[11].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/diag.m";
  c2_info[11].name = "eml_index_minus";
  c2_info[11].dominantType = "int32";
  c2_info[11].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[11].fileTimeLo = 1286822378U;
  c2_info[11].fileTimeHi = 0U;
  c2_info[11].mFileTimeLo = 0U;
  c2_info[11].mFileTimeHi = 0U;
  c2_info[12].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[12].name = "eml_index_class";
  c2_info[12].dominantType = "";
  c2_info[12].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[12].fileTimeLo = 1286822378U;
  c2_info[12].fileTimeHi = 0U;
  c2_info[12].mFileTimeLo = 0U;
  c2_info[12].mFileTimeHi = 0U;
  c2_info[13].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/diag.m";
  c2_info[13].name = "min";
  c2_info[13].dominantType = "int32";
  c2_info[13].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[13].fileTimeLo = 1311258918U;
  c2_info[13].fileTimeHi = 0U;
  c2_info[13].mFileTimeLo = 0U;
  c2_info[13].mFileTimeHi = 0U;
  c2_info[14].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[14].name = "eml_min_or_max";
  c2_info[14].dominantType = "int32";
  c2_info[14].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c2_info[14].fileTimeLo = 1303149812U;
  c2_info[14].fileTimeHi = 0U;
  c2_info[14].mFileTimeLo = 0U;
  c2_info[14].mFileTimeHi = 0U;
  c2_info[15].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c2_info[15].name = "eml_scalar_eg";
  c2_info[15].dominantType = "int32";
  c2_info[15].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[15].fileTimeLo = 1286822396U;
  c2_info[15].fileTimeHi = 0U;
  c2_info[15].mFileTimeLo = 0U;
  c2_info[15].mFileTimeHi = 0U;
  c2_info[16].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c2_info[16].name = "eml_scalexp_alloc";
  c2_info[16].dominantType = "int32";
  c2_info[16].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c2_info[16].fileTimeLo = 1286822396U;
  c2_info[16].fileTimeHi = 0U;
  c2_info[16].mFileTimeLo = 0U;
  c2_info[16].mFileTimeHi = 0U;
  c2_info[17].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c2_info[17].name = "eml_index_class";
  c2_info[17].dominantType = "";
  c2_info[17].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[17].fileTimeLo = 1286822378U;
  c2_info[17].fileTimeHi = 0U;
  c2_info[17].mFileTimeLo = 0U;
  c2_info[17].mFileTimeHi = 0U;
  c2_info[18].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c2_info[18].name = "eml_scalar_eg";
  c2_info[18].dominantType = "int32";
  c2_info[18].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[18].fileTimeLo = 1286822396U;
  c2_info[18].fileTimeHi = 0U;
  c2_info[18].mFileTimeLo = 0U;
  c2_info[18].mFileTimeHi = 0U;
  c2_info[19].context = "";
  c2_info[19].name = "colon";
  c2_info[19].dominantType = "double";
  c2_info[19].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m";
  c2_info[19].fileTimeLo = 1311258918U;
  c2_info[19].fileTimeHi = 0U;
  c2_info[19].mFileTimeLo = 0U;
  c2_info[19].mFileTimeHi = 0U;
  c2_info[20].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m";
  c2_info[20].name = "colon";
  c2_info[20].dominantType = "double";
  c2_info[20].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m";
  c2_info[20].fileTimeLo = 1311258918U;
  c2_info[20].fileTimeHi = 0U;
  c2_info[20].mFileTimeLo = 0U;
  c2_info[20].mFileTimeHi = 0U;
  c2_info[21].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!is_flint_colon";
  c2_info[21].name = "isfinite";
  c2_info[21].dominantType = "double";
  c2_info[21].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c2_info[21].fileTimeLo = 1286822358U;
  c2_info[21].fileTimeHi = 0U;
  c2_info[21].mFileTimeLo = 0U;
  c2_info[21].mFileTimeHi = 0U;
  c2_info[22].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c2_info[22].name = "isinf";
  c2_info[22].dominantType = "double";
  c2_info[22].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isinf.m";
  c2_info[22].fileTimeLo = 1286822360U;
  c2_info[22].fileTimeHi = 0U;
  c2_info[22].mFileTimeLo = 0U;
  c2_info[22].mFileTimeHi = 0U;
  c2_info[23].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c2_info[23].name = "isnan";
  c2_info[23].dominantType = "double";
  c2_info[23].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isnan.m";
  c2_info[23].fileTimeLo = 1286822360U;
  c2_info[23].fileTimeHi = 0U;
  c2_info[23].mFileTimeLo = 0U;
  c2_info[23].mFileTimeHi = 0U;
  c2_info[24].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!is_flint_colon";
  c2_info[24].name = "floor";
  c2_info[24].dominantType = "double";
  c2_info[24].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[24].fileTimeLo = 1286822342U;
  c2_info[24].fileTimeHi = 0U;
  c2_info[24].mFileTimeLo = 0U;
  c2_info[24].mFileTimeHi = 0U;
  c2_info[25].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[25].name = "eml_scalar_floor";
  c2_info[25].dominantType = "double";
  c2_info[25].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c2_info[25].fileTimeLo = 1286822326U;
  c2_info[25].fileTimeHi = 0U;
  c2_info[25].mFileTimeLo = 0U;
  c2_info[25].mFileTimeHi = 0U;
  c2_info[26].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!maxabs";
  c2_info[26].name = "abs";
  c2_info[26].dominantType = "double";
  c2_info[26].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[26].fileTimeLo = 1286822294U;
  c2_info[26].fileTimeHi = 0U;
  c2_info[26].mFileTimeLo = 0U;
  c2_info[26].mFileTimeHi = 0U;
  c2_info[27].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[27].name = "eml_scalar_abs";
  c2_info[27].dominantType = "double";
  c2_info[27].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c2_info[27].fileTimeLo = 1286822312U;
  c2_info[27].fileTimeHi = 0U;
  c2_info[27].mFileTimeLo = 0U;
  c2_info[27].mFileTimeHi = 0U;
  c2_info[28].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!is_flint_colon";
  c2_info[28].name = "eps";
  c2_info[28].dominantType = "double";
  c2_info[28].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[28].fileTimeLo = 1307654840U;
  c2_info[28].fileTimeHi = 0U;
  c2_info[28].mFileTimeLo = 0U;
  c2_info[28].mFileTimeHi = 0U;
  c2_info[29].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[29].name = "eml_mantissa_nbits";
  c2_info[29].dominantType = "char";
  c2_info[29].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_mantissa_nbits.m";
  c2_info[29].fileTimeLo = 1307654842U;
  c2_info[29].fileTimeHi = 0U;
  c2_info[29].mFileTimeLo = 0U;
  c2_info[29].mFileTimeHi = 0U;
  c2_info[30].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_mantissa_nbits.m";
  c2_info[30].name = "eml_float_model";
  c2_info[30].dominantType = "char";
  c2_info[30].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c2_info[30].fileTimeLo = 1307654842U;
  c2_info[30].fileTimeHi = 0U;
  c2_info[30].mFileTimeLo = 0U;
  c2_info[30].mFileTimeHi = 0U;
  c2_info[31].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[31].name = "eml_realmin";
  c2_info[31].dominantType = "char";
  c2_info[31].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c2_info[31].fileTimeLo = 1307654844U;
  c2_info[31].fileTimeHi = 0U;
  c2_info[31].mFileTimeLo = 0U;
  c2_info[31].mFileTimeHi = 0U;
  c2_info[32].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c2_info[32].name = "eml_float_model";
  c2_info[32].dominantType = "char";
  c2_info[32].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c2_info[32].fileTimeLo = 1307654842U;
  c2_info[32].fileTimeHi = 0U;
  c2_info[32].mFileTimeLo = 0U;
  c2_info[32].mFileTimeHi = 0U;
  c2_info[33].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[33].name = "eml_realmin_denormal";
  c2_info[33].dominantType = "char";
  c2_info[33].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_realmin_denormal.m";
  c2_info[33].fileTimeLo = 1307654844U;
  c2_info[33].fileTimeHi = 0U;
  c2_info[33].mFileTimeLo = 0U;
  c2_info[33].mFileTimeHi = 0U;
  c2_info[34].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_realmin_denormal.m";
  c2_info[34].name = "eml_float_model";
  c2_info[34].dominantType = "char";
  c2_info[34].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c2_info[34].fileTimeLo = 1307654842U;
  c2_info[34].fileTimeHi = 0U;
  c2_info[34].mFileTimeLo = 0U;
  c2_info[34].mFileTimeHi = 0U;
  c2_info[35].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[35].name = "abs";
  c2_info[35].dominantType = "double";
  c2_info[35].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[35].fileTimeLo = 1286822294U;
  c2_info[35].fileTimeHi = 0U;
  c2_info[35].mFileTimeLo = 0U;
  c2_info[35].mFileTimeHi = 0U;
  c2_info[36].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[36].name = "isfinite";
  c2_info[36].dominantType = "double";
  c2_info[36].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c2_info[36].fileTimeLo = 1286822358U;
  c2_info[36].fileTimeHi = 0U;
  c2_info[36].mFileTimeLo = 0U;
  c2_info[36].mFileTimeHi = 0U;
  c2_info[37].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c2_info[37].name = "realmax";
  c2_info[37].dominantType = "char";
  c2_info[37].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/realmax.m";
  c2_info[37].fileTimeLo = 1307654842U;
  c2_info[37].fileTimeHi = 0U;
  c2_info[37].mFileTimeLo = 0U;
  c2_info[37].mFileTimeHi = 0U;
  c2_info[38].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/realmax.m";
  c2_info[38].name = "eml_realmax";
  c2_info[38].dominantType = "char";
  c2_info[38].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_realmax.m";
  c2_info[38].fileTimeLo = 1307654844U;
  c2_info[38].fileTimeHi = 0U;
  c2_info[38].mFileTimeLo = 0U;
  c2_info[38].mFileTimeHi = 0U;
  c2_info[39].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_realmax.m";
  c2_info[39].name = "eml_float_model";
  c2_info[39].dominantType = "char";
  c2_info[39].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c2_info[39].fileTimeLo = 1307654842U;
  c2_info[39].fileTimeHi = 0U;
  c2_info[39].mFileTimeLo = 0U;
  c2_info[39].mFileTimeHi = 0U;
  c2_info[40].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_realmax.m";
  c2_info[40].name = "mtimes";
  c2_info[40].dominantType = "double";
  c2_info[40].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[40].fileTimeLo = 1289523292U;
  c2_info[40].fileTimeHi = 0U;
  c2_info[40].mFileTimeLo = 0U;
  c2_info[40].mFileTimeHi = 0U;
  c2_info[41].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon";
  c2_info[41].name = "mrdivide";
  c2_info[41].dominantType = "double";
  c2_info[41].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[41].fileTimeLo = 1325127738U;
  c2_info[41].fileTimeHi = 0U;
  c2_info[41].mFileTimeLo = 1319733566U;
  c2_info[41].mFileTimeHi = 0U;
  c2_info[42].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon";
  c2_info[42].name = "floor";
  c2_info[42].dominantType = "double";
  c2_info[42].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[42].fileTimeLo = 1286822342U;
  c2_info[42].fileTimeHi = 0U;
  c2_info[42].mFileTimeLo = 0U;
  c2_info[42].mFileTimeHi = 0U;
  c2_info[43].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon";
  c2_info[43].name = "eml_index_class";
  c2_info[43].dominantType = "";
  c2_info[43].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[43].fileTimeLo = 1286822378U;
  c2_info[43].fileTimeHi = 0U;
  c2_info[43].mFileTimeLo = 0U;
  c2_info[43].mFileTimeHi = 0U;
  c2_info[44].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon";
  c2_info[44].name = "intmax";
  c2_info[44].dominantType = "char";
  c2_info[44].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[44].fileTimeLo = 1311258916U;
  c2_info[44].fileTimeHi = 0U;
  c2_info[44].mFileTimeLo = 0U;
  c2_info[44].mFileTimeHi = 0U;
  c2_info[45].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[45].name = "eml_index_class";
  c2_info[45].dominantType = "";
  c2_info[45].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[45].fileTimeLo = 1286822378U;
  c2_info[45].fileTimeHi = 0U;
  c2_info[45].mFileTimeLo = 0U;
  c2_info[45].mFileTimeHi = 0U;
  c2_info[46].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[46].name = "eml_scalar_eg";
  c2_info[46].dominantType = "double";
  c2_info[46].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[46].fileTimeLo = 1286822396U;
  c2_info[46].fileTimeHi = 0U;
  c2_info[46].mFileTimeLo = 0U;
  c2_info[46].mFileTimeHi = 0U;
  c2_info[47].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[47].name = "eml_xgemm";
  c2_info[47].dominantType = "int32";
  c2_info[47].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c2_info[47].fileTimeLo = 1299080372U;
  c2_info[47].fileTimeHi = 0U;
  c2_info[47].mFileTimeLo = 0U;
  c2_info[47].mFileTimeHi = 0U;
  c2_info[48].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c2_info[48].name = "eml_blas_inline";
  c2_info[48].dominantType = "";
  c2_info[48].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[48].fileTimeLo = 1299080368U;
  c2_info[48].fileTimeHi = 0U;
  c2_info[48].mFileTimeLo = 0U;
  c2_info[48].mFileTimeHi = 0U;
  c2_info[49].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c2_info[49].name = "mtimes";
  c2_info[49].dominantType = "double";
  c2_info[49].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[49].fileTimeLo = 1289523292U;
  c2_info[49].fileTimeHi = 0U;
  c2_info[49].mFileTimeLo = 0U;
  c2_info[49].mFileTimeHi = 0U;
  c2_info[50].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c2_info[50].name = "eml_scalar_eg";
  c2_info[50].dominantType = "double";
  c2_info[50].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[50].fileTimeLo = 1286822396U;
  c2_info[50].fileTimeHi = 0U;
  c2_info[50].mFileTimeLo = 0U;
  c2_info[50].mFileTimeHi = 0U;
  c2_info[51].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c2_info[51].name = "eml_refblas_xgemm";
  c2_info[51].dominantType = "int32";
  c2_info[51].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c2_info[51].fileTimeLo = 1299080374U;
  c2_info[51].fileTimeHi = 0U;
  c2_info[51].mFileTimeLo = 0U;
  c2_info[51].mFileTimeHi = 0U;
  c2_info[52].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c2_info[52].name = "eml_index_class";
  c2_info[52].dominantType = "";
  c2_info[52].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[52].fileTimeLo = 1286822378U;
  c2_info[52].fileTimeHi = 0U;
  c2_info[52].mFileTimeLo = 0U;
  c2_info[52].mFileTimeHi = 0U;
  c2_info[53].context = "";
  c2_info[53].name = "all";
  c2_info[53].dominantType = "logical";
  c2_info[53].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/all.m";
  c2_info[53].fileTimeLo = 1286822434U;
  c2_info[53].fileTimeHi = 0U;
  c2_info[53].mFileTimeLo = 0U;
  c2_info[53].mFileTimeHi = 0U;
  c2_info[54].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/all.m";
  c2_info[54].name = "eml_all_or_any";
  c2_info[54].dominantType = "char";
  c2_info[54].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c2_info[54].fileTimeLo = 1286822294U;
  c2_info[54].fileTimeHi = 0U;
  c2_info[54].mFileTimeLo = 0U;
  c2_info[54].mFileTimeHi = 0U;
  c2_info[55].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c2_info[55].name = "isequal";
  c2_info[55].dominantType = "double";
  c2_info[55].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isequal.m";
  c2_info[55].fileTimeLo = 1286822358U;
  c2_info[55].fileTimeHi = 0U;
  c2_info[55].mFileTimeLo = 0U;
  c2_info[55].mFileTimeHi = 0U;
  c2_info[56].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isequal.m";
  c2_info[56].name = "eml_isequal_core";
  c2_info[56].dominantType = "double";
  c2_info[56].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c2_info[56].fileTimeLo = 1286822386U;
  c2_info[56].fileTimeHi = 0U;
  c2_info[56].mFileTimeLo = 0U;
  c2_info[56].mFileTimeHi = 0U;
  c2_info[57].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c2_info[57].name = "eml_const_nonsingleton_dim";
  c2_info[57].dominantType = "logical";
  c2_info[57].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m";
  c2_info[57].fileTimeLo = 1286822296U;
  c2_info[57].fileTimeHi = 0U;
  c2_info[57].mFileTimeLo = 0U;
  c2_info[57].mFileTimeHi = 0U;
  c2_info[58].context = "";
  c2_info[58].name = "rdivide";
  c2_info[58].dominantType = "double";
  c2_info[58].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[58].fileTimeLo = 1286822444U;
  c2_info[58].fileTimeHi = 0U;
  c2_info[58].mFileTimeLo = 0U;
  c2_info[58].mFileTimeHi = 0U;
  c2_info[59].context = "";
  c2_info[59].name = "norm";
  c2_info[59].dominantType = "double";
  c2_info[59].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/norm.m";
  c2_info[59].fileTimeLo = 1286822426U;
  c2_info[59].fileTimeHi = 0U;
  c2_info[59].mFileTimeLo = 0U;
  c2_info[59].mFileTimeHi = 0U;
  c2_info[60].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c2_info[60].name = "eml_index_class";
  c2_info[60].dominantType = "";
  c2_info[60].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[60].fileTimeLo = 1286822378U;
  c2_info[60].fileTimeHi = 0U;
  c2_info[60].mFileTimeLo = 0U;
  c2_info[60].mFileTimeHi = 0U;
  c2_info[61].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c2_info[61].name = "eml_xnrm2";
  c2_info[61].dominantType = "int32";
  c2_info[61].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c2_info[61].fileTimeLo = 1299080376U;
  c2_info[61].fileTimeHi = 0U;
  c2_info[61].mFileTimeLo = 0U;
  c2_info[61].mFileTimeHi = 0U;
  c2_info[62].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c2_info[62].name = "eml_blas_inline";
  c2_info[62].dominantType = "";
  c2_info[62].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[62].fileTimeLo = 1299080368U;
  c2_info[62].fileTimeHi = 0U;
  c2_info[62].mFileTimeLo = 0U;
  c2_info[62].mFileTimeHi = 0U;
  c2_info[63].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c2_info[63].name = "eml_refblas_xnrm2";
  c2_info[63].dominantType = "int32";
  c2_info[63].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[63].fileTimeLo = 1299080384U;
  c2_info[63].fileTimeHi = 0U;
  c2_info[63].mFileTimeLo = 0U;
  c2_info[63].mFileTimeHi = 0U;
}

static void c2_b_info_helper(c2_ResolvedFunctionInfo c2_info[276])
{
  c2_info[64].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[64].name = "realmin";
  c2_info[64].dominantType = "char";
  c2_info[64].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/realmin.m";
  c2_info[64].fileTimeLo = 1307654842U;
  c2_info[64].fileTimeHi = 0U;
  c2_info[64].mFileTimeLo = 0U;
  c2_info[64].mFileTimeHi = 0U;
  c2_info[65].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/realmin.m";
  c2_info[65].name = "eml_realmin";
  c2_info[65].dominantType = "char";
  c2_info[65].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c2_info[65].fileTimeLo = 1307654844U;
  c2_info[65].fileTimeHi = 0U;
  c2_info[65].mFileTimeLo = 0U;
  c2_info[65].mFileTimeHi = 0U;
  c2_info[66].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[66].name = "eml_index_class";
  c2_info[66].dominantType = "";
  c2_info[66].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[66].fileTimeLo = 1286822378U;
  c2_info[66].fileTimeHi = 0U;
  c2_info[66].mFileTimeLo = 0U;
  c2_info[66].mFileTimeHi = 0U;
  c2_info[67].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[67].name = "eml_index_minus";
  c2_info[67].dominantType = "int32";
  c2_info[67].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[67].fileTimeLo = 1286822378U;
  c2_info[67].fileTimeHi = 0U;
  c2_info[67].mFileTimeLo = 0U;
  c2_info[67].mFileTimeHi = 0U;
  c2_info[68].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[68].name = "eml_index_times";
  c2_info[68].dominantType = "int32";
  c2_info[68].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[68].fileTimeLo = 1286822380U;
  c2_info[68].fileTimeHi = 0U;
  c2_info[68].mFileTimeLo = 0U;
  c2_info[68].mFileTimeHi = 0U;
  c2_info[69].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[69].name = "eml_index_plus";
  c2_info[69].dominantType = "int32";
  c2_info[69].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[69].fileTimeLo = 1286822378U;
  c2_info[69].fileTimeHi = 0U;
  c2_info[69].mFileTimeLo = 0U;
  c2_info[69].mFileTimeHi = 0U;
  c2_info[70].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[70].name = "eml_int_forloop_overflow_check";
  c2_info[70].dominantType = "";
  c2_info[70].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[70].fileTimeLo = 1311258916U;
  c2_info[70].fileTimeHi = 0U;
  c2_info[70].mFileTimeLo = 0U;
  c2_info[70].mFileTimeHi = 0U;
  c2_info[71].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c2_info[71].name = "intmax";
  c2_info[71].dominantType = "char";
  c2_info[71].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[71].fileTimeLo = 1311258916U;
  c2_info[71].fileTimeHi = 0U;
  c2_info[71].mFileTimeLo = 0U;
  c2_info[71].mFileTimeHi = 0U;
  c2_info[72].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[72].name = "abs";
  c2_info[72].dominantType = "double";
  c2_info[72].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[72].fileTimeLo = 1286822294U;
  c2_info[72].fileTimeHi = 0U;
  c2_info[72].mFileTimeLo = 0U;
  c2_info[72].mFileTimeHi = 0U;
  c2_info[73].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[73].name = "eml_xdotu";
  c2_info[73].dominantType = "int32";
  c2_info[73].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c2_info[73].fileTimeLo = 1299080372U;
  c2_info[73].fileTimeHi = 0U;
  c2_info[73].mFileTimeLo = 0U;
  c2_info[73].mFileTimeHi = 0U;
  c2_info[74].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c2_info[74].name = "eml_blas_inline";
  c2_info[74].dominantType = "";
  c2_info[74].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[74].fileTimeLo = 1299080368U;
  c2_info[74].fileTimeHi = 0U;
  c2_info[74].mFileTimeLo = 0U;
  c2_info[74].mFileTimeHi = 0U;
  c2_info[75].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c2_info[75].name = "eml_xdot";
  c2_info[75].dominantType = "int32";
  c2_info[75].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c2_info[75].fileTimeLo = 1299080372U;
  c2_info[75].fileTimeHi = 0U;
  c2_info[75].mFileTimeLo = 0U;
  c2_info[75].mFileTimeHi = 0U;
  c2_info[76].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c2_info[76].name = "eml_blas_inline";
  c2_info[76].dominantType = "";
  c2_info[76].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[76].fileTimeLo = 1299080368U;
  c2_info[76].fileTimeHi = 0U;
  c2_info[76].mFileTimeLo = 0U;
  c2_info[76].mFileTimeHi = 0U;
  c2_info[77].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c2_info[77].name = "eml_refblas_xdot";
  c2_info[77].dominantType = "int32";
  c2_info[77].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c2_info[77].fileTimeLo = 1299080372U;
  c2_info[77].fileTimeHi = 0U;
  c2_info[77].mFileTimeLo = 0U;
  c2_info[77].mFileTimeHi = 0U;
  c2_info[78].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c2_info[78].name = "eml_refblas_xdotx";
  c2_info[78].dominantType = "int32";
  c2_info[78].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[78].fileTimeLo = 1299080374U;
  c2_info[78].fileTimeHi = 0U;
  c2_info[78].mFileTimeLo = 0U;
  c2_info[78].mFileTimeHi = 0U;
  c2_info[79].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[79].name = "eml_scalar_eg";
  c2_info[79].dominantType = "double";
  c2_info[79].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[79].fileTimeLo = 1286822396U;
  c2_info[79].fileTimeHi = 0U;
  c2_info[79].mFileTimeLo = 0U;
  c2_info[79].mFileTimeHi = 0U;
  c2_info[80].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[80].name = "eml_index_class";
  c2_info[80].dominantType = "";
  c2_info[80].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[80].fileTimeLo = 1286822378U;
  c2_info[80].fileTimeHi = 0U;
  c2_info[80].mFileTimeLo = 0U;
  c2_info[80].mFileTimeHi = 0U;
  c2_info[81].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[81].name = "eml_index_minus";
  c2_info[81].dominantType = "int32";
  c2_info[81].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[81].fileTimeLo = 1286822378U;
  c2_info[81].fileTimeHi = 0U;
  c2_info[81].mFileTimeLo = 0U;
  c2_info[81].mFileTimeHi = 0U;
  c2_info[82].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[82].name = "eml_index_times";
  c2_info[82].dominantType = "int32";
  c2_info[82].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[82].fileTimeLo = 1286822380U;
  c2_info[82].fileTimeHi = 0U;
  c2_info[82].mFileTimeLo = 0U;
  c2_info[82].mFileTimeHi = 0U;
  c2_info[83].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[83].name = "eml_index_plus";
  c2_info[83].dominantType = "int32";
  c2_info[83].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[83].fileTimeLo = 1286822378U;
  c2_info[83].fileTimeHi = 0U;
  c2_info[83].mFileTimeLo = 0U;
  c2_info[83].mFileTimeHi = 0U;
  c2_info[84].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[84].name = "eml_int_forloop_overflow_check";
  c2_info[84].dominantType = "";
  c2_info[84].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[84].fileTimeLo = 1311258916U;
  c2_info[84].fileTimeHi = 0U;
  c2_info[84].mFileTimeLo = 0U;
  c2_info[84].mFileTimeHi = 0U;
  c2_info[85].context = "";
  c2_info[85].name = "exp";
  c2_info[85].dominantType = "double";
  c2_info[85].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/exp.m";
  c2_info[85].fileTimeLo = 1286822340U;
  c2_info[85].fileTimeHi = 0U;
  c2_info[85].mFileTimeLo = 0U;
  c2_info[85].mFileTimeHi = 0U;
  c2_info[86].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/exp.m";
  c2_info[86].name = "eml_scalar_exp";
  c2_info[86].dominantType = "double";
  c2_info[86].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/eml_scalar_exp.m";
  c2_info[86].fileTimeLo = 1301332064U;
  c2_info[86].fileTimeHi = 0U;
  c2_info[86].mFileTimeLo = 0U;
  c2_info[86].mFileTimeHi = 0U;
  c2_info[87].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/diag.m";
  c2_info[87].name = "eml_scalar_eg";
  c2_info[87].dominantType = "double";
  c2_info[87].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[87].fileTimeLo = 1286822396U;
  c2_info[87].fileTimeHi = 0U;
  c2_info[87].mFileTimeLo = 0U;
  c2_info[87].mFileTimeHi = 0U;
  c2_info[88].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/diag.m";
  c2_info[88].name = "eml_int_forloop_overflow_check";
  c2_info[88].dominantType = "";
  c2_info[88].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[88].fileTimeLo = 1311258916U;
  c2_info[88].fileTimeHi = 0U;
  c2_info[88].mFileTimeLo = 0U;
  c2_info[88].mFileTimeHi = 0U;
  c2_info[89].context = "";
  c2_info[89].name = "chol";
  c2_info[89].dominantType = "double";
  c2_info[89].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/chol.m";
  c2_info[89].fileTimeLo = 1286822422U;
  c2_info[89].fileTimeHi = 0U;
  c2_info[89].mFileTimeLo = 0U;
  c2_info[89].mFileTimeHi = 0U;
  c2_info[90].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/chol.m";
  c2_info[90].name = "eml_tolower";
  c2_info[90].dominantType = "char";
  c2_info[90].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_tolower.m";
  c2_info[90].fileTimeLo = 1286822400U;
  c2_info[90].fileTimeHi = 0U;
  c2_info[90].mFileTimeLo = 0U;
  c2_info[90].mFileTimeHi = 0U;
  c2_info[91].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/chol.m";
  c2_info[91].name = "eml_index_class";
  c2_info[91].dominantType = "";
  c2_info[91].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[91].fileTimeLo = 1286822378U;
  c2_info[91].fileTimeHi = 0U;
  c2_info[91].mFileTimeLo = 0U;
  c2_info[91].mFileTimeHi = 0U;
  c2_info[92].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/chol.m";
  c2_info[92].name = "eml_error";
  c2_info[92].dominantType = "char";
  c2_info[92].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_error.m";
  c2_info[92].fileTimeLo = 1305321600U;
  c2_info[92].fileTimeHi = 0U;
  c2_info[92].mFileTimeLo = 0U;
  c2_info[92].mFileTimeHi = 0U;
  c2_info[93].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/chol.m";
  c2_info[93].name = "eml_xpotrf";
  c2_info[93].dominantType = "int32";
  c2_info[93].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/eml_xpotrf.m";
  c2_info[93].fileTimeLo = 1286822408U;
  c2_info[93].fileTimeHi = 0U;
  c2_info[93].mFileTimeLo = 0U;
  c2_info[93].mFileTimeHi = 0U;
  c2_info[94].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/eml_xpotrf.m";
  c2_info[94].name = "eml_lapack_xpotrf";
  c2_info[94].dominantType = "int32";
  c2_info[94].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xpotrf.m";
  c2_info[94].fileTimeLo = 1286822412U;
  c2_info[94].fileTimeHi = 0U;
  c2_info[94].mFileTimeLo = 0U;
  c2_info[94].mFileTimeHi = 0U;
  c2_info[95].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xpotrf.m";
  c2_info[95].name = "eml_matlab_zpotrf";
  c2_info[95].dominantType = "int32";
  c2_info[95].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zpotrf.m";
  c2_info[95].fileTimeLo = 1286822424U;
  c2_info[95].fileTimeHi = 0U;
  c2_info[95].mFileTimeLo = 0U;
  c2_info[95].mFileTimeHi = 0U;
  c2_info[96].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zpotrf.m";
  c2_info[96].name = "eml_index_class";
  c2_info[96].dominantType = "";
  c2_info[96].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[96].fileTimeLo = 1286822378U;
  c2_info[96].fileTimeHi = 0U;
  c2_info[96].mFileTimeLo = 0U;
  c2_info[96].mFileTimeHi = 0U;
  c2_info[97].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zpotrf.m";
  c2_info[97].name = "eml_scalar_eg";
  c2_info[97].dominantType = "double";
  c2_info[97].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[97].fileTimeLo = 1286822396U;
  c2_info[97].fileTimeHi = 0U;
  c2_info[97].mFileTimeLo = 0U;
  c2_info[97].mFileTimeHi = 0U;
  c2_info[98].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zpotrf.m";
  c2_info[98].name = "eml_index_minus";
  c2_info[98].dominantType = "int32";
  c2_info[98].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[98].fileTimeLo = 1286822378U;
  c2_info[98].fileTimeHi = 0U;
  c2_info[98].mFileTimeLo = 0U;
  c2_info[98].mFileTimeHi = 0U;
  c2_info[99].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zpotrf.m";
  c2_info[99].name = "eml_index_times";
  c2_info[99].dominantType = "int32";
  c2_info[99].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[99].fileTimeLo = 1286822380U;
  c2_info[99].fileTimeHi = 0U;
  c2_info[99].mFileTimeLo = 0U;
  c2_info[99].mFileTimeHi = 0U;
  c2_info[100].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zpotrf.m";
  c2_info[100].name = "eml_index_plus";
  c2_info[100].dominantType = "int32";
  c2_info[100].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[100].fileTimeLo = 1286822378U;
  c2_info[100].fileTimeHi = 0U;
  c2_info[100].mFileTimeLo = 0U;
  c2_info[100].mFileTimeHi = 0U;
  c2_info[101].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zpotrf.m";
  c2_info[101].name = "eml_xdotc";
  c2_info[101].dominantType = "int32";
  c2_info[101].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xdotc.m";
  c2_info[101].fileTimeLo = 1299080372U;
  c2_info[101].fileTimeHi = 0U;
  c2_info[101].mFileTimeLo = 0U;
  c2_info[101].mFileTimeHi = 0U;
  c2_info[102].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xdotc.m";
  c2_info[102].name = "eml_blas_inline";
  c2_info[102].dominantType = "";
  c2_info[102].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[102].fileTimeLo = 1299080368U;
  c2_info[102].fileTimeHi = 0U;
  c2_info[102].mFileTimeLo = 0U;
  c2_info[102].mFileTimeHi = 0U;
  c2_info[103].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xdotc.m";
  c2_info[103].name = "eml_xdot";
  c2_info[103].dominantType = "int32";
  c2_info[103].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c2_info[103].fileTimeLo = 1299080372U;
  c2_info[103].fileTimeHi = 0U;
  c2_info[103].mFileTimeLo = 0U;
  c2_info[103].mFileTimeHi = 0U;
  c2_info[104].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/chol.m";
  c2_info[104].name = "eml_index_minus";
  c2_info[104].dominantType = "int32";
  c2_info[104].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[104].fileTimeLo = 1286822378U;
  c2_info[104].fileTimeHi = 0U;
  c2_info[104].mFileTimeLo = 0U;
  c2_info[104].mFileTimeHi = 0U;
  c2_info[105].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/chol.m";
  c2_info[105].name = "eml_int_forloop_overflow_check";
  c2_info[105].dominantType = "";
  c2_info[105].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[105].fileTimeLo = 1311258916U;
  c2_info[105].fileTimeHi = 0U;
  c2_info[105].mFileTimeLo = 0U;
  c2_info[105].mFileTimeHi = 0U;
  c2_info[106].context = "";
  c2_info[106].name = "eye";
  c2_info[106].dominantType = "double";
  c2_info[106].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eye.m";
  c2_info[106].fileTimeLo = 1286822288U;
  c2_info[106].fileTimeHi = 0U;
  c2_info[106].mFileTimeLo = 0U;
  c2_info[106].mFileTimeHi = 0U;
  c2_info[107].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[107].name = "eml_assert_valid_size_arg";
  c2_info[107].dominantType = "double";
  c2_info[107].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[107].fileTimeLo = 1286822294U;
  c2_info[107].fileTimeHi = 0U;
  c2_info[107].mFileTimeLo = 0U;
  c2_info[107].mFileTimeHi = 0U;
  c2_info[108].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c2_info[108].name = "isinf";
  c2_info[108].dominantType = "double";
  c2_info[108].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isinf.m";
  c2_info[108].fileTimeLo = 1286822360U;
  c2_info[108].fileTimeHi = 0U;
  c2_info[108].mFileTimeLo = 0U;
  c2_info[108].mFileTimeHi = 0U;
  c2_info[109].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c2_info[109].name = "mtimes";
  c2_info[109].dominantType = "double";
  c2_info[109].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[109].fileTimeLo = 1289523292U;
  c2_info[109].fileTimeHi = 0U;
  c2_info[109].mFileTimeLo = 0U;
  c2_info[109].mFileTimeHi = 0U;
  c2_info[110].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[110].name = "eml_index_class";
  c2_info[110].dominantType = "";
  c2_info[110].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[110].fileTimeLo = 1286822378U;
  c2_info[110].fileTimeHi = 0U;
  c2_info[110].mFileTimeLo = 0U;
  c2_info[110].mFileTimeHi = 0U;
  c2_info[111].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[111].name = "intmax";
  c2_info[111].dominantType = "char";
  c2_info[111].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[111].fileTimeLo = 1311258916U;
  c2_info[111].fileTimeHi = 0U;
  c2_info[111].mFileTimeLo = 0U;
  c2_info[111].mFileTimeHi = 0U;
  c2_info[112].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[112].name = "eml_is_float_class";
  c2_info[112].dominantType = "char";
  c2_info[112].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c2_info[112].fileTimeLo = 1286822382U;
  c2_info[112].fileTimeHi = 0U;
  c2_info[112].mFileTimeLo = 0U;
  c2_info[112].mFileTimeHi = 0U;
  c2_info[113].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[113].name = "min";
  c2_info[113].dominantType = "double";
  c2_info[113].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[113].fileTimeLo = 1311258918U;
  c2_info[113].fileTimeHi = 0U;
  c2_info[113].mFileTimeLo = 0U;
  c2_info[113].mFileTimeHi = 0U;
  c2_info[114].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[114].name = "eml_min_or_max";
  c2_info[114].dominantType = "char";
  c2_info[114].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c2_info[114].fileTimeLo = 1303149812U;
  c2_info[114].fileTimeHi = 0U;
  c2_info[114].mFileTimeLo = 0U;
  c2_info[114].mFileTimeHi = 0U;
  c2_info[115].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c2_info[115].name = "eml_scalar_eg";
  c2_info[115].dominantType = "double";
  c2_info[115].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[115].fileTimeLo = 1286822396U;
  c2_info[115].fileTimeHi = 0U;
  c2_info[115].mFileTimeLo = 0U;
  c2_info[115].mFileTimeHi = 0U;
  c2_info[116].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c2_info[116].name = "eml_scalexp_alloc";
  c2_info[116].dominantType = "double";
  c2_info[116].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c2_info[116].fileTimeLo = 1286822396U;
  c2_info[116].fileTimeHi = 0U;
  c2_info[116].mFileTimeLo = 0U;
  c2_info[116].mFileTimeHi = 0U;
  c2_info[117].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c2_info[117].name = "eml_scalar_eg";
  c2_info[117].dominantType = "double";
  c2_info[117].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[117].fileTimeLo = 1286822396U;
  c2_info[117].fileTimeHi = 0U;
  c2_info[117].mFileTimeLo = 0U;
  c2_info[117].mFileTimeHi = 0U;
  c2_info[118].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[118].name = "eml_index_class";
  c2_info[118].dominantType = "";
  c2_info[118].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[118].fileTimeLo = 1286822378U;
  c2_info[118].fileTimeHi = 0U;
  c2_info[118].mFileTimeLo = 0U;
  c2_info[118].mFileTimeHi = 0U;
  c2_info[119].context = "";
  c2_info[119].name = "linsolve";
  c2_info[119].dominantType = "struct";
  c2_info[119].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/linsolve.m";
  c2_info[119].fileTimeLo = 1305321600U;
  c2_info[119].fileTimeHi = 0U;
  c2_info[119].mFileTimeLo = 0U;
  c2_info[119].mFileTimeHi = 0U;
  c2_info[120].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/linsolve.m";
  c2_info[120].name = "eml_index_class";
  c2_info[120].dominantType = "";
  c2_info[120].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[120].fileTimeLo = 1286822378U;
  c2_info[120].fileTimeHi = 0U;
  c2_info[120].mFileTimeLo = 0U;
  c2_info[120].mFileTimeHi = 0U;
  c2_info[121].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/linsolve.m";
  c2_info[121].name = "min";
  c2_info[121].dominantType = "int32";
  c2_info[121].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[121].fileTimeLo = 1311258918U;
  c2_info[121].fileTimeHi = 0U;
  c2_info[121].mFileTimeLo = 0U;
  c2_info[121].mFileTimeHi = 0U;
  c2_info[122].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/linsolve.m";
  c2_info[122].name = "eml_scalar_eg";
  c2_info[122].dominantType = "double";
  c2_info[122].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[122].fileTimeLo = 1286822396U;
  c2_info[122].fileTimeHi = 0U;
  c2_info[122].mFileTimeLo = 0U;
  c2_info[122].mFileTimeHi = 0U;
  c2_info[123].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/linsolve.m";
  c2_info[123].name = "eml_parse_parameter_inputs";
  c2_info[123].dominantType = "struct";
  c2_info[123].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_parse_parameter_inputs.m";
  c2_info[123].fileTimeLo = 1286822390U;
  c2_info[123].fileTimeHi = 0U;
  c2_info[123].mFileTimeLo = 0U;
  c2_info[123].mFileTimeHi = 0U;
  c2_info[124].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_parse_parameter_inputs.m!parameter_names_match";
  c2_info[124].name = "eml_tolower";
  c2_info[124].dominantType = "char";
  c2_info[124].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_tolower.m";
  c2_info[124].fileTimeLo = 1286822400U;
  c2_info[124].fileTimeHi = 0U;
  c2_info[124].mFileTimeLo = 0U;
  c2_info[124].mFileTimeHi = 0U;
  c2_info[125].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_parse_parameter_inputs.m!parameter_names_match";
  c2_info[125].name = "eml_partial_strcmp";
  c2_info[125].dominantType = "char";
  c2_info[125].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_partial_strcmp.m";
  c2_info[125].fileTimeLo = 1286822390U;
  c2_info[125].fileTimeHi = 0U;
  c2_info[125].mFileTimeLo = 0U;
  c2_info[125].mFileTimeHi = 0U;
  c2_info[126].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/linsolve.m";
  c2_info[126].name = "eml_get_parameter_value";
  c2_info[126].dominantType = "struct";
  c2_info[126].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_get_parameter_value.m";
  c2_info[126].fileTimeLo = 1286822376U;
  c2_info[126].fileTimeHi = 0U;
  c2_info[126].mFileTimeLo = 0U;
  c2_info[126].mFileTimeHi = 0U;
  c2_info[127].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_get_parameter_value.m";
  c2_info[127].name = "intmax";
  c2_info[127].dominantType = "char";
  c2_info[127].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[127].fileTimeLo = 1311258916U;
  c2_info[127].fileTimeHi = 0U;
  c2_info[127].mFileTimeLo = 0U;
  c2_info[127].mFileTimeHi = 0U;
}

static void c2_c_info_helper(c2_ResolvedFunctionInfo c2_info[276])
{
  c2_info[128].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/linsolve.m";
  c2_info[128].name = "eml_index_plus";
  c2_info[128].dominantType = "int32";
  c2_info[128].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[128].fileTimeLo = 1286822378U;
  c2_info[128].fileTimeHi = 0U;
  c2_info[128].mFileTimeLo = 0U;
  c2_info[128].mFileTimeHi = 0U;
  c2_info[129].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/linsolve.m";
  c2_info[129].name = "eml_xtrsv";
  c2_info[129].dominantType = "int32";
  c2_info[129].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xtrsv.m";
  c2_info[129].fileTimeLo = 1299080378U;
  c2_info[129].fileTimeHi = 0U;
  c2_info[129].mFileTimeLo = 0U;
  c2_info[129].mFileTimeHi = 0U;
  c2_info[130].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xtrsv.m";
  c2_info[130].name = "eml_blas_inline";
  c2_info[130].dominantType = "";
  c2_info[130].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[130].fileTimeLo = 1299080368U;
  c2_info[130].fileTimeHi = 0U;
  c2_info[130].mFileTimeLo = 0U;
  c2_info[130].mFileTimeHi = 0U;
  c2_info[131].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsv.m!below_threshold";
  c2_info[131].name = "mtimes";
  c2_info[131].dominantType = "double";
  c2_info[131].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[131].fileTimeLo = 1289523292U;
  c2_info[131].fileTimeHi = 0U;
  c2_info[131].mFileTimeLo = 0U;
  c2_info[131].mFileTimeHi = 0U;
  c2_info[132].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsv.m";
  c2_info[132].name = "eml_refblas_xtrsv";
  c2_info[132].dominantType = "int32";
  c2_info[132].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsv.m";
  c2_info[132].fileTimeLo = 1299080386U;
  c2_info[132].fileTimeHi = 0U;
  c2_info[132].mFileTimeLo = 0U;
  c2_info[132].mFileTimeHi = 0U;
  c2_info[133].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsv.m";
  c2_info[133].name = "eml_index_class";
  c2_info[133].dominantType = "";
  c2_info[133].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[133].fileTimeLo = 1286822378U;
  c2_info[133].fileTimeHi = 0U;
  c2_info[133].mFileTimeLo = 0U;
  c2_info[133].mFileTimeHi = 0U;
  c2_info[134].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsv.m";
  c2_info[134].name = "eml_index_minus";
  c2_info[134].dominantType = "int32";
  c2_info[134].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[134].fileTimeLo = 1286822378U;
  c2_info[134].fileTimeHi = 0U;
  c2_info[134].mFileTimeLo = 0U;
  c2_info[134].mFileTimeHi = 0U;
  c2_info[135].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsv.m";
  c2_info[135].name = "eml_index_plus";
  c2_info[135].dominantType = "int32";
  c2_info[135].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[135].fileTimeLo = 1286822378U;
  c2_info[135].fileTimeHi = 0U;
  c2_info[135].mFileTimeLo = 0U;
  c2_info[135].mFileTimeHi = 0U;
  c2_info[136].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsv.m";
  c2_info[136].name = "eml_index_times";
  c2_info[136].dominantType = "int32";
  c2_info[136].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[136].fileTimeLo = 1286822380U;
  c2_info[136].fileTimeHi = 0U;
  c2_info[136].mFileTimeLo = 0U;
  c2_info[136].mFileTimeHi = 0U;
  c2_info[137].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsv.m";
  c2_info[137].name = "eml_div";
  c2_info[137].dominantType = "double";
  c2_info[137].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[137].fileTimeLo = 1313351410U;
  c2_info[137].fileTimeHi = 0U;
  c2_info[137].mFileTimeLo = 0U;
  c2_info[137].mFileTimeHi = 0U;
  c2_info[138].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/linsolve.m!is_singular_triangular_matrix";
  c2_info[138].name = "eml_index_class";
  c2_info[138].dominantType = "";
  c2_info[138].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[138].fileTimeLo = 1286822378U;
  c2_info[138].fileTimeHi = 0U;
  c2_info[138].mFileTimeLo = 0U;
  c2_info[138].mFileTimeHi = 0U;
  c2_info[139].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/linsolve.m!is_singular_triangular_matrix";
  c2_info[139].name = "min";
  c2_info[139].dominantType = "double";
  c2_info[139].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[139].fileTimeLo = 1311258918U;
  c2_info[139].fileTimeHi = 0U;
  c2_info[139].mFileTimeLo = 0U;
  c2_info[139].mFileTimeHi = 0U;
  c2_info[140].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum";
  c2_info[140].name = "eml_const_nonsingleton_dim";
  c2_info[140].dominantType = "double";
  c2_info[140].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m";
  c2_info[140].fileTimeLo = 1286822296U;
  c2_info[140].fileTimeHi = 0U;
  c2_info[140].mFileTimeLo = 0U;
  c2_info[140].mFileTimeHi = 0U;
  c2_info[141].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum";
  c2_info[141].name = "eml_scalar_eg";
  c2_info[141].dominantType = "double";
  c2_info[141].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[141].fileTimeLo = 1286822396U;
  c2_info[141].fileTimeHi = 0U;
  c2_info[141].mFileTimeLo = 0U;
  c2_info[141].mFileTimeHi = 0U;
  c2_info[142].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum";
  c2_info[142].name = "eml_index_class";
  c2_info[142].dominantType = "";
  c2_info[142].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[142].fileTimeLo = 1286822378U;
  c2_info[142].fileTimeHi = 0U;
  c2_info[142].mFileTimeLo = 0U;
  c2_info[142].mFileTimeHi = 0U;
  c2_info[143].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub";
  c2_info[143].name = "eml_index_class";
  c2_info[143].dominantType = "";
  c2_info[143].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[143].fileTimeLo = 1286822378U;
  c2_info[143].fileTimeHi = 0U;
  c2_info[143].mFileTimeLo = 0U;
  c2_info[143].mFileTimeHi = 0U;
  c2_info[144].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub";
  c2_info[144].name = "isnan";
  c2_info[144].dominantType = "double";
  c2_info[144].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isnan.m";
  c2_info[144].fileTimeLo = 1286822360U;
  c2_info[144].fileTimeHi = 0U;
  c2_info[144].mFileTimeLo = 0U;
  c2_info[144].mFileTimeHi = 0U;
  c2_info[145].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub";
  c2_info[145].name = "eml_index_plus";
  c2_info[145].dominantType = "int32";
  c2_info[145].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[145].fileTimeLo = 1286822378U;
  c2_info[145].fileTimeHi = 0U;
  c2_info[145].mFileTimeLo = 0U;
  c2_info[145].mFileTimeHi = 0U;
  c2_info[146].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub";
  c2_info[146].name = "eml_int_forloop_overflow_check";
  c2_info[146].dominantType = "";
  c2_info[146].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[146].fileTimeLo = 1311258916U;
  c2_info[146].fileTimeHi = 0U;
  c2_info[146].mFileTimeLo = 0U;
  c2_info[146].mFileTimeHi = 0U;
  c2_info[147].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub";
  c2_info[147].name = "eml_relop";
  c2_info[147].dominantType = "function_handle";
  c2_info[147].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_relop.m";
  c2_info[147].fileTimeLo = 1292194110U;
  c2_info[147].fileTimeHi = 0U;
  c2_info[147].mFileTimeLo = 0U;
  c2_info[147].mFileTimeHi = 0U;
  c2_info[148].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/linsolve.m!is_singular_triangular_matrix";
  c2_info[148].name = "isfinite";
  c2_info[148].dominantType = "double";
  c2_info[148].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c2_info[148].fileTimeLo = 1286822358U;
  c2_info[148].fileTimeHi = 0U;
  c2_info[148].mFileTimeLo = 0U;
  c2_info[148].mFileTimeHi = 0U;
  c2_info[149].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/linsolve.m!warn_singular";
  c2_info[149].name = "eml_warning";
  c2_info[149].dominantType = "char";
  c2_info[149].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_warning.m";
  c2_info[149].fileTimeLo = 1286822402U;
  c2_info[149].fileTimeHi = 0U;
  c2_info[149].mFileTimeLo = 0U;
  c2_info[149].mFileTimeHi = 0U;
  c2_info[150].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/length.m!intlength";
  c2_info[150].name = "eml_index_class";
  c2_info[150].dominantType = "";
  c2_info[150].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[150].fileTimeLo = 1286822378U;
  c2_info[150].fileTimeHi = 0U;
  c2_info[150].mFileTimeLo = 0U;
  c2_info[150].mFileTimeHi = 0U;
  c2_info[151].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zpotrf.m";
  c2_info[151].name = "eml_int_forloop_overflow_check";
  c2_info[151].dominantType = "";
  c2_info[151].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[151].fileTimeLo = 1311258916U;
  c2_info[151].fileTimeHi = 0U;
  c2_info[151].mFileTimeLo = 0U;
  c2_info[151].mFileTimeHi = 0U;
  c2_info[152].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m!below_threshold";
  c2_info[152].name = "length";
  c2_info[152].dominantType = "double";
  c2_info[152].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/length.m";
  c2_info[152].fileTimeLo = 1303149806U;
  c2_info[152].fileTimeHi = 0U;
  c2_info[152].mFileTimeLo = 0U;
  c2_info[152].mFileTimeHi = 0U;
  c2_info[153].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zpotrf.m";
  c2_info[153].name = "eml_xgemv";
  c2_info[153].dominantType = "int32";
  c2_info[153].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xgemv.m";
  c2_info[153].fileTimeLo = 1299080374U;
  c2_info[153].fileTimeHi = 0U;
  c2_info[153].mFileTimeLo = 0U;
  c2_info[153].mFileTimeHi = 0U;
  c2_info[154].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xgemv.m";
  c2_info[154].name = "eml_blas_inline";
  c2_info[154].dominantType = "";
  c2_info[154].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[154].fileTimeLo = 1299080368U;
  c2_info[154].fileTimeHi = 0U;
  c2_info[154].mFileTimeLo = 0U;
  c2_info[154].mFileTimeHi = 0U;
  c2_info[155].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemv.m!below_threshold";
  c2_info[155].name = "length";
  c2_info[155].dominantType = "double";
  c2_info[155].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/length.m";
  c2_info[155].fileTimeLo = 1303149806U;
  c2_info[155].fileTimeHi = 0U;
  c2_info[155].mFileTimeLo = 0U;
  c2_info[155].mFileTimeHi = 0U;
  c2_info[156].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemv.m!below_threshold";
  c2_info[156].name = "intmax";
  c2_info[156].dominantType = "char";
  c2_info[156].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[156].fileTimeLo = 1311258916U;
  c2_info[156].fileTimeHi = 0U;
  c2_info[156].mFileTimeLo = 0U;
  c2_info[156].mFileTimeHi = 0U;
  c2_info[157].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemv.m!below_threshold";
  c2_info[157].name = "mtimes";
  c2_info[157].dominantType = "double";
  c2_info[157].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[157].fileTimeLo = 1289523292U;
  c2_info[157].fileTimeHi = 0U;
  c2_info[157].mFileTimeLo = 0U;
  c2_info[157].mFileTimeHi = 0U;
  c2_info[158].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemv.m";
  c2_info[158].name = "eml_scalar_eg";
  c2_info[158].dominantType = "double";
  c2_info[158].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[158].fileTimeLo = 1286822396U;
  c2_info[158].fileTimeHi = 0U;
  c2_info[158].mFileTimeLo = 0U;
  c2_info[158].mFileTimeHi = 0U;
  c2_info[159].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemv.m";
  c2_info[159].name = "eml_refblas_xgemv";
  c2_info[159].dominantType = "int32";
  c2_info[159].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemv.m";
  c2_info[159].fileTimeLo = 1299080376U;
  c2_info[159].fileTimeHi = 0U;
  c2_info[159].mFileTimeLo = 0U;
  c2_info[159].mFileTimeHi = 0U;
  c2_info[160].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemv.m";
  c2_info[160].name = "eml_index_minus";
  c2_info[160].dominantType = "int32";
  c2_info[160].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[160].fileTimeLo = 1286822378U;
  c2_info[160].fileTimeHi = 0U;
  c2_info[160].mFileTimeLo = 0U;
  c2_info[160].mFileTimeHi = 0U;
  c2_info[161].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemv.m";
  c2_info[161].name = "eml_index_class";
  c2_info[161].dominantType = "";
  c2_info[161].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[161].fileTimeLo = 1286822378U;
  c2_info[161].fileTimeHi = 0U;
  c2_info[161].mFileTimeLo = 0U;
  c2_info[161].mFileTimeHi = 0U;
  c2_info[162].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemv.m";
  c2_info[162].name = "eml_index_times";
  c2_info[162].dominantType = "int32";
  c2_info[162].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[162].fileTimeLo = 1286822380U;
  c2_info[162].fileTimeHi = 0U;
  c2_info[162].mFileTimeLo = 0U;
  c2_info[162].mFileTimeHi = 0U;
  c2_info[163].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemv.m";
  c2_info[163].name = "eml_index_plus";
  c2_info[163].dominantType = "int32";
  c2_info[163].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[163].fileTimeLo = 1286822378U;
  c2_info[163].fileTimeHi = 0U;
  c2_info[163].mFileTimeLo = 0U;
  c2_info[163].mFileTimeHi = 0U;
  c2_info[164].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemv.m";
  c2_info[164].name = "eml_int_forloop_overflow_check";
  c2_info[164].dominantType = "";
  c2_info[164].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[164].fileTimeLo = 1311258916U;
  c2_info[164].fileTimeHi = 0U;
  c2_info[164].mFileTimeLo = 0U;
  c2_info[164].mFileTimeHi = 0U;
  c2_info[165].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemv.m";
  c2_info[165].name = "eml_index_class";
  c2_info[165].dominantType = "";
  c2_info[165].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[165].fileTimeLo = 1286822378U;
  c2_info[165].fileTimeHi = 0U;
  c2_info[165].mFileTimeLo = 0U;
  c2_info[165].mFileTimeHi = 0U;
  c2_info[166].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zpotrf.m";
  c2_info[166].name = "eml_div";
  c2_info[166].dominantType = "double";
  c2_info[166].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[166].fileTimeLo = 1313351410U;
  c2_info[166].fileTimeHi = 0U;
  c2_info[166].mFileTimeLo = 0U;
  c2_info[166].mFileTimeHi = 0U;
  c2_info[167].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zpotrf.m";
  c2_info[167].name = "eml_xscal";
  c2_info[167].dominantType = "int32";
  c2_info[167].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xscal.m";
  c2_info[167].fileTimeLo = 1299080376U;
  c2_info[167].fileTimeHi = 0U;
  c2_info[167].mFileTimeLo = 0U;
  c2_info[167].mFileTimeHi = 0U;
  c2_info[168].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xscal.m";
  c2_info[168].name = "eml_blas_inline";
  c2_info[168].dominantType = "";
  c2_info[168].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[168].fileTimeLo = 1299080368U;
  c2_info[168].fileTimeHi = 0U;
  c2_info[168].mFileTimeLo = 0U;
  c2_info[168].mFileTimeHi = 0U;
  c2_info[169].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xscal.m!below_threshold";
  c2_info[169].name = "length";
  c2_info[169].dominantType = "double";
  c2_info[169].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/length.m";
  c2_info[169].fileTimeLo = 1303149806U;
  c2_info[169].fileTimeHi = 0U;
  c2_info[169].mFileTimeLo = 0U;
  c2_info[169].mFileTimeHi = 0U;
  c2_info[170].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xscal.m";
  c2_info[170].name = "eml_scalar_eg";
  c2_info[170].dominantType = "double";
  c2_info[170].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[170].fileTimeLo = 1286822396U;
  c2_info[170].fileTimeHi = 0U;
  c2_info[170].mFileTimeLo = 0U;
  c2_info[170].mFileTimeHi = 0U;
  c2_info[171].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xscal.m";
  c2_info[171].name = "eml_refblas_xscal";
  c2_info[171].dominantType = "int32";
  c2_info[171].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xscal.m";
  c2_info[171].fileTimeLo = 1299080384U;
  c2_info[171].fileTimeHi = 0U;
  c2_info[171].mFileTimeLo = 0U;
  c2_info[171].mFileTimeHi = 0U;
  c2_info[172].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xscal.m";
  c2_info[172].name = "eml_index_class";
  c2_info[172].dominantType = "";
  c2_info[172].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[172].fileTimeLo = 1286822378U;
  c2_info[172].fileTimeHi = 0U;
  c2_info[172].mFileTimeLo = 0U;
  c2_info[172].mFileTimeHi = 0U;
  c2_info[173].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xscal.m";
  c2_info[173].name = "eml_index_minus";
  c2_info[173].dominantType = "int32";
  c2_info[173].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[173].fileTimeLo = 1286822378U;
  c2_info[173].fileTimeHi = 0U;
  c2_info[173].mFileTimeLo = 0U;
  c2_info[173].mFileTimeHi = 0U;
  c2_info[174].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xscal.m";
  c2_info[174].name = "eml_index_times";
  c2_info[174].dominantType = "int32";
  c2_info[174].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[174].fileTimeLo = 1286822380U;
  c2_info[174].fileTimeHi = 0U;
  c2_info[174].mFileTimeLo = 0U;
  c2_info[174].mFileTimeHi = 0U;
  c2_info[175].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xscal.m";
  c2_info[175].name = "eml_index_plus";
  c2_info[175].dominantType = "int32";
  c2_info[175].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[175].fileTimeLo = 1286822378U;
  c2_info[175].fileTimeHi = 0U;
  c2_info[175].mFileTimeLo = 0U;
  c2_info[175].mFileTimeHi = 0U;
  c2_info[176].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xscal.m";
  c2_info[176].name = "eml_int_forloop_overflow_check";
  c2_info[176].dominantType = "";
  c2_info[176].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[176].fileTimeLo = 1311258916U;
  c2_info[176].fileTimeHi = 0U;
  c2_info[176].mFileTimeLo = 0U;
  c2_info[176].mFileTimeHi = 0U;
  c2_info[177].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[177].name = "eml_int_forloop_overflow_check";
  c2_info[177].dominantType = "";
  c2_info[177].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[177].fileTimeLo = 1311258916U;
  c2_info[177].fileTimeHi = 0U;
  c2_info[177].mFileTimeLo = 0U;
  c2_info[177].mFileTimeHi = 0U;
  c2_info[178].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/linsolve.m";
  c2_info[178].name = "eml_int_forloop_overflow_check";
  c2_info[178].dominantType = "";
  c2_info[178].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[178].fileTimeLo = 1311258916U;
  c2_info[178].fileTimeHi = 0U;
  c2_info[178].mFileTimeLo = 0U;
  c2_info[178].mFileTimeHi = 0U;
  c2_info[179].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/linsolve.m";
  c2_info[179].name = "eml_xtrsm";
  c2_info[179].dominantType = "int32";
  c2_info[179].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m";
  c2_info[179].fileTimeLo = 1299080378U;
  c2_info[179].fileTimeHi = 0U;
  c2_info[179].mFileTimeLo = 0U;
  c2_info[179].mFileTimeHi = 0U;
  c2_info[180].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m";
  c2_info[180].name = "eml_blas_inline";
  c2_info[180].dominantType = "";
  c2_info[180].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[180].fileTimeLo = 1299080368U;
  c2_info[180].fileTimeHi = 0U;
  c2_info[180].mFileTimeLo = 0U;
  c2_info[180].mFileTimeHi = 0U;
  c2_info[181].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsm.m!below_threshold";
  c2_info[181].name = "mtimes";
  c2_info[181].dominantType = "double";
  c2_info[181].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[181].fileTimeLo = 1289523292U;
  c2_info[181].fileTimeHi = 0U;
  c2_info[181].mFileTimeLo = 0U;
  c2_info[181].mFileTimeHi = 0U;
  c2_info[182].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsm.m";
  c2_info[182].name = "eml_scalar_eg";
  c2_info[182].dominantType = "double";
  c2_info[182].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[182].fileTimeLo = 1286822396U;
  c2_info[182].fileTimeHi = 0U;
  c2_info[182].mFileTimeLo = 0U;
  c2_info[182].mFileTimeHi = 0U;
  c2_info[183].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsm.m";
  c2_info[183].name = "eml_refblas_xtrsm";
  c2_info[183].dominantType = "int32";
  c2_info[183].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c2_info[183].fileTimeLo = 1299080386U;
  c2_info[183].fileTimeHi = 0U;
  c2_info[183].mFileTimeLo = 0U;
  c2_info[183].mFileTimeHi = 0U;
  c2_info[184].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c2_info[184].name = "eml_scalar_eg";
  c2_info[184].dominantType = "double";
  c2_info[184].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[184].fileTimeLo = 1286822396U;
  c2_info[184].fileTimeHi = 0U;
  c2_info[184].mFileTimeLo = 0U;
  c2_info[184].mFileTimeHi = 0U;
  c2_info[185].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c2_info[185].name = "eml_index_minus";
  c2_info[185].dominantType = "int32";
  c2_info[185].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[185].fileTimeLo = 1286822378U;
  c2_info[185].fileTimeHi = 0U;
  c2_info[185].mFileTimeLo = 0U;
  c2_info[185].mFileTimeHi = 0U;
  c2_info[186].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c2_info[186].name = "eml_index_class";
  c2_info[186].dominantType = "";
  c2_info[186].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[186].fileTimeLo = 1286822378U;
  c2_info[186].fileTimeHi = 0U;
  c2_info[186].mFileTimeLo = 0U;
  c2_info[186].mFileTimeHi = 0U;
  c2_info[187].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c2_info[187].name = "eml_int_forloop_overflow_check";
  c2_info[187].dominantType = "";
  c2_info[187].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[187].fileTimeLo = 1311258916U;
  c2_info[187].fileTimeHi = 0U;
  c2_info[187].mFileTimeLo = 0U;
  c2_info[187].mFileTimeHi = 0U;
  c2_info[188].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c2_info[188].name = "eml_index_times";
  c2_info[188].dominantType = "int32";
  c2_info[188].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[188].fileTimeLo = 1286822380U;
  c2_info[188].fileTimeHi = 0U;
  c2_info[188].mFileTimeLo = 0U;
  c2_info[188].mFileTimeHi = 0U;
  c2_info[189].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c2_info[189].name = "eml_index_plus";
  c2_info[189].dominantType = "int32";
  c2_info[189].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[189].fileTimeLo = 1286822378U;
  c2_info[189].fileTimeHi = 0U;
  c2_info[189].mFileTimeLo = 0U;
  c2_info[189].mFileTimeHi = 0U;
  c2_info[190].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c2_info[190].name = "eml_div";
  c2_info[190].dominantType = "double";
  c2_info[190].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[190].fileTimeLo = 1313351410U;
  c2_info[190].fileTimeHi = 0U;
  c2_info[190].mFileTimeLo = 0U;
  c2_info[190].mFileTimeHi = 0U;
  c2_info[191].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/linsolve.m!is_singular_triangular_matrix";
  c2_info[191].name = "eml_int_forloop_overflow_check";
  c2_info[191].dominantType = "";
  c2_info[191].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[191].fileTimeLo = 1311258916U;
  c2_info[191].fileTimeHi = 0U;
  c2_info[191].mFileTimeLo = 0U;
  c2_info[191].mFileTimeHi = 0U;
}

static void c2_d_info_helper(c2_ResolvedFunctionInfo c2_info[276])
{
  c2_info[192].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c2_info[192].name = "intmin";
  c2_info[192].dominantType = "char";
  c2_info[192].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/intmin.m";
  c2_info[192].fileTimeLo = 1311258918U;
  c2_info[192].fileTimeHi = 0U;
  c2_info[192].mFileTimeLo = 0U;
  c2_info[192].mFileTimeHi = 0U;
  c2_info[193].context = "";
  c2_info[193].name = "max";
  c2_info[193].dominantType = "double";
  c2_info[193].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/datafun/max.m";
  c2_info[193].fileTimeLo = 1311258916U;
  c2_info[193].fileTimeHi = 0U;
  c2_info[193].mFileTimeLo = 0U;
  c2_info[193].mFileTimeHi = 0U;
  c2_info[194].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/datafun/max.m";
  c2_info[194].name = "eml_min_or_max";
  c2_info[194].dominantType = "char";
  c2_info[194].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c2_info[194].fileTimeLo = 1303149812U;
  c2_info[194].fileTimeHi = 0U;
  c2_info[194].mFileTimeLo = 0U;
  c2_info[194].mFileTimeHi = 0U;
  c2_info[195].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum";
  c2_info[195].name = "eml_matrix_vstride";
  c2_info[195].dominantType = "double";
  c2_info[195].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_matrix_vstride.m";
  c2_info[195].fileTimeLo = 1286822388U;
  c2_info[195].fileTimeHi = 0U;
  c2_info[195].mFileTimeLo = 0U;
  c2_info[195].mFileTimeHi = 0U;
  c2_info[196].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_matrix_vstride.m";
  c2_info[196].name = "eml_index_minus";
  c2_info[196].dominantType = "double";
  c2_info[196].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[196].fileTimeLo = 1286822378U;
  c2_info[196].fileTimeHi = 0U;
  c2_info[196].mFileTimeLo = 0U;
  c2_info[196].mFileTimeHi = 0U;
  c2_info[197].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_matrix_vstride.m";
  c2_info[197].name = "eml_index_class";
  c2_info[197].dominantType = "";
  c2_info[197].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[197].fileTimeLo = 1286822378U;
  c2_info[197].fileTimeHi = 0U;
  c2_info[197].mFileTimeLo = 0U;
  c2_info[197].mFileTimeHi = 0U;
  c2_info[198].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_matrix_vstride.m";
  c2_info[198].name = "eml_size_prod";
  c2_info[198].dominantType = "int32";
  c2_info[198].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_size_prod.m";
  c2_info[198].fileTimeLo = 1286822398U;
  c2_info[198].fileTimeHi = 0U;
  c2_info[198].mFileTimeLo = 0U;
  c2_info[198].mFileTimeHi = 0U;
  c2_info[199].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_size_prod.m";
  c2_info[199].name = "eml_index_class";
  c2_info[199].dominantType = "";
  c2_info[199].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[199].fileTimeLo = 1286822378U;
  c2_info[199].fileTimeHi = 0U;
  c2_info[199].mFileTimeLo = 0U;
  c2_info[199].mFileTimeHi = 0U;
  c2_info[200].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum";
  c2_info[200].name = "eml_index_minus";
  c2_info[200].dominantType = "int32";
  c2_info[200].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[200].fileTimeLo = 1286822378U;
  c2_info[200].fileTimeHi = 0U;
  c2_info[200].mFileTimeLo = 0U;
  c2_info[200].mFileTimeHi = 0U;
  c2_info[201].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum";
  c2_info[201].name = "eml_index_times";
  c2_info[201].dominantType = "int32";
  c2_info[201].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[201].fileTimeLo = 1286822380U;
  c2_info[201].fileTimeHi = 0U;
  c2_info[201].mFileTimeLo = 0U;
  c2_info[201].mFileTimeHi = 0U;
  c2_info[202].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum";
  c2_info[202].name = "eml_matrix_npages";
  c2_info[202].dominantType = "double";
  c2_info[202].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_matrix_npages.m";
  c2_info[202].fileTimeLo = 1286822386U;
  c2_info[202].fileTimeHi = 0U;
  c2_info[202].mFileTimeLo = 0U;
  c2_info[202].mFileTimeHi = 0U;
  c2_info[203].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_matrix_npages.m";
  c2_info[203].name = "eml_index_plus";
  c2_info[203].dominantType = "double";
  c2_info[203].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[203].fileTimeLo = 1286822378U;
  c2_info[203].fileTimeHi = 0U;
  c2_info[203].mFileTimeLo = 0U;
  c2_info[203].mFileTimeHi = 0U;
  c2_info[204].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_matrix_npages.m";
  c2_info[204].name = "eml_index_class";
  c2_info[204].dominantType = "";
  c2_info[204].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[204].fileTimeLo = 1286822378U;
  c2_info[204].fileTimeHi = 0U;
  c2_info[204].mFileTimeLo = 0U;
  c2_info[204].mFileTimeHi = 0U;
  c2_info[205].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_matrix_npages.m";
  c2_info[205].name = "eml_size_prod";
  c2_info[205].dominantType = "int32";
  c2_info[205].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_size_prod.m";
  c2_info[205].fileTimeLo = 1286822398U;
  c2_info[205].fileTimeHi = 0U;
  c2_info[205].mFileTimeLo = 0U;
  c2_info[205].mFileTimeHi = 0U;
  c2_info[206].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_size_prod.m";
  c2_info[206].name = "eml_index_times";
  c2_info[206].dominantType = "int32";
  c2_info[206].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[206].fileTimeLo = 1286822380U;
  c2_info[206].fileTimeHi = 0U;
  c2_info[206].mFileTimeLo = 0U;
  c2_info[206].mFileTimeHi = 0U;
  c2_info[207].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum";
  c2_info[207].name = "eml_int_forloop_overflow_check";
  c2_info[207].dominantType = "";
  c2_info[207].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[207].fileTimeLo = 1311258916U;
  c2_info[207].fileTimeHi = 0U;
  c2_info[207].mFileTimeLo = 0U;
  c2_info[207].mFileTimeHi = 0U;
  c2_info[208].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum";
  c2_info[208].name = "eml_index_plus";
  c2_info[208].dominantType = "int32";
  c2_info[208].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[208].fileTimeLo = 1286822378U;
  c2_info[208].fileTimeHi = 0U;
  c2_info[208].mFileTimeLo = 0U;
  c2_info[208].mFileTimeHi = 0U;
  c2_info[209].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub";
  c2_info[209].name = "eml_index_minus";
  c2_info[209].dominantType = "int32";
  c2_info[209].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[209].fileTimeLo = 1286822378U;
  c2_info[209].fileTimeHi = 0U;
  c2_info[209].mFileTimeLo = 0U;
  c2_info[209].mFileTimeHi = 0U;
  c2_info[210].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub";
  c2_info[210].name = "eml_index_times";
  c2_info[210].dominantType = "int32";
  c2_info[210].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[210].fileTimeLo = 1286822380U;
  c2_info[210].fileTimeHi = 0U;
  c2_info[210].mFileTimeLo = 0U;
  c2_info[210].mFileTimeHi = 0U;
  c2_info[211].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[211].name = "eml_guarded_nan";
  c2_info[211].dominantType = "";
  c2_info[211].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c2_info[211].fileTimeLo = 1286822376U;
  c2_info[211].fileTimeHi = 0U;
  c2_info[211].mFileTimeLo = 0U;
  c2_info[211].mFileTimeHi = 0U;
  c2_info[212].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!float_colon_length";
  c2_info[212].name = "isnan";
  c2_info[212].dominantType = "double";
  c2_info[212].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isnan.m";
  c2_info[212].fileTimeLo = 1286822360U;
  c2_info[212].fileTimeHi = 0U;
  c2_info[212].mFileTimeLo = 0U;
  c2_info[212].mFileTimeHi = 0U;
  c2_info[213].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!float_colon_length";
  c2_info[213].name = "eml_index_class";
  c2_info[213].dominantType = "";
  c2_info[213].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[213].fileTimeLo = 1286822378U;
  c2_info[213].fileTimeHi = 0U;
  c2_info[213].mFileTimeLo = 0U;
  c2_info[213].mFileTimeHi = 0U;
  c2_info[214].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!float_colon_length";
  c2_info[214].name = "eml_guarded_nan";
  c2_info[214].dominantType = "char";
  c2_info[214].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c2_info[214].fileTimeLo = 1286822376U;
  c2_info[214].fileTimeHi = 0U;
  c2_info[214].mFileTimeLo = 0U;
  c2_info[214].mFileTimeHi = 0U;
  c2_info[215].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c2_info[215].name = "eml_is_float_class";
  c2_info[215].dominantType = "char";
  c2_info[215].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c2_info[215].fileTimeLo = 1286822382U;
  c2_info[215].fileTimeHi = 0U;
  c2_info[215].mFileTimeLo = 0U;
  c2_info[215].mFileTimeHi = 0U;
  c2_info[216].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!float_colon_length";
  c2_info[216].name = "isinf";
  c2_info[216].dominantType = "double";
  c2_info[216].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isinf.m";
  c2_info[216].fileTimeLo = 1286822360U;
  c2_info[216].fileTimeHi = 0U;
  c2_info[216].mFileTimeLo = 0U;
  c2_info[216].mFileTimeHi = 0U;
  c2_info[217].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!float_colon_length";
  c2_info[217].name = "floor";
  c2_info[217].dominantType = "double";
  c2_info[217].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[217].fileTimeLo = 1286822342U;
  c2_info[217].fileTimeHi = 0U;
  c2_info[217].mFileTimeLo = 0U;
  c2_info[217].mFileTimeHi = 0U;
  c2_info[218].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!float_colon_length";
  c2_info[218].name = "mtimes";
  c2_info[218].dominantType = "double";
  c2_info[218].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[218].fileTimeLo = 1289523292U;
  c2_info[218].fileTimeHi = 0U;
  c2_info[218].mFileTimeLo = 0U;
  c2_info[218].mFileTimeHi = 0U;
  c2_info[219].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!float_colon_length";
  c2_info[219].name = "abs";
  c2_info[219].dominantType = "double";
  c2_info[219].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[219].fileTimeLo = 1286822294U;
  c2_info[219].fileTimeHi = 0U;
  c2_info[219].mFileTimeLo = 0U;
  c2_info[219].mFileTimeHi = 0U;
  c2_info[220].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!float_colon_length";
  c2_info[220].name = "eps";
  c2_info[220].dominantType = "char";
  c2_info[220].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[220].fileTimeLo = 1307654840U;
  c2_info[220].fileTimeHi = 0U;
  c2_info[220].mFileTimeLo = 0U;
  c2_info[220].mFileTimeHi = 0U;
  c2_info[221].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[221].name = "eml_is_float_class";
  c2_info[221].dominantType = "char";
  c2_info[221].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c2_info[221].fileTimeLo = 1286822382U;
  c2_info[221].fileTimeHi = 0U;
  c2_info[221].mFileTimeLo = 0U;
  c2_info[221].mFileTimeHi = 0U;
  c2_info[222].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[222].name = "eml_eps";
  c2_info[222].dominantType = "char";
  c2_info[222].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c2_info[222].fileTimeLo = 1307654840U;
  c2_info[222].fileTimeHi = 0U;
  c2_info[222].mFileTimeLo = 0U;
  c2_info[222].mFileTimeHi = 0U;
  c2_info[223].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c2_info[223].name = "eml_float_model";
  c2_info[223].dominantType = "char";
  c2_info[223].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c2_info[223].fileTimeLo = 1307654842U;
  c2_info[223].fileTimeHi = 0U;
  c2_info[223].mFileTimeLo = 0U;
  c2_info[223].mFileTimeHi = 0U;
  c2_info[224].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/colon.m!float_colon_length";
  c2_info[224].name = "intmax";
  c2_info[224].dominantType = "char";
  c2_info[224].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[224].fileTimeLo = 1311258916U;
  c2_info[224].fileTimeHi = 0U;
  c2_info[224].mFileTimeLo = 0U;
  c2_info[224].mFileTimeHi = 0U;
  c2_info[225].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/norm.m";
  c2_info[225].name = "svd";
  c2_info[225].dominantType = "double";
  c2_info[225].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/svd.m";
  c2_info[225].fileTimeLo = 1286822432U;
  c2_info[225].fileTimeHi = 0U;
  c2_info[225].mFileTimeLo = 0U;
  c2_info[225].mFileTimeHi = 0U;
  c2_info[226].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/svd.m";
  c2_info[226].name = "eml_index_class";
  c2_info[226].dominantType = "";
  c2_info[226].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[226].fileTimeLo = 1286822378U;
  c2_info[226].fileTimeHi = 0U;
  c2_info[226].mFileTimeLo = 0U;
  c2_info[226].mFileTimeHi = 0U;
  c2_info[227].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/svd.m";
  c2_info[227].name = "eml_int_forloop_overflow_check";
  c2_info[227].dominantType = "";
  c2_info[227].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[227].fileTimeLo = 1311258916U;
  c2_info[227].fileTimeHi = 0U;
  c2_info[227].mFileTimeLo = 0U;
  c2_info[227].mFileTimeHi = 0U;
  c2_info[228].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/svd.m";
  c2_info[228].name = "isfinite";
  c2_info[228].dominantType = "double";
  c2_info[228].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c2_info[228].fileTimeLo = 1286822358U;
  c2_info[228].fileTimeHi = 0U;
  c2_info[228].mFileTimeLo = 0U;
  c2_info[228].mFileTimeHi = 0U;
  c2_info[229].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/svd.m";
  c2_info[229].name = "eml_error";
  c2_info[229].dominantType = "char";
  c2_info[229].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_error.m";
  c2_info[229].fileTimeLo = 1305321600U;
  c2_info[229].fileTimeHi = 0U;
  c2_info[229].mFileTimeLo = 0U;
  c2_info[229].mFileTimeHi = 0U;
  c2_info[230].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/svd.m";
  c2_info[230].name = "eml_xgesvd";
  c2_info[230].dominantType = "double";
  c2_info[230].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/eml_xgesvd.m";
  c2_info[230].fileTimeLo = 1286822406U;
  c2_info[230].fileTimeHi = 0U;
  c2_info[230].mFileTimeLo = 0U;
  c2_info[230].mFileTimeHi = 0U;
  c2_info[231].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/eml_xgesvd.m";
  c2_info[231].name = "eml_lapack_xgesvd";
  c2_info[231].dominantType = "double";
  c2_info[231].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgesvd.m";
  c2_info[231].fileTimeLo = 1286822410U;
  c2_info[231].fileTimeHi = 0U;
  c2_info[231].mFileTimeLo = 0U;
  c2_info[231].mFileTimeHi = 0U;
  c2_info[232].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgesvd.m";
  c2_info[232].name = "eml_matlab_zsvdc";
  c2_info[232].dominantType = "double";
  c2_info[232].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[232].fileTimeLo = 1295288466U;
  c2_info[232].fileTimeHi = 0U;
  c2_info[232].mFileTimeLo = 0U;
  c2_info[232].mFileTimeHi = 0U;
  c2_info[233].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[233].name = "eml_index_class";
  c2_info[233].dominantType = "";
  c2_info[233].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[233].fileTimeLo = 1286822378U;
  c2_info[233].fileTimeHi = 0U;
  c2_info[233].mFileTimeLo = 0U;
  c2_info[233].mFileTimeHi = 0U;
  c2_info[234].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[234].name = "eml_scalar_eg";
  c2_info[234].dominantType = "double";
  c2_info[234].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[234].fileTimeLo = 1286822396U;
  c2_info[234].fileTimeHi = 0U;
  c2_info[234].mFileTimeLo = 0U;
  c2_info[234].mFileTimeHi = 0U;
  c2_info[235].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[235].name = "eml_index_plus";
  c2_info[235].dominantType = "int32";
  c2_info[235].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[235].fileTimeLo = 1286822378U;
  c2_info[235].fileTimeHi = 0U;
  c2_info[235].mFileTimeLo = 0U;
  c2_info[235].mFileTimeHi = 0U;
  c2_info[236].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[236].name = "min";
  c2_info[236].dominantType = "int32";
  c2_info[236].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[236].fileTimeLo = 1311258918U;
  c2_info[236].fileTimeHi = 0U;
  c2_info[236].mFileTimeLo = 0U;
  c2_info[236].mFileTimeHi = 0U;
  c2_info[237].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[237].name = "max";
  c2_info[237].dominantType = "int32";
  c2_info[237].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/datafun/max.m";
  c2_info[237].fileTimeLo = 1311258916U;
  c2_info[237].fileTimeHi = 0U;
  c2_info[237].mFileTimeLo = 0U;
  c2_info[237].mFileTimeHi = 0U;
  c2_info[238].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/datafun/max.m";
  c2_info[238].name = "eml_min_or_max";
  c2_info[238].dominantType = "int32";
  c2_info[238].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c2_info[238].fileTimeLo = 1303149812U;
  c2_info[238].fileTimeHi = 0U;
  c2_info[238].mFileTimeLo = 0U;
  c2_info[238].mFileTimeHi = 0U;
  c2_info[239].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c2_info[239].name = "eml_relop";
  c2_info[239].dominantType = "function_handle";
  c2_info[239].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_relop.m";
  c2_info[239].fileTimeLo = 1292194110U;
  c2_info[239].fileTimeHi = 0U;
  c2_info[239].mFileTimeLo = 0U;
  c2_info[239].mFileTimeHi = 0U;
  c2_info[240].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c2_info[240].name = "isnan";
  c2_info[240].dominantType = "int32";
  c2_info[240].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isnan.m";
  c2_info[240].fileTimeLo = 1286822360U;
  c2_info[240].fileTimeHi = 0U;
  c2_info[240].mFileTimeLo = 0U;
  c2_info[240].mFileTimeHi = 0U;
  c2_info[241].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[241].name = "eml_index_minus";
  c2_info[241].dominantType = "int32";
  c2_info[241].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[241].fileTimeLo = 1286822378U;
  c2_info[241].fileTimeHi = 0U;
  c2_info[241].mFileTimeLo = 0U;
  c2_info[241].mFileTimeHi = 0U;
  c2_info[242].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[242].name = "eml_int_forloop_overflow_check";
  c2_info[242].dominantType = "";
  c2_info[242].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[242].fileTimeLo = 1311258916U;
  c2_info[242].fileTimeHi = 0U;
  c2_info[242].mFileTimeLo = 0U;
  c2_info[242].mFileTimeHi = 0U;
  c2_info[243].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[243].name = "eml_index_times";
  c2_info[243].dominantType = "int32";
  c2_info[243].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[243].fileTimeLo = 1286822380U;
  c2_info[243].fileTimeHi = 0U;
  c2_info[243].mFileTimeLo = 0U;
  c2_info[243].mFileTimeHi = 0U;
  c2_info[244].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[244].name = "eml_xnrm2";
  c2_info[244].dominantType = "int32";
  c2_info[244].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c2_info[244].fileTimeLo = 1299080376U;
  c2_info[244].fileTimeHi = 0U;
  c2_info[244].mFileTimeLo = 0U;
  c2_info[244].mFileTimeHi = 0U;
  c2_info[245].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m!below_threshold";
  c2_info[245].name = "length";
  c2_info[245].dominantType = "double";
  c2_info[245].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/length.m";
  c2_info[245].fileTimeLo = 1303149806U;
  c2_info[245].fileTimeHi = 0U;
  c2_info[245].mFileTimeLo = 0U;
  c2_info[245].mFileTimeHi = 0U;
  c2_info[246].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[246].name = "eml_div";
  c2_info[246].dominantType = "double";
  c2_info[246].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[246].fileTimeLo = 1313351410U;
  c2_info[246].fileTimeHi = 0U;
  c2_info[246].mFileTimeLo = 0U;
  c2_info[246].mFileTimeHi = 0U;
  c2_info[247].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[247].name = "eml_xscal";
  c2_info[247].dominantType = "int32";
  c2_info[247].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xscal.m";
  c2_info[247].fileTimeLo = 1299080376U;
  c2_info[247].fileTimeHi = 0U;
  c2_info[247].mFileTimeLo = 0U;
  c2_info[247].mFileTimeHi = 0U;
  c2_info[248].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[248].name = "eml_xdotc";
  c2_info[248].dominantType = "int32";
  c2_info[248].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xdotc.m";
  c2_info[248].fileTimeLo = 1299080372U;
  c2_info[248].fileTimeHi = 0U;
  c2_info[248].mFileTimeLo = 0U;
  c2_info[248].mFileTimeHi = 0U;
  c2_info[249].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[249].name = "eml_xaxpy";
  c2_info[249].dominantType = "int32";
  c2_info[249].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xaxpy.m";
  c2_info[249].fileTimeLo = 1299080370U;
  c2_info[249].fileTimeHi = 0U;
  c2_info[249].mFileTimeLo = 0U;
  c2_info[249].mFileTimeHi = 0U;
  c2_info[250].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xaxpy.m";
  c2_info[250].name = "eml_blas_inline";
  c2_info[250].dominantType = "";
  c2_info[250].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[250].fileTimeLo = 1299080368U;
  c2_info[250].fileTimeHi = 0U;
  c2_info[250].mFileTimeLo = 0U;
  c2_info[250].mFileTimeHi = 0U;
  c2_info[251].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xaxpy.m!below_threshold";
  c2_info[251].name = "length";
  c2_info[251].dominantType = "double";
  c2_info[251].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/length.m";
  c2_info[251].fileTimeLo = 1303149806U;
  c2_info[251].fileTimeHi = 0U;
  c2_info[251].mFileTimeLo = 0U;
  c2_info[251].mFileTimeHi = 0U;
  c2_info[252].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xaxpy.m";
  c2_info[252].name = "eml_scalar_eg";
  c2_info[252].dominantType = "double";
  c2_info[252].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[252].fileTimeLo = 1286822396U;
  c2_info[252].fileTimeHi = 0U;
  c2_info[252].mFileTimeLo = 0U;
  c2_info[252].mFileTimeHi = 0U;
  c2_info[253].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xaxpy.m";
  c2_info[253].name = "eml_refblas_xaxpy";
  c2_info[253].dominantType = "int32";
  c2_info[253].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xaxpy.m";
  c2_info[253].fileTimeLo = 1299080372U;
  c2_info[253].fileTimeHi = 0U;
  c2_info[253].mFileTimeLo = 0U;
  c2_info[253].mFileTimeHi = 0U;
  c2_info[254].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xaxpy.m";
  c2_info[254].name = "eml_index_class";
  c2_info[254].dominantType = "";
  c2_info[254].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[254].fileTimeLo = 1286822378U;
  c2_info[254].fileTimeHi = 0U;
  c2_info[254].mFileTimeLo = 0U;
  c2_info[254].mFileTimeHi = 0U;
  c2_info[255].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xaxpy.m";
  c2_info[255].name = "eml_isa_uint";
  c2_info[255].dominantType = "int32";
  c2_info[255].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c2_info[255].fileTimeLo = 1286822384U;
  c2_info[255].fileTimeHi = 0U;
  c2_info[255].mFileTimeLo = 0U;
  c2_info[255].mFileTimeHi = 0U;
}

static void c2_e_info_helper(c2_ResolvedFunctionInfo c2_info[276])
{
  c2_info[256].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xaxpy.m";
  c2_info[256].name = "eml_index_minus";
  c2_info[256].dominantType = "int32";
  c2_info[256].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[256].fileTimeLo = 1286822378U;
  c2_info[256].fileTimeHi = 0U;
  c2_info[256].mFileTimeLo = 0U;
  c2_info[256].mFileTimeHi = 0U;
  c2_info[257].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xaxpy.m";
  c2_info[257].name = "eml_int_forloop_overflow_check";
  c2_info[257].dominantType = "";
  c2_info[257].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[257].fileTimeLo = 1311258916U;
  c2_info[257].fileTimeHi = 0U;
  c2_info[257].mFileTimeLo = 0U;
  c2_info[257].mFileTimeHi = 0U;
  c2_info[258].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xaxpy.m";
  c2_info[258].name = "eml_index_plus";
  c2_info[258].dominantType = "int32";
  c2_info[258].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[258].fileTimeLo = 1286822378U;
  c2_info[258].fileTimeHi = 0U;
  c2_info[258].mFileTimeLo = 0U;
  c2_info[258].mFileTimeHi = 0U;
  c2_info[259].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[259].name = "abs";
  c2_info[259].dominantType = "double";
  c2_info[259].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[259].fileTimeLo = 1286822294U;
  c2_info[259].fileTimeHi = 0U;
  c2_info[259].mFileTimeLo = 0U;
  c2_info[259].mFileTimeHi = 0U;
  c2_info[260].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[260].name = "mtimes";
  c2_info[260].dominantType = "double";
  c2_info[260].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[260].fileTimeLo = 1289523292U;
  c2_info[260].fileTimeHi = 0U;
  c2_info[260].mFileTimeLo = 0U;
  c2_info[260].mFileTimeHi = 0U;
  c2_info[261].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[261].name = "realmin";
  c2_info[261].dominantType = "char";
  c2_info[261].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/realmin.m";
  c2_info[261].fileTimeLo = 1307654842U;
  c2_info[261].fileTimeHi = 0U;
  c2_info[261].mFileTimeLo = 0U;
  c2_info[261].mFileTimeHi = 0U;
  c2_info[262].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[262].name = "eps";
  c2_info[262].dominantType = "char";
  c2_info[262].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[262].fileTimeLo = 1307654840U;
  c2_info[262].fileTimeHi = 0U;
  c2_info[262].mFileTimeLo = 0U;
  c2_info[262].mFileTimeHi = 0U;
  c2_info[263].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[263].name = "max";
  c2_info[263].dominantType = "double";
  c2_info[263].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/datafun/max.m";
  c2_info[263].fileTimeLo = 1311258916U;
  c2_info[263].fileTimeHi = 0U;
  c2_info[263].mFileTimeLo = 0U;
  c2_info[263].mFileTimeHi = 0U;
  c2_info[264].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[264].name = "eml_error";
  c2_info[264].dominantType = "char";
  c2_info[264].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_error.m";
  c2_info[264].fileTimeLo = 1305321600U;
  c2_info[264].fileTimeHi = 0U;
  c2_info[264].mFileTimeLo = 0U;
  c2_info[264].mFileTimeHi = 0U;
  c2_info[265].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[265].name = "sqrt";
  c2_info[265].dominantType = "double";
  c2_info[265].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c2_info[265].fileTimeLo = 1286822352U;
  c2_info[265].fileTimeHi = 0U;
  c2_info[265].mFileTimeLo = 0U;
  c2_info[265].mFileTimeHi = 0U;
  c2_info[266].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c2_info[266].name = "eml_error";
  c2_info[266].dominantType = "char";
  c2_info[266].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_error.m";
  c2_info[266].fileTimeLo = 1305321600U;
  c2_info[266].fileTimeHi = 0U;
  c2_info[266].mFileTimeLo = 0U;
  c2_info[266].mFileTimeHi = 0U;
  c2_info[267].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c2_info[267].name = "eml_scalar_sqrt";
  c2_info[267].dominantType = "double";
  c2_info[267].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m";
  c2_info[267].fileTimeLo = 1286822338U;
  c2_info[267].fileTimeHi = 0U;
  c2_info[267].mFileTimeLo = 0U;
  c2_info[267].mFileTimeHi = 0U;
  c2_info[268].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zsvdc.m";
  c2_info[268].name = "eml_xrotg";
  c2_info[268].dominantType = "double";
  c2_info[268].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xrotg.m";
  c2_info[268].fileTimeLo = 1299080376U;
  c2_info[268].fileTimeHi = 0U;
  c2_info[268].mFileTimeLo = 0U;
  c2_info[268].mFileTimeHi = 0U;
  c2_info[269].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xrotg.m";
  c2_info[269].name = "eml_blas_inline";
  c2_info[269].dominantType = "";
  c2_info[269].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[269].fileTimeLo = 1299080368U;
  c2_info[269].fileTimeHi = 0U;
  c2_info[269].mFileTimeLo = 0U;
  c2_info[269].mFileTimeHi = 0U;
  c2_info[270].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xrotg.m";
  c2_info[270].name = "eml_refblas_xrotg";
  c2_info[270].dominantType = "double";
  c2_info[270].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xrotg.m";
  c2_info[270].fileTimeLo = 1299080384U;
  c2_info[270].fileTimeHi = 0U;
  c2_info[270].mFileTimeLo = 0U;
  c2_info[270].mFileTimeHi = 0U;
  c2_info[271].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xrotg.m";
  c2_info[271].name = "abs";
  c2_info[271].dominantType = "double";
  c2_info[271].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[271].fileTimeLo = 1286822294U;
  c2_info[271].fileTimeHi = 0U;
  c2_info[271].mFileTimeLo = 0U;
  c2_info[271].mFileTimeHi = 0U;
  c2_info[272].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xrotg.m";
  c2_info[272].name = "mrdivide";
  c2_info[272].dominantType = "double";
  c2_info[272].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[272].fileTimeLo = 1325127738U;
  c2_info[272].fileTimeHi = 0U;
  c2_info[272].mFileTimeLo = 1319733566U;
  c2_info[272].mFileTimeHi = 0U;
  c2_info[273].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xrotg.m";
  c2_info[273].name = "sqrt";
  c2_info[273].dominantType = "double";
  c2_info[273].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c2_info[273].fileTimeLo = 1286822352U;
  c2_info[273].fileTimeHi = 0U;
  c2_info[273].mFileTimeLo = 0U;
  c2_info[273].mFileTimeHi = 0U;
  c2_info[274].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xrotg.m!eml_ceval_xrotg";
  c2_info[274].name = "eml_scalar_eg";
  c2_info[274].dominantType = "double";
  c2_info[274].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[274].fileTimeLo = 1286822396U;
  c2_info[274].fileTimeHi = 0U;
  c2_info[274].mFileTimeLo = 0U;
  c2_info[274].mFileTimeHi = 0U;
  c2_info[275].context =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsv.m";
  c2_info[275].name = "eml_int_forloop_overflow_check";
  c2_info[275].dominantType = "";
  c2_info[275].resolved =
    "[ILXE]C:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[275].fileTimeLo = 1311258916U;
  c2_info[275].fileTimeHi = 0U;
  c2_info[275].mFileTimeLo = 0U;
  c2_info[275].mFileTimeHi = 0U;
}

static real_T c2_eml_div(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x, real_T c2_y)
{
  return c2_x / c2_y;
}

static void c2_diag(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                    real_T c2_v[1600], real_T c2_d[40])
{
  int32_T c2_i1022;
  int32_T c2_i1023;
  c2_i1022 = 0;
  for (c2_i1023 = 0; c2_i1023 < 40; c2_i1023++) {
    c2_d[c2_i1023] = c2_v[c2_i1022];
    c2_i1022 += 41;
  }
}

static real_T c2_abs(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                     real_T c2_x)
{
  real_T c2_b_x;
  c2_b_x = c2_x;
  return muDoubleScalarAbs(c2_b_x);
}

static void c2_eml_realmin(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_realmax(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
}

static void c2_preMultByA(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_M[3], real_T c2_A[9], real_T c2_switches[9], real_T
  c2_y[3])
{
  uint32_T c2_debug_family_var_map[7];
  real_T c2_n;
  real_T c2_nargin = 3.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i1024;
  real_T c2_a[9];
  int32_T c2_i1025;
  real_T c2_b[3];
  int32_T c2_i1026;
  int32_T c2_i1027;
  int32_T c2_i1028;
  real_T c2_C[3];
  int32_T c2_i1029;
  int32_T c2_i1030;
  int32_T c2_i1031;
  int32_T c2_i1032;
  int32_T c2_i1033;
  int32_T c2_i1034;
  int32_T c2_i1035;
  int32_T c2_ii;
  real_T c2_b_ii;
  real_T c2_b_a;
  real_T c2_b_y;
  real_T c2_c_a;
  real_T c2_c_y;
  real_T c2_d_a;
  real_T c2_b_b;
  real_T c2_d_y;
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c2_b_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_n, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 1U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 2U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_M, 3U, c2_i_sf_marshallOut,
    c2_r_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_A, 4U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_switches, 5U, c2_v_sf_marshallOut,
    c2_p_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_y, 6U, c2_i_sf_marshallOut,
    c2_r_sf_marshallIn);
  CV_EML_FCN(0, 14);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 929);
  if (CV_EML_IF(0, 1, 61, c2_switches[5] == 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 930);
    for (c2_i1024 = 0; c2_i1024 < 9; c2_i1024++) {
      c2_a[c2_i1024] = c2_A[c2_i1024];
    }

    for (c2_i1025 = 0; c2_i1025 < 3; c2_i1025++) {
      c2_b[c2_i1025] = c2_M[c2_i1025];
    }

    c2_eml_scalar_eg(chartInstance);
    c2_eml_scalar_eg(chartInstance);
    for (c2_i1026 = 0; c2_i1026 < 3; c2_i1026++) {
      c2_y[c2_i1026] = 0.0;
    }

    for (c2_i1027 = 0; c2_i1027 < 3; c2_i1027++) {
      c2_y[c2_i1027] = 0.0;
    }

    for (c2_i1028 = 0; c2_i1028 < 3; c2_i1028++) {
      c2_C[c2_i1028] = c2_y[c2_i1028];
    }

    for (c2_i1029 = 0; c2_i1029 < 3; c2_i1029++) {
      c2_y[c2_i1029] = c2_C[c2_i1029];
    }

    for (c2_i1030 = 0; c2_i1030 < 3; c2_i1030++) {
      c2_C[c2_i1030] = c2_y[c2_i1030];
    }

    for (c2_i1031 = 0; c2_i1031 < 3; c2_i1031++) {
      c2_y[c2_i1031] = c2_C[c2_i1031];
    }

    for (c2_i1032 = 0; c2_i1032 < 3; c2_i1032++) {
      c2_y[c2_i1032] = 0.0;
      c2_i1033 = 0;
      for (c2_i1034 = 0; c2_i1034 < 3; c2_i1034++) {
        c2_y[c2_i1032] += c2_a[c2_i1033 + c2_i1032] * c2_b[c2_i1034];
        c2_i1033 += 3;
      }
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 933);
    c2_n = 1.5;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 935);
    for (c2_i1035 = 0; c2_i1035 < 3; c2_i1035++) {
      c2_y[c2_i1035] = 0.0;
    }

    c2_ii = 0;
    while (c2_ii < 2) {
      c2_b_ii = 1.0 + (real_T)c2_ii;
      CV_EML_FOR(0, 1, 18, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 938);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_b_a = c2_b_ii - 1.0;
      c2_b_y = c2_b_a * 1.5;
      c2_c_a = c2_b_ii - 1.0;
      c2_c_y = c2_c_a * 1.5;
      c2_d_a = c2_A[0];
      c2_b_b = c2_M[_SFD_EML_ARRAY_BOUNDS_CHECK("M", (int32_T)_SFD_INTEGER_CHECK
        ("(1:n)+(ii-1)*n", 1.0 + c2_c_y), 1, 3, 1, 0) - 1];
      c2_d_y = c2_d_a * c2_b_b;
      c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("y", (int32_T)_SFD_INTEGER_CHECK(
        "(1:n)+(ii-1)*n", 1.0 + c2_b_y), 1, 3, 1, 0) - 1] = c2_d_y;
      c2_ii++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 18, 0);
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -938);
  sf_debug_symbol_scope_pop();
}

static void c2_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_b_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[40], real_T c2_C[44], real_T
  c2_b_C[44])
{
  int32_T c2_i1036;
  int32_T c2_i1037;
  real_T c2_b_A[1760];
  int32_T c2_i1038;
  real_T c2_b_B[40];
  for (c2_i1036 = 0; c2_i1036 < 44; c2_i1036++) {
    c2_b_C[c2_i1036] = c2_C[c2_i1036];
  }

  for (c2_i1037 = 0; c2_i1037 < 1760; c2_i1037++) {
    c2_b_A[c2_i1037] = c2_A[c2_i1037];
  }

  for (c2_i1038 = 0; c2_i1038 < 40; c2_i1038++) {
    c2_b_B[c2_i1038] = c2_B[c2_i1038];
  }

  c2_n_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static boolean_T c2_all(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, boolean_T c2_x[44])
{
  boolean_T c2_y;
  int32_T c2_k;
  real_T c2_b_k;
  boolean_T exitg1;
  c2_y = TRUE;
  c2_k = 0;
  exitg1 = FALSE;
  while ((exitg1 == 0U) && (c2_k < 44)) {
    c2_b_k = 1.0 + (real_T)c2_k;
    if ((real_T)c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
         ("", c2_b_k), 1, 44, 1, 0) - 1] == 0.0) {
      c2_y = FALSE;
      exitg1 = TRUE;
    } else {
      c2_k++;
    }
  }

  return c2_y;
}

static void c2_multByP(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
  real_T c2_z[40], real_T c2_P[1760], real_T c2_Fx[12], real_T c2_Fu[4], real_T
  c2_Ff[12], real_T c2_switches[9], real_T c2_y[44])
{
  uint32_T c2_debug_family_var_map[14];
  real_T c2_T;
  real_T c2_n;
  real_T c2_m;
  real_T c2_ell;
  real_T c2_ellf;
  real_T c2_nargin = 11.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i1039;
  real_T c2_a[1760];
  int32_T c2_i1040;
  real_T c2_b[40];
  int32_T c2_i1041;
  int32_T c2_i1042;
  int32_T c2_i1043;
  real_T c2_dv55[1760];
  int32_T c2_i1044;
  real_T c2_dv56[40];
  int32_T c2_i1045;
  real_T c2_dv57[1760];
  int32_T c2_i1046;
  real_T c2_dv58[40];
  int32_T c2_i1047;
  int32_T c2_i1048;
  real_T c2_b_a[4];
  real_T c2_b_b;
  int32_T c2_i1049;
  int32_T c2_i1050;
  int32_T c2_ii;
  real_T c2_b_ii;
  real_T c2_c_b;
  real_T c2_b_y;
  real_T c2_c_a;
  real_T c2_c_y;
  int32_T c2_i1051;
  real_T c2_d_a[12];
  real_T c2_b_m;
  int32_T c2_i1052;
  real_T c2_d_b[3];
  int32_T c2_i1053;
  real_T c2_d_y[4];
  int32_T c2_i1054;
  int32_T c2_i1055;
  real_T c2_e_a;
  real_T c2_e_y;
  int32_T c2_i1056;
  real_T c2_e_b;
  int32_T c2_i1057;
  int32_T c2_i1058;
  int32_T c2_i1059;
  real_T c2_c_m;
  int32_T c2_i1060;
  int32_T c2_i1061;
  int32_T c2_i1062;
  int32_T c2_i1063;
  int32_T c2_i1064;
  sf_debug_symbol_scope_push_eml(0U, 14U, 14U, c2_c_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_T, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_n, 1U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_m, 2U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_ell, 3U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_ellf, 4U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 5U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 6U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_z, 7U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_P, 8U, c2_m_sf_marshallOut,
    c2_t_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Fx, 9U, c2_c_sf_marshallOut,
    c2_s_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Fu, 10U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Ff, 11U, c2_c_sf_marshallOut,
    c2_s_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_switches, 12U, c2_v_sf_marshallOut,
    c2_p_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_y, 13U, c2_l_sf_marshallOut,
    c2_e_sf_marshallIn);
  c2_T = 10.0;
  c2_n = 3.0;
  c2_m = 1.0;
  c2_ell = 4.0;
  c2_ellf = 4.0;
  CV_EML_FCN(0, 10);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 845);
  if (CV_EML_IF(0, 1, 55, c2_switches[1] == 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 846);
    for (c2_i1039 = 0; c2_i1039 < 1760; c2_i1039++) {
      c2_a[c2_i1039] = c2_P[c2_i1039];
    }

    for (c2_i1040 = 0; c2_i1040 < 40; c2_i1040++) {
      c2_b[c2_i1040] = c2_z[c2_i1040];
    }

    c2_b_eml_scalar_eg(chartInstance);
    c2_b_eml_scalar_eg(chartInstance);
    for (c2_i1041 = 0; c2_i1041 < 44; c2_i1041++) {
      c2_y[c2_i1041] = 0.0;
    }

    for (c2_i1042 = 0; c2_i1042 < 44; c2_i1042++) {
      c2_y[c2_i1042] = 0.0;
    }

    for (c2_i1043 = 0; c2_i1043 < 1760; c2_i1043++) {
      c2_dv55[c2_i1043] = c2_a[c2_i1043];
    }

    for (c2_i1044 = 0; c2_i1044 < 40; c2_i1044++) {
      c2_dv56[c2_i1044] = c2_b[c2_i1044];
    }

    for (c2_i1045 = 0; c2_i1045 < 1760; c2_i1045++) {
      c2_dv57[c2_i1045] = c2_dv55[c2_i1045];
    }

    for (c2_i1046 = 0; c2_i1046 < 40; c2_i1046++) {
      c2_dv58[c2_i1046] = c2_dv56[c2_i1046];
    }

    c2_n_eml_xgemm(chartInstance, c2_dv57, c2_dv58, c2_y);
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 848);
    for (c2_i1047 = 0; c2_i1047 < 44; c2_i1047++) {
      c2_y[c2_i1047] = 0.0;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 850);
    for (c2_i1048 = 0; c2_i1048 < 4; c2_i1048++) {
      c2_b_a[c2_i1048] = c2_Fu[c2_i1048];
    }

    c2_b_b = c2_z[0];
    for (c2_i1049 = 0; c2_i1049 < 4; c2_i1049++) {
      c2_b_a[c2_i1049] *= c2_b_b;
    }

    for (c2_i1050 = 0; c2_i1050 < 4; c2_i1050++) {
      c2_y[c2_i1050] = c2_b_a[c2_i1050];
    }

    c2_ii = 0;
    while (c2_ii < 9) {
      c2_b_ii = 2.0 + (real_T)c2_ii;
      CV_EML_FOR(0, 1, 14, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 852);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_c_b = c2_b_ii - 1.0;
      c2_b_y = 4.0 * c2_c_b;
      c2_c_a = c2_b_ii - 2.0;
      c2_c_y = c2_c_a * 4.0;
      for (c2_i1051 = 0; c2_i1051 < 12; c2_i1051++) {
        c2_d_a[c2_i1051] = c2_Fx[c2_i1051];
      }

      c2_b_m = c2_m + c2_c_y;
      for (c2_i1052 = 0; c2_i1052 < 3; c2_i1052++) {
        c2_d_b[c2_i1052] = c2_z[_SFD_EML_ARRAY_BOUNDS_CHECK("z", (int32_T)
          _SFD_INTEGER_CHECK("m+(ii-2)*(n+m)+(1:n)", c2_b_m + (1.0 + (real_T)
          c2_i1052)), 1, 40, 1, 0) - 1];
      }

      c2_c_eml_scalar_eg(chartInstance);
      c2_c_eml_scalar_eg(chartInstance);
      for (c2_i1053 = 0; c2_i1053 < 4; c2_i1053++) {
        c2_d_y[c2_i1053] = 0.0;
        c2_i1054 = 0;
        for (c2_i1055 = 0; c2_i1055 < 3; c2_i1055++) {
          c2_d_y[c2_i1053] += c2_d_a[c2_i1054 + c2_i1053] * c2_d_b[c2_i1055];
          c2_i1054 += 4;
        }
      }

      c2_e_a = c2_b_ii - 1.0;
      c2_e_y = c2_e_a * 4.0;
      for (c2_i1056 = 0; c2_i1056 < 4; c2_i1056++) {
        c2_b_a[c2_i1056] = c2_Fu[c2_i1056];
      }

      c2_e_b = c2_z[_SFD_EML_ARRAY_BOUNDS_CHECK("z", (int32_T)_SFD_INTEGER_CHECK
        ("(ii-1)*(n+m)+(1:m)", c2_e_y + 1.0), 1, 40, 1, 0) - 1];
      for (c2_i1057 = 0; c2_i1057 < 4; c2_i1057++) {
        c2_b_a[c2_i1057] *= c2_e_b;
      }

      for (c2_i1058 = 0; c2_i1058 < 4; c2_i1058++) {
        c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("y", (int32_T)_SFD_INTEGER_CHECK(
          "ell*(ii-1)+(1:ell)", c2_b_y + (1.0 + (real_T)c2_i1058)), 1, 44, 1, 0)
          - 1] = c2_d_y[c2_i1058] + c2_b_a[c2_i1058];
      }

      c2_ii++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 14, 0);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 854);
    CV_EML_IF(0, 1, 56, c2_ellf > 0.0);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 855);
    c2_realmax(chartInstance);
    c2_realmax(chartInstance);
    for (c2_i1059 = 0; c2_i1059 < 12; c2_i1059++) {
      c2_d_a[c2_i1059] = c2_Ff[c2_i1059];
    }

    c2_c_m = c2_m + 36.0;
    for (c2_i1060 = 0; c2_i1060 < 3; c2_i1060++) {
      c2_d_b[c2_i1060] = c2_z[_SFD_EML_ARRAY_BOUNDS_CHECK("z", (int32_T)
        _SFD_INTEGER_CHECK("m+(T-1)*(n+m)+(1:n)", c2_c_m + (1.0 + (real_T)
        c2_i1060)), 1, 40, 1, 0) - 1];
    }

    c2_c_eml_scalar_eg(chartInstance);
    c2_c_eml_scalar_eg(chartInstance);
    for (c2_i1061 = 0; c2_i1061 < 4; c2_i1061++) {
      c2_d_y[c2_i1061] = 0.0;
      c2_i1062 = 0;
      for (c2_i1063 = 0; c2_i1063 < 3; c2_i1063++) {
        c2_d_y[c2_i1061] += c2_d_a[c2_i1062 + c2_i1061] * c2_d_b[c2_i1063];
        c2_i1062 += 4;
      }
    }

    for (c2_i1064 = 0; c2_i1064 < 4; c2_i1064++) {
      c2_y[c2_i1064 + 40] = c2_d_y[c2_i1064];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -855);
  sf_debug_symbol_scope_pop();
}

static void c2_c_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_rdivide(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
  real_T c2_x, real_T c2_y[44], real_T c2_z[44])
{
  real_T c2_b_x;
  int32_T c2_i1065;
  c2_b_x = c2_x;
  for (c2_i1065 = 0; c2_i1065 < 44; c2_i1065++) {
    c2_z[c2_i1065] = c2_b_x / c2_y[c2_i1065];
  }
}

static void c2_d_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_b_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[40], real_T c2_C[32], real_T
  c2_b_C[32])
{
  int32_T c2_i1066;
  int32_T c2_i1067;
  real_T c2_b_A[1280];
  int32_T c2_i1068;
  real_T c2_b_B[40];
  for (c2_i1066 = 0; c2_i1066 < 32; c2_i1066++) {
    c2_b_C[c2_i1066] = c2_C[c2_i1066];
  }

  for (c2_i1067 = 0; c2_i1067 < 1280; c2_i1067++) {
    c2_b_A[c2_i1067] = c2_A[c2_i1067];
  }

  for (c2_i1068 = 0; c2_i1068 < 40; c2_i1068++) {
    c2_b_B[c2_i1068] = c2_B[c2_i1068];
  }

  c2_o_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static void c2_calcRp(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_z[40], real_T c2_b[32], real_T c2_A[9], real_T
                      c2_B[3], real_T c2_C[1280], real_T c2_Ef[6], real_T
                      c2_switches[9], real_T c2_rp[32])
{
  uint32_T c2_debug_family_var_map[14];
  real_T c2_T;
  real_T c2_n;
  real_T c2_m;
  real_T c2_ellef;
  real_T c2_nargin = 11.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i1069;
  real_T c2_b_z[40];
  int32_T c2_i1070;
  real_T c2_b_A[9];
  int32_T c2_i1071;
  real_T c2_b_B[3];
  int32_T c2_i1072;
  real_T c2_b_C[1280];
  int32_T c2_i1073;
  real_T c2_b_Ef[6];
  int32_T c2_i1074;
  real_T c2_b_switches[9];
  real_T c2_dv59[32];
  int32_T c2_i1075;
  sf_debug_symbol_scope_push_eml(0U, 14U, 14U, c2_e_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_T, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_n, 1U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_m, 2U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_ellef, 3U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 4U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 5U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_z, 6U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_b, 7U, c2_j_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_A, 8U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_B, 9U, c2_i_sf_marshallOut,
    c2_r_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_C, 10U, c2_k_sf_marshallOut,
    c2_v_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Ef, 11U, c2_d_sf_marshallOut,
    c2_u_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_switches, 12U, c2_v_sf_marshallOut,
    c2_p_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_rp, 13U, c2_j_sf_marshallOut,
    c2_d_sf_marshallIn);
  c2_T = 10.0;
  c2_n = 3.0;
  c2_m = 1.0;
  c2_ellef = 2.0;
  CV_EML_FCN(0, 8);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 815);
  for (c2_i1069 = 0; c2_i1069 < 40; c2_i1069++) {
    c2_b_z[c2_i1069] = c2_z[c2_i1069];
  }

  for (c2_i1070 = 0; c2_i1070 < 9; c2_i1070++) {
    c2_b_A[c2_i1070] = c2_A[c2_i1070];
  }

  for (c2_i1071 = 0; c2_i1071 < 3; c2_i1071++) {
    c2_b_B[c2_i1071] = c2_B[c2_i1071];
  }

  for (c2_i1072 = 0; c2_i1072 < 1280; c2_i1072++) {
    c2_b_C[c2_i1072] = c2_C[c2_i1072];
  }

  for (c2_i1073 = 0; c2_i1073 < 6; c2_i1073++) {
    c2_b_Ef[c2_i1073] = c2_Ef[c2_i1073];
  }

  for (c2_i1074 = 0; c2_i1074 < 9; c2_i1074++) {
    c2_b_switches[c2_i1074] = c2_switches[c2_i1074];
  }

  c2_multByC(chartInstance, c2_b_z, c2_b_A, c2_b_B, c2_b_C, c2_b_Ef,
             c2_b_switches, c2_dv59);
  for (c2_i1075 = 0; c2_i1075 < 32; c2_i1075++) {
    c2_rp[c2_i1075] = c2_dv59[c2_i1075] - c2_b[c2_i1075];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -815);
  sf_debug_symbol_scope_pop();
}

static void c2_multByC(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
  real_T c2_z[40], real_T c2_A[9], real_T c2_B[3], real_T c2_C[1280], real_T
  c2_Ef[6], real_T c2_switches[9], real_T c2_y[32])
{
  uint32_T c2_debug_family_var_map[13];
  real_T c2_T;
  real_T c2_n;
  real_T c2_m;
  real_T c2_ellef;
  real_T c2_nargin = 10.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i1076;
  real_T c2_a[1280];
  int32_T c2_i1077;
  real_T c2_b[40];
  int32_T c2_i1078;
  int32_T c2_i1079;
  int32_T c2_i1080;
  real_T c2_dv60[1280];
  int32_T c2_i1081;
  real_T c2_dv61[40];
  int32_T c2_i1082;
  real_T c2_dv62[1280];
  int32_T c2_i1083;
  real_T c2_dv63[40];
  int32_T c2_i1084;
  int32_T c2_i1085;
  real_T c2_b_a[3];
  real_T c2_b_b;
  int32_T c2_i1086;
  int32_T c2_i1087;
  int32_T c2_ii;
  real_T c2_b_ii;
  real_T c2_c_b;
  real_T c2_b_y;
  real_T c2_c_a;
  real_T c2_c_y;
  real_T c2_d_a;
  real_T c2_d_y;
  real_T c2_e_a;
  real_T c2_e_y;
  int32_T c2_i1088;
  real_T c2_d_b;
  int32_T c2_i1089;
  real_T c2_b_m;
  int32_T c2_i1090;
  real_T c2_b_z[3];
  int32_T c2_i1091;
  real_T c2_b_A[9];
  int32_T c2_i1092;
  real_T c2_b_switches[9];
  real_T c2_dv64[3];
  real_T c2_c_m;
  int32_T c2_i1093;
  int32_T c2_i1094;
  real_T c2_f_a[6];
  real_T c2_d_m;
  int32_T c2_i1095;
  int32_T c2_i1096;
  real_T c2_f_y[2];
  int32_T c2_i1097;
  int32_T c2_i1098;
  int32_T c2_i1099;
  sf_debug_symbol_scope_push_eml(0U, 13U, 13U, c2_d_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_T, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_n, 1U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_m, 2U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_ellef, 3U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 4U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 5U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_z, 6U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_A, 7U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_B, 8U, c2_i_sf_marshallOut,
    c2_r_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_C, 9U, c2_k_sf_marshallOut,
    c2_v_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Ef, 10U, c2_d_sf_marshallOut,
    c2_u_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_switches, 11U, c2_v_sf_marshallOut,
    c2_p_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_y, 12U, c2_j_sf_marshallOut,
    c2_d_sf_marshallIn);
  c2_T = 10.0;
  c2_n = 3.0;
  c2_m = 1.0;
  c2_ellef = 2.0;
  CV_EML_FCN(0, 9);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 823);
  if (CV_EML_IF(0, 1, 53, c2_switches[0] == 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 824);
    for (c2_i1076 = 0; c2_i1076 < 1280; c2_i1076++) {
      c2_a[c2_i1076] = c2_C[c2_i1076];
    }

    for (c2_i1077 = 0; c2_i1077 < 40; c2_i1077++) {
      c2_b[c2_i1077] = c2_z[c2_i1077];
    }

    c2_d_eml_scalar_eg(chartInstance);
    c2_d_eml_scalar_eg(chartInstance);
    for (c2_i1078 = 0; c2_i1078 < 32; c2_i1078++) {
      c2_y[c2_i1078] = 0.0;
    }

    for (c2_i1079 = 0; c2_i1079 < 32; c2_i1079++) {
      c2_y[c2_i1079] = 0.0;
    }

    for (c2_i1080 = 0; c2_i1080 < 1280; c2_i1080++) {
      c2_dv60[c2_i1080] = c2_a[c2_i1080];
    }

    for (c2_i1081 = 0; c2_i1081 < 40; c2_i1081++) {
      c2_dv61[c2_i1081] = c2_b[c2_i1081];
    }

    for (c2_i1082 = 0; c2_i1082 < 1280; c2_i1082++) {
      c2_dv62[c2_i1082] = c2_dv60[c2_i1082];
    }

    for (c2_i1083 = 0; c2_i1083 < 40; c2_i1083++) {
      c2_dv63[c2_i1083] = c2_dv61[c2_i1083];
    }

    c2_o_eml_xgemm(chartInstance, c2_dv62, c2_dv63, c2_y);
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 826);
    for (c2_i1084 = 0; c2_i1084 < 32; c2_i1084++) {
      c2_y[c2_i1084] = 0.0;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 828);
    c2_realmax(chartInstance);
    for (c2_i1085 = 0; c2_i1085 < 3; c2_i1085++) {
      c2_b_a[c2_i1085] = c2_B[c2_i1085];
    }

    c2_b_b = c2_z[0];
    for (c2_i1086 = 0; c2_i1086 < 3; c2_i1086++) {
      c2_b_a[c2_i1086] *= c2_b_b;
    }

    for (c2_i1087 = 0; c2_i1087 < 3; c2_i1087++) {
      c2_y[c2_i1087] = c2_z[_SFD_EML_ARRAY_BOUNDS_CHECK("z", (int32_T)
        _SFD_INTEGER_CHECK("m+(1:n)", c2_m + (1.0 + (real_T)c2_i1087)), 1, 40, 1,
        0) - 1] - c2_b_a[c2_i1087];
    }

    c2_ii = 0;
    while (c2_ii < 9) {
      c2_b_ii = 2.0 + (real_T)c2_ii;
      CV_EML_FOR(0, 1, 13, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 831);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_c_b = c2_b_ii - 1.0;
      c2_b_y = 3.0 * c2_c_b;
      c2_c_a = c2_b_ii - 1.0;
      c2_c_y = c2_c_a * 4.0;
      c2_d_a = c2_b_ii - 2.0;
      c2_d_y = c2_d_a * 4.0;
      c2_e_a = c2_b_ii - 1.0;
      c2_e_y = c2_e_a * 4.0;
      for (c2_i1088 = 0; c2_i1088 < 3; c2_i1088++) {
        c2_b_a[c2_i1088] = c2_B[c2_i1088];
      }

      c2_d_b = c2_z[_SFD_EML_ARRAY_BOUNDS_CHECK("z", (int32_T)_SFD_INTEGER_CHECK
        ("(ii-1)*(n+m)+(1:m)", c2_e_y + 1.0), 1, 40, 1, 0) - 1];
      for (c2_i1089 = 0; c2_i1089 < 3; c2_i1089++) {
        c2_b_a[c2_i1089] *= c2_d_b;
      }

      c2_b_m = c2_m + c2_d_y;
      for (c2_i1090 = 0; c2_i1090 < 3; c2_i1090++) {
        c2_b_z[c2_i1090] = c2_z[_SFD_EML_ARRAY_BOUNDS_CHECK("z", (int32_T)
          _SFD_INTEGER_CHECK("m+(ii-2)*(n+m)+(1:n)", c2_b_m + (1.0 + (real_T)
          c2_i1090)), 1, 40, 1, 0) - 1];
      }

      for (c2_i1091 = 0; c2_i1091 < 9; c2_i1091++) {
        c2_b_A[c2_i1091] = c2_A[c2_i1091];
      }

      for (c2_i1092 = 0; c2_i1092 < 9; c2_i1092++) {
        c2_b_switches[c2_i1092] = c2_switches[c2_i1092];
      }

      c2_preMultByA(chartInstance, c2_b_z, c2_b_A, c2_b_switches, c2_dv64);
      c2_c_m = c2_m + c2_c_y;
      for (c2_i1093 = 0; c2_i1093 < 3; c2_i1093++) {
        c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("y", (int32_T)_SFD_INTEGER_CHECK(
          "n*(ii-1)+(1:n)", c2_b_y + (1.0 + (real_T)c2_i1093)), 1, 32, 1, 0) - 1]
          = (c2_z[_SFD_EML_ARRAY_BOUNDS_CHECK("z", (int32_T)_SFD_INTEGER_CHECK(
               "m+(ii-1)*(n+m)+(1:n)", c2_c_m + (1.0 + (real_T)c2_i1093)), 1, 40,
              1, 0) - 1] - c2_dv64[c2_i1093]) - c2_b_a[c2_i1093];
      }

      c2_ii++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 13, 0);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 834);
    CV_EML_IF(0, 1, 54, c2_ellef > 0.0);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 835);
    c2_realmax(chartInstance);
    c2_realmax(chartInstance);
    for (c2_i1094 = 0; c2_i1094 < 6; c2_i1094++) {
      c2_f_a[c2_i1094] = c2_Ef[c2_i1094];
    }

    c2_d_m = c2_m + 36.0;
    for (c2_i1095 = 0; c2_i1095 < 3; c2_i1095++) {
      c2_b_a[c2_i1095] = c2_z[_SFD_EML_ARRAY_BOUNDS_CHECK("z", (int32_T)
        _SFD_INTEGER_CHECK("m+(T-1)*(n+m)+(1:n)", c2_d_m + (1.0 + (real_T)
        c2_i1095)), 1, 40, 1, 0) - 1];
    }

    c2_e_eml_scalar_eg(chartInstance);
    c2_e_eml_scalar_eg(chartInstance);
    for (c2_i1096 = 0; c2_i1096 < 2; c2_i1096++) {
      c2_f_y[c2_i1096] = 0.0;
      c2_i1097 = 0;
      for (c2_i1098 = 0; c2_i1098 < 3; c2_i1098++) {
        c2_f_y[c2_i1096] += c2_f_a[c2_i1097 + c2_i1096] * c2_b_a[c2_i1098];
        c2_i1097 += 2;
      }
    }

    for (c2_i1099 = 0; c2_i1099 < 2; c2_i1099++) {
      c2_y[c2_i1099 + 30] = c2_f_y[c2_i1099];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -835);
  sf_debug_symbol_scope_pop();
}

static void c2_e_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static real_T c2_norm(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_x[32])
{
  real_T c2_y;
  real_T c2_scale;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_absxk;
  real_T c2_t;
  c2_y = 0.0;
  c2_eml_realmin(chartInstance);
  c2_scale = 2.2250738585072014E-308;
  c2_eml_int_forloop_overflow_check(chartInstance);
  for (c2_k = 1; c2_k < 33; c2_k++) {
    c2_b_k = c2_k;
    c2_b_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_b_k), 1, 32, 1, 0) - 1];
    c2_c_x = c2_b_x;
    c2_absxk = muDoubleScalarAbs(c2_c_x);
    if (c2_absxk > c2_scale) {
      c2_t = c2_scale / c2_absxk;
      c2_y = 1.0 + c2_y * c2_t * c2_t;
      c2_scale = c2_absxk;
    } else {
      c2_t = c2_absxk / c2_scale;
      c2_y += c2_t * c2_t;
    }
  }

  return c2_scale * muDoubleScalarSqrt(c2_y);
}

static void c2_realmin(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
  c2_eml_realmin(chartInstance);
}

static void c2_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
}

static void c2_f_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_c_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[44], real_T c2_C[40], real_T
  c2_b_C[40])
{
  int32_T c2_i1100;
  int32_T c2_i1101;
  real_T c2_b_A[1760];
  int32_T c2_i1102;
  real_T c2_b_B[44];
  for (c2_i1100 = 0; c2_i1100 < 40; c2_i1100++) {
    c2_b_C[c2_i1100] = c2_C[c2_i1100];
  }

  for (c2_i1101 = 0; c2_i1101 < 1760; c2_i1101++) {
    c2_b_A[c2_i1101] = c2_A[c2_i1101];
  }

  for (c2_i1102 = 0; c2_i1102 < 44; c2_i1102++) {
    c2_b_B[c2_i1102] = c2_B[c2_i1102];
  }

  c2_p_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static void c2_g_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_d_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[32], real_T c2_C[40], real_T
  c2_b_C[40])
{
  int32_T c2_i1103;
  int32_T c2_i1104;
  real_T c2_b_A[1280];
  int32_T c2_i1105;
  real_T c2_b_B[32];
  for (c2_i1103 = 0; c2_i1103 < 40; c2_i1103++) {
    c2_b_C[c2_i1103] = c2_C[c2_i1103];
  }

  for (c2_i1104 = 0; c2_i1104 < 1280; c2_i1104++) {
    c2_b_A[c2_i1104] = c2_A[c2_i1104];
  }

  for (c2_i1105 = 0; c2_i1105 < 32; c2_i1105++) {
    c2_b_B[c2_i1105] = c2_B[c2_i1105];
  }

  c2_q_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static void c2_multByCT(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_nu[32], real_T c2_CT[1280], real_T c2_AT[9], real_T
  c2_BT[3], real_T c2_EfT[6], real_T c2_switches[9], real_T c2_y[40])
{
  uint32_T c2_debug_family_var_map[13];
  real_T c2_T;
  real_T c2_n;
  real_T c2_m;
  real_T c2_ellef;
  real_T c2_nargin = 10.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i1106;
  real_T c2_a[1280];
  int32_T c2_i1107;
  real_T c2_b[32];
  int32_T c2_i1108;
  int32_T c2_i1109;
  int32_T c2_i1110;
  real_T c2_dv65[1280];
  int32_T c2_i1111;
  real_T c2_dv66[32];
  int32_T c2_i1112;
  real_T c2_dv67[1280];
  int32_T c2_i1113;
  real_T c2_dv68[32];
  int32_T c2_i1114;
  int32_T c2_i1115;
  real_T c2_b_a[3];
  int32_T c2_i1116;
  real_T c2_b_b[3];
  real_T c2_b_y;
  int32_T c2_k;
  int32_T c2_b_k;
  int32_T c2_ii;
  real_T c2_b_ii;
  real_T c2_c_a;
  real_T c2_c_y;
  real_T c2_d_a;
  real_T c2_d_y;
  real_T c2_e_a;
  real_T c2_e_y;
  int32_T c2_i1117;
  real_T c2_b_nu[3];
  int32_T c2_i1118;
  real_T c2_b_AT[9];
  int32_T c2_i1119;
  real_T c2_b_switches[9];
  int32_T c2_i1120;
  real_T c2_f_a;
  real_T c2_f_y;
  real_T c2_g_a;
  real_T c2_g_y;
  int32_T c2_i1121;
  int32_T c2_i1122;
  real_T c2_h_y;
  int32_T c2_c_k;
  int32_T c2_d_k;
  real_T c2_d3;
  int32_T c2_i1123;
  int32_T c2_i1124;
  real_T c2_h_a[6];
  int32_T c2_i1125;
  real_T c2_c_b[2];
  int32_T c2_i1126;
  int32_T c2_i1127;
  int32_T c2_i1128;
  int32_T c2_i1129;
  sf_debug_symbol_scope_push_eml(0U, 13U, 13U, c2_f_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_T, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_n, 1U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_m, 2U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_ellef, 3U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 4U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 5U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_nu, 6U, c2_j_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_CT, 7U, c2_q_sf_marshallOut,
    c2_k_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_AT, 8U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_BT, 9U, c2_r_sf_marshallOut,
    c2_l_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_EfT, 10U, c2_p_sf_marshallOut,
    c2_j_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_switches, 11U, c2_v_sf_marshallOut,
    c2_p_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_y, 12U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  c2_T = 10.0;
  c2_n = 3.0;
  c2_m = 1.0;
  c2_ellef = 2.0;
  CV_EML_FCN(0, 13);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 905);
  if (CV_EML_IF(0, 1, 59, c2_switches[4] == 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 906);
    for (c2_i1106 = 0; c2_i1106 < 1280; c2_i1106++) {
      c2_a[c2_i1106] = c2_CT[c2_i1106];
    }

    for (c2_i1107 = 0; c2_i1107 < 32; c2_i1107++) {
      c2_b[c2_i1107] = c2_nu[c2_i1107];
    }

    c2_g_eml_scalar_eg(chartInstance);
    c2_g_eml_scalar_eg(chartInstance);
    for (c2_i1108 = 0; c2_i1108 < 40; c2_i1108++) {
      c2_y[c2_i1108] = 0.0;
    }

    for (c2_i1109 = 0; c2_i1109 < 40; c2_i1109++) {
      c2_y[c2_i1109] = 0.0;
    }

    for (c2_i1110 = 0; c2_i1110 < 1280; c2_i1110++) {
      c2_dv65[c2_i1110] = c2_a[c2_i1110];
    }

    for (c2_i1111 = 0; c2_i1111 < 32; c2_i1111++) {
      c2_dv66[c2_i1111] = c2_b[c2_i1111];
    }

    for (c2_i1112 = 0; c2_i1112 < 1280; c2_i1112++) {
      c2_dv67[c2_i1112] = c2_dv65[c2_i1112];
    }

    for (c2_i1113 = 0; c2_i1113 < 32; c2_i1113++) {
      c2_dv68[c2_i1113] = c2_dv66[c2_i1113];
    }

    c2_q_eml_xgemm(chartInstance, c2_dv67, c2_dv68, c2_y);
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 908);
    for (c2_i1114 = 0; c2_i1114 < 40; c2_i1114++) {
      c2_y[c2_i1114] = 0.0;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 910);
    for (c2_i1115 = 0; c2_i1115 < 3; c2_i1115++) {
      c2_b_a[c2_i1115] = -c2_BT[c2_i1115];
    }

    for (c2_i1116 = 0; c2_i1116 < 3; c2_i1116++) {
      c2_b_b[c2_i1116] = c2_nu[c2_i1116];
    }

    c2_h_eml_scalar_eg(chartInstance);
    c2_h_eml_scalar_eg(chartInstance);
    c2_b_y = 0.0;
    c2_b_eml_int_forloop_overflow_check(chartInstance);
    for (c2_k = 1; c2_k < 4; c2_k++) {
      c2_b_k = c2_k;
      c2_b_y += c2_b_a[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 3, 1, 0) - 1] *
        c2_b_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_b_k), 1, 3, 1, 0) - 1];
    }

    c2_y[0] = c2_b_y;
    c2_ii = 0;
    while (c2_ii < 9) {
      c2_b_ii = 2.0 + (real_T)c2_ii;
      CV_EML_FOR(0, 1, 17, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 913);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_c_a = c2_b_ii - 2.0;
      c2_c_y = c2_c_a * 4.0;
      c2_d_a = c2_b_ii - 2.0;
      c2_d_y = c2_d_a * 3.0;
      c2_e_a = c2_b_ii - 1.0;
      c2_e_y = c2_e_a * 3.0;
      for (c2_i1117 = 0; c2_i1117 < 3; c2_i1117++) {
        c2_b_nu[c2_i1117] = c2_nu[_SFD_EML_ARRAY_BOUNDS_CHECK("nu", (int32_T)
          _SFD_INTEGER_CHECK("(1:n) + (ii-1)*n", (1.0 + (real_T)c2_i1117) +
                             c2_e_y), 1, 32, 1, 0) - 1];
      }

      for (c2_i1118 = 0; c2_i1118 < 9; c2_i1118++) {
        c2_b_AT[c2_i1118] = c2_AT[c2_i1118];
      }

      for (c2_i1119 = 0; c2_i1119 < 9; c2_i1119++) {
        c2_b_switches[c2_i1119] = c2_switches[c2_i1119];
      }

      c2_preMultByA(chartInstance, c2_b_nu, c2_b_AT, c2_b_switches, c2_b_b);
      for (c2_i1120 = 0; c2_i1120 < 3; c2_i1120++) {
        c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("y", (int32_T)_SFD_INTEGER_CHECK(
          "m+(1:n)+(ii-2)*(n+m)", (c2_m + (1.0 + (real_T)c2_i1120)) + c2_c_y), 1,
          40, 1, 0) - 1] = c2_nu[_SFD_EML_ARRAY_BOUNDS_CHECK("nu", (int32_T)
          _SFD_INTEGER_CHECK("(1:n) + (ii-2)*n", (1.0 + (real_T)c2_i1120) +
                             c2_d_y), 1, 32, 1, 0) - 1] - c2_b_b[c2_i1120];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 914);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_f_a = c2_b_ii - 2.0;
      c2_f_y = c2_f_a * 4.0;
      c2_g_a = c2_b_ii - 1.0;
      c2_g_y = c2_g_a * 3.0;
      for (c2_i1121 = 0; c2_i1121 < 3; c2_i1121++) {
        c2_b_a[c2_i1121] = -c2_BT[c2_i1121];
      }

      for (c2_i1122 = 0; c2_i1122 < 3; c2_i1122++) {
        c2_b_b[c2_i1122] = c2_nu[_SFD_EML_ARRAY_BOUNDS_CHECK("nu", (int32_T)
          _SFD_INTEGER_CHECK("(1:n) + (ii-1)*n", (1.0 + (real_T)c2_i1122) +
                             c2_g_y), 1, 32, 1, 0) - 1];
      }

      c2_h_eml_scalar_eg(chartInstance);
      c2_h_eml_scalar_eg(chartInstance);
      c2_h_y = 0.0;
      c2_b_eml_int_forloop_overflow_check(chartInstance);
      for (c2_c_k = 1; c2_c_k < 4; c2_c_k++) {
        c2_d_k = c2_c_k;
        c2_h_y += c2_b_a[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_d_k), 1, 3, 1, 0) - 1] *
          c2_b_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_d_k), 1, 3, 1, 0) - 1];
      }

      c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("y", (int32_T)_SFD_INTEGER_CHECK(
        "m+n+(1:m)+(ii-2)*(n+m)", ((c2_m + c2_n) + 1.0) + c2_f_y), 1, 40, 1, 0)
        - 1] = c2_h_y;
      c2_ii++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 17, 0);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 916);
    c2_realmax(chartInstance);
    c2_realmax(chartInstance);
    c2_d3 = 36.0 + c2_m;
    for (c2_i1123 = 0; c2_i1123 < 3; c2_i1123++) {
      c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("y", (int32_T)_SFD_INTEGER_CHECK(
        "(T-1)*(n+m)+m+(1:n)", c2_d3 + (1.0 + (real_T)c2_i1123)), 1, 40, 1, 0) -
        1] = c2_nu[27 + c2_i1123];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 918);
    CV_EML_IF(0, 1, 60, c2_ellef > 0.0);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 919);
    c2_realmax(chartInstance);
    c2_realmax(chartInstance);
    for (c2_i1124 = 0; c2_i1124 < 6; c2_i1124++) {
      c2_h_a[c2_i1124] = c2_EfT[c2_i1124];
    }

    for (c2_i1125 = 0; c2_i1125 < 2; c2_i1125++) {
      c2_c_b[c2_i1125] = c2_nu[c2_i1125 + 30];
    }

    c2_i_eml_scalar_eg(chartInstance);
    c2_i_eml_scalar_eg(chartInstance);
    for (c2_i1126 = 0; c2_i1126 < 3; c2_i1126++) {
      c2_b_b[c2_i1126] = 0.0;
      c2_i1127 = 0;
      for (c2_i1128 = 0; c2_i1128 < 2; c2_i1128++) {
        c2_b_b[c2_i1126] += c2_h_a[c2_i1127 + c2_i1126] * c2_c_b[c2_i1128];
        c2_i1127 += 3;
      }
    }

    for (c2_i1129 = 0; c2_i1129 < 3; c2_i1129++) {
      c2_y[c2_i1129 + 37] = c2_nu[c2_i1129 + 27] + c2_b_b[c2_i1129];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -919);
  sf_debug_symbol_scope_pop();
}

static void c2_h_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_b_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
}

static void c2_i_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_j_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_e_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1600], real_T c2_B[40], real_T c2_C[40], real_T
  c2_b_C[40])
{
  int32_T c2_i1130;
  int32_T c2_i1131;
  real_T c2_b_A[1600];
  int32_T c2_i1132;
  real_T c2_b_B[40];
  for (c2_i1130 = 0; c2_i1130 < 40; c2_i1130++) {
    c2_b_C[c2_i1130] = c2_C[c2_i1130];
  }

  for (c2_i1131 = 0; c2_i1131 < 1600; c2_i1131++) {
    c2_b_A[c2_i1131] = c2_A[c2_i1131];
  }

  for (c2_i1132 = 0; c2_i1132 < 40; c2_i1132++) {
    c2_b_B[c2_i1132] = c2_B[c2_i1132];
  }

  c2_r_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static void c2_calcDs(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_z[40], real_T c2_Ps[1600], real_T c2_Fxs[12],
                      real_T c2_Fus[4], real_T c2_hs[40], boolean_T
                      c2_flagNoPade, real_T c2_switches[9], real_T c2_ds[40],
                      real_T c2_es[40])
{
  uint32_T c2_debug_family_var_map[18];
  real_T c2_rs[40];
  real_T c2_checkPs;
  real_T c2_T;
  real_T c2_n;
  real_T c2_m;
  real_T c2_ells;
  real_T c2_rho;
  real_T c2_nargin = 12.0;
  real_T c2_nargout = 2.0;
  int32_T c2_i1133;
  int32_T c2_i1134;
  int32_T c2_i1135;
  real_T c2_b_z[40];
  int32_T c2_i1136;
  real_T c2_b_Ps[1600];
  int32_T c2_i1137;
  real_T c2_b_Fxs[12];
  int32_T c2_i1138;
  real_T c2_b_Fus[4];
  int32_T c2_i1139;
  real_T c2_b_switches[9];
  real_T c2_dv69[40];
  int32_T c2_i1140;
  int32_T c2_ii;
  real_T c2_b_ii;
  real_T c2_b;
  real_T c2_y;
  real_T c2_B;
  real_T c2_b_y;
  real_T c2_c_y;
  real_T c2_d_y;
  real_T c2_b_b;
  real_T c2_e_y;
  real_T c2_A;
  real_T c2_b_B;
  real_T c2_x;
  real_T c2_f_y;
  real_T c2_b_x;
  real_T c2_g_y;
  real_T c2_h_y;
  sf_debug_symbol_scope_push_eml(0U, 18U, 18U, c2_i_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(c2_rs, 0U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_checkPs, 1U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c2_T, 2U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_n, 3U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_m, 4U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_ells, 5U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_rho, 6U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 7U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 8U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_z, 9U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Ps, 10U, c2_e_sf_marshallOut,
    c2_i_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Fxs, 11U, c2_c_sf_marshallOut,
    c2_s_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Fus, 12U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_hs, 13U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_flagNoPade, 14U,
    c2_w_sf_marshallOut, c2_q_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_switches, 15U, c2_v_sf_marshallOut,
    c2_p_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_ds, 16U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_es, 17U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  c2_T = 10.0;
  c2_n = 3.0;
  c2_m = 1.0;
  c2_ells = 4.0;
  c2_rho = 10.0;
  CV_EML_FCN(0, 6);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 766);
  for (c2_i1133 = 0; c2_i1133 < 40; c2_i1133++) {
    c2_es[c2_i1133] = c2_hs[c2_i1133];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 767);
  for (c2_i1134 = 0; c2_i1134 < 40; c2_i1134++) {
    c2_ds[c2_i1134] = c2_hs[c2_i1134];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 771);
  for (c2_i1135 = 0; c2_i1135 < 40; c2_i1135++) {
    c2_b_z[c2_i1135] = c2_z[c2_i1135];
  }

  for (c2_i1136 = 0; c2_i1136 < 1600; c2_i1136++) {
    c2_b_Ps[c2_i1136] = c2_Ps[c2_i1136];
  }

  for (c2_i1137 = 0; c2_i1137 < 12; c2_i1137++) {
    c2_b_Fxs[c2_i1137] = c2_Fxs[c2_i1137];
  }

  for (c2_i1138 = 0; c2_i1138 < 4; c2_i1138++) {
    c2_b_Fus[c2_i1138] = c2_Fus[c2_i1138];
  }

  for (c2_i1139 = 0; c2_i1139 < 9; c2_i1139++) {
    c2_b_switches[c2_i1139] = c2_switches[c2_i1139];
  }

  c2_multByPs(chartInstance, c2_b_z, c2_b_Ps, c2_b_Fxs, c2_b_Fus, c2_b_switches,
              c2_dv69);
  for (c2_i1140 = 0; c2_i1140 < 40; c2_i1140++) {
    c2_rs[c2_i1140] = c2_dv69[c2_i1140] - c2_hs[c2_i1140];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 773);
  CV_EML_IF(0, 1, 50, FALSE);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 776);
  c2_checkPs = 0.0;
  c2_ii = 0;
  while (c2_ii < 40) {
    c2_b_ii = 1.0 + (real_T)c2_ii;
    CV_EML_FOR(0, 1, 11, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 783);
    if (CV_EML_IF(0, 1, 51, c2_rs[_SFD_EML_ARRAY_BOUNDS_CHECK("rs", (int32_T)
          _SFD_INTEGER_CHECK("ii", c2_b_ii), 1, 40, 1, 0) - 1] > 0.0)) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 784);
      c2_b = c2_rs[_SFD_EML_ARRAY_BOUNDS_CHECK("rs", (int32_T)_SFD_INTEGER_CHECK
        ("ii", c2_b_ii), 1, 40, 1, 0) - 1];
      c2_y = -10.0 * c2_b;
      c2_es[_SFD_EML_ARRAY_BOUNDS_CHECK("es", (int32_T)_SFD_INTEGER_CHECK("ii",
        c2_b_ii), 1, 40, 1, 0) - 1] = c2_myexp(chartInstance, c2_y,
        c2_flagNoPade);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 785);
      c2_B = 1.0 + c2_es[_SFD_EML_ARRAY_BOUNDS_CHECK("es", (int32_T)
        _SFD_INTEGER_CHECK("ii", c2_b_ii), 1, 40, 1, 0) - 1];
      c2_b_y = c2_B;
      c2_c_y = c2_b_y;
      c2_d_y = 1.0 / c2_c_y;
      c2_ds[_SFD_EML_ARRAY_BOUNDS_CHECK("ds", (int32_T)_SFD_INTEGER_CHECK("ii",
        c2_b_ii), 1, 40, 1, 0) - 1] = c2_d_y;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 787);
      c2_b_b = c2_rs[_SFD_EML_ARRAY_BOUNDS_CHECK("rs", (int32_T)
        _SFD_INTEGER_CHECK("ii", c2_b_ii), 1, 40, 1, 0) - 1];
      c2_e_y = 10.0 * c2_b_b;
      c2_es[_SFD_EML_ARRAY_BOUNDS_CHECK("es", (int32_T)_SFD_INTEGER_CHECK("ii",
        c2_b_ii), 1, 40, 1, 0) - 1] = c2_myexp(chartInstance, c2_e_y,
        c2_flagNoPade);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 788);
      c2_A = c2_es[_SFD_EML_ARRAY_BOUNDS_CHECK("es", (int32_T)_SFD_INTEGER_CHECK
        ("ii", c2_b_ii), 1, 40, 1, 0) - 1];
      c2_b_B = 1.0 + c2_es[_SFD_EML_ARRAY_BOUNDS_CHECK("es", (int32_T)
        _SFD_INTEGER_CHECK("ii", c2_b_ii), 1, 40, 1, 0) - 1];
      c2_x = c2_A;
      c2_f_y = c2_b_B;
      c2_b_x = c2_x;
      c2_g_y = c2_f_y;
      c2_h_y = c2_b_x / c2_g_y;
      c2_ds[_SFD_EML_ARRAY_BOUNDS_CHECK("ds", (int32_T)_SFD_INTEGER_CHECK("ii",
        c2_b_ii), 1, 40, 1, 0) - 1] = c2_h_y;
    }

    c2_ii++;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 11, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -788);
  sf_debug_symbol_scope_pop();
}

static void c2_multByPs(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_z[40], real_T c2_Ps[1600], real_T c2_Fxs[12], real_T
  c2_Fus[4], real_T c2_switches[9], real_T c2_y[40])
{
  uint32_T c2_debug_family_var_map[12];
  real_T c2_T;
  real_T c2_n;
  real_T c2_m;
  real_T c2_ells;
  real_T c2_nargin = 9.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i1141;
  static real_T c2_a[1600];
  int32_T c2_i1142;
  real_T c2_b[40];
  int32_T c2_i1143;
  int32_T c2_i1144;
  int32_T c2_i1145;
  static real_T c2_dv70[1600];
  int32_T c2_i1146;
  real_T c2_dv71[40];
  int32_T c2_i1147;
  static real_T c2_dv72[1600];
  int32_T c2_i1148;
  real_T c2_dv73[40];
  int32_T c2_i1149;
  int32_T c2_i1150;
  real_T c2_b_a[4];
  real_T c2_b_b;
  int32_T c2_i1151;
  int32_T c2_i1152;
  int32_T c2_ii;
  real_T c2_b_ii;
  real_T c2_c_b;
  real_T c2_b_y;
  real_T c2_c_a;
  real_T c2_c_y;
  int32_T c2_i1153;
  real_T c2_d_a[12];
  real_T c2_b_m;
  int32_T c2_i1154;
  real_T c2_d_b[3];
  int32_T c2_i1155;
  real_T c2_d_y[4];
  int32_T c2_i1156;
  int32_T c2_i1157;
  real_T c2_e_a;
  real_T c2_e_y;
  int32_T c2_i1158;
  real_T c2_e_b;
  int32_T c2_i1159;
  int32_T c2_i1160;
  sf_debug_symbol_scope_push_eml(0U, 12U, 12U, c2_g_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_T, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_n, 1U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_m, 2U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_ells, 3U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 4U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 5U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_z, 6U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Ps, 7U, c2_e_sf_marshallOut,
    c2_i_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Fxs, 8U, c2_c_sf_marshallOut,
    c2_s_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Fus, 9U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_switches, 10U, c2_v_sf_marshallOut,
    c2_p_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_y, 11U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  c2_T = 10.0;
  c2_n = 3.0;
  c2_m = 1.0;
  c2_ells = 4.0;
  CV_EML_FCN(0, 11);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 865);
  if (CV_EML_IF(0, 1, 57, c2_switches[2] == 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 866);
    for (c2_i1141 = 0; c2_i1141 < 1600; c2_i1141++) {
      c2_a[c2_i1141] = c2_Ps[c2_i1141];
    }

    for (c2_i1142 = 0; c2_i1142 < 40; c2_i1142++) {
      c2_b[c2_i1142] = c2_z[c2_i1142];
    }

    c2_j_eml_scalar_eg(chartInstance);
    c2_j_eml_scalar_eg(chartInstance);
    for (c2_i1143 = 0; c2_i1143 < 40; c2_i1143++) {
      c2_y[c2_i1143] = 0.0;
    }

    for (c2_i1144 = 0; c2_i1144 < 40; c2_i1144++) {
      c2_y[c2_i1144] = 0.0;
    }

    for (c2_i1145 = 0; c2_i1145 < 1600; c2_i1145++) {
      c2_dv70[c2_i1145] = c2_a[c2_i1145];
    }

    for (c2_i1146 = 0; c2_i1146 < 40; c2_i1146++) {
      c2_dv71[c2_i1146] = c2_b[c2_i1146];
    }

    for (c2_i1147 = 0; c2_i1147 < 1600; c2_i1147++) {
      c2_dv72[c2_i1147] = c2_dv70[c2_i1147];
    }

    for (c2_i1148 = 0; c2_i1148 < 40; c2_i1148++) {
      c2_dv73[c2_i1148] = c2_dv71[c2_i1148];
    }

    c2_r_eml_xgemm(chartInstance, c2_dv72, c2_dv73, c2_y);
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 868);
    for (c2_i1149 = 0; c2_i1149 < 40; c2_i1149++) {
      c2_y[c2_i1149] = 0.0;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 870);
    for (c2_i1150 = 0; c2_i1150 < 4; c2_i1150++) {
      c2_b_a[c2_i1150] = c2_Fus[c2_i1150];
    }

    c2_b_b = c2_z[0];
    for (c2_i1151 = 0; c2_i1151 < 4; c2_i1151++) {
      c2_b_a[c2_i1151] *= c2_b_b;
    }

    for (c2_i1152 = 0; c2_i1152 < 4; c2_i1152++) {
      c2_y[c2_i1152] = c2_b_a[c2_i1152];
    }

    c2_ii = 0;
    while (c2_ii < 9) {
      c2_b_ii = 2.0 + (real_T)c2_ii;
      CV_EML_FOR(0, 1, 15, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 872);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_c_b = c2_b_ii - 1.0;
      c2_b_y = 4.0 * c2_c_b;
      c2_c_a = c2_b_ii - 2.0;
      c2_c_y = c2_c_a * 4.0;
      for (c2_i1153 = 0; c2_i1153 < 12; c2_i1153++) {
        c2_d_a[c2_i1153] = c2_Fxs[c2_i1153];
      }

      c2_b_m = c2_m + c2_c_y;
      for (c2_i1154 = 0; c2_i1154 < 3; c2_i1154++) {
        c2_d_b[c2_i1154] = c2_z[_SFD_EML_ARRAY_BOUNDS_CHECK("z", (int32_T)
          _SFD_INTEGER_CHECK("m+(ii-2)*(n+m)+(1:n)", c2_b_m + (1.0 + (real_T)
          c2_i1154)), 1, 40, 1, 0) - 1];
      }

      c2_c_eml_scalar_eg(chartInstance);
      c2_c_eml_scalar_eg(chartInstance);
      for (c2_i1155 = 0; c2_i1155 < 4; c2_i1155++) {
        c2_d_y[c2_i1155] = 0.0;
        c2_i1156 = 0;
        for (c2_i1157 = 0; c2_i1157 < 3; c2_i1157++) {
          c2_d_y[c2_i1155] += c2_d_a[c2_i1156 + c2_i1155] * c2_d_b[c2_i1157];
          c2_i1156 += 4;
        }
      }

      c2_e_a = c2_b_ii - 1.0;
      c2_e_y = c2_e_a * 4.0;
      for (c2_i1158 = 0; c2_i1158 < 4; c2_i1158++) {
        c2_b_a[c2_i1158] = c2_Fus[c2_i1158];
      }

      c2_e_b = c2_z[_SFD_EML_ARRAY_BOUNDS_CHECK("z", (int32_T)_SFD_INTEGER_CHECK
        ("(ii-1)*(n+m)+(1:m)", c2_e_y + 1.0), 1, 40, 1, 0) - 1];
      for (c2_i1159 = 0; c2_i1159 < 4; c2_i1159++) {
        c2_b_a[c2_i1159] *= c2_e_b;
      }

      for (c2_i1160 = 0; c2_i1160 < 4; c2_i1160++) {
        c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("y", (int32_T)_SFD_INTEGER_CHECK(
          "ells*(ii-1)+(1:ells)", c2_b_y + (1.0 + (real_T)c2_i1160)), 1, 40, 1,
          0) - 1] = c2_d_y[c2_i1160] + c2_b_a[c2_i1160];
      }

      c2_ii++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 15, 0);
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -872);
  sf_debug_symbol_scope_pop();
}

static real_T c2_myexp(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
  real_T c2_u, boolean_T c2_flagNoPade)
{
  real_T c2_y;
  uint32_T c2_debug_family_var_map[7];
  real_T c2_di;
  real_T c2_ds;
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  real_T c2_x;
  real_T c2_b_x;
  int32_T c2_ii;
  real_T c2_b_ii;
  real_T c2_B;
  real_T c2_b_y;
  real_T c2_c_y;
  real_T c2_d_y;
  real_T c2_a;
  real_T c2_b;
  real_T c2_e_y;
  real_T c2_f_y;
  real_T c2_g_y;
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c2_h_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c2_di, 0U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_ds, 1U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 2U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 3U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_u, 4U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_flagNoPade, 5U,
    c2_w_sf_marshallOut, c2_q_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_y, 6U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  CV_EML_FCN(0, 7);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 797);
  if (CV_EML_IF(0, 1, 52, c2_flagNoPade)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 798);
    c2_x = c2_u;
    c2_y = c2_x;
    c2_b_x = c2_y;
    c2_y = c2_b_x;
    c2_y = muDoubleScalarExp(c2_y);
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 801);
    c2_di = 1.0;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 802);
    c2_ds = c2_di;
    c2_ii = 0;
    while (c2_ii < 3) {
      c2_b_ii = 1.0 + (real_T)c2_ii;
      CV_EML_FOR(0, 1, 12, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 804);
      c2_B = c2_b_ii;
      c2_b_y = c2_B;
      c2_c_y = c2_b_y;
      c2_d_y = -1.0 / c2_c_y;
      c2_a = c2_d_y;
      c2_b = c2_di;
      c2_e_y = c2_a * c2_b;
      c2_di = c2_e_y * c2_u;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 805);
      c2_ds += c2_di;
      c2_ii++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 12, 0);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 807);
    c2_f_y = c2_ds;
    c2_g_y = c2_f_y;
    c2_y = 1.0 / c2_g_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -807);
  sf_debug_symbol_scope_pop();
  return c2_y;
}

static void c2_multByPsT(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_ds[40], real_T c2_PsT[1600], real_T c2_FxsT[12],
  real_T c2_FusT[4], real_T c2_switches[9], real_T c2_y[40])
{
  uint32_T c2_debug_family_var_map[12];
  real_T c2_T;
  real_T c2_n;
  real_T c2_m;
  real_T c2_ells;
  real_T c2_nargin = 9.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i1161;
  real_T c2_a[1600];
  int32_T c2_i1162;
  real_T c2_b[40];
  int32_T c2_i1163;
  int32_T c2_i1164;
  int32_T c2_i1165;
  real_T c2_dv74[1600];
  int32_T c2_i1166;
  real_T c2_dv75[40];
  int32_T c2_i1167;
  real_T c2_dv76[1600];
  int32_T c2_i1168;
  real_T c2_dv77[40];
  int32_T c2_i1169;
  int32_T c2_i1170;
  real_T c2_b_a[4];
  int32_T c2_i1171;
  real_T c2_b_b[4];
  real_T c2_b_y;
  int32_T c2_k;
  int32_T c2_b_k;
  int32_T c2_ii;
  real_T c2_b_ii;
  real_T c2_c_a;
  real_T c2_c_y;
  real_T c2_c_b;
  real_T c2_d_y;
  int32_T c2_i1172;
  real_T c2_d_a[12];
  int32_T c2_i1173;
  int32_T c2_i1174;
  real_T c2_e_y[3];
  int32_T c2_i1175;
  int32_T c2_i1176;
  int32_T c2_i1177;
  real_T c2_e_a;
  real_T c2_f_y;
  real_T c2_d_b;
  real_T c2_g_y;
  int32_T c2_i1178;
  int32_T c2_i1179;
  real_T c2_h_y;
  int32_T c2_c_k;
  int32_T c2_d_k;
  sf_debug_symbol_scope_push_eml(0U, 12U, 12U, c2_j_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_T, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_n, 1U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_m, 2U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_ells, 3U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 4U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 5U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_ds, 6U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_PsT, 7U, c2_e_sf_marshallOut,
    c2_i_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_FxsT, 8U, c2_t_sf_marshallOut,
    c2_n_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_FusT, 9U, c2_s_sf_marshallOut,
    c2_m_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_switches, 10U, c2_v_sf_marshallOut,
    c2_p_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_y, 11U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  c2_T = 10.0;
  c2_n = 3.0;
  c2_m = 1.0;
  c2_ells = 4.0;
  CV_EML_FCN(0, 12);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 884);
  if (CV_EML_IF(0, 1, 58, c2_switches[3] == 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 885);
    for (c2_i1161 = 0; c2_i1161 < 1600; c2_i1161++) {
      c2_a[c2_i1161] = c2_PsT[c2_i1161];
    }

    for (c2_i1162 = 0; c2_i1162 < 40; c2_i1162++) {
      c2_b[c2_i1162] = c2_ds[c2_i1162];
    }

    c2_j_eml_scalar_eg(chartInstance);
    c2_j_eml_scalar_eg(chartInstance);
    for (c2_i1163 = 0; c2_i1163 < 40; c2_i1163++) {
      c2_y[c2_i1163] = 0.0;
    }

    for (c2_i1164 = 0; c2_i1164 < 40; c2_i1164++) {
      c2_y[c2_i1164] = 0.0;
    }

    for (c2_i1165 = 0; c2_i1165 < 1600; c2_i1165++) {
      c2_dv74[c2_i1165] = c2_a[c2_i1165];
    }

    for (c2_i1166 = 0; c2_i1166 < 40; c2_i1166++) {
      c2_dv75[c2_i1166] = c2_b[c2_i1166];
    }

    for (c2_i1167 = 0; c2_i1167 < 1600; c2_i1167++) {
      c2_dv76[c2_i1167] = c2_dv74[c2_i1167];
    }

    for (c2_i1168 = 0; c2_i1168 < 40; c2_i1168++) {
      c2_dv77[c2_i1168] = c2_dv75[c2_i1168];
    }

    c2_r_eml_xgemm(chartInstance, c2_dv76, c2_dv77, c2_y);
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 887);
    for (c2_i1169 = 0; c2_i1169 < 40; c2_i1169++) {
      c2_y[c2_i1169] = 0.0;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 889);
    for (c2_i1170 = 0; c2_i1170 < 4; c2_i1170++) {
      c2_b_a[c2_i1170] = c2_FusT[c2_i1170];
    }

    for (c2_i1171 = 0; c2_i1171 < 4; c2_i1171++) {
      c2_b_b[c2_i1171] = c2_ds[c2_i1171];
    }

    c2_k_eml_scalar_eg(chartInstance);
    c2_k_eml_scalar_eg(chartInstance);
    c2_b_y = 0.0;
    c2_c_eml_int_forloop_overflow_check(chartInstance);
    for (c2_k = 1; c2_k < 5; c2_k++) {
      c2_b_k = c2_k;
      c2_b_y += c2_b_a[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 4, 1, 0) - 1] *
        c2_b_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_b_k), 1, 4, 1, 0) - 1];
    }

    c2_y[0] = c2_b_y;
    c2_ii = 0;
    while (c2_ii < 9) {
      c2_b_ii = 2.0 + (real_T)c2_ii;
      CV_EML_FOR(0, 1, 16, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 891);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_c_a = c2_b_ii - 2.0;
      c2_c_y = c2_c_a * 4.0;
      c2_c_b = c2_b_ii - 1.0;
      c2_d_y = 4.0 * c2_c_b;
      for (c2_i1172 = 0; c2_i1172 < 12; c2_i1172++) {
        c2_d_a[c2_i1172] = c2_FxsT[c2_i1172];
      }

      for (c2_i1173 = 0; c2_i1173 < 4; c2_i1173++) {
        c2_b_b[c2_i1173] = c2_ds[_SFD_EML_ARRAY_BOUNDS_CHECK("ds", (int32_T)
          _SFD_INTEGER_CHECK("ells*(ii-1)+(1:ells)", c2_d_y + (1.0 + (real_T)
          c2_i1173)), 1, 40, 1, 0) - 1];
      }

      c2_l_eml_scalar_eg(chartInstance);
      c2_l_eml_scalar_eg(chartInstance);
      for (c2_i1174 = 0; c2_i1174 < 3; c2_i1174++) {
        c2_e_y[c2_i1174] = 0.0;
        c2_i1175 = 0;
        for (c2_i1176 = 0; c2_i1176 < 4; c2_i1176++) {
          c2_e_y[c2_i1174] += c2_d_a[c2_i1175 + c2_i1174] * c2_b_b[c2_i1176];
          c2_i1175 += 3;
        }
      }

      for (c2_i1177 = 0; c2_i1177 < 3; c2_i1177++) {
        c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("y", (int32_T)_SFD_INTEGER_CHECK(
          "m+(1:n)+(ii-2)*(n+m)", (c2_m + (1.0 + (real_T)c2_i1177)) + c2_c_y), 1,
          40, 1, 0) - 1] = c2_e_y[c2_i1177];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 892);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_e_a = c2_b_ii - 2.0;
      c2_f_y = c2_e_a * 4.0;
      c2_d_b = c2_b_ii - 1.0;
      c2_g_y = 4.0 * c2_d_b;
      for (c2_i1178 = 0; c2_i1178 < 4; c2_i1178++) {
        c2_b_a[c2_i1178] = c2_FusT[c2_i1178];
      }

      for (c2_i1179 = 0; c2_i1179 < 4; c2_i1179++) {
        c2_b_b[c2_i1179] = c2_ds[_SFD_EML_ARRAY_BOUNDS_CHECK("ds", (int32_T)
          _SFD_INTEGER_CHECK("ells*(ii-1)+(1:ells)", c2_g_y + (1.0 + (real_T)
          c2_i1179)), 1, 40, 1, 0) - 1];
      }

      c2_k_eml_scalar_eg(chartInstance);
      c2_k_eml_scalar_eg(chartInstance);
      c2_h_y = 0.0;
      c2_c_eml_int_forloop_overflow_check(chartInstance);
      for (c2_c_k = 1; c2_c_k < 5; c2_c_k++) {
        c2_d_k = c2_c_k;
        c2_h_y += c2_b_a[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_d_k), 1, 4, 1, 0) - 1] *
          c2_b_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_d_k), 1, 4, 1, 0) - 1];
      }

      c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("y", (int32_T)_SFD_INTEGER_CHECK(
        "m+n+(1:m)+(ii-2)*(n+m)", ((c2_m + c2_n) + 1.0) + c2_f_y), 1, 40, 1, 0)
        - 1] = c2_h_y;
      c2_ii++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 16, 0);
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -892);
  sf_debug_symbol_scope_pop();
}

static void c2_k_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_c_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
}

static void c2_l_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static real_T c2_b_norm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x[40])
{
  real_T c2_y;
  real_T c2_scale;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_absxk;
  real_T c2_t;
  c2_y = 0.0;
  c2_eml_realmin(chartInstance);
  c2_scale = 2.2250738585072014E-308;
  c2_d_eml_int_forloop_overflow_check(chartInstance);
  for (c2_k = 1; c2_k < 41; c2_k++) {
    c2_b_k = c2_k;
    c2_b_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_b_k), 1, 40, 1, 0) - 1];
    c2_c_x = c2_b_x;
    c2_absxk = muDoubleScalarAbs(c2_c_x);
    if (c2_absxk > c2_scale) {
      c2_t = c2_scale / c2_absxk;
      c2_y = 1.0 + c2_y * c2_t * c2_t;
      c2_scale = c2_absxk;
    } else {
      c2_t = c2_absxk / c2_scale;
      c2_y += c2_t * c2_t;
    }
  }

  return c2_scale * muDoubleScalarSqrt(c2_y);
}

static void c2_d_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
}

static real_T c2_c_norm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x[2])
{
  real_T c2_y;
  real_T c2_scale;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_absxk;
  real_T c2_t;
  c2_y = 0.0;
  c2_eml_realmin(chartInstance);
  c2_scale = 2.2250738585072014E-308;
  c2_e_eml_int_forloop_overflow_check(chartInstance);
  for (c2_k = 1; c2_k < 3; c2_k++) {
    c2_b_k = c2_k;
    c2_b_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_b_k), 1, 2, 1, 0) - 1];
    c2_c_x = c2_b_x;
    c2_absxk = muDoubleScalarAbs(c2_c_x);
    if (c2_absxk > c2_scale) {
      c2_t = c2_scale / c2_absxk;
      c2_y = 1.0 + c2_y * c2_t * c2_t;
      c2_scale = c2_absxk;
    } else {
      c2_t = c2_absxk / c2_scale;
      c2_y += c2_t * c2_t;
    }
  }

  return c2_scale * muDoubleScalarSqrt(c2_y);
}

static void c2_e_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
}

static real_T c2_d_norm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x[44])
{
  real_T c2_y;
  real_T c2_scale;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_absxk;
  real_T c2_t;
  c2_y = 0.0;
  c2_eml_realmin(chartInstance);
  c2_scale = 2.2250738585072014E-308;
  c2_f_eml_int_forloop_overflow_check(chartInstance);
  for (c2_k = 1; c2_k < 45; c2_k++) {
    c2_b_k = c2_k;
    c2_b_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_b_k), 1, 44, 1, 0) - 1];
    c2_c_x = c2_b_x;
    c2_absxk = muDoubleScalarAbs(c2_c_x);
    if (c2_absxk > c2_scale) {
      c2_t = c2_scale / c2_absxk;
      c2_y = 1.0 + c2_y * c2_t * c2_t;
      c2_scale = c2_absxk;
    } else {
      c2_t = c2_absxk / c2_scale;
      c2_y += c2_t * c2_t;
    }
  }

  return c2_scale * muDoubleScalarSqrt(c2_y);
}

static void c2_f_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
}

static void c2_b_rdivide(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x[40], real_T c2_y[40], real_T c2_z[40])
{
  int32_T c2_i1180;
  for (c2_i1180 = 0; c2_i1180 < 40; c2_i1180++) {
    c2_z[c2_i1180] = c2_x[c2_i1180] / c2_y[c2_i1180];
  }
}

static void c2_c_rdivide(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x, real_T c2_y[40], real_T c2_z[40])
{
  real_T c2_b_x;
  int32_T c2_i1181;
  c2_b_x = c2_x;
  for (c2_i1181 = 0; c2_i1181 < 40; c2_i1181++) {
    c2_z[c2_i1181] = c2_b_x / c2_y[c2_i1181];
  }
}

static void c2_b_diag(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_v[40], real_T c2_d[1600])
{
  int32_T c2_i1182;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_a;
  int32_T c2_c;
  for (c2_i1182 = 0; c2_i1182 < 1600; c2_i1182++) {
    c2_d[c2_i1182] = 0.0;
  }

  c2_d_eml_int_forloop_overflow_check(chartInstance);
  for (c2_j = 1; c2_j < 41; c2_j++) {
    c2_b_j = c2_j;
    c2_a = c2_b_j;
    c2_c = c2_a;
    c2_d[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_j), 1, 40, 1, 0) + 40 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_c), 1, 40, 2, 0) - 1)) -
      1] = c2_v[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_b_j), 1, 40, 1, 0) - 1];
  }
}

static void c2_c_diag(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_v[4], real_T c2_d[16])
{
  int32_T c2_i1183;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_a;
  int32_T c2_c;
  for (c2_i1183 = 0; c2_i1183 < 16; c2_i1183++) {
    c2_d[c2_i1183] = 0.0;
  }

  c2_c_eml_int_forloop_overflow_check(chartInstance);
  for (c2_j = 1; c2_j < 5; c2_j++) {
    c2_b_j = c2_j;
    c2_a = c2_b_j;
    c2_c = c2_a;
    c2_d[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_j), 1, 4, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("",
             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_c), 1, 4, 2, 0) - 1) <<
           2)) - 1] = c2_v[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 4, 1, 0) - 1];
  }
}

static void c2_m_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static real_T c2_mySymPDinv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_M)
{
  real_T c2_Minv;
  uint32_T c2_debug_family_var_map[6];
  real_T c2_cholM;
  real_T c2_tmp;
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  real_T c2_A;
  real_T c2_b_A;
  real_T c2_x;
  real_T c2_c_A;
  real_T c2_b_x;
  real_T c2_d_A;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_y;
  real_T c2_e_A;
  real_T c2_B;
  real_T c2_f_A;
  real_T c2_e_x;
  real_T c2_g_A;
  real_T c2_f_x;
  real_T c2_h_A;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_b_y;
  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c2_k_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c2_cholM, 0U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_tmp, 1U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 2U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 3U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_M, 4U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_Minv, 5U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  CV_EML_FCN(0, 5);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 751);
  c2_cholM = c2_M;
  c2_d_chol(chartInstance, &c2_cholM);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 752);
  c2_A = c2_cholM;
  c2_n_eml_scalar_eg(chartInstance);
  c2_tmp = 1.0;
  c2_b_A = c2_A;
  c2_x = c2_tmp;
  c2_tmp = c2_x;
  c2_c_A = c2_b_A;
  c2_b_x = c2_tmp;
  c2_tmp = c2_b_x;
  c2_below_threshold(chartInstance);
  c2_d_A = c2_c_A;
  c2_c_x = c2_tmp;
  c2_tmp = c2_c_x;
  c2_d_x = c2_tmp;
  c2_y = c2_d_A;
  c2_tmp = c2_d_x / c2_y;
  if (c2_is_singular_triangular_matrix(chartInstance, c2_A)) {
    c2_eml_warning(chartInstance);
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 753);
  c2_e_A = c2_cholM;
  c2_B = c2_tmp;
  c2_n_eml_scalar_eg(chartInstance);
  c2_Minv = c2_B;
  c2_f_A = c2_e_A;
  c2_e_x = c2_Minv;
  c2_Minv = c2_e_x;
  c2_g_A = c2_f_A;
  c2_f_x = c2_Minv;
  c2_Minv = c2_f_x;
  c2_below_threshold(chartInstance);
  c2_h_A = c2_g_A;
  c2_g_x = c2_Minv;
  c2_Minv = c2_g_x;
  c2_h_x = c2_Minv;
  c2_b_y = c2_h_A;
  c2_Minv = c2_h_x / c2_b_y;
  if (c2_is_singular_triangular_matrix(chartInstance, c2_e_A)) {
    c2_eml_warning(chartInstance);
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -753);
  sf_debug_symbol_scope_pop();
  return c2_Minv;
}

static real_T c2_chol(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_A)
{
  real_T c2_b_A;
  c2_b_A = c2_A;
  c2_d_chol(chartInstance, &c2_b_A);
  return c2_b_A;
}

static void c2_eml_error(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
  int32_T c2_i1184;
  static char_T c2_varargin_1[48] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'c', 'h', 'o', 'l', '_', 'm', 'a', 't', 'r', 'i',
    'x', 'M', 'u', 's', 't', 'B', 'e', 'P', 'o', 's', 'D', 'e', 'f', 'W', 'i',
    't', 'h', 'R', 'e', 'a', 'l', 'D', 'i', 'a', 'g' };

  char_T c2_u[48];
  const mxArray *c2_y = NULL;
  for (c2_i1184 = 0; c2_i1184 < 48; c2_i1184++) {
    c2_u[c2_i1184] = c2_varargin_1[c2_i1184];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 48), FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c2_y));
}

static void c2_n_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_b_eml_error(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
  int32_T c2_i1185;
  static char_T c2_varargin_1[19] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'p', 'o', 's', 'd', 'e', 'f' };

  char_T c2_u[19];
  const mxArray *c2_y = NULL;
  for (c2_i1185 = 0; c2_i1185 < 19; c2_i1185++) {
    c2_u[c2_i1185] = c2_varargin_1[c2_i1185];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 19), FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c2_y));
}

static void c2_g_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, int32_T c2_b)
{
  int32_T c2_b_b;
  boolean_T c2_overflow;
  boolean_T c2_safe;
  int32_T c2_i1186;
  static char_T c2_cv0[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  char_T c2_u[34];
  const mxArray *c2_y = NULL;
  int32_T c2_i1187;
  static char_T c2_cv1[5] = { 'i', 'n', 't', '3', '2' };

  char_T c2_b_u[5];
  const mxArray *c2_b_y = NULL;
  c2_b_b = c2_b;
  if (2 > c2_b_b) {
    c2_overflow = FALSE;
  } else {
    c2_overflow = (c2_b_b > 2147483646);
  }

  c2_safe = !c2_overflow;
  if (c2_safe) {
  } else {
    for (c2_i1186 = 0; c2_i1186 < 34; c2_i1186++) {
      c2_u[c2_i1186] = c2_cv0[c2_i1186];
    }

    c2_y = NULL;
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 34),
                  FALSE);
    for (c2_i1187 = 0; c2_i1187 < 5; c2_i1187++) {
      c2_b_u[c2_i1187] = c2_cv1[c2_i1187];
    }

    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 5),
                  FALSE);
    sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
      14, c2_y, 14, c2_b_y));
  }
}

static void c2_h_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, int32_T c2_b)
{
  int32_T c2_b_b;
  boolean_T c2_overflow;
  boolean_T c2_safe;
  int32_T c2_i1188;
  static char_T c2_cv2[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  char_T c2_u[34];
  const mxArray *c2_y = NULL;
  int32_T c2_i1189;
  static char_T c2_cv3[5] = { 'i', 'n', 't', '3', '2' };

  char_T c2_b_u[5];
  const mxArray *c2_b_y = NULL;
  c2_b_b = c2_b;
  if (1 > c2_b_b) {
    c2_overflow = FALSE;
  } else {
    c2_overflow = (c2_b_b > 2147483646);
  }

  c2_safe = !c2_overflow;
  if (c2_safe) {
  } else {
    for (c2_i1188 = 0; c2_i1188 < 34; c2_i1188++) {
      c2_u[c2_i1188] = c2_cv2[c2_i1188];
    }

    c2_y = NULL;
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 34),
                  FALSE);
    for (c2_i1189 = 0; c2_i1189 < 5; c2_i1189++) {
      c2_b_u[c2_i1189] = c2_cv3[c2_i1189];
    }

    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 5),
                  FALSE);
    sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
      14, c2_y, 14, c2_b_y));
  }
}

static void c2_isVariableSizing(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_below_threshold(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static boolean_T c2_is_singular_triangular_matrix
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, real_T c2_A)
{
  boolean_T c2_p;
  real_T c2_x;
  real_T c2_b_x;
  boolean_T c2_b;
  boolean_T c2_b1;
  real_T c2_c_x;
  boolean_T c2_b_b;
  boolean_T c2_b2;
  boolean_T c2_c_b;
  boolean_T guard1 = FALSE;
  guard1 = FALSE;
  if (c2_A == 0.0) {
    guard1 = TRUE;
  } else {
    c2_x = c2_A;
    c2_b_x = c2_x;
    c2_b = muDoubleScalarIsInf(c2_b_x);
    c2_b1 = !c2_b;
    c2_c_x = c2_x;
    c2_b_b = muDoubleScalarIsNaN(c2_c_x);
    c2_b2 = !c2_b_b;
    c2_c_b = (c2_b1 && c2_b2);
    if (!c2_c_b) {
      guard1 = TRUE;
    } else {
      c2_p = FALSE;
    }
  }

  if (guard1 == TRUE) {
    c2_p = TRUE;
  }

  return c2_p;
}

static void c2_eml_warning(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
  int32_T c2_i1190;
  static char_T c2_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c2_u[27];
  const mxArray *c2_y = NULL;
  for (c2_i1190 = 0; c2_i1190 < 27; c2_i1190++) {
    c2_u[c2_i1190] = c2_varargin_1[c2_i1190];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 27), FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
    14, c2_y));
}

static void c2_o_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_b_mySymPDinv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_M[16], real_T c2_Minv[16])
{
  uint32_T c2_debug_family_var_map[6];
  real_T c2_cholM[16];
  real_T c2_tmp[16];
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i1191;
  real_T c2_A[16];
  int32_T c2_i1192;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_i1193;
  int32_T c2_info;
  int32_T c2_b_info;
  int32_T c2_c_info;
  int32_T c2_i1194;
  int32_T c2_d_info;
  int32_T c2_jmax;
  int32_T c2_a;
  int32_T c2_c_j;
  int32_T c2_b_a;
  int32_T c2_i1195;
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_i1196;
  real_T c2_b_cholM[16];
  int32_T c2_i1197;
  static real_T c2_dv78[16] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  real_T c2_dv79[16];
  real_T c2_dv80[16];
  int32_T c2_i1198;
  int32_T c2_i1199;
  int32_T c2_i1200;
  int32_T c2_i1201;
  int32_T c2_i1202;
  real_T c2_c_cholM[16];
  int32_T c2_i1203;
  real_T c2_b_tmp[16];
  real_T c2_dv81[16];
  int32_T c2_i1204;
  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c2_l_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(c2_cholM, 0U, c2_o_sf_marshallOut,
    c2_h_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_tmp, 1U, c2_o_sf_marshallOut,
    c2_h_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 2U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 3U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_M, 4U, c2_o_sf_marshallOut,
    c2_h_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Minv, 5U, c2_o_sf_marshallOut,
    c2_h_sf_marshallIn);
  CV_EML_FCN(0, 5);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 751);
  for (c2_i1191 = 0; c2_i1191 < 16; c2_i1191++) {
    c2_A[c2_i1191] = c2_M[c2_i1191];
  }

  for (c2_i1192 = 0; c2_i1192 < 16; c2_i1192++) {
    c2_cholM[c2_i1192] = c2_A[c2_i1192];
  }

  c2_c_eml_int_forloop_overflow_check(chartInstance);
  for (c2_j = 1; c2_j < 5; c2_j++) {
    c2_b_j = c2_j;
  }

  for (c2_i1193 = 0; c2_i1193 < 16; c2_i1193++) {
    c2_A[c2_i1193] = c2_cholM[c2_i1193];
  }

  c2_info = c2_d_eml_matlab_zpotrf(chartInstance, c2_A);
  c2_b_info = c2_info;
  c2_c_info = c2_b_info;
  for (c2_i1194 = 0; c2_i1194 < 16; c2_i1194++) {
    c2_cholM[c2_i1194] = c2_A[c2_i1194];
  }

  c2_d_info = c2_c_info;
  if (c2_d_info == 0) {
    c2_jmax = 4;
  } else {
    c2_b_eml_error(chartInstance);
    c2_a = c2_d_info - 1;
    c2_jmax = c2_a;
  }

  c2_g_eml_int_forloop_overflow_check(chartInstance, c2_jmax);
  for (c2_c_j = 2; c2_c_j <= c2_jmax; c2_c_j++) {
    c2_b_j = c2_c_j;
    c2_b_a = c2_b_j - 1;
    c2_i1195 = c2_b_a;
    c2_h_eml_int_forloop_overflow_check(chartInstance, c2_i1195);
    for (c2_i = 1; c2_i <= c2_i1195; c2_i++) {
      c2_b_i = c2_i;
      c2_cholM[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_b_i), 1, 4, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK(
        "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 4, 2, 0) - 1) <<
                 2)) - 1] = 0.0;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 752);
  for (c2_i1196 = 0; c2_i1196 < 16; c2_i1196++) {
    c2_b_cholM[c2_i1196] = c2_cholM[c2_i1196];
  }

  for (c2_i1197 = 0; c2_i1197 < 16; c2_i1197++) {
    c2_dv79[c2_i1197] = c2_dv78[c2_i1197];
  }

  c2_linsolve(chartInstance, c2_b_cholM, c2_dv79, c2_dv80);
  for (c2_i1198 = 0; c2_i1198 < 16; c2_i1198++) {
    c2_tmp[c2_i1198] = c2_dv80[c2_i1198];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 753);
  c2_i1199 = 0;
  for (c2_i1200 = 0; c2_i1200 < 4; c2_i1200++) {
    c2_i1201 = 0;
    for (c2_i1202 = 0; c2_i1202 < 4; c2_i1202++) {
      c2_c_cholM[c2_i1202 + c2_i1199] = c2_cholM[c2_i1201 + c2_i1200];
      c2_i1201 += 4;
    }

    c2_i1199 += 4;
  }

  for (c2_i1203 = 0; c2_i1203 < 16; c2_i1203++) {
    c2_b_tmp[c2_i1203] = c2_tmp[c2_i1203];
  }

  c2_b_linsolve(chartInstance, c2_c_cholM, c2_b_tmp, c2_dv81);
  for (c2_i1204 = 0; c2_i1204 < 16; c2_i1204++) {
    c2_Minv[c2_i1204] = c2_dv81[c2_i1204];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -753);
  sf_debug_symbol_scope_pop();
}

static void c2_eml_matlab_zpotrf(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[16], real_T c2_b_A[16], int32_T *c2_info)
{
  int32_T c2_i1205;
  for (c2_i1205 = 0; c2_i1205 < 16; c2_i1205++) {
    c2_b_A[c2_i1205] = c2_A[c2_i1205];
  }

  *c2_info = c2_d_eml_matlab_zpotrf(chartInstance, c2_b_A);
}

static void c2_eml_xgemv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_ia0, int32_T c2_ix0,
  real_T c2_y[16], int32_T c2_iy0, real_T c2_b_y[16])
{
  int32_T c2_i1206;
  for (c2_i1206 = 0; c2_i1206 < 16; c2_i1206++) {
    c2_b_y[c2_i1206] = c2_y[c2_i1206];
  }

  c2_d_eml_xgemv(chartInstance, c2_m, c2_n, c2_ia0, c2_ix0, c2_b_y, c2_iy0);
}

static void c2_i_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, int32_T c2_a,
   int32_T c2_b)
{
  int32_T c2_b_a;
  int32_T c2_b_b;
  boolean_T c2_overflow;
  boolean_T c2_safe;
  int32_T c2_i1207;
  static char_T c2_cv4[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  char_T c2_u[34];
  const mxArray *c2_y = NULL;
  int32_T c2_i1208;
  static char_T c2_cv5[5] = { 'i', 'n', 't', '3', '2' };

  char_T c2_b_u[5];
  const mxArray *c2_b_y = NULL;
  c2_b_a = c2_a;
  c2_b_b = c2_b;
  if (c2_b_a > c2_b_b) {
    c2_overflow = FALSE;
  } else {
    c2_overflow = (c2_b_b > 2147483646);
  }

  c2_safe = !c2_overflow;
  if (c2_safe) {
  } else {
    for (c2_i1207 = 0; c2_i1207 < 34; c2_i1207++) {
      c2_u[c2_i1207] = c2_cv4[c2_i1207];
    }

    c2_y = NULL;
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 34),
                  FALSE);
    for (c2_i1208 = 0; c2_i1208 < 5; c2_i1208++) {
      c2_b_u[c2_i1208] = c2_cv5[c2_i1208];
    }

    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 5),
                  FALSE);
    sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
      14, c2_y, 14, c2_b_y));
  }
}

static void c2_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[16], real_T c2_B[16], real_T c2_C[16])
{
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_c_j;
  int32_T c2_d_j;
  int32_T c2_a;
  int32_T c2_c;
  int32_T c2_b;
  int32_T c2_b_c;
  int32_T c2_b_b;
  int32_T c2_jBcol;
  int32_T c2_k;
  int32_T c2_b_k;
  int32_T c2_b_a;
  int32_T c2_c_c;
  int32_T c2_c_b;
  int32_T c2_d_c;
  int32_T c2_d_b;
  int32_T c2_kAcol;
  int32_T c2_c_a;
  int32_T c2_e_b;
  int32_T c2_e_c;
  int32_T c2_d_a;
  int32_T c2_f_b;
  int32_T c2_f_c;
  int32_T c2_e_a;
  int32_T c2_g_b;
  int32_T c2_g_c;
  int32_T c2_f_a;
  int32_T c2_h_b;
  int32_T c2_h_c;
  real_T c2_x;
  real_T c2_y;
  real_T c2_z;
  int32_T c2_g_a;
  int32_T c2_i1209;
  int32_T c2_c_i;
  int32_T c2_d_i;
  int32_T c2_h_a;
  int32_T c2_i_b;
  int32_T c2_i_c;
  int32_T c2_i_a;
  int32_T c2_j_b;
  int32_T c2_j_c;
  int32_T c2_j_a;
  int32_T c2_k_b;
  int32_T c2_k_c;
  int32_T c2_k_a;
  int32_T c2_l_b;
  int32_T c2_l_c;
  int32_T c2_i1210;
  real_T c2_b_A[16];
  c2_o_eml_scalar_eg(chartInstance);
  c2_c_eml_int_forloop_overflow_check(chartInstance);
  for (c2_j = 1; c2_j < 5; c2_j++) {
    c2_b_j = c2_j;
    c2_c_eml_int_forloop_overflow_check(chartInstance);
    for (c2_i = 1; c2_i < 5; c2_i++) {
      c2_b_i = c2_i;
      c2_C[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_i), 1, 4, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("",
               (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 4, 2, 0) - 1)
             << 2)) - 1] = c2_B[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 4, 1, 0) +
        ((_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_b_j), 1, 4, 2, 0) - 1) << 2)) - 1];
    }
  }

  c2_b_below_threshold(chartInstance);
  c2_p_eml_scalar_eg(chartInstance);
  c2_c_eml_int_forloop_overflow_check(chartInstance);
  for (c2_c_j = 1; c2_c_j < 5; c2_c_j++) {
    c2_d_j = c2_c_j;
    c2_a = c2_d_j;
    c2_c = c2_a;
    c2_b = c2_c - 1;
    c2_b_c = c2_b << 2;
    c2_b_b = c2_b_c;
    c2_jBcol = c2_b_b;
    c2_c_eml_int_forloop_overflow_check(chartInstance);
    for (c2_k = 1; c2_k < 5; c2_k++) {
      c2_b_k = c2_k;
      c2_b_a = c2_b_k;
      c2_c_c = c2_b_a;
      c2_c_b = c2_c_c - 1;
      c2_d_c = c2_c_b << 2;
      c2_d_b = c2_d_c;
      c2_kAcol = c2_d_b;
      c2_c_a = c2_b_k;
      c2_e_b = c2_jBcol;
      c2_e_c = c2_c_a + c2_e_b;
      if (c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_e_c), 1, 16, 1, 0) - 1] != 0.0) {
        c2_d_a = c2_b_k;
        c2_f_b = c2_jBcol;
        c2_f_c = c2_d_a + c2_f_b;
        c2_e_a = c2_b_k;
        c2_g_b = c2_jBcol;
        c2_g_c = c2_e_a + c2_g_b;
        c2_f_a = c2_b_k;
        c2_h_b = c2_kAcol;
        c2_h_c = c2_f_a + c2_h_b;
        c2_x = c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_g_c), 1, 16, 1, 0) - 1];
        c2_y = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_h_c), 1, 16, 1, 0) - 1];
        c2_z = c2_x / c2_y;
        c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_f_c), 1, 16, 1, 0) - 1] = c2_z;
        c2_g_a = c2_b_k + 1;
        c2_i1209 = c2_g_a;
        c2_i_eml_int_forloop_overflow_check(chartInstance, c2_i1209, 4);
        for (c2_c_i = c2_i1209; c2_c_i < 5; c2_c_i++) {
          c2_d_i = c2_c_i;
          c2_h_a = c2_d_i;
          c2_i_b = c2_jBcol;
          c2_i_c = c2_h_a + c2_i_b;
          c2_i_a = c2_d_i;
          c2_j_b = c2_jBcol;
          c2_j_c = c2_i_a + c2_j_b;
          c2_j_a = c2_b_k;
          c2_k_b = c2_jBcol;
          c2_k_c = c2_j_a + c2_k_b;
          c2_k_a = c2_d_i;
          c2_l_b = c2_kAcol;
          c2_l_c = c2_k_a + c2_l_b;
          c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_i_c), 1, 16, 1, 0) - 1] =
            c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_j_c), 1, 16, 1, 0) - 1] -
            c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_k_c), 1, 16, 1, 0) - 1] *
            c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_l_c), 1, 16, 1, 0) - 1];
        }
      }
    }
  }

  for (c2_i1210 = 0; c2_i1210 < 16; c2_i1210++) {
    c2_b_A[c2_i1210] = c2_A[c2_i1210];
  }

  if (c2_b_is_singular_triangular_matrix(chartInstance, c2_b_A)) {
    c2_eml_warning(chartInstance);
  }
}

static void c2_b_below_threshold(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_p_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static boolean_T c2_b_is_singular_triangular_matrix
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, real_T c2_A[16])
{
  boolean_T c2_p;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_x;
  real_T c2_b_x;
  boolean_T c2_b;
  boolean_T c2_b3;
  real_T c2_c_x;
  boolean_T c2_b_b;
  boolean_T c2_b4;
  boolean_T c2_c_b;
  boolean_T guard1 = FALSE;
  int32_T exitg1;
  c2_c_eml_int_forloop_overflow_check(chartInstance);
  c2_k = 1;
  guard1 = FALSE;
  do {
    exitg1 = 0;
    if (c2_k < 5) {
      c2_b_k = c2_k;
      if (c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
             (real_T)c2_b_k), 1, 4, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 4, 2, 0) - 1) <<
            2)) - 1] == 0.0) {
        guard1 = TRUE;
        exitg1 = 1;
      } else {
        c2_x = c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_b_k), 1, 4, 1, 0) +
                     ((_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 4, 2, 0) - 1) << 2)) - 1];
        c2_b_x = c2_x;
        c2_b = muDoubleScalarIsInf(c2_b_x);
        c2_b3 = !c2_b;
        c2_c_x = c2_x;
        c2_b_b = muDoubleScalarIsNaN(c2_c_x);
        c2_b4 = !c2_b_b;
        c2_c_b = (c2_b3 && c2_b4);
        if (!c2_c_b) {
          guard1 = TRUE;
          exitg1 = 1;
        } else {
          c2_k++;
          guard1 = FALSE;
        }
      }
    } else {
      c2_p = FALSE;
      exitg1 = 1;
    }
  } while (exitg1 == 0U);

  if (guard1 == TRUE) {
    c2_p = TRUE;
  }

  return c2_p;
}

static void c2_b_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[16], real_T c2_B[16], real_T c2_C[16])
{
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_c_j;
  int32_T c2_d_j;
  int32_T c2_a;
  int32_T c2_c;
  int32_T c2_b;
  int32_T c2_b_c;
  int32_T c2_b_b;
  int32_T c2_jBcol;
  int32_T c2_k;
  int32_T c2_b_k;
  int32_T c2_b_a;
  int32_T c2_c_c;
  int32_T c2_c_b;
  int32_T c2_d_c;
  int32_T c2_d_b;
  int32_T c2_kAcol;
  int32_T c2_c_a;
  int32_T c2_e_b;
  int32_T c2_e_c;
  int32_T c2_d_a;
  int32_T c2_f_b;
  int32_T c2_f_c;
  int32_T c2_e_a;
  int32_T c2_g_b;
  int32_T c2_g_c;
  int32_T c2_f_a;
  int32_T c2_h_b;
  int32_T c2_h_c;
  real_T c2_x;
  real_T c2_y;
  real_T c2_z;
  int32_T c2_g_a;
  int32_T c2_i1211;
  int32_T c2_c_i;
  int32_T c2_d_i;
  int32_T c2_h_a;
  int32_T c2_i_b;
  int32_T c2_i_c;
  int32_T c2_i_a;
  int32_T c2_j_b;
  int32_T c2_j_c;
  int32_T c2_j_a;
  int32_T c2_k_b;
  int32_T c2_k_c;
  int32_T c2_k_a;
  int32_T c2_l_b;
  int32_T c2_l_c;
  int32_T c2_i1212;
  real_T c2_b_A[16];
  c2_o_eml_scalar_eg(chartInstance);
  c2_c_eml_int_forloop_overflow_check(chartInstance);
  for (c2_j = 1; c2_j < 5; c2_j++) {
    c2_b_j = c2_j;
    c2_c_eml_int_forloop_overflow_check(chartInstance);
    for (c2_i = 1; c2_i < 5; c2_i++) {
      c2_b_i = c2_i;
      c2_C[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_i), 1, 4, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("",
               (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 4, 2, 0) - 1)
             << 2)) - 1] = c2_B[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 4, 1, 0) +
        ((_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_b_j), 1, 4, 2, 0) - 1) << 2)) - 1];
    }
  }

  c2_b_below_threshold(chartInstance);
  c2_p_eml_scalar_eg(chartInstance);
  c2_c_eml_int_forloop_overflow_check(chartInstance);
  for (c2_c_j = 1; c2_c_j < 5; c2_c_j++) {
    c2_d_j = c2_c_j;
    c2_a = c2_d_j;
    c2_c = c2_a;
    c2_b = c2_c - 1;
    c2_b_c = c2_b << 2;
    c2_b_b = c2_b_c;
    c2_jBcol = c2_b_b;
    c2_j_eml_int_forloop_overflow_check(chartInstance);
    for (c2_k = 4; c2_k > 0; c2_k--) {
      c2_b_k = c2_k;
      c2_b_a = c2_b_k;
      c2_c_c = c2_b_a;
      c2_c_b = c2_c_c - 1;
      c2_d_c = c2_c_b << 2;
      c2_d_b = c2_d_c;
      c2_kAcol = c2_d_b;
      c2_c_a = c2_b_k;
      c2_e_b = c2_jBcol;
      c2_e_c = c2_c_a + c2_e_b;
      if (c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_e_c), 1, 16, 1, 0) - 1] != 0.0) {
        c2_d_a = c2_b_k;
        c2_f_b = c2_jBcol;
        c2_f_c = c2_d_a + c2_f_b;
        c2_e_a = c2_b_k;
        c2_g_b = c2_jBcol;
        c2_g_c = c2_e_a + c2_g_b;
        c2_f_a = c2_b_k;
        c2_h_b = c2_kAcol;
        c2_h_c = c2_f_a + c2_h_b;
        c2_x = c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_g_c), 1, 16, 1, 0) - 1];
        c2_y = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_h_c), 1, 16, 1, 0) - 1];
        c2_z = c2_x / c2_y;
        c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_f_c), 1, 16, 1, 0) - 1] = c2_z;
        c2_g_a = c2_b_k - 1;
        c2_i1211 = c2_g_a;
        c2_h_eml_int_forloop_overflow_check(chartInstance, c2_i1211);
        for (c2_c_i = 1; c2_c_i <= c2_i1211; c2_c_i++) {
          c2_d_i = c2_c_i;
          c2_h_a = c2_d_i;
          c2_i_b = c2_jBcol;
          c2_i_c = c2_h_a + c2_i_b;
          c2_i_a = c2_d_i;
          c2_j_b = c2_jBcol;
          c2_j_c = c2_i_a + c2_j_b;
          c2_j_a = c2_b_k;
          c2_k_b = c2_jBcol;
          c2_k_c = c2_j_a + c2_k_b;
          c2_k_a = c2_d_i;
          c2_l_b = c2_kAcol;
          c2_l_c = c2_k_a + c2_l_b;
          c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_i_c), 1, 16, 1, 0) - 1] =
            c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_j_c), 1, 16, 1, 0) - 1] -
            c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_k_c), 1, 16, 1, 0) - 1] *
            c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_l_c), 1, 16, 1, 0) - 1];
        }
      }
    }
  }

  for (c2_i1212 = 0; c2_i1212 < 16; c2_i1212++) {
    c2_b_A[c2_i1212] = c2_A[c2_i1212];
  }

  if (c2_b_is_singular_triangular_matrix(chartInstance, c2_b_A)) {
    c2_eml_warning(chartInstance);
  }
}

static void c2_j_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
}

static void c2_q_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_r_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_c_mySymPDinv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_M[9], real_T c2_Minv[9])
{
  uint32_T c2_debug_family_var_map[6];
  real_T c2_cholM[9];
  real_T c2_tmp[9];
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i1213;
  int32_T c2_i1214;
  real_T c2_b_cholM[9];
  int32_T c2_i1215;
  static real_T c2_dv82[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

  real_T c2_dv83[9];
  real_T c2_dv84[9];
  int32_T c2_i1216;
  int32_T c2_i1217;
  int32_T c2_i1218;
  int32_T c2_i1219;
  int32_T c2_i1220;
  real_T c2_c_cholM[9];
  int32_T c2_i1221;
  real_T c2_b_tmp[9];
  real_T c2_dv85[9];
  int32_T c2_i1222;
  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c2_m_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(c2_cholM, 0U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_tmp, 1U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 2U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 3U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_M, 4U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Minv, 5U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  CV_EML_FCN(0, 5);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 751);
  for (c2_i1213 = 0; c2_i1213 < 9; c2_i1213++) {
    c2_cholM[c2_i1213] = c2_M[c2_i1213];
  }

  c2_e_chol(chartInstance, c2_cholM);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 752);
  for (c2_i1214 = 0; c2_i1214 < 9; c2_i1214++) {
    c2_b_cholM[c2_i1214] = c2_cholM[c2_i1214];
  }

  for (c2_i1215 = 0; c2_i1215 < 9; c2_i1215++) {
    c2_dv83[c2_i1215] = c2_dv82[c2_i1215];
  }

  c2_c_linsolve(chartInstance, c2_b_cholM, c2_dv83, c2_dv84);
  for (c2_i1216 = 0; c2_i1216 < 9; c2_i1216++) {
    c2_tmp[c2_i1216] = c2_dv84[c2_i1216];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 753);
  c2_i1217 = 0;
  for (c2_i1218 = 0; c2_i1218 < 3; c2_i1218++) {
    c2_i1219 = 0;
    for (c2_i1220 = 0; c2_i1220 < 3; c2_i1220++) {
      c2_c_cholM[c2_i1220 + c2_i1217] = c2_cholM[c2_i1219 + c2_i1218];
      c2_i1219 += 3;
    }

    c2_i1217 += 3;
  }

  for (c2_i1221 = 0; c2_i1221 < 9; c2_i1221++) {
    c2_b_tmp[c2_i1221] = c2_tmp[c2_i1221];
  }

  c2_d_linsolve(chartInstance, c2_c_cholM, c2_b_tmp, c2_dv85);
  for (c2_i1222 = 0; c2_i1222 < 9; c2_i1222++) {
    c2_Minv[c2_i1222] = c2_dv85[c2_i1222];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -753);
  sf_debug_symbol_scope_pop();
}

static void c2_b_chol(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_A[9], real_T c2_b_A[9])
{
  int32_T c2_i1223;
  for (c2_i1223 = 0; c2_i1223 < 9; c2_i1223++) {
    c2_b_A[c2_i1223] = c2_A[c2_i1223];
  }

  c2_e_chol(chartInstance, c2_b_A);
}

static void c2_s_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_b_eml_matlab_zpotrf(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_b_A[9], int32_T *c2_info)
{
  int32_T c2_i1224;
  for (c2_i1224 = 0; c2_i1224 < 9; c2_i1224++) {
    c2_b_A[c2_i1224] = c2_A[c2_i1224];
  }

  *c2_info = c2_e_eml_matlab_zpotrf(chartInstance, c2_b_A);
}

static void c2_b_eml_xgemv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_ia0, int32_T c2_ix0,
  real_T c2_y[9], int32_T c2_iy0, real_T c2_b_y[9])
{
  int32_T c2_i1225;
  for (c2_i1225 = 0; c2_i1225 < 9; c2_i1225++) {
    c2_b_y[c2_i1225] = c2_y[c2_i1225];
  }

  c2_e_eml_xgemv(chartInstance, c2_m, c2_n, c2_ia0, c2_ix0, c2_b_y, c2_iy0);
}

static void c2_c_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_B[9], real_T c2_C[9])
{
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_c_j;
  int32_T c2_d_j;
  int32_T c2_a;
  int32_T c2_c;
  int32_T c2_b;
  int32_T c2_b_c;
  int32_T c2_b_b;
  int32_T c2_jBcol;
  int32_T c2_k;
  int32_T c2_b_k;
  int32_T c2_b_a;
  int32_T c2_c_c;
  int32_T c2_c_b;
  int32_T c2_d_c;
  int32_T c2_d_b;
  int32_T c2_kAcol;
  int32_T c2_c_a;
  int32_T c2_e_b;
  int32_T c2_e_c;
  int32_T c2_d_a;
  int32_T c2_f_b;
  int32_T c2_f_c;
  int32_T c2_e_a;
  int32_T c2_g_b;
  int32_T c2_g_c;
  int32_T c2_f_a;
  int32_T c2_h_b;
  int32_T c2_h_c;
  real_T c2_x;
  real_T c2_y;
  real_T c2_z;
  int32_T c2_g_a;
  int32_T c2_i1226;
  int32_T c2_c_i;
  int32_T c2_d_i;
  int32_T c2_h_a;
  int32_T c2_i_b;
  int32_T c2_i_c;
  int32_T c2_i_a;
  int32_T c2_j_b;
  int32_T c2_j_c;
  int32_T c2_j_a;
  int32_T c2_k_b;
  int32_T c2_k_c;
  int32_T c2_k_a;
  int32_T c2_l_b;
  int32_T c2_l_c;
  int32_T c2_i1227;
  real_T c2_b_A[9];
  c2_s_eml_scalar_eg(chartInstance);
  c2_b_eml_int_forloop_overflow_check(chartInstance);
  for (c2_j = 1; c2_j < 4; c2_j++) {
    c2_b_j = c2_j;
    c2_b_eml_int_forloop_overflow_check(chartInstance);
    for (c2_i = 1; c2_i < 4; c2_i++) {
      c2_b_i = c2_i;
      c2_C[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1))
        - 1] = c2_B[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                     (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1];
    }
  }

  c2_c_below_threshold(chartInstance);
  c2_t_eml_scalar_eg(chartInstance);
  c2_b_eml_int_forloop_overflow_check(chartInstance);
  for (c2_c_j = 1; c2_c_j < 4; c2_c_j++) {
    c2_d_j = c2_c_j;
    c2_a = c2_d_j;
    c2_c = c2_a;
    c2_b = c2_c - 1;
    c2_b_c = 3 * c2_b;
    c2_b_b = c2_b_c;
    c2_jBcol = c2_b_b;
    c2_b_eml_int_forloop_overflow_check(chartInstance);
    for (c2_k = 1; c2_k < 4; c2_k++) {
      c2_b_k = c2_k;
      c2_b_a = c2_b_k;
      c2_c_c = c2_b_a;
      c2_c_b = c2_c_c - 1;
      c2_d_c = 3 * c2_c_b;
      c2_d_b = c2_d_c;
      c2_kAcol = c2_d_b;
      c2_c_a = c2_b_k;
      c2_e_b = c2_jBcol;
      c2_e_c = c2_c_a + c2_e_b;
      if (c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_e_c), 1, 9, 1, 0) - 1] != 0.0) {
        c2_d_a = c2_b_k;
        c2_f_b = c2_jBcol;
        c2_f_c = c2_d_a + c2_f_b;
        c2_e_a = c2_b_k;
        c2_g_b = c2_jBcol;
        c2_g_c = c2_e_a + c2_g_b;
        c2_f_a = c2_b_k;
        c2_h_b = c2_kAcol;
        c2_h_c = c2_f_a + c2_h_b;
        c2_x = c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_g_c), 1, 9, 1, 0) - 1];
        c2_y = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_h_c), 1, 9, 1, 0) - 1];
        c2_z = c2_x / c2_y;
        c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_f_c), 1, 9, 1, 0) - 1] = c2_z;
        c2_g_a = c2_b_k + 1;
        c2_i1226 = c2_g_a;
        c2_i_eml_int_forloop_overflow_check(chartInstance, c2_i1226, 3);
        for (c2_c_i = c2_i1226; c2_c_i < 4; c2_c_i++) {
          c2_d_i = c2_c_i;
          c2_h_a = c2_d_i;
          c2_i_b = c2_jBcol;
          c2_i_c = c2_h_a + c2_i_b;
          c2_i_a = c2_d_i;
          c2_j_b = c2_jBcol;
          c2_j_c = c2_i_a + c2_j_b;
          c2_j_a = c2_b_k;
          c2_k_b = c2_jBcol;
          c2_k_c = c2_j_a + c2_k_b;
          c2_k_a = c2_d_i;
          c2_l_b = c2_kAcol;
          c2_l_c = c2_k_a + c2_l_b;
          c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_i_c), 1, 9, 1, 0) - 1] = c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK
            ("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_j_c), 1, 9, 1, 0) -
            1] - c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_k_c), 1, 9, 1, 0) - 1] *
            c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_l_c), 1, 9, 1, 0) - 1];
        }
      }
    }
  }

  for (c2_i1227 = 0; c2_i1227 < 9; c2_i1227++) {
    c2_b_A[c2_i1227] = c2_A[c2_i1227];
  }

  if (c2_c_is_singular_triangular_matrix(chartInstance, c2_b_A)) {
    c2_eml_warning(chartInstance);
  }
}

static void c2_c_below_threshold(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_t_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static boolean_T c2_c_is_singular_triangular_matrix
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, real_T c2_A[9])
{
  boolean_T c2_p;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_x;
  real_T c2_b_x;
  boolean_T c2_b;
  boolean_T c2_b5;
  real_T c2_c_x;
  boolean_T c2_b_b;
  boolean_T c2_b6;
  boolean_T c2_c_b;
  boolean_T guard1 = FALSE;
  int32_T exitg1;
  c2_b_eml_int_forloop_overflow_check(chartInstance);
  c2_k = 1;
  guard1 = FALSE;
  do {
    exitg1 = 0;
    if (c2_k < 4) {
      c2_b_k = c2_k;
      if (c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
             (real_T)c2_b_k), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 3, 2, 0) - 1))
          - 1] == 0.0) {
        guard1 = TRUE;
        exitg1 = 1;
      } else {
        c2_x = c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_b_k), 1, 3, 1, 0) + 3 *
                     (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 3, 2, 0) - 1)) - 1];
        c2_b_x = c2_x;
        c2_b = muDoubleScalarIsInf(c2_b_x);
        c2_b5 = !c2_b;
        c2_c_x = c2_x;
        c2_b_b = muDoubleScalarIsNaN(c2_c_x);
        c2_b6 = !c2_b_b;
        c2_c_b = (c2_b5 && c2_b6);
        if (!c2_c_b) {
          guard1 = TRUE;
          exitg1 = 1;
        } else {
          c2_k++;
          guard1 = FALSE;
        }
      }
    } else {
      c2_p = FALSE;
      exitg1 = 1;
    }
  } while (exitg1 == 0U);

  if (guard1 == TRUE) {
    c2_p = TRUE;
  }

  return c2_p;
}

static void c2_d_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_B[9], real_T c2_C[9])
{
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_c_j;
  int32_T c2_d_j;
  int32_T c2_a;
  int32_T c2_c;
  int32_T c2_b;
  int32_T c2_b_c;
  int32_T c2_b_b;
  int32_T c2_jBcol;
  int32_T c2_k;
  int32_T c2_b_k;
  int32_T c2_b_a;
  int32_T c2_c_c;
  int32_T c2_c_b;
  int32_T c2_d_c;
  int32_T c2_d_b;
  int32_T c2_kAcol;
  int32_T c2_c_a;
  int32_T c2_e_b;
  int32_T c2_e_c;
  int32_T c2_d_a;
  int32_T c2_f_b;
  int32_T c2_f_c;
  int32_T c2_e_a;
  int32_T c2_g_b;
  int32_T c2_g_c;
  int32_T c2_f_a;
  int32_T c2_h_b;
  int32_T c2_h_c;
  real_T c2_x;
  real_T c2_y;
  real_T c2_z;
  int32_T c2_g_a;
  int32_T c2_i1228;
  int32_T c2_c_i;
  int32_T c2_d_i;
  int32_T c2_h_a;
  int32_T c2_i_b;
  int32_T c2_i_c;
  int32_T c2_i_a;
  int32_T c2_j_b;
  int32_T c2_j_c;
  int32_T c2_j_a;
  int32_T c2_k_b;
  int32_T c2_k_c;
  int32_T c2_k_a;
  int32_T c2_l_b;
  int32_T c2_l_c;
  int32_T c2_i1229;
  real_T c2_b_A[9];
  c2_s_eml_scalar_eg(chartInstance);
  c2_b_eml_int_forloop_overflow_check(chartInstance);
  for (c2_j = 1; c2_j < 4; c2_j++) {
    c2_b_j = c2_j;
    c2_b_eml_int_forloop_overflow_check(chartInstance);
    for (c2_i = 1; c2_i < 4; c2_i++) {
      c2_b_i = c2_i;
      c2_C[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1))
        - 1] = c2_B[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                     (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1];
    }
  }

  c2_c_below_threshold(chartInstance);
  c2_t_eml_scalar_eg(chartInstance);
  c2_b_eml_int_forloop_overflow_check(chartInstance);
  for (c2_c_j = 1; c2_c_j < 4; c2_c_j++) {
    c2_d_j = c2_c_j;
    c2_a = c2_d_j;
    c2_c = c2_a;
    c2_b = c2_c - 1;
    c2_b_c = 3 * c2_b;
    c2_b_b = c2_b_c;
    c2_jBcol = c2_b_b;
    c2_k_eml_int_forloop_overflow_check(chartInstance);
    for (c2_k = 3; c2_k > 0; c2_k--) {
      c2_b_k = c2_k;
      c2_b_a = c2_b_k;
      c2_c_c = c2_b_a;
      c2_c_b = c2_c_c - 1;
      c2_d_c = 3 * c2_c_b;
      c2_d_b = c2_d_c;
      c2_kAcol = c2_d_b;
      c2_c_a = c2_b_k;
      c2_e_b = c2_jBcol;
      c2_e_c = c2_c_a + c2_e_b;
      if (c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_e_c), 1, 9, 1, 0) - 1] != 0.0) {
        c2_d_a = c2_b_k;
        c2_f_b = c2_jBcol;
        c2_f_c = c2_d_a + c2_f_b;
        c2_e_a = c2_b_k;
        c2_g_b = c2_jBcol;
        c2_g_c = c2_e_a + c2_g_b;
        c2_f_a = c2_b_k;
        c2_h_b = c2_kAcol;
        c2_h_c = c2_f_a + c2_h_b;
        c2_x = c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_g_c), 1, 9, 1, 0) - 1];
        c2_y = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_h_c), 1, 9, 1, 0) - 1];
        c2_z = c2_x / c2_y;
        c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_f_c), 1, 9, 1, 0) - 1] = c2_z;
        c2_g_a = c2_b_k - 1;
        c2_i1228 = c2_g_a;
        c2_h_eml_int_forloop_overflow_check(chartInstance, c2_i1228);
        for (c2_c_i = 1; c2_c_i <= c2_i1228; c2_c_i++) {
          c2_d_i = c2_c_i;
          c2_h_a = c2_d_i;
          c2_i_b = c2_jBcol;
          c2_i_c = c2_h_a + c2_i_b;
          c2_i_a = c2_d_i;
          c2_j_b = c2_jBcol;
          c2_j_c = c2_i_a + c2_j_b;
          c2_j_a = c2_b_k;
          c2_k_b = c2_jBcol;
          c2_k_c = c2_j_a + c2_k_b;
          c2_k_a = c2_d_i;
          c2_l_b = c2_kAcol;
          c2_l_c = c2_k_a + c2_l_b;
          c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_i_c), 1, 9, 1, 0) - 1] = c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK
            ("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_j_c), 1, 9, 1, 0) -
            1] - c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_k_c), 1, 9, 1, 0) - 1] *
            c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_l_c), 1, 9, 1, 0) - 1];
        }
      }
    }
  }

  for (c2_i1229 = 0; c2_i1229 < 9; c2_i1229++) {
    c2_b_A[c2_i1229] = c2_A[c2_i1229];
  }

  if (c2_c_is_singular_triangular_matrix(chartInstance, c2_b_A)) {
    c2_eml_warning(chartInstance);
  }
}

static void c2_k_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
}

static void c2_d_diag(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_v[44], real_T c2_d[1936])
{
  int32_T c2_i1230;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_a;
  int32_T c2_c;
  for (c2_i1230 = 0; c2_i1230 < 1936; c2_i1230++) {
    c2_d[c2_i1230] = 0.0;
  }

  c2_f_eml_int_forloop_overflow_check(chartInstance);
  for (c2_j = 1; c2_j < 45; c2_j++) {
    c2_b_j = c2_j;
    c2_a = c2_b_j;
    c2_c = c2_a;
    c2_d[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_j), 1, 44, 1, 0) + 44 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_c), 1, 44, 2, 0) - 1)) -
      1] = c2_v[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_b_j), 1, 44, 1, 0) - 1];
  }
}

static void c2_u_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_f_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[1936], real_T c2_C[1760],
  real_T c2_b_C[1760])
{
  int32_T c2_i1231;
  int32_T c2_i1232;
  real_T c2_b_A[1760];
  int32_T c2_i1233;
  real_T c2_b_B[1936];
  for (c2_i1231 = 0; c2_i1231 < 1760; c2_i1231++) {
    c2_b_C[c2_i1231] = c2_C[c2_i1231];
  }

  for (c2_i1232 = 0; c2_i1232 < 1760; c2_i1232++) {
    c2_b_A[c2_i1232] = c2_A[c2_i1232];
  }

  for (c2_i1233 = 0; c2_i1233 < 1936; c2_i1233++) {
    c2_b_B[c2_i1233] = c2_B[c2_i1233];
  }

  c2_s_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static void c2_v_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_g_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[1760], real_T c2_C[1600],
  real_T c2_b_C[1600])
{
  int32_T c2_i1234;
  int32_T c2_i1235;
  real_T c2_b_A[1760];
  int32_T c2_i1236;
  real_T c2_b_B[1760];
  for (c2_i1234 = 0; c2_i1234 < 1600; c2_i1234++) {
    c2_b_C[c2_i1234] = c2_C[c2_i1234];
  }

  for (c2_i1235 = 0; c2_i1235 < 1760; c2_i1235++) {
    c2_b_A[c2_i1235] = c2_A[c2_i1235];
  }

  for (c2_i1236 = 0; c2_i1236 < 1760; c2_i1236++) {
    c2_b_B[c2_i1236] = c2_B[c2_i1236];
  }

  c2_t_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static void c2_w_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_h_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1600], real_T c2_B[1600], real_T c2_C[1600],
  real_T c2_b_C[1600])
{
  int32_T c2_i1237;
  int32_T c2_i1238;
  real_T c2_b_A[1600];
  int32_T c2_i1239;
  real_T c2_b_B[1600];
  for (c2_i1237 = 0; c2_i1237 < 1600; c2_i1237++) {
    c2_b_C[c2_i1237] = c2_C[c2_i1237];
  }

  for (c2_i1238 = 0; c2_i1238 < 1600; c2_i1238++) {
    c2_b_A[c2_i1238] = c2_A[c2_i1238];
  }

  for (c2_i1239 = 0; c2_i1239 < 1600; c2_i1239++) {
    c2_b_B[c2_i1239] = c2_B[c2_i1239];
  }

  c2_u_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static void c2_eye(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                   real_T c2_I[1600])
{
  int32_T c2_i1240;
  int32_T c2_i;
  int32_T c2_b_i;
  c2_isVariableSizing(chartInstance);
  for (c2_i1240 = 0; c2_i1240 < 1600; c2_i1240++) {
    c2_I[c2_i1240] = 0.0;
  }

  c2_d_eml_int_forloop_overflow_check(chartInstance);
  for (c2_i = 1; c2_i < 41; c2_i++) {
    c2_b_i = c2_i;
    c2_I[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_i), 1, 40, 1, 0) + 40 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 40, 2, 0) - 1))
      - 1] = 1.0;
  }
}

static void c2_eps(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance)
{
}

static real_T c2_Rtil(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_phiInv[1600])
{
  real_T c2_Rt;
  uint32_T c2_debug_family_var_map[7];
  real_T c2_ii;
  real_T c2_n;
  real_T c2_m;
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 1.0;
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c2_n_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_ii, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_n, 1U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_m, 2U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 3U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 4U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_phiInv, 5U, c2_e_sf_marshallOut,
    c2_i_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_Rt, 6U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  c2_ii = 0.0;
  c2_n = 3.0;
  c2_m = 1.0;
  CV_EML_FCN(0, 2);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 734);
  c2_realmax(chartInstance);
  c2_realmax(chartInstance);
  c2_Rt = c2_phiInv[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -734);
  sf_debug_symbol_scope_pop();
  return c2_Rt;
}

static void c2_Qtil(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                    real_T c2_phiInv[1600], real_T c2_Qt[9])
{
  uint32_T c2_debug_family_var_map[7];
  real_T c2_ii;
  real_T c2_n;
  real_T c2_m;
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i1241;
  int32_T c2_i1242;
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c2_o_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_ii, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_n, 1U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_m, 2U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 3U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 4U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_phiInv, 5U, c2_e_sf_marshallOut,
    c2_i_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Qt, 6U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  c2_ii = 1.0;
  c2_n = 3.0;
  c2_m = 1.0;
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 730);
  c2_realmax(chartInstance);
  c2_realmax(chartInstance);
  for (c2_i1241 = 0; c2_i1241 < 3; c2_i1241++) {
    for (c2_i1242 = 0; c2_i1242 < 3; c2_i1242++) {
      c2_Qt[c2_i1242 + 3 * c2_i1241] = c2_phiInv[(_SFD_EML_ARRAY_BOUNDS_CHECK(
        "phiInv", (int32_T)_SFD_INTEGER_CHECK("m + (m+n)*(ii-1) + (1:n)", c2_m +
        (1.0 + (real_T)c2_i1242)), 1, 40, 1, 0) + 40 *
        (_SFD_EML_ARRAY_BOUNDS_CHECK("phiInv", (int32_T)_SFD_INTEGER_CHECK(
        "m + (m+n)*(ii-1) + (1:n)", c2_m + (1.0 + (real_T)c2_i1241)), 1, 40, 2,
        0) - 1)) - 1];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -730);
  sf_debug_symbol_scope_pop();
}

static void c2_b_Qtil(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_phiInv[1600], real_T c2_ii, real_T c2_Qt[9])
{
  uint32_T c2_debug_family_var_map[7];
  real_T c2_n;
  real_T c2_m;
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 1.0;
  real_T c2_b;
  real_T c2_y;
  real_T c2_b_b;
  real_T c2_b_y;
  real_T c2_b_m;
  real_T c2_c_m;
  int32_T c2_i1243;
  int32_T c2_i1244;
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c2_p_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_n, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_m, 1U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 2U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 3U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_phiInv, 4U, c2_e_sf_marshallOut,
    c2_i_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_ii, 5U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Qt, 6U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  c2_n = 3.0;
  c2_m = 1.0;
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 730);
  c2_realmax(chartInstance);
  c2_realmax(chartInstance);
  c2_b = c2_ii - 1.0;
  c2_y = 4.0 * c2_b;
  c2_b_b = c2_ii - 1.0;
  c2_b_y = 4.0 * c2_b_b;
  c2_b_m = c2_m + c2_y;
  c2_c_m = c2_m + c2_b_y;
  for (c2_i1243 = 0; c2_i1243 < 3; c2_i1243++) {
    for (c2_i1244 = 0; c2_i1244 < 3; c2_i1244++) {
      c2_Qt[c2_i1244 + 3 * c2_i1243] = c2_phiInv[(_SFD_EML_ARRAY_BOUNDS_CHECK(
        "phiInv", (int32_T)_SFD_INTEGER_CHECK("m + (m+n)*(ii-1) + (1:n)", c2_b_m
        + (1.0 + (real_T)c2_i1244)), 1, 40, 1, 0) + 40 *
        (_SFD_EML_ARRAY_BOUNDS_CHECK("phiInv", (int32_T)_SFD_INTEGER_CHECK(
        "m + (m+n)*(ii-1) + (1:n)", c2_c_m + (1.0 + (real_T)c2_i1243)), 1, 40, 2,
        0) - 1)) - 1];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -730);
  sf_debug_symbol_scope_pop();
}

static void c2_multByAT(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_M[9], real_T c2_AT[9], real_T c2_switches[9], real_T
  c2_y[9])
{
  uint32_T c2_debug_family_var_map[7];
  real_T c2_n;
  real_T c2_nargin = 3.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i1245;
  real_T c2_a[9];
  int32_T c2_i1246;
  real_T c2_b[9];
  int32_T c2_i1247;
  int32_T c2_i1248;
  int32_T c2_i1249;
  real_T c2_C[9];
  int32_T c2_i1250;
  int32_T c2_i1251;
  int32_T c2_i1252;
  int32_T c2_i1253;
  int32_T c2_i1254;
  int32_T c2_i1255;
  int32_T c2_i1256;
  int32_T c2_i1257;
  int32_T c2_i1258;
  int32_T c2_ii;
  real_T c2_b_ii;
  real_T c2_b_a;
  real_T c2_b_y;
  real_T c2_c_a;
  real_T c2_c_y;
  int32_T c2_i1259;
  int32_T c2_i1260;
  real_T c2_d_a[3];
  real_T c2_b_b;
  int32_T c2_i1261;
  int32_T c2_i1262;
  int32_T c2_i1263;
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c2_q_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_n, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 1U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 2U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_M, 3U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_AT, 4U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_switches, 5U, c2_v_sf_marshallOut,
    c2_p_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_y, 6U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  CV_EML_FCN(0, 15);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 948);
  if (CV_EML_IF(0, 1, 62, c2_switches[6] == 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 949);
    for (c2_i1245 = 0; c2_i1245 < 9; c2_i1245++) {
      c2_a[c2_i1245] = c2_M[c2_i1245];
    }

    for (c2_i1246 = 0; c2_i1246 < 9; c2_i1246++) {
      c2_b[c2_i1246] = c2_AT[c2_i1246];
    }

    c2_s_eml_scalar_eg(chartInstance);
    c2_s_eml_scalar_eg(chartInstance);
    for (c2_i1247 = 0; c2_i1247 < 9; c2_i1247++) {
      c2_y[c2_i1247] = 0.0;
    }

    for (c2_i1248 = 0; c2_i1248 < 9; c2_i1248++) {
      c2_y[c2_i1248] = 0.0;
    }

    for (c2_i1249 = 0; c2_i1249 < 9; c2_i1249++) {
      c2_C[c2_i1249] = c2_y[c2_i1249];
    }

    for (c2_i1250 = 0; c2_i1250 < 9; c2_i1250++) {
      c2_y[c2_i1250] = c2_C[c2_i1250];
    }

    for (c2_i1251 = 0; c2_i1251 < 9; c2_i1251++) {
      c2_C[c2_i1251] = c2_y[c2_i1251];
    }

    for (c2_i1252 = 0; c2_i1252 < 9; c2_i1252++) {
      c2_y[c2_i1252] = c2_C[c2_i1252];
    }

    for (c2_i1253 = 0; c2_i1253 < 3; c2_i1253++) {
      c2_i1254 = 0;
      for (c2_i1255 = 0; c2_i1255 < 3; c2_i1255++) {
        c2_y[c2_i1254 + c2_i1253] = 0.0;
        c2_i1256 = 0;
        for (c2_i1257 = 0; c2_i1257 < 3; c2_i1257++) {
          c2_y[c2_i1254 + c2_i1253] += c2_a[c2_i1256 + c2_i1253] * c2_b[c2_i1257
            + c2_i1254];
          c2_i1256 += 3;
        }

        c2_i1254 += 3;
      }
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 952);
    c2_n = 1.5;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 954);
    for (c2_i1258 = 0; c2_i1258 < 9; c2_i1258++) {
      c2_y[c2_i1258] = 0.0;
    }

    c2_ii = 0;
    while (c2_ii < 2) {
      c2_b_ii = 1.0 + (real_T)c2_ii;
      CV_EML_FOR(0, 1, 19, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 957);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_b_a = c2_b_ii - 1.0;
      c2_b_y = c2_b_a * 1.5;
      c2_c_a = c2_b_ii - 1.0;
      c2_c_y = c2_c_a * 1.5;
      c2_i1259 = _SFD_EML_ARRAY_BOUNDS_CHECK("M", (int32_T)_SFD_INTEGER_CHECK(
        "(1:n)+(ii-1)*n", 1.0 + c2_c_y), 1, 3, 2, 0) - 1;
      for (c2_i1260 = 0; c2_i1260 < 3; c2_i1260++) {
        c2_d_a[c2_i1260] = c2_M[c2_i1260 + 3 * c2_i1259];
      }

      c2_b_b = c2_AT[0];
      for (c2_i1261 = 0; c2_i1261 < 3; c2_i1261++) {
        c2_d_a[c2_i1261] *= c2_b_b;
      }

      c2_i1262 = _SFD_EML_ARRAY_BOUNDS_CHECK("y", (int32_T)_SFD_INTEGER_CHECK(
        "(1:n)+(ii-1)*n", 1.0 + c2_b_y), 1, 3, 2, 0) - 1;
      for (c2_i1263 = 0; c2_i1263 < 3; c2_i1263++) {
        c2_y[c2_i1263 + 3 * c2_i1262] = c2_d_a[c2_i1263];
      }

      c2_ii++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 19, 0);
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -957);
  sf_debug_symbol_scope_pop();
}

static void c2_Stil(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                    real_T c2_phiInv[1600], real_T c2_ii, real_T c2_St[3])
{
  uint32_T c2_debug_family_var_map[7];
  real_T c2_n;
  real_T c2_m;
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 1.0;
  real_T c2_b;
  real_T c2_y;
  real_T c2_b_b;
  real_T c2_b_y;
  real_T c2_b_m;
  int32_T c2_c_y;
  int32_T c2_i1264;
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c2_r_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_n, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_m, 1U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 2U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 3U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_phiInv, 4U, c2_e_sf_marshallOut,
    c2_i_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_ii, 5U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_St, 6U, c2_i_sf_marshallOut,
    c2_r_sf_marshallIn);
  c2_n = 3.0;
  c2_m = 1.0;
  CV_EML_FCN(0, 3);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 738);
  c2_realmax(chartInstance);
  c2_realmax(chartInstance);
  c2_b = c2_ii - 1.0;
  c2_y = 4.0 * c2_b;
  c2_b_b = c2_ii;
  c2_b_y = 4.0 * c2_b_b;
  c2_b_m = c2_m + c2_y;
  c2_c_y = _SFD_EML_ARRAY_BOUNDS_CHECK("phiInv", (int32_T)_SFD_INTEGER_CHECK(
    "(m+n)*ii + (1:m)", c2_b_y + 1.0), 1, 40, 2, 0) - 1;
  for (c2_i1264 = 0; c2_i1264 < 3; c2_i1264++) {
    c2_St[c2_i1264] = c2_phiInv[(_SFD_EML_ARRAY_BOUNDS_CHECK("phiInv", (int32_T)
      _SFD_INTEGER_CHECK("m + (m+n)*(ii-1) + (1:n)", c2_b_m + (1.0 + (real_T)
      c2_i1264)), 1, 40, 1, 0) + 40 * c2_c_y) - 1];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -738);
  sf_debug_symbol_scope_pop();
}

static void c2_b_preMultByA(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_M[9], real_T c2_A[9], real_T c2_switches[9], real_T
  c2_y[9])
{
  uint32_T c2_debug_family_var_map[7];
  real_T c2_n;
  real_T c2_nargin = 3.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i1265;
  real_T c2_a[9];
  int32_T c2_i1266;
  real_T c2_b[9];
  int32_T c2_i1267;
  int32_T c2_i1268;
  int32_T c2_i1269;
  real_T c2_C[9];
  int32_T c2_i1270;
  int32_T c2_i1271;
  int32_T c2_i1272;
  int32_T c2_i1273;
  int32_T c2_i1274;
  int32_T c2_i1275;
  int32_T c2_i1276;
  int32_T c2_i1277;
  int32_T c2_i1278;
  int32_T c2_ii;
  real_T c2_b_ii;
  real_T c2_b_a;
  real_T c2_b_y;
  real_T c2_c_a;
  real_T c2_c_y;
  real_T c2_d_a;
  int32_T c2_i1279;
  int32_T c2_i1280;
  real_T c2_b_b[3];
  int32_T c2_i1281;
  int32_T c2_i1282;
  int32_T c2_i1283;
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c2_s_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_n, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 1U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 2U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_M, 3U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_A, 4U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_switches, 5U, c2_v_sf_marshallOut,
    c2_p_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_y, 6U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  CV_EML_FCN(0, 14);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 929);
  if (CV_EML_IF(0, 1, 61, c2_switches[5] == 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 930);
    for (c2_i1265 = 0; c2_i1265 < 9; c2_i1265++) {
      c2_a[c2_i1265] = c2_A[c2_i1265];
    }

    for (c2_i1266 = 0; c2_i1266 < 9; c2_i1266++) {
      c2_b[c2_i1266] = c2_M[c2_i1266];
    }

    c2_s_eml_scalar_eg(chartInstance);
    c2_s_eml_scalar_eg(chartInstance);
    for (c2_i1267 = 0; c2_i1267 < 9; c2_i1267++) {
      c2_y[c2_i1267] = 0.0;
    }

    for (c2_i1268 = 0; c2_i1268 < 9; c2_i1268++) {
      c2_y[c2_i1268] = 0.0;
    }

    for (c2_i1269 = 0; c2_i1269 < 9; c2_i1269++) {
      c2_C[c2_i1269] = c2_y[c2_i1269];
    }

    for (c2_i1270 = 0; c2_i1270 < 9; c2_i1270++) {
      c2_y[c2_i1270] = c2_C[c2_i1270];
    }

    for (c2_i1271 = 0; c2_i1271 < 9; c2_i1271++) {
      c2_C[c2_i1271] = c2_y[c2_i1271];
    }

    for (c2_i1272 = 0; c2_i1272 < 9; c2_i1272++) {
      c2_y[c2_i1272] = c2_C[c2_i1272];
    }

    for (c2_i1273 = 0; c2_i1273 < 3; c2_i1273++) {
      c2_i1274 = 0;
      for (c2_i1275 = 0; c2_i1275 < 3; c2_i1275++) {
        c2_y[c2_i1274 + c2_i1273] = 0.0;
        c2_i1276 = 0;
        for (c2_i1277 = 0; c2_i1277 < 3; c2_i1277++) {
          c2_y[c2_i1274 + c2_i1273] += c2_a[c2_i1276 + c2_i1273] * c2_b[c2_i1277
            + c2_i1274];
          c2_i1276 += 3;
        }

        c2_i1274 += 3;
      }
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 933);
    c2_n = 1.5;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 935);
    for (c2_i1278 = 0; c2_i1278 < 9; c2_i1278++) {
      c2_y[c2_i1278] = 0.0;
    }

    c2_ii = 0;
    while (c2_ii < 2) {
      c2_b_ii = 1.0 + (real_T)c2_ii;
      CV_EML_FOR(0, 1, 18, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 938);
      c2_realmax(chartInstance);
      c2_realmax(chartInstance);
      c2_b_a = c2_b_ii - 1.0;
      c2_b_y = c2_b_a * 1.5;
      c2_c_a = c2_b_ii - 1.0;
      c2_c_y = c2_c_a * 1.5;
      c2_d_a = c2_A[0];
      c2_i1279 = _SFD_EML_ARRAY_BOUNDS_CHECK("M", (int32_T)_SFD_INTEGER_CHECK(
        "(1:n)+(ii-1)*n", 1.0 + c2_c_y), 1, 3, 1, 0) - 1;
      for (c2_i1280 = 0; c2_i1280 < 3; c2_i1280++) {
        c2_b_b[c2_i1280] = c2_M[c2_i1279 + 3 * c2_i1280];
      }

      for (c2_i1281 = 0; c2_i1281 < 3; c2_i1281++) {
        c2_b_b[c2_i1281] *= c2_d_a;
      }

      c2_i1282 = _SFD_EML_ARRAY_BOUNDS_CHECK("y", (int32_T)_SFD_INTEGER_CHECK(
        "(1:n)+(ii-1)*n", 1.0 + c2_b_y), 1, 3, 1, 0) - 1;
      for (c2_i1283 = 0; c2_i1283 < 3; c2_i1283++) {
        c2_y[c2_i1282 + 3 * c2_i1283] = c2_b_b[c2_i1283];
      }

      c2_ii++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 18, 0);
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -938);
  sf_debug_symbol_scope_pop();
}

static real_T c2_b_Rtil(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_phiInv[1600], real_T c2_ii)
{
  real_T c2_Rt;
  uint32_T c2_debug_family_var_map[7];
  real_T c2_n;
  real_T c2_m;
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 1.0;
  real_T c2_b;
  real_T c2_y;
  real_T c2_b_b;
  real_T c2_b_y;
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c2_t_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_n, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_m, 1U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 2U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 3U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_phiInv, 4U, c2_e_sf_marshallOut,
    c2_i_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_ii, 5U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_Rt, 6U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  c2_n = 3.0;
  c2_m = 1.0;
  CV_EML_FCN(0, 2);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 734);
  c2_realmax(chartInstance);
  c2_realmax(chartInstance);
  c2_b = c2_ii;
  c2_y = 4.0 * c2_b;
  c2_b_b = c2_ii;
  c2_b_y = 4.0 * c2_b_b;
  c2_Rt = c2_phiInv[(_SFD_EML_ARRAY_BOUNDS_CHECK("phiInv", (int32_T)
    _SFD_INTEGER_CHECK("(m+n)*ii + (1:m)", c2_y + 1.0), 1, 40, 1, 0) + 40 *
                     (_SFD_EML_ARRAY_BOUNDS_CHECK("phiInv", (int32_T)
    _SFD_INTEGER_CHECK("(m+n)*ii + (1:m)", c2_b_y + 1.0), 1, 40, 2, 0) - 1)) - 1];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -734);
  sf_debug_symbol_scope_pop();
  return c2_Rt;
}

static void c2_x_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_y_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_ab_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_i_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[1600], real_T c2_C[1280],
  real_T c2_b_C[1280])
{
  int32_T c2_i1284;
  int32_T c2_i1285;
  real_T c2_b_A[1280];
  int32_T c2_i1286;
  real_T c2_b_B[1600];
  for (c2_i1284 = 0; c2_i1284 < 1280; c2_i1284++) {
    c2_b_C[c2_i1284] = c2_C[c2_i1284];
  }

  for (c2_i1285 = 0; c2_i1285 < 1280; c2_i1285++) {
    c2_b_A[c2_i1285] = c2_A[c2_i1285];
  }

  for (c2_i1286 = 0; c2_i1286 < 1600; c2_i1286++) {
    c2_b_B[c2_i1286] = c2_B[c2_i1286];
  }

  c2_v_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static void c2_bb_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_j_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[1280], real_T c2_C[1024],
  real_T c2_b_C[1024])
{
  int32_T c2_i1287;
  int32_T c2_i1288;
  real_T c2_b_A[1280];
  int32_T c2_i1289;
  real_T c2_b_B[1280];
  for (c2_i1287 = 0; c2_i1287 < 1024; c2_i1287++) {
    c2_b_C[c2_i1287] = c2_C[c2_i1287];
  }

  for (c2_i1288 = 0; c2_i1288 < 1280; c2_i1288++) {
    c2_b_A[c2_i1288] = c2_A[c2_i1288];
  }

  for (c2_i1289 = 0; c2_i1289 < 1280; c2_i1289++) {
    c2_b_B[c2_i1289] = c2_B[c2_i1289];
  }

  c2_w_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static void c2_cb_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static real_T c2_e_norm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x[1024])
{
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_b_x;
  real_T c2_c_x;
  boolean_T c2_b;
  boolean_T c2_b7;
  real_T c2_d_x;
  boolean_T c2_b_b;
  boolean_T c2_b8;
  boolean_T c2_c_b;
  int32_T c2_i1290;
  real_T c2_e_x[1024];
  real_T c2_s[32];
  c2_h_eml_int_forloop_overflow_check(chartInstance, 1024);
  for (c2_k = 1; c2_k < 1025; c2_k++) {
    c2_b_k = c2_k;
    c2_b_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_b_k), 1, 1024, 1, 0) - 1];
    c2_c_x = c2_b_x;
    c2_b = muDoubleScalarIsInf(c2_c_x);
    c2_b7 = !c2_b;
    c2_d_x = c2_b_x;
    c2_b_b = muDoubleScalarIsNaN(c2_d_x);
    c2_b8 = !c2_b_b;
    c2_c_b = (c2_b7 && c2_b8);
    if (!c2_c_b) {
      c2_c_eml_error(chartInstance);
    }
  }

  for (c2_i1290 = 0; c2_i1290 < 1024; c2_i1290++) {
    c2_e_x[c2_i1290] = c2_x[c2_i1290];
  }

  c2_eml_matlab_zsvdc(chartInstance, c2_e_x, c2_s);
  return c2_s[0];
}

static void c2_c_eml_error(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
  int32_T c2_i1291;
  static char_T c2_varargin_1[33] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'v', 'd', '_', 'm', 'a', 't', 'r', 'i', 'x',
    'W', 'i', 't', 'h', 'N', 'a', 'N', 'I', 'n', 'f' };

  char_T c2_u[33];
  const mxArray *c2_y = NULL;
  for (c2_i1291 = 0; c2_i1291 < 33; c2_i1291++) {
    c2_u[c2_i1291] = c2_varargin_1[c2_i1291];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 33), FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c2_y));
}

static void c2_eml_matlab_zsvdc(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1024], real_T c2_S[32])
{
  int32_T c2_i1292;
  real_T c2_s[32];
  int32_T c2_i1293;
  real_T c2_e[32];
  int32_T c2_i1294;
  real_T c2_work[32];
  int32_T c2_q;
  int32_T c2_b_q;
  int32_T c2_a;
  int32_T c2_qp1;
  int32_T c2_b_a;
  int32_T c2_qm1;
  int32_T c2_b;
  int32_T c2_c;
  int32_T c2_c_a;
  int32_T c2_b_b;
  int32_T c2_qq;
  int32_T c2_c_b;
  int32_T c2_nmq;
  int32_T c2_d_a;
  int32_T c2_nmqp1;
  int32_T c2_i1295;
  real_T c2_b_A[1024];
  real_T c2_nrm;
  real_T c2_absx;
  real_T c2_d;
  real_T c2_y;
  real_T c2_d4;
  int32_T c2_b_qp1;
  int32_T c2_jj;
  int32_T c2_b_jj;
  int32_T c2_e_a;
  int32_T c2_b_c;
  int32_T c2_d_b;
  int32_T c2_c_c;
  int32_T c2_f_a;
  int32_T c2_e_b;
  int32_T c2_qjj;
  int32_T c2_i1296;
  real_T c2_c_A[1024];
  int32_T c2_i1297;
  real_T c2_d_A[1024];
  real_T c2_t;
  int32_T c2_f_b;
  int32_T c2_pmq;
  int32_T c2_i1298;
  real_T c2_b_e[32];
  real_T c2_b_absx;
  real_T c2_b_d;
  real_T c2_b_y;
  real_T c2_d5;
  int32_T c2_c_qp1;
  int32_T c2_ii;
  int32_T c2_b_ii;
  int32_T c2_d_qp1;
  int32_T c2_c_jj;
  int32_T c2_g_a;
  int32_T c2_d_c;
  int32_T c2_g_b;
  int32_T c2_e_c;
  int32_T c2_h_a;
  int32_T c2_h_b;
  int32_T c2_qp1jj;
  int32_T c2_i1299;
  real_T c2_e_A[1024];
  int32_T c2_e_qp1;
  int32_T c2_d_jj;
  int32_T c2_i_a;
  int32_T c2_f_c;
  int32_T c2_i_b;
  int32_T c2_g_c;
  int32_T c2_j_a;
  int32_T c2_j_b;
  int32_T c2_i1300;
  real_T c2_b_work[32];
  int32_T c2_m;
  int32_T c2_c_q;
  real_T c2_rt;
  real_T c2_r;
  int32_T c2_k_a;
  int32_T c2_h_c;
  int32_T c2_l_a;
  int32_T c2_i_c;
  real_T c2_m_a;
  real_T c2_k_b;
  real_T c2_c_y;
  real_T c2_iter;
  real_T c2_tiny;
  real_T c2_snorm;
  int32_T c2_c_ii;
  real_T c2_varargin_1;
  real_T c2_varargin_2;
  real_T c2_b_varargin_2;
  real_T c2_varargin_3;
  real_T c2_x;
  real_T c2_d_y;
  real_T c2_b_x;
  real_T c2_e_y;
  real_T c2_xk;
  real_T c2_yk;
  real_T c2_c_x;
  real_T c2_f_y;
  real_T c2_maxval;
  real_T c2_b_varargin_1;
  real_T c2_c_varargin_2;
  real_T c2_d_varargin_2;
  real_T c2_b_varargin_3;
  real_T c2_d_x;
  real_T c2_g_y;
  real_T c2_e_x;
  real_T c2_h_y;
  real_T c2_b_xk;
  real_T c2_b_yk;
  real_T c2_f_x;
  real_T c2_i_y;
  int32_T c2_n_a;
  int32_T c2_o_a;
  int32_T c2_i1301;
  int32_T c2_d_ii;
  int32_T c2_p_a;
  int32_T c2_j_c;
  real_T c2_test0;
  real_T c2_ztest0;
  real_T c2_l_b;
  real_T c2_j_y;
  real_T c2_m_b;
  real_T c2_k_y;
  int32_T c2_q_a;
  int32_T c2_k_c;
  real_T c2_kase;
  int32_T c2_qs;
  int32_T c2_b_m;
  int32_T c2_e_ii;
  real_T c2_test;
  int32_T c2_r_a;
  int32_T c2_l_c;
  int32_T c2_s_a;
  int32_T c2_m_c;
  real_T c2_ztest;
  real_T c2_n_b;
  real_T c2_l_y;
  int32_T c2_t_a;
  int32_T c2_u_a;
  int32_T c2_n_c;
  real_T c2_f;
  int32_T c2_v_a;
  int32_T c2_o_c;
  int32_T c2_w_a;
  int32_T c2_i1302;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_t1;
  real_T c2_b_t1;
  real_T c2_b_f;
  real_T c2_sn;
  real_T c2_cs;
  real_T c2_b_cs;
  real_T c2_b_sn;
  int32_T c2_x_a;
  int32_T c2_km1;
  real_T c2_y_a;
  real_T c2_o_b;
  real_T c2_ab_a;
  real_T c2_p_b;
  real_T c2_m_y;
  int32_T c2_bb_a;
  int32_T c2_d_q;
  int32_T c2_c_k;
  real_T c2_c_t1;
  real_T c2_unusedU0;
  real_T c2_c_sn;
  real_T c2_c_cs;
  real_T c2_cb_a;
  real_T c2_q_b;
  real_T c2_db_a;
  real_T c2_r_b;
  real_T c2_n_y;
  int32_T c2_eb_a;
  int32_T c2_mm1;
  real_T c2_d6;
  real_T c2_d7;
  real_T c2_d8;
  real_T c2_d9;
  real_T c2_d10;
  real_T c2_c_varargin_1[5];
  int32_T c2_ixstart;
  real_T c2_mtmp;
  real_T c2_g_x;
  boolean_T c2_s_b;
  int32_T c2_ix;
  int32_T c2_b_ix;
  real_T c2_h_x;
  boolean_T c2_t_b;
  int32_T c2_fb_a;
  int32_T c2_i1303;
  int32_T c2_c_ix;
  real_T c2_gb_a;
  real_T c2_u_b;
  boolean_T c2_p;
  real_T c2_b_mtmp;
  real_T c2_scale;
  real_T c2_sm;
  real_T c2_smm1;
  real_T c2_emm1;
  real_T c2_sqds;
  real_T c2_eqds;
  real_T c2_hb_a;
  real_T c2_v_b;
  real_T c2_o_y;
  real_T c2_ib_a;
  real_T c2_w_b;
  real_T c2_p_y;
  real_T c2_x_b;
  real_T c2_jb_a;
  real_T c2_y_b;
  real_T c2_p_c;
  real_T c2_kb_a;
  real_T c2_ab_b;
  real_T c2_shift;
  real_T c2_lb_a;
  real_T c2_bb_b;
  real_T c2_q_y;
  real_T c2_mb_a;
  real_T c2_cb_b;
  real_T c2_r_y;
  real_T c2_nb_a;
  real_T c2_db_b;
  real_T c2_g;
  int32_T c2_e_q;
  int32_T c2_d_k;
  int32_T c2_ob_a;
  int32_T c2_pb_a;
  int32_T c2_kp1;
  real_T c2_c_f;
  real_T c2_unusedU1;
  real_T c2_d_sn;
  real_T c2_d_cs;
  real_T c2_qb_a;
  real_T c2_eb_b;
  real_T c2_s_y;
  real_T c2_rb_a;
  real_T c2_fb_b;
  real_T c2_t_y;
  real_T c2_sb_a;
  real_T c2_gb_b;
  real_T c2_u_y;
  real_T c2_tb_a;
  real_T c2_hb_b;
  real_T c2_v_y;
  real_T c2_ub_a;
  real_T c2_ib_b;
  real_T c2_vb_a;
  real_T c2_jb_b;
  real_T c2_w_y;
  real_T c2_d_f;
  real_T c2_unusedU2;
  real_T c2_e_sn;
  real_T c2_e_cs;
  real_T c2_wb_a;
  real_T c2_kb_b;
  real_T c2_x_y;
  real_T c2_xb_a;
  real_T c2_lb_b;
  real_T c2_y_y;
  real_T c2_yb_a;
  real_T c2_mb_b;
  real_T c2_ab_y;
  real_T c2_ac_a;
  real_T c2_nb_b;
  real_T c2_bb_y;
  real_T c2_bc_a;
  real_T c2_ob_b;
  real_T c2_cc_a;
  real_T c2_pb_b;
  real_T c2_cb_y;
  int32_T c2_dc_a;
  int32_T c2_q_c;
  int32_T c2_e_k;
  int32_T c2_ec_a;
  int32_T c2_fc_a;
  int32_T c2_gc_a;
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  boolean_T guard4 = FALSE;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T exitg3;
  boolean_T exitg4;
  boolean_T exitg5;
  boolean_T guard11 = FALSE;
  c2_cb_eml_scalar_eg(chartInstance);
  for (c2_i1292 = 0; c2_i1292 < 32; c2_i1292++) {
    c2_s[c2_i1292] = 0.0;
  }

  for (c2_i1293 = 0; c2_i1293 < 32; c2_i1293++) {
    c2_e[c2_i1293] = 0.0;
  }

  for (c2_i1294 = 0; c2_i1294 < 32; c2_i1294++) {
    c2_work[c2_i1294] = 0.0;
  }

  c2_h_eml_int_forloop_overflow_check(chartInstance, 31);
  for (c2_q = 1; c2_q < 32; c2_q++) {
    c2_b_q = c2_q;
    c2_a = c2_b_q + 1;
    c2_qp1 = c2_a;
    c2_b_a = c2_b_q - 1;
    c2_qm1 = c2_b_a;
    c2_b = c2_qm1;
    c2_c = c2_b << 5;
    c2_c_a = c2_b_q;
    c2_b_b = c2_c;
    c2_qq = c2_c_a + c2_b_b;
    c2_c_b = c2_b_q;
    c2_nmq = 32 - c2_c_b;
    c2_d_a = c2_nmq + 1;
    c2_nmqp1 = c2_d_a;
    if (c2_b_q <= 31) {
      for (c2_i1295 = 0; c2_i1295 < 1024; c2_i1295++) {
        c2_b_A[c2_i1295] = c2_A[c2_i1295];
      }

      c2_nrm = c2_eml_xnrm2(chartInstance, c2_nmqp1, c2_b_A, c2_qq);
      if (c2_nrm > 0.0) {
        c2_absx = c2_nrm;
        c2_d = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_qq), 1, 1024, 1, 0) - 1];
        if (c2_d < 0.0) {
          c2_y = -c2_absx;
        } else {
          c2_y = c2_absx;
        }

        c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_q), 1, 32, 1, 0) - 1] = c2_y;
        c2_d4 = c2_eml_div(chartInstance, 1.0, c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK(
          "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_q), 1, 32, 1, 0) - 1]);
        c2_c_eml_xscal(chartInstance, c2_nmqp1, c2_d4, c2_A, c2_qq);
        c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_qq), 1, 1024, 1, 0) - 1] = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK
          ("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_qq), 1, 1024, 1, 0) -
          1] + 1.0;
        c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_q), 1, 32, 1, 0) - 1] = -c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK
          ("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_q), 1, 32, 1, 0) - 1];
      } else {
        c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_q), 1, 32, 1, 0) - 1] = 0.0;
      }
    }

    c2_b_qp1 = c2_qp1;
    c2_i_eml_int_forloop_overflow_check(chartInstance, c2_b_qp1, 32);
    for (c2_jj = c2_b_qp1; c2_jj < 33; c2_jj++) {
      c2_b_jj = c2_jj;
      c2_e_a = c2_b_jj - 1;
      c2_b_c = c2_e_a;
      c2_d_b = c2_b_c;
      c2_c_c = c2_d_b << 5;
      c2_f_a = c2_b_q;
      c2_e_b = c2_c_c;
      c2_qjj = c2_f_a + c2_e_b;
      if (c2_b_q <= 31) {
        if (c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_q), 1, 32, 1, 0) - 1] != 0.0) {
          for (c2_i1296 = 0; c2_i1296 < 1024; c2_i1296++) {
            c2_c_A[c2_i1296] = c2_A[c2_i1296];
          }

          for (c2_i1297 = 0; c2_i1297 < 1024; c2_i1297++) {
            c2_d_A[c2_i1297] = c2_A[c2_i1297];
          }

          c2_t = c2_eml_xdotc(chartInstance, c2_nmqp1, c2_c_A, c2_qq, c2_d_A,
                              c2_qjj);
          c2_t = -c2_eml_div(chartInstance, c2_t, c2_A
                             [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_q), 1, 32, 1, 0) +
                               ((_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_q), 1, 32, 2, 0) - 1) << 5)) - 1]);
          c2_d_eml_xaxpy(chartInstance, c2_nmqp1, c2_t, c2_qq, c2_A, c2_qjj);
        }
      }

      c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_b_jj), 1, 32, 1, 0) - 1] = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK(
        "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_qjj), 1, 1024, 1, 0) - 1];
    }

    if (c2_b_q <= 30) {
      c2_f_b = c2_b_q;
      c2_pmq = 32 - c2_f_b;
      for (c2_i1298 = 0; c2_i1298 < 32; c2_i1298++) {
        c2_b_e[c2_i1298] = c2_e[c2_i1298];
      }

      c2_nrm = c2_b_eml_xnrm2(chartInstance, c2_pmq, c2_b_e, c2_qp1);
      if (c2_nrm == 0.0) {
        c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_q), 1, 32, 1, 0) - 1] = 0.0;
      } else {
        c2_b_absx = c2_nrm;
        c2_b_d = c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_qp1), 1, 32, 1, 0) - 1];
        if (c2_b_d < 0.0) {
          c2_b_y = -c2_b_absx;
        } else {
          c2_b_y = c2_b_absx;
        }

        c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_q), 1, 32, 1, 0) - 1] = c2_b_y;
        c2_d5 = c2_eml_div(chartInstance, 1.0, c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK(
          "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_q), 1, 32, 1, 0) - 1]);
        c2_d_eml_xscal(chartInstance, c2_pmq, c2_d5, c2_e, c2_qp1);
        c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_qp1), 1, 32, 1, 0) - 1] = c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK(
          "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_qp1), 1, 32, 1, 0) - 1]
          + 1.0;
      }

      c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_b_q), 1, 32, 1, 0) - 1] = -c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK(
        "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_q), 1, 32, 1, 0) - 1];
      if (c2_qp1 <= 32) {
        if (c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_q), 1, 32, 1, 0) - 1] != 0.0) {
          c2_c_qp1 = c2_qp1;
          c2_i_eml_int_forloop_overflow_check(chartInstance, c2_c_qp1, 32);
          for (c2_ii = c2_c_qp1; c2_ii < 33; c2_ii++) {
            c2_b_ii = c2_ii;
            c2_work[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
              "", (real_T)c2_b_ii), 1, 32, 1, 0) - 1] = 0.0;
          }

          c2_d_qp1 = c2_qp1;
          c2_i_eml_int_forloop_overflow_check(chartInstance, c2_d_qp1, 32);
          for (c2_c_jj = c2_d_qp1; c2_c_jj < 33; c2_c_jj++) {
            c2_b_jj = c2_c_jj;
            c2_g_a = c2_b_jj - 1;
            c2_d_c = c2_g_a;
            c2_g_b = c2_d_c;
            c2_e_c = c2_g_b << 5;
            c2_h_a = c2_qp1;
            c2_h_b = c2_e_c;
            c2_qp1jj = c2_h_a + c2_h_b;
            for (c2_i1299 = 0; c2_i1299 < 1024; c2_i1299++) {
              c2_e_A[c2_i1299] = c2_A[c2_i1299];
            }

            c2_e_eml_xaxpy(chartInstance, c2_nmq,
                           c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c2_b_jj), 1, 32, 1, 0) - 1], c2_e_A,
                           c2_qp1jj, c2_work, c2_qp1);
          }

          c2_e_qp1 = c2_qp1;
          c2_i_eml_int_forloop_overflow_check(chartInstance, c2_e_qp1, 32);
          for (c2_d_jj = c2_e_qp1; c2_d_jj < 33; c2_d_jj++) {
            c2_b_jj = c2_d_jj;
            c2_t = c2_eml_div(chartInstance, -c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK(
              "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_jj), 1, 32, 1, 0)
                              - 1], c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_qp1), 1, 32, 1, 0) - 1]);
            c2_i_a = c2_b_jj - 1;
            c2_f_c = c2_i_a;
            c2_i_b = c2_f_c;
            c2_g_c = c2_i_b << 5;
            c2_j_a = c2_qp1;
            c2_j_b = c2_g_c;
            c2_qp1jj = c2_j_a + c2_j_b;
            for (c2_i1300 = 0; c2_i1300 < 32; c2_i1300++) {
              c2_b_work[c2_i1300] = c2_work[c2_i1300];
            }

            c2_f_eml_xaxpy(chartInstance, c2_nmq, c2_t, c2_b_work, c2_qp1, c2_A,
                           c2_qp1jj);
          }
        }
      }
    }
  }

  c2_m = 32;
  c2_s[31] = c2_A[1023];
  c2_e[30] = c2_A[1022];
  c2_e[31] = 0.0;
  c2_eml_int_forloop_overflow_check(chartInstance);
  for (c2_c_q = 1; c2_c_q < 33; c2_c_q++) {
    c2_b_q = c2_c_q;
    if (c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_q), 1, 32, 1, 0) - 1] != 0.0) {
      c2_rt = c2_abs(chartInstance, c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_q), 1, 32, 1, 0) - 1]);
      c2_r = c2_eml_div(chartInstance, c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_q), 1, 32, 1, 0) - 1],
                        c2_rt);
      c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_b_q), 1, 32, 1, 0) - 1] = c2_rt;
      if (c2_b_q < 32) {
        c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_q), 1, 32, 1, 0) - 1] = c2_eml_div(chartInstance,
          c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_q), 1, 32, 1, 0) - 1], c2_r);
      }
    }

    if (c2_b_q < 32) {
      if (c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_q), 1, 32, 1, 0) - 1] != 0.0) {
        c2_rt = c2_abs(chartInstance, c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_q), 1, 32, 1, 0) - 1]);
        c2_r = c2_eml_div(chartInstance, c2_rt, c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK
                          ("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_q),
                           1, 32, 1, 0) - 1]);
        c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_q), 1, 32, 1, 0) - 1] = c2_rt;
        c2_k_a = c2_b_q + 1;
        c2_h_c = c2_k_a;
        c2_l_a = c2_b_q + 1;
        c2_i_c = c2_l_a;
        c2_m_a = c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_i_c), 1, 32, 1, 0) - 1];
        c2_k_b = c2_r;
        c2_c_y = c2_m_a * c2_k_b;
        c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_h_c), 1, 32, 1, 0) - 1] = c2_c_y;
      }
    }
  }

  c2_iter = 0.0;
  c2_realmin(chartInstance);
  c2_eps(chartInstance);
  c2_tiny = c2_eml_div(chartInstance, 2.2250738585072014E-308,
                       2.2204460492503131E-16);
  c2_snorm = 0.0;
  c2_eml_int_forloop_overflow_check(chartInstance);
  for (c2_c_ii = 1; c2_c_ii < 33; c2_c_ii++) {
    c2_b_ii = c2_c_ii;
    c2_varargin_1 = c2_abs(chartInstance, c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("",
      (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_ii), 1, 32, 1, 0) - 1]);
    c2_varargin_2 = c2_abs(chartInstance, c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("",
      (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_ii), 1, 32, 1, 0) - 1]);
    c2_b_varargin_2 = c2_varargin_1;
    c2_varargin_3 = c2_varargin_2;
    c2_x = c2_b_varargin_2;
    c2_d_y = c2_varargin_3;
    c2_b_x = c2_x;
    c2_e_y = c2_d_y;
    c2_n_eml_scalar_eg(chartInstance);
    c2_xk = c2_b_x;
    c2_yk = c2_e_y;
    c2_c_x = c2_xk;
    c2_f_y = c2_yk;
    c2_n_eml_scalar_eg(chartInstance);
    c2_maxval = muDoubleScalarMax(c2_c_x, c2_f_y);
    c2_b_varargin_1 = c2_snorm;
    c2_c_varargin_2 = c2_maxval;
    c2_d_varargin_2 = c2_b_varargin_1;
    c2_b_varargin_3 = c2_c_varargin_2;
    c2_d_x = c2_d_varargin_2;
    c2_g_y = c2_b_varargin_3;
    c2_e_x = c2_d_x;
    c2_h_y = c2_g_y;
    c2_n_eml_scalar_eg(chartInstance);
    c2_b_xk = c2_e_x;
    c2_b_yk = c2_h_y;
    c2_f_x = c2_b_xk;
    c2_i_y = c2_b_yk;
    c2_n_eml_scalar_eg(chartInstance);
    c2_snorm = muDoubleScalarMax(c2_f_x, c2_i_y);
  }

  exitg1 = FALSE;
  while ((exitg1 == 0U) && ((real_T)c2_m > 0.0)) {
    if (c2_iter >= 75.0) {
      c2_d_eml_error(chartInstance);
      exitg1 = TRUE;
    } else {
      c2_n_a = c2_m - 1;
      c2_b_q = c2_n_a;
      c2_o_a = c2_m - 1;
      c2_i1301 = c2_o_a;
      c2_l_eml_int_forloop_overflow_check(chartInstance, c2_i1301);
      c2_d_ii = c2_i1301;
      guard3 = FALSE;
      guard4 = FALSE;
      exitg5 = FALSE;
      while ((exitg5 == 0U) && (c2_d_ii > -1)) {
        c2_b_ii = c2_d_ii;
        c2_b_q = c2_b_ii;
        if ((real_T)c2_b_ii == 0.0) {
          exitg5 = TRUE;
        } else {
          c2_p_a = c2_b_ii + 1;
          c2_j_c = c2_p_a;
          c2_test0 = c2_abs(chartInstance, c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("",
                             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_ii), 1,
            32, 1, 0) - 1]) + c2_abs(chartInstance,
            c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                                       (real_T)c2_j_c), 1, 32, 1, 0) - 1]);
          c2_ztest0 = c2_abs(chartInstance, c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("",
                              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_ii),
            1, 32, 1, 0) - 1]);
          c2_eps(chartInstance);
          c2_l_b = c2_test0;
          c2_j_y = 2.2204460492503131E-16 * c2_l_b;
          if (c2_ztest0 <= c2_j_y) {
            guard4 = TRUE;
            exitg5 = TRUE;
          } else if (c2_ztest0 <= c2_tiny) {
            guard4 = TRUE;
            exitg5 = TRUE;
          } else {
            guard11 = FALSE;
            if (c2_iter > 20.0) {
              c2_eps(chartInstance);
              c2_m_b = c2_snorm;
              c2_k_y = 2.2204460492503131E-16 * c2_m_b;
              if (c2_ztest0 <= c2_k_y) {
                guard3 = TRUE;
                exitg5 = TRUE;
              } else {
                guard11 = TRUE;
              }
            } else {
              guard11 = TRUE;
            }

            if (guard11 == TRUE) {
              c2_d_ii--;
              guard3 = FALSE;
              guard4 = FALSE;
            }
          }
        }
      }

      if (guard4 == TRUE) {
        guard3 = TRUE;
      }

      if (guard3 == TRUE) {
        c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_ii), 1, 32, 1, 0) - 1] = 0.0;
      }

      c2_q_a = c2_m - 1;
      c2_k_c = c2_q_a;
      if (c2_b_q == c2_k_c) {
        c2_kase = 4.0;
      } else {
        c2_qs = c2_m;
        c2_b_m = c2_m;
        c2_m_eml_int_forloop_overflow_check(chartInstance, c2_b_m, c2_b_q);
        c2_e_ii = c2_b_m;
        guard2 = FALSE;
        exitg4 = FALSE;
        while ((exitg4 == 0U) && (c2_e_ii >= c2_b_q)) {
          c2_b_ii = c2_e_ii;
          c2_qs = c2_b_ii;
          if (c2_b_ii == c2_b_q) {
            exitg4 = TRUE;
          } else {
            c2_test = 0.0;
            if (c2_b_ii < c2_m) {
              c2_test = c2_abs(chartInstance, c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_ii), 1, 32, 1,
                0) - 1]);
            }

            c2_r_a = c2_b_q + 1;
            c2_l_c = c2_r_a;
            if (c2_b_ii > c2_l_c) {
              c2_s_a = c2_b_ii - 1;
              c2_m_c = c2_s_a;
              c2_test += c2_abs(chartInstance, c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_m_c), 1, 32, 1, 0)
                                - 1]);
            }

            c2_ztest = c2_abs(chartInstance, c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("",
                               (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_ii),
              1, 32, 1, 0) - 1]);
            c2_eps(chartInstance);
            c2_n_b = c2_test;
            c2_l_y = 2.2204460492503131E-16 * c2_n_b;
            if (c2_ztest <= c2_l_y) {
              guard2 = TRUE;
              exitg4 = TRUE;
            } else if (c2_ztest <= c2_tiny) {
              guard2 = TRUE;
              exitg4 = TRUE;
            } else {
              c2_e_ii--;
              guard2 = FALSE;
            }
          }
        }

        if (guard2 == TRUE) {
          c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_ii), 1, 32, 1, 0) - 1] = 0.0;
        }

        if (c2_qs == c2_b_q) {
          c2_kase = 3.0;
        } else if (c2_qs == c2_m) {
          c2_kase = 1.0;
        } else {
          c2_kase = 2.0;
          c2_b_q = c2_qs;
        }
      }

      c2_t_a = c2_b_q + 1;
      c2_b_q = c2_t_a;
      switch ((int32_T)_SFD_INTEGER_CHECK("", c2_kase)) {
       case 1:
        c2_u_a = c2_m - 1;
        c2_n_c = c2_u_a;
        c2_f = c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_n_c), 1, 32, 1, 0) - 1];
        c2_v_a = c2_m - 1;
        c2_o_c = c2_v_a;
        c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_o_c), 1, 32, 1, 0) - 1] = 0.0;
        c2_w_a = c2_m - 1;
        c2_i1302 = c2_w_a;
        c2_m_eml_int_forloop_overflow_check(chartInstance, c2_i1302, c2_b_q);
        for (c2_k = c2_i1302; c2_k >= c2_b_q; c2_k--) {
          c2_b_k = c2_k;
          c2_t1 = c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 32, 1, 0) - 1];
          c2_b_t1 = c2_t1;
          c2_b_f = c2_f;
          c2_b_eml_xrotg(chartInstance, &c2_b_t1, &c2_b_f, &c2_cs, &c2_sn);
          c2_t1 = c2_b_t1;
          c2_f = c2_b_f;
          c2_b_cs = c2_cs;
          c2_b_sn = c2_sn;
          c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_k), 1, 32, 1, 0) - 1] = c2_t1;
          if (c2_b_k > c2_b_q) {
            c2_x_a = c2_b_k - 1;
            c2_km1 = c2_x_a;
            c2_y_a = -c2_b_sn;
            c2_o_b = c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c2_km1), 1, 32, 1, 0) - 1];
            c2_f = c2_y_a * c2_o_b;
            c2_ab_a = c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c2_km1), 1, 32, 1, 0) - 1];
            c2_p_b = c2_b_cs;
            c2_m_y = c2_ab_a * c2_p_b;
            c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_km1), 1, 32, 1, 0) - 1] = c2_m_y;
          }
        }
        break;

       case 2:
        c2_bb_a = c2_b_q - 1;
        c2_qm1 = c2_bb_a;
        c2_f = c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_qm1), 1, 32, 1, 0) - 1];
        c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_qm1), 1, 32, 1, 0) - 1] = 0.0;
        c2_d_q = c2_b_q;
        c2_i_eml_int_forloop_overflow_check(chartInstance, c2_d_q, c2_m);
        for (c2_c_k = c2_d_q; c2_c_k <= c2_m; c2_c_k++) {
          c2_b_k = c2_c_k;
          c2_t1 = c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 32, 1, 0) - 1];
          c2_c_t1 = c2_t1;
          c2_unusedU0 = c2_f;
          c2_b_eml_xrotg(chartInstance, &c2_c_t1, &c2_unusedU0, &c2_c_cs,
                         &c2_c_sn);
          c2_t1 = c2_c_t1;
          c2_b_cs = c2_c_cs;
          c2_b_sn = c2_c_sn;
          c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_k), 1, 32, 1, 0) - 1] = c2_t1;
          c2_cb_a = -c2_b_sn;
          c2_q_b = c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 32, 1, 0) - 1];
          c2_f = c2_cb_a * c2_q_b;
          c2_db_a = c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 32, 1, 0) - 1];
          c2_r_b = c2_b_cs;
          c2_n_y = c2_db_a * c2_r_b;
          c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_k), 1, 32, 1, 0) - 1] = c2_n_y;
        }
        break;

       case 3:
        c2_eb_a = c2_m - 1;
        c2_mm1 = c2_eb_a;
        c2_d6 = c2_abs(chartInstance, c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 32, 1, 0) - 1]);
        c2_d7 = c2_abs(chartInstance, c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 32, 1, 0) - 1]);
        c2_d8 = c2_abs(chartInstance, c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 32, 1, 0) - 1]);
        c2_d9 = c2_abs(chartInstance, c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_q), 1, 32, 1, 0) - 1]);
        c2_d10 = c2_abs(chartInstance, c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_q), 1, 32, 1, 0) - 1]);
        c2_c_varargin_1[0] = c2_d6;
        c2_c_varargin_1[1] = c2_d7;
        c2_c_varargin_1[2] = c2_d8;
        c2_c_varargin_1[3] = c2_d9;
        c2_c_varargin_1[4] = c2_d10;
        c2_ixstart = 1;
        c2_mtmp = c2_c_varargin_1[0];
        c2_g_x = c2_mtmp;
        c2_s_b = muDoubleScalarIsNaN(c2_g_x);
        if (c2_s_b) {
          c2_i_eml_int_forloop_overflow_check(chartInstance, 2, 5);
          c2_ix = 2;
          exitg2 = FALSE;
          while ((exitg2 == 0U) && (c2_ix < 6)) {
            c2_b_ix = c2_ix;
            c2_ixstart = c2_b_ix;
            c2_h_x = c2_c_varargin_1[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c2_b_ix), 1, 5, 1, 0) - 1];
            c2_t_b = muDoubleScalarIsNaN(c2_h_x);
            if (!c2_t_b) {
              c2_mtmp = c2_c_varargin_1[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_b_ix), 1, 5, 1, 0) - 1];
              exitg2 = TRUE;
            } else {
              c2_ix++;
            }
          }
        }

        if (c2_ixstart < 5) {
          c2_fb_a = c2_ixstart + 1;
          c2_i1303 = c2_fb_a;
          c2_i_eml_int_forloop_overflow_check(chartInstance, c2_i1303, 5);
          for (c2_c_ix = c2_i1303; c2_c_ix < 6; c2_c_ix++) {
            c2_b_ix = c2_c_ix;
            c2_gb_a = c2_c_varargin_1[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c2_b_ix), 1, 5, 1, 0) - 1];
            c2_u_b = c2_mtmp;
            c2_p = (c2_gb_a > c2_u_b);
            if (c2_p) {
              c2_mtmp = c2_c_varargin_1[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_b_ix), 1, 5, 1, 0) - 1];
            }
          }
        }

        c2_b_mtmp = c2_mtmp;
        c2_scale = c2_b_mtmp;
        c2_sm = c2_eml_div(chartInstance, c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 32, 1, 0) - 1],
                           c2_scale);
        c2_smm1 = c2_eml_div(chartInstance, c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("",
                              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1,
          32, 1, 0) - 1], c2_scale);
        c2_emm1 = c2_eml_div(chartInstance, c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("",
                              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1,
          32, 1, 0) - 1], c2_scale);
        c2_sqds = c2_eml_div(chartInstance, c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("",
                              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_q), 1,
          32, 1, 0) - 1], c2_scale);
        c2_eqds = c2_eml_div(chartInstance, c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("",
                              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_q), 1,
          32, 1, 0) - 1], c2_scale);
        c2_hb_a = c2_smm1 + c2_sm;
        c2_v_b = c2_smm1 - c2_sm;
        c2_o_y = c2_hb_a * c2_v_b;
        c2_ib_a = c2_emm1;
        c2_w_b = c2_emm1;
        c2_p_y = c2_ib_a * c2_w_b;
        c2_x_b = c2_eml_div(chartInstance, c2_o_y + c2_p_y, 2.0);
        c2_jb_a = c2_sm;
        c2_y_b = c2_emm1;
        c2_p_c = c2_jb_a * c2_y_b;
        c2_kb_a = c2_p_c;
        c2_ab_b = c2_p_c;
        c2_p_c = c2_kb_a * c2_ab_b;
        c2_shift = 0.0;
        guard1 = FALSE;
        if (c2_x_b != 0.0) {
          guard1 = TRUE;
        } else {
          if (c2_p_c != 0.0) {
            guard1 = TRUE;
          }
        }

        if (guard1 == TRUE) {
          c2_lb_a = c2_x_b;
          c2_bb_b = c2_x_b;
          c2_q_y = c2_lb_a * c2_bb_b;
          c2_shift = c2_q_y + c2_p_c;
          c2_b_sqrt(chartInstance, &c2_shift);
          if (c2_x_b < 0.0) {
            c2_shift = -c2_shift;
          }

          c2_shift = c2_eml_div(chartInstance, c2_p_c, c2_x_b + c2_shift);
        }

        c2_mb_a = c2_sqds + c2_sm;
        c2_cb_b = c2_sqds - c2_sm;
        c2_r_y = c2_mb_a * c2_cb_b;
        c2_f = c2_r_y + c2_shift;
        c2_nb_a = c2_sqds;
        c2_db_b = c2_eqds;
        c2_g = c2_nb_a * c2_db_b;
        c2_e_q = c2_b_q;
        c2_i_eml_int_forloop_overflow_check(chartInstance, c2_e_q, c2_mm1);
        for (c2_d_k = c2_e_q; c2_d_k <= c2_mm1; c2_d_k++) {
          c2_b_k = c2_d_k;
          c2_ob_a = c2_b_k - 1;
          c2_km1 = c2_ob_a;
          c2_pb_a = c2_b_k + 1;
          c2_kp1 = c2_pb_a;
          c2_c_f = c2_f;
          c2_unusedU1 = c2_g;
          c2_b_eml_xrotg(chartInstance, &c2_c_f, &c2_unusedU1, &c2_d_cs,
                         &c2_d_sn);
          c2_f = c2_c_f;
          c2_b_cs = c2_d_cs;
          c2_b_sn = c2_d_sn;
          if (c2_b_k > c2_b_q) {
            c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_km1), 1, 32, 1, 0) - 1] = c2_f;
          }

          c2_qb_a = c2_b_cs;
          c2_eb_b = c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 32, 1, 0) - 1];
          c2_s_y = c2_qb_a * c2_eb_b;
          c2_rb_a = c2_b_sn;
          c2_fb_b = c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 32, 1, 0) - 1];
          c2_t_y = c2_rb_a * c2_fb_b;
          c2_f = c2_s_y + c2_t_y;
          c2_sb_a = c2_b_cs;
          c2_gb_b = c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 32, 1, 0) - 1];
          c2_u_y = c2_sb_a * c2_gb_b;
          c2_tb_a = c2_b_sn;
          c2_hb_b = c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 32, 1, 0) - 1];
          c2_v_y = c2_tb_a * c2_hb_b;
          c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_k), 1, 32, 1, 0) - 1] = c2_u_y - c2_v_y;
          c2_ub_a = c2_b_sn;
          c2_ib_b = c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_kp1), 1, 32, 1, 0) - 1];
          c2_g = c2_ub_a * c2_ib_b;
          c2_vb_a = c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_kp1), 1, 32, 1, 0) - 1];
          c2_jb_b = c2_b_cs;
          c2_w_y = c2_vb_a * c2_jb_b;
          c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_kp1), 1, 32, 1, 0) - 1] = c2_w_y;
          c2_d_f = c2_f;
          c2_unusedU2 = c2_g;
          c2_b_eml_xrotg(chartInstance, &c2_d_f, &c2_unusedU2, &c2_e_cs,
                         &c2_e_sn);
          c2_f = c2_d_f;
          c2_b_cs = c2_e_cs;
          c2_b_sn = c2_e_sn;
          c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_k), 1, 32, 1, 0) - 1] = c2_f;
          c2_wb_a = c2_b_cs;
          c2_kb_b = c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 32, 1, 0) - 1];
          c2_x_y = c2_wb_a * c2_kb_b;
          c2_xb_a = c2_b_sn;
          c2_lb_b = c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_kp1), 1, 32, 1, 0) - 1];
          c2_y_y = c2_xb_a * c2_lb_b;
          c2_f = c2_x_y + c2_y_y;
          c2_yb_a = -c2_b_sn;
          c2_mb_b = c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 32, 1, 0) - 1];
          c2_ab_y = c2_yb_a * c2_mb_b;
          c2_ac_a = c2_b_cs;
          c2_nb_b = c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_kp1), 1, 32, 1, 0) - 1];
          c2_bb_y = c2_ac_a * c2_nb_b;
          c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_kp1), 1, 32, 1, 0) - 1] = c2_ab_y + c2_bb_y;
          c2_bc_a = c2_b_sn;
          c2_ob_b = c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_kp1), 1, 32, 1, 0) - 1];
          c2_g = c2_bc_a * c2_ob_b;
          c2_cc_a = c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_kp1), 1, 32, 1, 0) - 1];
          c2_pb_b = c2_b_cs;
          c2_cb_y = c2_cc_a * c2_pb_b;
          c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_kp1), 1, 32, 1, 0) - 1] = c2_cb_y;
        }

        c2_dc_a = c2_m - 1;
        c2_q_c = c2_dc_a;
        c2_e[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_q_c), 1, 32, 1, 0) - 1] = c2_f;
        c2_iter++;
        break;

       default:
        if (c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_q), 1, 32, 1, 0) - 1] < 0.0) {
          c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_q), 1, 32, 1, 0) - 1] =
            -c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_q), 1, 32, 1, 0) - 1];
        }

        c2_ec_a = c2_b_q + 1;
        c2_qp1 = c2_ec_a;
        exitg3 = FALSE;
        while ((exitg3 == 0U) && (c2_b_q < 32)) {
          if (c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                "", (real_T)c2_b_q), 1, 32, 1, 0) - 1] <
              c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                "", (real_T)c2_qp1), 1, 32, 1, 0) - 1]) {
            c2_rt = c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c2_b_q), 1, 32, 1, 0) - 1];
            c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_q), 1, 32, 1, 0) - 1] =
              c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
              "", (real_T)c2_qp1), 1, 32, 1, 0) - 1];
            c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_qp1), 1, 32, 1, 0) - 1] = c2_rt;
            c2_b_q = c2_qp1;
            c2_gc_a = c2_b_q + 1;
            c2_qp1 = c2_gc_a;
          } else {
            exitg3 = TRUE;
          }
        }

        c2_iter = 0.0;
        c2_fc_a = c2_m - 1;
        c2_m = c2_fc_a;
        break;
      }
    }
  }

  c2_eml_int_forloop_overflow_check(chartInstance);
  for (c2_e_k = 1; c2_e_k < 33; c2_e_k++) {
    c2_b_k = c2_e_k;
    c2_S[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_b_k), 1, 32, 1, 0) - 1] = c2_s[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 32, 1, 0) - 1];
  }
}

static real_T c2_eml_xnrm2(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[1024], int32_T c2_ix0)
{
  real_T c2_y;
  int32_T c2_b_n;
  int32_T c2_b_ix0;
  int32_T c2_c_n;
  int32_T c2_c_ix0;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_scale;
  int32_T c2_kstart;
  int32_T c2_a;
  int32_T c2_c;
  int32_T c2_b_a;
  int32_T c2_b_c;
  int32_T c2_c_a;
  int32_T c2_b;
  int32_T c2_kend;
  int32_T c2_b_kstart;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_absxk;
  real_T c2_t;
  c2_b_n = c2_n;
  c2_b_ix0 = c2_ix0;
  c2_c_n = c2_b_n;
  c2_c_ix0 = c2_b_ix0;
  c2_y = 0.0;
  if ((real_T)c2_c_n < 1.0) {
  } else if ((real_T)c2_c_n == 1.0) {
    c2_b_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_c_ix0), 1, 1024, 1, 0) - 1];
    c2_c_x = c2_b_x;
    c2_y = muDoubleScalarAbs(c2_c_x);
  } else {
    c2_eml_realmin(chartInstance);
    c2_scale = 2.2250738585072014E-308;
    c2_kstart = c2_c_ix0;
    c2_a = c2_c_n;
    c2_c = c2_a;
    c2_b_a = c2_c - 1;
    c2_b_c = c2_b_a;
    c2_c_a = c2_kstart;
    c2_b = c2_b_c;
    c2_kend = c2_c_a + c2_b;
    c2_b_kstart = c2_kstart;
    c2_i_eml_int_forloop_overflow_check(chartInstance, c2_b_kstart, c2_kend);
    for (c2_k = c2_b_kstart; c2_k <= c2_kend; c2_k++) {
      c2_b_k = c2_k;
      c2_d_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c2_b_k), 1, 1024, 1, 0) - 1];
      c2_e_x = c2_d_x;
      c2_absxk = muDoubleScalarAbs(c2_e_x);
      if (c2_absxk > c2_scale) {
        c2_t = c2_scale / c2_absxk;
        c2_y = 1.0 + c2_y * c2_t * c2_t;
        c2_scale = c2_absxk;
      } else {
        c2_t = c2_absxk / c2_scale;
        c2_y += c2_t * c2_t;
      }
    }

    c2_y = c2_scale * muDoubleScalarSqrt(c2_y);
  }

  return c2_y;
}

static void c2_eml_xscal(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[1024], int32_T c2_ix0,
  real_T c2_b_x[1024])
{
  int32_T c2_i1304;
  for (c2_i1304 = 0; c2_i1304 < 1024; c2_i1304++) {
    c2_b_x[c2_i1304] = c2_x[c2_i1304];
  }

  c2_c_eml_xscal(chartInstance, c2_n, c2_a, c2_b_x, c2_ix0);
}

static real_T c2_eml_xdotc(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[1024], int32_T c2_ix0, real_T c2_y
  [1024], int32_T c2_iy0)
{
  real_T c2_d;
  int32_T c2_b_n;
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  int32_T c2_c_n;
  int32_T c2_c_ix0;
  int32_T c2_c_iy0;
  int32_T c2_d_n;
  int32_T c2_d_ix0;
  int32_T c2_d_iy0;
  int32_T c2_e_n;
  int32_T c2_e_ix0;
  int32_T c2_e_iy0;
  int32_T c2_ix;
  int32_T c2_iy;
  int32_T c2_loop_ub;
  int32_T c2_k;
  int32_T c2_a;
  int32_T c2_b_a;
  c2_b_n = c2_n;
  c2_b_ix0 = c2_ix0;
  c2_b_iy0 = c2_iy0;
  c2_c_n = c2_b_n;
  c2_c_ix0 = c2_b_ix0;
  c2_c_iy0 = c2_b_iy0;
  c2_d_n = c2_c_n;
  c2_d_ix0 = c2_c_ix0;
  c2_d_iy0 = c2_c_iy0;
  c2_e_n = c2_d_n;
  c2_e_ix0 = c2_d_ix0;
  c2_e_iy0 = c2_d_iy0;
  c2_db_eml_scalar_eg(chartInstance);
  c2_d = 0.0;
  if ((real_T)c2_e_n < 1.0) {
  } else {
    c2_ix = c2_e_ix0;
    c2_iy = c2_e_iy0;
    c2_h_eml_int_forloop_overflow_check(chartInstance, c2_e_n);
    c2_loop_ub = c2_e_n;
    for (c2_k = 1; c2_k <= c2_loop_ub; c2_k++) {
      c2_d += c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c2_ix), 1, 1024, 1, 0) - 1] *
        c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_iy), 1, 1024, 1, 0) - 1];
      c2_a = c2_ix + 1;
      c2_ix = c2_a;
      c2_b_a = c2_iy + 1;
      c2_iy = c2_b_a;
    }
  }

  return c2_d;
}

static void c2_db_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_eml_xaxpy(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, int32_T c2_ix0, real_T c2_y[1024],
  int32_T c2_iy0, real_T c2_b_y[1024])
{
  int32_T c2_i1305;
  for (c2_i1305 = 0; c2_i1305 < 1024; c2_i1305++) {
    c2_b_y[c2_i1305] = c2_y[c2_i1305];
  }

  c2_d_eml_xaxpy(chartInstance, c2_n, c2_a, c2_ix0, c2_b_y, c2_iy0);
}

static real_T c2_b_eml_xnrm2(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[32], int32_T c2_ix0)
{
  real_T c2_y;
  int32_T c2_b_n;
  int32_T c2_b_ix0;
  int32_T c2_c_n;
  int32_T c2_c_ix0;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_scale;
  int32_T c2_kstart;
  int32_T c2_a;
  int32_T c2_c;
  int32_T c2_b_a;
  int32_T c2_b_c;
  int32_T c2_c_a;
  int32_T c2_b;
  int32_T c2_kend;
  int32_T c2_b_kstart;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_absxk;
  real_T c2_t;
  c2_b_n = c2_n;
  c2_b_ix0 = c2_ix0;
  c2_c_n = c2_b_n;
  c2_c_ix0 = c2_b_ix0;
  c2_y = 0.0;
  if ((real_T)c2_c_n < 1.0) {
  } else if ((real_T)c2_c_n == 1.0) {
    c2_b_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_c_ix0), 1, 32, 1, 0) - 1];
    c2_c_x = c2_b_x;
    c2_y = muDoubleScalarAbs(c2_c_x);
  } else {
    c2_eml_realmin(chartInstance);
    c2_scale = 2.2250738585072014E-308;
    c2_kstart = c2_c_ix0;
    c2_a = c2_c_n;
    c2_c = c2_a;
    c2_b_a = c2_c - 1;
    c2_b_c = c2_b_a;
    c2_c_a = c2_kstart;
    c2_b = c2_b_c;
    c2_kend = c2_c_a + c2_b;
    c2_b_kstart = c2_kstart;
    c2_i_eml_int_forloop_overflow_check(chartInstance, c2_b_kstart, c2_kend);
    for (c2_k = c2_b_kstart; c2_k <= c2_kend; c2_k++) {
      c2_b_k = c2_k;
      c2_d_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c2_b_k), 1, 32, 1, 0) - 1];
      c2_e_x = c2_d_x;
      c2_absxk = muDoubleScalarAbs(c2_e_x);
      if (c2_absxk > c2_scale) {
        c2_t = c2_scale / c2_absxk;
        c2_y = 1.0 + c2_y * c2_t * c2_t;
        c2_scale = c2_absxk;
      } else {
        c2_t = c2_absxk / c2_scale;
        c2_y += c2_t * c2_t;
      }
    }

    c2_y = c2_scale * muDoubleScalarSqrt(c2_y);
  }

  return c2_y;
}

static void c2_b_eml_xscal(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[32], int32_T c2_ix0,
  real_T c2_b_x[32])
{
  int32_T c2_i1306;
  for (c2_i1306 = 0; c2_i1306 < 32; c2_i1306++) {
    c2_b_x[c2_i1306] = c2_x[c2_i1306];
  }

  c2_d_eml_xscal(chartInstance, c2_n, c2_a, c2_b_x, c2_ix0);
}

static void c2_b_eml_xaxpy(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[1024], int32_T c2_ix0,
  real_T c2_y[32], int32_T c2_iy0, real_T c2_b_y[32])
{
  int32_T c2_i1307;
  int32_T c2_i1308;
  real_T c2_b_x[1024];
  for (c2_i1307 = 0; c2_i1307 < 32; c2_i1307++) {
    c2_b_y[c2_i1307] = c2_y[c2_i1307];
  }

  for (c2_i1308 = 0; c2_i1308 < 1024; c2_i1308++) {
    c2_b_x[c2_i1308] = c2_x[c2_i1308];
  }

  c2_e_eml_xaxpy(chartInstance, c2_n, c2_a, c2_b_x, c2_ix0, c2_b_y, c2_iy0);
}

static void c2_c_eml_xaxpy(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[32], int32_T c2_ix0,
  real_T c2_y[1024], int32_T c2_iy0, real_T c2_b_y[1024])
{
  int32_T c2_i1309;
  int32_T c2_i1310;
  real_T c2_b_x[32];
  for (c2_i1309 = 0; c2_i1309 < 1024; c2_i1309++) {
    c2_b_y[c2_i1309] = c2_y[c2_i1309];
  }

  for (c2_i1310 = 0; c2_i1310 < 32; c2_i1310++) {
    c2_b_x[c2_i1310] = c2_x[c2_i1310];
  }

  c2_f_eml_xaxpy(chartInstance, c2_n, c2_a, c2_b_x, c2_ix0, c2_b_y, c2_iy0);
}

static void c2_d_eml_error(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
  int32_T c2_i1311;
  static char_T c2_varargin_1[30] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'v', 'd', '_', 'N', 'o', 'C', 'o', 'n', 'v',
    'e', 'r', 'g', 'e', 'n', 'c', 'e' };

  char_T c2_u[30];
  const mxArray *c2_y = NULL;
  for (c2_i1311 = 0; c2_i1311 < 30; c2_i1311++) {
    c2_u[c2_i1311] = c2_varargin_1[c2_i1311];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 30), FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c2_y));
}

static void c2_l_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, int32_T c2_a)
{
  boolean_T c2_overflow;
  boolean_T c2_safe;
  int32_T c2_i1312;
  static char_T c2_cv6[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  char_T c2_u[34];
  const mxArray *c2_y = NULL;
  int32_T c2_i1313;
  static char_T c2_cv7[5] = { 'i', 'n', 't', '3', '2' };

  char_T c2_b_u[5];
  const mxArray *c2_b_y = NULL;
  c2_overflow = FALSE;
  c2_safe = !c2_overflow;
  if (c2_safe) {
  } else {
    for (c2_i1312 = 0; c2_i1312 < 34; c2_i1312++) {
      c2_u[c2_i1312] = c2_cv6[c2_i1312];
    }

    c2_y = NULL;
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 34),
                  FALSE);
    for (c2_i1313 = 0; c2_i1313 < 5; c2_i1313++) {
      c2_b_u[c2_i1313] = c2_cv7[c2_i1313];
    }

    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 5),
                  FALSE);
    sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
      14, c2_y, 14, c2_b_y));
  }
}

static void c2_m_eml_int_forloop_overflow_check
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, int32_T c2_a,
   int32_T c2_b)
{
  int32_T c2_b_a;
  int32_T c2_b_b;
  boolean_T c2_overflow;
  boolean_T c2_safe;
  int32_T c2_i1314;
  static char_T c2_cv8[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  char_T c2_u[34];
  const mxArray *c2_y = NULL;
  int32_T c2_i1315;
  static char_T c2_cv9[5] = { 'i', 'n', 't', '3', '2' };

  char_T c2_b_u[5];
  const mxArray *c2_b_y = NULL;
  c2_b_a = c2_a;
  c2_b_b = c2_b;
  if (c2_b_a < c2_b_b) {
    c2_overflow = FALSE;
  } else {
    c2_overflow = (c2_b_b < -2147483647);
  }

  c2_safe = !c2_overflow;
  if (c2_safe) {
  } else {
    for (c2_i1314 = 0; c2_i1314 < 34; c2_i1314++) {
      c2_u[c2_i1314] = c2_cv8[c2_i1314];
    }

    c2_y = NULL;
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 34),
                  FALSE);
    for (c2_i1315 = 0; c2_i1315 < 5; c2_i1315++) {
      c2_b_u[c2_i1315] = c2_cv9[c2_i1315];
    }

    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 5),
                  FALSE);
    sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
      14, c2_y, 14, c2_b_y));
  }
}

static real_T c2_sqrt(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_x)
{
  real_T c2_b_x;
  c2_b_x = c2_x;
  c2_b_sqrt(chartInstance, &c2_b_x);
  return c2_b_x;
}

static void c2_e_eml_error(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
  int32_T c2_i1316;
  static char_T c2_varargin_1[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o',
    'o', 'l', 'b', 'o', 'x', ':', 's', 'q', 'r', 't', '_', 'd', 'o', 'm', 'a',
    'i', 'n', 'E', 'r', 'r', 'o', 'r' };

  char_T c2_u[30];
  const mxArray *c2_y = NULL;
  for (c2_i1316 = 0; c2_i1316 < 30; c2_i1316++) {
    c2_u[c2_i1316] = c2_varargin_1[c2_i1316];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 30), FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c2_y));
}

static void c2_eml_xrotg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_a, real_T c2_b, real_T *c2_b_a, real_T *c2_b_b,
  real_T *c2_c, real_T *c2_s)
{
  *c2_b_a = c2_a;
  *c2_b_b = c2_b;
  c2_b_eml_xrotg(chartInstance, c2_b_a, c2_b_b, c2_c, c2_s);
}

static void c2_eb_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_getSqBlk(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_U[1024], real_T c2_Y[9])
{
  uint32_T c2_debug_family_var_map[7];
  real_T c2_ii;
  real_T c2_jj;
  real_T c2_n;
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i1317;
  int32_T c2_i1318;
  int32_T c2_i1319;
  int32_T c2_i1320;
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c2_u_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_ii, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_jj, 1U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_n, 2U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 3U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 4U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_U, 5U, c2_n_sf_marshallOut,
    c2_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Y, 6U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  c2_ii = 1.0;
  c2_jj = 1.0;
  c2_n = 3.0;
  CV_EML_FCN(0, 4);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 743);
  c2_realmax(chartInstance);
  c2_realmax(chartInstance);
  c2_i1317 = 0;
  c2_i1318 = 0;
  for (c2_i1319 = 0; c2_i1319 < 3; c2_i1319++) {
    for (c2_i1320 = 0; c2_i1320 < 3; c2_i1320++) {
      c2_Y[c2_i1320 + c2_i1317] = c2_U[c2_i1320 + c2_i1318];
    }

    c2_i1317 += 3;
    c2_i1318 += 32;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -743);
  sf_debug_symbol_scope_pop();
}

static void c2_b_getSqBlk(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_U[1024], real_T c2_ii, real_T c2_jj, real_T c2_Y[9])
{
  uint32_T c2_debug_family_var_map[7];
  real_T c2_n;
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 1.0;
  real_T c2_a;
  real_T c2_y;
  real_T c2_b_a;
  real_T c2_b_y;
  int32_T c2_i1321;
  int32_T c2_i1322;
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c2_v_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_n, 0U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 1U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 2U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_U, 3U, c2_n_sf_marshallOut,
    c2_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_ii, 4U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_jj, 5U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Y, 6U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  c2_n = 3.0;
  CV_EML_FCN(0, 4);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 743);
  c2_realmax(chartInstance);
  c2_realmax(chartInstance);
  c2_a = c2_ii - 1.0;
  c2_y = c2_a * 3.0;
  c2_b_a = c2_jj - 1.0;
  c2_b_y = c2_b_a * 3.0;
  for (c2_i1321 = 0; c2_i1321 < 3; c2_i1321++) {
    for (c2_i1322 = 0; c2_i1322 < 3; c2_i1322++) {
      c2_Y[c2_i1322 + 3 * c2_i1321] = c2_U[(_SFD_EML_ARRAY_BOUNDS_CHECK("U",
        (int32_T)_SFD_INTEGER_CHECK("(ii-1)*n + (1:n)", c2_y + (1.0 + (real_T)
        c2_i1322)), 1, 32, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("U", (int32_T)
        _SFD_INTEGER_CHECK("(jj-1)*n + (1:n)", c2_b_y + (1.0 + (real_T)c2_i1321)),
        1, 32, 2, 0) - 1) << 5)) - 1];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -743);
  sf_debug_symbol_scope_pop();
}

static void c2_e_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_B[6], real_T c2_C[6])
{
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_i1323;
  real_T c2_b_A[9];
  int32_T c2_i1324;
  real_T c2_c_A[9];
  c2_x_eml_scalar_eg(chartInstance);
  c2_e_eml_int_forloop_overflow_check(chartInstance);
  for (c2_j = 1; c2_j < 3; c2_j++) {
    c2_b_j = c2_j;
    c2_b_eml_int_forloop_overflow_check(chartInstance);
    for (c2_i = 1; c2_i < 4; c2_i++) {
      c2_b_i = c2_i;
      c2_C[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 2, 2, 0) - 1))
        - 1] = c2_B[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                     (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 2, 2, 0) - 1)) - 1];
    }
  }

  for (c2_i1323 = 0; c2_i1323 < 9; c2_i1323++) {
    c2_b_A[c2_i1323] = c2_A[c2_i1323];
  }

  c2_b_eml_xtrsm(chartInstance, c2_b_A, c2_C);
  for (c2_i1324 = 0; c2_i1324 < 9; c2_i1324++) {
    c2_c_A[c2_i1324] = c2_A[c2_i1324];
  }

  if (c2_c_is_singular_triangular_matrix(chartInstance, c2_c_A)) {
    c2_eml_warning(chartInstance);
  }
}

static void c2_eml_xtrsm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_B[6], real_T c2_b_B[6])
{
  int32_T c2_i1325;
  int32_T c2_i1326;
  real_T c2_b_A[9];
  for (c2_i1325 = 0; c2_i1325 < 6; c2_i1325++) {
    c2_b_B[c2_i1325] = c2_B[c2_i1325];
  }

  for (c2_i1326 = 0; c2_i1326 < 9; c2_i1326++) {
    c2_b_A[c2_i1326] = c2_A[c2_i1326];
  }

  c2_b_eml_xtrsm(chartInstance, c2_b_A, c2_b_B);
}

static void c2_c_chol(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_A[4], real_T c2_b_A[4])
{
  int32_T c2_i1327;
  for (c2_i1327 = 0; c2_i1327 < 4; c2_i1327++) {
    c2_b_A[c2_i1327] = c2_A[c2_i1327];
  }

  c2_f_chol(chartInstance, c2_b_A);
}

static void c2_c_eml_matlab_zpotrf(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[4], real_T c2_b_A[4], int32_T *c2_info)
{
  int32_T c2_i1328;
  for (c2_i1328 = 0; c2_i1328 < 4; c2_i1328++) {
    c2_b_A[c2_i1328] = c2_A[c2_i1328];
  }

  *c2_info = c2_f_eml_matlab_zpotrf(chartInstance, c2_b_A);
}

static void c2_c_eml_xgemv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_ia0, int32_T c2_ix0,
  real_T c2_y[4], int32_T c2_iy0, real_T c2_b_y[4])
{
  int32_T c2_i1329;
  for (c2_i1329 = 0; c2_i1329 < 4; c2_i1329++) {
    c2_b_y[c2_i1329] = c2_y[c2_i1329];
  }

  c2_f_eml_xgemv(chartInstance, c2_m, c2_n, c2_ia0, c2_ix0, c2_b_y, c2_iy0);
}

static void c2_k_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1024], real_T c2_B[1024], real_T c2_C[1024],
  real_T c2_b_C[1024])
{
  int32_T c2_i1330;
  int32_T c2_i1331;
  real_T c2_b_A[1024];
  int32_T c2_i1332;
  real_T c2_b_B[1024];
  for (c2_i1330 = 0; c2_i1330 < 1024; c2_i1330++) {
    c2_b_C[c2_i1330] = c2_C[c2_i1330];
  }

  for (c2_i1331 = 0; c2_i1331 < 1024; c2_i1331++) {
    c2_b_A[c2_i1331] = c2_A[c2_i1331];
  }

  for (c2_i1332 = 0; c2_i1332 < 1024; c2_i1332++) {
    c2_b_B[c2_i1332] = c2_B[c2_i1332];
  }

  c2_x_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static void c2_f_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_B[3], real_T c2_C[3])
{
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_b;
  int32_T c2_c;
  int32_T c2_a;
  int32_T c2_b_c;
  int32_T c2_b_a;
  int32_T c2_c_c;
  int32_T c2_c_a;
  int32_T c2_b_b;
  int32_T c2_jjA;
  int32_T c2_d_a;
  int32_T c2_d_c;
  int32_T c2_e_a;
  int32_T c2_e_c;
  int32_T c2_c_b;
  int32_T c2_jx;
  real_T c2_x;
  real_T c2_y;
  real_T c2_z;
  int32_T c2_d_b;
  int32_T c2_i1333;
  int32_T c2_c_i;
  int32_T c2_d_i;
  int32_T c2_f_a;
  int32_T c2_f_c;
  int32_T c2_g_a;
  int32_T c2_e_b;
  int32_T c2_ix;
  int32_T c2_h_a;
  int32_T c2_f_b;
  int32_T c2_g_c;
  int32_T c2_i1334;
  real_T c2_b_A[9];
  c2_eml_scalar_eg(chartInstance);
  c2_b_eml_int_forloop_overflow_check(chartInstance);
  for (c2_i = 1; c2_i < 4; c2_i++) {
    c2_b_i = c2_i;
    c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_b_i), 1, 3, 1, 0) - 1] = c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) - 1];
  }

  c2_d_below_threshold(chartInstance);
  c2_b_eml_int_forloop_overflow_check(chartInstance);
  for (c2_j = 1; c2_j < 4; c2_j++) {
    c2_b_j = c2_j;
    c2_b = c2_b_j;
    c2_c = c2_b;
    c2_a = c2_b_j;
    c2_b_c = c2_a;
    c2_b_a = c2_b_c - 1;
    c2_c_c = c2_b_a * 3;
    c2_c_a = c2_c;
    c2_b_b = c2_c_c;
    c2_jjA = c2_c_a + c2_b_b;
    c2_d_a = c2_b_j;
    c2_d_c = c2_d_a;
    c2_e_a = c2_d_c - 1;
    c2_e_c = c2_e_a;
    c2_c_b = c2_e_c + 1;
    c2_jx = c2_c_b;
    c2_x = c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_jx), 1, 3, 1, 0) - 1];
    c2_y = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_jjA), 1, 9, 1, 0) - 1];
    c2_z = c2_x / c2_y;
    c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_jx), 1, 3, 1, 0) - 1] = c2_z;
    c2_d_b = c2_b_j;
    c2_i1333 = 3 - c2_d_b;
    c2_h_eml_int_forloop_overflow_check(chartInstance, c2_i1333);
    for (c2_c_i = 1; c2_c_i <= c2_i1333; c2_c_i++) {
      c2_d_i = c2_c_i;
      c2_f_a = c2_d_i;
      c2_f_c = c2_f_a;
      c2_g_a = c2_jx;
      c2_e_b = c2_f_c;
      c2_ix = c2_g_a + c2_e_b;
      c2_h_a = c2_jjA;
      c2_f_b = c2_d_i;
      c2_g_c = c2_h_a + c2_f_b;
      c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_ix), 1, 3, 1, 0) - 1] = c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_ix), 1, 3, 1, 0) - 1] -
        c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_jx), 1, 3, 1, 0) - 1] * c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_g_c), 1, 9, 1, 0) - 1];
    }
  }

  for (c2_i1334 = 0; c2_i1334 < 9; c2_i1334++) {
    c2_b_A[c2_i1334] = c2_A[c2_i1334];
  }

  if (c2_c_is_singular_triangular_matrix(chartInstance, c2_b_A)) {
    c2_eml_warning(chartInstance);
  }
}

static void c2_d_below_threshold(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_g_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[4], real_T c2_B[2], real_T c2_C[2])
{
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_b;
  int32_T c2_c;
  int32_T c2_a;
  int32_T c2_b_c;
  int32_T c2_b_a;
  int32_T c2_c_c;
  int32_T c2_c_a;
  int32_T c2_b_b;
  int32_T c2_jjA;
  int32_T c2_d_a;
  int32_T c2_d_c;
  int32_T c2_e_a;
  int32_T c2_e_c;
  int32_T c2_c_b;
  int32_T c2_jx;
  real_T c2_x;
  real_T c2_y;
  real_T c2_z;
  int32_T c2_d_b;
  int32_T c2_i1335;
  int32_T c2_c_i;
  int32_T c2_d_i;
  int32_T c2_f_a;
  int32_T c2_f_c;
  int32_T c2_g_a;
  int32_T c2_e_b;
  int32_T c2_ix;
  int32_T c2_h_a;
  int32_T c2_f_b;
  int32_T c2_g_c;
  int32_T c2_i1336;
  real_T c2_b_A[4];
  c2_fb_eml_scalar_eg(chartInstance);
  c2_e_eml_int_forloop_overflow_check(chartInstance);
  for (c2_i = 1; c2_i < 3; c2_i++) {
    c2_b_i = c2_i;
    c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_b_i), 1, 2, 1, 0) - 1] = c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 2, 1, 0) - 1];
  }

  c2_e_below_threshold(chartInstance);
  c2_e_eml_int_forloop_overflow_check(chartInstance);
  for (c2_j = 1; c2_j < 3; c2_j++) {
    c2_b_j = c2_j;
    c2_b = c2_b_j;
    c2_c = c2_b;
    c2_a = c2_b_j;
    c2_b_c = c2_a;
    c2_b_a = c2_b_c - 1;
    c2_c_c = c2_b_a << 1;
    c2_c_a = c2_c;
    c2_b_b = c2_c_c;
    c2_jjA = c2_c_a + c2_b_b;
    c2_d_a = c2_b_j;
    c2_d_c = c2_d_a;
    c2_e_a = c2_d_c - 1;
    c2_e_c = c2_e_a;
    c2_c_b = c2_e_c + 1;
    c2_jx = c2_c_b;
    c2_x = c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_jx), 1, 2, 1, 0) - 1];
    c2_y = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_jjA), 1, 4, 1, 0) - 1];
    c2_z = c2_x / c2_y;
    c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_jx), 1, 2, 1, 0) - 1] = c2_z;
    c2_d_b = c2_b_j;
    c2_i1335 = 2 - c2_d_b;
    c2_h_eml_int_forloop_overflow_check(chartInstance, c2_i1335);
    for (c2_c_i = 1; c2_c_i <= c2_i1335; c2_c_i++) {
      c2_d_i = c2_c_i;
      c2_f_a = c2_d_i;
      c2_f_c = c2_f_a;
      c2_g_a = c2_jx;
      c2_e_b = c2_f_c;
      c2_ix = c2_g_a + c2_e_b;
      c2_h_a = c2_jjA;
      c2_f_b = c2_d_i;
      c2_g_c = c2_h_a + c2_f_b;
      c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_ix), 1, 2, 1, 0) - 1] = c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_ix), 1, 2, 1, 0) - 1] -
        c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_jx), 1, 2, 1, 0) - 1] * c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_g_c), 1, 4, 1, 0) - 1];
    }
  }

  for (c2_i1336 = 0; c2_i1336 < 4; c2_i1336++) {
    c2_b_A[c2_i1336] = c2_A[c2_i1336];
  }

  if (c2_d_is_singular_triangular_matrix(chartInstance, c2_b_A)) {
    c2_eml_warning(chartInstance);
  }
}

static void c2_fb_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_e_below_threshold(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static boolean_T c2_d_is_singular_triangular_matrix
  (SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance, real_T c2_A[4])
{
  boolean_T c2_p;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_x;
  real_T c2_b_x;
  boolean_T c2_b;
  boolean_T c2_b9;
  real_T c2_c_x;
  boolean_T c2_b_b;
  boolean_T c2_b10;
  boolean_T c2_c_b;
  boolean_T guard1 = FALSE;
  int32_T exitg1;
  c2_e_eml_int_forloop_overflow_check(chartInstance);
  c2_k = 1;
  guard1 = FALSE;
  do {
    exitg1 = 0;
    if (c2_k < 3) {
      c2_b_k = c2_k;
      if (c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
             (real_T)c2_b_k), 1, 2, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 2, 2, 0) - 1) <<
            1)) - 1] == 0.0) {
        guard1 = TRUE;
        exitg1 = 1;
      } else {
        c2_x = c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_b_k), 1, 2, 1, 0) +
                     ((_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 2, 2, 0) - 1) << 1)) - 1];
        c2_b_x = c2_x;
        c2_b = muDoubleScalarIsInf(c2_b_x);
        c2_b9 = !c2_b;
        c2_c_x = c2_x;
        c2_b_b = muDoubleScalarIsNaN(c2_c_x);
        c2_b10 = !c2_b_b;
        c2_c_b = (c2_b9 && c2_b10);
        if (!c2_c_b) {
          guard1 = TRUE;
          exitg1 = 1;
        } else {
          c2_k++;
          guard1 = FALSE;
        }
      }
    } else {
      c2_p = FALSE;
      exitg1 = 1;
    }
  } while (exitg1 == 0U);

  if (guard1 == TRUE) {
    c2_p = TRUE;
  }

  return c2_p;
}

static void c2_gb_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_l_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1024], real_T c2_B[32], real_T c2_C[32], real_T
  c2_b_C[32])
{
  int32_T c2_i1337;
  int32_T c2_i1338;
  real_T c2_b_A[1024];
  int32_T c2_i1339;
  real_T c2_b_B[32];
  for (c2_i1337 = 0; c2_i1337 < 32; c2_i1337++) {
    c2_b_C[c2_i1337] = c2_C[c2_i1337];
  }

  for (c2_i1338 = 0; c2_i1338 < 1024; c2_i1338++) {
    c2_b_A[c2_i1338] = c2_A[c2_i1338];
  }

  for (c2_i1339 = 0; c2_i1339 < 32; c2_i1339++) {
    c2_b_B[c2_i1339] = c2_B[c2_i1339];
  }

  c2_y_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static void c2_h_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[4], real_T c2_B[2], real_T c2_C[2])
{
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_b;
  int32_T c2_c;
  int32_T c2_a;
  int32_T c2_b_c;
  int32_T c2_b_a;
  int32_T c2_c_c;
  int32_T c2_c_a;
  int32_T c2_b_b;
  int32_T c2_jjA;
  int32_T c2_d_a;
  int32_T c2_d_c;
  int32_T c2_e_a;
  int32_T c2_e_c;
  int32_T c2_c_b;
  int32_T c2_jx;
  real_T c2_x;
  real_T c2_y;
  real_T c2_z;
  int32_T c2_f_a;
  int32_T c2_i1340;
  int32_T c2_c_i;
  int32_T c2_d_i;
  int32_T c2_g_a;
  int32_T c2_f_c;
  int32_T c2_h_a;
  int32_T c2_d_b;
  int32_T c2_ix;
  int32_T c2_i_a;
  int32_T c2_e_b;
  int32_T c2_g_c;
  int32_T c2_i1341;
  real_T c2_b_A[4];
  c2_fb_eml_scalar_eg(chartInstance);
  c2_e_eml_int_forloop_overflow_check(chartInstance);
  for (c2_i = 1; c2_i < 3; c2_i++) {
    c2_b_i = c2_i;
    c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_b_i), 1, 2, 1, 0) - 1] = c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 2, 1, 0) - 1];
  }

  c2_e_below_threshold(chartInstance);
  c2_m_eml_int_forloop_overflow_check(chartInstance, 2, 1);
  for (c2_j = 2; c2_j > 0; c2_j--) {
    c2_b_j = c2_j;
    c2_b = c2_b_j;
    c2_c = c2_b;
    c2_a = c2_b_j;
    c2_b_c = c2_a;
    c2_b_a = c2_b_c - 1;
    c2_c_c = c2_b_a << 1;
    c2_c_a = c2_c;
    c2_b_b = c2_c_c;
    c2_jjA = c2_c_a + c2_b_b;
    c2_d_a = c2_b_j;
    c2_d_c = c2_d_a;
    c2_e_a = c2_d_c - 1;
    c2_e_c = c2_e_a;
    c2_c_b = c2_e_c + 1;
    c2_jx = c2_c_b;
    c2_x = c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_jx), 1, 2, 1, 0) - 1];
    c2_y = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_jjA), 1, 4, 1, 0) - 1];
    c2_z = c2_x / c2_y;
    c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_jx), 1, 2, 1, 0) - 1] = c2_z;
    c2_f_a = c2_b_j - 1;
    c2_i1340 = c2_f_a;
    c2_h_eml_int_forloop_overflow_check(chartInstance, c2_i1340);
    for (c2_c_i = 1; c2_c_i <= c2_i1340; c2_c_i++) {
      c2_d_i = c2_c_i;
      c2_g_a = c2_d_i;
      c2_f_c = c2_g_a;
      c2_h_a = c2_jx;
      c2_d_b = c2_f_c;
      c2_ix = c2_h_a - c2_d_b;
      c2_i_a = c2_jjA;
      c2_e_b = c2_d_i;
      c2_g_c = c2_i_a - c2_e_b;
      c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_ix), 1, 2, 1, 0) - 1] = c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_ix), 1, 2, 1, 0) - 1] -
        c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_jx), 1, 2, 1, 0) - 1] * c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_g_c), 1, 4, 1, 0) - 1];
    }
  }

  for (c2_i1341 = 0; c2_i1341 < 4; c2_i1341++) {
    c2_b_A[c2_i1341] = c2_A[c2_i1341];
  }

  if (c2_d_is_singular_triangular_matrix(chartInstance, c2_b_A)) {
    c2_eml_warning(chartInstance);
  }
}

static void c2_i_linsolve(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_B[3], real_T c2_C[3])
{
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_b;
  int32_T c2_c;
  int32_T c2_a;
  int32_T c2_b_c;
  int32_T c2_b_a;
  int32_T c2_c_c;
  int32_T c2_c_a;
  int32_T c2_b_b;
  int32_T c2_jjA;
  int32_T c2_d_a;
  int32_T c2_d_c;
  int32_T c2_e_a;
  int32_T c2_e_c;
  int32_T c2_c_b;
  int32_T c2_jx;
  real_T c2_x;
  real_T c2_y;
  real_T c2_z;
  int32_T c2_f_a;
  int32_T c2_i1342;
  int32_T c2_c_i;
  int32_T c2_d_i;
  int32_T c2_g_a;
  int32_T c2_f_c;
  int32_T c2_h_a;
  int32_T c2_d_b;
  int32_T c2_ix;
  int32_T c2_i_a;
  int32_T c2_e_b;
  int32_T c2_g_c;
  int32_T c2_i1343;
  real_T c2_b_A[9];
  c2_eml_scalar_eg(chartInstance);
  c2_b_eml_int_forloop_overflow_check(chartInstance);
  for (c2_i = 1; c2_i < 4; c2_i++) {
    c2_b_i = c2_i;
    c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_b_i), 1, 3, 1, 0) - 1] = c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) - 1];
  }

  c2_d_below_threshold(chartInstance);
  c2_k_eml_int_forloop_overflow_check(chartInstance);
  for (c2_j = 3; c2_j > 0; c2_j--) {
    c2_b_j = c2_j;
    c2_b = c2_b_j;
    c2_c = c2_b;
    c2_a = c2_b_j;
    c2_b_c = c2_a;
    c2_b_a = c2_b_c - 1;
    c2_c_c = c2_b_a * 3;
    c2_c_a = c2_c;
    c2_b_b = c2_c_c;
    c2_jjA = c2_c_a + c2_b_b;
    c2_d_a = c2_b_j;
    c2_d_c = c2_d_a;
    c2_e_a = c2_d_c - 1;
    c2_e_c = c2_e_a;
    c2_c_b = c2_e_c + 1;
    c2_jx = c2_c_b;
    c2_x = c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_jx), 1, 3, 1, 0) - 1];
    c2_y = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_jjA), 1, 9, 1, 0) - 1];
    c2_z = c2_x / c2_y;
    c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_jx), 1, 3, 1, 0) - 1] = c2_z;
    c2_f_a = c2_b_j - 1;
    c2_i1342 = c2_f_a;
    c2_h_eml_int_forloop_overflow_check(chartInstance, c2_i1342);
    for (c2_c_i = 1; c2_c_i <= c2_i1342; c2_c_i++) {
      c2_d_i = c2_c_i;
      c2_g_a = c2_d_i;
      c2_f_c = c2_g_a;
      c2_h_a = c2_jx;
      c2_d_b = c2_f_c;
      c2_ix = c2_h_a - c2_d_b;
      c2_i_a = c2_jjA;
      c2_e_b = c2_d_i;
      c2_g_c = c2_i_a - c2_e_b;
      c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_ix), 1, 3, 1, 0) - 1] = c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_ix), 1, 3, 1, 0) - 1] -
        c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_jx), 1, 3, 1, 0) - 1] * c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_g_c), 1, 9, 1, 0) - 1];
    }
  }

  for (c2_i1343 = 0; c2_i1343 < 9; c2_i1343++) {
    c2_b_A[c2_i1343] = c2_A[c2_i1343];
  }

  if (c2_c_is_singular_triangular_matrix(chartInstance, c2_b_A)) {
    c2_eml_warning(chartInstance);
  }
}

static void c2_hb_eml_scalar_eg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

static void c2_m_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[5184], real_T c2_B[72], real_T c2_C[72], real_T
  c2_b_C[72])
{
  int32_T c2_i1344;
  int32_T c2_i1345;
  real_T c2_b_A[5184];
  int32_T c2_i1346;
  real_T c2_b_B[72];
  for (c2_i1344 = 0; c2_i1344 < 72; c2_i1344++) {
    c2_b_C[c2_i1344] = c2_C[c2_i1344];
  }

  for (c2_i1345 = 0; c2_i1345 < 5184; c2_i1345++) {
    c2_b_A[c2_i1345] = c2_A[c2_i1345];
  }

  for (c2_i1346 = 0; c2_i1346 < 72; c2_i1346++) {
    c2_b_B[c2_i1346] = c2_B[c2_i1346];
  }

  c2_ab_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static real_T c2_f_norm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_x[72])
{
  real_T c2_y;
  real_T c2_scale;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_absxk;
  real_T c2_t;
  c2_y = 0.0;
  c2_eml_realmin(chartInstance);
  c2_scale = 2.2250738585072014E-308;
  c2_h_eml_int_forloop_overflow_check(chartInstance, 72);
  for (c2_k = 1; c2_k < 73; c2_k++) {
    c2_b_k = c2_k;
    c2_b_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_b_k), 1, 72, 1, 0) - 1];
    c2_c_x = c2_b_x;
    c2_absxk = muDoubleScalarAbs(c2_c_x);
    if (c2_absxk > c2_scale) {
      c2_t = c2_scale / c2_absxk;
      c2_y = 1.0 + c2_y * c2_t * c2_t;
      c2_scale = c2_absxk;
    } else {
      c2_t = c2_absxk / c2_scale;
      c2_y += c2_t * c2_t;
    }
  }

  return c2_scale * muDoubleScalarSqrt(c2_y);
}

static void c2_b_calcDs(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_z[40], real_T c2_Ps[1600], real_T c2_Fxs[12], real_T
  c2_Fus[4], real_T c2_hs[40], real_T c2_rho, boolean_T c2_flagNoPade, real_T
  c2_switches[9], real_T c2_ds[40], real_T c2_es[40])
{
  uint32_T c2_debug_family_var_map[18];
  real_T c2_rs[40];
  real_T c2_checkPs;
  real_T c2_T;
  real_T c2_n;
  real_T c2_m;
  real_T c2_ells;
  real_T c2_nargin = 12.0;
  real_T c2_nargout = 2.0;
  int32_T c2_i1347;
  int32_T c2_i1348;
  int32_T c2_i1349;
  real_T c2_b_z[40];
  int32_T c2_i1350;
  static real_T c2_b_Ps[1600];
  int32_T c2_i1351;
  real_T c2_b_Fxs[12];
  int32_T c2_i1352;
  real_T c2_b_Fus[4];
  int32_T c2_i1353;
  real_T c2_b_switches[9];
  real_T c2_dv86[40];
  int32_T c2_i1354;
  int32_T c2_ii;
  real_T c2_b_ii;
  real_T c2_a;
  real_T c2_b;
  real_T c2_y;
  real_T c2_B;
  real_T c2_b_y;
  real_T c2_c_y;
  real_T c2_d_y;
  real_T c2_b_a;
  real_T c2_b_b;
  real_T c2_e_y;
  real_T c2_A;
  real_T c2_b_B;
  real_T c2_x;
  real_T c2_f_y;
  real_T c2_b_x;
  real_T c2_g_y;
  real_T c2_h_y;
  sf_debug_symbol_scope_push_eml(0U, 18U, 18U, c2_w_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(c2_rs, 0U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_checkPs, 1U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c2_T, 2U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_n, 3U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_m, 4U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_ells, 5U, c2_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 6U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 7U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_z, 8U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Ps, 9U, c2_e_sf_marshallOut,
    c2_i_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Fxs, 10U, c2_c_sf_marshallOut,
    c2_s_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Fus, 11U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_hs, 12U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_rho, 13U, c2_h_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_flagNoPade, 14U,
    c2_w_sf_marshallOut, c2_q_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_switches, 15U, c2_v_sf_marshallOut,
    c2_p_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_ds, 16U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_es, 17U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  c2_T = 10.0;
  c2_n = 3.0;
  c2_m = 1.0;
  c2_ells = 4.0;
  CV_EML_FCN(0, 6);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 766);
  for (c2_i1347 = 0; c2_i1347 < 40; c2_i1347++) {
    c2_es[c2_i1347] = c2_hs[c2_i1347];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 767);
  for (c2_i1348 = 0; c2_i1348 < 40; c2_i1348++) {
    c2_ds[c2_i1348] = c2_hs[c2_i1348];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 771);
  for (c2_i1349 = 0; c2_i1349 < 40; c2_i1349++) {
    c2_b_z[c2_i1349] = c2_z[c2_i1349];
  }

  for (c2_i1350 = 0; c2_i1350 < 1600; c2_i1350++) {
    c2_b_Ps[c2_i1350] = c2_Ps[c2_i1350];
  }

  for (c2_i1351 = 0; c2_i1351 < 12; c2_i1351++) {
    c2_b_Fxs[c2_i1351] = c2_Fxs[c2_i1351];
  }

  for (c2_i1352 = 0; c2_i1352 < 4; c2_i1352++) {
    c2_b_Fus[c2_i1352] = c2_Fus[c2_i1352];
  }

  for (c2_i1353 = 0; c2_i1353 < 9; c2_i1353++) {
    c2_b_switches[c2_i1353] = c2_switches[c2_i1353];
  }

  c2_multByPs(chartInstance, c2_b_z, c2_b_Ps, c2_b_Fxs, c2_b_Fus, c2_b_switches,
              c2_dv86);
  for (c2_i1354 = 0; c2_i1354 < 40; c2_i1354++) {
    c2_rs[c2_i1354] = c2_dv86[c2_i1354] - c2_hs[c2_i1354];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 773);
  CV_EML_IF(0, 1, 50, FALSE);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 776);
  c2_checkPs = 0.0;
  c2_ii = 0;
  while (c2_ii < 40) {
    c2_b_ii = 1.0 + (real_T)c2_ii;
    CV_EML_FOR(0, 1, 11, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 783);
    if (CV_EML_IF(0, 1, 51, c2_rs[_SFD_EML_ARRAY_BOUNDS_CHECK("rs", (int32_T)
          _SFD_INTEGER_CHECK("ii", c2_b_ii), 1, 40, 1, 0) - 1] > 0.0)) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 784);
      c2_a = -c2_rho;
      c2_b = c2_rs[_SFD_EML_ARRAY_BOUNDS_CHECK("rs", (int32_T)_SFD_INTEGER_CHECK
        ("ii", c2_b_ii), 1, 40, 1, 0) - 1];
      c2_y = c2_a * c2_b;
      c2_es[_SFD_EML_ARRAY_BOUNDS_CHECK("es", (int32_T)_SFD_INTEGER_CHECK("ii",
        c2_b_ii), 1, 40, 1, 0) - 1] = c2_myexp(chartInstance, c2_y,
        c2_flagNoPade);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 785);
      c2_B = 1.0 + c2_es[_SFD_EML_ARRAY_BOUNDS_CHECK("es", (int32_T)
        _SFD_INTEGER_CHECK("ii", c2_b_ii), 1, 40, 1, 0) - 1];
      c2_b_y = c2_B;
      c2_c_y = c2_b_y;
      c2_d_y = 1.0 / c2_c_y;
      c2_ds[_SFD_EML_ARRAY_BOUNDS_CHECK("ds", (int32_T)_SFD_INTEGER_CHECK("ii",
        c2_b_ii), 1, 40, 1, 0) - 1] = c2_d_y;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 787);
      c2_b_a = c2_rho;
      c2_b_b = c2_rs[_SFD_EML_ARRAY_BOUNDS_CHECK("rs", (int32_T)
        _SFD_INTEGER_CHECK("ii", c2_b_ii), 1, 40, 1, 0) - 1];
      c2_e_y = c2_b_a * c2_b_b;
      c2_es[_SFD_EML_ARRAY_BOUNDS_CHECK("es", (int32_T)_SFD_INTEGER_CHECK("ii",
        c2_b_ii), 1, 40, 1, 0) - 1] = c2_myexp(chartInstance, c2_e_y,
        c2_flagNoPade);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 788);
      c2_A = c2_es[_SFD_EML_ARRAY_BOUNDS_CHECK("es", (int32_T)_SFD_INTEGER_CHECK
        ("ii", c2_b_ii), 1, 40, 1, 0) - 1];
      c2_b_B = 1.0 + c2_es[_SFD_EML_ARRAY_BOUNDS_CHECK("es", (int32_T)
        _SFD_INTEGER_CHECK("ii", c2_b_ii), 1, 40, 1, 0) - 1];
      c2_x = c2_A;
      c2_f_y = c2_b_B;
      c2_b_x = c2_x;
      c2_g_y = c2_f_y;
      c2_h_y = c2_b_x / c2_g_y;
      c2_ds[_SFD_EML_ARRAY_BOUNDS_CHECK("ds", (int32_T)_SFD_INTEGER_CHECK("ii",
        c2_b_ii), 1, 40, 1, 0) - 1] = c2_h_y;
    }

    c2_ii++;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 11, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -788);
  sf_debug_symbol_scope_pop();
}

static const mxArray *c2_x_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_y_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct *
  chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i1355;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i1355, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i1355;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_w_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
    chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_y_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_ab_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_mpcSetpointIntptCoupled,
  const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_bb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_mpcSetpointIntptCoupled), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_mpcSetpointIntptCoupled);
  return c2_y;
}

static uint8_T c2_bb_emlrt_marshallIn(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_n_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[40], real_T c2_C[44])
{
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_k;
  real_T c2_alpha1;
  int32_T c2_lda;
  int32_T c2_ldb;
  real_T c2_beta1;
  int32_T c2_ldc;
  char_T c2_TRANSA;
  char_T c2_TRANSB;
  c2_m = 44;
  c2_n = 1;
  c2_k = 40;
  c2_alpha1 = 1.0;
  c2_lda = 44;
  c2_ldb = 40;
  c2_beta1 = 0.0;
  c2_ldc = 44;
  c2_TRANSA = 'N';
  c2_TRANSB = 'N';
  dgemm32(&c2_TRANSA, &c2_TRANSB, &c2_m, &c2_n, &c2_k, &c2_alpha1, &c2_A[0],
          &c2_lda, &c2_B[0], &c2_ldb, &c2_beta1, &c2_C[0], &c2_ldc);
}

static void c2_o_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[40], real_T c2_C[32])
{
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_k;
  real_T c2_alpha1;
  int32_T c2_lda;
  int32_T c2_ldb;
  real_T c2_beta1;
  int32_T c2_ldc;
  char_T c2_TRANSA;
  char_T c2_TRANSB;
  c2_m = 32;
  c2_n = 1;
  c2_k = 40;
  c2_alpha1 = 1.0;
  c2_lda = 32;
  c2_ldb = 40;
  c2_beta1 = 0.0;
  c2_ldc = 32;
  c2_TRANSA = 'N';
  c2_TRANSB = 'N';
  dgemm32(&c2_TRANSA, &c2_TRANSB, &c2_m, &c2_n, &c2_k, &c2_alpha1, &c2_A[0],
          &c2_lda, &c2_B[0], &c2_ldb, &c2_beta1, &c2_C[0], &c2_ldc);
}

static void c2_p_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[44], real_T c2_C[40])
{
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_k;
  real_T c2_alpha1;
  int32_T c2_lda;
  int32_T c2_ldb;
  real_T c2_beta1;
  int32_T c2_ldc;
  char_T c2_TRANSA;
  char_T c2_TRANSB;
  c2_m = 40;
  c2_n = 1;
  c2_k = 44;
  c2_alpha1 = 1.0;
  c2_lda = 40;
  c2_ldb = 44;
  c2_beta1 = 0.0;
  c2_ldc = 40;
  c2_TRANSA = 'N';
  c2_TRANSB = 'N';
  dgemm32(&c2_TRANSA, &c2_TRANSB, &c2_m, &c2_n, &c2_k, &c2_alpha1, &c2_A[0],
          &c2_lda, &c2_B[0], &c2_ldb, &c2_beta1, &c2_C[0], &c2_ldc);
}

static void c2_q_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[32], real_T c2_C[40])
{
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_k;
  real_T c2_alpha1;
  int32_T c2_lda;
  int32_T c2_ldb;
  real_T c2_beta1;
  int32_T c2_ldc;
  char_T c2_TRANSA;
  char_T c2_TRANSB;
  c2_m = 40;
  c2_n = 1;
  c2_k = 32;
  c2_alpha1 = 1.0;
  c2_lda = 40;
  c2_ldb = 32;
  c2_beta1 = 0.0;
  c2_ldc = 40;
  c2_TRANSA = 'N';
  c2_TRANSB = 'N';
  dgemm32(&c2_TRANSA, &c2_TRANSB, &c2_m, &c2_n, &c2_k, &c2_alpha1, &c2_A[0],
          &c2_lda, &c2_B[0], &c2_ldb, &c2_beta1, &c2_C[0], &c2_ldc);
}

static void c2_r_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1600], real_T c2_B[40], real_T c2_C[40])
{
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_k;
  real_T c2_alpha1;
  int32_T c2_lda;
  int32_T c2_ldb;
  real_T c2_beta1;
  int32_T c2_ldc;
  char_T c2_TRANSA;
  char_T c2_TRANSB;
  c2_m = 40;
  c2_n = 1;
  c2_k = 40;
  c2_alpha1 = 1.0;
  c2_lda = 40;
  c2_ldb = 40;
  c2_beta1 = 0.0;
  c2_ldc = 40;
  c2_TRANSA = 'N';
  c2_TRANSB = 'N';
  dgemm32(&c2_TRANSA, &c2_TRANSB, &c2_m, &c2_n, &c2_k, &c2_alpha1, &c2_A[0],
          &c2_lda, &c2_B[0], &c2_ldb, &c2_beta1, &c2_C[0], &c2_ldc);
}

static void c2_d_chol(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T *c2_A)
{
  real_T c2_b_A;
  real_T c2_c_A;
  real_T c2_d_A;
  real_T c2_e_A;
  real_T c2_f_A;
  real_T c2_g_A;
  int32_T c2_info;
  real_T c2_ajj;
  int32_T c2_b_info;
  int32_T c2_c_info;
  int32_T c2_d_info;
  int32_T c2_jmax;
  int32_T c2_a;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_b_a;
  int32_T c2_i1356;
  int32_T c2_i;
  int32_T c2_b_i;
  c2_b_A = *c2_A;
  c2_c_A = c2_b_A;
  c2_d_A = c2_c_A;
  c2_e_A = c2_d_A;
  c2_f_A = c2_e_A;
  c2_g_A = c2_f_A;
  c2_info = 0;
  c2_n_eml_scalar_eg(chartInstance);
  c2_ajj = c2_g_A;
  if (c2_ajj > 0.0) {
    c2_ajj = muDoubleScalarSqrt(c2_ajj);
    c2_g_A = c2_ajj;
  } else {
    c2_info = 1;
  }

  c2_e_A = c2_g_A;
  c2_b_info = c2_info;
  c2_c_A = c2_e_A;
  c2_c_info = c2_b_info;
  *c2_A = c2_c_A;
  c2_d_info = c2_c_info;
  if (c2_d_info == 0) {
    c2_jmax = 1;
  } else {
    c2_b_eml_error(chartInstance);
    c2_a = c2_d_info - 1;
    c2_jmax = c2_a;
  }

  c2_g_eml_int_forloop_overflow_check(chartInstance, c2_jmax);
  for (c2_j = 2; c2_j <= c2_jmax; c2_j++) {
    c2_b_j = c2_j;
    c2_b_a = c2_b_j - 1;
    c2_i1356 = c2_b_a;
    c2_h_eml_int_forloop_overflow_check(chartInstance, c2_i1356);
    for (c2_i = 1; c2_i <= c2_i1356; c2_i++) {
      c2_b_i = c2_i;
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
        c2_b_i), 1, 1, 1, 0);
      _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
        c2_b_j), 1, 1, 2, 0);
      *c2_A = 0.0;
    }
  }
}

static int32_T c2_d_eml_matlab_zpotrf(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[16])
{
  int32_T c2_info;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_a;
  int32_T c2_jm1;
  int32_T c2_b_a;
  int32_T c2_c;
  int32_T c2_c_a;
  int32_T c2_b;
  int32_T c2_jj;
  int32_T c2_n;
  int32_T c2_ix0;
  int32_T c2_iy0;
  int32_T c2_b_n;
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  int32_T c2_c_n;
  int32_T c2_c_ix0;
  int32_T c2_c_iy0;
  int32_T c2_d_n;
  int32_T c2_d_ix0;
  int32_T c2_d_iy0;
  int32_T c2_e_n;
  int32_T c2_e_ix0;
  int32_T c2_e_iy0;
  real_T c2_d;
  int32_T c2_ix;
  int32_T c2_iy;
  int32_T c2_loop_ub;
  int32_T c2_k;
  int32_T c2_d_a;
  int32_T c2_e_a;
  real_T c2_ajj;
  int32_T c2_b_b;
  int32_T c2_nmj;
  int32_T c2_f_a;
  int32_T c2_jp1;
  int32_T c2_g_a;
  int32_T c2_jp1j;
  int32_T c2_b_k;
  int32_T c2_c_k;
  int32_T c2_d_k;
  real_T c2_y;
  real_T c2_z;
  int32_T c2_f_n;
  real_T c2_h_a;
  int32_T c2_f_ix0;
  int32_T c2_g_n;
  real_T c2_i_a;
  int32_T c2_g_ix0;
  int32_T c2_h_n;
  real_T c2_j_a;
  int32_T c2_h_ix0;
  int32_T c2_i_ix0;
  int32_T c2_k_a;
  int32_T c2_b_c;
  int32_T c2_c_b;
  int32_T c2_c_c;
  int32_T c2_l_a;
  int32_T c2_d_b;
  int32_T c2_i1357;
  int32_T c2_e_k;
  int32_T c2_f_k;
  boolean_T exitg1;
  c2_info = 0;
  c2_c_eml_int_forloop_overflow_check(chartInstance);
  c2_j = 1;
  exitg1 = FALSE;
  while ((exitg1 == 0U) && (c2_j < 5)) {
    c2_b_j = c2_j;
    c2_a = c2_b_j - 1;
    c2_jm1 = c2_a;
    c2_b_a = c2_jm1;
    c2_c = c2_b_a << 2;
    c2_c_a = c2_b_j;
    c2_b = c2_c;
    c2_jj = c2_c_a + c2_b;
    c2_n = c2_jm1;
    c2_ix0 = c2_b_j;
    c2_iy0 = c2_b_j;
    c2_b_n = c2_n;
    c2_b_ix0 = c2_ix0;
    c2_b_iy0 = c2_iy0;
    c2_c_n = c2_b_n;
    c2_c_ix0 = c2_b_ix0;
    c2_c_iy0 = c2_b_iy0;
    c2_d_n = c2_c_n;
    c2_d_ix0 = c2_c_ix0;
    c2_d_iy0 = c2_c_iy0;
    c2_e_n = c2_d_n;
    c2_e_ix0 = c2_d_ix0;
    c2_e_iy0 = c2_d_iy0;
    c2_o_eml_scalar_eg(chartInstance);
    c2_d = 0.0;
    if ((real_T)c2_e_n < 1.0) {
    } else {
      c2_ix = c2_e_ix0;
      c2_iy = c2_e_iy0;
      c2_h_eml_int_forloop_overflow_check(chartInstance, c2_e_n);
      c2_loop_ub = c2_e_n;
      for (c2_k = 1; c2_k <= c2_loop_ub; c2_k++) {
        c2_d += c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
          ("", (real_T)c2_ix), 1, 16, 1, 0) - 1] *
          c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_iy), 1, 16, 1, 0) - 1];
        c2_d_a = c2_ix + 4;
        c2_ix = c2_d_a;
        c2_e_a = c2_iy + 4;
        c2_iy = c2_e_a;
      }
    }

    c2_ajj = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_jj), 1, 16, 1, 0) - 1] - c2_d;
    if (c2_ajj > 0.0) {
      c2_ajj = muDoubleScalarSqrt(c2_ajj);
      c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_jj), 1, 16, 1, 0) - 1] = c2_ajj;
      if (c2_b_j < 4) {
        c2_b_b = c2_b_j;
        c2_nmj = 4 - c2_b_b;
        c2_f_a = c2_b_j;
        c2_jp1 = c2_f_a;
        c2_g_a = c2_jj + 1;
        c2_jp1j = c2_g_a;
        c2_h_eml_int_forloop_overflow_check(chartInstance, c2_jm1);
        for (c2_b_k = 1; c2_b_k <= c2_jm1; c2_b_k++) {
          c2_c_k = c2_b_k;
          c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_b_j), 1, 4, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK(
                   "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_c_k), 1, 4, 2,
                   0) - 1) << 2)) - 1] = c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 4, 1, 0) +
            ((_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_c_k), 1, 4, 2, 0) - 1) << 2)) - 1];
        }

        c2_d_eml_xgemv(chartInstance, c2_nmj, c2_jm1, c2_jp1 + 1, c2_b_j, c2_A,
                       c2_jp1j);
        c2_h_eml_int_forloop_overflow_check(chartInstance, c2_jm1);
        for (c2_d_k = 1; c2_d_k <= c2_jm1; c2_d_k++) {
          c2_c_k = c2_d_k;
          c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_b_j), 1, 4, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK(
                   "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_c_k), 1, 4, 2,
                   0) - 1) << 2)) - 1] = c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 4, 1, 0) +
            ((_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_c_k), 1, 4, 2, 0) - 1) << 2)) - 1];
        }

        c2_y = c2_ajj;
        c2_z = 1.0 / c2_y;
        c2_f_n = c2_nmj;
        c2_h_a = c2_z;
        c2_f_ix0 = c2_jp1j;
        c2_g_n = c2_f_n;
        c2_i_a = c2_h_a;
        c2_g_ix0 = c2_f_ix0;
        c2_h_n = c2_g_n;
        c2_j_a = c2_i_a;
        c2_h_ix0 = c2_g_ix0;
        c2_i_ix0 = c2_h_ix0;
        c2_k_a = c2_h_n;
        c2_b_c = c2_k_a;
        c2_c_b = c2_b_c - 1;
        c2_c_c = c2_c_b;
        c2_l_a = c2_h_ix0;
        c2_d_b = c2_c_c;
        c2_i1357 = c2_l_a + c2_d_b;
        c2_i_eml_int_forloop_overflow_check(chartInstance, c2_i_ix0, c2_i1357);
        for (c2_e_k = c2_i_ix0; c2_e_k <= c2_i1357; c2_e_k++) {
          c2_f_k = c2_e_k;
          c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_f_k), 1, 16, 1, 0) - 1] = c2_j_a *
            c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_f_k), 1, 16, 1, 0) - 1];
        }
      }

      c2_j++;
    } else {
      c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_jj), 1, 16, 1, 0) - 1] = c2_ajj;
      c2_info = c2_b_j;
      exitg1 = TRUE;
    }
  }

  return c2_info;
}

static void c2_d_eml_xgemv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_ia0, int32_T c2_ix0,
  real_T c2_y[16], int32_T c2_iy0)
{
  int32_T c2_b_m;
  int32_T c2_b_n;
  int32_T c2_b_ia0;
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  int32_T c2_c_m;
  int32_T c2_c_n;
  real_T c2_alpha1;
  int32_T c2_c_ia0;
  int32_T c2_lda;
  int32_T c2_c_ix0;
  int32_T c2_incx;
  real_T c2_beta1;
  int32_T c2_c_iy0;
  int32_T c2_incy;
  char_T c2_TRANSA;
  c2_b_m = c2_m;
  c2_b_n = c2_n;
  c2_b_ia0 = c2_ia0;
  c2_b_ix0 = c2_ix0;
  c2_b_iy0 = c2_iy0;
  if (c2_b_m < 1) {
  } else if (c2_b_n < 1) {
  } else {
    c2_c_m = c2_b_m;
    c2_c_n = c2_b_n;
    c2_alpha1 = -1.0;
    c2_c_ia0 = c2_b_ia0;
    c2_lda = 4;
    c2_c_ix0 = c2_b_ix0;
    c2_incx = 4;
    c2_beta1 = 1.0;
    c2_c_iy0 = c2_b_iy0;
    c2_incy = 1;
    c2_TRANSA = 'N';
    dgemv32(&c2_TRANSA, &c2_c_m, &c2_c_n, &c2_alpha1,
            &c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_c_ia0), 1, 16, 1, 0) - 1], &c2_lda,
            &c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_c_ix0), 1, 16, 1, 0) - 1], &c2_incx, &c2_beta1,
            &c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_c_iy0), 1, 16, 1, 0) - 1], &c2_incy);
  }
}

static void c2_e_chol(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_A[9])
{
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_info;
  int32_T c2_b_info;
  int32_T c2_c_info;
  int32_T c2_d_info;
  int32_T c2_jmax;
  int32_T c2_a;
  int32_T c2_c_j;
  int32_T c2_b_a;
  int32_T c2_i1358;
  int32_T c2_i;
  int32_T c2_b_i;
  c2_b_eml_int_forloop_overflow_check(chartInstance);
  for (c2_j = 1; c2_j < 4; c2_j++) {
    c2_b_j = c2_j;
  }

  c2_info = c2_e_eml_matlab_zpotrf(chartInstance, c2_A);
  c2_b_info = c2_info;
  c2_c_info = c2_b_info;
  c2_d_info = c2_c_info;
  if (c2_d_info == 0) {
    c2_jmax = 3;
  } else {
    c2_b_eml_error(chartInstance);
    c2_a = c2_d_info - 1;
    c2_jmax = c2_a;
  }

  c2_g_eml_int_forloop_overflow_check(chartInstance, c2_jmax);
  for (c2_c_j = 2; c2_c_j <= c2_jmax; c2_c_j++) {
    c2_b_j = c2_c_j;
    c2_b_a = c2_b_j - 1;
    c2_i1358 = c2_b_a;
    c2_h_eml_int_forloop_overflow_check(chartInstance, c2_i1358);
    for (c2_i = 1; c2_i <= c2_i1358; c2_i++) {
      c2_b_i = c2_i;
      c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1))
        - 1] = 0.0;
    }
  }
}

static int32_T c2_e_eml_matlab_zpotrf(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9])
{
  int32_T c2_info;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_a;
  int32_T c2_jm1;
  int32_T c2_b_a;
  int32_T c2_c;
  int32_T c2_c_a;
  int32_T c2_b;
  int32_T c2_jj;
  int32_T c2_n;
  int32_T c2_ix0;
  int32_T c2_iy0;
  int32_T c2_b_n;
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  int32_T c2_c_n;
  int32_T c2_c_ix0;
  int32_T c2_c_iy0;
  int32_T c2_d_n;
  int32_T c2_d_ix0;
  int32_T c2_d_iy0;
  int32_T c2_e_n;
  int32_T c2_e_ix0;
  int32_T c2_e_iy0;
  real_T c2_d;
  int32_T c2_ix;
  int32_T c2_iy;
  int32_T c2_loop_ub;
  int32_T c2_k;
  int32_T c2_d_a;
  int32_T c2_e_a;
  real_T c2_ajj;
  int32_T c2_b_b;
  int32_T c2_nmj;
  int32_T c2_f_a;
  int32_T c2_jp1;
  int32_T c2_g_a;
  int32_T c2_jp1j;
  int32_T c2_b_k;
  int32_T c2_c_k;
  int32_T c2_d_k;
  real_T c2_y;
  real_T c2_z;
  int32_T c2_f_n;
  real_T c2_h_a;
  int32_T c2_f_ix0;
  int32_T c2_g_n;
  real_T c2_i_a;
  int32_T c2_g_ix0;
  int32_T c2_h_n;
  real_T c2_j_a;
  int32_T c2_h_ix0;
  int32_T c2_i_ix0;
  int32_T c2_k_a;
  int32_T c2_b_c;
  int32_T c2_c_b;
  int32_T c2_c_c;
  int32_T c2_l_a;
  int32_T c2_d_b;
  int32_T c2_i1359;
  int32_T c2_e_k;
  int32_T c2_f_k;
  boolean_T exitg1;
  c2_info = 0;
  c2_b_eml_int_forloop_overflow_check(chartInstance);
  c2_j = 1;
  exitg1 = FALSE;
  while ((exitg1 == 0U) && (c2_j < 4)) {
    c2_b_j = c2_j;
    c2_a = c2_b_j - 1;
    c2_jm1 = c2_a;
    c2_b_a = c2_jm1;
    c2_c = c2_b_a * 3;
    c2_c_a = c2_b_j;
    c2_b = c2_c;
    c2_jj = c2_c_a + c2_b;
    c2_n = c2_jm1;
    c2_ix0 = c2_b_j;
    c2_iy0 = c2_b_j;
    c2_b_n = c2_n;
    c2_b_ix0 = c2_ix0;
    c2_b_iy0 = c2_iy0;
    c2_c_n = c2_b_n;
    c2_c_ix0 = c2_b_ix0;
    c2_c_iy0 = c2_b_iy0;
    c2_d_n = c2_c_n;
    c2_d_ix0 = c2_c_ix0;
    c2_d_iy0 = c2_c_iy0;
    c2_e_n = c2_d_n;
    c2_e_ix0 = c2_d_ix0;
    c2_e_iy0 = c2_d_iy0;
    c2_s_eml_scalar_eg(chartInstance);
    c2_d = 0.0;
    if ((real_T)c2_e_n < 1.0) {
    } else {
      c2_ix = c2_e_ix0;
      c2_iy = c2_e_iy0;
      c2_h_eml_int_forloop_overflow_check(chartInstance, c2_e_n);
      c2_loop_ub = c2_e_n;
      for (c2_k = 1; c2_k <= c2_loop_ub; c2_k++) {
        c2_d += c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
          ("", (real_T)c2_ix), 1, 9, 1, 0) - 1] *
          c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_iy), 1, 9, 1, 0) - 1];
        c2_d_a = c2_ix + 3;
        c2_ix = c2_d_a;
        c2_e_a = c2_iy + 3;
        c2_iy = c2_e_a;
      }
    }

    c2_ajj = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_jj), 1, 9, 1, 0) - 1] - c2_d;
    if (c2_ajj > 0.0) {
      c2_ajj = muDoubleScalarSqrt(c2_ajj);
      c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_jj), 1, 9, 1, 0) - 1] = c2_ajj;
      if (c2_b_j < 3) {
        c2_b_b = c2_b_j;
        c2_nmj = 3 - c2_b_b;
        c2_f_a = c2_b_j;
        c2_jp1 = c2_f_a;
        c2_g_a = c2_jj + 1;
        c2_jp1j = c2_g_a;
        c2_h_eml_int_forloop_overflow_check(chartInstance, c2_jm1);
        for (c2_b_k = 1; c2_b_k <= c2_jm1; c2_b_k++) {
          c2_c_k = c2_b_k;
          c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                   (real_T)c2_c_k), 1, 3, 2, 0) - 1)) - 1] = c2_A
            [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_j), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_c_k), 1, 3, 2, 0)
               - 1)) - 1];
        }

        c2_e_eml_xgemv(chartInstance, c2_nmj, c2_jm1, c2_jp1 + 1, c2_b_j, c2_A,
                       c2_jp1j);
        c2_h_eml_int_forloop_overflow_check(chartInstance, c2_jm1);
        for (c2_d_k = 1; c2_d_k <= c2_jm1; c2_d_k++) {
          c2_c_k = c2_d_k;
          c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                   (real_T)c2_c_k), 1, 3, 2, 0) - 1)) - 1] = c2_A
            [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_j), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_c_k), 1, 3, 2, 0)
               - 1)) - 1];
        }

        c2_y = c2_ajj;
        c2_z = 1.0 / c2_y;
        c2_f_n = c2_nmj;
        c2_h_a = c2_z;
        c2_f_ix0 = c2_jp1j;
        c2_g_n = c2_f_n;
        c2_i_a = c2_h_a;
        c2_g_ix0 = c2_f_ix0;
        c2_h_n = c2_g_n;
        c2_j_a = c2_i_a;
        c2_h_ix0 = c2_g_ix0;
        c2_i_ix0 = c2_h_ix0;
        c2_k_a = c2_h_n;
        c2_b_c = c2_k_a;
        c2_c_b = c2_b_c - 1;
        c2_c_c = c2_c_b;
        c2_l_a = c2_h_ix0;
        c2_d_b = c2_c_c;
        c2_i1359 = c2_l_a + c2_d_b;
        c2_i_eml_int_forloop_overflow_check(chartInstance, c2_i_ix0, c2_i1359);
        for (c2_e_k = c2_i_ix0; c2_e_k <= c2_i1359; c2_e_k++) {
          c2_f_k = c2_e_k;
          c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_f_k), 1, 9, 1, 0) - 1] = c2_j_a *
            c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_f_k), 1, 9, 1, 0) - 1];
        }
      }

      c2_j++;
    } else {
      c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_jj), 1, 9, 1, 0) - 1] = c2_ajj;
      c2_info = c2_b_j;
      exitg1 = TRUE;
    }
  }

  return c2_info;
}

static void c2_e_eml_xgemv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_ia0, int32_T c2_ix0,
  real_T c2_y[9], int32_T c2_iy0)
{
  int32_T c2_b_m;
  int32_T c2_b_n;
  int32_T c2_b_ia0;
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  int32_T c2_c_m;
  int32_T c2_c_n;
  real_T c2_alpha1;
  int32_T c2_c_ia0;
  int32_T c2_lda;
  int32_T c2_c_ix0;
  int32_T c2_incx;
  real_T c2_beta1;
  int32_T c2_c_iy0;
  int32_T c2_incy;
  char_T c2_TRANSA;
  c2_b_m = c2_m;
  c2_b_n = c2_n;
  c2_b_ia0 = c2_ia0;
  c2_b_ix0 = c2_ix0;
  c2_b_iy0 = c2_iy0;
  if (c2_b_m < 1) {
  } else if (c2_b_n < 1) {
  } else {
    c2_c_m = c2_b_m;
    c2_c_n = c2_b_n;
    c2_alpha1 = -1.0;
    c2_c_ia0 = c2_b_ia0;
    c2_lda = 3;
    c2_c_ix0 = c2_b_ix0;
    c2_incx = 3;
    c2_beta1 = 1.0;
    c2_c_iy0 = c2_b_iy0;
    c2_incy = 1;
    c2_TRANSA = 'N';
    dgemv32(&c2_TRANSA, &c2_c_m, &c2_c_n, &c2_alpha1,
            &c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_c_ia0), 1, 9, 1, 0) - 1], &c2_lda,
            &c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_c_ix0), 1, 9, 1, 0) - 1], &c2_incx, &c2_beta1,
            &c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_c_iy0), 1, 9, 1, 0) - 1], &c2_incy);
  }
}

static void c2_s_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[1936], real_T c2_C[1760])
{
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_k;
  real_T c2_alpha1;
  int32_T c2_lda;
  int32_T c2_ldb;
  real_T c2_beta1;
  int32_T c2_ldc;
  char_T c2_TRANSA;
  char_T c2_TRANSB;
  c2_m = 40;
  c2_n = 44;
  c2_k = 44;
  c2_alpha1 = 1.0;
  c2_lda = 40;
  c2_ldb = 44;
  c2_beta1 = 0.0;
  c2_ldc = 40;
  c2_TRANSA = 'N';
  c2_TRANSB = 'N';
  dgemm32(&c2_TRANSA, &c2_TRANSB, &c2_m, &c2_n, &c2_k, &c2_alpha1, &c2_A[0],
          &c2_lda, &c2_B[0], &c2_ldb, &c2_beta1, &c2_C[0], &c2_ldc);
}

static void c2_t_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1760], real_T c2_B[1760], real_T c2_C[1600])
{
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_k;
  real_T c2_alpha1;
  int32_T c2_lda;
  int32_T c2_ldb;
  real_T c2_beta1;
  int32_T c2_ldc;
  char_T c2_TRANSA;
  char_T c2_TRANSB;
  c2_m = 40;
  c2_n = 40;
  c2_k = 44;
  c2_alpha1 = 1.0;
  c2_lda = 40;
  c2_ldb = 44;
  c2_beta1 = 0.0;
  c2_ldc = 40;
  c2_TRANSA = 'N';
  c2_TRANSB = 'N';
  dgemm32(&c2_TRANSA, &c2_TRANSB, &c2_m, &c2_n, &c2_k, &c2_alpha1, &c2_A[0],
          &c2_lda, &c2_B[0], &c2_ldb, &c2_beta1, &c2_C[0], &c2_ldc);
}

static void c2_u_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1600], real_T c2_B[1600], real_T c2_C[1600])
{
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_k;
  real_T c2_alpha1;
  int32_T c2_lda;
  int32_T c2_ldb;
  real_T c2_beta1;
  int32_T c2_ldc;
  char_T c2_TRANSA;
  char_T c2_TRANSB;
  c2_m = 40;
  c2_n = 40;
  c2_k = 40;
  c2_alpha1 = 1.0;
  c2_lda = 40;
  c2_ldb = 40;
  c2_beta1 = 0.0;
  c2_ldc = 40;
  c2_TRANSA = 'N';
  c2_TRANSB = 'N';
  dgemm32(&c2_TRANSA, &c2_TRANSB, &c2_m, &c2_n, &c2_k, &c2_alpha1, &c2_A[0],
          &c2_lda, &c2_B[0], &c2_ldb, &c2_beta1, &c2_C[0], &c2_ldc);
}

static void c2_v_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[1600], real_T c2_C[1280])
{
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_k;
  real_T c2_alpha1;
  int32_T c2_lda;
  int32_T c2_ldb;
  real_T c2_beta1;
  int32_T c2_ldc;
  char_T c2_TRANSA;
  char_T c2_TRANSB;
  c2_m = 32;
  c2_n = 40;
  c2_k = 40;
  c2_alpha1 = 1.0;
  c2_lda = 32;
  c2_ldb = 40;
  c2_beta1 = 0.0;
  c2_ldc = 32;
  c2_TRANSA = 'N';
  c2_TRANSB = 'N';
  dgemm32(&c2_TRANSA, &c2_TRANSB, &c2_m, &c2_n, &c2_k, &c2_alpha1, &c2_A[0],
          &c2_lda, &c2_B[0], &c2_ldb, &c2_beta1, &c2_C[0], &c2_ldc);
}

static void c2_w_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1280], real_T c2_B[1280], real_T c2_C[1024])
{
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_k;
  real_T c2_alpha1;
  int32_T c2_lda;
  int32_T c2_ldb;
  real_T c2_beta1;
  int32_T c2_ldc;
  char_T c2_TRANSA;
  char_T c2_TRANSB;
  c2_m = 32;
  c2_n = 32;
  c2_k = 40;
  c2_alpha1 = 1.0;
  c2_lda = 32;
  c2_ldb = 40;
  c2_beta1 = 0.0;
  c2_ldc = 32;
  c2_TRANSA = 'N';
  c2_TRANSB = 'N';
  dgemm32(&c2_TRANSA, &c2_TRANSB, &c2_m, &c2_n, &c2_k, &c2_alpha1, &c2_A[0],
          &c2_lda, &c2_B[0], &c2_ldb, &c2_beta1, &c2_C[0], &c2_ldc);
}

static void c2_c_eml_xscal(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[1024], int32_T c2_ix0)
{
  int32_T c2_b_n;
  real_T c2_b_a;
  int32_T c2_b_ix0;
  int32_T c2_c_n;
  real_T c2_c_a;
  int32_T c2_c_ix0;
  int32_T c2_d_ix0;
  int32_T c2_d_a;
  int32_T c2_c;
  int32_T c2_b;
  int32_T c2_b_c;
  int32_T c2_e_a;
  int32_T c2_b_b;
  int32_T c2_i1360;
  int32_T c2_k;
  int32_T c2_b_k;
  c2_b_n = c2_n;
  c2_b_a = c2_a;
  c2_b_ix0 = c2_ix0;
  c2_c_n = c2_b_n;
  c2_c_a = c2_b_a;
  c2_c_ix0 = c2_b_ix0;
  c2_d_ix0 = c2_c_ix0;
  c2_d_a = c2_c_n;
  c2_c = c2_d_a;
  c2_b = c2_c - 1;
  c2_b_c = c2_b;
  c2_e_a = c2_c_ix0;
  c2_b_b = c2_b_c;
  c2_i1360 = c2_e_a + c2_b_b;
  c2_i_eml_int_forloop_overflow_check(chartInstance, c2_d_ix0, c2_i1360);
  for (c2_k = c2_d_ix0; c2_k <= c2_i1360; c2_k++) {
    c2_b_k = c2_k;
    c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_b_k), 1, 1024, 1, 0) - 1] = c2_c_a * c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK(
      "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 1024, 1, 0) - 1];
  }
}

static void c2_d_eml_xaxpy(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, int32_T c2_ix0, real_T c2_y[1024],
  int32_T c2_iy0)
{
  int32_T c2_b_n;
  real_T c2_b_a;
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  int32_T c2_c_n;
  real_T c2_c_a;
  int32_T c2_c_ix0;
  int32_T c2_c_iy0;
  int32_T c2_d_a;
  int32_T c2_ix;
  int32_T c2_e_a;
  int32_T c2_iy;
  int32_T c2_f_a;
  int32_T c2_i1361;
  int32_T c2_k;
  int32_T c2_g_a;
  int32_T c2_c;
  int32_T c2_h_a;
  int32_T c2_b_c;
  int32_T c2_i_a;
  int32_T c2_c_c;
  int32_T c2_j_a;
  int32_T c2_k_a;
  c2_b_n = c2_n;
  c2_b_a = c2_a;
  c2_b_ix0 = c2_ix0;
  c2_b_iy0 = c2_iy0;
  c2_c_n = c2_b_n;
  c2_c_a = c2_b_a;
  c2_c_ix0 = c2_b_ix0;
  c2_c_iy0 = c2_b_iy0;
  if ((real_T)c2_c_n < 1.0) {
  } else if (c2_c_a == 0.0) {
  } else {
    c2_d_a = c2_c_ix0 - 1;
    c2_ix = c2_d_a;
    c2_e_a = c2_c_iy0 - 1;
    c2_iy = c2_e_a;
    c2_f_a = c2_c_n - 1;
    c2_i1361 = c2_f_a;
    c2_i_eml_int_forloop_overflow_check(chartInstance, 0, c2_i1361);
    for (c2_k = 0; c2_k <= c2_i1361; c2_k++) {
      c2_g_a = c2_iy;
      c2_c = c2_g_a;
      c2_h_a = c2_iy;
      c2_b_c = c2_h_a;
      c2_i_a = c2_ix;
      c2_c_c = c2_i_a;
      c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)(c2_c + 1)), 1, 1024, 1, 0) - 1] =
        c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)(c2_b_c + 1)), 1, 1024, 1, 0) - 1] + c2_c_a *
        c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)(c2_c_c + 1)), 1, 1024, 1, 0) - 1];
      c2_j_a = c2_ix + 1;
      c2_ix = c2_j_a;
      c2_k_a = c2_iy + 1;
      c2_iy = c2_k_a;
    }
  }
}

static void c2_d_eml_xscal(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[32], int32_T c2_ix0)
{
  int32_T c2_b_n;
  real_T c2_b_a;
  int32_T c2_b_ix0;
  int32_T c2_c_n;
  real_T c2_c_a;
  int32_T c2_c_ix0;
  int32_T c2_d_ix0;
  int32_T c2_d_a;
  int32_T c2_c;
  int32_T c2_b;
  int32_T c2_b_c;
  int32_T c2_e_a;
  int32_T c2_b_b;
  int32_T c2_i1362;
  int32_T c2_k;
  int32_T c2_b_k;
  c2_b_n = c2_n;
  c2_b_a = c2_a;
  c2_b_ix0 = c2_ix0;
  c2_c_n = c2_b_n;
  c2_c_a = c2_b_a;
  c2_c_ix0 = c2_b_ix0;
  c2_d_ix0 = c2_c_ix0;
  c2_d_a = c2_c_n;
  c2_c = c2_d_a;
  c2_b = c2_c - 1;
  c2_b_c = c2_b;
  c2_e_a = c2_c_ix0;
  c2_b_b = c2_b_c;
  c2_i1362 = c2_e_a + c2_b_b;
  c2_i_eml_int_forloop_overflow_check(chartInstance, c2_d_ix0, c2_i1362);
  for (c2_k = c2_d_ix0; c2_k <= c2_i1362; c2_k++) {
    c2_b_k = c2_k;
    c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_b_k), 1, 32, 1, 0) - 1] = c2_c_a * c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("",
      (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 32, 1, 0) - 1];
  }
}

static void c2_e_eml_xaxpy(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[1024], int32_T c2_ix0,
  real_T c2_y[32], int32_T c2_iy0)
{
  int32_T c2_b_n;
  real_T c2_b_a;
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  int32_T c2_c_n;
  real_T c2_c_a;
  int32_T c2_c_ix0;
  int32_T c2_c_iy0;
  int32_T c2_d_a;
  int32_T c2_ix;
  int32_T c2_e_a;
  int32_T c2_iy;
  int32_T c2_f_a;
  int32_T c2_i1363;
  int32_T c2_k;
  int32_T c2_g_a;
  int32_T c2_c;
  int32_T c2_h_a;
  int32_T c2_b_c;
  int32_T c2_i_a;
  int32_T c2_c_c;
  int32_T c2_j_a;
  int32_T c2_k_a;
  c2_b_n = c2_n;
  c2_b_a = c2_a;
  c2_b_ix0 = c2_ix0;
  c2_b_iy0 = c2_iy0;
  c2_c_n = c2_b_n;
  c2_c_a = c2_b_a;
  c2_c_ix0 = c2_b_ix0;
  c2_c_iy0 = c2_b_iy0;
  if ((real_T)c2_c_n < 1.0) {
  } else if (c2_c_a == 0.0) {
  } else {
    c2_d_a = c2_c_ix0 - 1;
    c2_ix = c2_d_a;
    c2_e_a = c2_c_iy0 - 1;
    c2_iy = c2_e_a;
    c2_f_a = c2_c_n - 1;
    c2_i1363 = c2_f_a;
    c2_i_eml_int_forloop_overflow_check(chartInstance, 0, c2_i1363);
    for (c2_k = 0; c2_k <= c2_i1363; c2_k++) {
      c2_g_a = c2_iy;
      c2_c = c2_g_a;
      c2_h_a = c2_iy;
      c2_b_c = c2_h_a;
      c2_i_a = c2_ix;
      c2_c_c = c2_i_a;
      c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)(c2_c + 1)), 1, 32, 1, 0) - 1] =
        c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)(c2_b_c + 1)), 1, 32, 1, 0) - 1] + c2_c_a *
        c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)(c2_c_c + 1)), 1, 1024, 1, 0) - 1];
      c2_j_a = c2_ix + 1;
      c2_ix = c2_j_a;
      c2_k_a = c2_iy + 1;
      c2_iy = c2_k_a;
    }
  }
}

static void c2_f_eml_xaxpy(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[32], int32_T c2_ix0,
  real_T c2_y[1024], int32_T c2_iy0)
{
  int32_T c2_b_n;
  real_T c2_b_a;
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  int32_T c2_c_n;
  real_T c2_c_a;
  int32_T c2_c_ix0;
  int32_T c2_c_iy0;
  int32_T c2_d_a;
  int32_T c2_ix;
  int32_T c2_e_a;
  int32_T c2_iy;
  int32_T c2_f_a;
  int32_T c2_i1364;
  int32_T c2_k;
  int32_T c2_g_a;
  int32_T c2_c;
  int32_T c2_h_a;
  int32_T c2_b_c;
  int32_T c2_i_a;
  int32_T c2_c_c;
  int32_T c2_j_a;
  int32_T c2_k_a;
  c2_b_n = c2_n;
  c2_b_a = c2_a;
  c2_b_ix0 = c2_ix0;
  c2_b_iy0 = c2_iy0;
  c2_c_n = c2_b_n;
  c2_c_a = c2_b_a;
  c2_c_ix0 = c2_b_ix0;
  c2_c_iy0 = c2_b_iy0;
  if ((real_T)c2_c_n < 1.0) {
  } else if (c2_c_a == 0.0) {
  } else {
    c2_d_a = c2_c_ix0 - 1;
    c2_ix = c2_d_a;
    c2_e_a = c2_c_iy0 - 1;
    c2_iy = c2_e_a;
    c2_f_a = c2_c_n - 1;
    c2_i1364 = c2_f_a;
    c2_i_eml_int_forloop_overflow_check(chartInstance, 0, c2_i1364);
    for (c2_k = 0; c2_k <= c2_i1364; c2_k++) {
      c2_g_a = c2_iy;
      c2_c = c2_g_a;
      c2_h_a = c2_iy;
      c2_b_c = c2_h_a;
      c2_i_a = c2_ix;
      c2_c_c = c2_i_a;
      c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)(c2_c + 1)), 1, 1024, 1, 0) - 1] =
        c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)(c2_b_c + 1)), 1, 1024, 1, 0) - 1] + c2_c_a *
        c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)(c2_c_c + 1)), 1, 32, 1, 0) - 1];
      c2_j_a = c2_ix + 1;
      c2_ix = c2_j_a;
      c2_k_a = c2_iy + 1;
      c2_iy = c2_k_a;
    }
  }
}

static void c2_b_sqrt(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T *c2_x)
{
  if (*c2_x < 0.0) {
    c2_e_eml_error(chartInstance);
  }

  *c2_x = muDoubleScalarSqrt(*c2_x);
}

static void c2_b_eml_xrotg(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T *c2_a, real_T *c2_b, real_T *c2_c, real_T *c2_s)
{
  real_T c2_b_a;
  real_T c2_b_b;
  real_T c2_c_b;
  real_T c2_c_a;
  real_T c2_d_a;
  real_T c2_d_b;
  real_T c2_e_b;
  real_T c2_e_a;
  real_T c2_b_c;
  real_T c2_b_s;
  real_T c2_c_c;
  real_T c2_c_s;
  c2_b_a = *c2_a;
  c2_b_b = *c2_b;
  c2_c_b = c2_b_b;
  c2_c_a = c2_b_a;
  c2_d_a = c2_c_a;
  c2_d_b = c2_c_b;
  c2_e_b = c2_d_b;
  c2_e_a = c2_d_a;
  c2_b_c = 0.0;
  c2_b_s = 0.0;
  drotg32(&c2_e_a, &c2_e_b, &c2_b_c, &c2_b_s);
  c2_c_a = c2_e_a;
  c2_c_b = c2_e_b;
  c2_c_c = c2_b_c;
  c2_c_s = c2_b_s;
  *c2_a = c2_c_a;
  *c2_b = c2_c_b;
  *c2_c = c2_c_c;
  *c2_s = c2_c_s;
}

static void c2_b_eml_xtrsm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_B[6])
{
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_a;
  int32_T c2_c;
  int32_T c2_b;
  int32_T c2_b_c;
  int32_T c2_b_b;
  int32_T c2_jBcol;
  int32_T c2_k;
  int32_T c2_b_k;
  int32_T c2_b_a;
  int32_T c2_c_c;
  int32_T c2_c_b;
  int32_T c2_d_c;
  int32_T c2_d_b;
  int32_T c2_kAcol;
  int32_T c2_c_a;
  int32_T c2_e_b;
  int32_T c2_e_c;
  int32_T c2_d_a;
  int32_T c2_f_b;
  int32_T c2_f_c;
  int32_T c2_e_a;
  int32_T c2_g_b;
  int32_T c2_g_c;
  int32_T c2_f_a;
  int32_T c2_h_b;
  int32_T c2_h_c;
  real_T c2_x;
  real_T c2_y;
  real_T c2_z;
  int32_T c2_g_a;
  int32_T c2_i1365;
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_h_a;
  int32_T c2_i_b;
  int32_T c2_i_c;
  int32_T c2_i_a;
  int32_T c2_j_b;
  int32_T c2_j_c;
  int32_T c2_j_a;
  int32_T c2_k_b;
  int32_T c2_k_c;
  int32_T c2_k_a;
  int32_T c2_l_b;
  int32_T c2_l_c;
  c2_e_eml_int_forloop_overflow_check(chartInstance);
  for (c2_j = 1; c2_j < 3; c2_j++) {
    c2_b_j = c2_j;
    c2_a = c2_b_j;
    c2_c = c2_a;
    c2_b = c2_c - 1;
    c2_b_c = 3 * c2_b;
    c2_b_b = c2_b_c;
    c2_jBcol = c2_b_b;
    c2_b_eml_int_forloop_overflow_check(chartInstance);
    for (c2_k = 1; c2_k < 4; c2_k++) {
      c2_b_k = c2_k;
      c2_b_a = c2_b_k;
      c2_c_c = c2_b_a;
      c2_c_b = c2_c_c - 1;
      c2_d_c = 3 * c2_c_b;
      c2_d_b = c2_d_c;
      c2_kAcol = c2_d_b;
      c2_c_a = c2_b_k;
      c2_e_b = c2_jBcol;
      c2_e_c = c2_c_a + c2_e_b;
      if (c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_e_c), 1, 6, 1, 0) - 1] != 0.0) {
        c2_d_a = c2_b_k;
        c2_f_b = c2_jBcol;
        c2_f_c = c2_d_a + c2_f_b;
        c2_e_a = c2_b_k;
        c2_g_b = c2_jBcol;
        c2_g_c = c2_e_a + c2_g_b;
        c2_f_a = c2_b_k;
        c2_h_b = c2_kAcol;
        c2_h_c = c2_f_a + c2_h_b;
        c2_x = c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_g_c), 1, 6, 1, 0) - 1];
        c2_y = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_h_c), 1, 9, 1, 0) - 1];
        c2_z = c2_x / c2_y;
        c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_f_c), 1, 6, 1, 0) - 1] = c2_z;
        c2_g_a = c2_b_k + 1;
        c2_i1365 = c2_g_a;
        c2_i_eml_int_forloop_overflow_check(chartInstance, c2_i1365, 3);
        for (c2_i = c2_i1365; c2_i < 4; c2_i++) {
          c2_b_i = c2_i;
          c2_h_a = c2_b_i;
          c2_i_b = c2_jBcol;
          c2_i_c = c2_h_a + c2_i_b;
          c2_i_a = c2_b_i;
          c2_j_b = c2_jBcol;
          c2_j_c = c2_i_a + c2_j_b;
          c2_j_a = c2_b_k;
          c2_k_b = c2_jBcol;
          c2_k_c = c2_j_a + c2_k_b;
          c2_k_a = c2_b_i;
          c2_l_b = c2_kAcol;
          c2_l_c = c2_k_a + c2_l_b;
          c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_i_c), 1, 6, 1, 0) - 1] = c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK
            ("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_j_c), 1, 6, 1, 0) -
            1] - c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_k_c), 1, 6, 1, 0) - 1] *
            c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_l_c), 1, 9, 1, 0) - 1];
        }
      }
    }
  }
}

static void c2_f_chol(SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance,
                      real_T c2_A[4])
{
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_info;
  int32_T c2_b_info;
  int32_T c2_c_info;
  int32_T c2_d_info;
  int32_T c2_jmax;
  int32_T c2_a;
  int32_T c2_c_j;
  int32_T c2_b_a;
  int32_T c2_i1366;
  int32_T c2_i;
  int32_T c2_b_i;
  c2_e_eml_int_forloop_overflow_check(chartInstance);
  for (c2_j = 1; c2_j < 3; c2_j++) {
    c2_b_j = c2_j;
  }

  c2_info = c2_f_eml_matlab_zpotrf(chartInstance, c2_A);
  c2_b_info = c2_info;
  c2_c_info = c2_b_info;
  c2_d_info = c2_c_info;
  if (c2_d_info == 0) {
    c2_jmax = 2;
  } else {
    c2_b_eml_error(chartInstance);
    c2_a = c2_d_info - 1;
    c2_jmax = c2_a;
  }

  c2_g_eml_int_forloop_overflow_check(chartInstance, c2_jmax);
  for (c2_c_j = 2; c2_c_j <= c2_jmax; c2_c_j++) {
    c2_b_j = c2_c_j;
    c2_b_a = c2_b_j - 1;
    c2_i1366 = c2_b_a;
    c2_h_eml_int_forloop_overflow_check(chartInstance, c2_i1366);
    for (c2_i = 1; c2_i <= c2_i1366; c2_i++) {
      c2_b_i = c2_i;
      c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_i), 1, 2, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("",
               (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 2, 2, 0) - 1)
             << 1)) - 1] = 0.0;
    }
  }
}

static int32_T c2_f_eml_matlab_zpotrf(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[4])
{
  int32_T c2_info;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_a;
  int32_T c2_jm1;
  int32_T c2_b_a;
  int32_T c2_c;
  int32_T c2_c_a;
  int32_T c2_b;
  int32_T c2_jj;
  int32_T c2_n;
  int32_T c2_ix0;
  int32_T c2_iy0;
  int32_T c2_b_n;
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  int32_T c2_c_n;
  int32_T c2_c_ix0;
  int32_T c2_c_iy0;
  int32_T c2_d_n;
  int32_T c2_d_ix0;
  int32_T c2_d_iy0;
  int32_T c2_e_n;
  int32_T c2_e_ix0;
  int32_T c2_e_iy0;
  real_T c2_d;
  int32_T c2_ix;
  int32_T c2_iy;
  int32_T c2_loop_ub;
  int32_T c2_k;
  int32_T c2_d_a;
  int32_T c2_e_a;
  real_T c2_ajj;
  int32_T c2_b_b;
  int32_T c2_nmj;
  int32_T c2_f_a;
  int32_T c2_jp1;
  int32_T c2_g_a;
  int32_T c2_jp1j;
  int32_T c2_b_k;
  int32_T c2_c_k;
  int32_T c2_d_k;
  real_T c2_y;
  real_T c2_z;
  int32_T c2_f_n;
  real_T c2_h_a;
  int32_T c2_f_ix0;
  int32_T c2_g_n;
  real_T c2_i_a;
  int32_T c2_g_ix0;
  int32_T c2_h_n;
  real_T c2_j_a;
  int32_T c2_h_ix0;
  int32_T c2_i_ix0;
  int32_T c2_k_a;
  int32_T c2_b_c;
  int32_T c2_c_b;
  int32_T c2_c_c;
  int32_T c2_l_a;
  int32_T c2_d_b;
  int32_T c2_i1367;
  int32_T c2_e_k;
  int32_T c2_f_k;
  boolean_T exitg1;
  c2_info = 0;
  c2_e_eml_int_forloop_overflow_check(chartInstance);
  c2_j = 1;
  exitg1 = FALSE;
  while ((exitg1 == 0U) && (c2_j < 3)) {
    c2_b_j = c2_j;
    c2_a = c2_b_j - 1;
    c2_jm1 = c2_a;
    c2_b_a = c2_jm1;
    c2_c = c2_b_a << 1;
    c2_c_a = c2_b_j;
    c2_b = c2_c;
    c2_jj = c2_c_a + c2_b;
    c2_n = c2_jm1;
    c2_ix0 = c2_b_j;
    c2_iy0 = c2_b_j;
    c2_b_n = c2_n;
    c2_b_ix0 = c2_ix0;
    c2_b_iy0 = c2_iy0;
    c2_c_n = c2_b_n;
    c2_c_ix0 = c2_b_ix0;
    c2_c_iy0 = c2_b_iy0;
    c2_d_n = c2_c_n;
    c2_d_ix0 = c2_c_ix0;
    c2_d_iy0 = c2_c_iy0;
    c2_e_n = c2_d_n;
    c2_e_ix0 = c2_d_ix0;
    c2_e_iy0 = c2_d_iy0;
    c2_d = 0.0;
    if ((real_T)c2_e_n < 1.0) {
    } else {
      c2_ix = c2_e_ix0;
      c2_iy = c2_e_iy0;
      c2_h_eml_int_forloop_overflow_check(chartInstance, c2_e_n);
      c2_loop_ub = c2_e_n;
      for (c2_k = 1; c2_k <= c2_loop_ub; c2_k++) {
        c2_d += c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
          ("", (real_T)c2_ix), 1, 4, 1, 0) - 1] *
          c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_iy), 1, 4, 1, 0) - 1];
        c2_d_a = c2_ix + 2;
        c2_ix = c2_d_a;
        c2_e_a = c2_iy + 2;
        c2_iy = c2_e_a;
      }
    }

    c2_ajj = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_jj), 1, 4, 1, 0) - 1] - c2_d;
    if (c2_ajj > 0.0) {
      c2_ajj = muDoubleScalarSqrt(c2_ajj);
      c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_jj), 1, 4, 1, 0) - 1] = c2_ajj;
      if (c2_b_j < 2) {
        c2_b_b = c2_b_j;
        c2_nmj = 2 - c2_b_b;
        c2_f_a = c2_b_j;
        c2_jp1 = c2_f_a;
        c2_g_a = c2_jj + 1;
        c2_jp1j = c2_g_a;
        c2_h_eml_int_forloop_overflow_check(chartInstance, c2_jm1);
        for (c2_b_k = 1; c2_b_k <= c2_jm1; c2_b_k++) {
          c2_c_k = c2_b_k;
          c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_b_j), 1, 2, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK(
                   "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_c_k), 1, 2, 2,
                   0) - 1) << 1)) - 1] = c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 2, 1, 0) +
            ((_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_c_k), 1, 2, 2, 0) - 1) << 1)) - 1];
        }

        c2_f_eml_xgemv(chartInstance, c2_nmj, c2_jm1, c2_jp1 + 1, c2_b_j, c2_A,
                       c2_jp1j);
        c2_h_eml_int_forloop_overflow_check(chartInstance, c2_jm1);
        for (c2_d_k = 1; c2_d_k <= c2_jm1; c2_d_k++) {
          c2_c_k = c2_d_k;
          c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_b_j), 1, 2, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK(
                   "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_c_k), 1, 2, 2,
                   0) - 1) << 1)) - 1] = c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 2, 1, 0) +
            ((_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_c_k), 1, 2, 2, 0) - 1) << 1)) - 1];
        }

        c2_y = c2_ajj;
        c2_z = 1.0 / c2_y;
        c2_f_n = c2_nmj;
        c2_h_a = c2_z;
        c2_f_ix0 = c2_jp1j;
        c2_g_n = c2_f_n;
        c2_i_a = c2_h_a;
        c2_g_ix0 = c2_f_ix0;
        c2_h_n = c2_g_n;
        c2_j_a = c2_i_a;
        c2_h_ix0 = c2_g_ix0;
        c2_i_ix0 = c2_h_ix0;
        c2_k_a = c2_h_n;
        c2_b_c = c2_k_a;
        c2_c_b = c2_b_c - 1;
        c2_c_c = c2_c_b;
        c2_l_a = c2_h_ix0;
        c2_d_b = c2_c_c;
        c2_i1367 = c2_l_a + c2_d_b;
        c2_i_eml_int_forloop_overflow_check(chartInstance, c2_i_ix0, c2_i1367);
        for (c2_e_k = c2_i_ix0; c2_e_k <= c2_i1367; c2_e_k++) {
          c2_f_k = c2_e_k;
          c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_f_k), 1, 4, 1, 0) - 1] = c2_j_a *
            c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_f_k), 1, 4, 1, 0) - 1];
        }
      }

      c2_j++;
    } else {
      c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_jj), 1, 4, 1, 0) - 1] = c2_ajj;
      c2_info = c2_b_j;
      exitg1 = TRUE;
    }
  }

  return c2_info;
}

static void c2_f_eml_xgemv(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_ia0, int32_T c2_ix0,
  real_T c2_y[4], int32_T c2_iy0)
{
  int32_T c2_b_m;
  int32_T c2_b_n;
  int32_T c2_b_ia0;
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  int32_T c2_c_m;
  int32_T c2_c_n;
  real_T c2_alpha1;
  int32_T c2_c_ia0;
  int32_T c2_lda;
  int32_T c2_c_ix0;
  int32_T c2_incx;
  real_T c2_beta1;
  int32_T c2_c_iy0;
  int32_T c2_incy;
  char_T c2_TRANSA;
  c2_b_m = c2_m;
  c2_b_n = c2_n;
  c2_b_ia0 = c2_ia0;
  c2_b_ix0 = c2_ix0;
  c2_b_iy0 = c2_iy0;
  if (c2_b_m < 1) {
  } else if (c2_b_n < 1) {
  } else {
    c2_c_m = c2_b_m;
    c2_c_n = c2_b_n;
    c2_alpha1 = -1.0;
    c2_c_ia0 = c2_b_ia0;
    c2_lda = 2;
    c2_c_ix0 = c2_b_ix0;
    c2_incx = 2;
    c2_beta1 = 1.0;
    c2_c_iy0 = c2_b_iy0;
    c2_incy = 1;
    c2_TRANSA = 'N';
    dgemv32(&c2_TRANSA, &c2_c_m, &c2_c_n, &c2_alpha1,
            &c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_c_ia0), 1, 4, 1, 0) - 1], &c2_lda,
            &c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_c_ix0), 1, 4, 1, 0) - 1], &c2_incx, &c2_beta1,
            &c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_c_iy0), 1, 4, 1, 0) - 1], &c2_incy);
  }
}

static void c2_x_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1024], real_T c2_B[1024], real_T c2_C[1024])
{
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_k;
  real_T c2_alpha1;
  int32_T c2_lda;
  int32_T c2_ldb;
  real_T c2_beta1;
  int32_T c2_ldc;
  char_T c2_TRANSA;
  char_T c2_TRANSB;
  c2_m = 32;
  c2_n = 32;
  c2_k = 32;
  c2_alpha1 = 1.0;
  c2_lda = 32;
  c2_ldb = 32;
  c2_beta1 = 0.0;
  c2_ldc = 32;
  c2_TRANSA = 'N';
  c2_TRANSB = 'N';
  dgemm32(&c2_TRANSA, &c2_TRANSB, &c2_m, &c2_n, &c2_k, &c2_alpha1, &c2_A[0],
          &c2_lda, &c2_B[0], &c2_ldb, &c2_beta1, &c2_C[0], &c2_ldc);
}

static void c2_y_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[1024], real_T c2_B[32], real_T c2_C[32])
{
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_k;
  real_T c2_alpha1;
  int32_T c2_lda;
  int32_T c2_ldb;
  real_T c2_beta1;
  int32_T c2_ldc;
  char_T c2_TRANSA;
  char_T c2_TRANSB;
  c2_m = 32;
  c2_n = 1;
  c2_k = 32;
  c2_alpha1 = 1.0;
  c2_lda = 32;
  c2_ldb = 32;
  c2_beta1 = 0.0;
  c2_ldc = 32;
  c2_TRANSA = 'N';
  c2_TRANSB = 'N';
  dgemm32(&c2_TRANSA, &c2_TRANSB, &c2_m, &c2_n, &c2_k, &c2_alpha1, &c2_A[0],
          &c2_lda, &c2_B[0], &c2_ldb, &c2_beta1, &c2_C[0], &c2_ldc);
}

static void c2_ab_eml_xgemm(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance, real_T c2_A[5184], real_T c2_B[72], real_T c2_C[72])
{
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_k;
  real_T c2_alpha1;
  int32_T c2_lda;
  int32_T c2_ldb;
  real_T c2_beta1;
  int32_T c2_ldc;
  char_T c2_TRANSA;
  char_T c2_TRANSB;
  c2_m = 72;
  c2_n = 1;
  c2_k = 72;
  c2_alpha1 = 1.0;
  c2_lda = 72;
  c2_ldb = 72;
  c2_beta1 = 0.0;
  c2_ldc = 72;
  c2_TRANSA = 'N';
  c2_TRANSB = 'N';
  dgemm32(&c2_TRANSA, &c2_TRANSB, &c2_m, &c2_n, &c2_k, &c2_alpha1, &c2_A[0],
          &c2_lda, &c2_B[0], &c2_ldb, &c2_beta1, &c2_C[0], &c2_ldc);
}

static void init_dsm_address_info(SFc2_mpcSetpointIntptCoupledInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_mpcSetpointIntptCoupled_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2268491776U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2710896009U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2084349420U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2900063454U);
}

mxArray *sf_c2_mpcSetpointIntptCoupled_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("yJsxHRPRJ2yhD4Un49g2uH");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,21,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(40);
      pr[1] = (double)(40);
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
      pr[0] = (double)(40);
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
      pr[0] = (double)(44);
      pr[1] = (double)(40);
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
      pr[0] = (double)(44);
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
      pr[0] = (double)(32);
      pr[1] = (double)(40);
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
      pr[0] = (double)(32);
      pr[1] = (double)(1);
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
      pr[0] = (double)(40);
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
      pr[0] = (double)(3);
      pr[1] = (double)(3);
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
      pr[0] = (double)(3);
      pr[1] = (double)(1);
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
      pr[0] = (double)(4);
      pr[1] = (double)(3);
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
      pr[0] = (double)(4);
      pr[1] = (double)(1);
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
      pr[0] = (double)(4);
      pr[1] = (double)(3);
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
      pr[0] = (double)(1);
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
      pr[0] = (double)(3);
      pr[1] = (double)(3);
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
      pr[0] = (double)(8);
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
      pr[0] = (double)(40);
      pr[1] = (double)(40);
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
      pr[0] = (double)(40);
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
      pr[1] = (double)(3);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(3);
      mxSetField(mxData,19,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,19,"type",mxType);
    }

    mxSetField(mxData,19,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,20,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,20,"type",mxType);
    }

    mxSetField(mxData,20,"complexity",mxCreateDoubleScalar(0));
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

static const mxArray *sf_get_sim_state_info_c2_mpcSetpointIntptCoupled(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[21],T\"info\",},{M[1],M[5],T\"z\",},{M[8],M[0],T\"is_active_c2_mpcSetpointIntptCoupled\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_mpcSetpointIntptCoupled_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
    chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_mpcSetpointIntptCoupledMachineNumber_,
           2,
           1,
           1,
           23,
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
          init_script_number_translation(_mpcSetpointIntptCoupledMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (_mpcSetpointIntptCoupledMachineNumber_,chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds
            (_mpcSetpointIntptCoupledMachineNumber_,
             chartInstance->chartNumber,
             0,
             0,
             0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"H");
          _SFD_SET_DATA_PROPS(1,2,0,1,"z");
          _SFD_SET_DATA_PROPS(2,1,1,0,"g");
          _SFD_SET_DATA_PROPS(3,1,1,0,"P");
          _SFD_SET_DATA_PROPS(4,1,1,0,"h");
          _SFD_SET_DATA_PROPS(5,1,1,0,"C");
          _SFD_SET_DATA_PROPS(6,1,1,0,"b");
          _SFD_SET_DATA_PROPS(7,1,1,0,"z0");
          _SFD_SET_DATA_PROPS(8,1,1,0,"A");
          _SFD_SET_DATA_PROPS(9,1,1,0,"B");
          _SFD_SET_DATA_PROPS(10,1,1,0,"Fx");
          _SFD_SET_DATA_PROPS(11,1,1,0,"Fu");
          _SFD_SET_DATA_PROPS(12,1,1,0,"Ff");
          _SFD_SET_DATA_PROPS(13,1,1,0,"Q");
          _SFD_SET_DATA_PROPS(14,1,1,0,"R");
          _SFD_SET_DATA_PROPS(15,1,1,0,"Qf");
          _SFD_SET_DATA_PROPS(16,2,0,1,"info");
          _SFD_SET_DATA_PROPS(17,1,1,0,"opts");
          _SFD_SET_DATA_PROPS(18,1,1,0,"Ps");
          _SFD_SET_DATA_PROPS(19,1,1,0,"hs");
          _SFD_SET_DATA_PROPS(20,1,1,0,"Ef");
          _SFD_SET_DATA_PROPS(21,1,1,0,"Fxs");
          _SFD_SET_DATA_PROPS(22,1,1,0,"Fus");
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
        _SFD_CV_INIT_EML(0,1,16,63,0,0,20,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,24568);
        _SFD_CV_INIT_EML_FCN(0,1,"Qtil",24642,-1,24743);
        _SFD_CV_INIT_EML_FCN(0,2,"Rtil",24745,-1,24830);
        _SFD_CV_INIT_EML_FCN(0,3,"Stil",24832,-1,24925);
        _SFD_CV_INIT_EML_FCN(0,4,"getSqBlk",24981,-1,25060);
        _SFD_CV_INIT_EML_FCN(0,5,"mySymPDinv",25062,-1,25412);
        _SFD_CV_INIT_EML_FCN(0,6,"calcDs",25414,-1,25940);
        _SFD_CV_INIT_EML_FCN(0,7,"myexp",25942,-1,26198);
        _SFD_CV_INIT_EML_FCN(0,8,"calcRp",26200,-1,26344);
        _SFD_CV_INIT_EML_FCN(0,9,"multByC",26346,-1,26882);
        _SFD_CV_INIT_EML_FCN(0,10,"multByP",26884,-1,27257);
        _SFD_CV_INIT_EML_FCN(0,11,"multByPs",27259,-1,27553);
        _SFD_CV_INIT_EML_FCN(0,12,"multByPsT",27555,-1,27941);
        _SFD_CV_INIT_EML_FCN(0,13,"multByCT",27943,-1,28618);
        _SFD_CV_INIT_EML_FCN(0,14,"preMultByA",28620,-1,28953);
        _SFD_CV_INIT_EML_FCN(0,15,"multByAT",28955,-1,29292);
        _SFD_CV_INIT_EML_IF(0,1,0,1152,1170,1228,1251);
        _SFD_CV_INIT_EML_IF(0,1,1,1543,1550,1613,1624);
        _SFD_CV_INIT_EML_IF(0,1,2,1613,1624,-1,1624);
        _SFD_CV_INIT_EML_IF(0,1,3,1935,1944,2026,2104);
        _SFD_CV_INIT_EML_IF(0,1,4,2151,2160,2192,2225);
        _SFD_CV_INIT_EML_IF(0,1,5,2283,2292,2327,2383);
        _SFD_CV_INIT_EML_IF(0,1,6,2445,2454,2486,2539);
        _SFD_CV_INIT_EML_IF(0,1,7,2591,2600,2630,2683);
        _SFD_CV_INIT_EML_IF(0,1,8,2747,2756,2810,2889);
        _SFD_CV_INIT_EML_IF(0,1,9,2958,2967,-1,3023);
        _SFD_CV_INIT_EML_IF(0,1,10,2973,2985,-1,3019);
        _SFD_CV_INIT_EML_IF(0,1,11,3080,3089,-1,3152);
        _SFD_CV_INIT_EML_IF(0,1,12,3095,3107,-1,3148);
        _SFD_CV_INIT_EML_IF(0,1,13,3894,3901,4080,4325);
        _SFD_CV_INIT_EML_IF(0,1,14,4367,4384,4457,5214);
        _SFD_CV_INIT_EML_IF(0,1,15,4610,4616,-1,4670);
        _SFD_CV_INIT_EML_IF(0,1,16,4711,4724,4792,5205);
        _SFD_CV_INIT_EML_IF(0,1,17,4792,4810,4915,5205);
        _SFD_CV_INIT_EML_IF(0,1,18,4915,4930,5051,5205);
        _SFD_CV_INIT_EML_IF(0,1,19,5263,5278,-1,5317);
        _SFD_CV_INIT_EML_IF(0,1,20,5774,5792,-1,6150);
        _SFD_CV_INIT_EML_IF(0,1,21,6012,6016,6107,6141);
        _SFD_CV_INIT_EML_IF(0,1,22,6395,6410,6466,6507);
        _SFD_CV_INIT_EML_IF(0,1,23,6555,6570,6620,6661);
        _SFD_CV_INIT_EML_IF(0,1,24,6716,6734,-1,6871);
        _SFD_CV_INIT_EML_IF(0,1,25,6925,6941,7296,8518);
        _SFD_CV_INIT_EML_IF(0,1,26,7109,7127,-1,7196);
        _SFD_CV_INIT_EML_IF(0,1,27,7461,7479,7632,7756);
        _SFD_CV_INIT_EML_IF(0,1,28,7801,7819,8059,8218);
        _SFD_CV_INIT_EML_IF(0,1,29,8575,8590,8880,8925);
        _SFD_CV_INIT_EML_IF(0,1,30,8656,8674,-1,8758);
        _SFD_CV_INIT_EML_IF(0,1,31,9143,9150,-1,9504);
        _SFD_CV_INIT_EML_IF(0,1,32,9517,9524,-1,10185);
        _SFD_CV_INIT_EML_IF(0,1,33,11170,11180,-1,11420);
        _SFD_CV_INIT_EML_IF(0,1,34,11491,11506,11558,11598);
        _SFD_CV_INIT_EML_IF(0,1,35,12231,12246,12310,12353);
        _SFD_CV_INIT_EML_IF(0,1,36,12879,12889,-1,13182);
        _SFD_CV_INIT_EML_IF(0,1,37,13230,13245,13289,13329);
        _SFD_CV_INIT_EML_IF(0,1,38,13736,13746,-1,13925);
        _SFD_CV_INIT_EML_IF(0,1,39,13973,13988,14035,14076);
        _SFD_CV_INIT_EML_IF(0,1,40,14216,14226,14508,14626);
        _SFD_CV_INIT_EML_IF(0,1,41,14873,14888,14939,14982);
        _SFD_CV_INIT_EML_IF(0,1,42,17769,17784,17897,17937);
        _SFD_CV_INIT_EML_IF(0,1,43,17982,17998,18182,18813);
        _SFD_CV_INIT_EML_IF(0,1,44,18874,18889,19035,19080);
        _SFD_CV_INIT_EML_IF(0,1,45,19346,19360,-1,-2);
        _SFD_CV_INIT_EML_IF(0,1,46,19846,19864,-1,20166);
        _SFD_CV_INIT_EML_IF(0,1,47,21168,21186,-1,21394);
        _SFD_CV_INIT_EML_IF(0,1,48,21626,21660,22283,22394);
        _SFD_CV_INIT_EML_IF(0,1,49,21973,21991,-1,22118);
        _SFD_CV_INIT_EML_IF(0,1,50,25622,25626,25667,25692);
        _SFD_CV_INIT_EML_IF(0,1,51,25726,25737,25828,25931);
        _SFD_CV_INIT_EML_IF(0,1,52,26003,26016,26034,26193);
        _SFD_CV_INIT_EML_IF(0,1,53,26418,26437,26451,26878);
        _SFD_CV_INIT_EML_IF(0,1,54,26799,26809,-1,26874);
        _SFD_CV_INIT_EML_IF(0,1,55,26961,26980,26994,27253);
        _SFD_CV_INIT_EML_IF(0,1,56,27174,27183,-1,27249);
        _SFD_CV_INIT_EML_IF(0,1,57,27334,27353,27368,27549);
        _SFD_CV_INIT_EML_IF(0,1,58,27677,27696,27713,27937);
        _SFD_CV_INIT_EML_IF(0,1,59,28073,28092,28108,28614);
        _SFD_CV_INIT_EML_IF(0,1,60,28505,28515,-1,28610);
        _SFD_CV_INIT_EML_IF(0,1,61,28677,28696,28710,28949);
        _SFD_CV_INIT_EML_IF(0,1,62,29012,29031,29046,29288);
        _SFD_CV_INIT_EML_FOR(0,1,0,6242,6264,24330);
        _SFD_CV_INIT_EML_FOR(0,1,1,6320,6344,24276);
        _SFD_CV_INIT_EML_FOR(0,1,2,7769,7784,8356);
        _SFD_CV_INIT_EML_FOR(0,1,3,9119,9130,10197);
        _SFD_CV_INIT_EML_FOR(0,1,4,11775,11790,11977);
        _SFD_CV_INIT_EML_FOR(0,1,5,12530,12541,12805);
        _SFD_CV_INIT_EML_FOR(0,1,6,13506,13521,13678);
        _SFD_CV_INIT_EML_FOR(0,1,7,14635,14653,14816);
        _SFD_CV_INIT_EML_FOR(0,1,8,18496,18511,18699);
        _SFD_CV_INIT_EML_FOR(0,1,9,19190,19202,19466);
        _SFD_CV_INIT_EML_FOR(0,1,10,20809,20821,22419);
        _SFD_CV_INIT_EML_FOR(0,1,11,25696,25716,25935);
        _SFD_CV_INIT_EML_FOR(0,1,12,26107,26118,26174);
        _SFD_CV_INIT_EML_FOR(0,1,13,26529,26540,26789);
        _SFD_CV_INIT_EML_FOR(0,1,14,27063,27074,27169);
        _SFD_CV_INIT_EML_FOR(0,1,15,27435,27446,27545);
        _SFD_CV_INIT_EML_FOR(0,1,16,27783,27794,27933);
        _SFD_CV_INIT_EML_FOR(0,1,17,28174,28185,28445);
        _SFD_CV_INIT_EML_FOR(0,1,18,28865,28876,28945);
        _SFD_CV_INIT_EML_FOR(0,1,19,29203,29214,29284);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 40;
          dimVector[1]= 40;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 40;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 40;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 44;
          dimVector[1]= 40;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_m_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 44;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_l_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 32;
          dimVector[1]= 40;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_k_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 32;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_j_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 40;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_g_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_i_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_g_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_h_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_g_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(16,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 8;
          _SFD_SET_DATA_COMPILED_PROPS(17,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 40;
          dimVector[1]= 40;
          _SFD_SET_DATA_COMPILED_PROPS(18,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 40;
          _SFD_SET_DATA_COMPILED_PROPS(19,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(20,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(21,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(22,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T *c2_R;
          real_T (*c2_H)[1600];
          real_T (*c2_z)[40];
          real_T (*c2_g)[40];
          real_T (*c2_P)[1760];
          real_T (*c2_h)[44];
          real_T (*c2_C)[1280];
          real_T (*c2_b)[32];
          real_T (*c2_z0)[40];
          real_T (*c2_A)[9];
          real_T (*c2_B)[3];
          real_T (*c2_Fx)[12];
          real_T (*c2_Fu)[4];
          real_T (*c2_Ff)[12];
          real_T (*c2_Q)[9];
          real_T (*c2_Qf)[9];
          real_T (*c2_info)[4];
          real_T (*c2_opts)[8];
          real_T (*c2_Ps)[1600];
          real_T (*c2_hs)[40];
          real_T (*c2_Ef)[6];
          real_T (*c2_Fxs)[12];
          real_T (*c2_Fus)[4];
          c2_Fus = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 20);
          c2_Fxs = (real_T (*)[12])ssGetInputPortSignal(chartInstance->S, 19);
          c2_Ef = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 18);
          c2_hs = (real_T (*)[40])ssGetInputPortSignal(chartInstance->S, 17);
          c2_Ps = (real_T (*)[1600])ssGetInputPortSignal(chartInstance->S, 16);
          c2_opts = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 15);
          c2_info = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
          c2_Qf = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 14);
          c2_R = (real_T *)ssGetInputPortSignal(chartInstance->S, 13);
          c2_Q = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 12);
          c2_Ff = (real_T (*)[12])ssGetInputPortSignal(chartInstance->S, 11);
          c2_Fu = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 10);
          c2_Fx = (real_T (*)[12])ssGetInputPortSignal(chartInstance->S, 9);
          c2_B = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 8);
          c2_A = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 7);
          c2_z0 = (real_T (*)[40])ssGetInputPortSignal(chartInstance->S, 6);
          c2_b = (real_T (*)[32])ssGetInputPortSignal(chartInstance->S, 5);
          c2_C = (real_T (*)[1280])ssGetInputPortSignal(chartInstance->S, 4);
          c2_h = (real_T (*)[44])ssGetInputPortSignal(chartInstance->S, 3);
          c2_P = (real_T (*)[1760])ssGetInputPortSignal(chartInstance->S, 2);
          c2_g = (real_T (*)[40])ssGetInputPortSignal(chartInstance->S, 1);
          c2_z = (real_T (*)[40])ssGetOutputPortSignal(chartInstance->S, 1);
          c2_H = (real_T (*)[1600])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_H);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_z);
          _SFD_SET_DATA_VALUE_PTR(2U, *c2_g);
          _SFD_SET_DATA_VALUE_PTR(3U, *c2_P);
          _SFD_SET_DATA_VALUE_PTR(4U, *c2_h);
          _SFD_SET_DATA_VALUE_PTR(5U, *c2_C);
          _SFD_SET_DATA_VALUE_PTR(6U, *c2_b);
          _SFD_SET_DATA_VALUE_PTR(7U, *c2_z0);
          _SFD_SET_DATA_VALUE_PTR(8U, *c2_A);
          _SFD_SET_DATA_VALUE_PTR(9U, *c2_B);
          _SFD_SET_DATA_VALUE_PTR(10U, *c2_Fx);
          _SFD_SET_DATA_VALUE_PTR(11U, *c2_Fu);
          _SFD_SET_DATA_VALUE_PTR(12U, *c2_Ff);
          _SFD_SET_DATA_VALUE_PTR(13U, *c2_Q);
          _SFD_SET_DATA_VALUE_PTR(14U, c2_R);
          _SFD_SET_DATA_VALUE_PTR(15U, *c2_Qf);
          _SFD_SET_DATA_VALUE_PTR(16U, *c2_info);
          _SFD_SET_DATA_VALUE_PTR(17U, *c2_opts);
          _SFD_SET_DATA_VALUE_PTR(18U, *c2_Ps);
          _SFD_SET_DATA_VALUE_PTR(19U, *c2_hs);
          _SFD_SET_DATA_VALUE_PTR(20U, *c2_Ef);
          _SFD_SET_DATA_VALUE_PTR(21U, *c2_Fxs);
          _SFD_SET_DATA_VALUE_PTR(22U, *c2_Fus);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration
        (_mpcSetpointIntptCoupledMachineNumber_,chartInstance->chartNumber,
         chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization()
{
  return "nPvFgdNg4pGegV6ClEaV4B";
}

static void sf_opaque_initialize_c2_mpcSetpointIntptCoupled(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_mpcSetpointIntptCoupledInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_mpcSetpointIntptCoupled
    ((SFc2_mpcSetpointIntptCoupledInstanceStruct*) chartInstanceVar);
  initialize_c2_mpcSetpointIntptCoupled
    ((SFc2_mpcSetpointIntptCoupledInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_mpcSetpointIntptCoupled(void *chartInstanceVar)
{
  enable_c2_mpcSetpointIntptCoupled((SFc2_mpcSetpointIntptCoupledInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c2_mpcSetpointIntptCoupled(void *chartInstanceVar)
{
  disable_c2_mpcSetpointIntptCoupled((SFc2_mpcSetpointIntptCoupledInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_mpcSetpointIntptCoupled(void *chartInstanceVar)
{
  sf_c2_mpcSetpointIntptCoupled((SFc2_mpcSetpointIntptCoupledInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_mpcSetpointIntptCoupled
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_mpcSetpointIntptCoupled
    ((SFc2_mpcSetpointIntptCoupledInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_mpcSetpointIntptCoupled();/* state var info */
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

extern void sf_internal_set_sim_state_c2_mpcSetpointIntptCoupled(SimStruct* S,
  const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_mpcSetpointIntptCoupled();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_mpcSetpointIntptCoupled
    ((SFc2_mpcSetpointIntptCoupledInstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_mpcSetpointIntptCoupled
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c2_mpcSetpointIntptCoupled(S);
}

static void sf_opaque_set_sim_state_c2_mpcSetpointIntptCoupled(SimStruct* S,
  const mxArray *st)
{
  sf_internal_set_sim_state_c2_mpcSetpointIntptCoupled(S, st);
}

static void sf_opaque_terminate_c2_mpcSetpointIntptCoupled(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_mpcSetpointIntptCoupledInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_mpcSetpointIntptCoupled
      ((SFc2_mpcSetpointIntptCoupledInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_mpcSetpointIntptCoupled_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_mpcSetpointIntptCoupled
    ((SFc2_mpcSetpointIntptCoupledInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_mpcSetpointIntptCoupled(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_mpcSetpointIntptCoupled
      ((SFc2_mpcSetpointIntptCoupledInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_mpcSetpointIntptCoupled(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_mpcSetpointIntptCoupled_optimization_info();
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
      ssSetInputPortOptimOpts(S, 19, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 20, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,21);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,2);
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2185964428U));
  ssSetChecksum1(S,(1180195193U));
  ssSetChecksum2(S,(4234839415U));
  ssSetChecksum3(S,(1502425389U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_mpcSetpointIntptCoupled(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_mpcSetpointIntptCoupled(SimStruct *S)
{
  SFc2_mpcSetpointIntptCoupledInstanceStruct *chartInstance;
  chartInstance = (SFc2_mpcSetpointIntptCoupledInstanceStruct *)malloc(sizeof
    (SFc2_mpcSetpointIntptCoupledInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_mpcSetpointIntptCoupledInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_mpcSetpointIntptCoupled;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_mpcSetpointIntptCoupled;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_mpcSetpointIntptCoupled;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c2_mpcSetpointIntptCoupled;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c2_mpcSetpointIntptCoupled;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_mpcSetpointIntptCoupled;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_mpcSetpointIntptCoupled;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_mpcSetpointIntptCoupled;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_mpcSetpointIntptCoupled;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_mpcSetpointIntptCoupled;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_mpcSetpointIntptCoupled;
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

void c2_mpcSetpointIntptCoupled_method_dispatcher(SimStruct *S, int_T method,
  void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_mpcSetpointIntptCoupled(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_mpcSetpointIntptCoupled(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_mpcSetpointIntptCoupled(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_mpcSetpointIntptCoupled_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
