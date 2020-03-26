void arg_parser(int argc, char *argv[], int *tbool, int *pbool, int *dbool, char **filename)
{
    /* Function to parse the arguments of the executable, such that flags such as -t 
    and -p can be utilized to indicate whether or not the user would like to test or 
    parallelize the functions. All functions have testing capabilities (besides the 
    top_n_webpages), though only some of the functions have OpenMP parallelization 
    implemented. Added a -d flag for the default filename for easier execution.
    
    The function also takes in a filename argument. An error is raised if there is 
    more than one, and the filename argument is ignored if testing is initiated. */
    int option; 
    while((option = getopt(argc, argv, "tpd")) != -1)
	{
		switch(option)
		{
			case 't':
				(*tbool) = 1;
                (*filename) = "data/testingdata.txt";
				break;
			case 'p':
				(*pbool) = 1;
                break;
            case 'd':
				(*dbool) = 1;
                (*filename) = "data/web-NotreDame.txt";
                break;
			default:
                fprintf(stderr, "Usage: %s [filename], [-t] for testing, [-p] for parallelization\n", argv[0]);
                exit(EXIT_FAILURE);
		}
	}

    /* Count up the extra arguments. The arguments which are not flags are treated
    as the filename for the data. If there's more than one, raise a syntax error. */
    int commands = 0;
    for(; optind < argc; optind++)
    {
        if (!(*tbool) && !(*dbool)) {(*filename) = argv[optind];}
        commands++;
    } 

    /* If more than one are passed raise an error. Exception is for
     testing. Then we use the default filename 'data/testingdata.txt' */
    if ((commands != 1) && (!(*tbool) & !(*dbool)))
    {
        printf("Syntax error: %d arguments passed, expected one for filename.\n", commands);
        exit(EXIT_FAILURE);
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