% check flag
opts(4)=0;

% diag flag
opts(1)=0;

% number of iters
opts(2)=11;

% soft cons 1=on 0=ignore
opts(3)=1;

% checking
opts(4)=0;

% turn off Pade with opt 5 = 1
opts(5)=1;

% dummy state
x = [0.1 0 0]';

% dummy previous solution
z0 = 0*g+0.01;

% target state
xt = [0 0 0]';

% estimated disturbance
d = [0 0.05 0]';

% state-dependent weights etc
g1 = g + gt*xt;
h1 = hc + hx*x;
b1 = bx*x + bd*d;
hs1 = hxs*x + hcs;

[z_ks,info] = mpcsolve(H,g1,P,h1,C,b1,z0,A,B,Fx,Fu,Ff,Q,R,Qf,opts,Ps,hs1,Ef,Fxs,Fus);
info
