% csolve  Solves a custom quadratic program very rapidly.
%
% [vars, status] = csolve(params, settings)
%
% solves the convex optimization problem
%
%   minimize(quad_form(x_0 - xt, Q) + quad_form(u_0, R) + sum(pos(Fxs*x_0 + Fus*u_0 - fs)) + quad_form(x_1 - xt, Q) + quad_form(u_1, R) + sum(pos(Fxs*x_1 + Fus*u_1 - fs)) + quad_form(x_2 - xt, Q) + quad_form(u_2, R) + sum(pos(Fxs*x_2 + Fus*u_2 - fs)) + quad_form(x_3 - xt, Q) + quad_form(u_3, R) + sum(pos(Fxs*x_3 + Fus*u_3 - fs)) + quad_form(x_4 - xt, Q) + quad_form(u_4, R) + sum(pos(Fxs*x_4 + Fus*u_4 - fs)) + quad_form(x_5 - xt, Q) + quad_form(u_5, R) + sum(pos(Fxs*x_5 + Fus*u_5 - fs)) + quad_form(x_6 - xt, Q) + quad_form(u_6, R) + sum(pos(Fxs*x_6 + Fus*u_6 - fs)) + quad_form(x_7 - xt, Q) + quad_form(u_7, R) + sum(pos(Fxs*x_7 + Fus*u_7 - fs)) + quad_form(x_8 - xt, Q) + quad_form(u_8, R) + sum(pos(Fxs*x_8 + Fus*u_8 - fs)) + quad_form(x_9 - xt, Q) + quad_form(u_9, R) + sum(pos(Fxs*x_9 + Fus*u_9 - fs)) + quad_form(x_10 - xt, Q_final))
%   subject to
%     x_1 == A*x_0 + B*u_0 + d
%     x_2 == A*x_1 + B*u_1 + d
%     x_3 == A*x_2 + B*u_2 + d
%     x_4 == A*x_3 + B*u_3 + d
%     x_5 == A*x_4 + B*u_4 + d
%     x_6 == A*x_5 + B*u_5 + d
%     x_7 == A*x_6 + B*u_6 + d
%     x_8 == A*x_7 + B*u_7 + d
%     x_9 == A*x_8 + B*u_8 + d
%     x_10 == A*x_9 + B*u_9 + d
%     Fx*x_0 + Fu*u_0 <= f
%     Fx*x_1 + Fu*u_1 <= f
%     Fx*x_2 + Fu*u_2 <= f
%     Fx*x_3 + Fu*u_3 <= f
%     Fx*x_4 + Fu*u_4 <= f
%     Fx*x_5 + Fu*u_5 <= f
%     Fx*x_6 + Fu*u_6 <= f
%     Fx*x_7 + Fu*u_7 <= f
%     Fx*x_8 + Fu*u_8 <= f
%     Fx*x_9 + Fu*u_9 <= f
%     Ff*x_10 <= ff
%     Ef*x_10 + Ed*d == ef
%
% with variables
%      u_0   1 x 1
%      u_1   1 x 1
%      u_2   1 x 1
%      u_3   1 x 1
%      u_4   1 x 1
%      u_5   1 x 1
%      u_6   1 x 1
%      u_7   1 x 1
%      u_8   1 x 1
%      u_9   1 x 1
%      x_1   3 x 1
%      x_2   3 x 1
%      x_3   3 x 1
%      x_4   3 x 1
%      x_5   3 x 1
%      x_6   3 x 1
%      x_7   3 x 1
%      x_8   3 x 1
%      x_9   3 x 1
%     x_10   3 x 1
%
% and parameters
%        A   3 x 3
%        B   3 x 1
%       Ed   2 x 3
%       Ef   2 x 3
%       Ff   4 x 3
%       Fu   2 x 1
%      Fus   4 x 1
%       Fx   2 x 3
%      Fxs   4 x 3
%        Q   3 x 3    PSD
%  Q_final   3 x 3    PSD
%        R   1 x 1    PSD
%        d   3 x 1
%       ef   2 x 1
%        f   2 x 1
%       ff   4 x 1
%       fs   4 x 1
%      x_0   3 x 1
%       xt   3 x 1
%
% Note:
%   - Check status.converged, which will be 1 if optimization succeeded.
%   - You don't have to specify settings if you don't want to.
%   - To hide output, use settings.verbose = 0.
%   - To change iterations, use settings.max_iters = 20.
%   - You may wish to compare with cvxsolve to check the solver is correct.
%
% Specify params.A, ..., params.xt, then run
%   [vars, status] = csolve(params, settings)
% Produced by CVXGEN, 2014-06-19 05:28:51 -0400.
% CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com.
% The code in this file is Copyright (C) 2006-2012 Jacob Mattingley.
% CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial
% applications without prior written permission from Jacob Mattingley.

% Filename: csolve.m.
% Description: Help file for the Matlab solver interface.
