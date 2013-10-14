% batch results generation for ECC 2013
close all
clear all

% list of Newton iteration values
iters = (3:10);

%% slack method
for ii=1:length(iters),
    
    % ready for slack version
    prepSoftFewerSlacks
    
    % iteration value
    opts(2) = iters(ii);
    
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
    
    % iteration value
    opts(2) = iters(ii);
    
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
    
    % iteration value
    opts(2) = iters(ii);
    opts(5) = 1; % no Pade
    
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
    
    % iteration value
    opts(2) = iters(ii);
    opts(1) = 0; % no diagonal assumption
    opts(5) = 0;
    
    % initial run to get compiled
    sim mpcSetpointIntpt    
    
    % run the sim, timing
    tic
    sim mpcSetpointIntpt
    ksFmTimes(ii)=toc
    
    % save data
    save(sprintf('KS_FM_%i.mat',iters(ii)))
    
end