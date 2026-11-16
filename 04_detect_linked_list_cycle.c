#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int data; struct Node *next; } Node;

int main(void) {
    Node *head = NULL, *tail = NULL;
    int n, value, position;
    if (scanf("%d", &n) != 1 || n < 0) return 1;
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &value) != 1) return 1;
        Node *node = malloc(sizeof(Node));
        if (!node) return 1;
        node->data = value;
        node->next = NULL;
        if (!head) head = node; else tail->next = node;
        tail = node;
    }
    if (n == 0) { printf("No cycle\n"); return 0; }
    if (scanf("%d", &position) != 1) return 1;
    if (position >= 0 && position < n) {
        Node *target = head;
        for (int i = 0; i < position; i++) target = target->next;
        tail->next = target;
    }
    Node *slow = head, *fast = head;
    int found = 0;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) { found = 1; break; }
    }
    printf(found ? "Cycle detected\n" : "No cycle\n");
    if (found) {
        slow = head;
        while (slow != fast) { slow = slow->next; fast = fast->next; }
        printf("Cycle starts at node value: %d\n", slow->data);
    }
    if (tail) tail->next = NULL;
    while (head) { Node *temp = head; head = head->next; free(temp); }
    return 0;
}
