/** \file _template.h
 *  \brief This module contains continuous tasks.
 */
#ifndef TRAVEL_CONTROLLER_H
#define TRAVEL_CONTROLLER_H

//*****************************************************************************
// Includes
//*****************************************************************************
#include "io_mapper.h"
#include <stdint.h>
#include <stdbool.h>

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
  TRAVEL_CONTROL_SOURCE_REMOTE,
  TRAVEL_CONTROL_SOURCE_LOCAL

} travelControlSource_t;

typedef enum
{
  TRAVEL_DIRECTION_FORWARD,
  TRAVEL_DIRECTION_BACKWARD
} travelDirection_t;

//*****************************************************************************
// Variables
//*****************************************************************************

//*****************************************************************************
// Function Prototypes
//*****************************************************************************
/**
 * @brief Initialize the Travel controller with given values.
 * 
 * @param initialSpeedValue Speed to start the module with.
 * @param initialDirection Direction to start in.
 */
void TravelController_Init(uint8_t initialSpeedValue, travelDirection_t initialDirection);

/**
 * @brief Update function, should be frequently called by scheduler.
 * Handles the main logic of the module.
 * 1. Query current GPIO state
 * 
 */
void TravelController_Update(void);

/**
 * @brief Return the current travel direction
 * 
 * @return travelDirection_t The current travel direction
 */
travelDirection_t TravelController_GetDirection();

/**
 * @brief Function to set the travel speed.
 * @remark Function might change in future development
 *
 * @param speedPercentage Speed to set the controller to. Should be between 0 and 100%
 * @remark If parameter value is out of bounce, value is ignored!
 */
void TravelController_SetSpeed(uint8_t speedPercentage);
/**
 * @brief Function to receive the currently set speed.
 * @remark Function might change in future development
 * @return uint8_t Speed: Percentage value of current speed in 0..100%
 */
uint8_t TravelController_GetSpeed(void);

#endif