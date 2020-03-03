#include "functions.h"


void read_graph_from_file1(char *filename, int *N, char ***table2D)
{
	/* Function which opens a text file, allocates a 2D table of
	correct dimension and reads the web graph info into the table. */

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

  // read the first two lines.
  read = getline(&line, &len, datafile);
  read = getline(&line, &len, datafile);

  // read in the number of nodes and edges.
  int edges;
  fscanf(datafile, "# Nodes: %d Edges: %d\n", N, &edges);

  // read line four
  read = getline(&line, &len, datafile);

	// Allocate a 2D table, using the pointer table 2D.
	(*table2D) = (char**) malloc((*N) * sizeof(char*));
	for (int i = 0; i < (*N); i++)
	{
		(*table2D)[i] = (char*) malloc((*N) * sizeof(char));

    // fill this array with zeros
    for (int j = 0; j < (*N); j++)
    {
      (*table2D)[i][j] = 0;
    }
	}
  if ((*table2D) == NULL)
  {
    printf("Error in allocating memory.\n");
  }

  // read the rest of the values and add corresponding ones to the table2D array
  int val1, val2;
  while (fscanf(datafile, "%d\t%d\n", &val1, &val2) != EOF)
  {
    (*table2D)[val2][val1] = 1;
  }
	// finalize the function
	fclose(datafile);
} // read_graph_from_file1

void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx)
{
	/* Same purpose as the first function, except that the CRS format is used.
	In this function, you should avoid internally allocating/using a 2D table */

  // Open the file for reading
	FILE* datafile;
	datafile = fopen(filename, "r");
	if (datafile == NULL)
	{
		printf("Error in reading file %s.\n", filename);
		exit(1);
	}

	/* Can assume that the first two lines contain free text.
	Line 3 has the number of nodes and edges in the form:
		# Nodes:	int1 Edges: 	int2
	These need to be extracted. Line 4 doesn't need extraction. */
  char* line = NULL;
  size_t len = 0;
  ssize_t read;

  // read the first two lines.
  read = getline(&line, &len, datafile);
  read = getline(&line, &len, datafile);

  // read in the number of nodes and edges.
  int edges;
  fscanf(datafile, "# Nodes: %d Edges: %d\n", N, &edges);

  // Can now allocate the memory for the row_ptr and col_idx arrays.
  (*row_ptr) = (int*) malloc(((*N) + 1) * sizeof(int));
  (*col_idx) = (int*) malloc(edges * sizeof(int));

	if ((*row_ptr) == NULL || (*col_idx) == NULL)
	{
		printf("Error in allocating memory.\n");
		exit(1);
	}

  // read line four
  read = getline(&line, &len, datafile);

  /* Extract the parameters from the rest of the file,
  and use them to build the row_ptr and col_idx arrays. */
  int val1, val2, temp, ctr = 0;
  int* FromID;
  int* ToID;
  FromID = (int*) malloc(edges * sizeof(int));
  ToID = (int*) malloc(edges * sizeof(int));

  while (fscanf(datafile, "%d\t%d\n", &val1, &val2) != EOF)
  {
		/* count how many occurrences of each ToID value there are,
		following the convention of row_ptr[0]=0 */
		(*row_ptr)[val2+1]++;

		FromID[ctr] = val1;
    ToID[ctr] = val2;
    ctr++;
  }

	// Format this vector using convention (gradual addition)
	(*row_ptr)[0] = 0;
	for (int i = 1; i < ((*N)+1); i++)
	{
		(*row_ptr)[i] += (*row_ptr)[i-1];
	}

  /* Apply a sorting algorithm to the FromID and ToID
	arrays (according to the ToID values) to produce col_idx */
  ctr = 0;
  while (ctr < (edges-1))
  {
    if (ToID[ctr] > ToID[ctr + 1])
    {
			// If a value is found to be unsorted, swap it with its neighbor
      temp = ToID[ctr];
      ToID[ctr] = ToID[ctr + 1];
      ToID[ctr + 1] = temp;

      temp = FromID[ctr];
      FromID[ctr] = FromID[ctr + 1];
      FromID[ctr + 1] = temp;

      ctr = 0;  // start from the beginning each time we sort
    } else {
      ctr++;
    }
  }

	// copy this sorted vector into the col_idx array and finalize
	memcpy((*col_idx), FromID, edges * sizeof(int));
	free(FromID);
	free(ToID);
	fclose(datafile);
} // read_graph_from_file2

int count_mutual_links1(int N, char **table2D, int *num_involvements)
{
	/* Function to count the total number of mutual webpage linkage occurrences,
	as well as the number of involvements per webpage as outbound for such
	mutual linkage occurrences.*/

	// Mutual webpage linkages to '4' is a measurement of how many times 4 shows up in the ToID table.

	/* Should return the total number of mutual webpage linkage occurences.
	In addition, the array num_involvements is assumed to already be allocated
	and of length N. Should contain the number of involvements per webpage
	when the functions are complete. */
} // count_mutual_links1

int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx,int *num_involvements)
{

} // count_mutual_links2
