#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include "sw_conf.h"


typedef enum
{
  LIGHT_STATE_OFF,
  LIGHT_STATE_MANUAL,
  LIGHT_STATE_AUTOMATIC
} lightModuleState_t;

// Internal States
/*
1. Off
2. On (Auto)
3. On (Manual)

*/

/**
 * @brief Funcion for cycling call to update itself
 * 
 */
void LightController_Update();

lightModuleState_t LightController_GetModuleState();


void LightController_Init();

#endif