#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int data; struct Node *next; } Node;

void append(Node **head, Node **tail, int value) {
    Node *node = malloc(sizeof(Node));
    if (!node) exit(1);
    node->data = value;
    node->next = NULL;
    if (!*head) *head = node; else (*tail)->next = node;
    *tail = node;
}

Node *merge(Node *a, Node *b) {
    Node dummy;
    Node *tail = &dummy;
    dummy.next = NULL;
    while (a && b) {
        if (a->data <= b->data) { tail->next = a; a = a->next; }
        else { tail->next = b; b = b->next; }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}

void display(Node *head) {
    while (head) { printf("%d ", head->data); head = head->next; }
    printf("\n");
}

void freeList(Node *head) {
    while (head) { Node *temp = head; head = head->next; free(temp); }
}

int main(void) {
    Node *a = NULL, *at = NULL, *b = NULL, *bt = NULL;
    int n, m, value;
    if (scanf("%d", &n) != 1 || n < 0) return 1;
    for (int i = 0; i < n; i++) { if (scanf("%d", &value) != 1) return 1; append(&a, &at, value); }
    if (scanf("%d", &m) != 1 || m < 0) return 1;
    for (int i = 0; i < m; i++) { if (scanf("%d", &value) != 1) return 1; append(&b, &bt, value); }
    Node *result = merge(a, b);
    display(result);
    freeList(result);
    return 0;
}
