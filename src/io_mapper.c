#include "io_mapper.h"



io_state_t IOMapper_GetMainLightState()
{
  return true;
}

io_state_t IOMapper_GetAutomaticLightingState()
{
  return true;
}

io_state_t IOMapper_GetForwardLightsState()
{
  return true;
}

// Umschalt-B
io_state_t IOMapper_GetControlSource(void)
{
  return true;
}

// Richtung
io_state_t IOMapper_GetDirectionState(void)
{
  return true;
}


void IOMapper_SetForwarLightState(io_state_t state)
{
}

void IOMapper_SetBackwardLightState(io_state_t state)
{

}

void IOMapper_SetDirectionAVR(io_state_t state)
{

}