% constraints P*x<=q (soft)
P = [1 -1.5]'
q = [1 2]'

% test var
x = linspace(-3,3,1000);

% exact soft constraint cost
Jex = max(0,P(1)*x-q(1)) + max(0,P(2)*x-q(2));

% null space of P' is set of d that would make grad 0
V = null(P');
% just use first vec
V = V(:,1);

% find max entry
[vmax,imax] = max(V);
% and normalize in terms of inf norm
V = V/vmax;

for rhoConst = [1 1.4 3 6 9],
    
    % form K-S approx
    rho = [1 1]*rhoConst
    J2 = log(1+exp(rho(1)*(P(1)*x-q(1))))/rho(1) + log(1+exp(rho(2)*(P(2)*x-q(2))))/rho(2);
    
    % recentre
    for ii=1:length(q),
        
        if ii == imax,
            rho2(ii) = rho(ii);
        else
            rho2(ii) = log((1-V(ii)+exp(rho(imax)*q(imax)))/V(ii))/q(ii);
        end
        
    end
    rho2
    
    J3 = log(1+exp(rho2(1)*(P(1)*x-q(1))))/rho2(1) + log(1+exp(rho2(2)*(P(2)*x-q(2))))/rho2(2);
    
    % mark minimizers
    [J2min,i2min]=min(J2);
    [J3min,i3min]=min(J3);
    
    % plot
    subplot 211
    plot(x,Jex,x,J2,x(i2min),J2min,'k^')
    hold on
    grid on
    title('Uniform \rho')
    axis([-3 3 0 2])

    subplot 212
    plot(x,Jex,x,J3,x(i3min),J3min,'k^')
    hold on
    grid on
    title('Centering \rho_i')
    axis([-3 3 0 2])
    
end