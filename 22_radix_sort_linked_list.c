#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} Queue;

void enqueue(Queue *queue, Node *node) {
    node->next = NULL;
    if (queue->head == NULL)
        queue->head = node;
    else
        queue->tail->next = node;
    queue->tail = node;
}

void display(Node *head) {
    while (head != NULL) {
        printf("%d", head->value);
        if (head->next != NULL)
            printf(" -> ");
        head = head->next;
    }
    printf(" -> NULL\n");
}

int main(void) {
    Node *head = NULL;
    Node *tail = NULL;
    int n, value;
    long long maximum = 0;

    printf("Number of non-negative integers: ");
    scanf("%d", &n);
    printf("Enter values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        if (value < 0) {
            printf("This version accepts non-negative integers only\n");
            while (head != NULL) {
                Node *temp = head;
                head = head->next;
                free(temp);
            }
            return 1;
        }
        Node *node = (Node *)malloc(sizeof(Node));
        if (node == NULL)
            return 1;
        node->value = value;
        node->next = NULL;
        if (head == NULL)
            head = node;
        else
            tail->next = node;
        tail = node;
        if (value > maximum)
            maximum = value;
    }

    for (long long place = 1; maximum / place > 0; place *= 10) {
        Queue buckets[10] = {{NULL, NULL}};
        Node *current = head;
        while (current != NULL) {
            Node *next = current->next;
            int digit = (int)((current->value / place) % 10);
            enqueue(&buckets[digit], current);
            current = next;
        }

        head = NULL;
        tail = NULL;
        for (int i = 0; i < 10; i++) {
            if (buckets[i].head != NULL) {
                if (head == NULL)
                    head = buckets[i].head;
                else
                    tail->next = buckets[i].head;
                tail = buckets[i].tail;
            }
        }

        printf("After place %lld: ", place);
        display(head);
        if (place > maximum / 10)
            break;
    }

    printf("Sorted list: ");
    display(head);
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}
