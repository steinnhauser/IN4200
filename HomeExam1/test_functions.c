#include "test_functions.h"

void _test_read_graph_from_file1()
{
  /* Function to test the module read_graph_from_file1
  using the example given in the exercise paper. */

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

  // Read in the values using the function:
  char **table2D;
  char *filename;
  filename = "data/testingdata.txt";
  read_graph_from_file1(filename, &N, &table2D);

  // Assert the similarities between the two matrices:
  if (trueN != N)
  {
    printf("N was extracted incorrectly in function read_graph_from_file1\n");
    printf("True N is: %d, while extracted N is: %d\n", trueN, N);
    errno++;
  } else {
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
  printf("Test read_graph_from_file1 passed with \t %d errors.\n", errno);
}

void _test_read_graph_from_file2()
{
  /* Function to test the module read_graph_from_file2
  using the example given in the exercise paper. */

  // Know the true values to be:
  int trueN = 8, trueEdges = 17, errno = 0;

  // array to store the column index of the elements
  int trueCol_idx[17] = {
    6, 0, 2, 3, 0, 1, 2, 3, 6, 3, 4, 7, 4, 7, 4, 5, 6
  }; // length N links

  // array to store the locations of the values that start a row
  int trueRow_ptr[9] = {
    0, 1, 4, 5, 6, 9, 12, 14, 17
  }; // length N + 1

  // Read in the values using the function:
  char *filename;
  int N_links, N;
  int *row_ptr;
  int *col_idx;

  filename = "data/testingdata.txt";
  read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);

  // Assert the similarities between the two arrays:
  if (trueN != N)
  {
    printf("N was extracted incorrectly in function read_graph_from_file1\n");
    printf("True N is: %d, while extracted N is: %d\n", trueN, N);
    errno++;
  } else {
    for (int i = 0; i < trueN; i++)
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
  printf("Test read_graph_from_file2 passed with \t %d errors.\n", errno);
}

void _test_count_mutual_links1()
{
	/* Function to count the total number of mutual webpage linkage occurrences,
	as well as the number of involvements per webpage as outbound for such
	mutual linkage occurrences.*/

  /* Correct values for the table in Figure 1, listed by
  grouping together the {node, mutual_links} values */
  int errno = 0;
  int total_links;
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

  int N = 8;
  int *num_involvements;
  num_involvements = (int*) malloc(N * sizeof(int));
  int trueMtx[8][8] = {
    {0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 1, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 0},
    {0, 0, 0, 1, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 1, 1, 0},
  };
  int trueTotal_links = 13;

  char **table2D;
  table2D = (int**) malloc(N * sizeof(int*));
  for (int i = 0; i < N; i++)
  {
    table2D[i] = (int*) malloc(N * sizeof(int));
    for (int j = 0; j < N; j++)
    {
      table2D[i][j] = trueMtx[i][j];
    }
  }

  // Check that these links are equal.
  total_links = count_mutual_links1(N, table2D, num_involvements);

  // Check the total links value
  if (total_links != trueTotal_links)
  {
    errno++;
  }

  // Check the num_involvements values
  for (int i = 0; i < N; i++)
  {
    if (correctVals[i][1] != num_involvements[i])
    {
      errno++;
    }
  }

	/* Should return the total number of mutual webpage linkage occurences.
	In addition, the array num_involvements is assumed to already be allocated
	and of length N. Should contain the number of involvements per webpage
	when the functions are complete. */
  printf("Test count_mutual_links1 passed with \t %d errors.\n", errno);

  // Finalize
  free(num_involvements);
  for (int i = 0; i < N; i++)
  {
    free(table2D[i]);
  }
  free(table2D);
} // _test_count_mutual_links1

void _test_count_mutual_links2()
{
  // int N, int N_links, int *row_ptr, int *col_idx,int *num_involvements
  int errno = 0;
  int total_links;
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

  int N = 8;
  int *num_involvements;
  num_involvements = (int*) malloc(N * sizeof(int));
  for (int j = 0; j < N; j++)
	{
		num_involvements[j] = 0;
	}
  int trueMtx[8][8] = {
    {0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 1, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 0},
    {0, 0, 0, 1, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 1, 1, 0},
  };
  int trueTotal_links = 13;

  char *filename;
  int N_links;
  int *row_ptr;
  int *col_idx;

  filename = "data/testingdata.txt";
  read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);
  total_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);

  if (total_links != trueTotal_links)
  {
    errno++;
  }

  // Check the num_involvements values
  for (int i = 0; i < N; i++)
  {
    if (correctVals[i][1] != num_involvements[i])
    {
      errno++;
    }
  }

  printf("Test count_mutual_links2 passed with \t %d errors.\n", errno);
  // finalize
  free(row_ptr);
  free(col_idx);
  free(num_involvements);
} // _test_count_mutual_links2

