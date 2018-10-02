#include <iostream>
#include <semaphore.h>
#include <pthread.h>

using namespace std;

const int MAX = 50;
int thread_count;

//void* tokenize(void*);
void¨* Hello(void* rank);


int main(int argc, char*  argv[]){
  long thread;
  pthread* thread_handles;

  thread_count = strtol(argv[1], NULL, 10);

  thread_handles = malloc (thread_count * sizeof(pthread_t));

  for(thread = 0; thread < thread_count; thread++){
    pthread_create(&thread_handles[thread], NULL, Hello, (void*) thread);
  }

  cout<<"Main thread saying hi"<<endl;

  for(thread = 0; thread < thread_count; thread++){
    pthread_join(thread_handles[thread], NULL);
  }

  free(thread_handles);
  return 0;
}

void¨* Hello(void* rank){
  long my_rank = (long)rank;

  cout<<"saying hi from"<<my_rank<<" of "<<thread_count<<endl;

  return NULL;
}
/*
void* tokenize(void *rank){
  long my_rank = (long) rank;
  int count;
  int next = (my_rank + 1 ) % thread_count;
  char* fg_rv;
  char my_line[MAX];
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
}*/
