#ifndef MAINTASKTIMESUN_H
#define MAINTASKTIMESUN_H
#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "fauxmoESP.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "ClsTimeSun.h"
#include "mainDefines.h"

void g_MainTaskTimeSun(void *pvParameters)
{

#ifdef DEBUG
  //Serial.println("");
  //Serial.print("g_TaskCore_1_LoopNetWork running on core ");
  //Serial.println(xPortGetCoreID());
#endif
  //g_LedsRing.begin();
  for (;;)
  {
      g_Config.loop();   // if connection are lost try reconnect
      g_TimeSun.loop();
    
  }
}

#endif
