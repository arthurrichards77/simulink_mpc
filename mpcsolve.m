function [z,info] = mpcsolve(H,g,P,h,C,b,z0,A,B,Fx,Fu,Ff,Q,R,Qf,opts,Ps,hs,Ef,Fxs,Fus) %check_d, checkRp, checkPhiInv, checkY, checkBeta, checkL, check_t, check_dnu, checkNewton, checkInv
%#codegen

% Switches - Structural exploitations
% 1 - xC
% 2 - xP
% 3 - xPs
% 4 - xPs'
% 5 - xC'
% 6 - Ax
% 7 - xA'
% 8 - Bx
% 9 - xB'

% ,check_d, checkRp, checkPhiInv, checkY, checkBeta, checkL, check_t, check_dnu, checkNewton, checkInv

check_d = 0;
checkRp = 0;
checkPhiInv = 0;
checkY = 0;
checkBeta = 0;
checkL = 0;
check_t = 0;
check_dnu = 0;
checkNewton = 0;
checkInv = 0;

totBackTracks = 0;

% sizes
n = size(A,1); % number of states in system
m = size(B,2); % number of inputs to system
nz = length(g); % number of decision variables in z
ne = length(b); % number of equalities in Cz=b
ni = length(h); % number of inequalities Pz<=h
ns = length(hs); % number of soft constraints Ps*z<=hs (if possible)
ell = size(Fx,1); % number of inequalities per time step, Fx*x + Fu*u <= f
% ells = size(Fxs,1); % number of soft constraints per time step, Fxs*x + Fus*u <= fs
ellf = size(Ff,1); % number of terminal inequalities

% check for terminal equality cons
if size(Ef,2) == n,
    ellef = size(Ef,1); % number of terminal equalities
else
    ellef = 0;
end

% important to take T (the horizon) from here
% if you pass it in as a signal, code generator gets upset
% as it thinks its matrices could vary in size
T = (ne-ellef)/size(A,1);

ells = size(Fxs,1); % number of soft constraints per time step, Fxs*x + Fus*u <= fs

% list of slack variables
if m==3,
    slackList = kron(ones(1,T),[2 3]) + kron((1:T)-1,[6 6]);
elseif m==2,
    slackList = (2:5:(T*5));
end

%% barrier settings

% single fixed barrier weight
kappa = 0.005;

% fixed parameter for KS-function
rho=10;

% default - no outer iterations
numBarrIters = 1;

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

% option 6 - disable the use of sparse matrix structure if >0
if nop>=6,
    switches = [1 1 1 1 1 0 0 0 0]*(1-(opts(6)>0));
else
    switches = [1 1 1 1 1 0 0 0 0]; % default - use standard structure
end

% option 7 - optional setting of barrier weight kappa from outside
if nop>=7,
    if opts(7)>0,
        kappa = opts(7);
    end
end

% option 8 - number of outer barrier weight iterations
if nop>=8,
    if opts(8)>1,
        numBarrIters = opts(8);
    end
end

% option 9 - norm tolerance for early stopping
if nop>=9,
    termTol = opts(9);
else
    termTol = 0.0; % effectively use all iters
end
%% precalculations

% preform to avoid later work
kappaPt = kappa*P';
kappaPtSq = kappaPt.*P';
rhoPstSq = rho*Ps'.*Ps';
diagTwoH = diag(2*H);
% helpful to avoid lots of blkdiag calls later
% blkQR = blkdiag(Q,R); % can't call blkQR in embedded matlab 2011b
blkQR = zeros(size(Q) + size(R));
blkQR(1:length(Q),1:length(Q)) = Q;
blkQR(length(Q)+(1:length(R)),length(Q)+(1:length(R))) = R;
FxsT = Fxs';
FusT = Fus';
AT = A';
BT = B';
CT = C';
EfT = Ef';
PsT = Ps';

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
    zTail = [z0((m+n+1):nz); zeros(m,1); preMultByA(z0(nz - n + (1:n)),A,switches)]; %A*z0(nz - n + (1:n))];
