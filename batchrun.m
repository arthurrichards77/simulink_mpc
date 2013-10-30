% batch results generation for ECC 2013
% updated for EJC paper to include sparsity stuff
close all
clear all

% list of Newton iteration values
iters = (3:10);

%% slack method
for ii=1:length(iters),
    
    % ready for slack version
    prepSoftFewerSlacks
    
    % settings
    opts(1) = 0; % don't assume phi diag, as slacks cause coupling
    opts(2) = iters(ii); % number of iterations
    opts(3) = 0; % don't use KS soft cons
    opts(4) = 0; % no debug checking
    opts(5) = 0; % use Pade
    opts(6) = 0; % make use of sparsity
    
    % initial run to get compiled
    sim mpcSetpointIntpt    
    
    % run the sim, timing
    tic
    sim mpcSetpointIntpt
    slackTimes(ii)=toc
    
    % save data
    save(sprintf('Slacks_%i.mat',iters(ii)))

end
    
%% K-S
for ii=1:length(iters),
    
    % ready for KS version
    prepSoftKS
    
    % settings
    opts(1) = 1; % assume phi diag
    opts(2) = iters(ii); % number of iterations
    opts(3) = 1; % do use KS soft cons
    opts(4) = 0; % no debug checking
    opts(5) = 0; % use Pade
    opts(6) = 0; % make use of sparsity
    
    % initial run to get compiled
    sim mpcSetpointIntpt    
    
    % run the sim, timing
    tic
    sim mpcSetpointIntpt
    ksTimes(ii)=toc
    
    % save data
    save(sprintf('KS_%i.mat',iters(ii)))
    
end

%% K-S without the Pade
for ii=1:length(iters),
    
    % ready for KS version
    prepSoftKS
    
    % settings
    opts(1) = 1; % assume phi diag
    opts(2) = iters(ii); % number of iterations
    opts(3) = 1; % do use KS soft cons
    opts(4) = 0; % no debug checking
    opts(5) = 1; % don't use Pade
    opts(6) = 0; % make use of sparsity
    
    % initial run to get compiled
    sim mpcSetpointIntpt    
    
    % run the sim, timing
    tic
    sim mpcSetpointIntpt
    ksNpTimes(ii)=toc
    
    % save data
    save(sprintf('KS_NP_%i.mat',iters(ii)))
    
end

%% K-S without assuming diag
for ii=1:length(iters),
    
    % ready for KS version
    prepSoftKS
    
    % settings
    opts(1) = 0; % don't assume phi diag
    opts(2) = iters(ii); % number of iterations
    opts(3) = 1; % do use KS soft cons
    opts(4) = 0; % no debug checking
    opts(5) = 0; % use Pade
    opts(6) = 0; % make use of sparsity
    
    % initial run to get compiled
    sim mpcSetpointIntpt    
    
    % run the sim, timing
    tic
    sim mpcSetpointIntpt
    ksFmTimes(ii)=toc
    
    % save data
    save(sprintf('KS_FM_%i.mat',iters(ii)))
    
end

%% K-S without using sparsity
for ii=1:length(iters),
    
    % ready for KS version
    prepSoftKS
    
    % settings
    opts(1) = 1; % assume phi diag
    opts(2) = iters(ii); % number of iterations
    opts(3) = 1; % do use KS soft cons
    opts(4) = 0; % no debug checking
    opts(5) = 0; % use Pade
    opts(6) = 1; % don't make use of sparsity
    
    % initial run to get compiled
    sim mpcSetpointIntpt    
    
    % run the sim, timing
    tic
    sim mpcSetpointIntpt
    ksNsTimes(ii)=toc
    
    % save data
    save(sprintf('KS_NS_%i.mat',iters(ii)))
    
end