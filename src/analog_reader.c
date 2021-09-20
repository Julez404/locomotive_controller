/** \file analog_reader.h
 *  \brief This module pin function to the corrosponding Analog Values
 */
//*****************************************************************************
// Includes
//*****************************************************************************
#include "analog_reader.h"

//*****************************************************************************
// Module Preprocessor Constants
//*****************************************************************************
#define GPIO_WITHOUT_ADC_CHANNEL 255
#define ACTIVE_CHANNELS 4

//*****************************************************************************
// Module Preprocessor Macros
//*****************************************************************************

//*****************************************************************************
// Module Typedefs
//*****************************************************************************

//*****************************************************************************
// Module Variable Definitions
//*****************************************************************************
uint8_t channeltToActivate[ACTIVE_CHANNELS] =
    {Gas_Input, Break_Input, Laut_Input, Spare_Input};

//*****************************************************************************
// Function Prototypes
//*****************************************************************************
uint8_t PinToAdcChannel(GPIO_PinAssignment_t gpio_pin);

//*****************************************************************************
// Function Definitions
//*****************************************************************************
void ANALOG_READER_Init()
{
  ADC_Init(NULL);

  for (int i = 0; i < ACTIVE_CHANNELS; i++)
  {
    uint8_t channel = PinToAdcChannel(channeltToActivate[i]);
    ADC_ActivateChannel(channel);
  }
}

uint8_t ANALOG_DRIVER_GetAnalogValue(GPIO_PinAssignment_t gpio_pin)
{
  uint8_t channelToRead = PinToAdcChannel(gpio_pin);
  if (channelToRead == GPIO_WITHOUT_ADC_CHANNEL)
    return 0;
  return (uint8_t)ADC_GetChannelReading(channelToRead);
}

uint8_t PinToAdcChannel(GPIO_PinAssignment_t gpio_pin)
{
  switch (gpio_pin)
  {
  case 23:
    return 0;
  case 24:
    return 1;
  case 25:
    return 2;
  case 26:
    return 3;
  case 27:
    return 4;
  case 28:
    return 5;
  case 19:
    return 6;
  case 22:
    return 7;
  default:
    return GPIO_WITHOUT_ADC_CHANNEL;
  }
}
