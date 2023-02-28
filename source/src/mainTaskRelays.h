#ifndef MAINTASKRELAYS_H
#define MAINTASKRELAYS_H
#include "mainDefines.h"
void g_MainTaskRelays(void *pvParameters)
{

#ifdef DEBUG
  //Serial.println("");
  //Serial.print("g_TaskCore_1_LoopRelays running on core ");
  //Serial.println(xPortGetCoreID());
#endif
  for (;;)
  {
g_TimeSun.loop();
    for (int i = 0; i < g_RelaysCount; i++)
    {
      g_Relays[i].loop(g_TimeSun.IsSunrise());
      
    }
    
  }
}
#endif