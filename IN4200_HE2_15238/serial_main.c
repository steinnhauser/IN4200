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

    /* Allocate memory and set values for M rows and N columns.
     * Save the array in the row-major storage order. */
    int M = 100, N = 200;
    int **v = getMtx(M, N);

    /* Fill the matrix with values. See to the functions.c file for example matrices to fill up.
     * get_mtx1 requires M = 4, N = 5, and fills the matrix up with the values from the example text.
     * get_mtx4 fills the matrix up with pseudo-random numbers. No M or N requirements. */
    getRandomMtx(M, N, &v);

    // Call the count friends of ten function
    int no = count_friends_of_ten(M, N, v);
    printf("=======================================================\n");
    printf("Total number of triple-friends of 10 was found to be %d\n", no);
    printf("=======================================================\n");

    double endtime = ((double)(clock() - starttime))/CLOCKS_PER_SEC;
    printf("Completed after %.3f seconds.\n", endtime);
    return 0;
}