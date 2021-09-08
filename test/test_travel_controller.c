#include "../unity.framework/src/unity.h"
#include "../src/travel_controller.h"
#include "mock_io_mapper.h"

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

void test_DirectionChangePossible()
{
  uint8_t initSpeed = 2;
  travelDirection_t initialDirection = TRAVEL_DIRECTION_FORWARD;

  IOMapper_GetControlSource_IgnoreAndReturn(IO_STATE_ON);
  IOMapper_SetDirectionAVR_Ignore();

  IOMapper_GetDirectionState_ExpectAndReturn(IO_STATE_OFF);
  TravelController_Init(initSpeed, initialDirection);

  TravelController_Update();
  TEST_ASSERT_EQUAL(TravelController_GetDirection(), TRAVEL_DIRECTION_FORWARD);
  IOMapper_GetDirectionState_ExpectAndReturn(IO_STATE_ON);
  TravelController_Update();
  TEST_ASSERT_EQUAL(TravelController_GetDirection(), TRAVEL_DIRECTION_BACKWARD);
}

void test_DirectionChangeChangesOutput()
{
  IOMapper_GetControlSource_IgnoreAndReturn(IO_STATE_OFF);
  IOMapper_GetDirectionState_ExpectAndReturn(IO_STATE_OFF);
  IOMapper_SetDirectionAVR_Expect(IO_STATE_OFF);
  TravelController_Update();
  IOMapper_GetDirectionState_ExpectAndReturn(IO_STATE_ON);
  IOMapper_SetDirectionAVR_Expect(IO_STATE_ON);
  TravelController_Update();
}

void test_NoDirectionChangeAboveSpeedLimit()
{
  IOMapper_GetControlSource_IgnoreAndReturn(IO_STATE_OFF);
  IOMapper_SetDirectionAVR_Expect(IO_STATE_OFF);
  TravelController_Init(99, TRAVEL_DIRECTION_FORWARD);
  TravelController_Update();
}

void test_UpdateRequestsControlSource()
{
  IOMapper_SetDirectionAVR_Ignore();
  IOMapper_GetDirectionState_IgnoreAndReturn(IO_STATE_ON);
  TravelController_SetSpeed(1);
  IOMapper_GetControlSource_ExpectAndReturn(IO_STATE_ON);
  TravelController_Update();
  IOMapper_GetControlSource_ExpectAndReturn(IO_STATE_OFF);
  TravelController_Update();
}
