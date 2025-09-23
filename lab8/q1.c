#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int buf[5], f = -1, r = -1;
int produced = 0, consumed = 0;
sem_t mutex, full, empty;
sem_t max_diff;   

void *produce(void *arg)
{
    while (1)
    {
        sem_wait(&max_diff);   
        sem_wait(&empty);
        sem_wait(&mutex);

        r = (r + 1) % 5;
        buf[r] = produced;
        produced++;
        printf("Produced item %d | Difference = %d\n", buf[r], produced - consumed);

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);  
    }
    return NULL;
}

void *consume(void *arg)
{
    int item;
    while (1)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        f = (f + 1) % 5;
        item = buf[f];
        consumed++;
        printf("Consumed item %d | Difference = %d\n", item, produced - consumed);

        sem_post(&mutex);
        sem_post(&empty);
        sem_post(&max_diff);

        sleep(2.5);  
    }
    return NULL;
}

int main()
{
    pthread_t tid1, tid2;

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 5);
    sem_init(&max_diff, 0, 10);  // producer can only be 10 ahead

    pthread_create(&tid1, NULL, produce, NULL);
    pthread_create(&tid2, NULL, consume, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
