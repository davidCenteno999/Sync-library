#ifndef RWLOCK_H
#define RWLOCK_H

#include <pthread.h>

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

#endif
