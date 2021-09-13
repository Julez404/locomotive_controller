#include "sw_conf.h"
#include "../src/io_mapper.h"

#include <stdbool.h>
#include "../unity.framework/src/unity.h"
#include "mock_gpio_driver.h"

void test_GetPinRequestsStateFromDriver()
{
  GPIO_GetPin_CMockExpectAndReturn(0, LightsAutomatic, IO_STATE_ON);
  TEST_ASSERT_EQUAL(IOMapper_GetPinState(LightsAutomatic), IO_STATE_ON);
  GPIO_GetPin_CMockExpectAndReturn(0, LightsAutomatic, IO_STATE_OFF);
  TEST_ASSERT_EQUAL(IOMapper_GetPinState(LightsAutomatic), IO_STATE_OFF);
}

void test_SetPinRequestsSetOnDriver()
{
  GPIO_SetPin_CMockExpect(0, LightsMain, IO_STATE_ON);
  IOMapper_SetPinState(LightsMain, IO_STATE_ON);
}
