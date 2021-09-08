#include "travel_controller.h"
#include "io_mapper.h"

// Public methodes

// Get the current travel direction
// Set travel direction(forward/backward)

// Get current speed
// Set Speed(%)

// Inputs
/* 
Umschalt-B
Richtung
B-Gas
L-Gas
L-Bremse
L-
*/

static uint8_t currentSpeed;
static travelDirection_t currentDirection;
static travelControlSource_t currentControlSource;
static void ReadControllerSourceSwitch(void);
static bool SpeedIsSaveToSwitch(void);
static void ReadDirectionSwitch(void);
static void SetDirectionOutput(void);

/**
 * @brief Maximum speed where direction switch is allowed
 */
static const uint8_t directionSwitchSpeedLimit = 4;

void TravelController_Init(uint8_t initialSpeedValue, travelDirection_t initialDirection)
{
  // Protection ???
  // No Output if input was not once below Init Value?

  currentDirection = initialDirection;
  currentSpeed = initialSpeedValue;
}

/**
 * @brief Update function, called every x ms.
 * 
 */
void TravelController_Update(void)
{
  // Read input
  ReadControllerSourceSwitch();
  ReadDirectionSwitch();

  // Validate inputs if nessesary

  // Output information
  SetDirectionOutput();
}

static void ReadControllerSourceSwitch(void)
{
  if (SpeedIsSaveToSwitch())
  {
    if (IOMapper_GetControlSource() == IO_STATE_ON)
      currentControlSource = TRAVEL_CONTROL_SOURCE_REMOTE;
    else
      currentControlSource = TRAVEL_CONTROL_SOURCE_LOCAL;
  }
}

static void SetDirectionOutput()
{
  if (currentDirection == TRAVEL_DIRECTION_FORWARD)
    IOMapper_SetDirectionAVR(IO_STATE_OFF);
  else
    IOMapper_SetDirectionAVR(IO_STATE_ON);
}

static void ReadDirectionSwitch()
{
  if (SpeedIsSaveToSwitch())
  {
    if (IOMapper_GetDirectionState() == IO_STATE_ON)
      currentDirection = TRAVEL_DIRECTION_BACKWARD;
    else
      currentDirection = TRAVEL_DIRECTION_FORWARD;
  }
}

static bool SpeedIsSaveToSwitch()
{
  if (currentSpeed < directionSwitchSpeedLimit)
    return true;
  else
    return false;
}

void TravelController_SetSpeed(uint8_t speedPercentage)
{
  currentSpeed = speedPercentage;
}

uint8_t TravelController_GetSpeed(void)
{
  return currentSpeed;
}

travelDirection_t TravelController_GetDirection()
{
  return currentDirection;
}
