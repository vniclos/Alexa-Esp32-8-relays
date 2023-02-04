#ifndef MAINDEFINES_H
#define MAINDEFINES_H
#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "fauxmoESP.h"
#include <Adafruit_NeoPixel.h>
#include "ClsRelay.h"
#include "ClsTimeSun.h"
#include "ClsConfig.h"
#define SERIAL_BAUDRATE  115200

ClsTimeSun g_TimeSun;
ClsConfig g_Config;
 
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


TaskHandle_t g_TaskCore_0_HandleAlexa;
TaskHandle_t g_TaskCore_1_HandleNetWork;
TaskHandle_t g_TaskCore_1_HandleRelays;
void g_TaskCore_0_LoopAlexa(void *pvParameters);
void g_TaskCore_1_LoopNetWork(void *pvParameters);
void g_TaskCore_1_LoopRelays(void *pvParameters);

#endif