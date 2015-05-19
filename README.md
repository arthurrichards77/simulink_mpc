# simulink_mpc
Soft constrained Simulink MPC utility using fast quadratic programming
Developed at University of Bristol by Arthur Richards

Implements work published in A. Richards, "Fast model predictive control with soft constraints," European Control Conference 2013
http://ieeexplore.ieee.org/xpls/abs_all.jsp?arnumber=6669291&tag=1

@INPROCEEDINGS{6669291, 
author={Richards, A.}, 
booktitle={Control Conference (ECC), 2013 European}, 
title={Fast model predictive control with soft constraints}, 
year={2013}, 
month={July}, 
pages={1-6}, 
abstract={This paper describes a fast optimization algorithm for Model Predictive Control (MPC) with soft constraints. The method relies on the Kreisselmeier-Steinhauser function to provide a smooth approximation of the penalty function for a soft constraint. By introducing this approximation directly into the objective of an interior point optimization, there is no need for additional slack variables to capture constraint violation. Simulation results show significant speed-up compared to using slacks.}, 
keywords={optimisation;predictive control;Kreisselmeier-Steinhauser function;MPC;additional slack variables;constraint violation;fast model predictive control;fast optimization algorithm;interior point optimization;penalty function;smooth approximation;soft constraints;Educational institutions;Function approximation;Optimization;Predictive control;Simulation;Vectors},}
