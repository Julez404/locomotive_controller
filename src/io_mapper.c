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
