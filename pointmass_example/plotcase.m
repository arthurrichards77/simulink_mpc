function plotcase(simout,titleStr)

subplot 312
plot(simout(:,1),simout(:,3),'b',[0 200],[0.2 0.2],'r--',[0 200],[-0.2 -0.2],'r--')
ylabel('Velocity x_2')
axis([0 200 -0.25 0.4])
subplot 313
plot(simout(:,1),simout(:,4),'b',[0 200],[0.1 0.1],'r-.',[0 200],[-0.1 -0.1],'r-.')
xlabel('Time')
ylabel('Control u')
axis([0 200 -0.12 0.12])

% position vs reference
subplot 311
plot(simout(:,1),simout(:,2),'b',simout(:,1),simout(:,5),'m--')
ylabel('Position x_1')
%xlabel('Time')
legend('Response','Reference','Location','NorthWest')
title(titleStr)