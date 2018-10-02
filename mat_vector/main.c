#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int m = 100;
const int n = 150;
int thread_count;
int* y;
int** A;
int* x;

void* Pth_mat_vec(void* rank);

int main(int argc, char*  argv[]){
  long thread;
  pthread_t* thread_handles;
  int i = 0;

  thread_count = strtol(argv[1], NULL, 10);
  thread_handles = (pthread_t* )malloc (thread_count * sizeof(pthread_t));

  y = (int*)malloc(n* sizeof(int));
  x = (int*)malloc(n* sizeof(int));
  A = (int*)malloc(m * )


  for(thread = 0; thread < thread_count; thread++){
    pthread_create(&thread_handles[thread], NULL, tokenize, (void*) thread);
  }

  for(thread = 0; thread < thread_count; thread++){
    pthread_join(thread_handles[thread], NULL);
  }

  free(thread_handles);
  return 0;
}


void* Pth_mat_vec(void* rank){
  long my_rank = (long) rank;
  int i, j;
  int local_m = m / thread_count;
  int my_fisrt_row = my_rank * local_m;
  int my_last_row = (my_rank +1) * local_m - 1;

  for(i = my_fisrt_row; <= my_last_row; i++){
    y[i] = 0.0;
    for(j = 0; j < n; j++){
      y[i] += A[i][j] * x[j];
    }
  }
  return NULL;
}
