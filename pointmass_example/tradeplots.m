% load QP result for comparison
load('QP.mat','simout')

% channel to compare
cmpChannel = 4;

% just grab the control history
uqp = simout(:,cmpChannel);

% also grab the time results
load('KS_12.mat','ksTimes')
load('Slacks_12.mat','slackTimes')
load('KS_OU2_12.mat','ksOu2Times')
load('KS_OU2_12.mat','slackOu2Times')
%iters=(3:12);

for ii=1:length(iters),
    
    load(sprintf('Slacks_%i.mat',iters(ii)),'simout')
    % control "error"
    sldiffs(ii) = norm(simout(:,cmpChannel) - uqp);
    
    load(sprintf('KS_%i.mat',iters(ii)),'simout')
    % control "error"
    ksdiffs(ii) = norm(simout(:,cmpChannel) - uqp);
    
    load(sprintf('KS_OU2_%i.mat',iters(ii)),'simout')
    % control "error"
    ksOuDiffs(ii) = norm(simout(:,cmpChannel) - uqp);
    
    load(sprintf('Slacks_OU2_%i.mat',iters(ii)),'simout')
    % control "error"
    slOuDiffs(ii) = norm(simout(:,cmpChannel) - uqp);
    
end

figure
plot(ksTimes,ksdiffs,'o-',ksOu2Times,ksOuDiffs,'s-',slackTimes,sldiffs,'x-',slackOu2Times,slOuDiffs,'+-')
legend('K-S','K-S x 2','Slacks','Location','NorthWest')
%axis([0 18 0 1.5])



print -depsc trades.eps

return
    
for ii=1:length(iters),
    
    % control and velocity plot
    figure
    subplot 312
    plot(simout(:,1),simout(:,3),'b',[0 200],[0.2 0.2],'r--',[0 200],[-0.2 -0.2],'r--')
    ylabel('Velocity x_2')
    axis([0 200 -0.4 0.25])
    subplot 313
    plot(simout(:,1),simout(:,4),'b',[0 200],[0.1 0.1],'r-.',[0 200],[-0.1 -0.1],'r-.')
    xlabel('Time')
    ylabel('Control u')
    axis([0 200 -0.12 0.12])
    
    % position vs reference
    subplot 311
    plot(simout(:,1),simout(:,2),'b',simout(:,1),simout(:,5),'m--')
    ylabel('Position x_1')
    %xlabel('Time')
    legend('Response','Reference','Location','NorthWest')
    title(sprintf('Slack variables, %i iterations',iters(ii)))
    
    print('-depsc',sprintf('SL_%i.eps',iters(ii)))
    
    % %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    load(sprintf('KS_%i.mat',iters(ii)),'simout')
    
    % control and velocity plot
    figure
    subplot 312
    plot(simout(:,1),simout(:,3),'b',[0 200],[0.2 0.2],'r--',[0 200],[-0.2 -0.2],'r--')
    ylabel('Velocity x_2')
    axis([0 200 -0.4 0.25])
    subplot 313
    plot(simout(:,1),simout(:,4),'b',[0 200],[0.1 0.1],'r-.',[0 200],[-0.1 -0.1],'r-.')
    xlabel('Time')
    ylabel('Control u')
    axis([0 200 -0.12 0.12])
    
    % position vs reference
    subplot 311
    plot(simout(:,1),simout(:,2),'b',simout(:,1),simout(:,5),'m--')
    ylabel('Position x_1')
    %xlabel('Time')
    legend('Response','Reference','Location','NorthWest')
    title(sprintf('K-S method, %i iterations',iters(ii)))
    
    print('-depsc',sprintf('KS_%i.eps',iters(ii)))
    
    % %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    load(sprintf('KS_NP_%i.mat',iters(ii)),'simout')
    
    % control and velocity plot
    figure
    subplot 312
    plot(simout(:,1),simout(:,3),'b',[0 200],[0.2 0.2],'r--',[0 200],[-0.2 -0.2],'r--')
    ylabel('Velocity x_2')
    axis([0 200 -0.4 0.25])
    subplot 313
    plot(simout(:,1),simout(:,4),'b',[0 200],[0.1 0.1],'r-.',[0 200],[-0.1 -0.1],'r-.')
    xlabel('Time')
    ylabel('Control u')
    axis([0 200 -0.12 0.12])
    
    % position vs reference
    subplot 311
    plot(simout(:,1),simout(:,2),'b',simout(:,1),simout(:,5),'m--')
    ylabel('Position x_1')
    %xlabel('Time')
    legend('Response','Reference','Location','NorthWest')
    title(sprintf('K-S method w/o Pade, %i iterations',iters(ii)))
    
    print('-depsc',sprintf('KS_NP_%i.eps',iters(ii)))
    
    % %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    load(sprintf('KS_NS_%i.mat',iters(ii)),'simout')
    
    % control and velocity plot
    figure
    subplot 312
    plot(simout(:,1),simout(:,3),'b',[0 200],[0.2 0.2],'r--',[0 200],[-0.2 -0.2],'r--')
    ylabel('Velocity x_2')
    axis([0 200 -0.4 0.25])
    subplot 313
    plot(simout(:,1),simout(:,4),'b',[0 200],[0.1 0.1],'r-.',[0 200],[-0.1 -0.1],'r-.')
    xlabel('Time')
    ylabel('Control u')
    axis([0 200 -0.12 0.12])
    
    % position vs reference
    subplot 311
    plot(simout(:,1),simout(:,2),'b',simout(:,1),simout(:,5),'m--')
    ylabel('Position x_1')
    %xlabel('Time')
    legend('Response','Reference','Location','NorthWest')
    title(sprintf('K-S method w/o using Sparsity, %i iterations',iters(ii)))
    
    print('-depsc',sprintf('KS_NS_%i.eps',iters(ii)))
    
end

