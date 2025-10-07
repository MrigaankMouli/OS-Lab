#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

typedef struct process {
    int pid;
    int burst_time;
    int remaining_time;
    struct process* next;
} Process;

typedef struct queue {
    Process* front;
    Process* rear;
} Queue;

void enqueue(Queue* q, Process* p) {
    p->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = p;
    } else {
        q->rear->next = p;
        q->rear = p;
    }
}

Process* dequeue(Queue* q) {
    if (q->front == NULL)
        return NULL;
    Process* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    temp->next = NULL;
    return temp;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

void runRoundRobin(Queue* from, Queue* to, int time_quantum, int level) {
    printf("\nRunning Round Robin at Queue %d with time quantum %d\n", level, time_quantum);
    int time = 0;
    int count = 0;
    Process* p;

    int size = 0;
    for (Process* temp = from->front; temp != NULL; temp = temp->next)
        size++;

    for (int i = 0; i < size; i++) {
        p = dequeue(from);
        if (!p) break;

        int exec_time = (p->remaining_time > time_quantum) ? time_quantum : p->remaining_time;
        printf("Process %d executing for %d units (remaining before: %d)\n", p->pid, exec_time, p->remaining_time);

        p->remaining_time -= exec_time;
        time += exec_time;

        if (p->remaining_time > 0) {
            printf("Process %d not finished, demoting to next queue\n", p->pid);
            enqueue(to, p);
        } else {
            printf("Process %d finished execution\n", p->pid);
            free(p);
        }
    }
}

void runFCFS(Queue* q) {
    printf("\nRunning FCFS at Queue 3\n");
    int time = 0;
    Process* p;
    while ((p = dequeue(q)) != NULL) {
        printf("Process %d executing for %d units\n", p->pid, p->remaining_time);
        time += p->remaining_time;
        p->remaining_time = 0;
        printf("Process %d finished execution\n", p->pid);
        free(p);
    }
}

int main() {
    Queue q1 = {NULL, NULL};
    Queue q2 = {NULL, NULL};
    Queue q3 = {NULL, NULL};

    int burst_times[] = {10, 4, 6, 8, 14, 12};
    int n = sizeof(burst_times) / sizeof(burst_times[0]);

    for (int i = 0; i < n; i++) {
        Process* p = (Process*) malloc(sizeof(Process));
        p->pid = i + 1;
        p->burst_time = burst_times[i];
        p->remaining_time = burst_times[i];
        p->next = NULL;
        enqueue(&q1, p);
    }

    runRoundRobin(&q1, &q2, 4, 1);

    runRoundRobin(&q2, &q3, 8, 2);

    runFCFS(&q3);

    return 0;
}
