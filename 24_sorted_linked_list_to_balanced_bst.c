#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode { int value; struct ListNode *next; } ListNode;
typedef struct TreeNode { int value; struct TreeNode *left, *right; } TreeNode;

TreeNode *build(ListNode **current, int count) {
    if (count <= 0) return NULL;
    TreeNode *left = build(current, count / 2);
    TreeNode *root = malloc(sizeof(TreeNode));
    if (!root) exit(1);
    root->value = (*current)->value;
    root->left = left;
    *current = (*current)->next;
    root->right = build(current, count - count / 2 - 1);
    return root;
}

void preorder(TreeNode *root) { if (root) { printf("%d ", root->value); preorder(root->left); preorder(root->right); } }
void freeList(ListNode *p) { while (p) { ListNode *t = p; p = p->next; free(t); } }
void freeTree(TreeNode *p) { if (p) { freeTree(p->left); freeTree(p->right); free(p); } }

int main(void) {
    ListNode *head = NULL, *tail = NULL;
    int n, value;
    if (scanf("%d", &n) != 1 || n < 0) return 1;
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &value) != 1) return 1;
        ListNode *node = malloc(sizeof(ListNode));
        if (!node) return 1;
        node->value = value; node->next = NULL;
        if (!head) head = node; else tail->next = node;
        tail = node;
    }
    ListNode *current = head;
    TreeNode *root = build(&current, n);
    preorder(root); printf("\n");
    freeList(head); freeTree(root);
    return 0;
}
