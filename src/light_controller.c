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
    if (IOMapper_GetPinState(LightsOn))
      SetLightByDirection(TRAVEL_DIRECTION_FORWARD);
    else
      SetLightByDirection(TRAVEL_DIRECTION_BACKWARD);
    break;

  case LIGHT_STATE_AUTOMATIC:
    SetLightByDirection(TravelController_GetDirection());
    break;
  }
}

lightModuleState_t LightController_GetModuleState()
{
  return state;
}

void SetLightByDirection(travelDirection_t direction)
{
  if (direction == TRAVEL_DIRECTION_FORWARD)
    SetForwardLight();
  else
    SetBackwardLight();
}

void SetForwardLight(void)
{
  IOMapper_SetPinState(LightsFront, IO_STATE_ON);
  IOMapper_SetPinState(LightsRear, IO_STATE_OFF);
}

void SetBackwardLight(void)
{
  IOMapper_SetPinState(LightsFront, IO_STATE_OFF);
  IOMapper_SetPinState(LightsRear, IO_STATE_ON);
}

void TurnOffLights(void)
{
  IOMapper_SetPinState(LightsFront, IO_STATE_OFF);
  IOMapper_SetPinState(LightsRear, IO_STATE_OFF);
}

void ReadStateFromIO(void)
{
  if (IOMapper_GetPinState(LightsMain))
    if (IOMapper_GetPinState(LightsAutomatic))
      state = LIGHT_STATE_AUTOMATIC;
    else
      state = LIGHT_STATE_MANUAL;
  else
    state = LIGHT_STATE_OFF;
}