function [z,info] = mpcsolve_outer(x,xt,d,H,g,gt,P,hc,hx,C,bx,bd,z0,A,B,Fx,Fu,Ff,Q,R,Qf,opts,Ps,hcs,hxs,Ef,Fxs,Fus)
%#codegen

% this version just takes all constant matrices and, separately, the
% dynamic state, stage target and disturbance estimate

% state-dependent weights etc
g1 = g + gt*xt;
h1 = hc + hx*x;
b1 = bx*x + bd*d;
hs1 = hxs*x + hcs;

% solve it
[z,info] = mpcsolve(H,g1,P,h1,C,b1,z0,A,B,Fx,Fu,Ff,Q,R,Qf,opts,Ps,hs1,Ef,Fxs,Fus);
