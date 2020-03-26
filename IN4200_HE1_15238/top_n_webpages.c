void top_n_webpages(int num_webpages, int *num_involvements, int n)
{
	/* Function which finds the top n webpages with respect to the number of
	involvements in mutual linkages, and prints these out with their
	respective numbers of involvements. */

	if (n > num_webpages)
	{
		printf("Usage error: Maximum number of webpages to rank is %d, input %d not understood.\n", num_webpages, n);
		n = num_webpages;
	}
	else if (n < 0)
	{
		printf("Usage error in top_n_webpages:\n");
		printf("Negative integer input %d not understood.\n", n);
		printf("Showing top 4 webpages instead.\n");
		n = 4;
	}

	int *val_list, *idx_list;
	val_list = (int*) malloc(n * sizeof(int));
	idx_list = (int*) malloc(n * sizeof(int));

	int maxval, maxidx;
	// Loop through the array n times, to find the maximum value of each iteration.
	for (int i = 0; i < n; i++)
	{
		maxval = -1, maxidx = -1;
		for (int j = 0; j < num_webpages; j++)
		{
			if (num_involvements[j] > maxval)
			{
				maxval = num_involvements[j];
				maxidx = j;
			}
		}
		val_list[i] = maxval;
		idx_list[i] = maxidx;

		/* Need to remove this value from the num_involvements array so 
		it doesn't get reconglized on subsequent iterations. Could avoid 
		damaging the array by memcpy, but don't seem to need it later. */
		num_involvements[maxidx] = -1;
	}

	// Illustrate the winners.
	printf("-----------------\n");
	printf("Top %d webpages:\n", n);
	for (int i = 0; i < n; i++)
	{
		printf("%d. \t Webpage no. %d\twith %d linkage(s).\n", (i+1), idx_list[i], val_list[i]);
	}
	printf("-----------------\n");

	// Finalize.
	free(val_list);
	free(idx_list);
} // top_n_webpages