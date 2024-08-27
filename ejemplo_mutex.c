#include <math.h>
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;
int primos=0;


void *calcPrimos(void *arg) {

  int num = *(int *)arg;
  int raiz = sqrt(num);

  for (int i = 2; i <= raiz; i++) {
    if (num % i == 0) {
      return NULL;
    }
  }
  pthread_mutex_lock(&mutex);
  primos++;
  pthread_mutex_unlock(&mutex);
}

int main(void) {
  printf("Hello World\n");

  int numeros;

  pthread_mutex_init(&mutex, NULL);

  printf("Escriba los numeros a calcular: ");

  scanf("%d", &numeros);

  pthread_t threads[numeros - 2];

  for (int i = 2; i < numeros; i++) {
    int *num = malloc(sizeof(int));
    *num = i;
    pthread_create(&threads[i-2], NULL, (void*) calcPrimos, (void *)num);
  }

  for (int i = 2; i < numeros; i++) {
    pthread_join(threads[i-2], NULL);
  }

  printf("%d", primos);

  pthread_mutex_destroy(&mutex);
  return 0;
}