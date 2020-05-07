int count_mutual_links_OpenMP1(int N, char **table2D, int *num_involvements)
{
	/* Function which accomplishes the same objective as the count_mutual_links1
	function, but using OpenMP (<omp.h> library) to parallelize the processes. */
	int total_links = 0;
	#pragma omp parallel for reduction(+:total_links, num_involvements[:N])
	for (int j = 0; j < N; j++)
	{
		int j_links = 0;
		for (int i = 0; i < N; i++)
		{
			if (table2D[i][j] == 1)
			{
                // Count up the amount of other links in this row.
				for (int rowind = 0; rowind < N; rowind++)
				{
					if (table2D[i][rowind] == 1)
					{
						j_links++;
					}
				}
                // Avoid counting itself
				j_links--;
			}
		}
        /* Save the amount of mutual linkages found for this column 
        in the num_involvements array and add to the total links found. */
		num_involvements[j] += j_links;
		total_links += j_links;
	}

	/* Finally, account for double counting the 
    linkages (i.e. count both i->j and j->i). */
	total_links /= 2;

	return total_links;
} // count_mutual_links_OpenMP1