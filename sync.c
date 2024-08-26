#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "sync.h"

//-------------------------------Semaphore-------------------------------//

// Funcion para incicalizar el valor del semaforo,
// el puntero cond y el puntero mutex

void semaphore_init(semaphore *s, int num) {
  s->value = num;
  pthread_cond_init(&s->cond, NULL);
  pthread_mutex_init(&s->mutex, NULL);
}

// Funcion de wait, que espera a que el valor del semaforo sea mayor a 0
// y luego lo disminuye en 1
void wait_semaphore(semaphore *s) {
  pthread_mutex_lock(&s->mutex);
  s->value--;
  if (s->value < 0) {
    pthread_cond_wait(&s->cond, &s->mutex);
  }
  pthread_mutex_unlock(&s->mutex);
}

// La funcion signal, incrementa el valor del semaforo en 1
// y luego notifica a los hilos que estan esperando
void signal_semaphore(semaphore *s) {
  pthread_mutex_lock(&s->mutex);
  s->value++;
  if (s->value <= 0) {
    pthread_cond_signal(&s->cond);
  }
  pthread_mutex_unlock(&s->mutex);
}

void delete_semaphore(semaphore *s) {
    pthread_mutex_destroy(&(s->mutex));
    pthread_cond_destroy(&(s->cond));
}




//-------------------------------Read/Write Lock-------------------------------//
void rwlock_init(rwlock_t *rw) {
  pthread_mutex_init(&rw->lock, NULL);
  pthread_cond_init(&rw->readers, NULL);
  pthread_cond_init(&rw->writers, NULL);
  rw->active_readers = 0;
  rw->active_writers = 0;
  rw->waiting_writers = 0;
}

void read_lock(rwlock_t *rw) {
  pthread_mutex_lock(&rw->lock);
  while (rw->active_writers > 0 || rw->waiting_writers > 0) {
    pthread_cond_wait(&rw->readers, &rw->lock);
  }
  rw->active_readers++;
  pthread_mutex_unlock(&rw->lock);
}

void read_unlock(rwlock_t *rw) {
  pthread_mutex_lock(&rw->lock);
  rw->active_readers--;
  if (rw->active_readers == 0) {
    pthread_cond_signal(&rw->writers);
  }
  pthread_mutex_unlock(&rw->lock);
}

void write_lock(rwlock_t *rw) {
  pthread_mutex_lock(&rw->lock);
  rw->waiting_writers++;
  while (rw->active_writers > 0 || rw->active_readers > 0) {
    pthread_cond_wait(&rw->writers, &rw->lock);
  }
  rw->waiting_writers--;
  rw->active_writers++;
  pthread_mutex_unlock(&rw->lock);
}

void write_unlock(rwlock_t *rw) {
  pthread_mutex_lock(&rw->lock);
  rw->active_writers--;
  if (rw->waiting_writers > 0) {
    pthread_cond_signal(&rw->writers);
  } else {
    pthread_cond_broadcast(&rw->readers);
  }
  pthread_mutex_unlock(&rw->lock);
}