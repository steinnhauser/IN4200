void MPI_count_using_ghosts(int M, int N, int*v, int *no, int verbose, int N_per_rank)
{
    /* Function which takes as an argument a flattened (M x N) matrix in the one-
     * dimensional array v. The function assumes this array has two additional columns
     * attached to it on each side. These columns should include the ghost values from
     * the neighboring ranks. The function declares when friends of ten are found
     * depending on the verbosity boolean, and counts friends of ten found using
     * the '*no' pointer. The functionality is very similar to the serial case. */

    // Initialize booleans which describe which triple friends combinations to examine.
    int rank, size, bool1, bool2, bool34;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (int m = 0; m < M; m++) {
        for (int n = 1; n < (N-1); n++) {
            // check the neighbors in the same fashion as before
            bool1 = 1, bool2 = 1; bool34 = 1;

            if (((n == 1) && (rank==0)) || ((n == (N-2)) && (rank==(size-1)))) {
                // Here, we are either in the first or last column. 
                // Don't check horizontal or diagonal values.
                bool1 = 0; bool34 = 0;
            }

            if ((m == 0) || (m == (M-1))) {
                // Here, we are either in the first or last row.
                // Don't check vertical or diagonal values.
                bool2 = 0; bool34 = 0;
            }

            if (bool1) {
                if ((v[m + n * M] + v[m + (n-1) * M] + v[m + (n+1) * M]) == 10){ // 1
                    if (verbose){
                        printf("Triple shape (-) found at row: %d, col: %d\n", (m+1), ((n + N_per_rank*rank)));
                    }
                    (*no)++;
                }
            }

            if (bool2){
                if ((v[m + n * M] + v[(m+1) + n * M] + v[(m-1) + n * M]) == 10){ // 2
                    if (verbose){
                        printf("Triple shape (|) found at row: %d, col: %d\n", (m+1), ((n + N_per_rank*rank)));
                    }
                    (*no)++;
                }
            }
    
            if (bool34) {
                if ((v[m + n * M] + v[(m-1) + (n-1) * M] + v[(m+1) + (n+1) * M]) == 10){ // 3
                    if (verbose){
                        printf("Triple shape (\\) found at row: %d, col: %d\n", (m+1), ((n + N_per_rank*rank)));
                    }
                    (*no)++;
                }
                if ((v[m + n * M] + v[(m-1) + (n+1) * M] + v[(m+1) + (n-1) * M]) == 10){ // 4
                    if (verbose){
                        printf("Triple shape (/) found at row: %d, col: %d\n", (m+1), ((n + N_per_rank*rank)));
                    }
                    (*no)++;
                }
            }
        }
    }
}

