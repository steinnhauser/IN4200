#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void verify_limit(int n);
void random_vector(int n);
void two_dim_malloc();
void three_dim_malloc();
void read_in_temps();

int main(int argc, char *argv[]) {
  srand(time(0));
  printf("Running file %s\n", argv[0]);
  printf("-------------\n");
  /* Exercise 1 */
  printf("Exercise 1\n");
  int n1=30; // the computational equivalent of infinity
  verify_limit(n1);
  printf("-------------\n");

  /* Exercise 2 */
  printf("Exercise 2\n");
  /* Allocate a 1d array of length n and assign it random numbers.
  Subsequently find the maximum and minimum values. */
  int n2 = 10;
  random_vector(n2);
  printf("-------------\n");

  /* Exercise 3 */
  printf("Exercise 3\n");
  /* Assign values to the entries of a m x n matrix using a nested for loop.
  Verify that swapping the sequence of the two loops doesnt have an impact. */
  two_dim_malloc();
  printf("-------------\n");

  /* Exercise 4 */
  printf("Exercise 4\n");
  /* Allocate 3d array of size nx x ny x nz, assign values to each array in the
  fashion u[i][j][k]=i*n y*n z+j*n z+k. Deallocate the memory at the end */
  three_dim_malloc();
  printf("-------------\n");

  /* Exercise 5 */
  printf("Exercise 5\n");
  /*
    Read in a temperatures from the temps.txt file in the format
      00:05 -0.1
      00:21 0.1
      00:29 -0.2
    and finds the highest and lowest temperatures and when they occurred.
    Compute also the average temperature and the associated standard deviation.
  */
  read_in_temps();
  printf("-------------\n");

  return 0;
}


void verify_limit(int n)
{
  float tol = 0.0001, sum = 0, exp = 0.8;
  int sgn = 1;

  for (int i=0; i<n; i++)
  {
    // sum up the limit for n
    sum += sgn / pow(2, 2*i); // utilize the pow function from math.h
    sgn *= -1;
  }

  if (sum - exp < tol) {
    printf("The limit is within the tolerance %f using n= %d \n", tol, n);
    printf("Results were sum = %f, exp = %f, diff = %f \n", sum, exp, sum-exp);
  } else {
    printf("The limit was not within the tolerance for n=%d \n", n);
    printf("Results were sum = %f, exp = %f, diff = %f \n", sum, exp, sum-exp);
  }
}

void random_vector(int n)
{
  int *vec = NULL;
  vec = (int*) malloc(n * sizeof(int)); // allocate n integer instances
  for (int i = 0; i<n; i++)
  {
    vec[i] = rand() % 100; // random value between 0 and 99.
  }
  /* Find the maximum and minimum values of the vector ptr */
  int min = 99, max=0;
  for (int i = 0; i < n; i++)
  {
    if (vec[i] < min) min = vec[i];
    else if (vec[i] > max) max = vec[i];
  }
  printf("Minimum of vector is %d, and maximum is %d\n", min, max);
}

