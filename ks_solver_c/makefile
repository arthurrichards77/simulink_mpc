#MPCLIB = linsolve.o all.o blkdiag.o diag.o eig.o eye.o isfinite.o mod.o mpcsolve.o mpcsolve_outer.o mpcsolve_outer_initialize.o mpcsolve_outer_rtwutil.o mpcsolve_outer_terminate.o norm.o rdivide.o rt_nonfinite.o rtGetInf.o rtGetNaN.o sqrt.o
# copied from Matlab makefile output, replacing .obj with .o for gcc
MPCLIB = mpcsolve_outer_initialize.o mpcsolve_outer_terminate.o mpcsolve_outer.o mpcsolve.o rdivide.o diag.o all.o norm.o linsolve.o rt_nonfinite.o rtGetNaN.o rtGetInf.o

all: mpctest.c $(MPCLIB)
	gcc -o mpctest -I mpclib -L mpclib mpctest.c $(MPCLIB) -lm 

clean:
	rm *o mpctest
 
%.o: mpclib/%.c
	gcc -c -I mpclib $< -o $@ -lm
