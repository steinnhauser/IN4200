#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Example1_LoopOptimization();
void Example2_LoopFactoring();
void Example3_LookupTable();
void Example4_StrengthReduction();
void Example5_BranchAvoidance1();
void Example6_BranchAvoidance2();
void Example7_SIMDApplication();
void Example8_RiskOfAliasing()


int main(int argc, char *argv[])
{
  return 0;
}

void Example1_LoopOptimization()
{
  /* Nested for-loop optimization */

  // case:
  for (i=0; i<500; i++){
    for (j=0; j<80; j++){
      for (k=0; k<4; k++){
        a[i][j][k] = a[i][j][k] + b[i][j][k]*c[i][j][k];
      }
    }
  }

  /* How many of these loops are necessary? If the 3D arrays a, b, and c have
  CONTIGUOUS memory storage for all values, then we can perform the loop as: */
  double *a_ptr = a[0][0];
  double *b_ptr = b[0][0];
  double *c_ptr = c[0][0];

  for (i=0; i<(500*80*4); i++){
    a_ptr[i] = a_ptr[i] + b_ptr[i]*c_ptr[i];
  }

  /* This technique is called LOPP COLLAPSING. The main motivation is to reduce
  loop overhead, which may also help other compiler-supported optimizations */
}

void Example2_LoopFactoring()
{
  /* Example of factor independency and loop-factoring */
  // case:
  for (i = 0; i < n; i++) {
    a[i] = 0;
    for (j = 0; j < n; j++) {
      a[i] = a[i] + b[j]*d[j]*c[i];
    }
  }

  // Note that the factor c[i] is independent of the j-indexed loop. Improve:
  for (i = 0; i < n; i++) {
    a[i] = 0;
    for (j = 0; j < n; j++) {
      a[i] = a[i] + b[j]*d[j];
    }
    a[i] = a[i]*c[i];
  }
  /* This is possible due to c[i] being a common factor.
  However, are there more common factors?
  b[0]*d[0]+b[1]*d[1]+...+b[n-1]*d[n-1] is a common factor which is
  unnecessarily re-computed in every iteration of i. Reducing further: */
  t = 0.;
  for (j=0; j<ARRAY_SIZE; j++) {
    t = t + b[j]*d[j];
  }

  for (i=0; i<ARRAY_SIZE; i++) {
    a[i] = t*c[i];
  }

  /* This technique is called LOOP FACTORING or ELIMINATION OF
  COMMON SUBEXPRESSIONS. Another example could be: */
  for (i = 0; i < n; i++) {
    A[i] = A[i] + s + r*sin(x);
  }
  // being reduced to:
  tmp = s + r*sin(x);
  for (i = 0; i < n; i++) {
    A[i] = A[i] + tmp;
  }
}

void Example3_LookupTable()
{
  /* Special math functions are usually very costly to compute. An example
  from simulating non-equilibrium spins: */

  for (i=1; i<Nx-1; i++) {
    for (j=1; j<Ny-1; j++) {
      for (k=1; k<Nz-1; k++) {
        iL = spin_orientation[i-1][j][k];
        iR = spin_orientation[i+1][j][k];
        iS = spin_orientation[i][j-1][k];
        iN = spin_orientation[i][j+1][k];
        iO = spin_orientation[i][j][k-1];
        iU = spin_orientation[i][j][k+1];
        edelz = iL+iR+iS+iN+iO+iU;
        body_force[i][j][k] = 0.5*(1.0+tanh(edelz/tt));
      }
    }
  }

  /* If the spin values can only be +-1, then the sum can only be in the
  list {-6, -4, -2, 0, 2, 4, 6}. Assuming tt is a constant, we can create a so-
  called LOOKUP TABLE: */

  double tanh_table[13];
  for (i=0; i<=12; i+=2) {
    tanh_table[i] = 0.5*(1.0+tanh((i-6)/tt));
  }
  /* using this, we use the spin value as an index
  to look up the pre-calculated value: */
  for (i=1; i<Nx-1; i++) {
    for (j=1; j<Ny-1; j++) {
      for (k=1; k<Nz-1; k++) {
        // ...
        edelz = iL+iR+iS+iN+iO+iU;
        body_force[i][j][k] = tanh_table[edelz+6];
      }
    }
  }
}

void Example4_StrengthReduction()
{
  /* Aim to shrink the work set which we give to the instructions */
  for (i=0; i<N; i++) {
    y[i] = a*pow(x[i],4)+b*pow(x[i],3)+c*pow(x[i],2)+d*pow(x[i],1)+e;
  }
  // can be shrunken to:
  for (i=0; i<N; i++) {
    y[i] = (((a*x[i]+b)*x[i]+c)*x[i]+d)*x[i]+e;
  }
  // By use of Horner's rule of polynomial evaluation.
}

void Example5_BranchAvoidance1()
{
  /* The work set of a code is the amount of memory it uses (or touches),
  also called memory footprint. In general, shrinking the work set (if possible)
  is a good thing for performance, because it raises the probability of cache
  hit. One example: The spin_orientation array should store values of type char
  instead of type int. (A factor of 4 in the difference of memory footprint.) */

  /* “Tight” loops: few operations per iteration, typically optimized by
  compiler using some form of pipelining. In case of conditional branches in the
  loop body, the compiler optimization will easily fail. */

  for (j=0; j<N; j++) {
    for (i=0; i<N; i++) {
      if (i>j) {
        sign = 1.0;
      }
      else if (i<j) {
        sign = -1.0;
      }
      else {
        sign = 0.0;
      }

      C[j] = C[j] + sign * A[j][i] * B[i];
    }
  }

  // How to minimize the amount of if-tests? Consider:
  for (j=0; j<N-1; j++) {
    for (i=j+1; i<N; i++) {
      C[j] = C[j] + A[j][i] * B[i];
    }
  }

  for (j=1; j<N; j++) {
    for (i=0; i<j; i++) {
      C[j] = C[j] - A[j][i] * B[i];
    }
  }

  // This configuration accomplishes the same tast without any if-tests.
}

