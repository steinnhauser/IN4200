void top_n_webpages(int num_webpages, int *num_involvements, int n)
{
	/* Function which finds the top n webpages with respect to the number of
	involvements in mutual linkages, and prints these out with their
	respective numbers of involvements. */
	int *val_list, *idx_list;
	val_list = (int*) malloc(n * sizeof(int));
	idx_list = (int*) malloc(n * sizeof(int));
	
	int ctr, val;

	
	// Loop through and extract the top n maximum values of the num_involvements list.
	for (ctr = 0; ctr < num_webpages; ctr++)
	{
		if (ctr < n)
		{
			// Simply fill the list up with the first few pages.
			val_list[ctr] = num_involvements[ctr];
			idx_list[ctr] = ctr;
		}
		else {
			// If the list is filled, we need to start cross checking values.
			val = num_involvements[ctr];
			for (int i = 0; i < n; i++)
			{
				// If this value is larger than any of the others, replace it.
				if (val > val_list[i])
				{
					val_list[i] = val;
					idx_list[i] = ctr;
					break;
				}
			}
		}
	}

	// Illustrate the winners.
	printf("-----------------\n");
	printf("Top n webpages:\n");
	for (int i = (n-1); i >= 0; i--)
	{
		printf("%d. \t Webpage no. %d with %d linkages.\n", (-i+n), idx_list[i], val_list[i]);
	}
	printf("-----------------\n");
} // top_n_webpages