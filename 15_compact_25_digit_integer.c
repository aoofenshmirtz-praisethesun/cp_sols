#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node { int group; struct Node *next; } Node;

int main(void) {
    char number[128];
    Node *head = NULL, *tail = NULL;
    if (scanf("%127s", number) != 1) return 1;
    int length = (int)strlen(number);
    if (length != 25) return 1;
    int first = length % 3;
    if (first == 0) first = 3;
    int position = 0;
    while (position < length) {
        int take = position == 0 ? first : 3;
        int value = 0;
        for (int i = 0; i < take; i++) {
            char ch = number[position++];
            if (ch < '0' || ch > '9') return 1;
            value = value * 10 + ch - '0';
        }
        Node *node = malloc(sizeof(Node));
        if (!node) return 1;
        node->group = value; node->next = NULL;
        if (!head) head = node; else tail->next = node;
        tail = node;
    }
    int index = 0;
    for (Node *p = head; p; p = p->next) {
        if (index++ == 0) printf("%d", p->group);
        else printf("%03d", p->group);
    }
    printf("\n");
    while (head) { Node *temp = head; head = head->next; free(temp); }
    return 0;
}
