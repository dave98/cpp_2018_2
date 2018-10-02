#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX = 50;
int thread_count;
sem_t *sems;

void* tokenize(void*);
void* Hello(void* rank);
void* Pth_mat_vec(void* rank);


int main(int argc, char*  argv[]){
  long thread;
  pthread_t* thread_handles;
  int i = 0;

  thread_count = strtol(argv[1], NULL, 10);

  thread_handles = (pthread_t* )malloc (thread_count * sizeof(pthread_t));
  sems = (sem_t* )malloc (thread_count* sizeof(sem_t));

  sem_init(&sems[0], 0, 1);

  for(i = 1; i < thread_count; i++){
    sem_init(&sems[i], 0, 0);
  }

  for(thread = 0; thread < thread_count; thread++){
    pthread_create(&thread_handles[thread], NULL, tokenize, (void*) thread);
  }

  for(thread = 0; thread < thread_count; thread++){
    pthread_join(thread_handles[thread], NULL);
  }

  for(i = 0; i < thread_count; i++){
    sem_destroy(&sems[i]);
  }


  free(thread_handles);
  free(sems);
  return 0;
}

void* Hello(void* rank){
  long my_rank = (long)rank;

  printf("Hello from thread %ld of %d \n", my_rank, thread_count);

  return NULL;
}



void* tokenize(void *rank){
  long my_rank = (long) rank;
  int count;
  int next = (my_rank + 1 ) % thread_count;
  char* fg_rv;
  char* my_line[MAX];
  char* my_string;

  sem_wait(&sems[my_rank]);
  fg_rv = fgets(my_line, MAX, stdin);
  sem_post(&sems[next]);

  while(fg_rv != NULL){
    printf("Thread %ld -> my line = %s ", my_rank, my_line );

    count = 0;
    my_string = strtok(my_line, " \t\n");

    while(my_string != NULL){
        count++;
        printf("Thread %ld -> string %d = %s\n", my_rank, count, my_string );
        my_string = strtok(NULL, " \t\n");
    }
    sem_wait(&sems[my_rank]);
    fg_rv = fgets(my_line, MAX, stdin);
    sem_post(&sems[next]);
  }
  return NULL;
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
