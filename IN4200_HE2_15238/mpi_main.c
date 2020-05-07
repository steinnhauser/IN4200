#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <omp.h>

#include "mpi_count_friends_of_ten.c"
#include "functions.c"

int main(int argc, char *argv[])
{
    printf("Running file %s\n", argv[0]);

    /* Initialize the array v and values M, N.
     * Allocate memory and set values for M rows and N columns.
     * Save the array in the row-major storage order. */

    int M = 7, N = 9;
    int *A = (int*) malloc(M * N * sizeof(int*));
    int **v = (int**) malloc(M * sizeof(int*));
    if (v == NULL || A == NULL)
    {
        printf("Error in allocating memory.\n");
    }

    for (int i = 0; i < M; i++)
    {
        v[i] = &(A[i * N]);
        // fill this array with zeros
        for (int j = 0; j < M; j++)
        {
            v[i][j] = 0;
        }
    }

    /* Fill the matrix with values. See to the functions.c file for example matrices to fill up.
     * get_mtx1 requires M = 4, N = 5, and fills the matrix up with the values from the example text.
     * get_mtx4 fills the matrix up with pseudo-random numbers. No M or N requirements. */
    get_mtx4(M, N, &v);
    
    // Call the count friends of ten MPI function
    int no = MPI_count_friends_of_ten(M, N, v);
    printf("=======================================================\n");
    printf("Total number of triple-friends of 10 was found to be %d\n", no);
    printf("=======================================================\n");

    return 0;
}