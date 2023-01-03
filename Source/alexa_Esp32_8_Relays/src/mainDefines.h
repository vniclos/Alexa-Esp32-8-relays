#ifndef MAINDEFINES_H
#define MAINDEFINES_H
#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "fauxmoESP.h"
#include "ClsRelay.h"
// 
// WIFI AJUST VALUES TO YOUR REQUERIMENTS
const char *g_NetWsWifiSsid = "testudines";
const char *g_NetWsWifiPwd = "915265ABCD";
IPAddress g_NetWsIPAddresslocal_IP(192, 168, 2, 41);
IPAddress g_NetWsIpGateway(192, 168, 2, 1);
IPAddress g_NetWsIpSubnet(255, 255, 255, 0);
IPAddress g_NetWsIpDNS1(8, 8, 8, 8); // optional
IPAddress g_NetWSIpDNS2(8, 8, 4, 4); // optional
long g_NetWsWifiIntervalPrevious = 0;
long g_NetWsWifiIntervalLapse = 30000;
//
//--------------------- ALEXA AJUST NAME TO YOUR REQUERIMENTS
// THIS IS THE NAMES TO SAY alexa command
const char g_AlexaDeviceName_Relay1[] = "relay 1";   // JOIN TO RELAY 0
const char g_AlexaDeviceName_Relay2[] = "relay 2";   // JOIN TO RELAY 0
const char g_AlexaDeviceName_Relay3[] = "relay 3";   // JOIN TO RELAY 0
const char g_AlexaDeviceName_Relay4[] = "relay 4";   // JOIN TO RELAY 0
const char g_AlexaDeviceName_Relay5[] = "relay 5";   // JOIN TO RELAY 0
const char g_AlexaDeviceName_Relay6[] = "relay 6";   // JOIN TO RELAY 0
const char g_AlexaDeviceName_Relay7[] = "relay 7";   // JOIN TO RELAY 0
const char g_AlexaDeviceName_Relay8[] = "relay 8";   // JOIN TO RELAY 0
// const char g_AlexaDeviceNames[8][8]={{"rele 1"},{"rele 3"},{"rele 3"},{"rele 4"},{"rele 5"},{"rele 6"},{"rele 7"},{"rele 8"}};
unsigned long g_AlexaLastMillis = 0;
fauxmoESP g_NetFauxmoAlexa;
//
//-------------- NET Web
AsyncWebServer g_NetWebServer(80);
//
// PINS USED
#define SERIAL_BAUDRATE 115200
const int g_pinIntLedBlue = 2;
int g_pinRelays[8] = {23, 21, 19, 4, 25, 16, 13, 26}; // 3534}

//------ RELAYS
uint32_t g_RelayDelayLoop = 1;
const int g_RelaysCount = 8;
ClsRelay g_Relays[g_RelaysCount];
//
//-- TASK FOR ASIGN TO DISTRIBUTE WORK 
TaskHandle_t g_TaskCore_0_HandleAlexa;
TaskHandle_t g_TaskCore_1_HandleRelays;
void g_TaskCore_0_LoopAlexa(void *pvParameters);
void g_TaskCore_1_LoopRelays(void *pvParameters);

#endif
