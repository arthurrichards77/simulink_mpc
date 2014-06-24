function [z,info] = ipoptSolve(H,g,P,h,C,b,z0,A,B,Fx,Fu,Ff,Q,R,Qf,opts,Ps,hs,Ef,Fxs,Fus)
%sonotcodegen
%
% min z'*H*z + g'*z + sum(max(0,Ps*z-h))
% s.t. P*z <= h
%      C*z == b
%

% sizes
n = size(A,1); % number of states in system
m = size(B,2); % number of inputs to system
nz = length(g); % number of decision variables in z
ne = length(b); % number of equalities in Cz=b
ni = length(h); % number of inequalities Pz<=h
ns = length(hs); % number of soft constraints Ps*z<=hs (if possible)
ell = size(Fx,1); % number of inequalities per time step, Fx*x + Fu*u <= f
ells = size(Fxs,1); % number of soft constraints per time step, Fxs*x + Fus*u <= fs
ellf = size(Ff,1); % number of terminal inequalities
ellef = size(Ef,1); % number of terminal equalities

% important to take T (the horizon) from here
% if you pass it in as a signal, code generator gets upset
% as it thinks its matrices could vary in size
T = (ne-ellef)/size(A,1);

% list of slack variables
if m==3,
    slackList = kron(ones(1,T),[2 3]) + kron((1:T)-1,[6 6]);
elseif m==2,
    slackList = (2:5:(T*5));
end

%% process options

% number of options passed in
nop = length(opts);

% option 1 - assume Phi is diagonal if > 0
if nop>=1,
    flagPhiIsDiag = opts(1)>0; % turns on or off assumptions about diagonal Phi
else
    flagPhiIsDiag = false; % default setting does not assume diagonal
end

% option 2 - set number of Newton iterations
if nop>=2,
    numNewtonIters = opts(2);
else
    numNewtonIters = 10;
end

% option 3 - use KS function for soft constraints if >0
if nop>=3,
    flagUseSoftCons = opts(3)>0;
else
    flagUseSoftCons = false; % default - ignore
end

% option 4 - enable massive amount of checking (slow) if >0
if nop>=4,
    flagChecking = opts(4)>0;
else
    flagChecking = false; % default - ignore
end

% option 5 - disable the Pade approximation if >0
if nop>=5,
    flagNoPade = opts(5)>0;
else
    flagNoPade = false; % default - use Pade
end

% option 6 - norm tolerance for early stopping
if nop>=6,
    termTol = opts(6);
else
    termTol = 0; % effectively use all iters
end

%% settings

% single fixed barrier weight
kappa = 0.002;

% fixed parameter for KS-function
rho=10;

%% precalculations

% preform to avoid later work
kappaPt = kappa*P';
kappaPtSq = kappaPt.*P';
rhoPstSq = rho*Ps'.*Ps';
diagTwoH = diag(2*H);
% helpful to avoid lots of blkdiag calls later
blkQR = blkdiag(Q,R);

% pre-allocate for KS residuals
es = hs;
ds = hs;
dsNew = ds;
esNew = es;

% pre-assignment to keep coder happy
dz = zeros(nz,1);
phi = zeros(nz);
dhats = zeros(ns,1);

%% form initial solution

% form the tail of the previous solution
% plus a step of zero control on the end
if m==1, % hack - catch the slack case
    % no slacks - ok for zeros at end
    zTail = [z0((m+n+1):nz); zeros(m,1); A*z0(nz - n + (1:n))];
else,
    % slacks = can't be exactly zero
    zTail = [z0((m+n+1):nz); [0; 0.0001*zeros(m-1,1) ]; A*z0(nz - n + (1:n))];
end

% check if tail works as an initializer
if all(P*zTail<h),
    
    % tail is feasible
    z = zTail;
    initSolChoice = 1;
    
else
    
    % try fiddling with the slack variables
    z = zTail;
    
    % catch just the slack case
    if m>1,
        z(slackList) = -1.0001*min(P*z - h);
    end
    
    % now check if that worked
    if all(P*z<h),
        
        % worked
        initSolChoice = 4;
        
    elseif all(P*z0<h),
        
        % try last solution unchanged
        z = z0;
        initSolChoice = 2;
        
    elseif all(0<h),
        
        % in this case, start with zeros
        z = zeros(size(z0));
        initSolChoice = 3;
        
    else
        
        % out of ideas - zeros anyway
        z = zeros(size(z0));
        initSolChoice = 0;
        
    end
    
end

