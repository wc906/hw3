/******************************************************************************
* FILE: omp_bug2.c
* DESCRIPTION:
*   Another OpenMP program with a bug. 
* AUTHOR: Blaise Barney 
* LAST REVISED: 04/06/05 
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
int nthreads, i;
double total=0.0;
//shared variable initialization should be outside, change to double to be accurate

/*** Spawn parallel region ***/
#pragma omp parallel 
  {

    //tid should be private variable
    int tid;

  /* Obtain thread number */
  tid = omp_get_thread_num();
  /* Only master thread does this */
  if (tid == 0) {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }
  printf("Thread %d is starting...\n",tid);

  #pragma omp barrier

  /* do some work */
  //total needs reduction here.
#pragma omp for schedule(dynamic,10) reduction(+:total)
  for (i=0; i<1000000; i++) 
    total = total + i*1.0;

  printf ("Thread %d is done! Total= %.8e\n",tid,total);

  } /*** End of parallel region ***/
}
