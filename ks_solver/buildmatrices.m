function [H,g,gt,P,hx,hc,C,bx,bd,Ps,hxs,hcs,Ef_block,Ed_block,ef_block] = buildmatrices(A,B,Q,R,q,r,Qf,qf,T,Fx,Fu,f,Fxs,Fus,fs,Fxf,ff,Ef,ef,Ed,Fp,Fps,Fpf)
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
n = size(A,1);
m = size(B,2);
ell = size(Fx,1);
ellf = size(Fxf,1);
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

%% compile MPC problem

% min z'*H*z + (gt*xt+g)'*z + sum(max(0,Ps*z-hs))
% s.t. P*z <= h
%      C*z == b
%
% where h = hx*x0 + hc
% where hs = hxs*x0 + hcs
% and b = bx*x0 + bd*d

H = blkdiag(R,kron(eye(T-1),blkdiag(Q,R)),Qf);
P = blkdiag(Fu,kron(eye(T-1),[Fx Fu]),Fxf);
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