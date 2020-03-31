void top_n_webpages_OpenMP(int num_webpages, int *num_involvements, int n)
{
	/* A function to parallelize the process of finding the top_n_webpages
    of the num_involvements array. */

	if (n > num_webpages)
	{
		printf("Usage error: Maximum number of webpages to rank is %d. Displaying top %d webpages instead.\n", num_webpages, num_webpages);
		n = num_webpages;
	}
	else if (n < 0)
	{
		printf("Usage error in top_n_webpages_OpenMP:\n");
		printf("Negative integer input %d not understood.\n", n);
		printf("Showing top 4 webpages instead.\n");
		n = 4;
	}

	int threads = omp_get_max_threads();	// number of nodes to parallelize.

	threads = 1;

	int frac = num_webpages/threads;		// the fraction of the array each node will analyze.
	int remainder = num_webpages % threads;	// the remaining values which must also be accounted for.

	/* Have each node pick out a top_n_webpages list, and 
    compare them all using a single node to summarize. */
	int *val_list, *idx_list;
	val_list = (int*) malloc(threads * n * sizeof(int));
	idx_list = (int*) malloc(threads * n * sizeof(int));

	int maxval, maxidx, mythread;
	// Loop through the array n times, to find the maximum value of each iteration.
    #pragma omp parallel num_threads(threads)
	{
		mythread = omp_get_thread_num();
		for (int i = 0; i < n; i++)
		{
			maxval = -1, maxidx = -1;

			for (int j = mythread*frac; j < (mythread + 1) * frac; j++)
			{
				if (num_involvements[j] > maxval)
				{
					maxval = num_involvements[j];
					maxidx = j;
				}
			}
			val_list[i + mythread*n] = maxval;
			idx_list[i + mythread*n] = maxidx;

			/* Need to remove this value from the num_involvements array so 
			it doesn't get reconglized on subsequent iterations. Could avoid 
			damaging the array using memcpy, but don't seem to need it later. */
			num_involvements[maxidx] = num_involvements[maxidx] * (-1);
		}
	}
	

	// Go through each node's top n findings, as well as the remainders
	int dmyidx, restsbool = 0;
	int *winner_val_list, *winner_idx_list;
	winner_val_list = (int*) malloc(n * sizeof(int));
	winner_idx_list = (int*) malloc(n * sizeof(int));

	for (int i = 0; i < n; i++)
	{
		restsbool = 0, maxval = -1, maxidx = -1;
		for (int j = 0; j < (threads * n); j++)
		{
			if (val_list[j] > maxval)
			{
				maxval = val_list[j];
				maxidx = idx_list[j];
				dmyidx = j;
			}
		}

		// Go through the remaining values of the num_involvements array as well
		for (int k = (threads * frac); k < num_webpages; k++)
		{
			if (num_involvements[k] > maxval)
			{
				maxval = num_involvements[k];
				maxidx = k;
				restsbool = 1;
			}
		}

		winner_val_list[i] = maxval;
        winner_idx_list[i] = maxidx;

		// Need to check where the current max value occurred, and remove it for the next iteration.
		if (restsbool){
			num_involvements[maxidx] = -1;
		}
		else {
			val_list[dmyidx] = -1;
		}
	}

	// Illustrate the winners.
	printf("-----------------\n");
	printf("Top %d webpages:\n", n);
	for (int i = 0; i < n; i++)
	{
		printf("%d. \t Webpage no. %d\twith %d linkage(s).\n", (i+1), winner_idx_list[i], winner_val_list[i]);
	}
	printf("-----------------\n");

	// Finalize.
	free(val_list);
	free(idx_list);
	free(winner_val_list);
	free(winner_idx_list);
} // top_n_webpages