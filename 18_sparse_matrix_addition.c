#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int row;
    int column;
    int value;
    struct Node *next;
} Node;

void addTerm(Node **head, int row, int column, int value) {
    if (value == 0)
        return;
    Node **position = head;
    while (*position != NULL &&
           ((*position)->row < row ||
            ((*position)->row == row && (*position)->column < column)))
        position = &((*position)->next);
    if (*position != NULL && (*position)->row == row && (*position)->column == column) {
        (*position)->value += value;
        if ((*position)->value == 0) {
            Node *temp = *position;
            *position = temp->next;
            free(temp);
        }
        return;
    }
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
        exit(1);
    node->row = row;
    node->column = column;
    node->value = value;
    node->next = *position;
    *position = node;
}

Node *readSparseMatrix(int rows, int columns) {
    Node *head = NULL;
    int count, row, column, value;
    printf("Number of non-zero terms: ");
    scanf("%d", &count);
    printf("Enter row column value:\n");
    for (int i = 0; i < count; i++) {
        scanf("%d%d%d", &row, &column, &value);
        if (row >= 0 && row < rows && column >= 0 && column < columns)
            addTerm(&head, row, column, value);
    }
    return head;
}

Node *addMatrices(Node *a, Node *b) {
    Node *result = NULL;
    while (a != NULL) {
        addTerm(&result, a->row, a->column, a->value);
        a = a->next;
    }
    while (b != NULL) {
        addTerm(&result, b->row, b->column, b->value);
        b = b->next;
    }
    return result;
}

void display(Node *head) {
    if (head == NULL) {
        printf("No non-zero elements\n");
        return;
    }
    printf("row column value\n");
    while (head != NULL) {
        printf("%d %d %d\n", head->row, head->column, head->value);
        head = head->next;
    }
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    int rows, columns;
    printf("Rows and columns: ");
    scanf("%d%d", &rows, &columns);
    printf("First matrix\n");
    Node *a = readSparseMatrix(rows, columns);
    printf("Second matrix\n");
    Node *b = readSparseMatrix(rows, columns);
    Node *sum = addMatrices(a, b);
    printf("Sum in linked-list triplet form\n");
    display(sum);
    freeList(a);
    freeList(b);
    freeList(sum);
    return 0;
}
