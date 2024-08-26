#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "semaphore.h"

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

//---------------------------------------
