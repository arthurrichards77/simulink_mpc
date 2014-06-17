function [z,info] = cvxgenSolve(x,xt,Q,R,Qf,A,B,d,Fx,Fu,f,Fxs,Fus,fs,Ef,Ed,ef,Ff,ff) 
%#codegen

%% pack'em
params.x_0 = x;
params.xt = xt;
params.d = d;

%% fixed params
params.A = A;
params.B = B;
params.Ef = Ef;
params.Ed = Ed;
params.ef = ef;
params.Ff = Ff;
params.ff = ff;
params.Fx = Fx;
params.Fu = Fu;
params.f = f;
params.Fxs = Fxs;
params.Fus = Fus;
params.fs = fs;
params.Q = Q;
params.R = R;
params.Q_final = Qf;

%% solve it
settings.verbose=0;
[vars,status] = csolve(params,settings);

%% repack outputs
xs = cell2mat(vars.x'); % row of states
us = [vars.u_0 cell2mat(vars.u')]; % column of inputs
zs = [us; xs]; % combine
z = reshape(zs,prod(size(zs)),1);

info = status.converged;
