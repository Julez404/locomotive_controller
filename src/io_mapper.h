#ifndef IO_MAPPER_H
#define IO_MAPPER_H

#include "sw_conf.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum io_state
{
  IO_STATE_OFF,
  IO_STATE_ON
} io_state_t;

io_state_t IOMapper_GetControlSource(void);
io_state_t IOMapper_GetDirectionState(void);

io_state_t IOMapper_GetPinState(GPIO_PinAssignment_t gpioPin);
void IOMapper_SetPinState(GPIO_PinAssignment_t gpioPin, io_state_t state);

#endif
