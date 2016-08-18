/*
 * _coder_mpcsolve_outer_mex.c
 *
 * Code generation for function 'mpcsolve_outer'
 *
 */

/* Include files */
#include "mex.h"
#include "_coder_mpcsolve_outer_api.h"

/* Function Declarations */
static void mpcsolve_outer_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

/* Variable Definitions */
emlrtContext emlrtContextGlobal = { true, false, EMLRT_VERSION_INFO, NULL, "mpcsolve_outer", NULL, false, {2045744189U,2170104910U,2743257031U,4284093946U}, NULL };
void *emlrtRootTLSGlobal = NULL;

/* Function Definitions */
static void mpcsolve_outer_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  const mxArray *outputs[2];
  const mxArray *inputs[28];
  int n = 0;
  int nOutputs = (nlhs < 1 ? 1 : nlhs);
  int nInputs = nrhs;
  emlrtStack st = { NULL, NULL, NULL };
  /* Module initialization. */
  mpcsolve_outer_initialize(&emlrtContextGlobal);
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs < 28) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooFewInputsConstants", 9, mxCHAR_CLASS, (int)strlen(mexFunctionName()), mexFunctionName(), mxCHAR_CLASS, 14, "mpcsolve_outer", mxCHAR_CLASS, 14, "mpcsolve_outer");
  }
  if (nrhs != 28) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, mxINT32_CLASS, 28, mxCHAR_CLASS, 14, "mpcsolve_outer");
  } else if (nlhs > 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, mxCHAR_CLASS, 14, "mpcsolve_outer");
  }
  /* Temporary copy for mex inputs. */
  for (n = 0; n < nInputs; ++n) {
    inputs[n] = prhs[n];
  }
  /* Call the function. */
  mpcsolve_outer_api(inputs, outputs);
  /* Copy over outputs to the caller. */
  for (n = 0; n < nOutputs; ++n) {
    plhs[n] = emlrtReturnArrayR2009a(outputs[n]);
  }
  /* Module finalization. */
  mpcsolve_outer_terminate();
}

void mpcsolve_outer_atexit_wrapper(void)
{
   mpcsolve_outer_atexit();
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  /* Initialize the memory manager. */
  mexAtExit(mpcsolve_outer_atexit_wrapper);
  /* Dispatch the entry-point. */
  mpcsolve_outer_mexFunction(nlhs, plhs, nrhs, prhs);
}
/* End of code generation (_coder_mpcsolve_outer_mex.c) */