else,
    % slacks = can't be exactly zero
    zTail = [z0((m+n+1):nz); [0; 0.0001*ones(m-1,1) ]; preMultByA(z0(nz - n + (1:n)),A,switches)]; %A*z0(nz - n + (1:n))];
    %     max(abs(preMultByA(z0(nz - n + (1:n)),A) - A*z0(nz - n + (1:n))))
end

% check if tail works as an initializer
if all(P*zTail<h),
    
    % tail is feasible
    z = zTail;
    initSolChoice = 1;
    
else
    
    % show the problem
    %P*zTail-h
    
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
        
        % out of ideas - zeros anyway, plus a bit for slacks
        z = zeros(size(z0))+0.0001;
        initSolChoice = 0;
        
    end
    
end

% if checking enabled, display solution choice
if flagChecking,
    initSolChoice = initSolChoice
end

%% initialization

% initial lagrange multipliers
nu = zeros(ne,1);

% precalculate d
d = 1./(h - multByP(z,P,Fx,Fu,Ff,T,n,m,ell,ellf,switches));

% calculate residuals for first iteration
rp = calcRp(z,b,A,B,C,Ef,T,n,m,ellef,switches); %C*z - b;
rpMag = norm(rp);
rd = diagTwoH.*z + g + kappaPt*d + multByCT(nu,CT,AT,BT,EfT,T,n,m,ellef,switches); %C'*nu;

