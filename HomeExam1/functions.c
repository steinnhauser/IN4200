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
  fscanf(datafile, "# Nodes: %d Edges: %d\n", N, N_links);

  // Can now allocate the memory for the row_ptr and col_idx arrays.
  (*row_ptr) = (int*) malloc(((*N) + 1) * sizeof(int));
  (*col_idx) = (int*) malloc((*N_links) * sizeof(int));

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
  FromID = (int*) malloc((*N_links) * sizeof(int));
  ToID = (int*) malloc((*N_links) * sizeof(int));

	// fill the row_ptr array with zeros to prepare for counting.
	for (int i = 0; i < ((*N)+1); i++)
	{
		(*row_ptr)[i] = 0;
	}

	// scan through the rest of the file.
  while (fscanf(datafile, "%d\t%d\n", &val1, &val2) != EOF)
  {
		/* count how many occurrences of each ToID value there are,
		following the convention of row_ptr[0]=0 */
		(*row_ptr)[val2+1]++;

		FromID[ctr] = val1;
    ToID[ctr] = val2;
    ctr++;
		if ((ctr % 100) == 0) {
			printf("\rCounter: %d out of %d", ctr, (*N_links));
			fflush(stdout);
		}
  }
	printf("\n");
	printf("Done\n");

	// Format this vector using convention (gradual addition)
	(*row_ptr)[0] = 0;
	for (int i = 1; i < ((*N)+1); i++)
	{
		(*row_ptr)[i] += (*row_ptr)[i-1];
	}

  /* Apply a sorting algorithm to the FromID and ToID
	arrays (according to the ToID values) to produce col_idx */
  ctr = 0;
  while (ctr < ((*N_links)-1))
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

      ctr--;  // start from the beginning each time we sort
    } else {
			ctr++;
			if ((ctr % 100) == 0) {
				printf("\rCounter: %d out of %d", ctr, (*N_links));
				fflush(stdout);
			}
    }
  }
	printf("\n");

	// copy this sorted vector into the col_idx array and finalize
	memcpy((*col_idx), FromID, (*N_links) * sizeof(int));
	free(FromID);
	free(ToID);
	fclose(datafile);
} // read_graph_from_file2

int count_mutual_links1(int N, char **table2D, int *num_involvements)
{
	/* Function to count the total number of mutual webpage linkage occurrences,
	as well as the number of involvements per webpage as outbound for such
	mutual linkage occurrences.*/

	/* Should return the total number of mutual webpage linkage occurences.
	In addition, the array num_involvements is assumed to already be allocated
	and of length N. Should contain the number of involvements per webpage
	when the functions are complete. */

	int j_links, total_links = 0;

	/* To do this, first loop through all the pages that 4 is linked to. For each
	of these, count how many other nodes are also linked to this one.

	Doing this using the 2D matrix involves moving to column 4, starting from the
	top and moving on down, and each time a 1 is encountered ('ToID links'), you
	count how many other 1's are in that row ('FromID links' to the node). */
	for (int j = 0; j < N; j++)
	{
		// j indicates the column. Move from left to right and top to bottom
		j_links = 0;
		for (int i = 0; i < N; i++)
		{
			// Check if any of these values equal 1.
			// If so, we want to count up 1's in that row.
			if (table2D[i][j] == 1)
			{
				// note in the num_involvements array that there is a value here.
				for (int rowind = 0; rowind < N; rowind++)
				{
					if (table2D[i][rowind] == 1)
					{
						j_links++;
					}
				}
				j_links--; // remove the link addition from column j.
			}
		}
		num_involvements[j] = j_links;
		total_links += j_links;
	}
	// account for double counting the linkages (i.e. count both i->j and j->i).
	total_links /= 2;
	return total_links;
} // count_mutual_links1

int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements)
{
	/* Count the mutual links using the row_ptr and col_idx array */
	int total_links = 0;

	// Know that row_ptr tells us how many elements are in each row.
	// Know also that col_idx tells us where each of these elements are.
	// Need to loop through each node (column), and assert how many more elements
	// there are in each of the rows which contain a '1' for that column.

	for (int i = 0; i < N; i++)
	{
		if ((row_ptr[i+1] - row_ptr[i]) > 1)
		{
			// If there are more than one elements in the current row, count up the
			// mutual links for both columns where there is a linkage
			for (int j = row_ptr[i]; j < row_ptr[i+1]; j++)
			{
				num_involvements[col_idx[j]] += (row_ptr[i+1] - row_ptr[i]) - 1;
				total_links += (row_ptr[i+1] - row_ptr[i]) - 1;
			}
		}
	}

	// account for double counting the linkages (i.e. count both i->j and j->i).
	total_links /= 2;

	return total_links;
} // count_mutual_links2

int OMP_count_mutual_links1(int N, char **table2D, int *num_involvements)
{
	/* Function which accomplishes the same objective as the count_mutual_links1
	function, but using OpenMP (<omp.h> library) to parallelize the processes. */
	int j_links, total_links = 0;
	#pragma omp parallel for reduction(+:total_links, num_involvements[:N]) private(j_links)
	for (int j = 0; j < N; j++)
	{
		// j indicates the column. Move from left to right and top to bottom
		j_links = 0;
		for (int i = 0; i < N; i++)
		{
			// Check if any of these values equal 1.
			// If so, we want to count up 1's in that row.
			if (table2D[i][j] == 1)
			{
				// note in the num_involvements array that there is a value here.
				for (int rowind = 0; rowind < N; rowind++)
				{
					if (table2D[i][rowind] == 1)
					{
						j_links++;
					}
				}
				j_links--; // remove the link addition from column j.
			}
		}
		num_involvements[j] = j_links;
		total_links += j_links;
	}
	// account for double counting the linkages (i.e. count both i->j and j->i).
	total_links /= 2;
	return total_links;
} // OMP_count_mutual_links1

int OMP_count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx,int *num_involvements)
{
	/* Function which accomplishes the same objective as the count_mutual_links2
	function, but using OpenMP (<omp.h> library) to parallelize the processes. */
	int total_links = 0;
	#pragma omp parallel for reduction(+:total_links, num_involvements[:N])
	for (int i = 0; i < N; i++)
	{
		if ((row_ptr[i+1] - row_ptr[i]) > 1)
		{
			// If there are more than one elements in the current row, count up the
			// mutual links for both columns where there is a linkage
			for (int j = row_ptr[i]; j < row_ptr[i+1]; j++)
			{
				num_involvements[col_idx[j]] += (row_ptr[i+1] - row_ptr[i]) - 1;
				total_links += (row_ptr[i+1] - row_ptr[i]) - 1;
			}
		}
	}

	// account for double counting the linkages (i.e. count both i->j and j->i).
	total_links /= 2;

	return total_links;
} // OMP_count_mutual_links2

void top_n_webpages(int *num_involvements, int n)
{
	/* Function which finds the top n webpages with respect to the number of
	involvements in mutual linkages, and prints these out with their
	respective numbers of involvements. */

}	// top_n_webpages

void OMP_top_n_webpages(int *num_involvements, int n)
{

} // OMP_top_n_webpages
