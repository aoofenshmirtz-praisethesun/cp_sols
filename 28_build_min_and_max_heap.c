#include <stdio.h>

#define MAX 1000

void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

void maxHeapify(int a[], int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < n && a[left] > a[largest]) largest = left;
    if (right < n && a[right] > a[largest]) largest = right;
    if (largest != i) { swap(&a[i], &a[largest]); maxHeapify(a, n, largest); }
}

void minHeapify(int a[], int n, int i) {
    int smallest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < n && a[left] < a[smallest]) smallest = left;
    if (right < n && a[right] < a[smallest]) smallest = right;
    if (smallest != i) { swap(&a[i], &a[smallest]); minHeapify(a, n, smallest); }
}

int main(void) {
    int maxHeap[MAX], minHeap[MAX], n;
    if (scanf("%d", &n) != 1 || n < 0 || n > MAX) return 1;
    for (int i = 0; i < n; i++) if (scanf("%d", &maxHeap[i]) != 1) return 1;
    for (int i = 0; i < n; i++) minHeap[i] = maxHeap[i];
    for (int i = n / 2 - 1; i >= 0; i--) { maxHeapify(maxHeap, n, i); minHeapify(minHeap, n, i); }
    printf("Max heap: "); for (int i = 0; i < n; i++) printf("%d ", maxHeap[i]);
    printf("\nMin heap: "); for (int i = 0; i < n; i++) printf("%d ", minHeap[i]);
    printf("\n");
    return 0;
}
