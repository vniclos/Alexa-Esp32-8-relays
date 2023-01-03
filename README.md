# Alexa-Esp32-8-relays
Alexa join esp32 and 8 relays modules simultanead with web server 



![alt text](https://github.com/vniclos/Alexa-Esp32-8-relays/blob/main/images/hardware.jpg?raw=true)


# Before compile change file mainDefines.h 

You need change wifi connection values and if
```c
// WIFI AJUST VALUES TO YOUR REQUERIMENTS
const char *g_NetWsWifiSsid = "PUT YOUR WIFI SSIID";
const char *g_NetWsWifiPwd = "PUT YOU WIFI PASSWORD";

IPAddress g_NetWsIPAddresslocal_IP(192, 168, 2, 41); // CHANGE TO ASIGN VALID IP FOR YOUR NETWORK
IPAddress g_NetWsIpGateway(192, 168, 2, 1); // CHANGE TO ASIGN VALID IP GATEWAY IN  YOUR NETWORK (your router)
IPAddress g_NetWsIpSubnet(255, 255, 255, 0);
IPAddress g_NetWsIpDNS1(8, 8, 8, 8); // optional
IPAddress g_NetWSIpDNS2(8, 8, 4, 4); // optional
long g_NetWsWifiIntervalPrevious = 0;
long g_NetWsWifiIntervalLapse = 30000;
//
//--------------------- ALEXA AJUST NAME TO YOUR REQUERIMENTS
// THIS IS THE NAMES TO SAY alexa command
const char g_AlexaDeviceName_Belen1[] = "belen 1";   // CHANGE TO PREFERENCED NAME FOR RELAY  0
const char g_AlexaDeviceName_Belen2[] = "belen 2";   // CHANGE TO PREFERENCED NAME FOR RELAY  0
const char g_AlexaDeviceName_Belen3[] = "belen 3";   // CHANGE TO PREFERENCED NAME FOR RELAY  0
const char g_AlexaDeviceName_Belen4[] = "belen 4"; // CHANGE TO PREFERENCED NAME FOR RELAY  0
const char g_AlexaDeviceName_Belen5[] = "belen 5"; // CHANGE TO PREFERENCED NAME FOR RELAY  0
const char g_AlexaDeviceName_Belen6[] = "belen 6"; // CHANGE TO PREFERENCED NAME FOR RELAY  0
const char g_AlexaDeviceName_Belen7[] = "belen 7"; // CHANGE TO PREFERENCED NAME FOR RELAY  0JOIN TO RELAY 0
const char g_AlexaDeviceName_Belen8[] = "belen 8"; // CHANGE TO PREFERENCED NAME FOR RELAY  0

```c

![alt text](https://github.com/vniclos/Alexa-Esp32-8-relays/blob/main/images/web_belen..jpg?raw=true)
