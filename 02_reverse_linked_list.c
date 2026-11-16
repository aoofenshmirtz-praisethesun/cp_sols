#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int data; struct Node *next; } Node;

Node *newNode(int value) {
    Node *node = malloc(sizeof(Node));
    if (!node) exit(1);
    node->data = value;
    node->next = NULL;
    return node;
}

void append(Node **head, int value) {
    Node *node = newNode(value);
    if (*head == NULL) { *head = node; return; }
    Node *current = *head;
    while (current->next) current = current->next;
    current->next = node;
}

Node *reverse(Node *head) {
    Node *previous = NULL;
    Node *current = head;
    while (current) {
        Node *next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    return previous;
}

void display(Node *head) {
    while (head) { printf("%d", head->data); if (head->next) printf(" -> "); head = head->next; }
    printf(" -> NULL\n");
}

int main(void) {
    Node *head = NULL;
    int n, value;
    if (scanf("%d", &n) != 1 || n < 0) return 1;
    for (int i = 0; i < n; i++) { if (scanf("%d", &value) != 1) return 1; append(&head, value); }
    head = reverse(head);
    display(head);
    while (head) { Node *temp = head; head = head->next; free(temp); }
    return 0;
}
