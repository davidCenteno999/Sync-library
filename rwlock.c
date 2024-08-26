#include "rwlock.h"

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
