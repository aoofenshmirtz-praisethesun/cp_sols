#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
    int coefficient;
    int exponent;
    struct Term *next;
} Term;

Term *newTerm(int coefficient, int exponent) {
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

void insertSorted(Term **head, int coefficient, int exponent) {
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
    Term *node = newTerm(coefficient, exponent);
    node->next = current;
    if (previous == NULL)
        *head = node;
    else
        previous->next = node;
}

Term *readPolynomial(void) {
    Term *head = NULL;
    int n, coefficient, exponent;
    printf("Number of terms: ");
    scanf("%d", &n);
    printf("Enter coefficient and exponent:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &coefficient, &exponent);
        insertSorted(&head, coefficient, exponent);
    }
    return head;
}

Term *addPolynomial(Term *a, Term *b) {
    Term *result = NULL;
    while (a != NULL) {
        insertSorted(&result, a->coefficient, a->exponent);
        a = a->next;
    }
    while (b != NULL) {
        insertSorted(&result, b->coefficient, b->exponent);
        b = b->next;
    }
    return result;
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
    printf("First polynomial\n");
    Term *a = readPolynomial();
    printf("Second polynomial\n");
    Term *b = readPolynomial();
    Term *sum = addPolynomial(a, b);
    printf("Sum: ");
    display(sum);
    freePolynomial(a);
    freePolynomial(b);
    freePolynomial(sum);
    return 0;
}
