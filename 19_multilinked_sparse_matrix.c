#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Node {
    int row;
    int column;
    int value;
    struct Node *right;
    struct Node *down;
} Node;

int main(void) {
    Node *rowHead[MAX_SIZE] = {NULL};
    Node *columnHead[MAX_SIZE] = {NULL};
    Node *allNodes[MAX_SIZE * MAX_SIZE];
    int rows, columns, count = 0;

    printf("Rows and columns (maximum %d): ", MAX_SIZE);
    scanf("%d%d", &rows, &columns);
    if (rows < 1 || columns < 1 || rows > MAX_SIZE || columns > MAX_SIZE)
        return 1;

    printf("Enter the matrix row by row:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int value;
            scanf("%d", &value);
            if (value == 0)
                continue;
            Node *node = (Node *)malloc(sizeof(Node));
            if (node == NULL)
                return 1;
            node->row = i;
            node->column = j;
            node->value = value;
            node->right = NULL;
            node->down = NULL;
            allNodes[count++] = node;

            Node **rowPosition = &rowHead[i];
            while (*rowPosition != NULL && (*rowPosition)->column < j)
                rowPosition = &((*rowPosition)->right);
            node->right = *rowPosition;
            *rowPosition = node;

            Node **columnPosition = &columnHead[j];
            while (*columnPosition != NULL && (*columnPosition)->row < i)
                columnPosition = &((*columnPosition)->down);
            node->down = *columnPosition;
            *columnPosition = node;
        }
    }

    printf("Row-wise traversal\n");
    for (int i = 0; i < rows; i++) {
        Node *current = rowHead[i];
        printf("Row %d: ", i);
        while (current != NULL) {
            printf("(%d,%d,%d) ", current->row, current->column, current->value);
            current = current->right;
        }
        printf("\n");
    }

    printf("Column-wise traversal\n");
    for (int j = 0; j < columns; j++) {
        Node *current = columnHead[j];
        printf("Column %d: ", j);
        while (current != NULL) {
            printf("(%d,%d,%d) ", current->row, current->column, current->value);
            current = current->down;
        }
        printf("\n");
    }

    for (int i = 0; i < count; i++)
        free(allNodes[i]);
    return 0;
}