% checkCT = max(abs(multByCT(nu,AT,BT,EfT,T,n,m,ellef) - C'*nu))

% optional soft constraint info
if flagUseSoftCons,
    
    % evaluate soft version of d
    [ds,es]=calcDs(z,Ps,Fxs,Fus,T,n,m,ells,hs,rho,flagNoPade,switches);
    
    % add to residual
    rd = rd + multByPsT(ds,PsT,FxsT,FusT,T,n,m,ells,switches); %Ps'*ds;
    
    if 0
        checkPsT = abs(max(multByPsT(ds,PsT,FxsT,FusT,T,n,m,ells,switches) - Ps'*ds))
    else
        checkPsT = 0;
    end
    
end

rdMag = norm(rd);
rMag = norm([rdMag;rpMag]);

%% outer loop with varying barrier weights
iterCount = 0;
for ww=1:numBarrIters,
    
    %% main solution loop for Newton's method
    for kk=1:numNewtonIters,
        
        % check the P multiplier
        if flagChecking
            check_d = norm(d - (1./(h - P*z)))
        else
            check_d = 0;
        end
        
        % check residual calc
        if flagChecking
            checkRp = norm(C*z - b - rp)
        else
            checkRp = 0;
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
            checkPhiInv = max(max((phi*phiInv - eye(nz))))
        else
            checkPhiInv = 0;
        end
        
        % preallocate Y
        Y = zeros(ne);
        
        % form the block elements of Y = C*phiInv*C'
        Y(1:n,1:n) = B*Rtil(phiInv,0,n,m)*B' + Qtil(phiInv,1,n,m);
        for ii=1:T,
            if ii<T,
                %             Y((ii-1)*n+(1:n),ii*n+(1:n)) = -Qtil(phiInv,ii,n,m)*A' - Stil(phiInv,ii,n,m)*B'; %Yabove(:,:,ii)
                Y((ii-1)*n+(1:n),ii*n+(1:n)) = -multByAT(Qtil(phiInv,ii,n,m),AT,switches) - Stil(phiInv,ii,n,m)*B'; %Yabove(:,:,ii)
                Y(ii*n+(1:n),(ii-1)*n+(1:n)) = Y((ii-1)*n+(1:n),ii*n+(1:n))';
            end
            if ii>1,
                %             tmp = A*Stil(phiInv,ii-1,n,m)*B';
                tmp = preMultByA(Stil(phiInv,ii-1,n,m),A,switches)*B';
                %             Y((ii-1)*n+(1:n),(ii-1)*n+(1:n)) = A*Qtil(phiInv,ii-1,n,m)*A' + tmp + tmp' + B*Rtil(phiInv,ii-1,n,m)*B' + Qtil(phiInv,ii,n,m);
                %             Y((ii-1)*n+(1:n),(ii-1)*n+(1:n)) = preMultByA(Qtil(phiInv,ii-1,n,m),A)*A' + tmp + tmp' + B*Rtil(phiInv,ii-1,n,m)*B' + Qtil(phiInv,ii,n,m);
                Y((ii-1)*n+(1:n),(ii-1)*n+(1:n)) = multByAT(preMultByA(Qtil(phiInv,ii-1,n,m),A,switches),AT,switches) + tmp + tmp' + B*Rtil(phiInv,ii-1,n,m)*B' + Qtil(phiInv,ii,n,m);
            end
        end
        
        %     % -------- DO ALL THE Y STUFF AGAIN -------- %
        %
        %     % preallocate Y
        %     Y2 = zeros(ne);
        %
        %     % form the block elements of Y = C*phiInv*C'
        %     Y2(1:n,1:n) = B*Rtil(phiInv,0,n,m)*B' + Qtil(phiInv,1,n,m);
        %     for ii=1:T,
        %         if ii<T,
        %             Y2((ii-1)*n+(1:n),ii*n+(1:n)) = -Qtil(phiInv,ii,n,m)*A' - Stil(phiInv,ii,n,m)*B'; %Yabove(:,:,ii)
        %             Y2(ii*n+(1:n),(ii-1)*n+(1:n)) = Y2((ii-1)*n+(1:n),ii*n+(1:n))';
        %         end
        %         if ii>1,
        %             tmp = A*Stil(phiInv,ii-1,n,m)*B';
        %             Y2((ii-1)*n+(1:n),(ii-1)*n+(1:n)) = A*Qtil(phiInv,ii-1,n,m)*A' + tmp + tmp' + B*Rtil(phiInv,ii-1,n,m)*B' + Qtil(phiInv,ii,n,m);
        %         end
        %     end
        %
        %     % -------- DO ALL THE Y STUFF AGAIN -------- %
        
        % add terms for terminal equality cons
        if ellef>0,
            Y((T-1)*n+(1:n),T*n+(1:ellef)) = Qtil(phiInv,T,n,m)*Ef';
            Y(T*n+(1:ellef),(T-1)*n+(1:n)) = Y((T-1)*n+(1:n),T*n+(1:ellef))';
            Y(T*n+(1:ellef),T*n+(1:ellef)) = Ef*Y((T-1)*n+(1:n),T*n+(1:ellef));
        end
        
        % now check that Y was constructed correctly
        if flagChecking
            checkY = norm(Y - C*phiInv*C')
        else
            checkY = 0;
        end
        
        % now form PhiInv * rd in preparation for making the RHS (-beta)
        PhiInvRd = zeros(nz,1);
        PhiInvRd(1:m,:) = Rtil(phiInv,0,n,m)*rd(1:m);
        for ii=1:(T-1),
            PhiInvRd(m + (ii-1)*(m+n) + (1:(m+n)),:) = [Qtil(phiInv,ii,n,m) Stil(phiInv,ii,n,m); Stil(phiInv,ii,n,m)' Rtil(phiInv,ii,n,m)]*rd(m + (ii-1)*(m+n) + (1:(m+n)),:);
        end
        PhiInvRd(m + (T-1)*(m+n) +(1:n),:) = Qtil(phiInv,T,n,m)*rd(m + (T-1)*(m+n) +(1:n));
        
        % and the RHS, -beta = rp - C*phiInv*rd
        rhs = rp - multByC(PhiInvRd,A,B,C,Ef,T,n,m,ellef,switches);
        
        % check it
        if flagChecking
            checkBeta = norm(rhs - (rp - C*phiInv*rd))
        else
            checkBeta = 0;
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
        else
            checkL = 0;
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
        else
            check_t = 0;
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
        else
            check_dnu = 0;
        end
        
        %     % ------------------ DOUBLE THE LINSOLVE -------------------- %
        %
        %
        %     % now find the blocks of the lower triangular Cholesky factorization of Y
        %     L2 = zeros(ne);
        %     L2(1:n,1:n) = chol(getSqBlk(Y,1,1,n),'lower');
        %     for ii=2:T,
        %         L2((ii-1)*n+(1:n),(ii-2)*n+(1:n)) = linsolve(getSqBlk(L2,ii-1,ii-1,n),getSqBlk(Y,ii-1,ii,n),struct('LT',true))';
        %         L2((ii-1)*n+(1:n),(ii-1)*n+(1:n)) = chol(getSqBlk(Y,ii,ii,n) - getSqBlk(L2,ii,ii-1,n)*getSqBlk(L2,ii,ii-1,n)','lower');
        %     end
        %
        %     % and the extra bits for terminal equality cons
        %     if ellef>0,
        %         L2(T*n+(1:ellef),(T-1)*n+(1:n)) = linsolve(getSqBlk(L2,T,T,n),Y((T-1)*n+(1:n),T*n+(1:ellef)),struct('LT',true))';
        %         L2(T*n+(1:ellef),T*n+(1:ellef)) = chol(Y(T*n+(1:ellef),T*n+(1:ellef)) - L2(T*n+(1:ellef),(T-1)*n+(1:n))*L2(T*n+(1:ellef),(T-1)*n+(1:n))','lower');
        %     end
        %
        %     % solve (L*L')*dnu=rhs: part one: solve for t=L'*dnu
        %     t2 = zeros(ne,1);
        %     t2(1:n) = linsolve(getSqBlk(L2,1,1,n),rhs(1:n),struct('LT',true));
        %     for ii=1:(T-1),
        %         t2(ii*n + (1:n)) = linsolve(getSqBlk(L2,ii+1,ii+1,n),rhs(ii*n + (1:n)) - getSqBlk(L2,ii+1,ii,n)*t2((ii-1)*n + (1:n)),struct('LT',true));
        %     end
        %     % final elements for terminal equalities
        %     if ellef>0,
        %         t2(T*n + (1:ellef)) = linsolve(L2(T*n+(1:ellef),T*n+(1:ellef)),rhs(T*n + (1:ellef)) - L2(T*n+(1:ellef),(T-1)*n+(1:n))*t2((T-1)*n + (1:n)),struct('LT',true));
        %     end
        %
        %     % now solve part two: L'*dnu = t;
        %     dnu2 = zeros(ne,1);
        %     % different start for terminal equality case
        %     if ellef>0,
        %         dnu2(T*n + (1:ellef)) = linsolve(L2(T*n+(1:ellef),T*n+(1:ellef))',t2(T*n + (1:ellef)),struct('UT',true));
        %         dnu2((T-1)*n + (1:n)) = linsolve(getSqBlk(L2,T,T,n)',t2((T-1)*n + (1:n)) - L2(T*n+(1:ellef),(T-1)*n+(1:n))'*dnu2(T*n + (1:ellef)),struct('UT',true));
        %     else
        %         dnu2((T-1)*n + (1:n)) = linsolve(getSqBlk(L2,T,T,n)',t2((T-1)*n + (1:n)),struct('UT',true));
        %     end
        %     for ii=(T-1):-1:1,
        %         dnu2((ii-1)*n + (1:n)) = linsolve(getSqBlk(L2,ii,ii,n)',t2((ii-1)*n + (1:n)) - getSqBlk(L2,ii+1,ii,n)'*dnu2((ii)*n + (1:n)),struct('UT',true));
        %     end
        %
        %     % ------------------ END OF DOUBLE THE LINSOLVE ---------------%
        
        % going to need -(rd + C'*dnu) in next bit
        v = (-rd-multByCT(dnu,CT,AT,BT,EfT,T,n,m,ellef,switches));
        
        % check computation of Newton step
        if flagChecking
            %ellef
            %problem = [v+rd  (-C'*dnu)]
            checkV = norm(v - (-rd-C'*dnu))
        else
            checkV = 0;
        end
        
        % now solve for dz
        if flagPhiIsDiag,
            
            % solve for dz assuming PhiInv diagonal
            dz = diag(phiInv).*(-rd-multByCT(dnu,CT,AT,BT,EfT,T,n,m,ellef,switches)); %C'*dnu);
            
        else
            
            % form the vector to be multiplied, for shorthand
            v = (-rd-multByCT(dnu,CT,AT,BT,EfT,T,n,m,ellef,switches)); %C'*dnu);
            
            % now form PhiInv * rd in preparation for making the RHS (-beta)
            dz(1:m,:) = Rtil(phiInv,0,n,m)*v(1:m);
            for ii=1:(T-1),
                dz(m + (ii-1)*(m+n) + (1:(m+n)),:) = [Qtil(phiInv,ii,n,m) Stil(phiInv,ii,n,m); Stil(phiInv,ii,n,m)' Rtil(phiInv,ii,n,m)]*v(m + (ii-1)*(m+n) + (1:(m+n)),:);
            end
            dz(m + (T-1)*(m+n) +(1:n),:) = Qtil(phiInv,T,n,m)*v(m + (T-1)*(m+n) +(1:n));
            
        end
        
        % check computation of Newton step
        if flagChecking
            %problem = [phi C';C zeros(ne)]*[dz;dnu] + [rd; rp]
            checkNewton = norm([phi C';C zeros(ne)]*[dz;dnu] + [rd; rp])
        else
            checkNewton = 0;
        end
        
        % line search
        sMax = 1.0;
        
        % part 1 - reduce until feasible
        for jj=1:10,
            
            zFar = z + sMax*dz;
            iFar = h - multByP(zFar,P,Fx,Fu,Ff,T,n,m,ell,ellf,switches);
            
            if all(iFar>0),
                break
            end
            
            sMax = sMax*0.5;
            
        end
        
        % part 2 take a tiny step just to get the slope
        s = sMax/100;
        zNew = z + s*dz;
        nuNew = nu + s*dnu;
        iNew = h - multByP(zNew,P,Fx,Fu,Ff,T,n,m,ell,ellf,switches);
        % new residuals
        dNew = 1./iNew;
        rdNew = diagTwoH.*zNew + g + kappaPt*dNew + multByCT(nuNew,CT,AT,BT,EfT,T,n,m,ellef,switches); %C'*nuNew;
        if flagUseSoftCons,
            [dsNew,esNew] = calcDs(zNew,Ps,Fxs,Fus,T,n,m,ells,hs,rho,flagNoPade,switches);
            rdNew = rdNew + multByPsT(dsNew,PsT,FxsT,FusT,T,n,m,ells,switches); %Ps'*dsNew;
            
            %         checkPsT = max(abs(multByPsT(dsNew,FxsT,FusT,T,n,m,ells) - Ps'*dsNew))
        end
        rpNew = calcRp(zNew,b,A,B,C,Ef,T,n,m,ellef,switches);
        rdMagNew = norm(rdNew);
        rpMagNew = norm(rpNew);
        rMagNew = norm([rdMagNew;rpMagNew]);
        gradRmag = 100*(rMagNew-rMag);
        
        %     % Fix for doubling backtracking operation
        %     z2 = z;
        %     nu2 = nu;
        %     rMag2 = rMag;
        %     dsNew2 = dsNew;
        %     esNew2 = esNew;
        %     rdNew2 = rdNew;
        %     rpNew2 = rpNew;
        %     rpMagNew2 = rpMagNew;
        %     rdMagNew2 = rdMagNew;
        %     rMagNew2 = rMagNew;
        
        % part 3 - backtracking
        s = sMax;
        for jj=1:10,
            
            zNew = z + s*dz;
            nuNew = nu + s*dnu;
            iNew = h - multByP(zNew,P,Fx,Fu,Ff,T,n,m,ell,ellf,switches);
            
            % new residuals
            dNew = 1./iNew;
            rdNew = diagTwoH.*zNew + g + kappaPt*dNew + multByCT(nuNew,CT,AT,BT,EfT,T,n,m,ellef,switches); %C'*nuNew;
            if flagUseSoftCons,
                [dsNew,esNew] = calcDs(zNew,Ps,Fxs,Fus,T,n,m,ells,hs,rho,flagNoPade,switches);
                rdNew = rdNew + multByPsT(dsNew,PsT,FxsT,FusT,T,n,m,ells,switches); %Ps'*dsNew;
            end
            rpNew = calcRp(zNew,b,A,B,C,Ef,T,n,m,ellef,switches);
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
        
        %     % DO PART 3 AGAIN
        %     % part 3 - backtracking
        %     s = sMax;
        %     for jj=1:10,
        %         zNew2 = z2 + s*dz;
        %         nuNew2 = nu2 + s*dnu;
        %         iNew2 = h - multByP(zNew2,Fx,Fu,Ff,T,n,m,ell,ellf);
        %
        %         % new residuals
        %         dNew2 = 1./iNew2;
        %         rdNew2 = diagTwoH.*zNew2 + g + kappaPt*dNew2 + C'*nuNew2;
        %         if flagUseSoftCons,
        %             [dsNew2,esNew2] = calcDs(zNew2,Ps,hs,rho,flagNoPade);
        %             rdNew2 = rdNew2 + Ps'*dsNew2;
        %         end
        %         rpNew2 = calcRp(zNew2,b,A,B,Ef,T,n,m,ellef);
        %         rdMagNew2 = norm(rdNew2);
        %         rpMagNew2 = norm(rpNew2);
        %         rMagNew2 = norm([rdMagNew2;rpMagNew2]);
        %
        %         % test
        %         if rMagNew2 < rMag2 + 0.5*s*gradRmag,
        %
        %             % update
        %             z2 = zNew2;
        %             nu2 = nuNew2;
        %             d2 = dNew2;
        %             rd2 = rdNew2;
        %             rp2 = rpNew2;
        %             rpMag2 = rpMagNew2;
        %             rdMag2 = rdMagNew2;
        %             rMag2 = rMagNew2;
        %
        %             if flagUseSoftCons,
        %
        %                 ds2 = dsNew2;
        %                 es2 = esNew2;
        %
        %             end
        %
        %             % do nothing
        %             % lineSearchPass=[kk jj s norm(rdNew) norm(rpNew)]
        %             break
        %
        %         else
        %
        %             %covg = false
        %             s = s*0.7;
        %
        %         end
        %     end
        %     % END OF DO PART 3 AGAIN
        
        totBackTracks = totBackTracks + jj;
        
        % optional early termination
        if rMag < termTol,
            break
        end
        
    end
    
    iterCount = iterCount + kk;
            
    kappa = kappa*0.2;
    rho = rho*5;
    
end

% information for output
info = [rpMag; % primal residual, i.e. norm(C*z-b)
    rdMag; % dual residual, i.e. grad z
    initSolChoice; % which initial solution did I use?
    iterCount]; % iteration count

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
tmp = linsolve(cholM,eye(size(M,1)),struct('LT',true));
Minv = linsolve(cholM',tmp,struct('UT',true));

% if flagChecking,
%     checkInv = norm(Minv*M - eye(size(M,1)))
% else
%     checkInv = 0;
% end

end

function [ds,es]=calcDs(z,Ps,Fxs,Fus,T,n,m,ells,hs,rho,flagNoPade,switches)

% pre-assign to help coder
es = hs;
ds = hs;

% residuals
% rs = Ps*z - hs;
rs = multByPs(z,Ps,Fxs,Fus,T,n,m,ells,switches) - hs;

if 0,
    checkPs = max(abs(rs - Ps*z + hs))
else
    checkPs = 0;
end



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

function rp = calcRp(z,b,A,B,C,Ef,T,n,m,ellef,switches)
% calculate primal residual Cz-b

rp = multByC(z,A,B,C,Ef,T,n,m,ellef,switches) - b;
end

function y = multByC(z,A,B,C,Ef,T,n,m,ellef,switches)
%
% return C*z
%

if switches(1) == 0
    y = C*z;
else
    y = zeros(T*n+ellef,1);
    
    y(1:n) = z(m+(1:n)) - B*z(1:m);
    for ii=2:T,
        %     y(n*(ii-1)+(1:n)) = z(m+(ii-1)*(n+m)+(1:n)) - A*z(m+(ii-2)*(n+m)+(1:n)) - B*z((ii-1)*(n+m)+(1:m));
        y(n*(ii-1)+(1:n)) = z(m+(ii-1)*(n+m)+(1:n)) - preMultByA(z(m+(ii-2)*(n+m)+(1:n)),A,switches) - B*z((ii-1)*(n+m)+(1:m));
    end
    
    if ellef>0,
        y(T*n + (1:ellef)) = Ef*z(m+(T-1)*(n+m)+(1:n));
    end
end
end

function y = multByP(z,P,Fx,Fu,Ff,T,n,m,ell,ellf,switches)
%
% return P*z
%

if switches(2) == 0
    y = P*z;
else
    y = zeros(T*ell+ellf,1);
    
    y(1:ell) = Fu*z(1:m);
    for ii=2:T,
        y(ell*(ii-1)+(1:ell)) = Fx*z(m+(ii-2)*(n+m)+(1:n)) + Fu*z((ii-1)*(n+m)+(1:m));
    end
    if ellf>0,
        y(T*ell + (1:ellf)) = Ff*z(m+(T-1)*(n+m)+(1:n));
    end
end
end

function y = multByPs(z,Ps,Fxs,Fus,T,n,m,ells,switches)
%
% return Ps*z
%

if switches(3) == 0
    y = Ps*z;
else
    y = zeros(T*ells,1);
    
    y(1:ells) = Fus*z(1:m);
    for ii=2:T,
        y(ells*(ii-1)+(1:ells)) = Fxs*z(m+(ii-2)*(n+m)+(1:n)) + Fus*z((ii-1)*(n+m)+(1:m));
    end
end
end

function y = multByPsT(ds,PsT,FxsT,FusT,T,n,m,ells,switches)
%
% return Ps'*ds
%
% Where FxsT = Fxs'
%       FusT = Fus'

if switches(4) == 0
    y = PsT*ds;
else
    y = zeros(T*(n+m),1);
    
    y(1:m) = FusT*ds(1:ells);
    for ii=2:T
        y(m+(1:n)+(ii-2)*(n+m)) = FxsT*ds(ells*(ii-1)+(1:ells));
        y(m+n+(1:m)+(ii-2)*(n+m)) = FusT*ds(ells*(ii-1)+(1:ells));
    end
end
end

function y = multByCT(nu,CT,AT,BT,EfT,T,n,m,ellef,switches)
%
% return C'*nu
%
% Where AT = A'
%       BT = B'
%       EfT = Ef'

if switches(5) == 0
    y = CT*nu;
else
    y = zeros(T*(n+m),1);
    
    y(1:m) = -BT*nu(1:n);
    for ii=2:T
        %     y(m+(1:n)+(ii-2)*(n+m)) = nu((1:n) + (ii-2)*n) - AT*nu((1:n) + (ii-1)*n);
        y(m+(1:n)+(ii-2)*(n+m)) = nu((1:n) + (ii-2)*n) - preMultByA(nu((1:n) + (ii-1)*n),AT,switches);
        y(m+n+(1:m)+(ii-2)*(n+m)) = -BT*nu((1:n) + (ii-1)*n);
    end
    y((T-1)*(n+m)+m+(1:n)) = nu((1:n) + (T-1)*n);
    
    if ellef>0,
        y(1+m+(T-1)*(m+n):(T*(n+m))) = nu((1:n) + (T-1)*n) + EfT*nu((1:ellef) + T*n);
    end
end
end

function y = preMultByA(M,A,switches)
%
% returns A*M
%

if switches(6) == 0
    y = A*M;
else
    % Define n in this instance as a half the number of states (i.e. per axis)
    n = size(A,1)/2;
    
    y = zeros(size(A,1),size(M,2));
    
    for ii=1:2
        y((1:n)+(ii-1)*n,:) = A(1:n,1:n)*M((1:n)+(ii-1)*n,:);
    end
end
end

function y = multByAT(M,AT,switches)
%
% returns M*AT
%

if switches(7) == 0
    y = M*AT;
else
    % Define n in this instance as a half the number of states (i.e. per axis)
    n = size(AT,1)/2;
    
    y = zeros(size(M,1),size(AT,2));
    
    for ii=1:2
        y(:,(1:n)+(ii-1)*n) = M(:,(1:n)+(ii-1)*n)*AT(1:n,1:n);
    end
end
end