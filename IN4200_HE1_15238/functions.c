#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void fun1c(int argc, char *argv[], int *tbool, int *pbool)
{
    int option; 
    while((option = getopt(argc, argv, "tp")) != -1)
	{
		switch(option)
		{
			case 't':
				(*tbool) = 1;
				break;
			case 'p':
				(*pbool) = 1;
				break;
			default:
        fprintf(stderr, "Usage: %s [-t] for testing, [-p] for parallelization\n", argv[0]);
        exit(EXIT_FAILURE);
		}
	}
}