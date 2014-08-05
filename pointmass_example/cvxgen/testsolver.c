/* Produced by CVXGEN, 2014-06-24 11:44:06 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: testsolver.c. */
/* Description: Basic test harness for solver.c. */
#include "solver.h"
Vars vars;
Params params;
Workspace work;
Settings settings;
#define NUMTESTS 0
int main(int argc, char **argv) {
  int num_iters;
#if (NUMTESTS > 0)
  int i;
  double time;
  double time_per;
#endif
  set_defaults();
  setup_indexing();
  load_default_data();
  /* Solve problem instance for the record. */
  settings.verbose = 1;
  num_iters = solve();
#ifndef ZERO_LIBRARY_MODE
#if (NUMTESTS > 0)
  /* Now solve multiple problem instances for timing purposes. */
  settings.verbose = 0;
  tic();
  for (i = 0; i < NUMTESTS; i++) {
    solve();
  }
  time = tocq();
  printf("Timed %d solves over %.3f seconds.\n", NUMTESTS, time);
  time_per = time / NUMTESTS;
  if (time_per > 1) {
    printf("Actual time taken per solve: %.3g s.\n", time_per);
  } else if (time_per > 1e-3) {
    printf("Actual time taken per solve: %.3g ms.\n", 1e3*time_per);
  } else {
    printf("Actual time taken per solve: %.3g us.\n", 1e6*time_per);
  }
#endif
#endif
  return 0;
}
void load_default_data(void) {
  params.x_0[0] = 0.20319161029830202;
  params.x_0[1] = 0.8325912904724193;
  params.x_0[2] = -0.8363810443482227;
  params.xt[0] = 0.04331042079065206;
  params.xt[1] = 1.5717878173906188;
  params.xt[2] = 1.5851723557337523;
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.Q[0] = 1.1255853104638363;
  params.Q[3] = 0;
  params.Q[6] = 0;
  params.Q[1] = 0;
  params.Q[4] = 1.2072428781381868;
  params.Q[7] = 0;
  params.Q[2] = 0;
  params.Q[5] = 0;
  params.Q[8] = 1.0514672033008299;
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.R[0] = 1.4408098436506365;
  params.Fxs[0] = -1.8804951564857322;
  params.Fxs[1] = -0.17266710242115568;
  params.Fxs[2] = 0.596576190459043;
  params.Fxs[3] = -0.8860508694080989;
  params.Fxs[4] = 0.7050196079205251;
  params.Fxs[5] = 0.3634512696654033;
  params.Fus[0] = -1.9040724704913385;
  params.Fus[1] = 0.23541635196352795;
  params.fs[0] = -0.9629902123701384;
  params.fs[1] = -0.3395952119597214;
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.Q_final[0] = 1.2835250817713186;
  params.Q_final[3] = 0;
  params.Q_final[6] = 0;
  params.Q_final[1] = 0;
  params.Q_final[4] = 1.6931379183129964;
  params.Q_final[7] = 0;
  params.Q_final[2] = 0;
  params.Q_final[5] = 0;
  params.Q_final[8] = 1.4404537176707395;
  params.A[0] = -1.372529046100147;
  params.A[1] = 0.17859607212737894;
  params.A[2] = 1.1212590580454682;
  params.A[3] = -0.774545870495281;
  params.A[4] = -1.1121684642712744;
  params.A[5] = -0.44811496977740495;
  params.A[6] = 1.7455345994417217;
  params.A[7] = 1.9039816898917352;
  params.A[8] = 0.6895347036512547;
  params.B[0] = 1.6113364341535923;
  params.B[1] = 1.383003485172717;
  params.B[2] = -0.48802383468444344;
  params.d[0] = -1.631131964513103;
  params.d[1] = 0.6136436100941447;
  params.d[2] = 0.2313630495538037;
  params.Fx[0] = -0.5537409477496875;
  params.Fx[1] = -1.0997819806406723;
  params.Fx[2] = -0.3739203344950055;
  params.Fx[3] = -0.12423900520332376;
  params.Fx[4] = -0.923057686995755;
  params.Fx[5] = -0.8328289030982696;
  params.Fx[6] = -0.16925440270808823;
  params.Fx[7] = 1.442135651787706;
  params.Fx[8] = 0.34501161787128565;
  params.Fx[9] = -0.8660485502711608;
  params.Fx[10] = -0.8880899735055947;
  params.Fx[11] = -0.1815116979122129;
  params.Fu[0] = -1.17835862158005;
  params.Fu[1] = -1.1944851558277074;
  params.Fu[2] = 0.05614023926976763;
  params.Fu[3] = -1.6510825248767813;
  params.f[0] = -0.06565787059365391;
  params.f[1] = -0.5512951504486665;
  params.f[2] = 0.8307464872626844;
  params.f[3] = 0.9869848924080182;
  params.Ff[0] = 0.7643716874230573;
  params.Ff[1] = 0.7567216550196565;
  params.Ff[2] = -0.5055995034042868;
  params.Ff[3] = 0.6725392189410702;
  params.Ff[4] = -0.6406053441727284;
  params.Ff[5] = 0.29117547947550015;
  params.ff[0] = -0.6967713677405021;
  params.ff[1] = -0.21941980294587182;
}
