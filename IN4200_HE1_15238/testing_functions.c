void test_Exercise1()
{
    /* Function to test the read_graph_from_file1 and read_graph_from_file2 
    modules by using the example given in the exercise paper. These have 
    well defined and known values. Begin with read_graph_from_file1. */

    // Know the true values to be:
    int trueN = 8, trueEdges = 17, errno = 0, N, trueMtx[8][8] = {
        {0, 0, 0, 0, 0, 0, 1, 0},
        {1, 0, 1, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 1, 0},
        {0, 0, 0, 1, 1, 0, 0, 1},
        {0, 0, 0, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 1, 1, 1, 0},
    };

    // Now read in the values using the function read_graph_from_file1
    char **table2D;
    char *filename;
    filename = "data/testingdata.txt";
    read_graph_from_file1(filename, &N, &table2D);

    // Assess whether the 2d arrays trueMtx and table2D are equal:
    if (trueN != N)
    {
        printf("N was extracted incorrectly in function read_graph_from_file1\n");
        printf("True N is: %d, while extracted N is: %d\n", trueN, N);
        errno++;
    } 
    else {
        for (int i = 0; i < trueN; i++)
        {
            for (int j = 0; j < trueN; j++)
            {
                if (trueMtx[i][j] != table2D[i][j])
                {
                errno++;
                }
            }
        }
    }
    printf("Test read_graph_from_file1 passed with \t\t %d errors.\n", errno);

    /* Now test the implementation of the read_graph_from_file2 function.
    Once again using the example data given in the exercise text, as the 
    col_idx and row_ptr arrays of this data are well defined as: */

    int trueCol_idx[17] = {
        6, 0, 2, 3, 0, 1, 2, 3, 6, 3, 4, 7, 4, 7, 4, 5, 6
    }; // length N_links

    int trueRow_ptr[9] = {
        0, 1, 4, 5, 6, 9, 12, 14, 17
    }; // length N + 1

    int N_links;
    int *row_ptr, *col_idx;

    read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);

    /* Assess the performance of the function by comparing 
    the arrays to their respective 'true values'*/
    if ((trueN != N) || (trueEdges != N_links))
    {
        printf("N or N_links was extracted incorrectly in function read_graph_from_file2\n");
        printf("True N is: %d, while extracted N is: %d\n", trueN, N);
        printf("True N_links is: %d, while extracted N_links is: %d\n", trueEdges, N_links);
        errno++;
    } 
    else {
        for (int i = 0; i < (trueN + 1); i++)
        {
            if (trueRow_ptr[i] != row_ptr[i])
            {
                errno++;
            }
        }
        for (int j = 0; j < trueEdges; j++)
        {
            if (trueCol_idx[j] != col_idx[j])
            {
                errno++;
            }
        }
    }
    printf("Test read_graph_from_file2 passed with \t\t %d errors.\n", errno);
} // test_Exercise1

void test_Exercises_2_and_3()
{
    /* Function to assess the performances of the count_mutual_links1
    and count_mutual_links2 module implementations. The testing data
    used will once again be the web graph provided by the exercise text.
    Function utilizes previous implementations to extract table2D, so these
    are assumed to be tested beforehand. Tests are performed on both the
    regular implementations as well as the ones where OpenMP is utilized. */

    // Correct values, listed as {node no., no. of mutual links}.
    int correctVals[8][2] = {
        {0, 2},
        {1, 0},
        {2, 4},
        {3, 6},
        {4, 5},
        {5, 2},
        {6, 4},
        {7, 3}
    };
    int reg_errno = 0, omp_errno = 0, N, reg_total_links, omp_total_links, trueTotal_links = 13;

    // Extract the table2D array using the first function implementation.
    char **table2D;
    char *filename;
    filename = "data/testingdata.txt";
    read_graph_from_file1(filename, &N, &table2D);

    int *num_involvements;
    num_involvements = alloc_1d_zeros(N);

    reg_total_links = count_mutual_links1(N, table2D, num_involvements);

    // Check the regular total links and num_involvements values for errors.
    if (reg_total_links != trueTotal_links)
    {
        reg_errno++;
    }
    for (int i = 0; i < N; i++)
    {
        if (correctVals[i][1] != num_involvements[i])
        {
            reg_errno++;
        }
    }

    // Set the num_involvements array to zeros and generate the data using <omp.h>
    num_involvements = alloc_1d_zeros(N);
    omp_total_links = count_mutual_links_OpenMP1(N, table2D, num_involvements);


    // Check the OMP total links and num_involvements values for errors.
    if (omp_total_links != trueTotal_links)
    {
        omp_errno++;
    }
    for (int i = 0; i < N; i++)
    {
        if (correctVals[i][1] != num_involvements[i])
        {
            omp_errno++;
        }
    }

    printf("Test count_mutual_links1 passed with \t\t %d errors.\n", reg_errno);
    printf("Test count_mutual_links_OpenMP1 passed with \t %d errors.\n", omp_errno);

    // Finalize
    free(num_involvements);
    free(table2D);

    /* Now test the implementation of count_mutual_links2. Use the same example 
    data, and extract the col_idx and row_ptr arrays using read_graph_from_file2.c.
    Once again testing the implementation of the parallelized function as well. */

    int N_links;
    int *row_ptr, *col_idx;

    reg_errno = 0; omp_errno = 0;
    num_involvements = alloc_1d_zeros(N);

    read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);
    reg_total_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);

    // Check the total links and num_involvements values again
    if (reg_total_links != trueTotal_links)
    {
        reg_errno++;
    }
    for (int i = 0; i < N; i++)
    {
        if (correctVals[i][1] != num_involvements[i])
        {
            reg_errno++;
        }
    }

    // Set num_involvements to zero and test the parallelized version
    num_involvements = alloc_1d_zeros(N);
    omp_total_links = count_mutual_links_OpenMP2(N, N_links, row_ptr, col_idx, num_involvements);

    // Check the OMP implementation for errors.
    if (omp_total_links != trueTotal_links)
    {
        omp_errno++;
    }
    for (int i = 0; i < N; i++)
    {
        if (correctVals[i][1] != num_involvements[i])
        {
            omp_errno++;
        }
    }

    printf("Test count_mutual_links2 passed with \t\t %d errors.\n", reg_errno);
    printf("Test count_mutual_links_OpenMP2 passed with \t %d errors.\n", omp_errno);


    /* Test the top_n_webpages functions as well. */
    top_n_webpages(N, num_involvements, 4);

    // Finalize
    free(num_involvements);
    free(row_ptr);
    free(col_idx);
} // test_Exercises_2_and_3