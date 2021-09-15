// ****************************************************************************
/** \file travel_controller.c
 * \brief Control speed This module contains the 
 */
//*****************************************************************************
// Includes
//*****************************************************************************
#include "travel_controller.h"

//*****************************************************************************
// Module Preprocessor Constants
//*****************************************************************************
/**
 * @brief Maximum speed where direction switch is allowed
 */
#define MAX_SWITCH_SPEED 4

//*****************************************************************************
// Module Preprocessor Macros
//*****************************************************************************

//*****************************************************************************
// Module Typedefs
//*****************************************************************************

//*****************************************************************************
// Module Variable Definitions
//*****************************************************************************
static uint8_t currentSpeed;
static travelDirection_t currentDirection;
static travelControlSource_t currentControlSource;

//*****************************************************************************
// Function Prototypes
//*****************************************************************************
static void ReadControllerSourceSwitch(void);
static bool SpeedIsSaveToSwitch(void);
static void ReadDirectionSwitch(void);
static void SetDirectionOutput(void);

//*****************************************************************************
// Function Definitions
//*****************************************************************************
void TravelController_Init(uint8_t initialSpeedValue, travelDirection_t initialDirection)
{
  currentDirection = initialDirection;
  currentSpeed = initialSpeedValue;
}


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
    if (IOMapper_GetPinState(ControlSource) == IO_STATE_ON)
      currentControlSource = TRAVEL_CONTROL_SOURCE_REMOTE;
    else
      currentControlSource = TRAVEL_CONTROL_SOURCE_LOCAL;
  }
}

static void SetDirectionOutput()
{
  if (currentDirection == TRAVEL_DIRECTION_FORWARD)
    IOMapper_SetPinState(DirectionControl, IO_STATE_OFF);
  else
    IOMapper_SetPinState(DirectionControl, IO_STATE_ON);
}

static void ReadDirectionSwitch()
{
  if (SpeedIsSaveToSwitch())
  {
    io_state_t currentState = IOMapper_GetPinState(DirectionSelection);
    if (currentState == IO_STATE_ON)
      currentDirection = TRAVEL_DIRECTION_BACKWARD;
    else
      currentDirection = TRAVEL_DIRECTION_FORWARD;
  }
}

static bool SpeedIsSaveToSwitch()
{
  if (currentSpeed < MAX_SWITCH_SPEED)
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
