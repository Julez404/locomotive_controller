#include "travel_controller.h"

// Public methodes

// Get the current travel direction
// Set travel direction(forward/backward)

// Get current speed
// Set Speed(%)

static uint8_t currentSpeed;
static travelDirection_t currentDirection;

// Constant Values

/**
 * @brief Maximum speed where direction switch is allowed
 */
static const uint8_t directionSwitchSpeedLimit = 5;

// Local functions
/**
 * @brief Is a switch in direction currently allowed?
 * 
 */
static bool DirectionSwitchAllowed();

void TravelController_Init(uint8_t initialSpeedValue, travelDirection_t initialDirection)
{
  // Protection ???
  // No Output if input was not once below Init Value?

  currentDirection = initialDirection;
  currentSpeed = initialSpeedValue;
}

void TravelController_SetSpeed(uint8_t speedPercentage)
{
  currentSpeed = speedPercentage;
}

uint8_t TravelController_GetSpeed(void)
{
  return currentSpeed;
}

bool TravelController_SetDirection(travelDirection_t directionToSet)
{
  if (DirectionSwitchAllowed())
  {
    currentDirection = directionToSet;
    return false;
  }
  return true;
}

travelDirection_t TravelController_GetDirection()
{
  return currentDirection;
}

static bool DirectionSwitchAllowed()
{
  if (currentSpeed < directionSwitchSpeedLimit)
    return true;
  else
    return false;
}