#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "rwlock.h"

rwlock_t lock;
int data = 0;

void *reader(void *arg) {
      read_lock(&lock);
    printf("Reader %ld: Read data = %d\n", (long)arg, data);
    //sleep(1); 
      read_unlock(&lock);
    return NULL;
}

void *writer(void *arg) {
      write_lock(&lock);
      data += 1;
    printf("Writer %ld: Wrote data = %d\n", (long)arg, data);
    //sleep(1); 
      write_unlock(&lock);
    return NULL;
}

int main() {
  pthread_t r1, r2, r3, r4, r5, r6, r7, r8, r9, 
  w1, w2, w3 ,w4 ,w5 ,w6;

  rwlock_init(&lock);

  /*printf("Indique cuantos hilos quiere usar: ");
  int num;
  sscanf("%d", num);

  for(int i = 0; i < num) {
    if 
  }*/


  pthread_create(&r1, NULL, reader, (void *)1);
  pthread_create(&r2, NULL, reader, (void *)2);
  pthread_create(&w1, NULL, writer, (void *)1);
  pthread_create(&r3, NULL, reader, (void *)3);
  pthread_create(&w2, NULL, writer, (void *)2);
  pthread_create(&r4, NULL, reader, (void *)4);
  pthread_create(&r5, NULL, reader, (void *)5);
  pthread_create(&w3, NULL, writer, (void *)3);
  pthread_create(&r6, NULL, reader, (void *)6);
  pthread_create(&w4, NULL, writer, (void *)4);
  pthread_create(&r7, NULL, reader, (void *)7);
  pthread_create(&r8, NULL, reader, (void *)8);
  pthread_create(&w5, NULL, writer, (void *)5);
  pthread_create(&r9, NULL, reader, (void *)9);
  pthread_create(&w6, NULL, writer, (void *)6);

  pthread_join(r1, NULL);
  pthread_join(r2, NULL);
  pthread_join(w1, NULL);
  pthread_join(r3, NULL);
  pthread_join(w2, NULL);
  pthread_join(r4, NULL);
  pthread_join(r5, NULL);
  pthread_join(w3, NULL);
  pthread_join(r6, NULL);
  pthread_join(w4, NULL);
  pthread_join(r7, NULL);
  pthread_join(r8, NULL);
  pthread_join(w5, NULL);
  pthread_join(r9, NULL);
  pthread_join(w6, NULL);

  return 0;
}
