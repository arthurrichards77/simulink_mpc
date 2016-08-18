close all
clear all

%% load QP result for comparison
load('QP.mat','simout')

figure
plotcase(simout,sprintf('QuadProg'))
print('-depsc',sprintf('QP.eps',newtIters(ii),barrIters(jj)))

%%

% channel to compare
cmpChannel = 3;

% just grab the control history
uqp = simout(:,cmpChannel);

% list of Newton iteration values
newtIters = (1:5);
barrIters = (1:5);

%% load all combinations
for jj=1:length(barrIters),
    for ii=1:length(newtIters),
        
        % load data
        load(sprintf('SL_N%i_B%i.mat',newtIters(ii),barrIters(jj)),'simout','mytoc')
        % control "error"
        sldiffs(ii,jj) = norm(simout(:,cmpChannel) - uqp);
        sltimes(ii,jj) = mytoc;
        
        figure
        plotcase(simout,sprintf('Slacks (%i barrier / %i Newton iters) Runtime: %.1f',barrIters(jj),newtIters(ii),mytoc))
        print('-depsc',sprintf('SL_N%i_B%i.eps',newtIters(ii),barrIters(jj)))
        
        % load data
        load(sprintf('KS_N%i_B%i.mat',newtIters(ii),barrIters(jj)),'simout','mytoc')
        % control "error"
        ksdiffs(ii,jj) = norm(simout(:,cmpChannel) - uqp);
        kstimes(ii,jj) = mytoc;
        
        figure
        plotcase(simout,sprintf('K-S with Pade (%i barrier / %i Newton iters) Runtime: %.1f',barrIters(jj),newtIters(ii),mytoc))
        print('-depsc',sprintf('KS_N%i_B%i.eps',newtIters(ii),barrIters(jj)))
        
        % load data
        load(sprintf('KSNP_N%i_B%i.mat',newtIters(ii),barrIters(jj)),'simout','mytoc')
        % control "error"
        ksnpdiffs(ii,jj) = norm(simout(:,cmpChannel) - uqp);
        ksnptimes(ii,jj) = mytoc;
        
        figure
        plotcase(simout,sprintf('K-S w/o Pade (%i barrier / %i Newton iters) Runtime: %.1f',barrIters(jj),newtIters(ii),mytoc))
        print('-depsc',sprintf('KSNP_N%i_B%i.eps',newtIters(ii),barrIters(jj)))
        
        % load data
        load(sprintf('KSND_N%i_B%i.mat',newtIters(ii),barrIters(jj)),'simout','mytoc')
        % control "error"
        ksnddiffs(ii,jj) = norm(simout(:,cmpChannel) - uqp);
        ksndtimes(ii,jj) = mytoc;
        
    end
end


%% aggregate plots
figure
plot(sltimes,sldiffs,'ks',kstimes,ksdiffs,'k^',ksnptimes,ksnpdiffs,'kx')

%% new timing plot
newtCt = 3;
figure
plot(barrIters,kstimes(newtCt,:),'-o',barrIters,ksnptimes(newtCt,:),':^',barrIters,ksndtimes(newtCt,:),'+-.',barrIters,sltimes(newtCt,:),'-ks')
legend('K-S with Pade','K-S w/o Pade','K-S w/o Diagonal \Phi','Slacks','Location','NorthWest')
axis([0 6 0 25])
xlabel('Number of Barrier Iterations')
ylabel('Simulation Total Run Time')
title('All cases: 3 Newton Iters per Barrier Iter')
print -depsc newtimes.eps