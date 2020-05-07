/* Miscellaneous functions to fill the 2d matrix with various settings. */

void get_mtx1(int M, int N, int ***v)
{
    /* Matrix from the example test. M=4 and N=5 required. */
    int matrix[4][5] = {
        {1, 5, 6, 3, 1},
        {2, 4, 4, 1, 7},
        {7, 2, 3, 1, 2},
        {3, 2, 2, 5, 3}
    };

    if ((M != 4) || (N != 5))
    {
        printf("Usage error in get_mtx1: M=4 and N=5 required.\n");
        exit(1);
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            (*v)[i][j] = matrix[i][j];
        }
    }
}

void get_mtx2(int M, int N, int ***v)
{
    /* Testing matrix of strange size. M=1 and N=5 required. */
    int matrix[1][5] = {
        {1, 5, 6, 3, 1},
    };

    if ((M != 1) || (N != 5))
    {
        printf("Usage error in get_mtx2: M=1 and N=5 required.\n");
        exit(1);
    }


    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            (*v)[i][j] = matrix[i][j];
        }
    }
}

void get_mtx3(int M, int N, int ***v)
{
    /* Testing matrix with a strange sample size. M=4 and N=1 required. */
    int matrix[4][1] = {
        {1},
        {2},
        {7},
        {3}
    };

    if ((M != 4) || (N != 1))
    {
        printf("Usage error in get_mtx3: M=4 and N=1 required.\n");
        exit(1);
    }

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            (*v)[i][j] = matrix[i][j];
        }
    }
}

void get_mtx4(int M, int N, int ***v)
{
    /* Matrix with many pseudo-random values. M=8 and N=11 required. */
    int val, num = 0;   // treat the num initial value as the seed.
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // Generate some (not-so-) pseudo-random numbers from 1 to 9.
            num = ((j + 4) * (i+1) + (j+1) * (num+1) * num * (i + 2) + 3 * i + 4 * j + 9) % 256;
            val = num % 9 + 1;
            (*v)[i][j] = val;
        }
    }
}

