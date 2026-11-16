#include <stdio.h>

void showTree(int array[], int n) {
    int index = 0;
    int level = 0;
    int nodesAtLevel = 1;
    while (index < n) {
        printf("Level %d: ", level);
        for (int i = 0; i < nodesAtLevel && index < n; i++)
            printf("%d ", array[index++]);
        printf("\n");
        nodesAtLevel *= 2;
        level++;
    }
}

int isMaxHeap(int array[], int n) {
    for (int i = 0; i < n / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && array[i] < array[left])
            return 0;
        if (right < n && array[i] < array[right])
            return 0;
    }
    return 1;
}

int main(void) {
    int array[] = {10, 20, 5, 6, 1, 8, 9, 4};
    int n = (int)(sizeof(array) / sizeof(array[0]));
    printf("Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n\nBinary tree representation\n");
    showTree(array, n);
    if (isMaxHeap(array, n))
        printf("It satisfies the max-heap property\n");
    else
        printf("It does not satisfy the max-heap property\n");
    return 0;
}
