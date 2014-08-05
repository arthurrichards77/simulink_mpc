%% coupled masses MPC setup

% continuous system
Ac = [zeros(6) eye(6); -2*eye(6) zeros(6)];
Ac(7:11,2:6) = Ac(7:11,2:6) + eye(5);
Ac(8:12,1:5) = Ac(8:12,1:5) + eye(5);
Bc = zeros(12,3);
Bc(7,1) = 1;
Bc(8,1) = -1;
Bc(9,2) = 1;
Bc(11,2) = -1;
Bc(10,3) = 1;
Bc(12,3) = -1;

%% discretize

% time step
dt = 0.5;

% discretize
ssc = ss(Ac,Bc,eye(12),0*Bc);
ssd = c2d(ssc,dt);
[A,B,~,~] = ssdata(ssd);

%% LQR just for testing
Q = eye(12);
R = eye(3);
Klqr = dlqr(A,B,Q,R);

%% constraints

% adding hard control constraints    
Fx = [zeros(6,12)];
Fu = [eye(3); -eye(3) ];
f = [.4*ones(6,1)]; 
    
% soft constraints on mass positions
Fxs = [eye(6) zeros(6);
      -eye(6) zeros(6)]*100;
Fus = [zeros(12,3)];
fs = [0.4*ones(12,1) ]*100; 
    
% terminal constraints Ff*x(N)<=Ff;
% leave effectively relaxed for now
Ff = [[1;1] zeros(2,11)];
ff = [.3; .3];

% no terminal equality constraints
% Ef*xN + Ed*d = ef where d = disturbance
Ef = [];
ef = [];
Ed = [];

% cost 
% xN*Qf*xN + qf'*xN + sum (x'*Q*x + u'*R*u + q'*x + r'*u)
Q = eye(12);
R = eye(3);
qf = zeros(12,1);
q = qf;
r = zeros(3,1); 

% try dlqr terminal cost
[Kf,Qf] = dlqr(A,B,Q,R);

% lazy terminal cost
%Qf = Q;

% horizon
T = 10;

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
    Ef_sig = zeros(1,n+1); % deliberate detectable mismatch with state size
else
    Ef_sig = Ef;
end

%% compile MPC problem

% min z'*H*z + (gt*xt+g)'*z + sum(max(0,Ps*z-h))
% s.t. P*z <= h
%      C*z == b
%
% where h = hx*x0 + hc
% and b = bx*x0 + bd*d

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
    bd = [kron(ones(T,1),eye(n)); -Ed];
    Ef_block = Ef; 
    Ed_block = Ed;
    ef_block = ef;
else
    bd = [kron(ones(T,1),eye(n))];
    Ef_block = zeros(2*n,1); % dummy to signal no terminal eqs
    Ed_block = Ef_block;
    ef_block = Ef_block;
end

% optional removal of disturbance modeling
%bd = 0*bd;

% term for tracking non-zero reference
gt = kron(ones(T,1),[zeros(1,n); -2*Q]);

%% goof - try sparse
% seems to help quadprog anyway, provided interior point algorithm is used

%H = sparse(H);
%P = sparse(P);
%C = sparse(C);

%% options
opts=[];
opts(1)=1; % 1 = assume diagonal Phi when solving
opts(2)=5; % Newton iterations
opts(3)=1; % 1 = use soft constraints
opts(4)=0; % 1 = checking on
opts(5)=1; % 1 = Pade off
opts(6)=0; % 1 = no sparsity exploitation
opts(7)=0.01; % tuning of barrier weight kappa
opts(8)=3; % number of barrier iterations
opts(9)=1e-3; % Newton iter termination on residual
opts(10)=1; % KS parameter rho