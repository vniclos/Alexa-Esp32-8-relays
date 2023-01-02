#ifndef MAINDEFINES_H
#define MAINDEFINES_H
#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "fauxmoESP.h"
#include <Adafruit_NeoPixel.h>
#include "ClsRelay.h"

#define SERIAL_BAUDRATE 115200
const int g_pinIntLedBlue = 2;
const int g_pingSensorLed = 23;
const int g_pingRingLed = 15;
// 34 32 out
//// library esp32_servo Recommend only the following pins 2,4,12-19,21-23,25-27,32-33
//const int g_PinsServo[6] =             {21x,       4x,           19x,              32falla,             23x,             33};
int g_pinRelays[8] = {23, 21, 19, 4, 25, 16, 13, 26}; // 3534}

//------ RELAYS
uint32_t g_RelayDelayLoop = 1;
const int g_RelaysCount = 8;
ClsRelay g_Relays[g_RelaysCount];

//--------------------- alexa
const char g_AlexaDeviceName_Belen1[] = "belen 1";   // rele 0
const char g_AlexaDeviceName_Belen2[] = "belen 2";    // rele 1
const char g_AlexaDeviceName_Belen3[] = "belen 3";    // rele 2
const char g_AlexaDeviceName_Belen4[] = "belen 4"; // rele 3
const char g_AlexaDeviceName_Belen5[] = "belen 5"; // rele 3
const char g_AlexaDeviceName_Belen6[] = "belen 6"; // rele 3
const char g_AlexaDeviceName_Belen7[] = "belen 7"; // rele 3
const char g_AlexaDeviceName_Belen8[] = "belen 8"; // rele 3
                                                      // const char g_AlexaDeviceNames[8][8]={{"rele 1"},{"rele 3"},{"rele 3"},{"rele 4"},{"rele 5"},{"rele 6"},{"rele 7"},{"rele 8"}};

//-------------- NET SERVICES
unsigned long g_AlexaLastMillis = 0;
fauxmoESP g_NetFauxmoAlexa;
AsyncWebServer g_NetWebServer(80);

long g_NetWsWifiIntervalPrevious = 0;
long g_NetWsWifiIntervalLapse = 30000;
const char *g_NetWsWifiSsid = "testudines";
const char *g_NetWsWifiPwd = "915265ABCD";
IPAddress g_NetWsIPAddresslocal_IP(192, 168, 2, 41);
IPAddress g_NetWsIpGateway(192, 168, 2, 1);
IPAddress g_NetWsIpSubnet(255, 255, 255, 0);
IPAddress g_NetWsIpDNS1(8, 8, 8, 8); // optional
IPAddress g_NetWSIpDNS2(8, 8, 4, 4); // optional

TaskHandle_t g_TaskCore_0_HandleAlexa;
TaskHandle_t g_TaskCore_1_HandleRingLed;
TaskHandle_t g_TaskCore_1_HandleRelays;
void g_TaskCore_0_LoopAlexa(void *pvParameters);

void g_TaskCore_1_LoopRelays(void *pvParameters);

#endif