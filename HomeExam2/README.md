Compile the serial program using the following command:

```
gcc serial_main.c -o test.x -fopenmp -O3
```

followed by:

```
./test.x
```

This will use the serial program applied to the matrix in the exercise text.

To compile the parallel program, run the command:

```
gcc mpi_main.c -o test.x -fopenmp -O3
```

followed by:

```
./test.x
```
