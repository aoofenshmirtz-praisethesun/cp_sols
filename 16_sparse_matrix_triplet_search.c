#include <stdio.h>

#define MAX_TERMS 1000

typedef struct {
    int row;
    int column;
    int value;
} Term;

int main(void) {
    Term matrix[MAX_TERMS];
    int rows, columns, count;
    int searchRow, searchColumn;

    printf("Rows, columns and number of non-zero values: ");
    scanf("%d%d%d", &rows, &columns, &count);
    if (count < 0 || count > MAX_TERMS) {
        printf("Invalid number of terms\n");
        return 1;
    }

    printf("Enter row, column and value for each non-zero term:\n");
    for (int i = 0; i < count; i++)
        scanf("%d%d%d", &matrix[i].row, &matrix[i].column, &matrix[i].value);

    printf("Triplet representation\n");
    printf("Rows = %d, Columns = %d, Non-zero = %d\n", rows, columns, count);
    for (int i = 0; i < count; i++)
        printf("%d %d %d\n", matrix[i].row, matrix[i].column, matrix[i].value);

    printf("Position to search (row column): ");
    scanf("%d%d", &searchRow, &searchColumn);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (matrix[i].row == searchRow && matrix[i].column == searchColumn) {
            printf("Value = %d\n", matrix[i].value);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("The position contains 0 or is not present\n");
    return 0;
}
