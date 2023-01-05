#ifndef MAINDEFINES_H
#define MAINDEFINES_H
#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "fauxmoESP.h"
#include <Adafruit_NeoPixel.h>
#include "ClsRelay.h"
#define SERIAL_BAUDRATE  115200

 
//------ RELAYS
uint32_t g_RelayDelayLoop = 1;
const int g_RelaysCount = 8;
ClsRelay g_Relays[g_RelaysCount];

//------ HADWARE PINS USED
const int g_pinIntLedBlue =2;
const int g_pingSensorLed = 23;
const int g_pingRingLed = 15;
//int g_pinRelays[4] = {26, 25, 33, 32}; 
//int g_pinRelays[8] = {23, 21, 19, 4, 25, 16, 13, 26};
int g_pinRelays[g_RelaysCount] =   {23, 21, 19, 4, 25, 16, 13, 26}; 

//-------------- NET WIFi
const char *g_NetWsWifiSsid = "testudines";
const char *g_NetWsWifiPwd = "915265ABCD";
IPAddress g_NetWsIPAddresslocal_IP(192, 168, 2, 41);
IPAddress g_NetWsIpGateway(192, 168, 2, 1);
IPAddress g_NetWsIpSubnet(255, 255, 255, 0);
IPAddress g_NetWsIpDNS1(8, 8, 8, 8); // optional
IPAddress g_NetWSIpDNS2(8, 8, 4, 4); //optional
long g_NetWsWifiIntervalPrevious = 0;
long g_NetWsWifiIntervalLapse = 30000;




//-------------- NET SERVICES 
unsigned long g_AlexaLastMillis =0;
fauxmoESP g_NetFauxmoAlexa;
AsyncWebServer g_NetWebServer(80);
// THIS IS THE NAMES joined to reralys TO SAY alexa command 
// example like: "Alexa! turn on relay 1"

const char g_AlexaDeviceNames[8][8]={{"relay 1"},{"relay 2"},{"relay 3"},{"relay 4"},{"relay 5"},{"relay 6"},{"relay 7"},{"relay 8"}};

//---------------- RINGLED
double g_RingLedLastColorUpdate = 0;     // Epoch of last color update (local or remote)
String g_RingLedColorFromID;             // String, Tracks who sent the color (for debug)
uint16_t g_RingLedColorRecieved;         // 0 - 255, Tracks the color received from another lamp
bool g_RingLedLampOn = 0;                // Tracks if the lamp is lit
uint8_t g_RingLedActiveColor = 0;        // 0 - 255, Tracks what color is currently g_RingLedActive (default to red)
uint8_t g_RingLedActiveR = 255;          // 0 - 255, Red component of g_RingLedActiveColor;
uint8_t g_RingLedActiveG = 0;            // 0 - 255, Green component of g_RingLedActiveColor;
uint8_t g_RingLedActiveB = 0;            // 0 - 255, Blue component of g_RingLedActiveColor;
uint32_t g_RingLedDecayTime = 3600;      // Turn off light after elapsed seconds
uint32_t g_RingLedDecayDelay = 5;        // Seconds between g_RingLedDecay fade-out
uint32_t g_RingLedDecayDelayCounter = 0; // Tracker for g_RingLedDecayDelay
int16_t g_RingLedLampBrightness = 70;    // 0 - 255, Tracks current lamp brightness
byte g_RingLedActivePixels = 0;          // Tracks Pixels g_RingLedActive during various functions
uint32_t g_RingLedFadeColor = 0;
uint32_t g_LedsRingFadeDelay = 1000;
uint32_t g_LedsRingFadeDelayLoop = 100;
const int g_RingLedNum = 24;
Adafruit_NeoPixel g_LedsRing = Adafruit_NeoPixel(g_RingLedNum, g_pingRingLed, NEO_GRB + NEO_KHZ800);
uint32_t fncLedsRingwheelColor(uint16_t WheelPos, uint16_t iBrightness);
void fncLedsRingIdleChristmas();
TaskHandle_t g_TaskCore_0_HandleAlexa;
TaskHandle_t g_TaskCore_1_HandleRingLed;
TaskHandle_t g_TaskCore_1_HandleRelays;
void g_TaskCore_0_LoopAlexa(void *pvParameters);
void g_TaskCore_1_LoopRingLed(void *pvParameters);
void g_TaskCore_1_LoopRelays(void *pvParameters);

#endif