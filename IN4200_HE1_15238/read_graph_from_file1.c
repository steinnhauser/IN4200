
void read_graph_from_file1(char *filename, int *N, char ***table2D)
{
	/* Function which opens a text file of name filename, allocates 
    a 2D table of correct dimension according to the web graph,
    and finally reads the web graph info into the table. */

	// Open the file for reading
	FILE* datafile;
	datafile = fopen(filename, "r");
	if (datafile == NULL)
	{
		printf("Error in reading file %s\n", filename);
		exit(1);
	}

	/* Can assume that the first two lines contain free text.
	Line 3 has the number of nodes and edges in the form:
		# Nodes:	int1 Edges: 	int2
	These need to be extracted. Line 4 doesn't need extraction. */
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    // Lines no. 1 & 2
    read = getline(&line, &len, datafile); free(line); line = NULL;
    read = getline(&line, &len, datafile); free(line); line = NULL;

    // Line no. 3
    int edges, opt;
    opt = fscanf(datafile, "# Nodes: %d Edges: %d\n", N, &edges);

    // Line no. 4
    read = getline(&line, &len, datafile); free(line); line = NULL;

	// Allocate a 2D table, and fill it with zeros
	(*table2D) = alloc_2d_zeros((*N));

    /* Read in the rest of the datafile and add corresponding
    ones to represent linkage into the table2D array. */
    int val1, val2;
    while (fscanf(datafile, "%d\t%d\n", &val1, &val2) != EOF)
    {
        if (val1 != val2)
        {
            // Avoid self-linkages
            (*table2D)[val2][val1] = 1;
        }
    }

	// Finalize.
	fclose(datafile);
    free(line);
} // read_graph_from_file1