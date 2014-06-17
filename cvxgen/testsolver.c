/* Produced by CVXGEN, 2014-06-17 12:56:09 -0400.  */
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
  params.Fxs[6] = -1.9040724704913385;
  params.Fxs[7] = 0.23541635196352795;
  params.Fxs[8] = -0.9629902123701384;
  params.Fxs[9] = -0.3395952119597214;
  params.Fxs[10] = -0.865899672914725;
  params.Fxs[11] = 0.7725516732519853;
  params.Fus[0] = -0.23818512931704205;
  params.Fus[1] = -1.372529046100147;
  params.Fus[2] = 0.17859607212737894;
  params.Fus[3] = 1.1212590580454682;
  params.fs[0] = -0.774545870495281;
  params.fs[1] = -1.1121684642712744;
  params.fs[2] = -0.44811496977740495;
  params.fs[3] = 1.7455345994417217;
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.Q_final[0] = 1.9759954224729337;
  params.Q_final[3] = 0;
  params.Q_final[6] = 0;
  params.Q_final[1] = 0;
  params.Q_final[4] = 1.6723836759128137;
  params.Q_final[7] = 0;
  params.Q_final[2] = 0;
  params.Q_final[5] = 0;
  params.Q_final[8] = 1.9028341085383982;
  params.A[0] = 1.383003485172717;
  params.A[1] = -0.48802383468444344;
  params.A[2] = -1.631131964513103;
  params.A[3] = 0.6136436100941447;
  params.A[4] = 0.2313630495538037;
  params.A[5] = -0.5537409477496875;
  params.A[6] = -1.0997819806406723;
  params.A[7] = -0.3739203344950055;
  params.A[8] = -0.12423900520332376;
  params.B[0] = -0.923057686995755;
  params.B[1] = -0.8328289030982696;
  params.B[2] = -0.16925440270808823;
  params.d[0] = 1.442135651787706;
  params.d[1] = 0.34501161787128565;
  params.d[2] = -0.8660485502711608;
  params.Fx[0] = -0.8880899735055947;
  params.Fx[1] = -0.1815116979122129;
  params.Fx[2] = -1.17835862158005;
  params.Fx[3] = -1.1944851558277074;
  params.Fx[4] = 0.05614023926976763;
  params.Fx[5] = -1.6510825248767813;
  params.Fx[6] = -0.06565787059365391;
  params.Fx[7] = -0.5512951504486665;
  params.Fx[8] = 0.8307464872626844;
  params.Fx[9] = 0.9869848924080182;
  params.Fx[10] = 0.7643716874230573;
  params.Fx[11] = 0.7567216550196565;
  params.Fu[0] = -0.5055995034042868;
  params.Fu[1] = 0.6725392189410702;
  params.Fu[2] = -0.6406053441727284;
  params.Fu[3] = 0.29117547947550015;
  params.f[0] = -0.6967713677405021;
  params.f[1] = -0.21941980294587182;
  params.f[2] = -1.753884276680243;
  params.f[3] = -1.0292983112626475;
  params.Ff[0] = 1.8864104246942706;
  params.Ff[1] = -1.077663182579704;
  params.Ff[2] = 0.7659100437893209;
  params.Ff[3] = 0.6019074328549583;
  params.Ff[4] = 0.8957565577499285;
  params.Ff[5] = -0.09964555746227477;
  params.Ff[6] = 0.38665509840745127;
  params.Ff[7] = -1.7321223042686946;
  params.Ff[8] = -1.7097514487110663;
  params.Ff[9] = -1.2040958948116867;
  params.Ff[10] = -1.3925560119658358;
  params.Ff[11] = -1.5995826216742213;
  params.ff[0] = -1.4828245415645833;
  params.ff[1] = 0.21311092723061398;
  params.ff[2] = -1.248740700304487;
  params.ff[3] = 1.808404972124833;
  params.Ef[0] = 0.7264471152297065;
  params.Ef[1] = 0.16407869343908477;
  params.Ef[2] = 0.8287224032315907;
  params.Ef[3] = -0.9444533161899464;
  params.Ef[4] = 1.7069027370149112;
  params.Ef[5] = 1.3567722311998827;
  params.Ed[0] = 0.9052779937121489;
  params.Ed[1] = -0.07904017565835986;
  params.Ed[2] = 1.3684127435065871;
  params.Ed[3] = 0.979009293697437;
  params.Ed[4] = 0.6413036255984501;
  params.Ed[5] = 1.6559010680237511;
  params.ef[0] = 0.5346622551502991;
  params.ef[1] = -0.5362376605895625;
}