int MPI_count_friends_of_ten(int M, int N, int** v)
{
    /* Begin this function by splitting the v matrix into multiple matrices 
     * column-wise. This means that there will be N/size columns for each rank.
     * After this is done, a similar algorithm to the previous one must be implemented
     * to count the friends of ten for each element. It is important to be careful
     * about the boundaries between the matrix splits, as additional 'ghost' values
     * need to be added, but not looped over (i.e. element [i,j] needs to access elements 
     * in the next column [i,j+1] which might be allocated to a different rank). */

    int no_per_rank=0, size, rank, verbose = 0; // Vary verbosity to see shapes found.

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (verbose && (rank == 0)) {
        printf("Performing an MPI counting of the friends of ten of matrix:\n");
        for (int m = 0; m < M; m++) {
            for (int n = 0; n < N; n++) {
                printf("%d, ", v[m][n]);
            }
            printf("\n");
        }
    }

    // Broadcast to the other ranks the M, N we're working with.
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Send(&M, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&N, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&M, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    int N_per_rank = N/size;
    int rests = N % size;   // Need to assign these rests columns to the last rank

    // Need to save these 'rests' values before we scatter the v array.
    // Send these values to the last rank.
    int *restCols = malloc(sizeof(int) * rests * M);
    if (rank == 0) {
        for (int n = 0; n < rests; n++){
            for (int m = 0; m < M; m++){
                restCols[m + n * M] = v[m][N_per_rank*size + n];
            }
        }

        MPI_Send(restCols, rests*M, MPI_INT, (size-1), 0, MPI_COMM_WORLD);
    } else if (rank == (size-1)) {
        MPI_Recv(restCols, rests*M, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Flatten the matrix v to use the MPI_Scatter function
    int *v_ = malloc(sizeof(int) * M * N);
    if (rank == 0) {
        for (int n = 0; n < N; n++) {
            for (int m = 0; m < M; m++) {
                v_[m + n*M] = v[m][n];
            }
        }
    }

    /* Create a receiving matrix for the ranks to receive their slices */
    int *recvMtx = malloc(sizeof(int) * M * N_per_rank);

    // Split up the matrix for each rank using the scatter function
    MPI_Scatter(
        v_, M * N_per_rank, MPI_INT,
        recvMtx, M * N_per_rank, MPI_INT,
        0, MPI_COMM_WORLD
    );

    /* Create a slice matrix for each of the ranks to save their slice to.
     * This matrix is slightly larger than it should be, where there 
     * are two columns added to each side for ghost value insertion.
    
     * Insert the received values into the inner columns of the slice matrix. Add 
     * zeros into the extra outer columns which are later used for ghost values. */ 
    int *sliceMtx;
    if (rank == (size-1)) {
        /* For the last rank, allocate the remainder of the whole-number division. */
        sliceMtx = malloc(sizeof(int) * ((M * (N_per_rank+rests)) + 2 * M));
        int ctr = 0;

        // Here we add the restsCols to the sliceMtx of the last rank
        for (int n = 0; n < (N_per_rank + rests + 2); n++) {
            for (int m = 0; m < M; m++) {
                if ((n == 0) || (n == (1 + N_per_rank + rests))) {
                    sliceMtx[m + n * M] = 0;    // Zeros in the padding for now
                } else if (n < (N_per_rank + 1)) {
                    sliceMtx[m + n * M] = recvMtx[m + (n-1) * M];
                } else {
                    sliceMtx[m + n * M] = restCols[ctr];
                    ctr++;
                }
            }
        }
    } else {
        /* For all other ranks, simply pad the left and right sides. */
        sliceMtx = malloc(sizeof(int) * ((M * N_per_rank) + 2 * M));

        for (int n = 0; n < (N_per_rank+2); n++) {
            for (int m = 0; m < M; m++) {
                if ((n == 0) || (n == (1 + N_per_rank))) {
                    sliceMtx[m + n * M] = 0;    // Zeros in the padding for now
                } else {
                    sliceMtx[m + n * M] = recvMtx[m + (n-1) * M];
                }
            }
        }
    }
    /* Insert the ghost values into the borders by sending values from rank 0.
     * Start by creating temporary storage arrays for the sending and receiving */
    int *tempLeftBrd = malloc(sizeof(int) * M);     // Left border/ghost column
    int *tempRightBrd = malloc(sizeof(int) * M);    // Right border/ghost column

    if (rank == 0) {
        for (int node = 0; node < size; node++) {
            /* Insert the columns into the tempLeft and tempRight arrays. Node 0 needs 
             * ghost values from column number (N_per_rank + 1), and Node 1 needs ghost 
             * values from columns (N_per_rank - 1) and (2 * N_per_rank + 1). Send all 
             * these from here and receive in the else statement */ 

            for (int m = 0; m < M; m++)
            {
                // Reset the values to zero each time
                tempLeftBrd[m] = 0;
                tempRightBrd[m] = 0;

                // At the borders, keep the zeros to the left and right borders
                if (node != 0) {
                    tempLeftBrd[m] = v[m][node*N_per_rank - 1];
                } 
                
                if (node != (size-1)) {
                    tempRightBrd[m] = v[m][(node+1)*N_per_rank];
                }
            }

            if (node == 0) {
                // Apply rank zero's own padding/ghost columns
                for (int m = 0; m < M; m++) {
                    sliceMtx[m] = tempLeftBrd[m];
                    sliceMtx[(N_per_rank+1)*M + m] = tempRightBrd[m];
                }
            } else {
                // Send these arrays out
                MPI_Send(tempLeftBrd, M, MPI_INT, node, 0, MPI_COMM_WORLD);
                MPI_Send(tempRightBrd, M, MPI_INT, node, 0, MPI_COMM_WORLD);
            }
        }
    } else {
        // Receive these arrays 
        MPI_Recv(tempLeftBrd, M, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(tempRightBrd, M, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Apply the ghost columns to these ranks' borders
        if (rank != (size-1)) {
            for (int m = 0; m < M; m++) {
                sliceMtx[m] = tempLeftBrd[m];
                sliceMtx[(N_per_rank+1)*M + m] = tempRightBrd[m];
            }
        } else {
            // The last rank has larger boundaries
            for (int m = 0; m < M; m++) {
                sliceMtx[m] = tempLeftBrd[m];
                sliceMtx[(rests+N_per_rank+1)*M + m] = tempRightBrd[m];
            }
        }
    }

    /* Use a version of the serial function which takes in ghost 
     * values and handles on the arrays in a flattened form. */
    if (rank != (size-1)) {
        MPI_count_using_ghosts(M, N_per_rank + 2, sliceMtx, &no_per_rank, verbose, N_per_rank);
    } else {
        MPI_count_using_ghosts(M, N_per_rank + 2 + rests, sliceMtx, &no_per_rank, verbose, N_per_rank);
    }

    // Free all the memory allocated
    free(recvMtx);
    free(sliceMtx);
    free(v_);
    free(tempLeftBrd);
    free(tempRightBrd);

    printf("Rank: %d calculated the number of triple friends to be: %d\n", rank, no_per_rank);

    int total;
    MPI_Allreduce(&no_per_rank, &total, size, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    return total;
}
