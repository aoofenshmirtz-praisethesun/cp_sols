#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int key; struct Node *left, *right; } Node;

Node *insert(Node *root, int key) {
    if (!root) { root = malloc(sizeof(Node)); if (!root) exit(1); root->key = key; root->left = root->right = NULL; }
    else if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    return root;
}

void preorder(Node *root) { if (root) { printf("%d ", root->key); preorder(root->left); preorder(root->right); } }
void inorder(Node *root) { if (root) { inorder(root->left); printf("%d ", root->key); inorder(root->right); } }
void postorder(Node *root) { if (root) { postorder(root->left); postorder(root->right); printf("%d ", root->key); } }
void freeTree(Node *root) { if (root) { freeTree(root->left); freeTree(root->right); free(root); } }

int main(void) {
    int keys[] = {14, 18, 10, 15, 6, 20, 35, 46, 9, 2};
    int n = (int)(sizeof(keys) / sizeof(keys[0]));
    Node *root = NULL;
    for (int i = 0; i < n; i++) root = insert(root, keys[i]);
    printf("Preorder: "); preorder(root);
    printf("\nInorder: "); inorder(root);
    printf("\nPostorder: "); postorder(root);
    printf("\n");
    freeTree(root);
    return 0;
}
