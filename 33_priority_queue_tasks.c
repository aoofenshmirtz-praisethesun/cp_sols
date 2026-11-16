#include <stdio.h>

#define MAX 1000

typedef struct {
    int taskId;
    int priority;
} Task;

void swap(Task *a, Task *b) {
    Task temp = *a;
    *a = *b;
    *b = temp;
}

void insertTask(Task heap[], int *size, int taskId, int priority) {
    if (*size == MAX)
        return;
    int index = (*size)++;
    heap[index].taskId = taskId;
    heap[index].priority = priority;
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent].priority >= heap[index].priority)
            break;
        swap(&heap[parent], &heap[index]);
        index = parent;
    }
}

Task extractHighest(Task heap[], int *size) {
    Task empty = {-1, -1};
    if (*size == 0)
        return empty;
    Task answer = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    int index = 0;
    while (index < *size) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if (left < *size && heap[left].priority > heap[largest].priority)
            largest = left;
        if (right < *size && heap[right].priority > heap[largest].priority)
            largest = right;
        if (largest == index)
            break;
        swap(&heap[index], &heap[largest]);
        index = largest;
    }
    return answer;
}

int main(void) {
    Task heap[MAX];
    int size = 0;
    int n, taskId, priority;
    printf("Number of tasks: ");
    scanf("%d", &n);
    printf("Enter task ID and priority:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &taskId, &priority);
        insertTask(heap, &size, taskId, priority);
    }

    printf("Tasks processed from highest priority to lowest:\n");
    while (size > 0) {
        Task task = extractHighest(heap, &size);
        printf("Task %d, priority %d\n", task.taskId, task.priority);
    }
    return 0;
}
