#include <stdio.h>
#include <omp.h>
static long num_steps = 100000000;
double step;
const int THREAD_COUNT = 10;

int main ()
{
	  int i;
	  double pi, sum = 0.0;
	  double start_time, run_time;

	  start_time = omp_get_wtime();


      omp_set_num_threads(THREAD_COUNT);
      double values[10] = {0};
	  step = 1.0/(double) num_steps;

      #pragma omp parallel
      {
        int startThread = omp_get_thread_num();
        double threadApproxValue = 0;
        for (long i=startThread+1;i<= num_steps; i+=THREAD_COUNT){
		  double x = (i-0.5)*step;
		  threadApproxValue += 4.0/(1.0+x*x);
	    }
        values[startThread] = threadApproxValue;
      }

      for(int i=0; i<THREAD_COUNT; i++){
        sum += values[i];
      }

	  pi = step * sum;
	  run_time = omp_get_wtime() - start_time;
	  printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
}	  
