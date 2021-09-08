#include "sw_conf.h"
#include "avr/io.h"
#include "../src/gpio_driver.h"
#include <stdbool.h>
#include "../unity.framework/src/unity.h"

void test_True()
{
    GPIO_Init();
    TEST_ASSERT_EQUAL(0,1);
}
