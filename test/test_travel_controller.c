#include "../unity.framework/src/unity.h"
#include "../src/travel_controller.h"

void test_InitValuesGetSet()
{
  uint8_t initSpeed = 2;
  travelDirection_t initialDirection = forward;
  TravelController_Init(initSpeed, initialDirection);
  TEST_ASSERT_EQUAL(TravelController_GetDirection(), initialDirection);
  TEST_ASSERT_EQUAL(TravelController_GetSpeed(), initSpeed);
}

void test_SpeedCanBeSet()
{
  uint8_t speedToCheck = 55;
  TravelController_Init(0, forward);
  TravelController_SetSpeed(speedToCheck);
  TEST_ASSERT_EQUAL(TravelController_GetSpeed(), speedToCheck);
}

void test_DirectionChangePossible()
{
  TravelController_Init(0, forward);
  TEST_ASSERT_FALSE(TravelController_SetDirection(backward));
  TEST_ASSERT_EQUAL(TravelController_GetDirection(), backward);
  TEST_ASSERT_FALSE(TravelController_SetDirection(forward));
  TEST_ASSERT_EQUAL(TravelController_GetDirection(), forward);
}

void test_NoDirectionChangeAboveSpeedLimit()
{
  uint8_t switchSpeedLimit = 5;
  TravelController_Init(10, backward);
  TEST_ASSERT_TRUE(TravelController_SetDirection(forward));
  TEST_ASSERT_EQUAL(TravelController_GetDirection(), backward);
}