void two_dim_malloc()
{
  int **mtx1 = NULL, **mtx2 = NULL, m = 5, n = 3;
  // allocate two m x n integer instances
  mtx1 = (int**) malloc(m * sizeof(int *));
  mtx2 = (int**) malloc(m * sizeof(int *));
  for (int i = 0; i<m; i++)
  {
    mtx1[i] = (int*) malloc(n * sizeof(int));
    mtx2[i] = (int*) malloc(n * sizeof(int));
  }

  // assign values to the entries using two nested for-loop schemes:
  // case 1:
  int count = 0;
  for (int i = 0; i<m; i++)
  {
    for (int j = 0; j<n; j++)
    {
      mtx1[i][j] = i*j + i;
    }
  }

  // case 2:
  count = 0;
  for (int j = 0; j<n; j++)
  {
    for (int i = 0; i<m; i++)
    {
      mtx2[i][j] = i*j + i;
    }
  }

  // Assert that the two matrices are equal by printing them:
  printf("Matrix 1:\n");
  for (int i = 0; i<m; i++)
  {
    for (int j = 0; j<n; j++)
    {
      printf("%d, ", mtx1[i][j]);
    }
    printf("\n");
  }
  printf("Matrix 2:\n");
  for (int i = 0; i<m; i++)
  {
    for (int j = 0; j<n; j++)
    {
      printf("%d, ", mtx2[i][j]);
    }
    printf("\n");
  }
  // Element-wise check whether they are equal or not:
  int errors = 0;
  for (int i = 0; i<m; i++)
  {
    for (int j = 0; j<n; j++)
    {
      if (mtx1[i][j] != mtx2[i][j])
      {
        printf("Non-equal elements found:\n");
        printf("Index (%d, %d) yielded\nMatrix 1 = %d, Matrix 2 = %d\n", i, j, mtx1[i][j], mtx2[i][j]);
        errors++;
      }
    }
  }
  if (errors == 0) {printf("Nested for loop test was a success.\n");}
  else {printf("Nested for loop test raised %d errors.\n", errors);}
}

void three_dim_malloc()
{
  int ***tensor = NULL, nx = 2, ny = 3, nz = 4;

  // Allocate the tensor memory
  tensor = (int***) malloc(nx * sizeof(int**));
  for (int i = 0; i<nx; i++){
    tensor[i] = (int**) malloc(ny * sizeof(int*));
    for (int j = 0; j<ny; j++){
      tensor[i][j] = (int*) malloc(nz * sizeof(int));
    }
  }

  // assign values to all the points in the tensor.
  for (int i = 0; i<nx; i++){
    for (int j = 0; j<ny; j++){
      for (int k = 0; k<nz; k++){
        tensor[i][j][k] = i*ny*nz+j*nz+k;
      }
    }
  }
  printf("Three dimensional values assigned. Printing:\n");
  for (int i = 0; i<nx; i++){
    printf("\nSlice %d:\n", i);
    for (int j = 0; j<ny; j++){
      for (int k = 0; k<nz; k++){
        printf("%d, ", tensor[i][j][k]);
      }
      printf("\n");
    }
  }
  /* Free all the memory which was allocated for the tensor */
  // deallocate memory
	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < ny; j++)
    {
			free(tensor[i][j]);
    }
		free(tensor[i]);
	}
  free(tensor);
}

void read_in_temps()
{
  /*
    Read in a temperatures from the temps.txt file in the format
      00:05 -0.1
      00:21 0.1
      00:29 -0.2
    and finds the highest and lowest temperatures and when they occurred.
    Compute also the average temperature and the associated standard deviation.
  */
  FILE* temps;
  int hour, minute, maxtime, mintime, linecount = 0;
  float temp, maxtemp, mintemp, avetemp = 0, avetemp2 = 0;
  temps = fopen("temps.txt", "r");
  while (fscanf(temps, "%d:%d %f\n", &hour, &minute, &temp) != EOF)
  {
    avetemp += temp;
    avetemp2 += pow(temp, 2.0);
    if (linecount == 0) { // first iteration
      maxtemp = temp;
      mintemp = temp;
      maxtime = hour * 60 + minute;
      mintime = hour * 60 + minute;
    } else if (temp > maxtemp) {
      maxtemp = temp;
      maxtime = hour * 60 + minute; // units of minutes
    } else if (temp < mintemp) {
      mintemp = temp;
      mintime = hour * 60 + minute; // units of minutes
    }
    printf("%d\n", hour);
    printf("%d\n", minute);
    printf("%f\n", temp);

    linecount++;
  }
  avetemp /= linecount; // normalize
  avetemp2 /= linecount;
  float std = pow(avetemp2 - avetemp*avetemp, 0.5);
  printf("Maximum temperature was %f after %d minutes\n", maxtemp, maxtime);
  printf("Minimum temperature was %f after %d minutes\n", mintemp, mintime);
  printf("Average temperature was %f with std = %f\n", avetemp, std);
  fclose(temps);
}
