#ifndef MAINSETUPRELAYS_H
#define MAINSETUPRELAYS_H
#include "mainDefines.h"
#include "ClsRelay.h"

void fncMainSetupRelays()
{
  // set all relays to off allways and mode fixed
  for (uint8_t i = 0; i < g_RelaysCount; i++)
  {
    //eProgramationMode programtionMode, eProgramationTime programtionTime
    g_Relays[i].setup(i, g_pinRelays[i],g_AlexaDeviceNames[i],ClsRelay::FIXED_ON,ClsRelay::OFF_ALWAYS);
  }
  
  fncRelaysJsonApply(g_Config.relaysJson());
  // set especific relay 0 to:   ON in lightday  and flashing mode
  //g_Relays[0].setProgramationTime_OnDay();
  //g_Relays[0].setProgramationMode_FlashingFixed();
}
#endif