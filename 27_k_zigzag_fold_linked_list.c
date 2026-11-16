#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, k;
    if (scanf("%d", &n) != 1 || n <= 0) return 1;
    int *values = malloc((size_t)n * sizeof(int));
    if (!values) return 1;
    for (int i = 0; i < n; i++) if (scanf("%d", &values[i]) != 1) { free(values); return 1; }
    if (scanf("%d", &k) != 1 || k <= 0 || n % k != 0) { free(values); return 1; }
    int width = n / k;
    for (int column = 0; column < width; column++) {
        long long product = 1;
        for (int group = 0; group < k; group++) {
            int index = group * width + ((group % 2 == 0) ? column : width - 1 - column);
            product *= values[index];
        }
        printf("%lld", product);
        if (column + 1 < width) printf(" -> ");
    }
    printf(" -> NULL\n");
    free(values);
    return 0;
}
