#ifndef MAINSETUP_H
#define MAINSETUP_H
#include "mainDefines.h"
#include "web_css.h"
#include "web_js.h"
#include "web_root.h"
#include "web_svg.h"
#include "web_favicon.h"
#include "mainBlinCk.h"
void fncSetupHardwareRelays()
{
    for (uint8_t i = 0; i < g_RelaysCount; i++)
    {
        Serial.print("Relay ");
        Serial.print(i);
        Serial.print(" pin = ");
        Serial.print(g_pinRelays[i]);
        g_Relays[i].attach(i, g_pinRelays[i], "No id");
        Serial.println("-------------------------------");
    }
    g_Relays[0].m_programation.setupFixed_OFF();
    g_Relays[1].m_programation.setupFixed_OFF();
    g_Relays[2].m_programation.setupFixed_OFF();
    g_Relays[3].m_programation.setupFixed_OFF();
    g_Relays[4].m_programation.setupFixed_OFF();
    g_Relays[5].m_programation.setupFixed_OFF();
    g_Relays[6].m_programation.setupFixed_OFF();
    g_Relays[7].m_programation.setupFixed_OFF();
    // g_Relays[4].m_programation.setupIntevalFixed(1000);
    // g_Relays[5].m_programation.setupIntevalFixed(2000);
    // g_Relays[6].m_programation.setupIntervalRandon(2000, 4500);
    // g_Relays[7].m_programation.setupIntervalRandon(5000, 20000);
    /*
    g_Relays[1].m_programation.setupFixed_ON();
    g_Relays[2].m_programation.setupIntevalFixed(1000);
    g_Relays[3].m_programation.setupIntevalFixed(1000);
    g_Relays[4].m_programation.setupIntevalFixed(1000);
    g_Relays[5].m_programation.setupIntervalRandon(1000, 5000);
    g_Relays[6].m_programation.setupIntervalRandon(1500, 8000);
    g_Relays[7].m_programation.setupIntervalRandon(2500, 10000);
    */
}
void fncSetupHardware()
{
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println("Startinng");
    Serial.println();
    pinMode(g_pinIntLedBlue, OUTPUT);
    digitalWrite(g_pinIntLedBlue, HIGH);
    fncSetupHardwareRelays();
}

