void top_n_webpages(int *num_involvements, int n)
{
	/* Function which finds the top n webpages with respect to the number of
	involvements in mutual linkages, and prints these out with their
	respective numbers of involvements. */
	char* list;
	list = (char*) malloc(n * sizeof(char));
	
	// Index to save where the maximal value is
	int ctr = 0, val = 0, idx = 0;
	
	// Loop through and extract the top n maximum values of the num_involvements list.
	// while (num_involvements[ctr] != EOF)
	// {
	// 	...
	// 	ctr++;
	// }
} // top_n_webpages