#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct Node { int value; struct Node *next, *child; } Node;

Node *flatten(Node *head) {
    Node *current = head, *tail = head;
    while (current) {
        Node *next = current->next;
        if (current->child) {
            Node *childHead = current->child;
            Node *childTail = flatten(childHead);
            current->next = childHead;
            current->child = NULL;
            childTail->next = next;
            tail = childTail;
            current = childTail;
        } else tail = current;
        current = current->next;
    }
    return tail;
}

int main(void) {
    Node *nodes[MAX + 1];
    int hasIncoming[MAX + 1] = {0};
    int n;
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) return 1;
    for (int i = 1; i <= n; i++) {
        nodes[i] = malloc(sizeof(Node));
        if (!nodes[i]) return 1;
        if (scanf("%d", &nodes[i]->value) != 1) return 1;
        nodes[i]->next = nodes[i]->child = NULL;
    }
    for (int i = 1; i <= n; i++) {
        int nextIndex, childIndex;
        if (scanf("%d%d", &nextIndex, &childIndex) != 2) return 1;
        if (nextIndex < 0 || nextIndex > n || childIndex < 0 || childIndex > n) return 1;
        if (nextIndex) { nodes[i]->next = nodes[nextIndex]; hasIncoming[nextIndex] = 1; }
        if (childIndex) { nodes[i]->child = nodes[childIndex]; hasIncoming[childIndex] = 1; }
    }
    int start = 1;
    for (int i = 1; i <= n; i++) if (!hasIncoming[i]) { start = i; break; }
    Node *head = nodes[start];
    Node *tail = flatten(head);
    for (Node *p = head; p; p = p->next) printf("%d ", p->value);
    printf("\n");
    if (tail) tail->next = NULL;
    for (int i = 1; i <= n; i++) free(nodes[i]);
    return 0;
}
