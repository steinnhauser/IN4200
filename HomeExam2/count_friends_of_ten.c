int count_friends_of_ten(int M, int N, int** v)
{
    int no = 0;

    /*  Have four potential values. First, the horizontal (1), second,
     *  the vertical (2), and the top-left to bottom right diagonal (3)
     *  and the top right to bottom left diagonal (4). */

    // Initialize booleans which describe which triple friends combinations to examine.
    int bool1, bool2, bool34;
    
    printf("Counting 'triple-friends of 10' for matrix:\n");
    printf("--------------\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d, ", v[i][j]);
        }
        printf("\n");
    }
    printf("--------------\n");


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
                    printf("Triple shape (-) found at row: %d, col: %d\n", m, n);
                    no++;
                }
            }

            if (bool2)
            {
                if ((v[m][n] + v[m+1][n] + v[m-1][n]) == 10) // 2
                {
                    printf("Triple shape (|) found at row: %d, col: %d\n", m, n);
                    no++;
                }
            }
    
            if (bool34)
            {
                if ((v[m][n] + v[m-1][n-1] + v[m+1][n+1]) == 10) // 3
                {
                    printf("Triple shape (\\) found at row: %d, col: %d\n", m, n);
                    no++;
                }
                if ((v[m][n] + v[m-1][n+1] + v[m+1][n-1]) == 10) // 4
                {
                    printf("Triple shape (/) found at row: %d, col: %d\n", m, n);
                    no++;
                }
            }
        }
    }

    return no;
}