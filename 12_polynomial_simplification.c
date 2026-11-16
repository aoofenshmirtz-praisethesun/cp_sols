#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
    int coefficient;
    int exponent;
    struct Term *next;
} Term;

void insertOrAdd(Term **head, int coefficient, int exponent) {
    if (coefficient == 0)
        return;
    Term *current = *head;
    Term *previous = NULL;
    while (current != NULL && current->exponent > exponent) {
        previous = current;
        current = current->next;
    }
    if (current != NULL && current->exponent == exponent) {
        current->coefficient += coefficient;
        if (current->coefficient == 0) {
            if (previous == NULL)
                *head = current->next;
            else
                previous->next = current->next;
            free(current);
        }
        return;
    }
    Term *node = (Term *)malloc(sizeof(Term));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    node->coefficient = coefficient;
    node->exponent = exponent;
    node->next = current;
    if (previous == NULL)
        *head = node;
    else
        previous->next = node;
}

int main(void) {
    Term *head = NULL;
    int n, coefficient, exponent;
    printf("Number of input terms: ");
    scanf("%d", &n);
    printf("Enter terms in any order as coefficient exponent:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &coefficient, &exponent);
        insertOrAdd(&head, coefficient, exponent);
    }

    printf("Simplified polynomial: ");
    if (head == NULL)
        printf("0");
    while (head != NULL) {
        printf("%+d", head->coefficient);
        if (head->exponent != 0)
            printf("x^%d", head->exponent);
        head = head->next;
        if (head != NULL)
            printf(" ");
    }
    printf("\n");
    return 0;
}
