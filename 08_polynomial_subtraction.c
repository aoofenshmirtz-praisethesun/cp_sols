#include <stdio.h>
#include <stdlib.h>

typedef struct Term { int coefficient, exponent; struct Term *next; } Term;

void addTerm(Term **head, int c, int e) {
    if (c == 0) return;
    Term *previous = NULL, *current = *head;
    while (current && current->exponent > e) { previous = current; current = current->next; }
    if (current && current->exponent == e) {
        current->coefficient += c;
        if (current->coefficient == 0) {
            if (previous) previous->next = current->next; else *head = current->next;
            free(current);
        }
        return;
    }
    Term *node = malloc(sizeof(Term));
    if (!node) exit(1);
    node->coefficient = c; node->exponent = e; node->next = current;
    if (previous) previous->next = node; else *head = node;
}

Term *readPolynomial(void) {
    Term *head = NULL; int n, c, e;
    if (scanf("%d", &n) != 1 || n < 0) exit(1);
    for (int i = 0; i < n; i++) { if (scanf("%d%d", &c, &e) != 2) exit(1); addTerm(&head, c, e); }
    return head;
}

void display(Term *p) {
    if (!p) { printf("0\n"); return; }
    while (p) { printf("%+d", p->coefficient); if (p->exponent) printf("x^%d", p->exponent); p = p->next; }
    printf("\n");
}

int main(void) {
    Term *a = readPolynomial(), *b = readPolynomial(), *result = NULL;
    for (Term *p = a; p; p = p->next) addTerm(&result, p->coefficient, p->exponent);
    for (Term *p = b; p; p = p->next) addTerm(&result, -p->coefficient, p->exponent);
    display(result);
    Term *lists[] = {a, b, result};
    for (int i = 0; i < 3; i++) while (lists[i]) { Term *temp = lists[i]; lists[i] = lists[i]->next; free(temp); }
    return 0;
}
