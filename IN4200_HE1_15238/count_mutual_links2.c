int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements)
{
	/* Function to count up and return the amount of total mutual linkages.
    The number of linkages for each node are also saved in the num_involvements
    array, which is assumed to already be allocated. */

	int total_links = 0;

	for (int i = 0; i < N; i++)
	{
		if ((row_ptr[i+1] - row_ptr[i]) > 1)
		{
            /* If more than one element is in the current row, then add the 
            amount of mutual linkages found to all columns involved. */
			for (int j = row_ptr[i]; j < row_ptr[i+1]; j++)
			{
				num_involvements[col_idx[j]] += (row_ptr[i+1] - row_ptr[i]) - 1;
				total_links += (row_ptr[i+1] - row_ptr[i]) - 1;
			}
		}
	}

	/* Must once again account for double counting the 
    linkages (i.e. count both i->j and j->i). */
	total_links /= 2;

	return total_links;
} // count_mutual_links2