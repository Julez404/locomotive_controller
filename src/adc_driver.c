/** \file _template.c
 * \brief This module contains the 
 */
//*****************************************************************************
// Includes
//*****************************************************************************
#include "adc_driver.h"
#include "sw_conf.h"

//*****************************************************************************
// Module Preprocessor Constants
//*****************************************************************************

//*****************************************************************************
// Module Preprocessor Macros
//*****************************************************************************

//*****************************************************************************
// Module Typedefs
//*****************************************************************************
typedef enum ADC_Reference
{
  ADC_REFERENCE_AREF,
  ADC_REFERENCE_AVCC,
  ADC_REFERENCE_1v1,
  ADC_REFERENCE_2v56,
} ADC_Reference_t;

typedef enum ADC_Divider
{
  ADC_DIVIDER_2,
  ADC_DIVIDER_4,
  ADC_DIVIDER_8,
  ADC_DIVIDER_16,
  ADC_DIVIDER_32,
  ADC_DIVIDER_64,
  ADC_DIVIDER_128,
} ADC_Divider_t;

//*****************************************************************************
// Module Variable Definitions
//*****************************************************************************
/**
 * @brief channelValues stores the latest analog readouts.
 * @remark If a channel is disabled, the value is "-1"
 */
uint8_t channelValues[ADC_CHANNEL_COUNT] = {0};
bool activeChannels[ADC_CHANNEL_COUNT] = {0};
ADC_Analog_t *Analog = (ADC_Analog_t *)(0x78);
uint8_t currentChannel;

//*****************************************************************************
// Function Prototypes
//*****************************************************************************
bool ConversionActive(void);
void StoreResultForChannel(uint8_t channel);
bool AnyChannelActive(void);
uint8_t GetNextActiveChannel(uint8_t channel);

//*****************************************************************************
// Function Definitions
//*****************************************************************************
void ADC_Init(ADC_Analog_t *analogHardware)
{
  Analog = analogHardware;

  Analog->referenceVoltage = ADC_REFERENCE_AVCC;
  Analog->interruptEnable = false;
  Analog->clockDivider = ADC_DIVIDER_128;
  Analog->autoTriggerEnable = false;
  Analog->resultJustification = false;
  Analog->enable = true;
  Analog->startConversion = false;

  for (int ch = 0; ch < ADC_CHANNEL_COUNT; ch++)
  {
    channelValues[ch] = ADC_CHANNEL_INACTIVE;
    activeChannels[ch] = false;
  }

  currentChannel = 0;
}

void ADC_Update()
{
  if (ConversionActive())
    return;

  if (AnyChannelActive())
  {
    StoreResultForChannel(currentChannel);
    currentChannel = GetNextActiveChannel(currentChannel);
    Analog->startConversion = true;
  }
}

/**
 * @brief Get the Next Active Channel object
 * @remark Only call this function when at least one channel is active.
 * @return uint8_t 
 */
uint8_t GetNextActiveChannel(uint8_t channel)
{
  int lookupStart = channel + 1;
  int returnValue = channel;
  if (lookupStart == ADC_CHANNEL_COUNT)
    lookupStart = 0;

  for (int ch = 0; ch < ADC_CHANNEL_COUNT; ch++)
  {
    int iterateChannel = lookupStart + ch;
    if (iterateChannel >= ADC_CHANNEL_COUNT)
      iterateChannel -= ADC_CHANNEL_COUNT;
    if (activeChannels[iterateChannel])
    {
      returnValue = iterateChannel;
      break;
    }
  }
  return returnValue;
}

bool AnyChannelActive(void)
{
  for (int ch = 0; ch < ADC_CHANNEL_COUNT; ch++)
  {
    if (activeChannels[ch])
      return true;
  }
  return false;
}

bool ConversionActive(void)
{
  return Analog->startConversion;
}

void StoreResultForChannel(uint8_t channel)
{
  uint16_t temp = Analog->value;
  uint8_t percentage = (uint32_t)(temp * 100) / ADC_MAX_VALUE;
  channelValues[channel] = percentage;
}

int8_t ADC_GetChannelReading(uint8_t channel)
{
  return channelValues[channel];
}

void ADC_ActivateChannel(uint8_t channel)
{
  if (!AnyChannelActive())
    currentChannel = channel;

  activeChannels[channel] = true;
}

void ADC_DeactivateChannel(uint8_t channel)
{
  activeChannels[channel] = false;
}
// ---------------------------------------------------------------------------
