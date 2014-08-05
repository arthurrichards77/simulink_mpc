#ifndef __c2_mpcSetpointIntpt_h__
#define __c2_mpcSetpointIntpt_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_sjVaXfrJc3wv5faWU7kmQtG
#define struct_sjVaXfrJc3wv5faWU7kmQtG

typedef struct sjVaXfrJc3wv5faWU7kmQtG
{
  boolean_T LT;
} c2_sjVaXfrJc3wv5faWU7kmQtG;

#else

typedef struct sjVaXfrJc3wv5faWU7kmQtG c2_sjVaXfrJc3wv5faWU7kmQtG;

#endif

#ifndef struct_sKLpTDgVdadEcWmkZEqDlEH
#define struct_sKLpTDgVdadEcWmkZEqDlEH

typedef struct sKLpTDgVdadEcWmkZEqDlEH
{
  uint32_T LT;
  uint32_T UT;
  uint32_T UHESS;
  uint32_T SYM;
  uint32_T POSDEF;
  uint32_T RECT;
  uint32_T TRANSA;
} c2_sKLpTDgVdadEcWmkZEqDlEH;

#else

typedef struct sKLpTDgVdadEcWmkZEqDlEH c2_sKLpTDgVdadEcWmkZEqDlEH;

#endif

#ifndef struct_s9s8BC13iTohZXRbLMSIDHE
#define struct_s9s8BC13iTohZXRbLMSIDHE

typedef struct s9s8BC13iTohZXRbLMSIDHE
{
  boolean_T CaseSensitivity;
  boolean_T StructExpand;
  boolean_T PartialMatching;
} c2_s9s8BC13iTohZXRbLMSIDHE;

#else

typedef struct s9s8BC13iTohZXRbLMSIDHE c2_s9s8BC13iTohZXRbLMSIDHE;

#endif

#ifndef struct_sLakZ0H1iioO7nmpFVlciOC
#define struct_sLakZ0H1iioO7nmpFVlciOC

typedef struct sLakZ0H1iioO7nmpFVlciOC
{
  boolean_T UT;
} c2_sLakZ0H1iioO7nmpFVlciOC;

#else

typedef struct sLakZ0H1iioO7nmpFVlciOC c2_sLakZ0H1iioO7nmpFVlciOC;

#endif

typedef struct {
  const char * context;
  const char * name;
  const char * dominantType;
  const char * resolved;
  uint32_T fileTimeLo;
  uint32_T fileTimeHi;
  uint32_T mFileTimeLo;
  uint32_T mFileTimeHi;
} c2_ResolvedFunctionInfo;

typedef struct {
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_mpcSetpointIntpt;
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
} SFc2_mpcSetpointIntptInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_mpcSetpointIntpt_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c2_mpcSetpointIntpt_get_check_sum(mxArray *plhs[]);
extern void c2_mpcSetpointIntpt_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
