
% dummy state
x = [-15.7227   -1.4466   -0.0999]';

% dummy previous solution
z0 = [  0.0051
    1.0001
   -0.7431
   -0.0032
    0.0992
   -0.0029
    1.0001
   -0.6925
   -0.0034
    0.0989
    0.0001
    1.0001
   -0.6296
   -0.0043
    0.0981
   -0.0002
    1.0001
   -0.5596
   -0.0056
    0.0942
   -0.0153
    1.0001
   -0.4808
   -0.0125
    0.0730
   -0.0225
    1.0001
   -0.3997
   -0.0263
    0.0431
   -0.0171
    1.0001
   -0.3169
   -0.0450
    0.0168
   -0.0074
    1.0001
   -0.2561
   -0.0625
    0.0013
   -0.0005
    1.0001
   -0.1789
   -0.0731
   -0.0023
         0
    1.0001
   -0.1972
   -0.0737
   -0.0023];

% target state
xt = [2 0 0]';

% estimated disturbance
d = [0.1 0.6 2.4]'*0.001;

% state-dependent weights etc
g1 = g + gt*xt;
h1 = hc + hx*x;
b1 = bx*x + bd*d;
hs1 = hxs*x + hcs;

% options 
opts(2) = 5; % just one iteration
opts(4) = 1; % turn on all checks

[z,info] = mpcsolve(H,g1,P,h1,C,b1,z0,A,B,Fx,Fu,Ff,Q,R,Qf,opts,Ps,hs1,Ef,Fxs,Fus)
