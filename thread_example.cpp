#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define num_threads 6
pthread_mutext_t mutex_print;

/*
construct 6 threads. each thread print its number. For example, thread 1 prints "1", thread 2 print "2".
every time, only one thread can print. Thus, we lock the print-statement. After print it, unlock it.

 */




void *thread_worker(void *var) {
  // change the type
  int *n_ptr = (int *) var;
  
  while(1) {
    pthread_mutext_lock (&mutex_print);
    printf("%d", n_ptr);
    printf("\n");    
    pthread_mutext_unlock (&mutex_print);
  }

  pthread_exit((void*) 0);
  
}

int main() {
  pthread_t thread[num_threads];
  for (int i = 0; i < num_threads; i++) {
    int *ptr = (int *) malloc(sizeof(int));
    *ptr = i + 1;
    pthread_create(&thread[i], NULL, thread_worker, (void *) ptr);

  }

  for (int i = 0; i < num_threads; i++) {
    pthread_join(thread[i], NULL);
  }

  pthread_exit(NULL);
  return 0;

}
