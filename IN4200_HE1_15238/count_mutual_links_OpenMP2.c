int count_mutual_links_OpenMP2(int N, int N_links, int *row_ptr, int *col_idx,int *num_involvements)
{
	/* Function which accomplishes the same objective as the count_mutual_links2
	function, but using OpenMP (<omp.h> library) to parallelize the processes. */
	int add, total_links = 0;
	#pragma omp parallel for reduction(+:total_links, num_involvements[:N])
	for (int i = 0; i < N; i++)
	{
		if ((row_ptr[i+1] - row_ptr[i]) > 1)
		{
			/* If there are more than one elements in the current row, count 
			the mutual links for both columns where there is a linkage */
			for (int j = row_ptr[i]; j < row_ptr[i+1]; j++)
			{
				add = (row_ptr[i+1] - row_ptr[i]) - 1;
				num_involvements[col_idx[j]] += add;
				total_links += add;
			}
		}
	}

	// account for double counting the linkages (i.e. count both i->j and j->i).
	total_links /= 2;

	return total_links;
} // OMP_count_mutual_links2