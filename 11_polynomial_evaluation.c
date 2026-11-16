#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Term {
    double coefficient;
    int exponent;
    struct Term *next;
} Term;

void insertTerm(Term **head, double coefficient, int exponent) {
    Term *node = (Term *)malloc(sizeof(Term));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    node->coefficient = coefficient;
    node->exponent = exponent;
    node->next = NULL;
    if (*head == NULL) {
        *head = node;
        return;
    }
    Term *current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = node;
}

int main(void) {
    Term *head = NULL;
    int n, exponent;
    double coefficient, x, answer = 0.0;

    printf("Number of terms: ");
    scanf("%d", &n);
    printf("Enter coefficient and exponent:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf%d", &coefficient, &exponent);
        insertTerm(&head, coefficient, exponent);
    }

    printf("Enter x: ");
    scanf("%lf", &x);

    Term *current = head;
    while (current != NULL) {
        answer += current->coefficient * pow(x, current->exponent);
        current = current->next;
    }

    printf("Polynomial value = %.6f\n", answer);

    while (head != NULL) {
        Term *temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}
