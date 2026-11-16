#include <stdio.h>

#define MAX 1000

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyDown(int heap[], int size, int index) {
    while (1) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if (left < size && heap[left] < heap[smallest])
            smallest = left;
        if (right < size && heap[right] < heap[smallest])
            smallest = right;
        if (smallest == index)
            break;
        swap(&heap[index], &heap[smallest]);
        index = smallest;
    }
}

void buildHeap(int heap[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapifyDown(heap, size, i);
}

void insertElement(int heap[], int *size, int value) {
    if (*size == MAX) {
        printf("Heap is full\n");
        return;
    }
    int index = (*size)++;
    heap[index] = value;
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent] <= heap[index])
            break;
        swap(&heap[parent], &heap[index]);
        index = parent;
    }
}

int deleteMin(int heap[], int *size) {
    if (*size == 0)
        return -1;
    int minimum = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    if (*size > 0)
        heapifyDown(heap, *size, 0);
    return minimum;
}

void displayHeap(int heap[], int size) {
    printf("Heap array: ");
    for (int i = 0; i < size; i++)
        printf("%d ", heap[i]);
    printf("\n");
    int index = 0;
    int level = 0;
    int nodesAtLevel = 1;
    while (index < size) {
        printf("Level %d: ", level++);
        for (int i = 0; i < nodesAtLevel && index < size; i++)
            printf("%d ", heap[index++]);
        printf("\n");
        nodesAtLevel *= 2;
    }
}

int main(void) {
    int heap[MAX], size, choice, value;
    printf("Number of initial elements: ");
    scanf("%d", &size);
    if (size < 0 || size > MAX)
        return 1;
    printf("Enter elements: ");
    for (int i = 0; i < size; i++)
        scanf("%d", &heap[i]);
    buildHeap(heap, size);

    do {
        printf("\n1 Insert\n2 Delete minimum\n3 Display\n0 Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Value: ");
            scanf("%d", &value);
            insertElement(heap, &size, value);
        } else if (choice == 2) {
            if (size == 0) {
                printf("Heap is empty\n");
            } else {
                value = deleteMin(heap, &size);
                printf("Deleted minimum = %d\n", value);
            }
        } else if (choice == 3) {
            displayHeap(heap, size);
        }
    } while (choice != 0);
    return 0;
}
