void get_mtx(int ***v)
{
    int matrix[4][5] = {
        {1, 5, 6, 3, 1},
        {2, 4, 4, 1, 7},
        {7, 2, 3, 1, 2},
        {3, 2, 2, 5, 3}
    };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            (*v)[i][j] = matrix[i][j];
        }
    }


}