void fncLoopWifiWsConnect()
{
    unsigned long currentMillis = millis();
    // if WiFi is down, try reconnecting
    if ((WiFi.status() != WL_CONNECTED) && (currentMillis - g_NetWsWifiIntervalPrevious >= g_NetWsWifiIntervalLapse))
    {
        // fncSetupWifiWS();
        Serial.print(millis());
        Serial.println("Reconnecting to WiFi...");
        WiFi.disconnect();
        WiFi.reconnect();
        g_NetWsWifiIntervalPrevious = currentMillis;
    }
}
void fncSetupSoftWifi()
{

    WiFi.mode(WIFI_STA);

    // Connect
    Serial.printf("[WIFI] Connecting to %s ", g_NetWsWifiSsid);
    WiFi.mode(WIFI_STA);

    IPAddress g_NetWsIpDNS2(8, 8, 4, 4); // optional
    WiFi.disconnect();
    if (!WiFi.config(g_NetWsIPAddresslocal_IP, g_NetWsIpGateway, g_NetWsIpSubnet, g_NetWsIpDNS1, g_NetWsIpDNS2))
    {
        Serial.println("STA Failed to configure");
    }

    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(g_NetWsWifiSsid);
    WiFi.begin(g_NetWsWifiSsid, g_NetWsWifiPwd);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    //
    Serial.println();

    Serial.println("Wifi connected as ");
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}
void fncSetupSoftWebSrv()
{
    Serial.println("fncSetupSoftWebSrv");
    /*
      g_WebServer.on("/", handleROOT);
  g_WebServer.on("/.jsjs", handleJS);
  g_WebServer.on("/css.css", handleCSS);
  g_WebServer.on("/svg.svg", handleSVG);

  // g_WebServer.on("/fncDebug", handleDEBUG);
  g_WebServer.on("/cmd", handleCmd); // for one relay /fncAutomatic?id=n
    */

    // Custom entry point (not required by the library, here just as an example)
    g_NetWebServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                      {
                        Serial.println("Index");
                        fncBlinckOn();  
                        request->send(200, "text/html", g_HTML_Web_root);
                        fncBlinckOff(); });

    g_NetWebServer.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request)
                      {
                        Serial.println("Index");
                        fncBlinckOn();  
                        request->send(200, "text/plain", g_HTML_Web_root);
                        fncBlinckOff(); });

    g_NetWebServer.on("/cmd", HTTP_GET, [](AsyncWebServerRequest *request)
                      {
                        fncBlinckOn();  
                        
    String szHtml = "";

    String p_id = "";
    int8_t id;

    String p_value = "";
    //	let url="/cmd?idMotor="+idMotor+"&cmd="+cmd"&value="+value;
    if (request->hasArg("id"))
    {
        p_id = request->arg("id");
        id=p_id.toInt();
    }

    if (request->arg("value"))
    {
        p_value = request->arg("value");
    }

    Serial.print(id);
    Serial.println(p_value);

    szHtml = "Config: Relay ";
    szHtml += String(id+1)+ " ";
    szHtml += String(g_Relays[id].pin())+ " ";
    if (id>-1 && id<g_RelaysCount)
    {
        if (p_value == "0")
        {
            g_Relays[id].m_programation.setupFixed_OFF();
            szHtml += " Allways on";
        }
        if (p_value == "1")
        {
            g_Relays[id].m_programation.setupFixed_ON();
            szHtml += " Always off";
        }
        if (p_value == "2")
        {
            g_Relays[id].m_programation.setupIntevalFixed(1000);
            szHtml += " Flashing fix interval";
        }
        if (p_value == "3")
        {
            g_Relays[id].m_programation.setupIntervalRandon(10000, 30000);
            szHtml += " Flash randon interval";
        }
    }
                        request->send(200, "text/plain", szHtml);
                        fncBlinckOff(); });
    g_NetWebServer.on("/js.js", HTTP_GET, [](AsyncWebServerRequest *request)
                      { 
                      fncBlinckOn();  
                      request->send(200, "text/javascript", g_HTML_Web_JS);  
                      fncBlinckOff(); });
    g_NetWebServer.on("/css.css", HTTP_GET, [](AsyncWebServerRequest *request)
                      {
                       fncBlinckOn();  
                      request->send(200, "text/css", g_HTML_Web_CSS);  
                      fncBlinckOff(); });
    g_NetWebServer.on("/svg.svg", HTTP_GET, [](AsyncWebServerRequest *request)
                      {
                       fncBlinckOn();  
                       request->send(200, "image/svg+xml", g_HTML_Web_SVG);  
                       fncBlinckOff(); });

    g_NetWebServer.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request)
                      {
                       fncBlinckOn();  
                       request->send(200,  "image/x-icon", g_HTML_Web_favicon);  
                       fncBlinckOff(); });

    g_NetWebServer.on("/cmd", HTTP_GET, [](AsyncWebServerRequest *request)
                      {
                       fncBlinckOn();  
                       request->send(200, "text/plain", "not found"); 
                       fncBlinckOff(); });
    // These two callbacks are required for gen1 and gen3 compatibility
    g_NetWebServer.onRequestBody([](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
                                 {
                                     if (g_NetFauxmoAlexa.process(request->client(), request->method() == HTTP_GET, request->url(), String((char *)data)))
                                         return;
                                     // Handle any other body request here...
                                 });
    g_NetWebServer.onNotFound([](AsyncWebServerRequest *request)
                              {
                                  String body = (request->hasParam("body", true)) ? request->getParam("body", true)->value() : String();
                                  if (g_NetFauxmoAlexa.process(request->client(), request->method() == HTTP_GET, request->url(), body))
                                      return;
                                  // Handle not found request here...
                              });

    // Start the server
    g_NetWebServer.begin();
}
void fncSetupSoftFauxmoAlexa()
{

    Serial.println("fncSetupSoftFauxmoAlexa");
    g_NetFauxmoAlexa.createServer(false);
    g_NetFauxmoAlexa.setPort(80); // This is required for gen3 devices
    g_NetFauxmoAlexa.enable(true);
    g_NetFauxmoAlexa.addDevice(g_AlexaDeviceName_Relay1);
    g_NetFauxmoAlexa.addDevice(g_AlexaDeviceName_Relay2);
    g_NetFauxmoAlexa.addDevice(g_AlexaDeviceName_Relay3);
    g_NetFauxmoAlexa.addDevice(g_AlexaDeviceName_Relay4);
    g_NetFauxmoAlexa.addDevice(g_AlexaDeviceName_Relay5);
    g_NetFauxmoAlexa.addDevice(g_AlexaDeviceName_Relay6);
    g_NetFauxmoAlexa.addDevice(g_AlexaDeviceName_Relay7);
    g_NetFauxmoAlexa.addDevice(g_AlexaDeviceName_Relay8);

    g_NetFauxmoAlexa.setState(g_AlexaDeviceName_Relay1, true, 255);
    g_NetFauxmoAlexa.setState(g_AlexaDeviceName_Relay2, true, 255);
    g_NetFauxmoAlexa.setState(g_AlexaDeviceName_Relay3, true, 255);
    g_NetFauxmoAlexa.setState(g_AlexaDeviceName_Relay4, true, 255);
    g_NetFauxmoAlexa.setState(g_AlexaDeviceName_Relay5, true, 255);
    g_NetFauxmoAlexa.setState(g_AlexaDeviceName_Relay6, true, 255);
    g_NetFauxmoAlexa.setState(g_AlexaDeviceName_Relay7, true, 255);
    g_NetFauxmoAlexa.setState(g_AlexaDeviceName_Relay8, true, 255);

    g_NetFauxmoAlexa.onSetState([](unsigned char device_id, const char *device_name, bool state, unsigned char value)
                                {
                                    Serial.println("onSetState");
                                    // Callback when a command from Alexa is received.
                                    // You can use device_id or device_name to choose the element to perform an action onto (relay, LED,...)
                                    // State is a boolean (ON/OFF) and value a number from 0 to 255 (if you say "set kitchen light to 50%" you will receive a 128 here).
                                    // Just remember not to delay too much here, this is a callback, exit as soon as possible.
                                    // If you have to do something more involved here set a flag and process it in your main loop.

                                    // if (0 == device_id) digitalWrite(RELAY1_PIN, state);
                                    // if (1 == device_id) digitalWrite(RELAY2_PIN, state);
                                    // if (2 == device_id) analogWrite(LED1_PIN, value);

                                    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
                                    int8_t relayId = -1;
                                    int8_t relaySwitch = 0;
                                    if (device_id == 0)
                                    {
                                        relayId = 0;
                                    }
                                    if (device_id == 1)
                                    {
                                        relayId = 1;
                                    }
                                    if (device_id == 2)
                                    {
                                        relayId = 2;
                                    }
                                    if (device_id == 3)
                                    {
                                        relayId = 3;
                                    }
                                    if (device_id == 4)
                                    {
                                        relayId = 4;
                                    }
                                    if (device_id == 5)
                                    {
                                        relayId = 5;
                                    }
                                    if (device_id == 6)
                                    {
                                        relayId = 6;
                                    }
                                    if (device_id == 7)
                                    {
                                        relayId = 7;
                                    }

                                    if ((strcmp(device_name, g_AlexaDeviceName_Relay1) == 0))
                                    {
                                        relayId = 0;
                                    }
                                    if ((strcmp(device_name, g_AlexaDeviceName_Relay2) == 0))
                                    {
                                        relayId = 1;
                                    }
                                    if ((strcmp(device_name, g_AlexaDeviceName_Relay3) == 0))
                                    {
                                        relayId = 2;
                                    }
                                    if ((strcmp(device_name, g_AlexaDeviceName_Relay4) == 0))
                                    {
                                        relayId = 3;
                                    }
                                    if ((strcmp(device_name, g_AlexaDeviceName_Relay5) == 0))
                                    {
                                        relayId = 4;
                                    }
                                    if ((strcmp(device_name, g_AlexaDeviceName_Relay6) == 0))
                                    {
                                        relayId = 5;
                                    }
                                    if ((strcmp(device_name, g_AlexaDeviceName_Relay7) == 0))
                                    {
                                        relayId = 6;
                                    }
                                    if ((strcmp(device_name, g_AlexaDeviceName_Relay8) == 0))
                                    {
                                        relayId = 7;
                                    }

                                    if (state)
                                    {
                                        relaySwitch = HIGH;
                                    }
                                    else
                                    {
                                        relaySwitch = LOW;
                                    }
                                    if (relayId > 0)
                                    {
                                        Serial.printf("Alexa switch relay  #%d (%s) state: %s value: %d\n", relayId, device_name, state ? "ON" : "OFF", value);
                                        if (relaySwitch == HIGH)
                                        {
                                            g_Relays[relayId].m_programation.setupFixed_ON();
                                        };
                                        if (relaySwitch == LOW)
                                        {
                                            g_Relays[relayId].m_programation.setupFixed_OFF();
                                        };
                                    }
                                    // For the example we are turning the same LED on and off regardless fo the device triggered or the value
                                    digitalWrite(g_pinIntLedBlue, !state); // we are nor-ing the state because our LED has inverse logic.
                                });
    g_NetWebServer.begin();
    g_NetFauxmoAlexa.enable(true);
}
void fncSetupSoftMultiCoreTask()
{
    Serial.println("fncSetupMultiCoreTask ");
    xTaskCreatePinnedToCore(
        g_TaskCore_0_LoopAlexa,    /* Task function. */
        "g_TaskCore_0_Loop",       /* name of task. */
        10000,                     /* Stack size of task */
        NULL,                      /* parameter of the task */
        1,                         /* priority of the task */
        &g_TaskCore_0_HandleAlexa, /* Task handle to keep track of created task */
        0);                        /* pin task to core 0 */

    /* pin task to core 1 */
    /* pin task to core 1 */

    xTaskCreatePinnedToCore(
        g_TaskCore_1_LoopRelays,     /* Task function. */
        "g_TaskCore_1_HandleRelays", /* name of task. */
        10000,                       /* Stack size of task */
        NULL,                        /* parameter of the task */
        1,                           /* priority of the task */
        &g_TaskCore_1_HandleRelays,  /* Task handle to keep track of created task */
        1);                          /* pin task to core 1 */
                                     /* pin task to core 1 */
}

void fncSetupSoft()

{
    Serial.println("fncSetupSoftWebSrv");
    fncSetupSoftWifi();
    fncSetupSoftWebSrv();
    fncSetupSoftFauxmoAlexa();
    fncSetupSoftMultiCoreTask();
}
#endif