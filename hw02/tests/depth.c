
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "../stats.h"

int main(int argc, char *argv[])
{
    char *end;
    long requested;
    int n;
    float *a;
    float result;

    if (argc != 3) {
        fprintf(stderr, "usage: %s max|tail n\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "max") != 0 &&
        strcmp(argv[1], "tail") != 0) {
        fprintf(stderr, "error: use max or tail\n");
        return 1;
    }

    errno = 0;
    requested = strtol(argv[2], &end, 10);

    if (errno != 0 || end == argv[2] || *end != '\0' ||
        requested < 1 || requested > INT_MAX) {
        fprintf(stderr, "error: invalid value count\n");
        return 1;
    }

    n = (int)requested;

    a = malloc((size_t)n * sizeof *a);
    if (a == NULL) {
        fprintf(stderr, "error: could not allocate array\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        a[i] = (float)i;
    }

    if (strcmp(argv[1], "max") == 0) {
        result = stats_max(a, n);
    } else {
        result = stats_max_tail(a, n);
    }

    printf("%s: n = %d, maximum = %.1f\n",
           argv[1], n, result);

    free(a);
    return 0;
}