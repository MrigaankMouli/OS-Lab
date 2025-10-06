#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct ThreadData {
    int *arr;
    int size;
    long long even_sum;
    long long odd_sum;
};

void *sum_even_odd(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;
    data->even_sum = 0;
    data->odd_sum = 0;

    for (int i = 0; i < data->size; i++) {
        if (data->arr[i] % 2 == 0)
            data->even_sum += data->arr[i];
        else
            data->odd_sum += data->arr[i];
    }

    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    struct ThreadData data = {arr, n, 0, 0};
    pthread_t thread;

    pthread_create(&thread, NULL, sum_even_odd, &data);
    pthread_join(thread, NULL);

    printf("Sum of even numbers: %lld\n", data.even_sum);
    printf("Sum of odd numbers: %lld\n", data.odd_sum);

    free(arr);
    return 0;
}
