#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int value; struct Node *next; } Node;

void append(Node **head, Node **tail, int value) {
    Node *p = malloc(sizeof(Node)); if (!p) exit(1);
    p->value = value; p->next = NULL;
    if (!*head) *head = p; else (*tail)->next = p;
    *tail = p;
}

Node *reverseK(Node *head, int k) {
    Node *check = head;
    for (int i = 0; i < k; i++) { if (!check) return head; check = check->next; }
    Node *previous = NULL, *current = head;
    for (int i = 0; i < k; i++) { Node *next = current->next; current->next = previous; previous = current; current = next; }
    head->next = reverseK(current, k);
    return previous;
}

int main(void) {
    Node *head = NULL, *tail = NULL;
    int n, k, value;
    if (scanf("%d", &n) != 1 || n < 0) return 1;
    for (int i = 0; i < n; i++) { if (scanf("%d", &value) != 1) return 1; append(&head, &tail, value); }
    if (scanf("%d", &k) != 1 || k <= 0) return 1;
    head = reverseK(head, k);
    for (Node *p = head; p; p = p->next) printf("%d ", p->value);
    printf("\n");
    while (head) { Node *t = head; head = head->next; free(t); }
    return 0;
}
