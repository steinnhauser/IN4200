#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int memory_bandwidth();
int strided_access();
int matrix_mult();

int main(int argc, char *argv[])
{
	srand(time(0));
	clock_t starttime = clock();
	printf("Running file %s\n", argv[0]);

	memory_bandwidth();
	/*
	Following was accomplished with N = 1e9 and s = 43
	-----------------------------------------------------------
	steinn@steinn-PC:~/Desktop/IN4200/Exercises/Week4$ ./test.x
	Running file ./test.x
	Memory bandwidth loop completed after 3.175 seconds.
	Completed after 5.898 seconds.
	*/

	strided_access();
	/*
	Following was accomplished with N = 1e9, s = 43 and stride = 10
	-----------------------------------------------------------
	steinn@steinn-PC:~/Desktop/IN4200/Exercises/Week4$ ./test.x
	Running file ./test.x
	Memory bandwidth loop completed after 3.171 seconds.
	Stride loop completed after 1.346 seconds.
	Completed after 9.924 seconds.
	*/

	matrix_mult();
	/*
	Following was accomplished using n=1e4, m=1e2, p=1e3:
	-----------------------------------------------------------
	steinn@steinn-PC:~/Desktop/IN4200/Exercises/Week4$ ./test.x
	Running file ./test.x
	Completed after 4.559 seconds.
	*/


	double endtime = ((double)(clock() - starttime))/CLOCKS_PER_SEC;
	printf("Completed after %.3f seconds.\n", endtime);
	return 0;
}

int memory_bandwidth()
{
	/* Write a C program that makes use of the kernel loop:
	for (i=0; i<N; i++) {
		A[i] = s*B[i];
	}
	To measure the realistically achieveable memory bandwidth of a CPU
	*/

	int N = 1e9, s = 43;

	// initialize some random values for the A and B arrays
	int *A = NULL, *B = NULL;

	A = (int*) malloc(N * sizeof(int));
	B = (int*) malloc(N * sizeof(int));

	if (A == NULL || B == NULL) {
		printf("Error when allocating memory.\n");
		exit(1);
	}

	// fill B with the natural numbers
	for (int i=0; i<N; i++) {
		B[i] = i;
	}

	// start the time calculation
	clock_t simstart = clock();
	for (int i=0; i<N; i++) {
		A[i] = s*B[i];
	}
	double simend = ((double)(clock() - simstart))/CLOCKS_PER_SEC;
	printf("Memory bandwidth loop completed after %.3f seconds.\n", simend);

	free(A);
	free(B);
}

int strided_access()
{
	/* How will the performance, measured as number of FP operations per second,
	change if the above loop is modified as follows?  And why?

	for (int i=0; i<N; i += stride) {
		A[i] = s*B[i];
	}
	*/

	int N = 1e9, s = 43, stride = 10;

	// initialize some random values for the A and B arrays
	int *A = NULL, *B = NULL;

	A = (int*) malloc(N * sizeof(int));
	B = (int*) malloc(N * sizeof(int));

	if (A == NULL || B == NULL) {
		printf("Error when allocating memory.\n");
		exit(1);
	}

	// fill B with the natural numbers
	for (int i=0; i<N; i++) {
		B[i] = i;
	}

	// start the time calculation
	clock_t simstart = clock();
	for (int i = 0; i < N; i += stride) {
		A[i] = s*B[i];
	}
	double simend = ((double)(clock() - simstart))/CLOCKS_PER_SEC;
	printf("Stride loop completed after %.3f seconds.\n", simend);

	free(A);
	free(B);
}

int matrix_mult()
{
	/* MMult between n x m matrix A and m x p matrix B */
	int n=1e4, m=1e2, p=1e3, i, j, k;

	// allocate the matrices
	int **A = NULL, **B = NULL, **C = NULL;
	A = (int**) malloc(n * sizeof(int*));
	B = (int**) malloc(m * sizeof(int*));
	C = (int**) malloc(n * sizeof(int*));

	for (i = 0; i<n; i++){
		A[i] = (int*) malloc(m * sizeof(int));
		C[i] = (int*) malloc(p * sizeof(int));
	}

	for (i = 0; i<m; i++){
		B[i] = (int*) malloc(p * sizeof(int));
	}

	if (A == NULL || B == NULL || C == NULL){
		printf("Error when allocating memory.\n");
		exit(1);
	}

	// fill the matrices A and B with some values
	for (j = 0; j<m; j++){
		for (i = 0; i<n; i++){
			A[i][j] = i*j + 1;
		}
		for (k = 0; k<p; k++){
			B[j][k] = j*k + 2;
		}
	}

	// perform the matrix multiplication C = AB, where C has dimension n x p
	for (i = 0; i<n; i++){
		for (j=0; j<p; j++){
			for (k = 0; k<m; k++){
				C[i][j] += A[i][k]*B[k][j];
			}
		}
	}

	// finally, free all the memory allocated.
	for (i = 0; i<n; i++){
		free(A[i]);
		free(C[i]);
	}
	for (i = 0; i<m; i++){
		free(B[i]);
	}

	free(A);
	free(B);
	free(C);
}
