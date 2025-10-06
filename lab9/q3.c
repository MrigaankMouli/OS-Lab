#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

struct Range {
    int start;
    int end;
};

int is_prime(int num) {
    if (num < 2) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(num); i += 2)
        if (num % i == 0)
            return 0;
    return 1;
}

void *generate_primes(void *arg) {
    struct Range *range = (struct Range *)arg;
    int start = range->start;
    int end = range->end;

    printf("Prime numbers between %d and %d:\n", start, end);
    for (int i = start; i <= end; i++) {
        if (is_prime(i))
            printf("%d ", i);
    }
    printf("\n");

    pthread_exit(NULL);
}

int main() {
    struct Range range;
    printf("Enter starting number: ");
    scanf("%d", &range.start);
    printf("Enter ending number: ");
    scanf("%d", &range.end);

    pthread_t thread;
    pthread_create(&thread, NULL, generate_primes, &range);

    pthread_join(thread, NULL);

    return 0;
}
