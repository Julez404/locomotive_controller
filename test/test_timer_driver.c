#include "sw_conf.h"
#include "../src/timer_driver.h"
#include "../unity.framework/src/unity.h"

void test_CallInit()
{
  TIMER_Init();
}
