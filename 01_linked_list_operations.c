#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *createNode(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    node->data = value;
    node->next = NULL;
    return node;
}

void insertEnd(Node **head, int value) {
    Node *node = createNode(value);
    if (*head == NULL) {
        *head = node;
        return;
    }
    Node *current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = node;
}

void insertAtPosition(Node **head, int value, int position) {
    Node *node = createNode(value);
    if (position <= 1 || *head == NULL) {
        node->next = *head;
        *head = node;
        return;
    }
    Node *current = *head;
    int i = 1;
    while (current->next != NULL && i < position - 1) {
        current = current->next;
        i++;
    }
    node->next = current->next;
    current->next = node;
}

void deleteValue(Node **head, int value) {
    if (*head == NULL)
        return;
    Node *current = *head;
    if (current->data == value) {
        *head = current->next;
        free(current);
        return;
    }
    while (current->next != NULL && current->next->data != value)
        current = current->next;
    if (current->next != NULL) {
        Node *temp = current->next;
        current->next = temp->next;
        free(temp);
    }
}

void display(Node *head) {
    while (head != NULL) {
        printf("%d", head->data);
        if (head->next != NULL)
            printf(" -> ");
        head = head->next;
    }
    printf(" -> NULL\n");
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Node *head = NULL;
    int n, value, choice, position;

    printf("Number of initial nodes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        insertEnd(&head, value);
    }

    do {
        printf("\n1 Insert at end\n2 Insert at position\n3 Delete value\n4 Display\n0 Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Value: ");
            scanf("%d", &value);
            insertEnd(&head, value);
        } else if (choice == 2) {
            printf("Value and position: ");
            scanf("%d%d", &value, &position);
            insertAtPosition(&head, value, position);
        } else if (choice == 3) {
            printf("Value to delete: ");
            scanf("%d", &value);
            deleteValue(&head, value);
        } else if (choice == 4) {
            display(head);
        }
    } while (choice != 0);

    freeList(head);
    return 0;
}
