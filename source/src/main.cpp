#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "fauxmoESP.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "mainDefines.h"
#include "mainSetup.h"
#include "mainSetupTasks.h"

#include <SPIFFS.h>

void setup()
{
  fncMainSetup();
  fncMainSetupTask();
  // put your setup code here, to run once:
}

//---------------------------------------------------------

//----------------------------------------------------------



void loop()
{
  // loop is split into two separate tasks, each running that assigned to a different core
  // the tasks start  calling function   fncSetupTask() from setup() function
  // ----------   -------------------------------------   --------------------------
  //  Core        loop function                            main fun
  // ----------   -------------------------------------   --------------------------
  // Core 1    -> g_TaskCore_1_Loop( void * pvParameters )   -> g_WebServer.handleClient()
  // core 0    -> g_TaskCore_0_Loop ( void * pvParameters )  -> call fncloopServosWithButtons
}