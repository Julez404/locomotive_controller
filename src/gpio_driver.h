/** \file  gpio_driver.h
 *  \brief Handle GPIO access
 */
#ifndef GPIO_DRIVER
#define GPIO_DRIVER

//*****************************************************************************
// Includes
//*****************************************************************************
#include "../src/sw_conf.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

//*****************************************************************************
// Preprocessor Constants
//*****************************************************************************

//*****************************************************************************
// Configuration Constants
//*****************************************************************************

//*****************************************************************************
// Macros
//*****************************************************************************

//*****************************************************************************
// Typedefs
//*****************************************************************************
typedef enum
{
  PINTYPE_INPUT,
  PINTYPE_OUTPUT
} pintype_t;

typedef struct pinConfig
{
  pintype_t pintype;
  bool pullUpActive;
} pinConfig_t;

typedef struct GPIO_Port
{
  // Input
  uint8_t input : 6;

  // Direction
  uint8_t dataDirection : 8;

  // Output / PullUp
  uint8_t output : 8;
} GPIO_Port_t;

//*****************************************************************************
// Variables
//*****************************************************************************

//*****************************************************************************
// Function Prototypes
//*****************************************************************************

/**
 * @brief Init the module
 *
 * @remark Sets every GPIO Pin to Input, Pull-UP active.
 */
void GPIO_Init(GPIO_Port_t *portB_addr, GPIO_Port_t *portC_addr, GPIO_Port_t *portD_addr);

/**
 * @brief Configure a pin
 *
 * @param gpioPin Pin number of the selected pin
 * @param config Desired pin configuration
 */
void GPIO_ConfigurePin(uint8_t gpioPin, pinConfig_t config);

/**
 * @brief Get the State of a GPIO Pin.
 *
 * @param Pin numer of the GPIO Pin
 * @return true
 * @return false
 */
bool GPIO_GetPin(uint8_t gpioNumber);

/**
 * @brief Set the provided Pin to a given value.
 *
 * @remark Pin must previously be defined as output.
 * @param gpioNumber Pin number
 * @param state State the pin should be set to
 */
void GPIO_SetPin(uint8_t gpioNumber, bool state);

/**
 * @brief Utility to check if a given pin is valid.
 * Valid meaning the pin is in the valid range of available
 * pin.
 */
bool GPIO_IsValidPin(int8_t pin);

#endif