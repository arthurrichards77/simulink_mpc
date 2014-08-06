close all
clear all

%% KS plot
load results/ks.mat tout simout info_out xmax simtime_ks f
figure

subplot 211
plot(tout,simout(:,3:6),'-',tout,0*tout+xmax,'k:')
axis([0 60 -0.3 0.6])
ylabel Position
title(sprintf('KS Method - Runtime %.1f',simtime_ks))

subplot 212
plot(tout,simout(:,1:2),'-',tout,0*tout+f(1),'k:',tout,0*tout-f(1),'k:')
axis([0 60 -0.6 0.6])
ylabel Control
xlabel Time

print('-depsc','results/ks_4mass.eps')


%% CVXGEN plot
load results/cvxgen.mat tout simout_cvx info_cvx simtime_cvxgen dt
figure

subplot 211
plot(tout,simout_cvx(:,3:6),'-',tout,0*tout+xmax,'k:')
axis([0 60 -0.3 0.6])
ylabel Position
title(sprintf('CVXGEN - Runtime %.1f',simtime_cvxgen))

subplot 212
plot(tout,simout_cvx(:,1:2),'-',tout,0*tout+f(1),'k:',tout,0*tout-f(1),'k:')
axis([0 60 -0.6 0.6])
ylabel Control
xlabel Time

print('-depsc','results/cvxgen_4mass.eps')

%% iteration comparison

figure
titer = [0:dt:60];
plot(titer,info_cvx(:,2),'--',titer,info_out(:,4),'-')
xlabel('Time')
ylabel('Total number of Newton iterations')
cvxstr = sprintf('CVXGEN - %i total iterations',sum(info_cvx(:,2)));
ksstr = sprintf('KS - %i total iterations',sum(info_out(:,4)));
legend(cvxstr,ksstr,'Location','NorthEast')

print('-depsc','results/iters_4mass.eps')
