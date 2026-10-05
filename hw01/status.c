#include "status.h"
#include "bits.h"

status_t status_unpack(uint16_t word)
{
  status_t status;
  status.heat = get_field(word, STATUS_HEAT_POS, STATUS_HEAT_WIDTH);
  status.cool = get_field(word, STATUS_COOL_POS, STATUS_COOL_WIDTH);
  status.fan = get_field(word, STATUS_FAN_POS, STATUS_FAN_WIDTH);
  status.fault = get_field(word, STATUS_FAULT_POS, STATUS_FAULT_WIDTH);
  stauts.mode = get_field(word, STATUS_MODE_POS, STATUS_MODE_WIDTH);
  status.reserved = get_field(word, STATUS_RESERVED_POS, STATUS_RESERVED_WIDTH);
  status.setpoint = sign_extend(
      get_field(word, STATUS_SETPOINT_POS, STATUS_SETPOINT_WIDTH),
      STATUS_SETPOINT_WIDTH
    );
/*
 *Modes 5, 6, and 7 are invalid.
 *We represent an invalid mode as 4294967295
 */
if (status.mode >=5) {
    status.mode = UINT32_MAX;
}
return status;
