
#include <stdio.h>
#include <string.h>

#include "../tally.h"

static int test_counting(void)
{
    tally_t *t = tally_create();
    int ok;

    if (t == NULL) {
        return 0;
    }

    ok = tally_add(t, "apple") == 1
        && tally_add(t, "apple") == 2
        && tally_add(t, "apple") == 3
        && tally_count(t, "apple") == 3;

    tally_destroy(t);
    return ok;
}

static int test_name_never_added(void)
{
    tally_t *t = tally_create();
    int ok;

    if (t == NULL) {
        return 0;
    }

    ok = tally_count(t, "missing") == 0;
    tally_destroy(t);
    return ok;
}

static int test_empty_and_long_names(void)
{
    tally_t *t = tally_create();
    char exact[TALLY_LEN + 1];
    char too_long[TALLY_LEN + 2];
    int ok;

    if (t == NULL) {
        return 0;
    }

    memset(exact, 'a', TALLY_LEN);
    exact[TALLY_LEN] = '\0';

    memset(too_long, 'b', TALLY_LEN + 1);
    too_long[TALLY_LEN + 1] = '\0';

    ok = tally_add(t, "") == -1
        && tally_add(t, exact) == 1
        && tally_count(t, exact) == 1
        && tally_add(t, too_long) == -1
        && tally_size(t) == 1;

    tally_destroy(t);
    return ok;
}

static int test_null_arguments(void)
{
    tally_t *t = tally_create();
    int ok;

    if (t == NULL) {
        return 0;
    }

    ok = tally_add(NULL, "apple") == -1
        && tally_add(t, NULL) == -1
        && tally_count(NULL, "apple") == 0
        && tally_count(t, NULL) == 0
        && tally_size(NULL) == 0;

    tally_destroy(t);
    tally_destroy(NULL);
    return ok;
}

static int test_full_tally(void)
{
    tally_t *t = tally_create();
    char name[TALLY_LEN + 1];
    int i;
    int ok = 1;

    if (t == NULL) {
        return 0;
    }

    for (i = 0; i < TALLY_NAMES; i++) {
        (void)snprintf(name, sizeof(name), "n%02d", i);

        if (tally_add(t, name) != 1) {
            ok = 0;
        }
    }

    /* A new name must be refused when the tally is full. */
    if (tally_add(t, "newname") != -1) {
        ok = 0;
    }

    /* An existing name must still be counted. */
    if (tally_add(t, "n00") != 2) {
        ok = 0;
    }

    if (tally_size(t) != TALLY_NAMES) {
        ok = 0;
    }

    tally_destroy(t);
    return ok;
}

static int test_max_tallies(void)
{
    tally_t *items[TALLY_MAX];
    int i;
    int ok = 1;

    for (i = 0; i < TALLY_MAX; i++) {
        items[i] = tally_create();

        if (items[i] == NULL) {
            ok = 0;
        }
    }

    if (tally_create() != NULL) {
        ok = 0;
    }

    for (i = 0; i < TALLY_MAX; i++) {
        if (items[i] != NULL) {
            tally_destroy(items[i]);
        }
    }

    return ok;
}

static int test_create_after_destroy(void)
{
    tally_t *first = tally_create();
    tally_t *second;
    int ok;

    if (first == NULL) {
        return 0;
    }

    tally_destroy(first);
    second = tally_create();

    ok = second != NULL;

    if (second != NULL) {
        tally_destroy(second);
    }

    return ok;
}

static int test_independent_tallies(void)
{
    tally_t *a = tally_create();
    tally_t *b = tally_create();
    int ok;

    if (a == NULL || b == NULL) {
        tally_destroy(a);
        tally_destroy(b);
        return 0;
    }

    (void)tally_add(a, "apple");
    (void)tally_add(a, "apple");
    (void)tally_add(b, "apple");

    ok = tally_count(a, "apple") == 2
        && tally_count(b, "apple") == 1
        && tally_size(a) == 1
        && tally_size(b) == 1;

    tally_destroy(a);
    tally_destroy(b);
    return ok;
}

static int test_print_order(void)
{
    tally_t *t = tally_create();
    FILE *out;
    char result[128];
    const char expected[] =
        "apple 1\n"
        "banana 1\n"
        "orange 1\n";
    int ok = 0;

    if (t == NULL) {
        return 0;
    }

    out = tmpfile();

    if (out == NULL) {
        tally_destroy(t);
        return 0;
    }

    (void)tally_add(t, "orange");
    (void)tally_add(t, "apple");
    (void)tally_add(t, "banana");

    tally_print(t, out);
    rewind(out);

    if (fgets(result, sizeof(result), out) != NULL) {
        /* Read the entire output for comparison. */
        size_t used = strlen(result);

        while (used < sizeof(result) - 1
               && fgets(result + used,
                        (int)(sizeof(result) - used),
                        out) != NULL) {
            used += strlen(result + used);
        }

        ok = strcmp(result, expected) == 0;
    }

    (void)fclose(out);
    tally_destroy(t);
    return ok;
}

int main(void)
{
    int passed = 0;
    int failed = 0;
    int ok;

#define RUN_TEST(fn) do {                 \
    ok = fn();                            \
    printf("%s: %s\n",                    \
           ok ? "PASS" : "FAIL", #fn);    \
    if (ok) {                             \
        passed++;                         \
    } else {                              \
        failed++;                         \
    }                                     \
} while (0)

    RUN_TEST(test_counting);
    RUN_TEST(test_name_never_added);
    RUN_TEST(test_empty_and_long_names);
    RUN_TEST(test_null_arguments);
    RUN_TEST(test_full_tally);
    RUN_TEST(test_max_tallies);
    RUN_TEST(test_create_after_destroy);
    RUN_TEST(test_independent_tallies);
    RUN_TEST(test_print_order);

    printf("\nSummary: %d passed, %d failed\n",
           passed, failed);

    return failed == 0 ? 0 : 1;
}
