#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mpi.h"

#include "functions.c"
#include "mpi_count_friends_of_ten.c"

int main(int argc, char *argv[])
{
    /* Building upon the sketch given in the exercise text to find
     * the 'friends of ten' for an (M x N) matrix using MPI. */

    int M=0, N=0, rank, num_triple_friends;
    int **v=NULL;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank==0) {
        // decide the values for M and N
        // allocate 2D array v and assign it with suitable values

        // =====================================================================
        M = 100, N = 200;
        v = getMtx(M, N);

        /* Fill the matrix with values. See to the functions.c file for example 
         * matrices to fill up. get_mtx1 requires M = 4, N = 5, and fills the 
         * matrix up with the values from the example text. getRandomMtx fills 
         * the matrix up with pseudo-random numbers. No M or N requirements. */
        // getRandomMtx(M, N, &v);
        getRandomMtx(M, N, &v);
        // =====================================================================
    }
    
    num_triple_friends = MPI_count_friends_of_ten(M, N, v);
    printf("MPI rank <%d>: number of triple friends=%d\n", rank, num_triple_friends);
    
    if (rank == 0) {
        // deallocation of 2D array v
        free(v[0]);
        free(v);

        printf("Total number of triple friends was found to be: %d\n", num_triple_friends);
    }

    MPI_Finalize();    
    return 0;
}