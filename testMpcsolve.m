% check flag
opts(4)=1;

% diag flag
opts(1)=0;

% dummy state
x = [0.8 0 0]';

% dummy previous solution
z0 = 0*g+0.01;

% target state
xt = [-1 0 0]';

% estimated disturbance
d = [0 0.05 0]';

% state-dependent weights etc
g1 = g + gt*xt;
h1 = hc + hx*x;
b1 = bx*x + bd*d;
hs1 = hxs*x + hcs;

[z,info] = mpcsolve(H,g1,P,h1,C,b1,z0,A,B,Fx,Fu,Ff,Q,R,Qf,opts,Ps,hs1,Ef,Fxs,Fus)
