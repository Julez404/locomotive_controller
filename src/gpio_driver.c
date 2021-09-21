// ****************************************************************************
/** \file gpio_driver.c
 * \brief GPIO driver module
 */
//*****************************************************************************
// Includes
//*****************************************************************************
#include "gpio_driver.h"
#include "sw_conf.h"

//*****************************************************************************
// Module Preprocessor Constants
//*****************************************************************************
#define INVALID_VALUE -1
#define PIN_MAX 35

enum Ports
{
  PORTB,
  PORTC,
  PORTD,
  PORT_MAX
};

enum Pins
{
  PIN0,
  PIN1,
  PIN2,
  PIN3,
  PIN4,
  PIN5,
  PIN6,
  PIN7,
};

//*****************************************************************************
// Module Preprocessor Macros
//*****************************************************************************

//*****************************************************************************
// Module Typedefs
//*****************************************************************************

//*****************************************************************************
// Module Variable Definitions
//*****************************************************************************
volatile GPIO_Port_t *GPIO_Ports[PORT_MAX];
static int8_t PinToPort[PIN_MAX] =
    {
        INVALID_VALUE, // 0
        PORTD,         // 1
        PORTD,         // 2
        INVALID_VALUE, // 3
        INVALID_VALUE, // 4
        INVALID_VALUE, // 5
        INVALID_VALUE, // 6
        PORTB,         // 7
        PORTB,         // 8
        PORTD,         // 9
        PORTD,         // 10
        PORTD,         // 11
        PORTB,         // 12
        PORTB,         // 13
        PORTB,         // 14
        PORTB,         // 15
        PORTB,         // 16
        PORTB,         // 17
        INVALID_VALUE, // 18
        INVALID_VALUE, // 19
        INVALID_VALUE, // 20
        INVALID_VALUE, // 21
        INVALID_VALUE, // 22
        PORTC,         // 23
        PORTC,         // 24
        PORTC,         // 25
        PORTC,         // 26
        PORTC,         // 27
        PORTC,         // 28
        PORTC,         // 29
        PORTD,         // 30
        PORTD,         // 31
        PORTD,         // 32
        INVALID_VALUE, // 33
        INVALID_VALUE, // 34
};

static int8_t PinToPortPin[PIN_MAX] =
    {
        INVALID_VALUE, // 0
        PIN3,          // 1
        PIN4,          // 2
        INVALID_VALUE, // 3
        INVALID_VALUE, // 4
        INVALID_VALUE, // 5
        INVALID_VALUE, // 6
        PIN6,          // 7
        PIN7,          // 8
        PIN5,          // 9
        PIN6,          // 10
        PIN7,          // 11
        PIN0,          // 12
        PIN1,          // 13
        PIN2,          // 14
        PIN3,          // 15
        PIN4,          // 16
        PIN5,          // 17
        INVALID_VALUE, // 18
        INVALID_VALUE, // 19
        INVALID_VALUE, // 20
        INVALID_VALUE, // 21
        INVALID_VALUE, // 22
        PIN0,          // 23
        PIN1,          // 24
        PIN2,          // 25
        PIN3,          // 26
        PIN4,          // 27
        PIN5,          // 28
        PIN6,          // 29
        PIN0,          // 30
        PIN1,          // 31
        PIN2,          // 32
        INVALID_VALUE, // 33
        INVALID_VALUE, // 34
};

//*****************************************************************************
// Function Prototypes
//*****************************************************************************
static int8_t GetPortFromPin(uint8_t pin);
static int8_t GetPortPinFromPin(uint8_t pin);
static void SetPortsToDefaultConfig();
static bool PinValid(uint8_t pin);

//*****************************************************************************
// Function Definitions
//*****************************************************************************
void GPIO_Init(GPIO_Port_t *portB_addr, GPIO_Port_t *portC_addr, GPIO_Port_t *portD_addr)
{
  GPIO_Ports[PORTB] = portB_addr;
  GPIO_Ports[PORTC] = portC_addr;
  GPIO_Ports[PORTD] = portD_addr;

  SetPortsToDefaultConfig();
}

bool GPIO_GetPin(uint8_t gpioNumber)
{
  int8_t port = GetPortFromPin(gpioNumber);
  int8_t pin = GetPortPinFromPin(gpioNumber);

  bool test = false;

  return (bool)(GPIO_Ports[port]->input & (1 << pin));
}

void GPIO_SetPin(uint8_t gpioNumber, bool state)
{
  int port = GetPortFromPin(gpioNumber);
  int portPin = GetPortPinFromPin(gpioNumber);

  if ((port == -1) || (portPin == -1))
    return;

  if (state)
    GPIO_Ports[port]->output |= (1 << portPin);
  else
    GPIO_Ports[port]->output &= ~(1 << portPin);
}

void GPIO_ConfigurePin(uint8_t gpioPin, pinConfig_t config)
{
  int port = GetPortFromPin(gpioPin);
  int portPin = GetPortPinFromPin(gpioPin);

  if ((port == -1) || (portPin == -1))
    return;

  if (config.pintype == PINTYPE_INPUT)
  {
    GPIO_Ports[port]->dataDirection &= ~(1 << portPin);
    if (config.pullUpActive)
    {
      GPIO_Ports[port]->output |= (1 << portPin);
    }
    else
    {
      GPIO_Ports[port]->output &= ~(1 << portPin);
    }
  }
  else
  {
    GPIO_Ports[port]->dataDirection |= (1 << portPin);
    GPIO_Ports[port]->output &= ~(1 << portPin);
  }
}

static int8_t GetPortPinFromPin(uint8_t pin)
{
  if (PinValid(pin))
    return PinToPortPin[pin];
  else
    return INVALID_VALUE;
}

static int8_t GetPortFromPin(uint8_t pin)
{
  if (PinValid(pin))
    return PinToPort[pin];
  else
    return INVALID_VALUE;
}

static bool PinValid(uint8_t pin)
{
  if (pin >= PIN_MAX)
    return false;
  else
    return true;
}

static void SetPortsToDefaultConfig()
{
  for (uint8_t port = 0; port < PORT_MAX; port++)
  {
    // Set to input
    GPIO_Ports[port]->dataDirection = 0;

    // Activate PullUp
    GPIO_Ports[port]->output = 0xFF;
  }
}
