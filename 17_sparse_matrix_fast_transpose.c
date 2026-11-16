#include <stdio.h>

#define MAX_TERMS 1000
#define MAX_DIMENSION 1000

typedef struct {
    int row;
    int column;
    int value;
} Term;

int main(void) {
    Term a[MAX_TERMS], b[MAX_TERMS];
    int rows, columns, count;
    int rowTerms[MAX_DIMENSION] = {0};
    int startingPosition[MAX_DIMENSION] = {0};

    printf("Rows, columns and non-zero count: ");
    scanf("%d%d%d", &rows, &columns, &count);
    if (rows > MAX_DIMENSION || columns > MAX_DIMENSION || count > MAX_TERMS || count < 0) {
        printf("Input is too large\n");
        return 1;
    }

    for (int i = 0; i < count; i++)
        scanf("%d%d%d", &a[i].row, &a[i].column, &a[i].value);

    for (int i = 0; i < count; i++)
        rowTerms[a[i].column]++;

    startingPosition[0] = 0;
    for (int i = 1; i < columns; i++)
        startingPosition[i] = startingPosition[i - 1] + rowTerms[i - 1];

    for (int i = 0; i < count; i++) {
        int position = startingPosition[a[i].column]++;
        b[position].row = a[i].column;
        b[position].column = a[i].row;
        b[position].value = a[i].value;
    }

    printf("Transpose triplets\n");
    for (int i = 0; i < count; i++)
        printf("%d %d %d\n", b[i].row, b[i].column, b[i].value);
    return 0;
}
