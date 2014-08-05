%% double integrator MPC setup

% time step
dt = 0.25;

% system matrices x+ = Ax + Bu
A = [1 dt 0.5*dt*dt; 
     0 1 dt;
     0 0 1]; % states [pos; vel; acc]
B = [0.5*dt*dt  ;
     dt         ;
     1          ]; % inputs [delta-acc]

% adding hard control constraints    
Fx = [0 0 1 ;
     0 0 -1 ;
     0 0 0 ;
     0 0 0 ];
Fu = [0 ;
    0 ;
    1 ;
    -1 ];
f = [0.1 ; % control <= 0.1
    0.1 ;
    0.5 % move <= 0.5
        0.5 ]; 

% removing hard control constraints    
% Fx = [0 0 0 ;
%      0 0 0 ];
% Fu = [1 ;
%     -1 ];
% f = [0.5 % move <= 0.5
%         0.5 ]; 

% soft constraints: cost includes sum_i ( max{Cs_i*x + Ds_i*u - Ysmax, 0} )
% Fxs = [0 1 0; 
%      0 -1 0;
%      0 0 1;
%      0 0 -1];
% Fus = [0 ;
%      0 ;
%      0 ;
%      0 ];
% fs = [0.2; % vel <= 0.2
%         0.2;
%         0.1; % acc <= 0.1
%         0.1 ];     
    
    % soft constraints on vel only: cost includes sum_i ( max{Cs_i*x + Ds_i*u - Ysmax, 0} )
Fxs = [0 1 0; 
     0 -1 0];
Fus = [0 ;
     0 ];
fs = [0.2; % vel <= 0.2
        0.2 ];     
    
% terminal constraints Ff*x(N)<=ff;
Ff = 0.00001*[eye(2) [0;0]; -eye(2) [0;0]];
ff = ones(4,1); % effectively relaxed

% terminal constraints Ff*x(N)<=Ff;
% make sure control stays within limits
Ff = [0 0 1;
      0 0 -1];
ff = [0.1; 0.1];

% terminal equality constraints Ef*x(N)==ef
% Ef = [0 1 0; 0 0 1];
% ef = [0;0];

% no terminal equalities
Ef = [];
ef = [];

% cost 
% xN*Qf*xN + qf'*xN + sum (x'*Q*x + u'*R*u + q'*x + r'*u)
Q = diag([5 5 2]);
R = diag([10]);
qf = [0; 0; 0];
q = [0; 0; 0];
r = [0]; 

% try dlqr terminal cost
% [Kf,Qf] = dlqr(A,B,Q,R);

% lazy terminal cost
Qf = Q;

% horizon
T = 10;

% augment B, r and R to accommodate slacks for soft constraints
B = B*[1 0];
r = [r; 100]; % this captures cost weight on violations
R = blkdiag(R, 0.00001);

% couple them using the constraint matrices
Fx = [Fx;Fxs;zeros(1,size(A,1))]; % bottom row is for "slack >= 0" constraint
Fu = [Fu*[1 0]; Fus (0*fs - 1); [0 -1] ];
f = [f;fs;0];

% need to set the redundant soft constraint settings to compatible sizes,
% else coder gets in a knot
Fus = Fus*[1 0];

%% checking problem setup

% sizes
n = size(A,1);
m = size(B,2);
ell = size(Fx,1);
ellf = size(Ff,1);
ellef = size(Ef,1);
ells = size(Fxs,1);

% checks
if size(B,1)~=n,
    error('B must have same number of rows as A')
end
if size(A,2)~=n,
    error('A must be square')
end
if size(Q,2)~=n,
    error('Q must be the same size as A')
end
if size(Q,1)~=n,
    error('Q must be the same size as A')
end
if size(Fx,2)~=n,
    error('Fx must have same number of columns as A')
end
if size(Fu,1)~=ell,
    error('Fu must have same number of rows as Fx')
end
if size(Fu,2)~=m,
    error('Fu must have same number of columns as B')
end
if size(Fx,2)~=n,
    error('Fx must have same number of columns as A')
end
if size(Ff,2)~=n,
    error('Ff must have same number of columns as A')
end
if size(ff,1)~=ellf,
    error('ff must have same number of rows as Ff')
end
if (size(Ef,2)~=n) && (~isempty(Ef)),
    error('Ef must have same number of columns as A or be empty')
end
if size(ef,1)~=ellef,
    error('ef must have same number of rows as Ef')
end

%% trap the case with empty Ef so we don't have an empty signal
if isempty(Ef),
    Ef_block = zeros(1,n+1); % deliberate detectable mismatch with state size
else
    Ef_block = Ef;
end

%% compile MPC problem

% min z'*H*z + (gt*xt+g)'*z + sum(max(0,Ps*z-h))
% s.t. P*z <= h
%      C*z == b
%
% where h = hx*x0 + hc
% and b = bx*x0 + bd*d + b;

H = blkdiag(R,kron(eye(T-1),blkdiag(Q,R)),Qf);
P = blkdiag(Fu,kron(eye(T-1),[Fx Fu]),Ff);
C = [kron(eye(T),[-B eye(n)]) + kron([zeros(1,T); eye(T-1) zeros(T-1,1)],[zeros(n,m) -A]); zeros(ellef,m+(T-1)*(m+n)) Ef];

g = [r; repmat([q;r],T-1,1); qf];
hc = [repmat(f,T,1);ff];
hx = [-Fx; zeros((T-1)*ell + ellf,n)];
bx = [A; zeros(ellef+(T-1)*n,n)];
b = [zeros(T*n,1); ef];

Ps = blkdiag(Fus,kron(eye(T-1),[Fxs Fus]));
% check padding
Ps(1,T*(n+m))=0;
hcs = [repmat(fs,T,1)];
hxs = [-Fxs; zeros((T-1)*ells,n)];

% extra bit for offset free tracking
if ~isempty(Ef),
    bd = [kron(ones(T,1),eye(n)); [1 0 0; 0 1 0]];
else
    bd = [kron(ones(T,1),eye(n))];
end

% optional removal of disturbance modeling
%bd = 0*bd;

% term for tracking non-zero reference
gt = kron(ones(T,1),[zeros(2,n); -2*Q]);

%% goof - try sparse
% seems to help quadprog anyway, provided interior point algorithm is used

%H = sparse(H);
%P = sparse(P);
%C = sparse(C);

%% options
clear opts % make sure no hang-overs from previous runs
opts(1)=0; % 1 = assume diagonal Phi when solving
opts(2)=3; % Newton iterations
opts(3)=0; % 1 = use soft constraints