function [z,info] = mpcsolve(H,g,P,h,C,b,z0,A,B,Fx,Fu,Ff,Q,R,Qf,opts,Ps,hs,Ef,Fxs,Fus)
%#codegen

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

%% initialization

% initial lagrange multipliers
nu = zeros(ne,1);

% precalculate d
d = 1./(h - multByP(z,Fx,Fu,Ff,T,n,m,ell,ellf));

% calculate residuals for first iteration
rp = calcRp(z,b,A,B,Ef,T,n,m,ellef); %C*z - b;
rpMag = norm(rp);
rd = diagTwoH.*z + g + kappaPt*d + C'*nu;

% optional soft constraint info
if flagUseSoftCons,
    
    % evaluate soft version of d
    [ds,es]=calcDs(z,Ps,hs,rho,flagNoPade);
    
    % add to residual
    rd = rd + Ps'*ds;
    
end

rdMag = norm(rd);
rMag = norm([rdMag;rpMag]);

%% main solution loop for Newton's method
for kk=1:numNewtonIters,
    
    % check the P multiplier
    if flagChecking
        check_d = norm(d - (1./(h - P*z)))
    end
    
    % check residual calc
    if flagChecking
        checkRp = norm(C*z - b - rp)
    end
    
    % if using soft cons with KS
    if flagUseSoftCons,
        % need the "d-hat" for the second derivatives of the KS functions
        dhats = (es ./ ((1+es).*(1+es)));
    end
    
    % first form inverse of Phi
    if flagPhiIsDiag,
        
        % form the diagonals of Phi
        diagPhi = diagTwoH + kappaPtSq*(d.*d);
        
        % plus soft cons if used
        if flagUseSoftCons,
            diagPhi = diagPhi + rhoPstSq*dhats;
        end
        
        % "invert" it
        phiInv = diag(1./diagPhi);
        
    else
        
        % preallocate to avoid slowdown
        phiInv = zeros(nz);
        
        % build the blocks of Phi inverse
        if flagUseSoftCons,
            phiInv(1:m,1:m) = mySymPDinv(2*R + kappa*Fu'*diag(d(1:ell).*d(1:ell))*Fu + rho*Fus'*diag(dhats(1:ells))*Fus,flagChecking);
        else
            phiInv(1:m,1:m) = mySymPDinv(2*R + kappa*Fu'*diag(d(1:ell).*d(1:ell))*Fu,flagChecking);
        end
        for ii=1:(T-1),
            if flagUseSoftCons,
                blkInv = mySymPDinv(2*blkQR + kappa*[Fx Fu]'*diag(d(ii*ell + (1:ell)).*d(ii*ell + (1:ell)))*[Fx Fu] + ...
                    rho*[Fxs Fus]'*diag(dhats(ii*ells + (1:ells)))*[Fxs Fus],flagChecking);
            else
                blkInv = mySymPDinv(2*blkQR + kappa*[Fx Fu]'*diag(d(ii*ell + (1:ell)).*d(ii*ell + (1:ell)))*[Fx Fu],flagChecking);
            end
            phiInv(m+(ii-1)*(n+m)+(1:(n+m)),m+(ii-1)*(n+m)+(1:(n+m))) = blkInv; % [Q-tilde S-tilde; S-tilde' R-tilde]
        end
        phiInv(nz-n+(1:n),nz-n+(1:n)) = mySymPDinv(2*Qf + kappa*Ff'*diag(d(T*ell + (1:ellf)).*d(T*ell + (1:ellf)))*Ff,flagChecking);
        
    end
    
    % check phi inverted correctly
    if flagChecking,
        phi = 2*H + kappa*P'*diag(d)*diag(d)*P;
        if flagUseSoftCons,
            phi = phi+rho*Ps'*diag(es ./ ((1+es).*(1+es)))*Ps;
        end
        %checkPhiInv = norm(phi*phiInv - eye(nz))
        checkPhiInv = (phi*phiInv - eye(nz))
    end
    
    % preallocate Y
    Y = zeros(ne);
    
    % form the block elements of Y = C*phiInv*C'
    Y(1:n,1:n) = B*Rtil(phiInv,0,n,m)*B' + Qtil(phiInv,1,n,m);
    for ii=1:T,
        if ii<T,
            Y((ii-1)*n+(1:n),ii*n+(1:n)) = -Qtil(phiInv,ii,n,m)*A' - Stil(phiInv,ii,n,m)*B'; %Yabove(:,:,ii)
            Y(ii*n+(1:n),(ii-1)*n+(1:n)) = Y((ii-1)*n+(1:n),ii*n+(1:n))';
        end
        if ii>1,
            tmp = A*Stil(phiInv,ii-1,n,m)*B';
            Y((ii-1)*n+(1:n),(ii-1)*n+(1:n)) = A*Qtil(phiInv,ii-1,n,m)*A' + tmp + tmp' + B*Rtil(phiInv,ii-1,n,m)*B' + Qtil(phiInv,ii,n,m);
        end
    end
    
    % add terms for terminal equality cons
    if ellef>0,
        Y((T-1)*n+(1:n),T*n+(1:ellef)) = Qtil(phiInv,T,n,m)*Ef';
        Y(T*n+(1:ellef),(T-1)*n+(1:n)) = Y((T-1)*n+(1:n),T*n+(1:ellef))';
        Y(T*n+(1:ellef),T*n+(1:ellef)) = Ef*Y((T-1)*n+(1:n),T*n+(1:ellef));
    end
    
    % now check that Y was constructed correctly
    if flagChecking
        checkY = norm(Y - C*phiInv*C')
    end
    
    % now form PhiInv * rd in preparation for making the RHS (-beta)
    PhiInvRd = zeros(nz,1);
    PhiInvRd(1:m,:) = Rtil(phiInv,0,n,m)*rd(1:m);
    for ii=1:(T-1),
        PhiInvRd(m + (ii-1)*(m+n) + (1:(m+n)),:) = [Qtil(phiInv,ii,n,m) Stil(phiInv,ii,n,m); Stil(phiInv,ii,n,m)' Rtil(phiInv,ii,n,m)]*rd(m + (ii-1)*(m+n) + (1:(m+n)),:);
    end
    PhiInvRd(m + (T-1)*(m+n) +(1:n),:) = Qtil(phiInv,T,n,m)*rd(m + (T-1)*(m+n) +(1:n));
    
    % and the RHS, -beta = rp - C*phiInv*rd
    rhs = rp - multByC(PhiInvRd,A,B,Ef,T,n,m,ellef);
    
    % check it
    if flagChecking
        checkBeta = norm(rhs - (rp - C*phiInv*rd))
    end
    
    % now find the blocks of the lower triangular Cholesky factorization of Y
    L = zeros(ne);
    L(1:n,1:n) = chol(getSqBlk(Y,1,1,n),'lower');
    for ii=2:T,
        L((ii-1)*n+(1:n),(ii-2)*n+(1:n)) = linsolve(getSqBlk(L,ii-1,ii-1,n),getSqBlk(Y,ii-1,ii,n),struct('LT',true))';
        L((ii-1)*n+(1:n),(ii-1)*n+(1:n)) = chol(getSqBlk(Y,ii,ii,n) - getSqBlk(L,ii,ii-1,n)*getSqBlk(L,ii,ii-1,n)','lower');
    end
    
    % and the extra bits for terminal equality cons
    if ellef>0,
        L(T*n+(1:ellef),(T-1)*n+(1:n)) = linsolve(getSqBlk(L,T,T,n),Y((T-1)*n+(1:n),T*n+(1:ellef)),struct('LT',true))';
        L(T*n+(1:ellef),T*n+(1:ellef)) = chol(Y(T*n+(1:ellef),T*n+(1:ellef)) - L(T*n+(1:ellef),(T-1)*n+(1:n))*L(T*n+(1:ellef),(T-1)*n+(1:n))','lower');
    end
    
    % now check the thing
    if flagChecking,
        checkL = norm(L*L'-Y)
    end
    
    % solve (L*L')*dnu=rhs: part one: solve for t=L'*dnu
    t = zeros(ne,1);
    t(1:n) = linsolve(getSqBlk(L,1,1,n),rhs(1:n),struct('LT',true));
    for ii=1:(T-1),
        t(ii*n + (1:n)) = linsolve(getSqBlk(L,ii+1,ii+1,n),rhs(ii*n + (1:n)) - getSqBlk(L,ii+1,ii,n)*t((ii-1)*n + (1:n)),struct('LT',true));
    end
    % final elements for terminal equalities
    if ellef>0,
        t(T*n + (1:ellef)) = linsolve(L(T*n+(1:ellef),T*n+(1:ellef)),rhs(T*n + (1:ellef)) - L(T*n+(1:ellef),(T-1)*n+(1:n))*t((T-1)*n + (1:n)),struct('LT',true));
    end
    
    % check solve process
    if flagChecking
        check_t = norm(L*t - rhs)
    end
    
    % now solve part two: L'*dnu = t;
    dnu = zeros(ne,1);
    % different start for terminal equality case
    if ellef>0,
        dnu(T*n + (1:ellef)) = linsolve(L(T*n+(1:ellef),T*n+(1:ellef))',t(T*n + (1:ellef)),struct('UT',true));
        dnu((T-1)*n + (1:n)) = linsolve(getSqBlk(L,T,T,n)',t((T-1)*n + (1:n)) - L(T*n+(1:ellef),(T-1)*n+(1:n))'*dnu(T*n + (1:ellef)),struct('UT',true));
    else
        dnu((T-1)*n + (1:n)) = linsolve(getSqBlk(L,T,T,n)',t((T-1)*n + (1:n)),struct('UT',true));
    end
    for ii=(T-1):-1:1,
        dnu((ii-1)*n + (1:n)) = linsolve(getSqBlk(L,ii,ii,n)',t((ii-1)*n + (1:n)) - getSqBlk(L,ii+1,ii,n)'*dnu((ii)*n + (1:n)),struct('UT',true));
    end
    
    % check the whole solve worked
    if flagChecking
        check_dnu = norm(Y*dnu - rhs)
    end
    
    % now solve for dz
    if flagPhiIsDiag,
        
        % solve for dz assuming PhiInv diagonal
        dz = diag(phiInv).*(-rd-C'*dnu);
        
    else
        
        % form the vector to be multiplied, for shorthand
        v = (-rd-C'*dnu);
        
        % now form PhiInv * rd in preparation for making the RHS (-beta)
        dz(1:m,:) = Rtil(phiInv,1,n,m)*v(1:m);
        for ii=1:(T-1),
            dz(m + (ii-1)*(m+n) + (1:(m+n)),:) = [Qtil(phiInv,ii,n,m) Stil(phiInv,ii,n,m); Stil(phiInv,ii,n,m)' Rtil(phiInv,ii,n,m)]*v(m + (ii-1)*(m+n) + (1:(m+n)),:);
        end
        dz(m + (T-1)*(m+n) +(1:n),:) = Qtil(phiInv,T,n,m)*v(m + (T-1)*(m+n) +(1:n));
        
    end
    
    % check computation of Newton step
    if flagChecking
        checkNewton = norm([phi C';C zeros(ne)]*[dz;dnu] + [rd; rp])
    end
    
    % line search
    sMax = 1.0;
    
    % part 1 - reduce until feasible
    for jj=1:10,
        
        zFar = z + sMax*dz;
        iFar = h - multByP(zFar,Fx,Fu,Ff,T,n,m,ell,ellf);
        
        if all(iFar>0),
            break
        end
        
        sMax = sMax*0.5;
        
    end
    
    % part 2 take a tiny step just to get the slope
    s = sMax/100;
    zNew = z + s*dz;
    nuNew = nu + s*dnu;
    iNew = h - multByP(zNew,Fx,Fu,Ff,T,n,m,ell,ellf);
    % new residuals
    dNew = 1./iNew;
    rdNew = diagTwoH.*zNew + g + kappaPt*dNew + C'*nuNew;
    if flagUseSoftCons,
        [dsNew,esNew] = calcDs(zNew,Ps,hs,rho,flagNoPade);
        rdNew = rdNew + Ps'*dsNew;
    end
    rpNew = calcRp(zNew,b,A,B,Ef,T,n,m,ellef);
    rdMagNew = norm(rdNew);
    rpMagNew = norm(rpNew);
    rMagNew = norm([rdMagNew;rpMagNew]);
    gradRmag = 100*(rMagNew-rMag);
    
    % part 3 - backtracking
    s = sMax;
    for jj=1:10,
        
        zNew = z + s*dz;
        nuNew = nu + s*dnu;
        iNew = h - multByP(zNew,Fx,Fu,Ff,T,n,m,ell,ellf);
        
        % new residuals
        dNew = 1./iNew;
        rdNew = diagTwoH.*zNew + g + kappaPt*dNew + C'*nuNew;
        if flagUseSoftCons,
            [dsNew,esNew] = calcDs(zNew,Ps,hs,rho,flagNoPade);
            rdNew = rdNew + Ps'*dsNew;
        end
        rpNew = calcRp(zNew,b,A,B,Ef,T,n,m,ellef);
        rdMagNew = norm(rdNew);
        rpMagNew = norm(rpNew);
        rMagNew = norm([rdMagNew;rpMagNew]);
        
        % test
        if rMagNew < rMag + 0.5*s*gradRmag,
            
            % update
            z = zNew;
            nu = nuNew;
            d = dNew;
            rd = rdNew;
            rp = rpNew;
            rpMag = rpMagNew;
            rdMag = rdMagNew;
            rMag = rMagNew;
            
            if flagUseSoftCons,
                
                ds = dsNew;
                es = esNew;
                
            end
            
            % do nothing
            % lineSearchPass=[kk jj s norm(rdNew) norm(rpNew)]
            break
            
        else
            
            %covg = false
            s = s*0.7;
            
        end
        
    end
    
end

% information for output
info = [rpMag; % primal residual, i.e. norm(C*z-b)
    rdMag; % dual residual, i.e. grad z
    initSolChoice]; % which initial solution did I use?

end

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