#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "sync.h"

#define N 10


pthread_mutex_t mutex;

Barrera barrera;

int A[N][N], B[N][N], C[N][N];

void* multiplicar_matrices(void* arg) {
    int hilo = *(int*)arg;
    int i = hilo; 

  
    for (int j = 0; j < N; j++) {
        C[i][j] = 0;
        for (int z = 0; z < N; z++) {
            C[i][j] += A[i][z] * B[z][j];
        }
    }
  
    barrera_wait(&barrera);

  
    if (hilo == 0) {
        printf("Matriz resultante C:\n");
        for (i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[N];
    int hilos_fila[N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

    printf("Matriz A:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
        printf("\n");
    }

    printf("Matriz B:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
        printf("\n");
    }

    barrera_init(&barrera, N);

    for (int i = 0; i < N; i++) {
        hilos_fila[i] = i;
        pthread_create(&hilos[i], NULL, multiplicar_matrices, (void*)&hilos_fila[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(hilos[i], NULL);
    }
    barrera_destroy(&barrera);
    return 0;
}