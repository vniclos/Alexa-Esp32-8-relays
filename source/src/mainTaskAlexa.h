#ifndef MAINTASKALEXA_H
#define MAINTASKALEXA_H
#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "fauxmoESP.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "mainDefines.h"
#include "mainSetupTasks.h"
// g_TaskCore_0_Loop: blinks an LED every 1000 ms
void g_MainTaskAlexa(void *pvParameters)
{
#ifdef DEBUG
  //Serial.println("");
  //Serial.print("g_TaskCore_0_Loop running on core ");
  g_TaskCore_0_Loop
      //Serial.println(xPortGetCoreID());
  //Serial.println("");
#endif
  uint64_t millisNow = 0;
  for (;;)
  {
    // fncLoopWifiWsConnect();
    //  fauxmoESP uses an async TCP server but a sync UDP server
    // Therefore, we have to manually poll for UDP packets
    millisNow = millis();
    g_NetFauxmoAlexa.handle();
    if (g_AlexaLastMillis < millisNow)
    {
      g_AlexaLastMillis = 0;
    }
    if (millisNow - g_AlexaLastMillis > 5000)
    {
      g_AlexaLastMillis = millisNow;
       ESP.getFreeHeap();
      delay(100);
      ////Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
    }
  }
}
#endif