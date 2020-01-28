#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>


void compare_ASCII();
void compare_memcpy();
void exercise3();

int main(int argc, char *argv[])
{
  printf("----------\n");
  /* Exercise 1 */
  printf("Exercise 1\n");
  compare_ASCII();
  printf("----------\n");

  /* Exercise 2 */
  printf("Exercise 2\n");
  compare_memcpy();
  printf("----------\n");

  /* Exercise 3 */
  printf("Exercise 3\n");
  exercise3();
  printf("----------\n");
  return 0;
}

void compare_ASCII()
{
  /* Set up two reading/writing data files systems, one where the data is stored
  in binary format and another where it is stored using ASCII characters. Time
  both of these and compare them. */

  /* Generate large string of number values to be stored either binarily or
  using ASCII characters. */
  int n = 100000, *vec = NULL;
  vec = (int*) malloc(n * sizeof(int));

  if (vec == NULL) {
    printf("Error. Memory could not be allocated.\n");
    exit(0);
  }

  for (int i = 0; i < n; i++)
  {
    // Fill the vector with all the squares
    vec[i] = i * i;
  }

  // time the performance of the binary writing and reading functions
  clock_t starttime_bin = clock();

  // save the vector in a binary fashion first
  FILE* outfile_bin = fopen("data/data_bin.bin", "wb");
  if(outfile_bin == NULL)
  {
     printf("Error in opening file.");
     exit(1);
  }

  // writing the array to a binary file:
  fwrite(vec, sizeof(int), n, outfile_bin);
  fclose(outfile_bin);

  // open and read the binary file
  FILE* infile_bin = fopen("data/data_bin.bin", "rb");
  if (infile_bin == NULL) {
    printf("Binary reading file not found error.\n");
    exit(1);
  }

  int *binvec;
  binvec = (int*) malloc(n * sizeof(int));
  fread(binvec, sizeof(int), n, infile_bin);
  if (binvec == NULL) {
    printf("Error reading binary file into array.\n");
    exit(1);
  }
  fclose(infile_bin);
  // final time of the binary read/write
  double time_bin = ((double)(clock() - starttime_bin))/CLOCKS_PER_SEC;

  // do the same using the text file format
  clock_t starttime_ascii = clock();

  FILE* outfile_ascii = fopen("data/data_ascii.txt", "w");
  if (outfile_ascii == NULL) {
    printf("File not found error.\n");
    exit(1);
  }

  // writing the array to a text file:
  for (int i = 0; i < n; i++) {
    if (((i + 1) % 10) == 0) {
      fprintf(outfile_ascii, "%d,\n", vec[i]);
    } else {
      fprintf(outfile_ascii, "%d, ", vec[i]);
    }
  }
  fclose(outfile_ascii);

  // now, read in the file written.
  FILE* infile_ascii = fopen("data/data_ascii.txt", "r");
  if (infile_ascii == NULL) {
    printf("Error reading ASCII file.\n");
    exit(1);
  }

  int fac0, fac1, fac2, fac3, fac4, fac5, fac6, fac7, fac8, fac9;
  int *asciivec;
  asciivec = (int*) malloc(n * sizeof(int));
  if (asciivec == NULL) {
    printf("Failed to allocate memory for asciivec\n");
    exit(1);
  }

  int i = 0;
  while (fscanf(infile_ascii, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\n",
  &fac0, &fac1, &fac2, &fac3, &fac4, &fac5, &fac6, &fac7, &fac8, &fac9) != EOF)
  {
    asciivec[i] = fac0; asciivec[i+1] = fac1; asciivec[i+2] = fac2;
    asciivec[i+3] = fac3; asciivec[i+4] = fac4; asciivec[i+5] = fac5;
    asciivec[i+6] = fac6; asciivec[i+7] = fac7; asciivec[i+8] = fac8;
    asciivec[i+9] = fac9;
    i += 10;
  }

  double time_ascii = ((double)(clock() - starttime_ascii))/CLOCKS_PER_SEC;

  printf("Binary storing took %f seconds.\nASCII storing took %f seconds.\n"
    "Difference of %f seconds.\n", time_bin, time_ascii, time_ascii-time_bin);

  printf("First three elements of each loaded array:\n");
  printf("Vec: \t%d, %d, %d\nBin: \t%d, %d, %d\nASCII: \t%d, %d, %d\n", vec[0],
  vec[1], vec[2], binvec[0], binvec[1], binvec[2], asciivec[0], asciivec[1],
  asciivec[2]);

  // verify that all the vectors still equal each other;
  for (int i = 0; i < n; i++)
  {
    if ((vec[i] != binvec[i]) || (vec[i] != asciivec[i]))
    {
      printf("Error found in element of one of the loaded arrays.\n");
      exit(1);
    }
  }

  // finally, free the memory of the arrays
  free(vec);
  free(binvec);
  free(asciivec);
}

