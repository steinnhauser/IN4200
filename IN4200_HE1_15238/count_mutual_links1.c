int count_mutual_links1(int N, char **table2D, int *num_involvements)
{
	/* Function to count and return the total number of mutual webpage linkage 
    occurrences, as well as the number of involvements per webpage as outbound 
    for such mutual linkage occurrences. The function assumes the memory of 
    num_involvements to have already been allocated and of length N. */

	int j_links, total_links = 0;

	for (int j = 0; j < N; j++)
	{
		j_links = 0;
		for (int i = 0; i < N; i++)
		{
			if (table2D[i][j] == 1)
			{
				// Search the row to find any mutual linkages
				for (int rowind = 0; rowind < N; rowind++)
				{
					if (table2D[i][rowind] == 1)
					{
						j_links++;
					}
				}
                // Avoid counting itself.
				j_links--;
			}
		}
        /* Save the amount of mutual linkages found for this column 
        in the num_involvements array and add to the total links found. */
		num_involvements[j] = j_links;
		total_links += j_links;
	}

	/* Finally, account for double counting the 
    linkages (i.e. count both i->j and j->i). */
	total_links /= 2;
    
	return total_links;
} // count_mutual_links1