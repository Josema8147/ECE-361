#include <stdio.h>
#include <math.h>

#include "../stats.h"

static int tests_run = 0;
static int tests_failed = 0;

static void check(int condition, const char *name)
{
    tests_run++;

    if (condition) {
        printf("PASS: %s\n", name);
    } else {
        printf("FAIL: %s\n", name);
        tests_failed++;
    }
}

static int close_enough(float a, float b)
{
    return fabsf(a - b) < 0.001f;
}

static void test_one_value(void)
{
    const float a[] = {42.5f};

    check(close_enough(stats_min(a, 1), 42.5f)
          && close_enough(stats_max(a, 1), 42.5f)
          && close_enough(stats_mean(a, 1), 42.5f),
          "one value: min, max, and mean");
}

static void test_maximum_at_start(void)
{
    const float a[] = {99.0f, 2.0f, 7.0f, 12.0f};

    check(close_enough(stats_max(a, 4), 99.0f),
          "maximum at the start");
}

static void test_maximum_at_end(void)
{
    const float a[] = {2.0f, 7.0f, 12.0f, 99.0f};

    check(close_enough(stats_max(a, 4), 99.0f),
          "maximum at the end");
}

static void test_threshold_ends_run(void)
{
    const float a[] = {31.0f, 32.0f, 30.0f, 35.0f};
    int start_index = -1;

    int length = stats_longest_run(a, 4, 30.0f, &start_index);

    check(length == 2 && start_index == 0,
          "value equal to threshold ends a run");
}

static void test_large_recursive_maximum(void)
{
    enum { SIZE = 10000 };
    float a[SIZE];

    for (int i = 0; i < SIZE; i++) {
        a[i] = (float)i;
    }

    check(close_enough(stats_max(a, SIZE), 9999.0f),
          "recursive maximum of 10000 values");
}

static void test_tail_maximum(void)
{
    const float a[] = {4.0f, 19.0f, -3.0f, 27.0f, 8.0f};

    check(close_enough(stats_max_tail(a, 5), 27.0f),
          "tail maximum returns the correct result");

    check(close_enough(stats_max(a, 5), stats_max_tail(a, 5)),
          "tail maximum agrees with recursive maximum");
}

static void test_tail_maximum_one_value(void)
{
    const float a[] = {42.5f};

    check(close_enough(stats_max_tail(a, 1), 42.5f),
          "tail maximum with one value");
}

static void test_tail_maximum_negative_values(void)
{
    const float a[] = {-10.0f, -3.0f, -25.0f, -7.0f};

    check(close_enough(stats_max_tail(a, 4), -3.0f),
          "tail maximum with negative values");
}

int main(void)
{
    test_one_value();
    test_maximum_at_start();
    test_maximum_at_end();
    test_threshold_ends_run();
    test_large_recursive_maximum();
    test_tail_maximum();
    test_tail_maximum_one_value();
    test_tail_maximum_negative_values();

    printf("\nTests run: %d, failures: %d\n",
           tests_run, tests_failed);

    return tests_failed == 0 ? 0 : 1;
}