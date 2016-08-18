#include <stdio.h>
#include <math.h>
#include "mpcsolve_outer.h"

int printVec(double v[], int n) {

  int ii;

  printf("[\n");
  for (ii=0;ii<n;ii++) printf("%lf\n", v[ii]);
  printf("]\n");

  return(ii);

}

int main() {

  double x[3] = {0.0, 0.0, 0.0};

  double xt[3] = {0.0, 0.0, 0.0};

  double d[3] = {0, 0.05, 0.0};

  double z0[40] = {0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,
    0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,
    0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,
    0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,
    0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01};

  double z[40];

  double info[4];

  int ii;

  printVec(x,3);
  printVec(z0,40);

  for (ii=0;ii<1000;ii++) mpcsolve_outer(x,xt,d,z0,z,info);

  printVec(z,40);
  printVec(info,4);

  return(0);
}
