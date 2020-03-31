void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx)
{
	/* Function to read in a file in the same fashion as the read_graph_from_file1 
	function. This time, the data is saved in a CRS format instead of into a 2D table. */
	
	// Read in the datafile in the same way as previously
	FILE* datafile;
	datafile = fopen(filename, "r");
	if (datafile == NULL)
	{
		printf("Error in reading file %s.\n", filename);
		exit(EXIT_FAILURE);
	}

	/* Can assume that the first two lines contain free text.
	Line 3 has the number of nodes and edges in the form:
		# Nodes:	int1 Edges: 	int2
	These need to be extracted. Line 4 doesn't need extraction. */
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	// Read lines no. 1 & 2
	read = getline(&line, &len, datafile); free(line); line = NULL;
	read = getline(&line, &len, datafile); free(line); line = NULL;

	// Read line no. 3
	int opt = fscanf(datafile, "# Nodes: %d Edges: %d\n", N, N_links);

	// Read line no. 4
	read = getline(&line, &len, datafile); free(line); line = NULL;

	/* Allocate the memory for the row_ptr and col_idx arrays.
	Fill the row_ptr array with zeros to prepare for counting. */
	(*row_ptr) = alloc_1d_zeros((*N) + 1);

	if ((*row_ptr) == NULL)
	{
		printf("Error allocating row_ptr memory.\n");
		exit(EXIT_FAILURE);
	}

	// Extract the parameters from the rest of the file.
	int val1, val2, ctr = 0;
	int *FromID, *ToID;
	FromID 	= alloc_1d_zeros(*N_links);
	ToID	= alloc_1d_zeros(*N_links);

	while (fscanf(datafile, "%d\t%d\n", &val1, &val2) != EOF)
	{
		/* Save all the values of the file into the arrays FromID 
		and ToID. Also count how many occurrences of each ToID values 
		there are, following the convention of row_ptr[0] = 0. */
		if (val1 != val2) {
			// Avoid counting self-linkages
			(*row_ptr)[val2+1]++;
			FromID[ctr] = val1;
			ToID[ctr] = val2;
			ctr++;
		}
	}

	// Reallocate the memory, disregarding the self-linkage terms
	int *F_ID, *T_ID;
	F_ID = (int*) malloc(ctr * sizeof(int));
	T_ID = (int*) malloc(ctr * sizeof(int));
	for (int i = 0; i < ctr; i++){
		F_ID[i] = FromID[i];
		T_ID[i] = ToID[i];
	}
	free(FromID);
	free(ToID);

	// Format the row_ptr array using convention (gradual addition)
	(*row_ptr)[0] = 0;
	for (int i = 2; i < ((*N)+1); i++)
	{
		(*row_ptr)[i] += (*row_ptr)[i-1];
	}

	int *prev_row_ids = alloc_1d_zeros(*N);
	(*col_idx) = (int*) malloc(ctr * sizeof(int));
	if ((*col_idx) == NULL)
	{
		printf("Error allocating col_idx memory.\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < ctr; i++)
	{
		(*col_idx)[(*row_ptr)[T_ID[i]] + prev_row_ids[T_ID[i]]] = F_ID[i];

		// Counts how many places in the current row we've already counted.
		prev_row_ids[T_ID[i]]++;
	}

	// Finalize.
	free(F_ID);
	free(T_ID);
	free(prev_row_ids);
	fclose(datafile);
} // read_graph_from_file2