% quick illustration

x = -5:0.01:5;

% two functions
f1 = x.*x;
f2 = 6 + x +0.1*f1;

% plot'em
figure
plot(x,f1,x,f2)
hold on

% K-S functions
for rho=[0.2 0.5 1 2]
    ks = (1/rho)*log(exp(rho*f1) + exp(rho*f2));
    plot(x,ks,'r')
end

legend('g_1(x)','g_2(x)','KS(g(x))','Location','North')

% add an arrow
annotation('textarrow',[0.7 0.77],[0.5 0.3],'String','Increasing \rho')

print -depsc ksgen.eps

% two functions
f3 = max(x,0);

% plot'em
figure
plot(x,f3)
hold on

% K-S functions
for rho=[0.5 1 2 4]
    ks = (1/rho)*log(1 + exp(rho*x));
    plot(x,ks,'r')
end

legend('\theta_{EXACT}(x)','\theta(x)','Location','NorthWest')

% add an arrow
annotation('textarrow',[0.6 0.67],[0.5 0.3],'String','Increasing \rho')

print -depsc kssoft.eps

% now do a log barrier
x2 = (-5:0.001:0);

figure
plot(x,inf*x,[0 0],[-.2 1],'b')
hold on

for kappa = [0.005 0.01 0.05 0.1]
    plot(x2,-kappa*log(-x2),'r')
end

annotation('textarrow',[0.4 0.6],[0.3 0.2],'String','Decreasing \kappa ')

print -depsc loghard.eps