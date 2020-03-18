void arg_parser(int argc, char *argv[], int *tbool, int *pbool)
{
    /* Function to parse the arguments of the executable, such that
    flags such as -t and -p can be utilized to indicate whether or
    not the user would like to test or parallelize the functions.
    All functions have testing capabilities (besides the top_n_webpages), 
    though only some of the functions have OpenMP parallelization implemented. */
    int option; 
    while((option = getopt(argc, argv, "tp")) != -1)
	{
		switch(option)
		{
			case 't':
				(*tbool) = 1;
				break;
			case 'p':
				(*pbool) = 1;
				break;
			default:
        fprintf(stderr, "Usage: %s [-t] for testing, [-p] for parallelization\n", argv[0]);
        exit(EXIT_FAILURE);
		}
	}
}

int* alloc_1d_zeros(int N)
{
    int* array = (int*) malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        array[i] = 0;
    }
    return array;
}

char** alloc_2d_zeros(int N)
{
    /* Function to allocate a two-dimensional (N x N) table and fill it with 
    zero values. Care to save the array in the row-major storage order of C.*/
    char *A_str = (char*) malloc(N * N * sizeof(char*));
    char **table = (char**) malloc(N * sizeof(char*));
    if (table == NULL || A_str == NULL)
    {
        printf("Error in allocating memory.\n");
    }

	for (int i = 0; i < N; i++)
	{
		table[i] = &(A_str[i * N]);
        // fill this array with zeros
        for (int j = 0; j < N; j++)
        {
            table[i][j] = 0;
        }
    }
    return table;
}