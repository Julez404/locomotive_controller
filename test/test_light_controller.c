#include "../unity.framework/src/unity.h"
#include "../src/light_controller.h"
#include "mock_travel_controller.h"
#include "mock_io_mapper.h"

void test_ModeIsOffWhenWhenMainAndAutomaticAreOff()
{
  IOMapper_GetPinState_ExpectAndReturn(LightsMain, IO_STATE_OFF);
  IOMapper_GetPinState_IgnoreAndReturn(IO_STATE_OFF);
  IOMapper_SetPinState_Ignore();

  LightController_Update();
  TEST_ASSERT_EQUAL(LightController_GetModuleState(), LIGHT_STATE_OFF);
}

void test_ModeIsOffWhenWhenMainIsOffButAutomaticIsOn()
{
  IOMapper_GetPinState_ExpectAndReturn(LightsMain, IO_STATE_OFF);
  IOMapper_GetPinState_IgnoreAndReturn(IO_STATE_ON);
  IOMapper_SetPinState_Ignore();

  LightController_Update();
  TEST_ASSERT_EQUAL(LightController_GetModuleState(), LIGHT_STATE_OFF);
}

void test_ModeIsManualWhenMainIsOnAndAutomaticIsOff()
{
  IOMapper_GetPinState_ExpectAndReturn(LightsMain, IO_STATE_ON);
  IOMapper_GetPinState_ExpectAndReturn(LightsAutomatic, IO_STATE_OFF);
  IOMapper_GetPinState_ExpectAndReturn(LightsOn, IO_STATE_OFF);
  IOMapper_SetPinState_Ignore();

  LightController_Update();
  TEST_ASSERT_EQUAL(LightController_GetModuleState(), LIGHT_STATE_MANUAL);
}

void test_ModeIsAutomaticWhenMainIsOnAndAutomaticIsOn()
{
  IOMapper_GetPinState_ExpectAndReturn(LightsMain, IO_STATE_ON);
  IOMapper_GetPinState_ExpectAndReturn(LightsAutomatic, IO_STATE_ON);
  TravelController_GetDirection_IgnoreAndReturn(TRAVEL_DIRECTION_BACKWARD);
  IOMapper_SetPinState_Ignore();
  IOMapper_SetPinState_Ignore();
  LightController_Update();
  TEST_ASSERT_EQUAL(LightController_GetModuleState(), LIGHT_STATE_AUTOMATIC);
}

void test_AutomaticModeCallsTravelDirection()
{
  IOMapper_GetPinState_ExpectAndReturn(LightsMain, IO_STATE_ON);
  IOMapper_GetPinState_ExpectAndReturn(LightsAutomatic, IO_STATE_ON);
  IOMapper_SetPinState_Ignore();
  TravelController_GetDirection_ExpectAndReturn(TRAVEL_DIRECTION_FORWARD);
  LightController_Update();
}

void test_AutomaticForwardsSetsForwardLight()
{
  IOMapper_GetPinState_ExpectAndReturn(LightsMain, IO_STATE_ON);
  IOMapper_GetPinState_ExpectAndReturn(LightsAutomatic, IO_STATE_ON);
  TravelController_GetDirection_ExpectAndReturn(TRAVEL_DIRECTION_FORWARD);
  IOMapper_SetPinState_Expect(LightsFront, IO_STATE_ON);
  IOMapper_SetPinState_Expect(LightsRear, IO_STATE_OFF);

  LightController_Update();
}

void test_AutomaticBackwardSetsBackwardLight()
{
  IOMapper_GetPinState_ExpectAndReturn(LightsMain, IO_STATE_ON);
  IOMapper_GetPinState_ExpectAndReturn(LightsAutomatic, IO_STATE_ON);
  TravelController_GetDirection_ExpectAndReturn(TRAVEL_DIRECTION_BACKWARD);
  IOMapper_SetPinState_Expect(LightsFront, IO_STATE_OFF);
  IOMapper_SetPinState_Expect(LightsRear, IO_STATE_ON);
  LightController_Update();
}

void test_ManualLightForwardSwitchSetsForwardLights()
{
  IOMapper_GetPinState_ExpectAndReturn(LightsMain, IO_STATE_ON);
  IOMapper_GetPinState_ExpectAndReturn(LightsAutomatic, IO_STATE_OFF);
  IOMapper_GetPinState_ExpectAndReturn(LightsOn, IO_STATE_ON);
  IOMapper_SetPinState_Expect(LightsFront, IO_STATE_ON);
  IOMapper_SetPinState_Expect(LightsRear, IO_STATE_OFF);
  LightController_Update();
}

void test_ManualLightForwardSwitchSetsBackwardLights()
{

  IOMapper_GetPinState_ExpectAndReturn(LightsMain, IO_STATE_ON);
  IOMapper_GetPinState_ExpectAndReturn(LightsAutomatic, IO_STATE_OFF);
  IOMapper_GetPinState_ExpectAndReturn(LightsOn, IO_STATE_OFF);
  IOMapper_SetPinState_Expect(LightsFront, IO_STATE_OFF);
  IOMapper_SetPinState_Expect(LightsRear, IO_STATE_ON);
  LightController_Update();
}

void test_LightsTurnOffInModeOff()
{
  IOMapper_GetPinState_ExpectAndReturn(LightsMain, IO_STATE_OFF);
  IOMapper_SetPinState_Expect(LightsFront, IO_STATE_OFF);
  IOMapper_SetPinState_Expect(LightsRear, IO_STATE_OFF);
  LightController_Update();
}
