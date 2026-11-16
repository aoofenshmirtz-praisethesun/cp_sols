#include <stdio.h>
#include <stdlib.h>

void printArray(int array[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void countingPass(int array[], int n, long long minimum, unsigned long long place) {
    int count[10] = {0};
    int *output = (int *)malloc((size_t)n * sizeof(int));
    if (output == NULL)
        exit(1);

    for (int i = 0; i < n; i++) {
        unsigned long long key = (unsigned long long)((long long)array[i] - minimum);
        int digit = (int)((key / place) % 10);
        count[digit]++;
    }

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        unsigned long long key = (unsigned long long)((long long)array[i] - minimum);
        int digit = (int)((key / place) % 10);
        output[count[digit] - 1] = array[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        array[i] = output[i];
    free(output);
}

int main(void) {
    int n;
    printf("Number of elements: ");
    scanf("%d", &n);
    if (n <= 0)
        return 0;

    int *array = (int *)malloc((size_t)n * sizeof(int));
    if (array == NULL)
        return 1;
    printf("Enter integers, including negative values if needed:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);

    long long minimum = array[0];
    unsigned long long maximumKey = 0;
    for (int i = 1; i < n; i++)
        if (array[i] < minimum)
            minimum = array[i];

    for (int i = 0; i < n; i++) {
        unsigned long long key = (unsigned long long)((long long)array[i] - minimum);
        if (key > maximumKey)
            maximumKey = key;
    }

    if (maximumKey == 0) {
        printArray(array, n);
        free(array);
        return 0;
    }

    for (unsigned long long place = 1; maximumKey / place > 0; place *= 10) {
        countingPass(array, n, minimum, place);
        printf("After place %llu: ", place);
        printArray(array, n);
        if (place > maximumKey / 10)
            break;
    }

    free(array);
    return 0;
}
