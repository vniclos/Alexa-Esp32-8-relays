#ifndef MAINDEFINES_H
#define MAINDEFINES_H
#include <Arduino.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "fauxmoESP.h"
#include "ClsRelay.h"
#include "ClsTimeSun.h"
#include "ClsWifiConfig.h"
#define SERIAL_BAUDRATE  115200
  StaticJsonDocument<1024> g_docJsonRelays;
ClsTimeSun g_TimeSun;
ClsWifiConfig g_Config;
//------ RELAYS
uint32_t g_RelayDelayLoop = 1;
const int g_RelaysCount = 8;
ClsRelay g_Relays[g_RelaysCount];
//------ HADWARE PINS USED
const int g_pinIntLedBlue =2;
const int g_pingSensorLed = 23;
//int g_pinRelays[4] = {26, 25, 33, 32}; 
//int g_pinRelays[8] = {23, 21, 19, 4, 25, 16, 13, 26};
int g_pinRelays[g_RelaysCount] =   {23, 21, 19, 4, 25, 16, 13, 26}; 
//-------------- NET SERVICES 
unsigned long g_AlexaLastMillis =0;
fauxmoESP g_NetFauxmoAlexa;
AsyncWebServer g_NetWebServer(80);
// THIS IS THE NAMES joined to reralys TO SAY alexa command 
// example like: "Alexa! turn on relay 1"
const char g_AlexaDeviceNames[8][8]={{"belen 1"},{"belen 2"},{"belen 3"},{"belen 4"},{"belen 5"},{"belen 6"},{"belen 7"},{"belen 8"}};

TaskHandle_t g_MainTaskAlexaHandle;
TaskHandle_t g_MainTaskTimeSunHandle;
TaskHandle_t g_MainTaskRelaysHandle;
void g_MainTaskAlexa(void *pvParameters);
void g_MainTaskTimeSun(void *pvParameters);
void g_MainTaskRelays(void *pvParameters);

bool fncRelaysJsonApply(String sJson);

#endif