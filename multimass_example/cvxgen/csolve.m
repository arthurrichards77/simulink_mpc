% csolve  Solves a custom quadratic program very rapidly.
%
% [vars, status] = csolve(params, settings)
%
% solves the convex optimization problem
%
%   minimize(quad_form(x_0 - xt, Q) + quad_form(u_0, R) + sum(pos(Fxs*x_0 - fs)) + quad_form(x_1 - xt, Q) + quad_form(u_1, R) + sum(pos(Fxs*x_1 - fs)) + quad_form(x_2 - xt, Q) + quad_form(u_2, R) + sum(pos(Fxs*x_2 - fs)) + quad_form(x_3 - xt, Q) + quad_form(u_3, R) + sum(pos(Fxs*x_3 - fs)) + quad_form(x_4 - xt, Q) + quad_form(u_4, R) + sum(pos(Fxs*x_4 - fs)) + quad_form(x_5 - xt, Q) + quad_form(u_5, R) + sum(pos(Fxs*x_5 - fs)) + quad_form(x_6 - xt, Q) + quad_form(u_6, R) + sum(pos(Fxs*x_6 - fs)) + quad_form(x_7 - xt, Q) + quad_form(u_7, R) + sum(pos(Fxs*x_7 - fs)) + quad_form(x_8 - xt, Q) + quad_form(u_8, R) + sum(pos(Fxs*x_8 - fs)) + quad_form(x_9 - xt, Q) + quad_form(u_9, R) + sum(pos(Fxs*x_9 - fs)) + quad_form(x_10 - xt, Q) + quad_form(u_10, R) + sum(pos(Fxs*x_10 - fs)) + quad_form(x_11 - xt, Q) + quad_form(u_11, R) + sum(pos(Fxs*x_11 - fs)) + quad_form(x_12 - xt, Q) + quad_form(u_12, R) + sum(pos(Fxs*x_12 - fs)) + quad_form(x_13 - xt, Q) + quad_form(u_13, R) + sum(pos(Fxs*x_13 - fs)) + quad_form(x_14 - xt, Q) + quad_form(u_14, R) + sum(pos(Fxs*x_14 - fs)) + quad_form(x_15 - xt, Q) + quad_form(u_15, R) + sum(pos(Fxs*x_15 - fs)) + quad_form(x_16 - xt, Q) + quad_form(u_16, R) + sum(pos(Fxs*x_16 - fs)) + quad_form(x_17 - xt, Q) + quad_form(u_17, R) + sum(pos(Fxs*x_17 - fs)) + quad_form(x_18 - xt, Q) + quad_form(u_18, R) + sum(pos(Fxs*x_18 - fs)) + quad_form(x_19 - xt, Q) + quad_form(u_19, R) + sum(pos(Fxs*x_19 - fs)) + quad_form(x_20 - xt, Q) + quad_form(u_20, R) + sum(pos(Fxs*x_20 - fs)) + quad_form(x_21 - xt, Q_final))
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
%     x_11 == A*x_10 + B*u_10 + d
%     x_12 == A*x_11 + B*u_11 + d
%     x_13 == A*x_12 + B*u_12 + d
%     x_14 == A*x_13 + B*u_13 + d
%     x_15 == A*x_14 + B*u_14 + d
%     x_16 == A*x_15 + B*u_15 + d
%     x_17 == A*x_16 + B*u_16 + d
%     x_18 == A*x_17 + B*u_17 + d
%     x_19 == A*x_18 + B*u_18 + d
%     x_20 == A*x_19 + B*u_19 + d
%     x_21 == A*x_20 + B*u_20 + d
%     Fu*u_0 <= f
%     Fu*u_1 <= f
%     Fu*u_2 <= f
%     Fu*u_3 <= f
%     Fu*u_4 <= f
%     Fu*u_5 <= f
%     Fu*u_6 <= f
%     Fu*u_7 <= f
%     Fu*u_8 <= f
%     Fu*u_9 <= f
%     Fu*u_10 <= f
%     Fu*u_11 <= f
%     Fu*u_12 <= f
%     Fu*u_13 <= f
%     Fu*u_14 <= f
%     Fu*u_15 <= f
%     Fu*u_16 <= f
%     Fu*u_17 <= f
%     Fu*u_18 <= f
%     Fu*u_19 <= f
%     Fu*u_20 <= f
%     Ff*x_21 <= ff
%
% with variables
%      u_0   2 x 1
%      u_1   2 x 1
%      u_2   2 x 1
%      u_3   2 x 1
%      u_4   2 x 1
%      u_5   2 x 1
%      u_6   2 x 1
%      u_7   2 x 1
%      u_8   2 x 1
%      u_9   2 x 1
%     u_10   2 x 1
%     u_11   2 x 1
%     u_12   2 x 1
%     u_13   2 x 1
%     u_14   2 x 1
%     u_15   2 x 1
%     u_16   2 x 1
%     u_17   2 x 1
%     u_18   2 x 1
%     u_19   2 x 1
%     u_20   2 x 1
%      x_1   8 x 1
%      x_2   8 x 1
%      x_3   8 x 1
%      x_4   8 x 1
%      x_5   8 x 1
%      x_6   8 x 1
%      x_7   8 x 1
%      x_8   8 x 1
%      x_9   8 x 1
%     x_10   8 x 1
%     x_11   8 x 1
%     x_12   8 x 1
%     x_13   8 x 1
%     x_14   8 x 1
%     x_15   8 x 1
%     x_16   8 x 1
%     x_17   8 x 1
%     x_18   8 x 1
%     x_19   8 x 1
%     x_20   8 x 1
%     x_21   8 x 1
%
% and parameters
%        A   8 x 8
%        B   8 x 2
%       Ff   1 x 8
%       Fu   4 x 2
%      Fxs   4 x 8
%        Q   8 x 8    PSD
%  Q_final   8 x 8    PSD
%        R   2 x 2    PSD
%        d   8 x 1
%        f   4 x 1
%       ff   1 x 1
%       fs   4 x 1
%      x_0   8 x 1
%       xt   8 x 1
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
% Produced by CVXGEN, 2014-08-06 08:56:06 -0400.
% CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com.
% The code in this file is Copyright (C) 2006-2012 Jacob Mattingley.
% CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial
% applications without prior written permission from Jacob Mattingley.

% Filename: csolve.m.
% Description: Help file for the Matlab solver interface.
