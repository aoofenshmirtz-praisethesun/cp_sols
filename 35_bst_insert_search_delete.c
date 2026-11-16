#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
        exit(1);
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *insert(Node *root, int value) {
    if (root == NULL)
        return createNode(value);
    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    return root;
}

Node *search(Node *root, int value) {
    if (root == NULL || root->data == value)
        return root;
    if (value < root->data)
        return search(root->left, value);
    return search(root->right, value);
}

Node *minimumNode(Node *root) {
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}

Node *deleteNode(Node *root, int value) {
    if (root == NULL)
        return NULL;
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            Node *right = root->right;
            free(root);
            return right;
        }
        if (root->right == NULL) {
            Node *left = root->left;
            free(root);
            return left;
        }
        Node *successor = minimumNode(root->right);
        root->data = successor->data;
        root->right = deleteNode(root->right, successor->data);
    }
    return root;
}

void inorder(Node *root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void freeTree(Node *root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    int keys[] = {14, 18, 10, 15, 6, 20, 35, 46, 9, 2};
    int count = (int)(sizeof(keys) / sizeof(keys[0]));
    Node *root = NULL;
    for (int i = 0; i < count; i++)
        root = insert(root, keys[i]);

    printf("BST inorder traversal: ");
    inorder(root);
    printf("\nEnter a key to search: ");
    int key;
    scanf("%d", &key);
    printf(search(root, key) ? "Key found\n" : "Key not found\n");

    printf("Enter a key to delete: ");
    scanf("%d", &key);
    root = deleteNode(root, key);
    printf("After deletion: ");
    inorder(root);
    printf("\n");
    freeTree(root);
    return 0;
}
