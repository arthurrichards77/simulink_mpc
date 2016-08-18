% check flag
opts(4)=0;

% diag flag
opts(1)=0;

% number of iters
opts(2)=11;

% soft cons 1=on 0=ignore
opts(3)=1;

% checking
opts(4)=0;

% turn off Pade with opt 5 = 1
opts(5)=1;

% dummy state
x = [0.1 0 0]';

% dummy previous solution
z0 = 0*g+0.01;

% target state
xt = [0 0 0]';

% estimated disturbance
d = [0 0.05 0]';

[z_ks2,info2] = mpcsolve_outer(x,xt,d,H,g,gt,P,hc,hx,C,bx,bd,z0,A,B,Fx,Fu,Ff,Q,R,Qf,opts,Ps,hcs,hxs,Ef,Fxs,Fus);
info2

%% code generation

% first set up dynamic inputs
c_x = coder.typeof(x);
c_xt = coder.typeof(xt);
c_d = coder.typeof(d);
c_z0 = coder.typeof(z0);

% and now the many constants
c_H = coder.Constant(H);
c_g = coder.Constant(g);
c_gt = coder.Constant(gt);
c_P = coder.Constant(P);
c_hc = coder.Constant(hc);
c_hx = coder.Constant(hx);
c_C = coder.Constant(C);
c_bx = coder.Constant(bx);
c_bd = coder.Constant(bd);
c_A = coder.Constant(A);
c_B = coder.Constant(B);
c_Fx = coder.Constant(Fx);
c_Fu = coder.Constant(Fu);
c_Ff = coder.Constant(Ff);
c_Q  = coder.Constant(Q);
c_R  = coder.Constant(R);
c_Qf = coder.Constant(Qf);
c_opts = coder.Constant(opts);
c_Ps = coder.Constant(Ps);
c_hcs = coder.Constant(hcs);
c_hxs = coder.Constant(hxs);
c_Ef  = coder.Constant(Ef);
c_Fxs = coder.Constant(Fxs);
c_Fus = coder.Constant(Fus);

% make a mex for testing
%codegen mpcsolve_outer -report -args {c_x,c_xt,c_d,c_H,c_g,c_gt,c_P,c_hc,c_hx,c_C,c_bx,c_bd,c_z0,c_A,c_B,c_Fx,c_Fu,c_Ff,c_Q,c_R,c_Qf,c_opts,c_Ps,c_hcs,c_hxs,c_Ef,c_Fxs,c_Fus}

% now test the mex - still wants the constant inputs, although will complain if they change
[z_ks3,info3] = mpcsolve_outer_mex(x,xt,d,H,g,gt,P,hc,hx,C,bx,bd,z0,A,B,Fx,Fu,Ff,Q,R,Qf,opts,Ps,hcs,hxs,Ef,Fxs,Fus);
info3

% make C code this time
codegen mpcsolve_outer -c -d mpclib -config:lib -report -args {c_x,c_xt,c_d,c_H,c_g,c_gt,c_P,c_hc,c_hx,c_C,c_bx,c_bd,c_z0,c_A,c_B,c_Fx,c_Fu,c_Ff,c_Q,c_R,c_Qf,c_opts,c_Ps,c_hcs,c_hxs,c_Ef,c_Fxs,c_Fus}
