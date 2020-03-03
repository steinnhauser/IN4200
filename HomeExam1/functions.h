#ifndef TEST_FUNCTIONS_C
#define TEST_FUNCTIONS_C

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void read_graph_from_file1(char *filename, int *N, char ***table2D);
void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx);

int count_mutual_links1(int N, char **table2D, int *num_involvements);
int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx,int *num_involvements);

#endif  // TEST_FUNCTIONS_C
