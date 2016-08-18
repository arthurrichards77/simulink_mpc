%% load CVX result and plot
load results/cvxgen.mat

% plot it including runtime
titleStr = sprintf('CVXGEN - Runtime = %.2f',cvxTime);
plotcase(simout,titleStr)
print('-depsc',sprintf('results/cvxgen.eps'))

%% load KS with 2+2 iterations
load results/KS_N2_B2.mat

% plot it just to check
figure
plotcase(simout,'')

%% iteration comparison plot
figure
plot(tout,info_cvx(:,2),'--', tout,info_out(:,4),'-')
axis([0 200 0 15])
xlabel('Time')
ylabel('Total Number of Newton Iterations')
legend('CVXGEN','K-S','Location','NorthWest')
print('-depsc','results/compareIters.eps')