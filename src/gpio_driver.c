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
typedef struct GPIO_PinInfo
{
  uint8_t port;
  uint8_t pin;
  bool validGPIO;
} GPIO_PinInfo_t;

//*****************************************************************************
// Module Variable Definitions
//*****************************************************************************
volatile GPIO_Port_t *GPIO_Ports[PORT_MAX];
static GPIO_PinInfo_t gpioPinInfoStore[PIN_MAX] =
    {
        {0, 0, false},       // 0
        {PORTD, PIN3, true}, // 1
        {PORTD, PIN4, true}, // 2
        {0, 0, false},       // 3
        {0, 0, false},       // 4
        {0, 0, false},       // 5
        {0, 0, false},       // 6
        {PORTB, PIN6, true}, // 7
        {PORTB, PIN7, true}, // 8
        {PORTD, PIN5, true}, // 9
        {PORTD, PIN6, true}, // 10
        {PORTD, PIN7, true}, // 11
        {PORTB, PIN0, true}, // 12
        {PORTB, PIN1, true}, // 13
        {PORTB, PIN2, true}, // 14
        {PORTB, PIN3, true}, // 15
        {PORTB, PIN4, true}, // 16
        {PORTB, PIN5, true}, // 17
        {0, 0, false},       // 18
        {0, 0, false},       // 19
        {0, 0, false},       // 20
        {0, 0, false},       // 21
        {0, 0, false},       // 22
        {PORTC, PIN0, true}, // 23
        {PORTC, PIN1, true}, // 24
        {PORTC, PIN2, true}, // 25
        {PORTC, PIN3, true}, // 26
        {PORTC, PIN4, true}, // 27
        {PORTC, PIN5, true}, // 28
        {PORTC, PIN6, true}, // 29
        {PORTD, PIN0, true}, // 30
        {PORTD, PIN1, true}, // 31
        {PORTD, PIN2, true}, // 32
        {0, 0, false},       // 33
        {0, 0, false},       // 34
};

//*****************************************************************************
// Function Prototypes
//*****************************************************************************
static void SetPortsToDefaultConfig();
static bool PinOutOfBounce(uint8_t pin);

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
  if (PinOutOfBounce(gpioNumber))
    return false;

  GPIO_PinInfo_t gpioPin = gpioPinInfoStore[gpioNumber];

  if (!gpioPin.validGPIO)
    return false;

  return (bool)(GPIO_Ports[gpioPin.port]->input & (1 << gpioPin.pin));
}

void GPIO_SetPin(uint8_t gpioNumber, bool state)
{
  if (PinOutOfBounce(gpioNumber))
    return;

  GPIO_PinInfo_t gpioPin = gpioPinInfoStore[gpioNumber];

  if (!gpioPin.validGPIO)
    return;

  if (state)
    GPIO_Ports[gpioPin.port]->output |= (1 << gpioPin.pin);
  else
    GPIO_Ports[gpioPin.port]->output &= ~(1 << gpioPin.pin);
}

void GPIO_ConfigurePin(uint8_t pinNumber, pinConfig_t config)
{
  if (PinOutOfBounce(pinNumber))
    return;

  GPIO_PinInfo_t gpioPin = gpioPinInfoStore[pinNumber];

  if (!gpioPin.validGPIO)
    return;

  if (config.pintype == PINTYPE_INPUT)
  {
    GPIO_Ports[gpioPin.port]->dataDirection &= ~(1 << gpioPin.pin);
    if (config.pullUpActive)
    {
      GPIO_Ports[gpioPin.port]->output |= (1 << gpioPin.pin);
    }
    else
    {
      GPIO_Ports[gpioPin.port]->output &= ~(1 << gpioPin.pin);
    }
  }
  else
  {
    GPIO_Ports[gpioPin.port]->dataDirection |= (1 << gpioPin.pin);
    GPIO_Ports[gpioPin.port]->output &= ~(1 << gpioPin.pin);
  }
}

static bool PinOutOfBounce(uint8_t pin)
{
  if (pin >= PIN_MAX)
    return true;
  else
    return false;
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
