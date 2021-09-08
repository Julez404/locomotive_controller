#include "gpio_driver.h"
#include "sw_conf.h"

// Control 3 Port Register of GPIO Pins
uint8_t port_a;
uint8_t port_b;
uint8_t port_c;

// Control flow direction on these ports
uint8_t ddr_a;
uint8_t ddr_b;
uint8_t ddr_c;


#define PIN_MAX 31


static int GetPortDirectionGpioNumber(uint8_t gpioNumber);
static int GetPortFromGpioNumber(uint8_t gpioNumber);
static uint8_t GetPortPinFromGpioNumber(uint8_t gpioNumber);
static bool IsValidGPIO(uint8_t gpioNumber);


/**
 * @brief Sets every Available GPIO to Input without pullup
 * 
 */
void GPIO_Init()
{
  for (uint8_t inputNumer = 0; inputNumer < PIN_MAX; inputNumer++)
  {
    /* code */
  }
}

bool GPIO_GetPin(uint8_t gpioNumber)
{
  return true;
}

void GPIO_SetPin(uint8_t gpioNumber, bool state)
{
  return;
}


void GPIO_ConfigurePin(pinConfig_t pinConfiguration, uint8_t gpioNumber)
{
  if (!IsValidGPIO(gpioNumber))
    return;

  int portDirectionRegister = GetPortDirectionGpioNumber(gpioNumber);
  int port = GetPortFromGpioNumber(gpioNumber);
  int portPin = GetPortPinFromGpioNumber(gpioNumber);

  if (pinConfiguration.pintype == PINTYPE_INPUT)
  {
    portDirectionRegister &= ~(1 << portPin);
  }
  else
  {
    portDirectionRegister |= (1 << portPin);
  }
}

static int GetPortDirectionGpioNumber(uint8_t gpioNumber)
{

}

static int GetPortFromGpioNumber(uint8_t gpioNumber)
{
}

static uint8_t GetPortPinFromGpioNumber(uint8_t gpioNumber)
{
}

static bool IsValidGPIO(uint8_t gpioNumber)
{
  return true;
}
