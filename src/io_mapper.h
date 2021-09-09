#ifndef IO_MAPPER_H
#define IO_MAPPER_H

#include <stdbool.h>

typedef enum GPIO_PinAssignment
{
  LightsAutomatic = 1,
  DirectionControl = 12,
  LightsRear = 16,
  LightsFront = 17,
  LightsOn = 27,
  ControlSource = 30,
  DirectionSelection = 31,
  LightsMain = 32
} GPIO_PinAssignment_t;

typedef enum
{
  IO_STATE_OFF,
  IO_STATE_ON
} io_state_t;

io_state_t IOMapper_GetControlSource(void);
io_state_t IOMapper_GetDirectionState(void);

void IOMapper_SetDirectionAVR(io_state_t state);

io_state_t IOMapper_GetPinState(GPIO_PinAssignment_t gpioPin);
void IOMapper_SetPinState(GPIO_PinAssignment_t gpioPin, io_state_t state);

#endif
