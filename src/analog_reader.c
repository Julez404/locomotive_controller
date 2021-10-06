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
#define ACTIVE_CHANNELS 4
#define INVALID_CHANNEL -1

//*****************************************************************************
// Module Preprocessor Macros
//*****************************************************************************

//*****************************************************************************
// Module Typedefs
//*****************************************************************************

//*****************************************************************************
// Module Variable Definitions
//*****************************************************************************
/**
 * @brief Channels to activate during initialisation
 * 
 */
uint8_t activeChannels[ACTIVE_CHANNELS] =
    {Gas_Input, Break_Input, Laut_Input, Spare_Input};

/**
 * @brief Mapping for GPIO Pin Numbers to corrosponding ADC channels.
 * 
 */
static int8_t PinToAdc[LastGPIOPin] =
    {
        INVALID_CHANNEL, // 0
        INVALID_CHANNEL, // 1
        INVALID_CHANNEL, // 2
        INVALID_CHANNEL, // 3
        INVALID_CHANNEL, // 4
        INVALID_CHANNEL, // 5
        INVALID_CHANNEL, // 6
        INVALID_CHANNEL, // 7
        INVALID_CHANNEL, // 8
        INVALID_CHANNEL, // 9
        INVALID_CHANNEL, // 10
        INVALID_CHANNEL, // 11
        INVALID_CHANNEL, // 12
        INVALID_CHANNEL, // 13
        INVALID_CHANNEL, // 14
        INVALID_CHANNEL, // 15
        INVALID_CHANNEL, // 16
        INVALID_CHANNEL, // 17
        INVALID_CHANNEL, // 18
        6,               // 19
        INVALID_CHANNEL, // 20
        INVALID_CHANNEL, // 21
        7,               // 22
        0,               // 23
        1,               // 24
        2,               // 25
        3,               // 26
        4,               // 27
        5,               // 28
        INVALID_CHANNEL, // 29
        INVALID_CHANNEL, // 30
        INVALID_CHANNEL  // 31
};

//*****************************************************************************
// Function Prototypes
//*****************************************************************************
int8_t PinToAdcChannel(GPIO_PinAssignment_t gpio_pin);

//*****************************************************************************
// Function Definitions
//*****************************************************************************
void ANALOG_READER_Init()
{
  ADC_Init(NULL);

  for (int i = 0; i < ACTIVE_CHANNELS; i++)
  {
    int8_t channel = PinToAdcChannel(activeChannels[i]);
    if (channel != INVALID_CHANNEL)
      ADC_ActivateChannel(channel);
  }
}

int8_t ANALOG_DRIVER_GetAnalogValue(GPIO_PinAssignment_t gpio_pin)
{
  int8_t channelToRead = PinToAdcChannel(gpio_pin);
  if (channelToRead == INVALID_CHANNEL)
    return ANALOG_READER_INVALID_CHANNEL_ERROR;

  return ADC_GetChannelReading(channelToRead);
}

int8_t PinToAdcChannel(GPIO_PinAssignment_t gpio_pin)
{
  if (GPIO_IsValidPin(gpio_pin))
    return PinToAdc[gpio_pin];
  else
    return INVALID_CHANNEL;
}
