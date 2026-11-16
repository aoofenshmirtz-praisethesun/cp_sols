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

int identical(Node *a, Node *b) {
    if (a == NULL && b == NULL) return 1;
    if (a == NULL || b == NULL || a->data != b->data) return 0;
    return identical(a->left, b->left) && identical(a->right, b->right);
}

void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    Node *first = readTree();
    Node *second = readTree();
    printf(identical(first, second) ? "Identical trees\n" : "Not identical\n");
    freeTree(first);
    freeTree(second);
    return 0;
}
