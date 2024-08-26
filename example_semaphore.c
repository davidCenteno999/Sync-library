#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "semaphore.h"

semaphore sem;  // Cambiado de puntero a instancia
int num = 0;

typedef struct {
  int thread_id;
  int op1;
  int op2;
  char operation; 

} args_f1;


void *f1(void* args) {

    wait(&sem);
     args_f1 *t_args = (args_f1*)args;
    printf("Hilo %d\n", t_args->thread_id);
    printf("Operacion: %c || Operando 1: %d || Operando 2: %d \n",
    t_args->operation,t_args->op1,t_args->op2);
    int result;
    if(t_args->operation == '+'){
        result = t_args->op1 + t_args->op2;
    }else{
        result = t_args->op1 - t_args->op2;
    }
    printf("Resultado: %d\n", result);
    sleep(1);
    signal(&sem);
    free(args);  // Liberar la memoria asignada para el argumento
    return NULL;
}

int main(void) {
    srand(time(NULL));

    // Inicializar el semáforo
    semaphore_init(&sem, 1);

    pthread_t th[3];
    
    // Crear 3 hilos
    for (int i = 0; i < 3; i++) {
        
        args_f1 *args = malloc(sizeof(args_f1)); 
        args->thread_id = i;
        args->op1 = random() % 100;
        args->op2 = random() % 100;
        args->operation = (rand() % 2 == 0) ? '+' : '-';
        if (pthread_create(&th[i], NULL, f1, args) != 0) {
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