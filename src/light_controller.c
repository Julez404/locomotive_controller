#include "light_controller.h"
#include "travel_controller.h"
#include "io_mapper.h"

static lightModuleState_t state;

static void SetForwardLight(void);
static void SetBackwardLight(void);
static void ReadStateFromIO(void);
static void SetLightByDirection(travelDirection_t direction);
static void TurnOffLights(void);

void LightController_Update()
{
  ReadStateFromIO();

  switch (state)
  {
  case LIGHT_STATE_OFF:
      TurnOffLights();
    break;
  case LIGHT_STATE_MANUAL:
    if (IOMapper_GetForwardLightsState())
      SetLightByDirection(forward);
    else
      SetLightByDirection(backward);
    break;

  case LIGHT_STATE_AUTOMATIC:
    SetLightByDirection(TravelController_GetDirection());
    break;

  default:
    // Case not reachable
    break;
  }
}

lightModuleState_t LightController_GetModuleState()
{
  return state;
}

void SetLightByDirection(travelDirection_t direction)
{
  if (direction == forward)
    SetForwardLight();
  else
    SetBackwardLight();
}

void SetForwardLight(void)
{
  IOMapper_SetForwardLightState(IO_STATE_ON);
  IOMapper_SetBackwardLightState(IO_STATE_OFF);
}

void SetBackwardLight(void)
{
  IOMapper_SetForwardLightState(IO_STATE_OFF);
  IOMapper_SetBackwardLightState(IO_STATE_ON);
}

void TurnOffLights(void)
{
  IOMapper_SetForwardLightState(IO_STATE_OFF);
  IOMapper_SetBackwardLightState(IO_STATE_OFF);
}

void ReadStateFromIO(void)
{
  if (IOMapper_GetMainLightState())
    if (IOMapper_GetAutomaticLightingState())
      state = LIGHT_STATE_AUTOMATIC;
    else
      state = LIGHT_STATE_MANUAL;
  else
    state = LIGHT_STATE_OFF;
}