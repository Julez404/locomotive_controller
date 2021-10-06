/** \file analog_reader.h
 *  \brief This module maps pin function to the corrosponding Analog Values.
 * And relays adc_driver reading to higher up modules.
 * Activation and Deactication of Channels on Runtime is not intendet to be used.
 */
#ifndef ANALOG_READER_H
#define ANALOG_READER_H

//*****************************************************************************
// Includes
//*****************************************************************************
#include "stdint.h"
#include "sw_conf.h"
#include "adc_driver.h"
#include "gpio_driver.h"
#include <stddef.h>

//*****************************************************************************
// Preprocessor Constants
//*****************************************************************************
enum AnalogReaderErrors
{
  ANALOG_READER_ERROR = -1,
  ANALOG_READER_INVALID_CHANNEL_ERROR = -2,
  ANALOG_READER_DEACTIVATED_CHANNEL_ERROR = -3,
};

//*****************************************************************************
// Configuration Constants
//*****************************************************************************

//*****************************************************************************
// Macros
//*****************************************************************************

//*****************************************************************************
// Typedefs
//*****************************************************************************

//*****************************************************************************
// Variables
//*****************************************************************************

//*****************************************************************************
// Function Prototypes
//*****************************************************************************
/**
 * @brief Initializes the used ADC Channels on the driver level.
 * 
 */
void ANALOG_READER_Init();
/**
 * @brief Get the analog value of a given GPIO PIN.
 * 
 * @param gpio_pin The Pin from which the value should be read.
 * @return uint8_t Returns the analog value in percent.
**/
int8_t ANALOG_DRIVER_GetAnalogValue(GPIO_PinAssignment_t gpio_pin);

#endif