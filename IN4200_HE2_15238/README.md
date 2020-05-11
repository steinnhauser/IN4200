Compile the serial program using the following command:

```
gcc serial_main.c -o test.x -fopenmp -O3
```

followed by:

```
./test.x
```

To compile the parallel program, run the command:

```
mpicc -O3 -Wall -std=c11 mpi_main.c
```

followed by:

```
mpiexec -np 4 ./a.out
```


This will use the serial program applied to the matrix in the exercise text. Custom matrix configurations can also be produced in the functions.c file. There are a few example matrices there which require specific row M and column N values. Care to have the right M, N combination depending on the get_mtx function which is used.
