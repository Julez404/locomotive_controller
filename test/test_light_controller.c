#include "../unity.framework/src/unity.h"
#include "../src/light_controller.h"
#include "mock_travel_controller.h"
#include "mock_io_mapper.h"

void test_True()
{
  TEST_ASSERT_EQUAL(1, 1);
}

void test_ModeIsOffWhenWhenMainAndAutomaticAreOff()
{
  IOMapper_GetMainLightState_ExpectAndReturn(IO_STATE_OFF);
  IOMapper_GetAutomaticLightingState_IgnoreAndReturn(IO_STATE_OFF);
  IOMapper_SetForwardLightState_Ignore();
  IOMapper_SetBackwardLightState_Ignore();
  LightController_Update();
  TEST_ASSERT_EQUAL(LightController_GetModuleState(), LIGHT_STATE_OFF);
}

void test_ModeIsOffWhenWhenMainIsOffButAutomaticIsOn()
{
  IOMapper_GetMainLightState_ExpectAndReturn(IO_STATE_OFF);
  IOMapper_GetAutomaticLightingState_IgnoreAndReturn(IO_STATE_ON);
  IOMapper_SetForwardLightState_Ignore();
  IOMapper_SetBackwardLightState_Ignore();
  LightController_Update();
  TEST_ASSERT_EQUAL(LightController_GetModuleState(), LIGHT_STATE_OFF);
}

void test_ModeIsManualWhenMainIsOnAndAutomaticIsOff()
{
  IOMapper_GetMainLightState_ExpectAndReturn(IO_STATE_ON);
  IOMapper_GetAutomaticLightingState_ExpectAndReturn(IO_STATE_OFF);
  IOMapper_GetForwardLightsState_IgnoreAndReturn(IO_STATE_OFF);
  IOMapper_SetForwardLightState_Ignore();
  IOMapper_SetBackwardLightState_Ignore();
  LightController_Update();
  TEST_ASSERT_EQUAL(LightController_GetModuleState(), LIGHT_STATE_MANUAL);
}

void test_ModeIsManualWhenMainIsOnAndAutomaticIsOn()
{
  IOMapper_GetMainLightState_ExpectAndReturn(IO_STATE_ON);
  IOMapper_GetAutomaticLightingState_ExpectAndReturn(IO_STATE_ON);
  TravelController_GetDirection_IgnoreAndReturn(backward);
  IOMapper_SetForwardLightState_Ignore();
  IOMapper_SetBackwardLightState_Ignore();
  LightController_Update();
  TEST_ASSERT_EQUAL(LightController_GetModuleState(), LIGHT_STATE_AUTOMATIC);
}

void test_AutomaticModeCallsTravelDirection()
{
  IOMapper_GetMainLightState_ExpectAndReturn(IO_STATE_ON);
  IOMapper_GetAutomaticLightingState_ExpectAndReturn(IO_STATE_ON);
  IOMapper_SetForwardLightState_Ignore();
  IOMapper_SetBackwardLightState_Ignore();
  TravelController_GetDirection_ExpectAndReturn(forward);
  LightController_Update();
}

void test_AutomaticForwardsSetsForwardLight()
{
  IOMapper_GetMainLightState_ExpectAndReturn(IO_STATE_ON);
  IOMapper_GetAutomaticLightingState_ExpectAndReturn(IO_STATE_ON);
  TravelController_GetDirection_ExpectAndReturn(forward);
  IOMapper_SetForwardLightState_Expect(IO_STATE_ON);
  IOMapper_SetBackwardLightState_Expect(IO_STATE_OFF);
  LightController_Update();
}

void test_AutomaticBackwardSetsBackwardLight()
{
  IOMapper_GetMainLightState_ExpectAndReturn(IO_STATE_ON);
  IOMapper_GetAutomaticLightingState_ExpectAndReturn(IO_STATE_ON);
  TravelController_GetDirection_ExpectAndReturn(backward);
  IOMapper_SetForwardLightState_Expect(IO_STATE_OFF);
  IOMapper_SetBackwardLightState_Expect(IO_STATE_ON);
  LightController_Update();
}

void test_ManualLightForwardSwitchSetsForwardLights()
{
  IOMapper_GetMainLightState_ExpectAndReturn(IO_STATE_ON);
  IOMapper_GetAutomaticLightingState_ExpectAndReturn(IO_STATE_OFF);
  IOMapper_GetForwardLightsState_ExpectAndReturn(IO_STATE_ON);
  IOMapper_SetForwardLightState_Expect(IO_STATE_ON);
  IOMapper_SetBackwardLightState_Expect(IO_STATE_OFF);
  LightController_Update();
}

void test_ManualLightForwardSwitchSetsBackwardLights()
{
  IOMapper_GetMainLightState_ExpectAndReturn(IO_STATE_ON);
  IOMapper_GetAutomaticLightingState_ExpectAndReturn(IO_STATE_OFF);
  IOMapper_GetForwardLightsState_ExpectAndReturn(IO_STATE_OFF);
  IOMapper_SetForwardLightState_Expect(IO_STATE_OFF);
  IOMapper_SetBackwardLightState_Expect(IO_STATE_ON);
  LightController_Update();
}

void test_LightsTurnOffInModeOff()
{
  IOMapper_GetMainLightState_ExpectAndReturn(IO_STATE_OFF);
  IOMapper_SetForwardLightState_Expect(IO_STATE_OFF);
  IOMapper_SetBackwardLightState_Expect(IO_STATE_OFF);
  LightController_Update();
}