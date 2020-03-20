#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

#include "functions.c"
#include "read_graph_from_file1.c"
#include "read_graph_from_file2.c"
#include "count_mutual_links1.c"
#include "count_mutual_links2.c"
#include "count_mutual_links_OpenMP1.c"
#include "count_mutual_links_OpenMP2.c"
#include "top_n_webpages.c"
#include "top_n_webpages_OpenMP.c"
#include "testing_functions.c"

int main(int argc, char *argv[])
{
	srand(time(0));
	clock_t starttime = clock();
	printf("Running file %s\n", argv[0]);
    
    // Assert all the input arguments and parse them.
	int tbool = 0, pbool = 0;
	arg_parser(argc, argv, &tbool, &pbool);
	
	if (!tbool)
	{
		/* Perform the analysis. Do this using CRS formatting
		and an optional parallelisation flag [-p] at execution. */
		char* filename = "data/web-NotreDame.txt";
		int N, N_links, total_links;
		int *row_ptr, *col_idx, *num_involvements;
		
		read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);

		num_involvements = (int*) malloc(N * sizeof(int));
		
		if (pbool)
		{
			// Use the OpenMP implementation of the count_mutual_links2 function.
			total_links = count_mutual_links_OpenMP2(N, N_links, row_ptr, col_idx, num_involvements);
			printf("Total links of file %s were found to be: %d\n", filename, total_links);

		}
		else {
			// Use the regular implementation.
			total_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
			printf("Total links of file %s were found to be: %d\n", filename, total_links);
			top_n_webpages(N, num_involvements, 8);
		}
	}
	else {
		printf("Testing the implementations...\n");
		printf("-------------------------------\n");
		test_Exercise1();
		test_Exercises_2_and_3();
		printf("-------------------------------\n");
	}

	double endtime = ((double)(clock() - starttime))/CLOCKS_PER_SEC;
	printf("Completed after %.3f seconds.\n", endtime);
	return 0;
}