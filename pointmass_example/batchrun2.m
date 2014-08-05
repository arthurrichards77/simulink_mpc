% batch results generation for ECC 2013
% updated for EJC paper
% now with both inner and outer iterations

close all
clear all

% list of Newton iteration values
newtIters = (1:5);
barrIters = (1:5);

%% slack method
for jj=1:length(barrIters),
    for ii=1:length(newtIters),
        
        % ready for slack version
        prepSoftFewerSlacks
        
        % settings
        opts(1) = 0; % don't assume phi diag, as slacks cause coupling
        opts(2) = newtIters(ii); % number of iterations
        opts(3) = 0; % don't use KS soft cons
        opts(4) = 0; % no debug checking
        opts(5) = 0; % use Pade
        opts(6) = 0; % make use of sparsity
        opts(8) = barrIters(jj);
        
        % initial run to get compiled
        sim mpcSetpointIntpt
        
        % run the sim, timing
        tic
        sim mpcSetpointIntpt
        mytoc = toc;
        slackTimes(ii,jj) = mytoc
        
        % save data
        save(sprintf('results/SL_N%i_B%i.mat',newtIters(ii),barrIters(jj)))
        
    end
end


%% KS method
for jj=1:length(barrIters),
    for ii=1:length(newtIters),
        
        % ready for slack version
        prepSoftKS
        
        % settings
        opts(1) = 1; % do assume phi diag
        opts(2) = newtIters(ii); % number of iterations
        opts(3) = 1; % do use KS soft cons
        opts(4) = 0; % no debug checking
        opts(5) = 0; % use Pade
        opts(6) = 0; % make use of sparsity
        opts(8) = barrIters(jj);
        
        % initial run to get compiled
        sim mpcSetpointIntpt
        
        % run the sim, timing
        tic
        sim mpcSetpointIntpt
        mytoc = toc;
        ksTimes(ii,jj) = mytoc
        
        % save data
        save(sprintf('results/KS_N%i_B%i.mat',newtIters(ii),barrIters(jj)))
        
    end
end

%% KS method without Pade
for jj=1:length(barrIters),
    for ii=1:length(newtIters),
        
        % ready for slack version
        prepSoftKS
        
        % settings
        opts(1) = 1; % do assume phi diag
        opts(2) = newtIters(ii); % number of iterations
        opts(3) = 1; % do use KS soft cons
        opts(4) = 0; % no debug checking
        opts(5) = 1; % don't use Pade
        opts(6) = 0; % make use of sparsity
        opts(8) = barrIters(jj);
        
        % initial run to get compiled
        sim mpcSetpointIntpt
        
        % run the sim, timing
        tic
        sim mpcSetpointIntpt
        mytoc = toc;
        ksNoPadeTimes(ii,jj) = mytoc
        
        % save data
        save(sprintf('results/KSNP_N%i_B%i.mat',newtIters(ii),barrIters(jj)))
        
    end
end

%% KS method without Daig assumption
for jj=1:length(barrIters),
    for ii=1:length(newtIters),
        
        % ready for slack version
        prepSoftKS
        
        % settings
        opts(1) = 0; % do NOT assume phi diag
        opts(2) = newtIters(ii); % number of iterations
        opts(3) = 1; % do use KS soft cons
        opts(4) = 0; % no debug checking
        opts(5) = 0; % do use Pade
        opts(6) = 0; % make use of sparsity
        opts(8) = barrIters(jj);
        
        % initial run to get compiled
        sim mpcSetpointIntpt
        
        % run the sim, timing
        tic
        sim mpcSetpointIntpt
        mytoc = toc;
        ksNoDiagTimes(ii,jj) = mytoc
        
        % save data
        save(sprintf('results/KSND_N%i_B%i.mat',newtIters(ii),barrIters(jj)))
        
    end
end

