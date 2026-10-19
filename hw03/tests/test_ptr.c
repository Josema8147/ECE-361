
#include "../ptr.h"

#include <stddef.h>
#include <stdio.h>

static int passed = 0;
static int failed = 0;

static void check(int condition, const char *name)
{
    if (condition) {
        printf("PASS: %s\n", name);
        passed++;
    } else {
        printf("FAIL: %s\n", name);
        failed++;
    }
}

static int float_equal(float a, float b)
{
    const float epsilon = 0.0001f;
    return (a - b < epsilon) && (b - a < epsilon);
}

static int array_equal(const float *a, const float *b, int n)
{
    for (int i = 0; i < n; i++) {
        if (!float_equal(*(a + i), *(b + i))) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    /* Test 1: swap_float */
    {
        float a = 1.5f;
        float b = 9.5f;

        swap_float(&a, &b);

        check(float_equal(a, 9.5f) && float_equal(b, 1.5f),
              "swap_float exchanges two values");
    }

    /* Test 2: minmax with several values */
    {
        const float values[] = {3.0f, -2.0f, 8.5f, 4.0f};
        float min = 0.0f;
        float max = 0.0f;

        int result = minmax(values, 4, &min, &max);

        check(result == 0 &&
              float_equal(min, -2.0f) &&
              float_equal(max, 8.5f),
              "minmax finds minimum and maximum");
    }

    /* Test 3: minmax with one value */
    {
        const float values[] = {7.25f};
        float min = 0.0f;
        float max = 0.0f;

        int result = minmax(values, 1, &min, &max);

        check(result == 0 &&
              float_equal(min, 7.25f) &&
              float_equal(max, 7.25f),
              "minmax with one value");
    }

    /* Test 4: minmax with n = 0 */
    {
        const float values[] = {1.0f};
        float min = 10.0f;
        float max = 20.0f;

        int result = minmax(values, 0, &min, &max);

        check(result == -1 &&
              float_equal(min, 10.0f) &&
              float_equal(max, 20.0f),
              "minmax rejects n = 0 and preserves outputs");
    }

    /* Test 5: minmax with NULL array */
    {
        float min = 10.0f;
        float max = 20.0f;

        int result = minmax(NULL, 3, &min, &max);

        check(result == -1 &&
              float_equal(min, 10.0f) &&
              float_equal(max, 20.0f),
              "minmax rejects NULL array and preserves outputs");
    }

    /* Test 6: minmax with NULL minimum output */
    {
        const float values[] = {1.0f, 2.0f};
        float max = 20.0f;

        int result = minmax(values, 2, NULL, &max);

        check(result == -1 && float_equal(max, 20.0f),
              "minmax rejects NULL minimum output");
    }

    /* Test 7: minmax with NULL maximum output */
    {
        const float values[] = {1.0f, 2.0f};
        float min = 10.0f;

        int result = minmax(values, 2, &min, NULL);

        check(result == -1 && float_equal(min, 10.0f),
              "minmax rejects NULL maximum output");
    }

    /* Test 8: find_above with two matches */
    {
        const float values[] = {1.0f, 5.0f, 8.0f, 10.0f};
        const float *result = find_above(values, 4, 4.0f);

        check(result == values + 1 && float_equal(*result, 5.0f),
              "find_above returns the first of two matches");
    }

    /* Test 9: find_above with no matches */
    {
        const float values[] = {1.0f, 2.0f, 3.0f};
        const float *result = find_above(values, 3, 5.0f);

        check(result == NULL,
              "find_above returns NULL when no value matches");
    }

    /* Test 10: value equal to threshold is not a match */
    {
        const float values[] = {2.0f, 5.0f, 7.0f};
        const float *result = find_above(values, 3, 5.0f);

        check(result == values + 2 && float_equal(*result, 7.0f),
              "find_above skips values equal to threshold");
    }

    /* Test 11: find_above with NULL array */
    {
        const float *result = find_above(NULL, 3, 2.0f);

        check(result == NULL,
              "find_above handles NULL array");
    }

    /* Test 12: reverse an even-length array */
    {
        float values[] = {1.0f, 2.0f, 3.0f, 4.0f};
        const float expected[] = {4.0f, 3.0f, 2.0f, 1.0f};

        reverse(values, 4);

        check(array_equal(values, expected, 4),
              "reverse handles even-length array");
    }

    /* Test 13: reverse an odd-length array */
    {
        float values[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        const float expected[] = {5.0f, 4.0f, 3.0f, 2.0f, 1.0f};

        reverse(values, 5);

        check(array_equal(values, expected, 5),
              "reverse handles odd-length array");
    }

    /* Test 14: reverse with one element */
    {
        float values[] = {42.0f};

        reverse(values, 1);

        check(float_equal(values[0], 42.0f),
              "reverse leaves one-element array unchanged");
    }

    /* Test 15: reverse with NULL array */
    {
        reverse(NULL, 3);

        check(1, "reverse handles NULL array");
    }

    printf("\n----------------------------\n");
    printf("Tests passed: %d\n", passed);
    printf("Tests failed: %d\n", failed);
    printf("----------------------------\n");

    return failed == 0 ? 0 : 1;
}