all: omp_solved2 omp_solved3 omp_solved4 omp_solved5 omp_solved6 jacobi-omp gs-omp

omp_solved2:	omp_solved2.c
	gcc omp_solved2.c -o omp_solved2 -fopenmp -lm -lrt

omp_solved3:	omp_solved3.c
	gcc omp_solved3.c -o omp_solved3 -fopenmp -lm -lrt

omp_solved4:	omp_solved4.c
	gcc omp_solved4.c -o omp_solved4 -fopenmp -lm -lrt

omp_solved5:	omp_solved5.c
	gcc omp_solved5.c -o omp_solved5 -fopenmp -lm -lrt

omp_solved6:	omp_solved6.c
	gcc omp_solved6.c -o omp_solved6 -fopenmp -lm -lrt

jacobi-omp:	jacobi-omp.c
	gcc jacobi-omp.c -o jacobi-omp -fopenmp -lm -lrt

gs-omp:	gs-omp.c
	gcc gs-omp.c -o gs-omp -fopenmp -lm -lrt

clean:
	rm omp_solved2 omp_solved3 omp_solved4 omp_solved5 omp_solved6 gs-omp jacobi-omp