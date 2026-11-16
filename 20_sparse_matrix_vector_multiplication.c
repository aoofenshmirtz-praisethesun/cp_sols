#include <stdio.h>

#define MAX 1000

typedef struct { int row, column, value; } Term;

int main(void) {
    Term terms[MAX];
    int rows, columns, count, vector[MAX], result[MAX] = {0};
    if (scanf("%d%d%d", &rows, &columns, &count) != 3) return 1;
    if (rows < 0 || rows > MAX || columns < 0 || columns > MAX || count < 0 || count > MAX) return 1;
    for (int i = 0; i < count; i++) {
        if (scanf("%d%d%d", &terms[i].row, &terms[i].column, &terms[i].value) != 3) return 1;
        if (terms[i].row < 0 || terms[i].row >= rows || terms[i].column < 0 || terms[i].column >= columns) return 1;
    }
    for (int i = 0; i < columns; i++) if (scanf("%d", &vector[i]) != 1) return 1;
    for (int i = 0; i < count; i++) result[terms[i].row] += terms[i].value * vector[terms[i].column];
    for (int i = 0; i < rows; i++) printf("%d\n", result[i]);
    return 0;
}
