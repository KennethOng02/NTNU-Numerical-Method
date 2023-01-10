all:
	mkdir -p ./bin
	gcc -c matrix.c -o matrix.o
	gcc wk1-horner.c -o ./bin/wk1-horner
	gcc wk1-bisection.c -o ./bin/wk1-bisection
	gcc wk2-fpi.c -o ./bin/wk2-fpi
	gcc wk2-newton-fpi.c -o ./bin/wk2-newton-fpi
	gcc wk3-naiive-gaussian.c -o ./bin/wk3-naiive-gaussian
	gcc wk4-partial-pivoting.c matrix.o -o ./bin/wk4-partial-pivoting
	gcc wk5-jacobi.c -o ./bin/wk5-jacobi
	gcc wk6-nonlinear.c matrix.o -o ./bin/wk6-nonlinear
	gcc wk7-interpolation.c -o ./bin/wk7-interpolation
	gcc wk8-newton-difference-interpolation.c -o ./bin/wk8-newton-difference-interpolation
	gcc wk9-least-square.c matrix.o -o ./bin/wk9-least-square
	gcc wk10-qr.c -o ./bin/wk10-qr
	gcc wk11-gauss-newton.c matrix.o -o ./bin/wk11-gauss-newton
	gcc wk12-gradient-descent.c -o ./bin/wk12-gradient-descent

clean:
	rm ./matrix.o
	rm -rf ./bin
