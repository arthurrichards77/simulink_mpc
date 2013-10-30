% load QP result for comparison
load('QP.mat','simout')

% just grab the control history
uqp = simout(:,4);

% also grab the time results
load('KS_NS_10.mat')

iters=(3:10);

for ii=1:length(iters),
    
    load(sprintf('Slacks_%i.mat',iters(ii)),'simout')
    % control "error"
    sldiffs(ii) = norm(simout(:,4) - uqp);
    
    load(sprintf('KS_%i.mat',iters(ii)),'simout')
    % control "error"
    ksdiffs(ii) = norm(simout(:,4) - uqp);
    
end

figure
plot(ksTimes,ksdiffs,'o-',slackTimes,sldiffs,'x-')
legend('K-S','Slacks','Location','NorthWest')
axis([0 15 0 1.5])

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

