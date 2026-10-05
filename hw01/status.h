#ifndef STATUS_H
#define STATUS_H

#include <stdint.h>

/* Bit positions and widths in the thermostat status word. */
#define STATUS_HEAT_POS 0
#define STATUS_HEAT_WIDTH 1

#define STATUS_COOL_POS 1
#define STATUS_COOL_WIDTH 1

#define STATUS_FAN_POS 2
#define STATUS_FAN_WIDTH 1

#define STATUS_FAULT_POS 3
#define STATUS_FAULT_WIDTH 1

#define STATUS_MODE_POS 4
#define STATUS_MODE_WIDTH 1

#define STATUS_RESERVED_POS 7
#define STATUS_RESERVED_WIDTH 1

#define STATUS_SETPOINT_POS 8
#define STATUS_SETPOINT_WIDTH 8

typedef struct {
uint32_t heat;
uint32_t cool;
uint32_t fan;
uint32_t fault;
uint32_t mode;
uint32_t reserved;
int32_t setpoint;
} status_t;

status_t status_unpack(uint16_t word);

#endif
