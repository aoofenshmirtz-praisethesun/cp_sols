#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int digit;
    struct Node *next;
} Node;

Node *makeNumber(const char *text) {
    Node *head = NULL;
    Node *tail = NULL;
    int start = 0;
    while (text[start] == '0' && text[start + 1] != '\0')
        start++;
    for (int i = start; text[i] != '\0'; i++) {
        if (text[i] < '0' || text[i] > '9') {
            printf("Invalid number\n");
            exit(1);
        }
        Node *node = (Node *)malloc(sizeof(Node));
        if (node == NULL)
            exit(1);
        node->digit = text[i] - '0';
        node->next = NULL;
        if (head == NULL)
            head = node;
        else
            tail->next = node;
        tail = node;
    }
    return head;
}

int length(Node *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

int compareNumbers(Node *a, Node *b) {
    int lenA = length(a);
    int lenB = length(b);
    if (lenA > lenB)
        return 1;
    if (lenA < lenB)
        return -1;
    while (a != NULL && b != NULL) {
        if (a->digit > b->digit)
            return 1;
        if (a->digit < b->digit)
            return -1;
        a = a->next;
        b = b->next;
    }
    return 0;
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
    printf("First integer: ");
    if (scanf("%100000s", first) != 1) return 1;
    printf("Second integer: ");
    if (scanf("%100000s", second) != 1) return 1;

    Node *a = makeNumber(first);
    Node *b = makeNumber(second);
    int result = compareNumbers(a, b);
    if (result > 0) printf("First number is greater\n");
    else if (result < 0) printf("Second number is greater\n");
    else printf("Both numbers are equal\n");

    freeList(a);
    freeList(b);
    return 0;
}
