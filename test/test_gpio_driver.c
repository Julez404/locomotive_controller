#include "sw_conf.h"
#include <stdint.h>
#include <stdbool.h>
#include "../src/gpio_driver.h"
#include "../unity.framework/src/unity.h"

static GPIO_Port_t portB;
static GPIO_Port_t portC;
static GPIO_Port_t portD;

void setUp()
{
    GPIO_Init(&portB, &portC, &portD);
}

void test_GpioInitsToInputWithPullUp()
{
    TEST_ASSERT_EQUAL(0b00000000, portB.dataDirection);
    TEST_ASSERT_EQUAL(0b11111111, portB.output);
}

void test_ConfigSetsExpectedOutputFlag()
{
    // PortB, 0 -> 4
    pinConfig_t config;
    config.pintype = PINTYPE_OUTPUT;
    config.pullUpActive = false;
    GPIO_ConfigurePin(12, config);
    GPIO_ConfigurePin(13, config);
    GPIO_ConfigurePin(14, config);
    GPIO_ConfigurePin(15, config);
    GPIO_ConfigurePin(16, config);

    TEST_ASSERT_EQUAL(0b00011111, portB.dataDirection);
    TEST_ASSERT_EQUAL(0b11100000, portB.output);
}

void test_OutOffBouncePinHasNoEffect()
{
    // 16 == PORTB,4
    pinConfig_t config;
    config.pintype = PINTYPE_OUTPUT;
    config.pullUpActive = false;
    GPIO_ConfigurePin(40, config);
    GPIO_ConfigurePin(-1, config);

    TEST_ASSERT_EQUAL(0b00000000, portB.dataDirection);
    TEST_ASSERT_EQUAL(0b11111111, portB.output);
    TEST_ASSERT_EQUAL(0b00000000, portC.dataDirection);
    TEST_ASSERT_EQUAL(0b11111111, portC.output);
    TEST_ASSERT_EQUAL(0b00000000, portD.dataDirection);
    TEST_ASSERT_EQUAL(0b11111111, portD.output);
}

void test_PullUpCanBeDeactivated()
{
    pinConfig_t config;
    config.pintype = PINTYPE_INPUT;
    config.pullUpActive = false;
    GPIO_ConfigurePin(2, config);

    TEST_ASSERT_EQUAL(0b00000000, portD.dataDirection);
    TEST_ASSERT_EQUAL(0b11101111, portD.output);
}