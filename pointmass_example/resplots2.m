% batch results generation for ECC 2013
% updated for EJC paper
% now with both inner and outer iterations

close all
clear all

% list of Newton iteration values
newtIters = (1:5);
barrIters = (1:5);

%% slack method
for jj=1:length(barrIters),
    for ii=1:length(newtIters),
        
        % save data
        load(sprintf('results/SL_N%i_B%i.mat',newtIters(ii),barrIters(jj)))
        
        % plot it
        figure
        plotcase(simout,sprintf('Slacks (%i barrier / %i Newton iters) Runtime: %.1f',barrIters(jj),newtIters(ii),mytoc))
        
        % print it
        print('-depsc',sprintf('results/SL_N%i_B%i.eps',newtIters(ii),barrIters(jj)))
        
    end
end


%% KS method
for jj=1:length(barrIters),
    for ii=1:length(newtIters),
        
        % save data
        load(sprintf('results/KS_N%i_B%i.mat',newtIters(ii),barrIters(jj)))
        
        % plot it
        figure
        plotcase(simout,sprintf('KS with Pade (%i barrier / %i Newton iters) Runtime: %.1f',barrIters(jj),newtIters(ii),mytoc))
        
        % print it
        print('-depsc',sprintf('results/KS_N%i_B%i.eps',newtIters(ii),barrIters(jj)))                
        
    end
end

%% KS method without Pade
for jj=1:length(barrIters),
    for ii=1:length(newtIters),
        
        % save data
        load(sprintf('results/KSNP_N%i_B%i.mat',newtIters(ii),barrIters(jj)))
        
        % plot it
        figure
        plotcase(simout,sprintf('KS w/o Pade (%i barrier / %i Newton iters) Runtime: %.1f',barrIters(jj),newtIters(ii),mytoc))
        
        % print it
        print('-depsc',sprintf('results/KSNP_N%i_B%i.eps',newtIters(ii),barrIters(jj)))            
                
    end
end

%% KS method without Daig assumption
for jj=1:length(barrIters),
    for ii=1:length(newtIters),
        
        % save data
        load(sprintf('results/KSND_N%i_B%i.mat',newtIters(ii),barrIters(jj)))
        
        % plot it
        figure
        plotcase(simout,sprintf('KS w/o Diag \\Phi (%i barrier / %i Newton iters) Runtime: %.1f',barrIters(jj),newtIters(ii),mytoc))
        
        % print it
        print('-depsc',sprintf('results/KSND_N%i_B%i.eps',newtIters(ii),barrIters(jj)))           
                
    end
end

