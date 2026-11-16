#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int digit;
    struct Node *next;
} Node;

Node *append(Node **head, Node **tail, int digit) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    node->digit = digit;
    node->next = NULL;
    if (*head == NULL)
        *head = node;
    else
        (*tail)->next = node;
    *tail = node;
    return node;
}

Node *makeNumber(const char *text) {
    Node *head = NULL;
    Node *tail = NULL;
    int length = (int)strlen(text);
    for (int i = 0; i < length; i++) {
        if (text[i] < '0' || text[i] > '9') {
            printf("Only positive decimal integers are allowed\n");
            exit(1);
        }
        append(&head, &tail, text[i] - '0');
    }
    return head;
}

Node *reverse(Node *head) {
    Node *previous = NULL;
    while (head != NULL) {
        Node *next = head->next;
        head->next = previous;
        previous = head;
        head = next;
    }
    return previous;
}

void printNumber(Node *head) {
    Node *digits[100005];
    int count = 0;
    while (head != NULL && count < 100005) {
        digits[count++] = head;
        head = head->next;
    }
    while (count > 0)
        printf("%d", digits[--count]->digit);
    printf("\n");
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    char first[100001], second[100001];
    printf("First large integer: ");
    if (scanf("%100000s", first) != 1) return 1;
    printf("Second large integer: ");
    if (scanf("%100000s", second) != 1) return 1;

    Node *aOriginal = makeNumber(first);
    Node *bOriginal = makeNumber(second);
    Node *aReversed = reverse(aOriginal);
    Node *bReversed = reverse(bOriginal);
    Node *a = aReversed;
    Node *b = bReversed;
    Node *sum = NULL;
    Node *tail = NULL;
    int carry = 0;

    while (a != NULL || b != NULL || carry != 0) {
        int value = carry;
        if (a != NULL) { value += a->digit; a = a->next; }
        if (b != NULL) { value += b->digit; b = b->next; }
        append(&sum, &tail, value % 10);
        carry = value / 10;
    }

    printf("Sum: ");
    printNumber(sum);

    freeList(aReversed);
    freeList(bReversed);
    freeList(sum);
    return 0;
}
