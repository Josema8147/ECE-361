#include <stdio.h>
#include <stdint.h>

#include "../bits.h"
#include "../status.h"

static int tests_run = 0;
static int tests_failed = 0;

static void check_uint32(const char *name, uint32_t expected, uint32_t actual)
{
tests_run++;

if (expected == actual) {
    printf("PASS: %s\n", name);
} else {
    printf("FAIL: %s (expected %u, got %u)\n",
           name, expected, actual);
    tests_failed++;
}


}

static void check_int32(const char *name, int32_t expected, int32_t actual)
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

static void check_status(const char *name,
status_t actual,
uint32_t heat,
uint32_t cool,
uint32_t fan,
uint32_t fault,
uint32_t mode,
uint32_t reserved,
int32_t setpoint)
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
    printf("      Expected: heat=%u cool=%u fan=%u fault=%u "
           "mode=%u reserved=%u setpoint=%d\n",
           heat, cool, fan, fault, mode, reserved, setpoint);

    printf("      Got:      heat=%u cool=%u fan=%u fault=%u "
           "mode=%u reserved=%u setpoint=%d\n",
           actual.heat, actual.cool, actual.fan, actual.fault,
           actual.mode, actual.reserved, actual.setpoint);

    tests_failed++;
}


}

int main(void)
{
/*
* Test print_binary.
* Expected output: 0010 1100
*/
printf("Testing print_binary:\n");
printf("Expected: 0010 1100\n");
printf("Actual: ");
print_binary(UINT32_C(0x2C), 8);
printf("\n");

/*
 * Test get_field.
 */

check_uint32(
    "get_field width 1",
    UINT32_C(1),
    get_field(UINT32_C(0x80000000), 31, 1)
);

check_uint32(
    "get_field width 32",
    UINT32_C(0x12345678),
    get_field(UINT32_C(0x12345678), 0, 32)
);

check_uint32(
    "get_field position 31",
    UINT32_C(1),
    get_field(UINT32_C(0x80000000), 31, 1)
);

/*
 * Test invalid get_field arguments.
 * Our chosen behavior is to return 0.
 */
check_uint32(
    "get_field invalid width 0",
    UINT32_C(0),
    get_field(UINT32_C(0x12345678), 0, 0)
);

check_uint32(
    "get_field invalid position",
    UINT32_C(0),
    get_field(UINT32_C(0x12345678), 32, 1)
);

check_uint32(
    "get_field field extends past bit 31",
    UINT32_C(0),
    get_field(UINT32_C(0x12345678), 31, 2)
);

/*
 * Test set_field.
 */

check_uint32(
    "set_field width 1",
    UINT32_C(0x80000000),
    set_field(UINT32_C(0), 31, 1, UINT32_C(1))
);

/*
 * The field is only 2 bits wide.
 * 0xFF has lowest 2 bits equal to 3.
 */
check_uint32(
    "set_field uses only lowest width bits",
    UINT32_C(3),
    set_field(UINT32_C(0), 0, 2, UINT32_C(0xFF))
);

check_uint32(
    "set_field width 32",
    UINT32_C(0x12345678),
    set_field(UINT32_C(0), 0, 32, UINT32_C(0x12345678))
);

/*
 * Test invalid set_field arguments.
 * Our chosen behavior is to return the original word.
 */
check_uint32(
    "set_field invalid width 0",
    UINT32_C(0x12345678),
    set_field(UINT32_C(0x12345678), 0, 0, UINT32_C(5))
);

check_uint32(
    "set_field invalid position",
    UINT32_C(0x12345678),
    set_field(UINT32_C(0x12345678), 32, 1, UINT32_C(5))
);

check_uint32(
    "set_field field extends past bit 31",
    UINT32_C(0x12345678),
    set_field(UINT32_C(0x12345678), 31, 2, UINT32_C(5))
);

/*
 * Test sign_extend.
 */

check_int32(
    "sign_extend width 1 positive",
    INT32_C(0),
    sign_extend(UINT32_C(0), 1)
);

check_int32(
    "sign_extend width 1 negative",
    INT32_C(-1),
    sign_extend(UINT32_C(1), 1)
);

check_int32(
    "sign_extend width 32",
    INT32_C(-1),
    sign_extend(UINT32_MAX, 32)
);

/*
 * Most negative value for an 8-bit signed number.
 * 1000 0000 = -128.
 */
check_int32(
    "sign_extend most negative 8-bit value",
    INT32_C(-128),
    sign_extend(UINT32_C(0x80), 8)
);

check_int32(
    "sign_extend 0xF8",
    INT32_C(-8),
    sign_extend(UINT32_C(0xF8), 8)
);

/*
 * Test status_unpack.
 */

/*
 * Assignment example:
 * 0x1631
 *
 * heat = 1
 * cool = 0
 * fan = 0
 * fault = 0
 * mode = 3 (AUTO)
 * reserved = 0
 * setpoint = 22
 */
check_status(
    "status_unpack example 0x1631",
    status_unpack(UINT16_C(0x1631)),
    UINT32_C(1),
    UINT32_C(0),
    UINT32_C(0),
    UINT32_C(0),
    UINT32_C(3),
    UINT32_C(0),
    INT32_C(22)
);

/*
 * Test all fields off and setpoint = 0.
 */
check_status(
    "status_unpack all off",
    status_unpack(UINT16_C(0x0000)),
    UINT32_C(0),
    UINT32_C(0),
    UINT32_C(0),
    UINT32_C(0),
    UINT32_C(0),
    UINT32_C(0),
    INT32_C(0)
);

/*
 * Test FAN_ONLY mode and a negative setpoint.
 *
 * 0xFC44:
 * setpoint = 0xFC = -4
 * mode = 4 (FAN_ONLY)
 * fan = 1
 */
check_status(
    "status_unpack negative setpoint",
    status_unpack(UINT16_C(0xFC44)),
    UINT32_C(0),
    UINT32_C(0),
    UINT32_C(1),
    UINT32_C(0),
    UINT32_C(4),
    UINT32_C(0),
    INT32_C(-4)
);

/*
 * Test invalid mode.
 * MODE = 5, so status_unpack should report UINT32_MAX.
 */
check_status(
    "status_unpack invalid mode",
    status_unpack(UINT16_C(0x0050)),
    UINT32_C(0),
    UINT32_C(0),
    UINT32_C(0),
    UINT32_C(0),
    UINT32_MAX,
    UINT32_C(0),
    INT32_C(0)
);

/*
 * Print summary.
 */
printf("\n%d tests run, %d failed.\n",
       tests_run, tests_failed);

if (tests_failed == 0) {
    printf("All tests passed!\n");
    return 0;
}

printf("Some tests failed.\n");
return 1;


}
