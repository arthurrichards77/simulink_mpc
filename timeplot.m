load KS_NS_10.mat

figure
plot(iters,ksTimes,'o-',iters,ksFmTimes,'v-',iters,ksNpTimes,'s-',iters,slackTimes,'x-')
xlabel('Number of Newton iterations')
ylabel('Total simulation run time')
legend('K-S','K-S w/o diagonal','K-S w/o Pade','Slacks','Location','NorthWest')

axis([2 11 0 15])

print -depsc simtimes.eps

figure
plot(iters,ksTimes,'o-',iters,ksFmTimes,'v-',iters,ksNpTimes,'s-',iters,ksNsTimes,'^-',iters,slackTimes,'x-')
xlabel('Number of Newton iterations')
ylabel('Total simulation run time')
legend('K-S','K-S w/o diagonal','K-S w/o Pade','Not Sparse','Slacks','Location','NorthWest')

axis([2 11 0 15])

print -depsc simtimes2.eps