void _test_OMP_count_mutual_links1()
{
  /* Function to test the function OMP_count_mutual_links1, which accomplishes
  the same as the count_mutual_links1 function, only parallelized. */
  int errno = 0;
  int total_links;
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

  int N = 8;
  int *num_involvements;
  num_involvements = (int*) malloc(N * sizeof(int));
  for (int i = 0; i < N; i++)
  {
    num_involvements[i] = 0;
  }
  int trueMtx[8][8] = {
    {0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 1, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 0},
    {0, 0, 0, 1, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 1, 1, 0},
  };
  int trueTotal_links = 13;

  char **table2D;
  table2D = (int**) malloc(N * sizeof(int*));
  for (int i = 0; i < N; i++)
  {
    table2D[i] = (int*) malloc(N * sizeof(int));
    for (int j = 0; j < N; j++)
    {
      table2D[i][j] = trueMtx[i][j];
    }
  }

  // Check that these links are equal.
  total_links = OMP_count_mutual_links1(N, table2D, num_involvements);

  // Check the total links value
  if (total_links != trueTotal_links)
  {
    errno++;
  }

  // Check the num_involvements values
  for (int i = 0; i < N; i++)
  {
    if (correctVals[i][1] != num_involvements[i])
    {
      errno++;
    }
  }

	/* Should return the total number of mutual webpage linkage occurences.
	In addition, the array num_involvements is assumed to already be allocated
	and of length N. Should contain the number of involvements per webpage
	when the functions are complete. */
  printf("Test OMP_count_mutual_links1 passed with %d errors.\n", errno);

  // Finalize
  free(num_involvements);
  for (int i = 0; i < N; i++)
  {
    free(table2D[i]);
  }
  free(table2D);
}
void _test_OMP_count_mutual_links2()
{
  /* Function to test the function OMP_count_mutual_links2, which accomplishes
  the same as the count_mutual_links2 function, only parallelized. */
  // int N, int N_links, int *row_ptr, int *col_idx,int *num_involvements
  int errno = 0;
  int total_links;
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

  int N = 8;
  int *num_involvements;
  num_involvements = (int*) malloc(N * sizeof(int));
  for (int j = 0; j < N; j++)
	{
		num_involvements[j] = 0;
	}
  int trueMtx[8][8] = {
    {0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 1, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 0},
    {0, 0, 0, 1, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 1, 1, 0},
  };
  int trueTotal_links = 13;

  char *filename;
  int N_links;
  int *row_ptr;
  int *col_idx;

  filename = "data/testingdata.txt";
  read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);
  total_links = OMP_count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);

  if (total_links != trueTotal_links)
  {
    errno++;
  }

  // Check the num_involvements values
  for (int i = 0; i < N; i++)
  {
    if (correctVals[i][1] != num_involvements[i])
    {
      errno++;
    }
  }

  printf("Test OMP_count_mutual_links2 passed with %d errors.\n", errno);
  // finalize
  free(row_ptr);
  free(col_idx);
  free(num_involvements);
}

void _test_top_n_webpages()
{
  int errno = 0;
  /* Function to test the function top_n_webpages */
  int N = 8;
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
  int *num_involvements;
  num_involvements = (int*) malloc(N * sizeof(int));
  for (int i = 0; i < N; i++)
  {
    num_involvements[i] = correctVals[i][1];
  }

  int n = 10;
  top_n_webpages(num_involvements, n);

  printf("Test top_n_webpages passed with \t %d errors.\n", errno);
}

void _test_OMP_top_n_webpages()
{
  /* Function to test the function OMP_top_n_webpages */
  int N = 8;
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
  int *num_involvements;
  num_involvements = (int*) malloc(N * sizeof(int));
  for (int i = 0; i < N; i++)
  {
    num_involvements[i] = correctVals[i][1];
  }

  int n = 4;
  OMP_top_n_webpages(num_involvements, n);
}
