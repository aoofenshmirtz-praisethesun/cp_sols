#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *readTree(void) {
    int value;
    if (scanf("%d", &value) != 1) exit(1);
    if (value == -1) return NULL;
    Node *root = malloc(sizeof(Node));
    if (!root) exit(1);
    root->data = value;
    root->left = readTree();
    root->right = readTree();
    return root;
}

int heightOrUnbalanced(Node *root) {
    if (!root) return 0;
    int leftHeight = heightOrUnbalanced(root->left);
    if (leftHeight == -1) return -1;
    int rightHeight = heightOrUnbalanced(root->right);
    if (rightHeight == -1) return -1;
    if (leftHeight - rightHeight > 1 || rightHeight - leftHeight > 1) return -1;
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    Node *root = readTree();
    printf(heightOrUnbalanced(root) == -1 ? "Not height-balanced\n" : "Height-balanced\n");
    freeTree(root);
    return 0;
}
