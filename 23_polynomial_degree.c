#include <stdio.h>

int main(void) {
    int n, coefficient, exponent, degree = 0, found = 0;
    if (scanf("%d", &n) != 1 || n < 0) return 1;
    for (int i = 0; i < n; i++) {
        if (scanf("%d%d", &coefficient, &exponent) != 2) return 1;
        if (coefficient != 0 && (!found || exponent > degree)) { degree = exponent; found = 1; }
    }
    if (found) printf("Degree = %d\n", degree);
    else printf("Zero polynomial has no degree\n");
    return 0;
}