void compare_memcpy()
{
  /* Time two operations, one hard coded and one using the memcpy function, and
  study which one of them performes faster. */

  // create some array a which we would like to copy into array b.
  int n = 10000;
  int* a = (int*) malloc(n * sizeof(int));
  int* b = (int*) malloc(n * sizeof(int));
  if (a == NULL || b == NULL) {
    printf("Allocation of memory for arrays a or b was unsuccessful.\n");
    exit(1);
  }

  // fill a with the Fibonnacci sequence
  a[0] = 0; a[1] = 0;
  for (int i = 2; i < n; i++) {
    a[i] = a[i-1] + a[i-2];
  }

  // copy this sequence into the b array
  clock_t starttime_hardcode = clock();
  for (int i = 0; i < n; i++)
  {
    b[i] = a[i];
  }
  double time_hc = (double) (clock() - starttime_hardcode) / CLOCKS_PER_SEC;

  clock_t starttime_memcpy = clock();
  // memcpy function
  memcpy(b, a, n * sizeof(int));
  double time_mcpy = (double) (clock() - starttime_memcpy) / CLOCKS_PER_SEC;

  printf("Hard coding took %f seconds.\nMemcpy function took %f seconds.\n"
    "Difference of %f seconds.\n", time_hc, time_mcpy, time_hc-time_mcpy);
}

void exercise3(){
  // allocate two 3D arrays v and u, both of dimension nx x ny x nz.
  int nx = 4, ny = 4, nz = 4;
  double*** v;
  double*** u;
  v = (double***) malloc(nx * sizeof(double**));
  u = (double***) malloc(nx * sizeof(double**));
  for (int i = 0; i < nx; i++) {
    v[i] = (double**) malloc(ny * sizeof(double*));
    u[i] = (double**) malloc(ny * sizeof(double*));
    for (int j = 0; j < ny; j++) {
      v[i][j] = (double*) malloc(nz * sizeof(double));
      u[i][j] = (double*) malloc(nz * sizeof(double));
    }
  }

  if (v[0][0] == NULL || u[0][0] == NULL) {
    printf("Error in allocating memory for either tensor v or u.\n");
    exit(1);
  }

  // initialize the elements of the v array using a formula
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        v[i][j][k] = 2.0 + sin((double) (i*j*k*M_PI) / ((nx-1)*(ny-1)*(nz-1)));
      }
    }
  }

  // initialize all elements of the u array as zeros
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        u[i][j][k] = 0;
      }
    }
  }

  // carry out a computation for 100 iterations for
  // i = 1 -> nx-2
  // j = 1 -> ny-2
  // k = 1 -> nz-2
  for (int i = 1; i < nx-1; i++) {
    for (int j = 1; j < ny-1; j++) {
      for (int k = 1; k < nz-1; k++) {
        u[i][j][k] =    v[i][j][k] + (double) (v[i-1][j][k]+v[i][j-1][k]
                      + v[i][j][k-1]-6.0*v[i][j][k]+v[i+1][j][k]
                      + v[i][j+1][k]+v[i][j][k+1])/6.0;
      }
    }
  }

  // finally, deallocate the two 3D arrays of v and u.
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      free(v[i][j]);
      free(u[i][j]);
    }
  }

  for (int i = 0; i < nx; i++) {
    free(v[i]);
    free(u[i]);
  }

  free(v);
  free(u);

  printf("Memory successfully deallocated.\n");
}
