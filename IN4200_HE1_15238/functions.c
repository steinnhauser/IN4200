void arg_parser(int argc, char *argv[], int *tbool, int *pbool, int *dbool, char **filename)
{
    /* Function to parse the arguments of the executable, such that flags such as -t 
    and -p can be utilized to indicate whether or not the user would like to test or 
    parallelize the functions. All functions have testing capabilities (besides the 
    top_n_webpages), though only some of the functions have OpenMP parallelization 
    implemented. Added a -d flag for the default filename for easier execution.
    
    The function also takes in a filename argument. An error is raised if there is 
    more than one, and the filename argument is ignored if testing is initiated. */
    int option, optind, flags = 0;

    if (argc == 1)
    {
        printf("Bad usage: %s requires at least one command line argument.\nTry:\t%s [filename]\nor:\t%s [-d] for default data file,\n\t%s [-t] for testing,\n", argv[0], argv[0], argv[0], argv[0]);
        exit(EXIT_FAILURE);
    }

    while((option = getopt(argc, argv, "tpd")) != -1)
	{
		switch(option)
		{
			case 't':
				(*tbool) = 1;
                flags++;
                (*filename) = "data/testingdata.txt";
				break;
			case 'p':
				(*pbool) = 1;
                flags++;
                break;
            case 'd':
				(*dbool) = 1;
                flags++;
                (*filename) = "data/web-NotreDame.txt";
                break;
			default:
                fprintf(stderr, "Usage: %s [filename], [-t] for testing, [-p] for parallelization\n", argv[0]);
                exit(EXIT_FAILURE);
		}
	}

    int fnameset = (!(*tbool) && !(*dbool));

    /* The arguments which are not flags are treated as the filename for the data. 
    Do not overwrite the filename either the [-t] or the [-d] flag is passed. */
    for(; optind < argc; optind++)
    {
        if (fnameset) {(*filename) = argv[optind];}
    } 

    /* If more than one non-flag additional argument is passed raise an error. 
    Exception is for testing [-t] and if the default flag [-d] is passed. */
    if (((argc-flags) != 2) && (fnameset))
    {
        printf("Syntax error: Expected one filename argument.\n");
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