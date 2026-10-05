#include <stdio.h>
#include <stdint.h>
#include "bits.h"
#include "status.h"

static int tests_run = 0;
static int tests_failed = 0;

static void check_int(const char *name, int expected, int actual)
{
tests_run++;

if (expected == actual) {
    printf("PASS: %s\n", name);
} else {
    printf("FAIL: %s (expected %d, got %d)\n",
           name, expected, actual);
    tests_failed++;
}


}

static void check_uint32(const char *name,
uint32_t expected,
uint32_t actual)
{
tests_run++;

if (expected == actual) {
    printf("PASS: %s\n", name);
} else {
    printf("FAIL: %s (expected 0x%08X, got 0x%08X)\n",
           name, expected, actual);
    tests_failed++;
}


}

static void check_status(const char *name,
status_t actual,
uint8_t heat,
uint8_t cool,
uint8_t fan,
uint8_t fault,
uint8_t mode,
uint8_t reserved,
int8_t setpoint)
{
tests_run++;

if (actual.heat == heat &&
    actual.cool == cool &&
    actual.fan == fan &&
    actual.fault == fault &&
    actual.mode == mode &&
    actual.reserved == reserved &&
    actual.setpoint == setpoint) {

    printf("PASS: %s\n", name);
} else {
    printf("FAIL: %s\n", name);
    tests_failed++;
}


}

int main(void)
{
/*
* print_binary
*/
printf("\nTesting print_binary:\n");
printf("Expected: 0010 1100\n");
printf("Actual: ");
print_binary(0x2C, 8);

/*
 * get_field
 */

/* Width 1 */
check_uint32(
    "get_field width 1",
    1,
    get_field(UINT32_C(0x80000000), 31, 1)
);

/* Width 32 */
check_uint32(
    "get_field width 32",
    UINT32_C(0x12345678),
    get_field(UINT32_C(0x12345678), 0, 32)
);

/* Position 31 */
check_uint32(
    "get_field position 31",
    1,
    get_field(UINT32_C(0x80000000), 31, 1)
);

/*
 * set_field
 */

/* Width 1 */
check_uint32(
    "set_field width 1",
    UINT32_C(0x80000000),
    set_field(UINT32_C(0), 31, 1, 1)
);

/* Value wider than the field */
check_uint32(
    "set_field uses only lowest width bits",
    UINT32_C(0x00000003),
    set_field(UINT32_C(0), 0, 2, UINT32_C(0xFF))
);

/* Width 32 */
check_uint32(
    "set_field width 32",
    UINT32_C(0x12345678),
    set_field(UINT32_C(0), 0, 32, UINT32_C(0x12345678))
);

/*
 * sign_extend
 */

/* Width 1: 0 is positive */
check_int(
    "sign_extend width 1 positive",
    0,
    sign_extend(0, 1)
);

/* Width 1: 1 is -1 */
check_int(
    "sign_extend width 1 negative",
    -1,
    sign_extend(1, 1)
);

/* Width 32 */
check_int(
    "sign_extend width 32",
    -1,
    sign_extend(UINT32_MAX, 32)
);

/* Most negative 8-bit value: 1000 0000 = -128 */
check_int(
    "sign_extend most negative 8-bit value",
    -128,
    sign_extend(UINT32_C(0x80), 8)
);

/* Assignment example: 0xF8 = -8 */
check_int(
    "sign_extend 0xF8",
    -8,
    sign_extend(UINT32_C(0xF8), 8)
);

/*
 * status_unpack
 */

/* Assignment's example */
check_status(
    "status_unpack example 0x1631",
    status_unpack(UINT16_C(0x1631)),
    1,      /* heat */
    0,      /* cool */
    0,      /* fan */
    0,      /* fault */
    3,      /* mode */
    0,      /* reserved */
    22      /* setpoint */
);

/* Everything off, setpoint 0 */
check_status(
    "status_unpack all off",
    status_unpack(UINT16_C(0x0000)),
    0,
    0,
    0,
    0,
    0,
    0,
    0
);

/* Negative setpoint and FAN mode */
check_status(
    "status_unpack negative setpoint",
    status_unpack(UINT16_C(0xFC44)),
    0,
    0,
    1,
    0,
    4,
    0,
    -4
);

/* Invalid mode 5 should become 255 */
check_status(
    "status_unpack invalid mode",
    status_unpack(UINT16_C(0x0050)),
    0,
    0,
    0,
    0,
    UINT8_MAX,
    0,
    0
);

printf("\n%d tests run, %d failed.\n",
       tests_run, tests_failed);

if (tests_failed == 0) {
    printf("All tests passed!\n");
    return 0;
}

printf("Some tests failed.\n");
return 1;


}
