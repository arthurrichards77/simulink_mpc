% generate random disturbance

% number of points
Nw = 5000;

% in format for read in to Simulink
w = [dt*(1:Nw)-1;rand(6,Nw)-0.5];

% save it
save w.mat w
