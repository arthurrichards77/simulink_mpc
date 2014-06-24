%% dynamic settings

% dummy state
x = [0.8 0 0]';

% dummy previous solution
z0 = 0*g+0.01;

% target state
xt = [-1 0 0]';

% estimated disturbance
d = 0*[0 0.05 0]';

%% solve
[z_cvxgen,info] = cvxgenSolve(x,xt,Q,R,Qf,A,B,d,Fx,Fu,f,Fxs,Fus,fs,Ef,Ed,ef,Ff,ff) 
