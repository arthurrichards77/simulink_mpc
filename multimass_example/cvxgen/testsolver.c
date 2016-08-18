/* Produced by CVXGEN, 2014-08-06 08:56:45 -0400.  */
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
  params.x_0[3] = 0.04331042079065206;
  params.x_0[4] = 1.5717878173906188;
  params.x_0[5] = 1.5851723557337523;
  params.x_0[6] = -1.497658758144655;
  params.x_0[7] = -1.171028487447253;
  params.xt[0] = -1.7941311867966805;
  params.xt[1] = -0.23676062539745413;
  params.xt[2] = -1.8804951564857322;
  params.xt[3] = -0.17266710242115568;
  params.xt[4] = 0.596576190459043;
  params.xt[5] = -0.8860508694080989;
  params.xt[6] = 0.7050196079205251;
  params.xt[7] = 0.3634512696654033;
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.Q[0] = 1.0239818823771654;
  params.Q[8] = 0;
  params.Q[16] = 0;
  params.Q[24] = 0;
  params.Q[32] = 0;
  params.Q[40] = 0;
  params.Q[48] = 0;
  params.Q[56] = 0;
  params.Q[1] = 0;
  params.Q[9] = 1.5588540879908819;
  params.Q[17] = 0;
  params.Q[25] = 0;
  params.Q[33] = 0;
  params.Q[41] = 0;
  params.Q[49] = 0;
  params.Q[57] = 0;
  params.Q[2] = 0;
  params.Q[10] = 0;
  params.Q[18] = 1.2592524469074653;
  params.Q[26] = 0;
  params.Q[34] = 0;
  params.Q[42] = 0;
  params.Q[50] = 0;
  params.Q[58] = 0;
  params.Q[3] = 0;
  params.Q[11] = 0;
  params.Q[19] = 0;
  params.Q[27] = 1.4151011970100695;
  params.Q[35] = 0;
  params.Q[43] = 0;
  params.Q[51] = 0;
  params.Q[59] = 0;
  params.Q[4] = 0;
  params.Q[12] = 0;
  params.Q[20] = 0;
  params.Q[28] = 0;
  params.Q[36] = 1.2835250817713186;
  params.Q[44] = 0;
  params.Q[52] = 0;
  params.Q[60] = 0;
  params.Q[5] = 0;
  params.Q[13] = 0;
  params.Q[21] = 0;
  params.Q[29] = 0;
  params.Q[37] = 0;
  params.Q[45] = 1.6931379183129964;
  params.Q[53] = 0;
  params.Q[61] = 0;
  params.Q[6] = 0;
  params.Q[14] = 0;
  params.Q[22] = 0;
  params.Q[30] = 0;
  params.Q[38] = 0;
  params.Q[46] = 0;
  params.Q[54] = 1.4404537176707395;
  params.Q[62] = 0;
  params.Q[7] = 0;
  params.Q[15] = 0;
  params.Q[23] = 0;
  params.Q[31] = 0;
  params.Q[39] = 0;
  params.Q[47] = 0;
  params.Q[55] = 0;
  params.Q[63] = 1.1568677384749633;
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.R[0] = 1.5446490180318446;
  params.R[2] = 0;
  params.R[1] = 0;
  params.R[3] = 1.780314764511367;
  params.Fxs[0] = -0.774545870495281;
  params.Fxs[1] = -1.1121684642712744;
  params.Fxs[2] = -0.44811496977740495;
  params.Fxs[3] = 1.7455345994417217;
  params.fs[0] = 1.9039816898917352;
  params.fs[1] = 0.6895347036512547;
  params.fs[2] = 1.6113364341535923;
  params.fs[3] = 1.383003485172717;
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.Q_final[0] = 1.3779940413288891;
  params.Q_final[8] = 0;
  params.Q_final[16] = 0;
  params.Q_final[24] = 0;
  params.Q_final[32] = 0;
  params.Q_final[40] = 0;
  params.Q_final[48] = 0;
  params.Q_final[56] = 0;
  params.Q_final[1] = 0;
  params.Q_final[9] = 1.0922170088717242;
  params.Q_final[17] = 0;
  params.Q_final[25] = 0;
  params.Q_final[33] = 0;
  params.Q_final[41] = 0;
  params.Q_final[49] = 0;
  params.Q_final[57] = 0;
  params.Q_final[2] = 0;
  params.Q_final[10] = 0;
  params.Q_final[18] = 1.6534109025235362;
  params.Q_final[26] = 0;
  params.Q_final[34] = 0;
  params.Q_final[42] = 0;
  params.Q_final[50] = 0;
  params.Q_final[58] = 0;
  params.Q_final[3] = 0;
  params.Q_final[11] = 0;
  params.Q_final[19] = 0;
  params.Q_final[27] = 1.557840762388451;
  params.Q_final[35] = 0;
  params.Q_final[43] = 0;
  params.Q_final[51] = 0;
  params.Q_final[59] = 0;
  params.Q_final[4] = 0;
  params.Q_final[12] = 0;
  params.Q_final[20] = 0;
  params.Q_final[28] = 0;
  params.Q_final[36] = 1.361564763062578;
  params.Q_final[44] = 0;
  params.Q_final[52] = 0;
  params.Q_final[60] = 0;
  params.Q_final[5] = 0;
  params.Q_final[13] = 0;
  params.Q_final[21] = 0;
  params.Q_final[29] = 0;
  params.Q_final[37] = 0;
  params.Q_final[45] = 1.2250545048398318;
  params.Q_final[53] = 0;
  params.Q_final[61] = 0;
  params.Q_final[6] = 0;
  params.Q_final[14] = 0;
  params.Q_final[22] = 0;
  params.Q_final[30] = 0;
  params.Q_final[38] = 0;
  params.Q_final[46] = 0;
  params.Q_final[54] = 1.4065199163762485;
  params.Q_final[62] = 0;
  params.Q_final[7] = 0;
  params.Q_final[15] = 0;
  params.Q_final[23] = 0;
  params.Q_final[31] = 0;
  params.Q_final[39] = 0;
  params.Q_final[47] = 0;
  params.Q_final[55] = 0;
  params.Q_final[63] = 1.4689402486991692;
  params.A[0] = -0.923057686995755;
  params.A[1] = -0.8328289030982696;
  params.A[2] = -0.16925440270808823;
  params.A[3] = 1.442135651787706;
  params.A[4] = 0.34501161787128565;
  params.A[5] = -0.8660485502711608;
  params.A[6] = -0.8880899735055947;
  params.A[7] = -0.1815116979122129;
  params.A[8] = -1.17835862158005;
  params.A[9] = -1.1944851558277074;
  params.A[10] = 0.05614023926976763;
  params.A[11] = -1.6510825248767813;
  params.A[12] = -0.06565787059365391;
  params.A[13] = -0.5512951504486665;
  params.A[14] = 0.8307464872626844;
  params.A[15] = 0.9869848924080182;
  params.A[16] = 0.7643716874230573;
  params.A[17] = 0.7567216550196565;
  params.A[18] = -0.5055995034042868;
  params.A[19] = 0.6725392189410702;
  params.A[20] = -0.6406053441727284;
  params.A[21] = 0.29117547947550015;
  params.A[22] = -0.6967713677405021;
  params.A[23] = -0.21941980294587182;
  params.A[24] = -1.753884276680243;
  params.A[25] = -1.0292983112626475;
  params.A[26] = 1.8864104246942706;
  params.A[27] = -1.077663182579704;
  params.A[28] = 0.7659100437893209;
  params.A[29] = 0.6019074328549583;
  params.A[30] = 0.8957565577499285;
  params.A[31] = -0.09964555746227477;
  params.A[32] = 0.38665509840745127;
  params.A[33] = -1.7321223042686946;
  params.A[34] = -1.7097514487110663;
  params.A[35] = -1.2040958948116867;
  params.A[36] = -1.3925560119658358;
  params.A[37] = -1.5995826216742213;
  params.A[38] = -1.4828245415645833;
  params.A[39] = 0.21311092723061398;
  params.A[40] = -1.248740700304487;
  params.A[41] = 1.808404972124833;
  params.A[42] = 0.7264471152297065;
  params.A[43] = 0.16407869343908477;
  params.A[44] = 0.8287224032315907;
  params.A[45] = -0.9444533161899464;
  params.A[46] = 1.7069027370149112;
  params.A[47] = 1.3567722311998827;
  params.A[48] = 0.9052779937121489;
  params.A[49] = -0.07904017565835986;
  params.A[50] = 1.3684127435065871;
  params.A[51] = 0.979009293697437;
  params.A[52] = 0.6413036255984501;
  params.A[53] = 1.6559010680237511;
  params.A[54] = 0.5346622551502991;
  params.A[55] = -0.5362376605895625;
  params.A[56] = 0.2113782926017822;
  params.A[57] = -1.2144776931994525;
  params.A[58] = -1.2317108144255875;
  params.A[59] = 0.9026784957312834;
  params.A[60] = 1.1397468137245244;
  params.A[61] = 1.8883934547350631;
  params.A[62] = 1.4038856681660068;
  params.A[63] = 0.17437730638329096;
  params.B[0] = -1.6408365219077408;
  params.B[1] = -0.04450702153554875;
  params.B[2] = 1.7117453902485025;
  params.B[3] = 1.1504727980139053;
  params.B[4] = -0.05962309578364744;
  params.B[5] = -0.1788825540764547;
  params.B[6] = -1.1280569263625857;
  params.B[7] = -1.2911464767927057;
  params.B[8] = -1.7055053231225696;
  params.B[9] = 1.56957275034837;
  params.B[10] = 0.5607064675962357;
  params.B[11] = -1.4266707301147146;
  params.B[12] = -0.3434923211351708;
  params.B[13] = -1.8035643024085055;
  params.B[14] = -1.1625066019105454;
  params.B[15] = 0.9228324965161532;
  params.d[0] = 0.6044910817663975;
  params.d[1] = -0.0840868104920891;
  params.d[2] = -0.900877978017443;
  params.d[3] = 0.608892500264739;
  params.d[4] = 1.8257980452695217;
  params.d[5] = -0.25791777529922877;
  params.d[6] = -1.7194699796493191;
  params.d[7] = -1.7690740487081298;
  params.Fu[0] = -1.6685159248097703;
  params.Fu[1] = 1.8388287490128845;
  params.Fu[2] = 0.16304334474597537;
  params.Fu[3] = 1.3498497306788897;
  params.f[0] = -1.3198658230514613;
  params.f[1] = -0.9586197090843394;
  params.f[2] = 0.7679100474913709;
  params.f[3] = 1.5822813125679343;
  params.Ff[0] = -0.6372460621593619;
  params.Ff[1] = -1.741307208038867;
  params.Ff[2] = 1.456478677642575;
  params.Ff[3] = -0.8365102166820959;
  params.Ff[4] = 0.9643296255982503;
  params.Ff[5] = -1.367865381194024;
  params.Ff[6] = 0.7798537405635035;
  params.Ff[7] = 1.3656784761245926;
  params.ff[0] = 0.9086083149868371;
}
