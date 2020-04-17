#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "count_friends_of_ten.c"
#include "functions.c"

int main(int argc, char *argv[])
{
    srand(time(0));
    clock_t starttime = clock();
    printf("Running file %s\n", argv[0]);

    // Allocate memory and set values for M rows and N columns
    // Save the array in the row-major storage order.
    int M = 4, N = 5;
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

    // Fill the matrix up with the example matrix in the text.
    get_mtx(&v);

    // Call the count friends of ten function
    int no = count_friends_of_ten(M, N, v);
    printf("=======================================================\n");
    printf("Total number of triple-friends of 10 was found to be %d\n", no);
    printf("=======================================================\n");

    double endtime = ((double)(clock() - starttime))/CLOCKS_PER_SEC;
    printf("Completed after %.3f seconds.\n", endtime);
    return 0;
}