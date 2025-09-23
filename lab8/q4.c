#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CHAIRS 3

sem_t waitingChairs;
sem_t customerReady;
sem_t barberReady;
sem_t mutex;
int customerID = 1;

void *barber(void *arg)
{
    while (1)
    {
        sem_wait(&customerReady);
        sem_wait(&mutex);

        sem_post(&waitingChairs);
        printf("Barber: calling next customer\n");

        sem_post(&mutex);
        sem_post(&barberReady);

        printf("Barber: cutting hair...\n");
        sleep(2);
    }
}

void *customer(void *arg)
{
    int id = *((int *)arg);

    sem_wait(&mutex);
    int val;
    sem_getvalue(&waitingChairs, &val);

    if (val > 0)
    {
        sem_wait(&waitingChairs);
        printf("Customer %d: waiting\n", id);

        sem_post(&mutex);
        sem_post(&customerReady);

        sem_wait(&barberReady);
        printf("Customer %d: getting haircut\n", id);
    }
    else
    {
        printf("Customer %d: no chairs, leaving...\n", id);
        sem_post(&mutex);
    }

    free(arg);
    return NULL;
}

int main()
{
    pthread_t barberThread;
    pthread_create(&barberThread, NULL, barber, NULL);
    sem_init(&waitingChairs, 0, CHAIRS);
    sem_init(&customerReady, 0, 0);
    sem_init(&barberReady, 0, 0);
    sem_init(&mutex, 0, 1);

    while (1)
    {
        pthread_t custThread;
        int *id = malloc(sizeof(int));
        *id = customerID++;
        pthread_create(&custThread, NULL, customer, id);
        pthread_detach(custThread);

        sleep(rand() % 3);
    }

    pthread_join(barberThread, NULL);
    return 0;
}
