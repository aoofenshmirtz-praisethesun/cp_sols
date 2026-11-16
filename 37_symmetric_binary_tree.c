#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int data; struct Node *left, *right; } Node;

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

int mirror(Node *a, Node *b) {
    if (!a && !b) return 1;
    if (!a || !b || a->data != b->data) return 0;
    return mirror(a->left, b->right) && mirror(a->right, b->left);
}

void freeTree(Node *root) { if (root) { freeTree(root->left); freeTree(root->right); free(root); } }

int main(void) {
    Node *root = readTree();
    printf(mirror(root, root) ? "Symmetric tree\n" : "Not symmetric\n");
    freeTree(root);
    return 0;
}
