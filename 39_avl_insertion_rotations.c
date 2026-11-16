#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char key;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

int max(int a, int b) {
    return a > b ? a : b;
}

int height(Node *node) {
    return node == NULL ? 0 : node->height;
}

int balance(Node *node) {
    return node == NULL ? 0 : height(node->left) - height(node->right);
}

Node *newNode(char key) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) exit(1);
    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *rightRotate(Node *root) {
    Node *child = root->left;
    Node *middle = child->right;
    child->right = root;
    root->left = middle;
    root->height = 1 + max(height(root->left), height(root->right));
    child->height = 1 + max(height(child->left), height(child->right));
    return child;
}

Node *leftRotate(Node *root) {
    Node *child = root->right;
    Node *middle = child->left;
    child->left = root;
    root->right = middle;
    root->height = 1 + max(height(root->left), height(root->right));
    child->height = 1 + max(height(child->left), height(child->right));
    return child;
}

Node *insert(Node *root, char key) {
    if (root == NULL) return newNode(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    else return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int bf = balance(root);

    if (bf > 1 && key < root->left->key) return rightRotate(root);
    if (bf < -1 && key > root->right->key) return leftRotate(root);
    if (bf > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void inorder(Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%c(BF=%d) ", root->key, balance(root));
    inorder(root->right);
}

void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    char keys[] = {'F', 'S', 'Q', 'K', 'C', 'L', 'H', 'T', 'V', 'W', 'M', 'R', 'N', 'P', 'A', 'B', 'X', 'Y', 'D', 'Z', 'E'};
    int count = (int)(sizeof(keys) / sizeof(keys[0]));
    Node *root = NULL;

    for (int i = 0; i < count; i++) {
        root = insert(root, keys[i]);
        printf("After inserting %c: ", keys[i]);
        inorder(root);
        printf("\n");
    }

    freeTree(root);
    return 0;
}
