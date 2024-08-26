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
void sem_delete(semaphore *s);

typedef struct {
  pthread_mutex_t lock;
  pthread_cond_t readers;
  pthread_cond_t writers;
  int active_readers;
  int active_writers;
  int waiting_writers;
} rwlock_t;

// Funciones
void rwlock_init(rwlock_t *rw);

void read_lock(rwlock_t *rw);
void read_unlock(rwlock_t *rw);

void write_lock(rwlock_t *rw);
void write_unlock(rwlock_t *rw);


#endif // SEMAPHORE_H