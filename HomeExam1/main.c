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
	int option, tbool = 0, pbool = 0;
	while((option = getopt(argc, argv, "tp")) != -1)
	{
		switch(option)
		{
			case 't':
				tbool = 1;
			case 'p':
				pbool = 1;
		}
	}

	// Test all the modules to assert whether or not they are in order.
	if (tbool) {
		printf("Testing...\n");

		// 3.1
		_test_read_graph_from_file1();
		_test_read_graph_from_file2();

		// 3.2
		_test_count_mutual_links1();
		// _test_count_mutual_links2();	// incomplete.

		// 3.3
		if (pbool){
			printf("Parallelizing...\n");
			_test_OMP_count_mutual_links1();	// incomplete.
			_test_OMP_count_mutual_links2();	// incomplete.
		}
		printf("Function test complete.\n");
	}

	if (pbool)
	{
		// Running main calculations using the parallelized functions
		/* Read a web graph from file */
		// int N;
		// char **table2D;
		// read_graph_from_file1(argv[1], &N, &table2D);
		// OMP_count_mutual_links1();
	}	else {
		// Run the main calculations without parallelization
		/* Read a web graph from file */
		// int N;
		// char **table2D;
		// read_graph_from_file1(argv[1], &N, &table2D);
		// count_mutual_links1();
	}

	double endtime = ((double)(clock() - starttime))/CLOCKS_PER_SEC;
	printf("Completed after %.3f seconds.\n", endtime);
	return 0;
}



	// char *filename;
	// char **table2D;
	// int N;
	// filename = "data/100nodes_graph.txt";
	// read_graph_from_file1(filename, &N, &table2D);
	// printf("Done, N=%d\n", N);
	//
	// int N_links;
	// int *row_ptr;
	// int *col_idx;
	// read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);
	// printf("Done again.\n");
	//
	// for (int i = 0; i < (N+1); i++)
	// {
	// 	printf("%d\n", row_ptr[i]);
	// }
	// printf("------\n");
	// for (int i = 0; i < (N_links); i++)
	// {
	// 	printf("%d\n", col_idx[i]);
	// }
