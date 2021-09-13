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
enum Ports
{
  PORTB,
  PORTC,
  PORTD,
  PORT_MAX
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

//*****************************************************************************
// Function Prototypes
//*****************************************************************************
static int8_t GetPortFromPin(uint8_t pin);
static uint8_t GetPortPinFromPin(uint8_t pin);
static void SetPortsToDefaultConfig();

//*****************************************************************************
// Function Definitions
//*****************************************************************************
void GPIO_Init(GPIO_Port_t *portB_addr, GPIO_Port_t *portC_addr, GPIO_Port_t *portD_addr)
{
  // Load default Hardware addresses if needed
  if (portB_addr == NULL)
    portB_addr = (GPIO_Port_t *)0x03;
  if (portC_addr == NULL)
    portC_addr = (GPIO_Port_t *)0x06;
  if (portD_addr == NULL)
    portD_addr = (GPIO_Port_t *)0x09;

  GPIO_Ports[PORTB] = portB_addr;
  GPIO_Ports[PORTC] = portC_addr;
  GPIO_Ports[PORTD] = portD_addr;

  SetPortsToDefaultConfig();
}

bool GPIO_GetPin(uint8_t gpioNumber)
{
  return true;
}

void GPIO_SetPin(uint8_t gpioNumber, bool state)
{
  return;
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

static uint8_t GetPortPinFromPin(uint8_t pin)
{
  switch (pin)
  {
  case 12:
  case 23:
  case 30:
    return 0;
  case 13:
  case 24:
  case 31:
    return 1;
  case 14:
  case 25:
  case 32:
    return 2;
  case 1:
  case 15:
  case 26:
    return 3;
  case 2:
  case 16:
  case 27:
    return 4;
  case 9:
  case 17:
  case 28:
    return 5;
  case 7:
  case 10:
  case 29:
    return 6;
  case 8:
  case 11:
    return 7;
  default:
    return -1;
  }
}

static int8_t GetPortFromPin(uint8_t pin)
{
  switch (pin)
  {
  case 7:
  case 8:
  case 12:
  case 13:
  case 14:
  case 15:
  case 16:
  case 17:
    return PORTB;
  case 23:
  case 24:
  case 25:
  case 26:
  case 27:
  case 28:
  case 29:
    return PORTC;
  case 1:
  case 2:
  case 9:
  case 10:
  case 11:
  case 30:
  case 31:
  case 32:
    return PORTD;
  default:
    return -1;
  }
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
