#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semA, semB;

void *thread1(void *arg)
{
    sem_wait(&semA);
    printf("Thread 1: locked semA\n");
    sleep(1); 

    sem_wait(&semB);
    printf("Thread 1: locked semB\n");

    printf("Thread 1: accessing shared resource\n");

    sem_post(&semB);
    sem_post(&semA);

    return NULL;
}

void *thread2(void *arg)
{
    sem_wait(&semB);
    printf("Thread 2: locked semB\n");
    sleep(1); 

    sem_wait(&semA);
    printf("Thread 2: locked semA\n");

    printf("Thread 2: accessing shared resource\n");

    sem_post(&semA);
    sem_post(&semB);

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    sem_init(&semA, 0, 1);
    sem_init(&semB, 0, 1);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
