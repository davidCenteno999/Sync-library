#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <pthread.h>

typedef struct {
  int value;
  pthread_cond_t cond;
  pthread_mutex_t mutex;

} semaphore;


void semaphore_init(semaphore *s, int num);
void wait_semaphore(semaphore *s);
void signal_semaphore(semaphore *s);
void sem_delete(semaphore *s);


#endif // SEMAPHORE_H