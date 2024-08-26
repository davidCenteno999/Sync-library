#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <pthread.h>

typedef struct {
  int value;
  pthread_cond_t cond;
  pthread_mutex_t mutex;

} semaphore;


void semaphore_init(semaphore *s, int num);
void wait(semaphore *s);
void signal(semaphore *s);
void delete_semaphore(semaphore *s);


#endif // SEMAPHORE_H
