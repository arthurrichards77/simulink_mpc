%% common setup of state etc

% dummy state
x = [0.1 0 0]';

% target state
xt = [0.2 0 0]';

% estimated disturbance
d = [0.1 0.6 2.4]'*0.001;

%% starting guess for those that need it

% dummy previous solution
z0 = 0*g + 0.01;

%% build QP

% state-dependent weights etc
g1 = g + gt*xt;
h1 = hc + hx*x;
b1 = bx*x + bd*d;
hs1 = hxs*x + hcs;

%% K-S solver

% max number of Newton iters
opts(2)=11;

% soft cons 1=on 0=ignore
opts(3)=1;

% checking
opts(4)=0;

% turn off Pade with opt 5 = 1
opts(5)=1;

% Newton tolerance
opts(9)=1e-4;

[z_ks,info_ks] = mpcsolve(H,g1,P,h1,C,b1,z0,A,B,Fx,Fu,Ff,Q,R,Qf,opts,Ps,hs1,Ef,Fxs,Fus);
info_ks

%% CVX solver

[z_cvxgen,info_cvx] = cvxgenSolve(x,xt,Q,R,Qf,A,B,d,Fx,Fu,f,Fxs,Fus,fs,Ef,Ed,ef,Ff,ff);
info_cvx

%% IPOPT solver

[z_ip,info_ip] = ipoptSolve(H,g1,P,h1,C,b1,z0,A,B,Fx,Fu,Ff,Q,R,Qf,opts,Ps,hs1,Ef,Fxs,Fus);
info_ip

%% IPOPT solver 2

[z_ip2,info_ip2] = ipoptSolve2(H,g1,P,h1,C,b1,z0,A,B,Fx,Fu,Ff,Q,R,Qf,opts,Ps,hs1,Ef,Fxs,Fus);
info_ip2

%% compare

cf_ks_cvx_ipopt = [z_ks z_cvxgen z_ip z_ip2]