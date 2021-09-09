#include "sw_conf.h"
#include "io_mapper.h"
#include "gpio_driver.h"

io_state_t IOMapper_GetPinState(GPIO_PinAssignment_t gpioPin)
{
  return GPIO_GetPin(gpioPin);
}

void IOMapper_SetPinState(GPIO_PinAssignment_t gpioPin, io_state_t state)
{
  GPIO_SetPin(gpioPin, state);
}

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