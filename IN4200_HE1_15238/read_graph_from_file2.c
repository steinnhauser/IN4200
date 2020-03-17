// void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx)
// {
// 	/* Read in a web file, and save the data using the CRS format. */
// 	FILE* datafile;
// 	datafile = fopen(filename, "r");
// 	if (datafile == NULL)
// 	{
// 		printf("Error in reading file %s.\n", filename);
// 		exit(1);
// 	}

// 	/* Can assume that the first two lines contain free text.
// 	Line 3 has the number of nodes and edges in the form:
// 		# Nodes:	int1 Edges: 	int2
// 	These need to be extracted. Line 4 doesn't need extraction. */
// 	char* line = NULL;
// 	size_t len = 0;
// 	ssize_t read;

// 	// read the first two lines.
// 	read = getline(&line, &len, datafile);
// 	read = getline(&line, &len, datafile);

// 	// read in the number of nodes and edges.
// 	fscanf(datafile, "# Nodes: %d Edges: %d\n", N, N_links);

// 	// Can now allocate the memory for the row_ptr and col_idx arrays.
// 	(*row_ptr) = (int*) malloc(((*N) + 1) * sizeof(int));
// 	(*col_idx) = (int*) malloc((*N_links) * sizeof(int));

// 	if ((*row_ptr) == NULL || (*col_idx) == NULL)
// 	{
// 		printf("Error in allocating memory.\n");
// 		exit(1);
// 	}

// 	// read line four
// 	read = getline(&line, &len, datafile);

// 	/* Extract the parameters from the rest of the file.
// 	Use these to build the row_ptr and col_idx arrays. */
// 	int val1, val2, ctr = 0;
// 	int* FromID;
// 	int* ToID;
// 	FromID = (int*) malloc((*N_links) * sizeof(int));
// 	ToID = (int*) malloc((*N_links) * sizeof(int));

// 	// fill the row_ptr array with zeros to prepare for counting.
// 	for (int i = 0; i < ((*N)+1); i++)
// 	{
// 		(*row_ptr)[i] = 0;
// 	}

// 	// scan through the rest of the file.
// 	while (fscanf(datafile, "%d\t%d\n", &val1, &val2) != EOF)
// 	{
// 		/* Save all the values of the file into the arrays FromID 
// 		and ToID. Also count how many occurrences of each ToID values 
// 		there are, following the convention of row_ptr[0]=0 */
// 		if (val1 != val2) {
// 			// Avoid counting self-linkages
// 			(*row_ptr)[val2+1]++;
// 			FromID[ctr] = val1;
// 			ToID[ctr] = val2;
// 			ctr++;
// 		}
// 	}

// 	// Format this vector using convention (gradual addition)
// 	(*row_ptr)[0] = 0;
// 	for (int i = 1; i < ((*N)+1); i++)
// 	{
// 		(*row_ptr)[i] += (*row_ptr)[i-1];
// 	}

// 	// Create the array col_idx
// 	ctr = 0;
// 	int pos = 0;
//     for (int i = 0; i < *N; i++) {
//         if (ctr >= 1000) {
// 			printf("\r");
//             printf("\r%.3f%%", 100 *i / (double) *N);
// 			fflush(stdout);
//             ctr = 0;
//         }
//         else {
//             ctr++;
//         }

//         for (int j = 0; j < *N_links; j++) {
//             if (ToID[j] == i) {
//                 (*col_idx)[pos] = FromID[j];
//                 pos++;
//             }
//         }
//     }
// 	printf("\n");

// 	free(FromID);
// 	free(ToID);
// 	fclose(datafile);
// } // read_graph_from_file2