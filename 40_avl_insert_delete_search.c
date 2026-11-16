#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int key, height; struct Node *left, *right; } Node;

int max(int a, int b) { return a > b ? a : b; }
int height(Node *p) { return p ? p->height : 0; }
int balance(Node *p) { return p ? height(p->left) - height(p->right) : 0; }

Node *newNode(int key) {
    Node *p = malloc(sizeof(Node));
    if (!p) exit(1);
    p->key = key; p->height = 1; p->left = p->right = NULL;
    return p;
}

Node *rightRotate(Node *y) {
    Node *x = y->left, *t = x->right;
    x->right = y; y->left = t;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right, *t = y->left;
    y->left = x; x->right = t;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

Node *rebalance(Node *root) {
    root->height = 1 + max(height(root->left), height(root->right));
    int b = balance(root);
    if (b > 1 && balance(root->left) >= 0) return rightRotate(root);
    if (b > 1 && balance(root->left) < 0) { root->left = leftRotate(root->left); return rightRotate(root); }
    if (b < -1 && balance(root->right) <= 0) return leftRotate(root);
    if (b < -1 && balance(root->right) > 0) { root->right = rightRotate(root->right); return leftRotate(root); }
    return root;
}

Node *insert(Node *root, int key) {
    if (!root) return newNode(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    else return root;
    return rebalance(root);
}

Node *minimum(Node *root) { while (root && root->left) root = root->left; return root; }

Node *deleteNode(Node *root, int key) {
    if (!root) return NULL;
    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node *child = root->left ? root->left : root->right;
            free(root);
            return child;
        }
        Node *successor = minimum(root->right);
        root->key = successor->key;
        root->right = deleteNode(root->right, successor->key);
    }
    return rebalance(root);
}

Node *search(Node *root, int key) {
    while (root && root->key != key) root = key < root->key ? root->left : root->right;
    return root;
}

void inorder(Node *root) { if (root) { inorder(root->left); printf("%d(BF=%d) ", root->key, balance(root)); inorder(root->right); } }
void freeTree(Node *root) { if (root) { freeTree(root->left); freeTree(root->right); free(root); } }

int main(void) {
    Node *root = NULL;
    int queries, choice, key;
    if (scanf("%d", &queries) != 1 || queries < 0) return 1;
    for (int i = 0; i < queries; i++) {
        if (scanf("%d%d", &choice, &key) != 2) return 1;
        if (choice == 1) root = insert(root, key);
        else if (choice == 2) root = deleteNode(root, key);
        else if (choice == 3) printf(search(root, key) ? "Found\n" : "Not found\n");
        inorder(root); printf("\n");
    }
    freeTree(root);
    return 0;
}
