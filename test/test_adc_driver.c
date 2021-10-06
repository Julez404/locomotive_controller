#include "sw_conf.h"
#include <stdint.h>
#include <stdbool.h>
#include "../src/adc_driver.h"
#include "../unity.framework/src/unity.h"

static ADC_Analog_t adc_hardware;

void setUp()
{
  ADC_Init(&adc_hardware);
}

void test_InactiveChannelReadsError()
{
  int i;
  for (i = 0; i < ADC_CHANNEL_COUNT; i++)
  {
    int8_t reading = ADC_GetChannelReading(i);
    TEST_ASSERT_EQUAL(ADC_CHANNEL_INACTIVE, reading);
  }

  // Check that all channels were iteratet.
  TEST_ASSERT_EQUAL(ADC_CHANNEL_COUNT, i);
}

void test_InitEnablesADC()
{
  TEST_ASSERT_EQUAL(1, adc_hardware.enable);
}

void test_NoConversionStartWhenNoChannelIsActive()
{
  ADC_Update();
  TEST_ASSERT_EQUAL(0, adc_hardware.startConversion);
}

void test_ConversionStartWhenChannelIsActive()
{
  ADC_ActivateChannel(0);
  ADC_Update();
  TEST_ASSERT_EQUAL(1, adc_hardware.startConversion);
}

void test_CheckPercentageValues()
{
  uint8_t channel = 4;
  ADC_ActivateChannel(channel);
  adc_hardware.value = 0;
  ADC_Update();
  TEST_ASSERT_EQUAL(0, ADC_GetChannelReading(channel));

  adc_hardware.startConversion = false;
  adc_hardware.value = 512;
  ADC_Update();
  TEST_ASSERT_EQUAL(50, ADC_GetChannelReading(channel));

  adc_hardware.startConversion = false;
  adc_hardware.value = 1023;
  ADC_Update();
  TEST_ASSERT_EQUAL(100, ADC_GetChannelReading(channel));
}

void test_AllActiveChannelsAreIteratet()
{
  // Activate all Channels
  for (int i = 0; i < ADC_CHANNEL_COUNT; i++)
  {
    ADC_ActivateChannel(i);
  }

  adc_hardware.value = 512; // 50%

  // Call Update CHANNEL_COUNT times
  ADC_Update();
  adc_hardware.startConversion = false;
  ADC_Update();
  adc_hardware.startConversion = false;
  ADC_Update();
  adc_hardware.startConversion = false;
  ADC_Update();
  adc_hardware.startConversion = false;
  ADC_Update();
  adc_hardware.startConversion = false;
  ADC_Update();
  adc_hardware.startConversion = false;
  ADC_Update();
  adc_hardware.startConversion = false;
  ADC_Update();
  adc_hardware.startConversion = false;

  // Check all Channels reads are valid
  TEST_ASSERT_EQUAL(50, ADC_GetChannelReading(0));
  TEST_ASSERT_EQUAL(50, ADC_GetChannelReading(1));
  TEST_ASSERT_EQUAL(50, ADC_GetChannelReading(2));
  TEST_ASSERT_EQUAL(50, ADC_GetChannelReading(3));
  TEST_ASSERT_EQUAL(50, ADC_GetChannelReading(4));
  TEST_ASSERT_EQUAL(50, ADC_GetChannelReading(5));
  TEST_ASSERT_EQUAL(50, ADC_GetChannelReading(6));
  TEST_ASSERT_EQUAL(50, ADC_GetChannelReading(7));
}

void test_NoResultStorageDuringConversion()
{
  uint8_t channel = 5;

  ADC_ActivateChannel(channel);
  adc_hardware.value = 512;
  ADC_Update();
  TEST_ASSERT_EQUAL(50, ADC_GetChannelReading(channel));

  adc_hardware.value = 0;
  adc_hardware.startConversion = true;
  ADC_Update();
  TEST_ASSERT_EQUAL(50, ADC_GetChannelReading(channel));
}

void test_ChannelCanBeDisables()
{
  uint8_t channel = 6;

  ADC_ActivateChannel(channel);
  ADC_Update();
  TEST_ASSERT_TRUE(adc_hardware.startConversion);
  adc_hardware.startConversion = false;

  ADC_DeactivateChannel(channel);
  ADC_Update();
  TEST_ASSERT_FALSE(adc_hardware.startConversion);
}