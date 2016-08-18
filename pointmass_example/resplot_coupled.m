
% control and velocity plot
figure
subplot 312
plot(simout(:,1),simout(:,3),'b',[0 200],[0.2 0.2],'r--',[0 200],[-0.2 -0.2],'r--')
ylabel('Velocity x_2')
axis([0 200 -0.4 0.25])
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

print('-depsc',sprintf('CP.eps'))

%% phase plane plot
figure
plot(simout(:,2),simout(:,3),[0 2.5],[.3 -0.25 .2 -.2;.05 0 .2 -.2],'r--')
axis([-0.2 2.5 -0.25 0.25])
xlabel('x_1')
ylabel('x_2')

print('-depsc',sprintf('CP_phase.eps'))