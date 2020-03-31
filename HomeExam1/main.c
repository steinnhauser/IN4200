#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <omp.h>
#include "test_functions.h"
#include "functions.h"

int main(int argc, char *argv[])
{
	srand(time(0));
	clock_t starttime = clock();
	printf("Running file %s\n", argv[0]);

	// Assert all the input arguments and parse them.
	int total_links, option, tbool = 0, pbool = 0;
	while((option = getopt(argc, argv, "tp")) != -1)
	{
		switch(option)
		{
			case 't':
				tbool = 1;
				break;
			case 'p':
				pbool = 1;
				break;
			default:
        fprintf (stderr, "Usage: %s [-t] for testing, [-p] for parallelization\n", argv[0]);
        exit (EXIT_FAILURE);
		}
	}

	// Test all the modules to assert whether or not they are working properly.
	// 3.5
	if (tbool) {
		printf("Testing...\n");

		// 3.1
		_test_read_graph_from_file1();
		_test_read_graph_from_file2();

		// 3.2
		_test_count_mutual_links1();
		_test_count_mutual_links2();

		// 3.4
		_test_top_n_webpages(); 	// incomplete.

		if (pbool){
			printf("Parallelizing...\n");

			// 3.3
			_test_OMP_count_mutual_links1();
			_test_OMP_count_mutual_links2();

			// 3.4
			_test_OMP_top_n_webpages(); 	// incomplete.
		}

		printf("Function test complete.\n");
	} else {
		if (pbool)
		{
			printf("Parallelizing main program\n");
			// Run the main calculations without parallelization
			/* Read a web graph from file */
			int N, N_links, total_links;
			char *filename;
			filename = "data/web-NotreDame.txt";
			int *row_ptr;
			int *col_idx;
			read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);

			int *num_involvements;
			num_involvements = (int*) malloc(N*sizeof(int));
			for (int i = 0; i < N; i++)
			{
				num_involvements[i] = 0;
			}
			total_links = OMP_count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
			printf("Total links of %s: %d\n", filename, total_links);
		} 
		else {
			// Run the main calculations without parallelization
			/* Read a web graph from file */
			int N, N_links, total_links;
			char *filename;
			filename = "data/web-NotreDame.txt";
			int *row_ptr;
			int *col_idx;
			read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);

			int *num_involvements;
			num_involvements = (int*) malloc(N*sizeof(int));
			for (int i = 0; i < N; i++)
			{
				num_involvements[i] = 0;
			}
			total_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
			printf("Total links of %s: %d\n", filename, total_links);
		}
	}

	double endtime = ((double)(clock() - starttime))/CLOCKS_PER_SEC;
	printf("Completed after %.3f seconds.\n", endtime);
	return 0;
}