void Example6_BranchAvoidance2()
{
  /* Two more examples of branch avoidance: */
  // FIRST EXAMPLE
  for (i=0; i<n; i++) {
    if (i==0) {
      a[i] = b[i+1]-b[i];
    }
    else if (i==n-1) {
      a[i] = b[i]-b[i-1];
    }
    else {
      a[i] = b[i+1]-b[i-1];
    }
  }

  // By a technique called LOOP PEELING, can be recoded as:
  a[0] = b[1]-b[0];
  for (i=1; i<n-1; i++) {
    a[i] = b[i+1]-b[i-1];
  }
  a[n-1] = b[n-1]-b[n-2];

  // SECOND EXAMPLE
  for (i=0; i<n; i++) {
    if (j>0) {
      x[i] = x[i] + 1;
    }
    else {
      x[i] = 0;
    }
  }
  // Recoded as:
  if (j>0) {
    for (i=0; i<n; i++) {
      x[i] = x[i] + 1;
    }
  }
  else {
    for (i=0; i<n; i++) {
      x[i] = 0;
    }
  }
}

void Example7_SIMDApplication()
{
  /* A “vectorizable” loop can potentially run faster if multiple operations can
  be performed with a single instruction. Using SIMD instructions,
  register-to-register operations will be greatly accelerated.
  Warning: if the code is strongly limited by memory bandwidth,
  no SIMD technique can bridge this gap. */

  /* Ideal scenario for applying SIMD to a loop is in the case of:
        * All iterations are independent
        * There is no branch in the loop body
        * The arrays are accessed with a stride of one
  */
  // Example:
  for (i=0; i<n; i++)
  {
    r[i] = x[i] + y[i];
  }
  /* Assuming the memory regions pointed
  by r, x and y do not overlap / no aliasing

  Following is a PSEUDOCODE for applying SIMD
  (assuming 4 value storage register)*/

  int i, rest = N%4;
  for (i=0; i<N-rest; i+=4) {
    load R1 = [x[i],x[i+1],x[i+2],x[i+3]];
    load R2 = [y[i],y[i+1],y[i+2],y[i+3]];
    R3 = ADD(R1,R2);
    store [r[i],r[i+1],r[i+2],r[i+3]] = R3;
  }
  for (i=N-rest; i<N; i++) {
    r[i] = x[i] + y[i];
  }

  /* However, you need to beware loop dependency. If a loop iteration depends
  on the result of another iteration, then there is LOOP-CARRIED DEPENDENCY. */
  for (i=0; i<n; i++){
    A[i] = 10.0 * A[i+offset];
  }
  /*
    * If offset < 0 then you have REAL dependency (read-after-write hazard)
    * If offset > 0 then you have PSEUDO dependency (write-after-read hazard)
  */

  /* In case of real dependency, SIMD cannot be applied if the negative offset
  size is smaller than the SIMD width. For example: */
  for (i=0; i<n; i++){
    A[i] = 10.0 * A[i-1];
  }

  /* In case of pseudo dependency, SIMD can be applied.
  For example when offset > 0: */
  for (i=0;i<n;i++){
    A[i] = 10.0 * A[i+offset];
  }
}

void Example8_RiskOfAliasing()
{
  /* Is it safe to vectorize the following function? */
  void compute(int start, int stop, double *a, double *b) {
    for (int i=start; i<stop; i++) {
      a[i] = 10.0*b[i];
    }
  }

  /* A problem of ALIASING will arise if the compute function is called as: */
  compute(0, N-1, &(array_a[1]), array_a);
  /* If a programmer can guarantee that aliasing won't happen,
  then this hint can be provided to the compiler. */

  // THE ROLE OF COMPILERS
  /* A compiler translates a program, which is implemented in a programming
  language, to machine code. A compiler can carry out code optimization of
  various degrees, dictated by the compiler options provided by the user.
  (-O0, -O1,-O2, ....)

  Different compilers probably allow different compiler options, should
  therefore refer to the user manual! Numerical accuracy may suffer from too
  aggressive compiler optimizations. */

  // CONCEPT OF PROFILING
  /* Profiling — gather information about a program’s behavior, especially its
  use of resourses. The purpose is to pinpoint the “hotspots”, and more
  importantly, to identify any performance optimization
  opportunities (if any) and/or bugs. */

  /* Two approaches to profiling / information gathering:
      * Instrumentation -- compiler automatically inserts some code
        to LOG each function call during the actual execution.
      * Sampling -- the program execution is interrupted at periodic
        intervals, with information being recorded.
  */

  /* One well known profiler: GNU gprof.
      https://sourceware.org/binutils/docs/gprof/

        * Step 1: Compile and link the program with profiling enabled.
        * Step 2: Execute the program to generate a profile data file.
        * Step 3: Run gprof to analyze the profile data.

  */

  // HARDWARE PERFORMANCE COUNTERS
  /* Knowing how much time is spent in what pieces of the code is the
  first step. But what is the actual reason for 'a slow code' or which resource
  is the one that limits the performance? */

  /* Modern processors feature a small number of PERFORMANCE COUNTERS, which are
  special on-chip registers that get incrememted each time a certain event
  occurs. Examples of possible events to monitor in this way:

      * Number of Cache Line transfers.
      * Number of loads and stores.
      * Number of floating-point operations.
      * Number of branch mispredictions.
      * Number of pipeline stalls.
      * Number of instructions executed.
      
  */
}
