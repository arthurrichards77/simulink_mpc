load results/KS_NS_12.mat

figure
plot(iters,ksTimes,'o-',iters,ksFmTimes,'v-',iters,ksNpTimes,'s-',iters,slackTimes,'x-')
xlabel('Number of Newton iterations')
ylabel('Total simulation run time')
legend('K-S','K-S w/o diagonal','K-S w/o Pade','Slacks','Location','NorthWest')

axis([2 11 0 15])

print -depsc results/simtimes.eps

figure
plot(iters,ksTimes,'o-',iters,ksFmTimes,'v-',iters,ksNpTimes,'s-',iters,ksNsTimes,'^-',iters,slackTimes,'x-')
xlabel('Number of Newton iterations')
ylabel('Total simulation run time')
legend('K-S','K-S w/o diagonal','K-S w/o Pade','Not Sparse','Slacks','Location','NorthWest')

axis([2 11 0 15])

print -depsc results/simtimes2.eps

figure
plot(iters,ksNpTimes,'o-',iters,ksFmTimes,'v-',iters,slackTimes,'x-')
xlabel('Number of Newton iterations')
ylabel('Total simulation run time')
legend('K-S','K-S w/o diagonal','Slacks','Location','NorthWest')

axis([2 11 0 15])

print -depsc results/simtimes3.eps