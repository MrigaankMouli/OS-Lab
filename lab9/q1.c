#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *fib_series;
int n;

void *generate_fibonacci(void *arg) {
    fib_series[0] = 0;
    if (n > 1)
        fib_series[1] = 1;
    for (int i = 2; i < n; i++)
        fib_series[i] = fib_series[i - 1] + fib_series[i - 2];
    pthread_exit(NULL);
}

int main() {
    printf("Enter the number of Fibonacci terms: ");
    scanf("%d", &n);

    fib_series = (int *)malloc(n * sizeof(int));

    pthread_t thread;
    pthread_create(&thread, NULL, generate_fibonacci, NULL);

    pthread_join(thread, NULL);

    printf("Fibonacci Series: ");
    for (int i = 0; i < n; i++)
        printf("%d ", fib_series[i]);
    printf("\n");

    free(fib_series);
    return 0;
}
