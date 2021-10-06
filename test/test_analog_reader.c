#include "sw_conf.h"
#include "../src/analog_reader.h"
#include "mock_gpio_driver.h"
#include "mock_adc_driver.h"
#include "../unity.framework/src/unity.h"

void test_InitInitializesAdcDriver()
{
  GPIO_IsValidPin_IgnoreAndReturn(true);
  ADC_Init_Expect(NULL);
  ADC_ActivateChannel_Expect(0);
  ADC_ActivateChannel_Expect(1);
  ADC_ActivateChannel_Expect(2);
  ADC_ActivateChannel_Expect(3);
  ANALOG_READER_Init();
}

void test_ValueRequestIsRelayedToDriver()
{
  GPIO_IsValidPin_IgnoreAndReturn(true);
  ADC_Init_Ignore();
  ADC_ActivateChannel_Ignore();

  ADC_GetChannelReading_ExpectAndReturn(0, 50);
  uint8_t reading = ANALOG_DRIVER_GetAnalogValue(Gas_Input);
  TEST_ASSERT_EQUAL(50, reading);
}

void test_InvalidChannelRequestReturnError()
{
  GPIO_IsValidPin_IgnoreAndReturn(true);
  ADC_Init_Ignore();
  ADC_ActivateChannel_Ignore();

  int8_t reading = ANALOG_DRIVER_GetAnalogValue(0);
  TEST_ASSERT_EQUAL(ANALOG_READER_INVALID_CHANNEL_ERROR, reading);
}

void test_InvalidPinRequestReturnError()
{
  GPIO_IsValidPin_IgnoreAndReturn(false);
  ADC_Init_Ignore();
  ADC_ActivateChannel_Ignore();

  int8_t reading = ANALOG_DRIVER_GetAnalogValue(0);
  TEST_ASSERT_EQUAL(ANALOG_READER_INVALID_CHANNEL_ERROR, reading);
}
