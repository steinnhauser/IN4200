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
  printf("Test read_graph_from_file1 passed with %d errors.\n", errno);
}

void _test_read_graph_from_file2()
{
  /* Function to test the module read_graph_from_file1
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

  // Assert the similarities between the two matrices:
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
  printf("Test read_graph_from_file2 passed with %d errors.\n", errno);
}

int _test_count_mutual_links1(int N, char **table2D, int *num_involvements)
{
	/* Function to count the total number of mutual webpage linkage occurrences,
	as well as the number of involvements per webpage as outbound for such
	mutual linkage occurrences.*/

	// Mutual webpage linkages to '4' is a measurement of how many times 4 shows up in the ToID table.
  count_mutual_links1(int N, char **table2D, int *num_involvements);
	/* Should return the total number of mutual webpage linkage occurences.
	In addition, the array num_involvements is assumed to already be allocated
	and of length N. Should contain the number of involvements per webpage
	when the functions are complete. */
} // _test_count_mutual_links1

int _test_count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx,int *num_involvements)
{
  /**/
  int i = 0;
  count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx,int *num_involvements);
} // _test_count_mutual_links2
