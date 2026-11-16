#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
    int coefficient;
    int exponent;
    struct Term *next;
} Term;

Term *createTerm(int coefficient, int exponent) {
    Term *node = (Term *)malloc(sizeof(Term));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    node->coefficient = coefficient;
    node->exponent = exponent;
    node->next = NULL;
    return node;
}

void insertTerm(Term **head, int coefficient, int exponent) {
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
    Term *node = createTerm(coefficient, exponent);
    node->next = current;
    if (previous == NULL)
        *head = node;
    else
        previous->next = node;
}

void display(Term *head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    while (head != NULL) {
        printf("%+d", head->coefficient);
        if (head->exponent != 0)
            printf("x^%d", head->exponent);
        head = head->next;
        if (head != NULL)
            printf(" ");
    }
    printf("\n");
}

void freePolynomial(Term *head) {
    while (head != NULL) {
        Term *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Term *polynomial = NULL;
    int n, coefficient, exponent;

    printf("Number of terms: ");
    scanf("%d", &n);
    printf("Enter coefficient and exponent for each term:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &coefficient, &exponent);
        insertTerm(&polynomial, coefficient, exponent);
    }

    printf("Polynomial: ");
    display(polynomial);
    freePolynomial(polynomial);
    return 0;
}
