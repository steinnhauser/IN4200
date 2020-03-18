#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "functions.c"
#include "read_graph_from_file1.c"
#include "read_graph_from_file2.c"
#include "count_mutual_links1.c"
#include "testing_functions.c"

int main(int argc, char *argv[])
{
	srand(time(0));
	clock_t starttime = clock();
	printf("Running file %s\n", argv[0]);
    
    // Assert all the input arguments and parse them.
	int total_links, tbool = 0, pbool = 0;
	arg_parser(argc, argv, &tbool, &pbool);
	
	if (!tbool)
	{
		/* Perform the count_mutual_links functions. Reading in the 
		web-NotreDame.txt data into a 2D array causes memory errors. 
		The col_idx and row_ptr arrays will only be extracted. */
	}
	else {
		printf("Testing the count_mutual_links functions...\n");
		test_Exercise2();
	}

	double endtime = ((double)(clock() - starttime))/CLOCKS_PER_SEC;
	printf("Completed after %.3f seconds.\n", endtime);
	return 0;
}