function [H,g,gt,P,hx,hc,C,bx,bd,Ps,hxs,hcs,Ef_block,Ed_block,ef_block,hp,hps] = buildmatrices(A,B,Q,R,q,r,Qf,qf,T,Fx,Fu,f,Fxs,Fus,fs,Fxf,ff,Ef,ef,Ed,Fp,Fps,Fpf)
%
% MPC for system x+ = A*x + B*u + d
% tracking target state xt
% minimize sum {x'*Q*x + u'*R*u + q'*x + r'*u} + x(T)*Qf*x(T) + qf'*x(T)
% hard constraints Fx*x + Fu*u <= f
% soft constraints Fxs*x + Fus*u <= fs
% hard terminal constraints Ff*x(T) <= ff
% terminal equality constraints Ef*x(T) == ef + Ed*d
%
% Outputs matrices for QP of the form:
%
% min z'*H*z + (gt*xt+g)'*z + sum(max(0,Ps*z-hs))
% s.t. P*z <= h
%      C*z == b
%
% where h = hx*x0 + hc
% where hs = hxs*x0 + hcs
% and b = bx*x0 + bd*d
% 

%% checking problem setup

% sizes
n = size(A,1); % number of states
m = size(B,2); % number of inputs
ell = size(Fx,1); % number of hard constraints
ellf = size(Fxf,1); % number of terminal state constraints
ellef = size(Ef,1); % number of terminal equality constraints
ells = size(Fxs,1); % number of soft constraints

% checks
assert(all(size(A)==[n n]),'A must be n x n')
assert(all(size(B)==[n m]),'B must be n x m')
assert(all(size(Q)==size(A)),'Q must be same size as A')
if size(Fx,2)~=n,
    error('Fx must have same number of columns as A')
end
if size(Fu,1)~=ell,
    error('Fu must have same number of rows as Fx')
end
if size(Fu,2)~=m,
    error('Fu must have same number of columns as B')
end
if size(f,1)~=ell,
    error('f must have same number of rows as Fx')
end
if size(Fx,2)~=n,
    error('Fx must have same number of columns as A')
end
if size(Fxf,2)~=n,
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

% test soft constraint sizing
assert(all(size(Fxs)==[ells n]),'Size Fxs')
assert(all(size(Fus)==[ells m]),'Size Fus')
assert(all(size(fs)==[ells 1]),'Size fs')

% test for optional parametric constraints
if ~exist('Fp','var'),
    warning('No parametric constraints specified')
    ellp = 0; % number of parameters
elseif isempty(Fp),
    warning('No parametric constraints specified')
    ellp = 0; % number of parameters
else
    ellp = size(Fp,2); % number of parameters
    % must also provide Fps and Fpf
    assert(exist('Fps','var')>0,'Must specify Fps with parametric constraints')
    assert(exist('Fpf','var')>0,'Must specify Fpf with parametric constraints')
    % and they must be compatible sizes
    assert(all(size(Fp)==[ell ellp]),'Fp must be ell x ellp')
    assert(all(size(Fps)==[ells ellp]),'Fp must be ell x ellp')
    assert(all(size(Fpf)==[ellf ellp]),'Fp must be ell x ellp')
end

%% compile MPC problem

% min z'*H*z + (gt*xt+g)'*z + sum(max(0,Ps*z-hs))
% s.t. P*z <= h
%      C*z == b
%
% where h = hx*x0 + hp*p + hc
% where hs = hxs*x0 + hps*p + hcs
% and b = bx*x0 + bd*d

H = blkdiag(R,kron(eye(T-1),blkdiag(Q,R)),Qf);
g = [r; repmat([q;r],T-1,1); qf];
gt = kron(ones(T,1),[zeros(m,n); -2*Q]);

P = blkdiag(Fu,kron(eye(T-1),[Fx Fu]),Fxf);
hc = [repmat(f,T,1);ff];
hx = [-Fx; zeros((T-1)*ell + ellf,n)];
% optional parametric bit
if ellp>0,
    hp = [repmat(-Fp,T,1); -Fpf];
else
    hp=[];
end

C = [kron(eye(T),[-B eye(n)]) + kron([zeros(1,T); eye(T-1) zeros(T-1,1)],[zeros(n,m) -A])];
if ellef>0,
    C = [C; zeros(ellef,m+(T-1)*(m+n)) Ef];
end
% bc = [zeros(T*n,1); ef]; % note this means non-zero ef is ignored
bx = [A; zeros(ellef+(T-1)*n,n)];
% bd done lower down, dependent on Ef etc

Ps = blkdiag(Fus,kron(eye(T-1),[Fxs Fus]));
% check padding
Ps(1,T*(n+m))=0;
hcs = [repmat(fs,T,1)];
hxs = [-Fxs; zeros((T-1)*ells,n)];
% optional parametric bit
if ellp>0,
    hps = repmat(-Fps,T,1);
else
    hps=[];
end

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