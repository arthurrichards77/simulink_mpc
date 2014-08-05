%% load results
load results/KSND_N5_B5.mat

%%
figure
plot(barrIters,ksTimes(3,:),'o-',barrIters,ksNoPadeTimes(3,:),'^:',barrIters,ksNoDiagTimes(3,:),'+-.',barrIters,slackTimes(3,:),'ks-')
xlabel('Number of Barrier+KS iterations')
ylabel('Total simulation run time')
legend('K-S','K-S w/o diagonal \Phi','K-S w/o Pade','Slacks','Location','NorthWest')
title('All cases: 3 Newton Iters per Barrier Iter')
axis([0 6 0 25])

print -depsc results/simtimes4.eps