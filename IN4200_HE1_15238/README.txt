The code should be compiled as:

$ gcc main.c -o test.x -O3 -fopenmp

And subsequently executed as:

$ ./test.x -d

This uses the default data path "data/web-NotreDame.txt". 

If another data path is desired, you can input it in the command line as:

$ ./test.x YourPath

If parallelisation, or tests are preferred, you can add flags to the executable:

$ ./test.x [-t] [-p]

These can be combined in several ways. 

The testing flag tests both parallel and serial implementations.