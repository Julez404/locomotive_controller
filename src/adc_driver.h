/** \file adc_driver.h
 *  \brief This module contains the analog driver
 */
#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

//*****************************************************************************
// Includes
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

//*****************************************************************************
// Preprocessor Constants
//*****************************************************************************
#define ADC_MAX_VALUE 1023
#define ADC_CHANNEL_INACTIVE -1
#define ADC_STEP 49
#define ADC_CHANNEL_COUNT 8

//*****************************************************************************
// Configuration Constants
//*****************************************************************************

//*****************************************************************************
// Macros
//*****************************************************************************

//*****************************************************************************
// Typedefs
//*****************************************************************************
typedef struct Analog
{
  // ADC L/H
  uint16_t value : 10;
  uint8_t reserved2 : 6;

  // ADCSRA
  uint8_t clockDivider : 3;
  uint8_t interruptEnable : 1;
  uint8_t interruptFlag : 1;
  uint8_t autoTriggerEnable : 1;
  uint8_t startConversion : 1;
  uint8_t enable : 1;

  // ADCSRB
  uint8_t autoTriggerSource : 3;
  uint8_t reserved : 5;

  // ADMUX
  uint8_t channel : 5;
  uint8_t resultJustification : 1;
  uint8_t referenceVoltage : 2;
} ADC_Analog_t;

//*****************************************************************************
// Variables
//*****************************************************************************

//*****************************************************************************
// Function Prototypes
//*****************************************************************************
/**
 * @brief 
 * 
 * @param analogHardware Analog hardware base address.
 */
void ADC_Init(ADC_Analog_t *analogHardware);
/**
 * @brief 
 * 
 */
void ADC_Update();
/**
 * @brief 
 * 
 * @return int8_t 
 */
int8_t ADC_GetChannelReading(uint8_t channel);
/**
 * @brief 
 * 
 * @param channel Channel to activate
 */
void ADC_ActivateChannel(uint8_t channel);
/**
 * @brief 
 * 
 * @param channel Channel to deactivate
 */
void ADC_DeactivateChannel(uint8_t channel);
#endif
