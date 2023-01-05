#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "fauxmoESP.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "mainDefines.h"
#include "mainRingLed.h"
#include "mainSetup.h"

void setup()
{
  fncSetupHardware();
  fncSetupSoft();
  fncSetupMultiCoreTask();
  // put your setup code here, to run once:
}

//---------------------------------------------------------

// g_TaskCore_0_Loop: blinks an LED every 1000 ms
void g_TaskCore_0_LoopAlexa(void *pvParameters)
{
#ifdef DEBUG
  Serial.println("");
  Serial.print("g_TaskCore_0_Loop running on core ");
  g_TaskCore_0_Loop
      Serial.println(xPortGetCoreID());
  Serial.println("");
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
      Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
    }
  }
}
//----------------------------------------------------------

void g_TaskCore_1_LoopRingLed(void *pvParameters)
{
#ifdef DEBUG
  Serial.println("");
  Serial.print("g_TaskCore_1_LoopRingLed running on core ");
  Serial.println(xPortGetCoreID());
#endif
  g_LedsRing.begin();
  for (;;)
  {
    fncLedsRingIdleChristmas();
    vTaskDelay(g_LedsRingFadeDelayLoop / portTICK_RATE_MS);
  }
}
void g_TaskCore_1_LoopRelays(void *pvParameters)
{

#ifdef DEBUG
  Serial.println("");
  Serial.print("g_TaskCore_1_LoopRelays running on core ");
  Serial.println(xPortGetCoreID());
#endif
  for (;;)
  {

    for (int i = 0; i < g_RelaysCount; i++)
    {
      g_Relays[i].loop();
    }
  }
}

void loop()
{
  // loop is split into two separate tasks, each running that assigned to a different core
  // the tasks start  calling function   fncSetupMultiCoreTask() from setup() function
  // ----------   -------------------------------------   --------------------------
  //  Core        loop function                            main fun
  // ----------   -------------------------------------   --------------------------
  // Core 1    -> g_TaskCore_1_Loop( void * pvParameters )   -> g_WebServer.handleClient()
  // core 0    -> g_TaskCore_0_Loop ( void * pvParameters )  -> call fncloopServosWithButtons
}