
all:
	clang-10 -Wall -g -pg -O3 -DSRAND=1602886277 -mtune=znver1 -march=znver1 -ffast-math -funroll-loops  -fopenmp q-McEliece-demo.c

nie:
	clang -Wall -g -pg -O3 -DSRAND=1602886277 -mtune=znver1 -march=znver1 -ffast-math -funroll-loops  -fopenmp q-Niederreiter-demo.c

dev:
	clang -Wall -g -pg -O3 -DSRAND=1602886277 -mtune=znver1 -march=znver1 -ffast-math -funroll-loops  -fopenmp op.c

old:
	clang-10 -Wall -g -pg -O3 -DSRAND=1602886277 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp old.c

oo:
	clang-10 -Wall -g -pg -O3 -DSRAND=1602886277 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp oo.c

ooo:
	clang-10 -Wall -g -pg -O3 -DSRAND=1602886277 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp nie.c


gcc:
	gcc -Wall -g -pg -O3 -mtune=znver2 -march=znver2 -ffast-math -funroll-loops  -fopenmp main.c

stable:
	gcc -Wall -O3 -g -pg -mtune=native -march=native -ffast-math -funroll-loops -fopenmp oplib.c

clean:
	rm -f a.out
