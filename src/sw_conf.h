#ifndef SWCONF
#define SWCONF

#define __AVR_ATMEGA328P__
#define F_CPU 16000000

typedef enum GPIO_PinAssignment
{
  LightsAutomatic = 1,
  DirectionControl = 12,
  LightsRear = 16,
  LightsFront = 17,
  Gas_Input = 23,
  Break_Input = 24,
  Laut_Input = 25,
  Spare_Input = 26,
  LightsOn = 27,
  ControlSource = 30,
  DirectionSelection = 31,
  LightsMain = 32,
  PinFunction_Last=33
} GPIO_PinAssignment_t;

#endif