%% set up functions
funcs.objective = @(z) objective(z,H,g,h,P,Ps,hs,kappa,rho);
funcs.gradient = @(z) diagTwoH.*z + g + kappaPt*(1./(h - sparse(P)*z)) + sparse(Ps')*calcDs2(z,Ps,hs,rho,flagNoPade);
funcs.constraints = @(z) sparse(C)*z;
options.cu = b;
options.cl = b; % equality constraints Cz=b
funcs.jacobian = @(z) sparse(C);
funcs.jacobianstructure = @() sparse(C);
funcs.hessian = @(z,sigma,lambda) hessian(z,sigma,lambda,H,P,h,Ps,hs,rho,kappa,ns,ni);
funcs.hessianstructure = @() sparse(H) + sparse(P)'*sparse(P) + sparse(Ps)'*sparse(Ps);
options.ipopt.hessian_approximation = 'exact';

%% solve the thing
[z,status] = ipopt(z, funcs, options);

%% respond
info = [status.status;status.iter;0;0];

end

% function for objective
function J = objective(z,H,g,h,P,Ps,hs,kappa,rho)

J = z'*sparse(H)*z + sparse(g)'*z + kappa*sum(-log(h - sparse(P)*z)) + sum(log(1+exp(rho*(sparse(Ps)*z - hs))))/rho

end

% function for hessian
function hess = hessian(z,sigma,~,H,P,h,Ps,hs,rho,kappa,ns,ni)

[~,es]=calcDs(z,Ps,hs,rho,1);
hess_full = sigma*(sparse(2*H) + kappa*sparse(P)'*spdiags(1./(h - sparse(P)*z).^2,0,ni,ni)*sparse(P) + rho*sparse(Ps)'*spdiags(es ./ ((1+es).*(1+es)),0,ns,ns)*sparse(Ps));
hess = tril(hess_full);

end

%% utilities

% some functions to get block terms Q,R and S out of phi-inverse easily
function Qt = Qtil(phiInv,ii,n,m)
Qt = phiInv(m + (m+n)*(ii-1) + (1:n),m + (m+n)*(ii-1) + (1:n));
end

function Rt = Rtil(phiInv,ii,n,m)
Rt = phiInv((m+n)*ii + (1:m),(m+n)*ii + (1:m));
end

function St = Stil(phiInv,ii,n,m)
St = phiInv(m + (m+n)*(ii-1) + (1:n),(m+n)*ii + (1:m));
end

% another function to get n x n square block elements
function Y = getSqBlk(U,ii,jj,n)
Y = U((ii-1)*n + (1:n), (jj-1)*n + (1:n));
end

function Minv = mySymPDinv(M,flagChecking)
%
% utility for quick inversion of a symmetric positive definite matrix
%

cholM = chol(M,'lower');
T = linsolve(cholM,eye(size(M,1)),struct('LT',true));
Minv = linsolve(cholM',T,struct('UT',true));

if flagChecking,
    checkInv = norm(Minv*M - eye(size(M,1)))
end

end

function [ds,es]=calcDs(z,Ps,hs,rho,flagNoPade)

% pre-assign to help coder
es = hs;
ds = hs;

% residuals
rs = Ps*z - hs;

for ii=1:length(hs),
    
    if rs(ii)>0,
        es(ii,1) = myexp(-rho*rs(ii),flagNoPade);
        ds(ii,1) = 1/(1+es(ii,1));
    else
        es(ii,1) = myexp(rho*rs(ii),flagNoPade);
        ds(ii,1) = es(ii,1)/(1+es(ii,1));
    end
end

end

function [ds]=calcDs2(z,Ps,hs,rho,flagNoPade)

% pre-assign to help coder
es = hs;
ds = hs;

% residuals
rs = Ps*z - hs;

for ii=1:length(hs),
    
    if rs(ii)>0,
        es(ii,1) = myexp(-rho*rs(ii),flagNoPade);
        ds(ii,1) = 1/(1+es(ii,1));
    else
        es(ii,1) = myexp(rho*rs(ii),flagNoPade);
        ds(ii,1) = es(ii,1)/(1+es(ii,1));
    end
end

end

function y = myexp(u,flagNoPade)

% use built in exponential
if flagNoPade,
    y = exp(u);
else
    % use pade approximant
    di = ones(size(u));
    ds = di;
    for ii=1:3,
        di = (-1/ii)*di.*u;
        ds = ds+di;
    end
    y = 1./ds;
end

end

function rp = calcRp(z,b,A,B,Ef,T,n,m,ellef)
% calculate primal residual Cz-b

rp = multByC(z,A,B,Ef,T,n,m,ellef) - b;

end

function y = multByC(z,A,B,Ef,T,n,m,ellef)
%
% return C*z
%

y = zeros(T*n+ellef,1);

y(1:n) = z(m+(1:n)) - B*z(1:m);
for ii=2:T,
    y(n*(ii-1)+(1:n)) = z(m+(ii-1)*(n+m)+(1:n)) - A*z(m+(ii-2)*(n+m)+(1:n)) - B*z((ii-1)*(n+m)+(1:m));
end

if ellef>0,
    y(T*n + (1:ellef)) = Ef*z(m+(T-1)*(n+m)+(1:n));
end

end

function y = multByP(z,Fx,Fu,Ff,T,n,m,ell,ellf)
%
% return P*z
%

y = zeros(T*ell+ellf,1);

y(1:ell) = Fu*z(1:m);
for ii=2:T,
    y(ell*(ii-1)+(1:ell)) = Fx*z(m+(ii-2)*(n+m)+(1:n)) + Fu*z((ii-1)*(n+m)+(1:m));
end
if ellf>0,
    y(T*ell + (1:ellf)) = Ff*z(m+(T-1)*(n+m)+(1:n));
end

end