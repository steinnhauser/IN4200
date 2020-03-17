#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "functions.c"

int main(int argc, char *argv[])
{
	srand(time(0));
	clock_t starttime = clock();
	printf("Running file %s\n", argv[0]);
    
    // Assert all the input arguments and parse them.
	int total_links, tbool = 0, pbool = 0;
	fun1c(argc, argv, &tbool, &pbool);
    printf("Done\n");   
}