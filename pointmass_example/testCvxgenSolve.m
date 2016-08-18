%% dynamic settings

% dummy state
x = [0.1 0 0]';

% target state
xt = [0.2 0 0]';

% estimated disturbance
d = [0.1 0.6 2.4]'*0.001;

%% solve
[z_cvxgen,info] = cvxgenSolve(x,xt,Q,R,Qf,A,B,d,Fx,Fu,f,Fxs,Fus,fs,Ef,Ed,ef,Ff,ff) 
