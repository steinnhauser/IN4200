#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "test_functions.h"
// #include "functions.h"

int main(int argc, char *argv[])
{
	srand(time(0));
	clock_t starttime = clock();
	printf("Running file %s\n", argv[0]);

	// Assert all the input arguments and parse them.
	int option, tbool = 0;
	while((option = getopt(argc, argv, "t")) != -1)
	{
		switch(option)
		{
			case 't':
				tbool = 1;
		}
	}

	// Test all the modules to assert whether or not they are in order.
	if (tbool) {
		printf("Testing...\n");
		_test_read_graph_from_file1();
		_test_read_graph_from_file2();
		printf("Function test complete.\n");
	}

	/* Read a web graph from file */
	// int N;
	// char **table2D;
	// read_graph_from_file1(argv[1], &N, &table2D);

	double endtime = ((double)(clock() - starttime))/CLOCKS_PER_SEC;
	printf("Completed after %.3f seconds.\n", endtime);
	return 0;
}
