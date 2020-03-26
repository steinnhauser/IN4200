The code should be compiled as:

```
$ gcc main.c -o test.x -O3 -fopenmp
```

And subsequently executed as:

```
$ ./test.x
```

If parallelisation, or tests are preferred, you can add flags to the executable:

```
$ ./test.x [-t] [-p]
```