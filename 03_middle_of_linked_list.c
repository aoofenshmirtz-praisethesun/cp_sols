#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int data; struct Node *next; } Node;

int main(void) {
    Node *head = NULL, *tail = NULL;
    int n, value;
    if (scanf("%d", &n) != 1 || n <= 0) return 1;
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &value) != 1) return 1;
        Node *node = malloc(sizeof(Node));
        if (!node) return 1;
        node->data = value;
        node->next = NULL;
        if (!head) head = node; else tail->next = node;
        tail = node;
    }
    Node *slow = head, *fast = head;
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
    printf("Middle node: %d\n", slow->data);
    while (head) { Node *temp = head; head = head->next; free(temp); }
    return 0;
}
