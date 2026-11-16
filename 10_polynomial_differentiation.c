#include <stdio.h>
#include <stdlib.h>

typedef struct Term { int coefficient, exponent; struct Term *next; } Term;

int main(void) {
    Term *head = NULL, *tail = NULL;
    int n, c, e;
    if (scanf("%d", &n) != 1 || n < 0) return 1;
    for (int i = 0; i < n; i++) {
        if (scanf("%d%d", &c, &e) != 2) return 1;
        if (e == 0 || c == 0) continue;
        Term *node = malloc(sizeof(Term));
        if (!node) return 1;
        node->coefficient = c * e;
        node->exponent = e - 1;
        node->next = NULL;
        if (!head) head = node; else tail->next = node;
        tail = node;
    }
    if (!head) printf("0\n");
    while (head) {
        printf("%+dx^%d", head->coefficient, head->exponent);
        head = head->next;
    }
    printf("\n");
    return 0;
}
