#ifndef TRAVEL_CONTROLLER_H
#define TRAVEL_CONTROLLER_H

#include <avr/io.h>
#include <stdbool.h>

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

void TravelController_SetSpeed(uint8_t speedPercentage);
uint8_t TravelController_GetSpeed(void);

/**
 * @brief Initialize the Travel controller with given values.
 * 
 * @param initialSpeedValue Speed to start the module with.
 * @param initialDirection Direction to start in.
 */
void TravelController_Init(uint8_t initialSpeedValue, travelDirection_t initialDirection);

/**
 * @brief 
 * 
 */
void TravelController_Update(void);

/**
 * @brief Set the travel direction of the controller.
 * Function will check the current speed to validate if a direction switch is allowed.
 * If the transition was successfull the function returns false.
 * @param direction 
 * @return * brief 
 */
bool TravelController_SetDirection(travelDirection_t direction);

/**
 * @brief Return the current travel direction
 * 
 * @return travelDirection_t The current travel direction
 */
travelDirection_t TravelController_GetDirection();

#endif