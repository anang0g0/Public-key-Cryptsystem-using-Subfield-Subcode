
test:
	clang-10 -Wall -g -pg -O3 -DSRAND=1602886277 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp main.c

gcc:
	gcc -Wall -g -pg -O3 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp main.c

mtx:

	gcc -O3 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops mtx.c
clean:
	rm -f a.out
