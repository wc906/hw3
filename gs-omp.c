# include <stdio.h>
# include <string.h>
# include <math.h>
# include "util.h"



double Residual(long N,double *u){

  double sum=0;
  long i;
  double residualV[N];
  double h=1.0/(N+1);
  double aii=2/h/h;
  double aij=-1/h/h;

  residualV[0]=u[0]*aii+u[1]*aij-1;
#pragma omp parallel for
  for(i=1;i<N-1;i++){
    residualV[i]=u[i-1]*aij+u[i]*aii+u[i+1]*aij-1;
  }
  residualV[N-1]=u[N-2]*aij+u[N-1]*aii-1;

  sum=0;
#pragma omp parallel for reduction(+:sum)
  for(i=0;i<N;i++){
    sum=sum+residualV[i]*residualV[i];
  }

  return sqrt(sum);

}



int main(int argc, char ** argv)
{
  
  long N= atol(argv[1]);
  double h=1.0/(N+1);
  double aii=2/h/h;
  double aij=-1/h/h;
  double sum=0,residual,residual0;
  double u[N];
  long i,j,iter,MaxIter;
  MaxIter=100;  
  
  timestamp_type time1,time2;


  printf("%ld\n",N);
#pragma omp parallel for
  for(i=0;i<N;i++){
    u[i]=0.0;
  }


  
  get_timestamp(&time1);


  residual0=Residual(N,u);


  printf("Start RB-GS method!\n");
  iter=0;
  do{
    u[0]=(1-u[1]*aij)/aii;
#pragma omp parallel for
    for(i=2;i<N-1;i+=2){
      u[i]=(1-u[i-1]*aij-u[i+1]*aij)/aii;
    }
#pragma omp parallel for
    for(i=1;i<N-1;i+=2){
      u[i]=(1-u[i-1]*aij-u[i+1]*aij)/aii;
    }
    u[N-1]=(1-u[N-2]*aij)/aii;

    residual=Residual(N,u);


    //printf("%f\n",residual);
    iter++;
  }while(residual>residual0*0.000001 && iter<MaxIter);

  
  printf("Gauss-Seidel method!\n");
  printf("Iteration:%ld\n",iter);
  printf("Last residual: %f\n",residual);



  get_timestamp(&time2);

  double elapsed = timestamp_diff_in_seconds(time1,time2);
  printf("Time elapsed is %f seconds.\n",elapsed);
  
  return 0;
}


