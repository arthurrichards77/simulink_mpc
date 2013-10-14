load KS_FM_10.mat

plot(iters,ksTimes,'o-',iters,ksFmTimes,'v-',iters,ksNpTimes,'s-',iters,slackTimes,'x-')
xlabel('Number of Newton iterations')
ylabel('Total simulation run time')
legend('K-S','K-S w/o diagonal','K-S w/o Pade','Slacks','Location','NorthWest')

axis([2 11 0 30])

print -depsc simtimes.eps