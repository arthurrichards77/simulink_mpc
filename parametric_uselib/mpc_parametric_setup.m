% now includes parametric constraints

%% setup path for KS solver
addpath('../ks_solver')

%% double integrator MPC setup

% time step
dt = 0.25;

% system matrices x+ = A*x + B*u + d
A = [1 dt 0.5*dt*dt; 
     0 1 dt;
     0 0 1]; % states [pos; vel; acc]
B = [0.5*dt*dt  ;
     dt         ;
     1          ]; % inputs [delta-acc]

% adding hard control constraints 
% Fx*x + Fu*u  + Fp*p <= f
Fx = [0 0 1 ;
     0 0 -1 ;
     0 0 0 ;
     0 0 0 ];
Fu = [0 ;
    0 ;
    1 ;
    -1 ];
Fp = zeros(4,1); % single parameter has nothing to do here
f = [0.1 ; % control <= 0.1
    0.1 ;
    0.5 % move <= 0.5
        0.5 ]; 
    
% penalty weight for soft constraints
softWt = 100;
% soft constraints on velocity only    
% Fxs*x + Fus*u  + Fps*p <= fs
Fxs = [0 1 0; 
     0 -1 0]*softWt;
Fus = [0 ;
     0 ]*softWt;
Fps = [1; 1]*softWt; %
fs = [0.2; % vel <= 0.2
        0.2 ]*softWt; 
    
% hard terminal state constraints Fxf*x(N) + Fpf*p <= ff;
Fxf = [0 0 1;
      0 0 -1];
Fpf = [0; 0]; % no parameter dependency here
ff = [0.1; 0.1]; % make sure control stays within limits

% terminal equality constraints Ef*x(N) + Ed*d ==ef
% Ef = eye(3)-A;
% Ef = Ef(1:2,:); % otherwise just get a zero row
% %Ef = [0 1 0; 0 0 1];
% ef = [0;0];
% remove terminal equality constraints
Ef = [];
ef = [];
Ed = []; % dependency on disturbance

% cost 
% xN*Qf*xN + qf'*xN + sum (x'*Q*x + u'*R*u + q'*x + r'*u)
Q = diag([5 5 2]);
R = diag([5]);
qf = [0; 0; 0];
q = [0; 0; 0];
r = [0]; 

% try dlqr terminal cost
% [Kf,Qf] = dlqr(A,B,Q,R);
% lazy terminal cost
Qf = Q;

% horizon
T = 10;