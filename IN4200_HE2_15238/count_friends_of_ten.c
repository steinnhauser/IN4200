int count_friends_of_ten(int M, int N, int** v)
{
    int no = 0;

    /*  Have four potential values. First, the horizontal (1), second,
     *  the vertical (2), and the top-left to bottom right diagonal (3)
     *  and the top right to bottom left diagonal (4). */

    // Initialize booleans which describe which triple friends combinations to examine.
    int bool1, bool2, bool34;
    
    /*  Can display the matrix, the shapes, and the locations of the friends-of-ten 
     *  by parsing the verbose bool. It is nice to have the verbose bool equal to true 
     *  for smaller matrices, but for larger matrices, simply printing the amount of 
     *  friends-of-ten found is sufficient. */
    int verbose = 1;
    
    if (verbose) {
        printf("Counting 'triple-friends of 10' for matrix:\n");
        printf("[\n");   
        for (int i = 0; i < M; i++)
        {
            printf("   [");
            for (int j = 0; j < N; j++)
            {
                printf(" %d ", v[i][j]);
            }
            printf("],\n");
        }
        printf("]\n");
    }
    


    for (int m = 0; m < M; m++)
    {
        for (int n = 0; n < N; n++)
        {
            bool1 = 1; bool2 = 1; bool34 = 1;

            if ((n == 0) || (n == (N-1))) {
                // Here, we are either in the first or last column. 
                // Don't check horizontal or diagonal values.
                bool1 = 0; bool34 = 0;
            }

            if ((m == 0) || (m == (M-1))) {
                // Here, we are either in the first or last row.
                // Don't check vertical or diagonal values.
                bool2 = 0; bool34 = 0;
            }

            if (bool1) 
            {
                if ((v[m][n] + v[m][n-1] + v[m][n+1]) == 10) // 1
                {
                    if (verbose) {
                        printf("Triple shape (-) found at row: %d, col: %d\n", (m+1), (n+1));
                    }
                    no++;
                }
            }

            if (bool2)
            {
                if ((v[m][n] + v[m+1][n] + v[m-1][n]) == 10) // 2
                {
                    if (verbose) {
                        printf("Triple shape (|) found at row: %d, col: %d\n", (m+1), (n+1));
                    }
                    no++;
                }
            }
    
            if (bool34)
            {
                if ((v[m][n] + v[m-1][n-1] + v[m+1][n+1]) == 10) // 3
                {
                    if (verbose) {
                        printf("Triple shape (\\) found at row: %d, col: %d\n", (m+1), (n+1));
                    }
                    no++;
                }
                if ((v[m][n] + v[m-1][n+1] + v[m+1][n-1]) == 10) // 4
                {
                    if (verbose) {
                        printf("Triple shape (/) found at row: %d, col: %d\n", (m+1), (n+1));
                    }
                    no++;
                }
            }
        }
    }

    return no;
}