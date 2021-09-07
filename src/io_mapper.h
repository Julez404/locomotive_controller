#ifndef IO_MAPPER_H
#define IO_MAPPER_H

#include <stdbool.h>

typedef enum
{
  IO_STATE_OFF,
  IO_STATE_ON
} io_state_t;

io_state_t IOMapper_GetMainLightState(void);
io_state_t IOMapper_GetAutomaticLightingState(void);
io_state_t IOMapper_GetForwardLightsState(void);
io_state_t IOMapper_GetControlSource(void);
io_state_t IOMapper_GetDirectionState(void);

void IOMapper_SetForwardLightState(io_state_t state);
void IOMapper_SetBackwardLightState(io_state_t state);
void IOMapper_SetDirectionAVR(io_state_t state);

#endif
