#include "../unity.framework/src/unity.h"
#include "../src/travel_controller.h"
#include "mock_io_mapper.h"
#include <stdio.h>

void test_InitValuesGetSet()
{
  uint8_t initSpeed = 2;
  travelDirection_t initialDirection = TRAVEL_DIRECTION_FORWARD;
  TravelController_Init(initSpeed, initialDirection);
  TEST_ASSERT_EQUAL(TravelController_GetDirection(), initialDirection);
  TEST_ASSERT_EQUAL(TravelController_GetSpeed(), initSpeed);
}

void test_SpeedCanBeSet()
{
  uint8_t speedToCheck = 55;
  TravelController_Init(0, TRAVEL_DIRECTION_FORWARD);
  TravelController_SetSpeed(speedToCheck);
  TEST_ASSERT_EQUAL(TravelController_GetSpeed(), speedToCheck);
}

void test_DirectionChangePossibleWhenSpeedIsBelowLimit()
{
  // Setup
  uint8_t initSpeed = 2;
  travelDirection_t initialDirection = TRAVEL_DIRECTION_FORWARD;

  //IOMapper_SetPinState_Ignore();
  TravelController_Init(initSpeed, initialDirection);

  // Check Forward direction
  IOMapper_GetPinState_ExpectAndReturn(ControlSource, IO_STATE_OFF);
  IOMapper_GetPinState_ExpectAndReturn(DirectionSelection, IO_STATE_OFF);
  IOMapper_SetPinState_Expect(DirectionControl, IO_STATE_OFF);
  TravelController_Update();
  TEST_ASSERT_EQUAL(TRAVEL_DIRECTION_FORWARD, TravelController_GetDirection());

  // Check Backward direction
  IOMapper_GetPinState_ExpectAndReturn(ControlSource, IO_STATE_OFF);
  IOMapper_GetPinState_ExpectAndReturn(DirectionSelection, IO_STATE_ON);
  IOMapper_SetPinState_Expect(DirectionControl, IO_STATE_ON);
  TravelController_Update();
  TEST_ASSERT_EQUAL(TRAVEL_DIRECTION_BACKWARD, TravelController_GetDirection());
}

void test_DirectionChangeChangesOutput()
{
  uint8_t initSpeed = 2;
  travelDirection_t initialDirection = TRAVEL_DIRECTION_FORWARD;

  TravelController_Init(initSpeed, initialDirection);

  IOMapper_GetPinState_ExpectAndReturn(ControlSource, IO_STATE_OFF);
  IOMapper_GetPinState_ExpectAndReturn(DirectionSelection, IO_STATE_OFF);
  IOMapper_SetPinState_Expect(DirectionControl, IO_STATE_OFF);
  TravelController_Update();

  IOMapper_GetPinState_ExpectAndReturn(ControlSource, IO_STATE_OFF);
  IOMapper_GetPinState_ExpectAndReturn(DirectionSelection, IO_STATE_ON);
  IOMapper_SetPinState_Expect(DirectionControl, IO_STATE_ON);
  TravelController_Update();
}

void test_NoDirectionChangeAboveSpeedLimit()
{
  IOMapper_GetControlSource_IgnoreAndReturn(IO_STATE_OFF);
  IOMapper_SetPinState_Expect(DirectionControl, IO_STATE_OFF);
  TravelController_Init(99, TRAVEL_DIRECTION_FORWARD);
  TravelController_Update();
}

/*
void test_SpeedInformationSourceChangesWithControlSource()
{
  // Check if PWM or Analog module is called to get the corrospondig Speed value.
  TEST_FAIL_MESSAGE("Test needs to be implemented!");
}
*/
