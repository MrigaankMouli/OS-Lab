#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct ThreadData {
    int *arr;
    int size;
};

void *calculate_sum(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;
    long long *sum = malloc(sizeof(long long));
    *sum = 0;
    for (int i = 0; i < data->size; i++)
        *sum += data->arr[i];
    pthread_exit(sum);
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    printf("Enter %d non-negative integers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    struct ThreadData data = {arr, n};
    pthread_t thread;

    pthread_create(&thread, NULL, calculate_sum, &data);

    long long *result;
    pthread_join(thread, (void **)&result);

    printf("Sum of array elements: %lld\n", *result);

    free(arr);
    free(result);
    return 0;
}
