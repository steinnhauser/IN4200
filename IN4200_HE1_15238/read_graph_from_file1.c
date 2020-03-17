
// void read_graph_from_file1(char *filename, int *N, char ***table2D)
// {
// 	/* Function which opens a text file, allocates a 2D table of
// 	correct dimension and reads the web graph info into the table. */

// 	// Open the file for reading
// 	FILE* datafile;
// 	datafile = fopen(filename, "r");
// 	if (datafile == NULL)
// 	{
// 		printf("Error in reading file %s\n", filename);
// 		exit(1);
// 	}

// 	/* Can assume that the first two lines contain free text.
// 	Line 3 has the number of nodes and edges in the form:
// 		# Nodes:	int1 Edges: 	int2
// 	These need to be extracted. Line 4 doesn't need extraction. */
//     char* line = NULL;
//     size_t len = 0;
//     ssize_t read;

//     // read the first two lines.
//     read = getline(&line, &len, datafile);
//     read = getline(&line, &len, datafile);

//     // read in the number of nodes and edges.
//     int edges;
//     fscanf(datafile, "# Nodes: %d Edges: %d\n", N, &edges);

//     // read line four
//     read = getline(&line, &len, datafile);

// 	// Allocate a 2D table, using the pointer table 2D.
// 	(*table2D) = (char**) malloc((*N) * sizeof(char*));
// 	for (int i = 0; i < (*N); i++)
// 	{
// 		(*table2D)[i] = (char*) malloc((*N) * sizeof(char));
//         // fill this array with zeros
//         for (int j = 0; j < (*N); j++)
//         {
//         (*table2D)[i][j] = 0;
//         }
//     }

//     if ((*table2D) == NULL)
//     {
//         printf("Error in allocating memory.\n");
//     }

//     // read the rest of the values and add corresponding ones to the table2D array
//     int val1, val2;
//     while (fscanf(datafile, "%d\t%d\n", &val1, &val2) != EOF)
//     {
//         (*table2D)[val2][val1] = 1;
//     }
// 	// finalize the function
// 	fclose(datafile);
// } // read_graph_from_file1