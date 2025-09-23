#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;
int readcount = 0;   // number of active readers
int data = 0;        // shared resource

void *reader(void *arg)
{
    int id = *((int *)arg);
    while (1) {
        sem_wait(&mutex);
        readcount++;
        if (readcount == 1)
            sem_wait(&wrt);  // first reader locks writers out
        sem_post(&mutex);

        // critical section (reading)
        printf("Reader %d: read data = %d\n", id, data);
        sleep(1);

        sem_wait(&mutex);
        readcount--;
        if (readcount == 0)
            sem_post(&wrt);  // last reader unlocks writers
        sem_post(&mutex);

        sleep(1); // simulate doing something else
    }
}

void *writer(void *arg)
{
    int id = *((int *)arg);
    while (1) {
        sem_wait(&wrt);

        // critical section (writing)
        data++;
        printf("Writer %d: wrote data = %d\n", id, data);
        sleep(2);

        sem_post(&wrt);

        sleep(1); // simulate doing something else
    }
}

int main()
{
    pthread_t rtid[3], wtid[2];
    int rids[3] = {1, 2, 3};
    int wids[2] = {1, 2};

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // create readers
    for (int i = 0; i < 3; i++)
        pthread_create(&rtid[i], NULL, reader, &rids[i]);

    // create writers
    for (int i = 0; i < 2; i++)
        pthread_create(&wtid[i], NULL, writer, &wids[i]);

    // join threads (infinite loop, so program runs until stopped)
    for (int i = 0; i < 3; i++)
        pthread_join(rtid[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(wtid[i], NULL);

    return 0;
}
