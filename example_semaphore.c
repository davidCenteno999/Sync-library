#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "semaphore.h"

semaphore sem;  // Cambiado de puntero a instancia

void *f1(void* args) {
    wait(&sem);
    sleep(1);
    printf("Hilo %d\n", *(int*)args);
    signal(&sem);
    free(args);  // Liberar la memoria asignada para el argumento
    return NULL;
}

int main(void) {
    //printf("Hello World\n");

    // Inicializar el semáforo
    semaphore_init(&sem, 1);

    pthread_t th[3];

    // Crear 3 hilos
    for (int i = 0; i < 3; i++) {
        int *a = malloc(sizeof(int)); 
        *a = i;
        if (pthread_create(&th[i], NULL, f1, a) != 0) {
            printf("Error al crear el hilo\n");
        }
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < 3; i++) {
        pthread_join(th[i], NULL);
    }

    // Destruir el semáforo
    delete_semaphore(&sem);

    return 0;
}


