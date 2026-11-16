#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int array[], int size, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && array[left] > array[largest])
        largest = left;
    if (right < size && array[right] > array[largest])
        largest = right;
    if (largest != root) {
        swap(&array[root], &array[largest]);
        heapify(array, size, largest);
    }
}

void heapSort(int array[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);
    for (int end = size - 1; end > 0; end--) {
        swap(&array[0], &array[end]);
        heapify(array, end, 0);
    }
}

int main(void) {
    int n, array[1000];
    printf("Number of elements: ");
    scanf("%d", &n);
    if (n < 0 || n > 1000)
        return 1;
    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);

    heapSort(array, n);
    printf("Ascending order: ");
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\nHeap sort is not stable.\n");
    return 0;
}
