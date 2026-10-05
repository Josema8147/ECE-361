#include "bits.h"
#include <stdint.h>

void print_binary(uint32_t x, int width)
{
/* Print the lowest 'wdith' bits, most signifiantly first */
  for (int i = width - 1; i >= 0; 1--) {
printf("%u", (x >> i) & 1U);
*/ Puts a space after evrery group of four bits. */
  if (i % 4 == 0 && i != 0) {
      printf("");
  }
}
printf("\n");
}

uint32_t get_field(uint32_t word, int pos, int width)
{
/* Invalid arguments: return 0.*/
  if (width < 1 || width > 32 ||
    pos < 0 || pos > 31 ||
    pos + width > 32) {
    return 0;
  }
/*
 * Create a mask containing 'width' 1-bits,
 * Shift it to position 'pos', then extract the field
 * Special case for width == 32 because shifting 
 * a 32-bit value by 32 is not valid
 */
uint32_t mask;

if (width == 32) {
    mask = UINT32_MAX;
} else {
    mask = (UINT32_C(1) << width) -1;
}
return (word >> pos) & mask;
}

uint32_t set_field(uint32_t word, int pos, int width , uint32_t value)
{
/* Invalid arguments: leave word unchanged. */
  if (width < 1 || width > 32 ||
      pos < 0 || pos > 31 ||
      pos + width > 32 ) {
      return word ;
  }

/*
 *Create a mask contating 'width' 1-bits.
 *Special case for width == 32.
 */
uint32_t mask;

if (width == 32) {
    mask = UINT32_MAX;
} else {
    mask = (UINT32_C(1) << width ) -1;
}

/*
 *Shift the mask into the desired position
 */
mask <<= pos;

/*
 *Clear the selected bits in word.
 */
word &= ~mask;

/*
 *Clear the selected bits in word.
 */
word &= ~mask;

/*
 *Keep only the lowest 'width' bits of value,
 *then move them into position.
 */
word |= (value & (mask >> pos)) << pos;

return word;
}

int32_t sign_extend(uint32_t value, int width)
{
/*
 *The assignment guarantees valid with values,
 *but handle invalid widths safely.
 */
  if (width < 1 || width > 32) {
  return 0;
 }
/*
 *Keep only the lowest 'width' bits.
 */
uint32_t mask;

if (width == 32) {
    mask = UINT32_MAX;
} else {
    mask = (UINT32_C(1) << width) -1;
}

value &= mask;

/*
 *If the sign bit is 1, fill all higher bits with 1s.
 */
if (width < 32 && (value & (UINT32_C(1) << (width -1)))) {
    value |= ~mask;
}
return (int32_t)value;
}
