#ifndef SYNC_H
#define SYNC_H


#include <pthread.h>

//Semaforo

typedef struct {
  int value;
  pthread_cond_t cond;
  pthread_mutex_t mutex;

} semaphore;


void semaphore_init(semaphore *s, int num);
void wait_semaphore(semaphore *s);
void signal_semaphore(semaphore *s);
void delete_semaphore(semaphore *s);


//R/W Lock
typedef struct {
  pthread_mutex_t lock;
  pthread_cond_t readers;
  pthread_cond_t writers;
  int active_readers;
  int active_writers;
  int waiting_writers;
} rwlock_t;

void rwlock_init(rwlock_t *rw);

void read_lock(rwlock_t *rw);
void read_unlock(rwlock_t *rw);

void write_lock(rwlock_t *rw);
void write_unlock(rwlock_t *rw);


//Barrera

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t hilos;
    int contador;
    int limite;
} Barrera;

void barrera_init(Barrera* barrier, int limite);
void barrera_wait(Barrera* barrier);
void barrera_destroy(Barrera* barrier);


#endif