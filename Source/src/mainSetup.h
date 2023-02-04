#ifndef MAINSETUP_H
#define MAINSETUP_H
#include "mainDefines.h"
#include "ClsConfig.h"
#include "web_html_root.h"
#include "web_Html_config.h"
#include "web_css.h"
#include "web_js.h"
#include "web_svg.h"
#include "web_favicon.h"
#include "mainBlinCk.h"
void fncSetupHardwareRelays()
{
  for (uint8_t i = 0; i < g_RelaysCount; i++)
  {
    g_Relays[i].attach(i, g_pinRelays[i], "No id");
  }
  g_Relays[0].m_programation.setupFixed_ON();
  g_Relays[1].m_programation.setupFixed_ON();
  g_Relays[2].m_programation.setupFixed_OFF();
  g_Relays[3].m_programation.setupFixed_OFF();
}
void fncSetupHardware()
{

  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Startinng");
  Serial.println();
  pinMode(g_pinIntLedBlue, OUTPUT);
  digitalWrite(g_pinIntLedBlue, HIGH);
  g_Config.setup();
  fncSetupHardwareRelays();
}

void fncSetupSoftWifi()
{
  g_Config.setup();

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
                        request->send(200, "text/html", g_Web_Htlm_Root);
                        fncBlinckOff(); });

  g_NetWebServer.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        Serial.println("Index");
                        fncBlinckOn();  
                        request->send(200, "text/plain", g_Web_Htlm_Root);
                        fncBlinckOff(); });
  g_NetWebServer.on("/favicon.svg", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       fncBlinckOn();  
                       //<link rel="icon" type="image/svg+xml" href="/favicon.svg">
                       request->send(200,  "image/svg+xml", g_HTML_Web_faviconSvg);  
                       fncBlinckOff(); });
  g_NetWebServer.on("/favicon.png", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       fncBlinckOn();  
                       //<link rel="icon" type="image/svg+xml" href="/favicon.svg">
                       request->send(200,  "image/png", g_HTML_Web_faviconPng);  
                       fncBlinckOff(); });
  g_NetWebServer.on("/cmd", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        fncBlinckOn();  

                        g_NetWebServer.on("/cfgsave", HTTP_GET, [](AsyncWebServerRequest *request)
                 {
                   digitalWrite(2, HIGH);
                   Serial.println("/cfgsave-----------------------------");

                   String wifiWsSsid = "";
                   String wifiWsPwd = "";
                   IPAddress wifiWsNetIp;
                   IPAddress wifiWsNetMask;
                   IPAddress wifiWsNetGat;
                   int ntpTimeZone = 2;
                   int ntpTimeZoneDayLight = 0;
                   double gpsLongitude = 0;
                   double gpsLatitude = 0;
                   String szMsg = "";
                   String sz = "";
                   int paramsNr = request->params();
                   Serial.println(paramsNr);

                   for (int i = 0; i < paramsNr; i++)
                   {

                     AsyncWebParameter *p = request->getParam(i);
                     Serial.print("p->name(): ");
                     Serial.print(p->name());
                     Serial.print("p->value(): ");
                     Serial.print(p->value());
                     Serial.print(" Convert to: ");
                     szMsg = szMsg + p->name() + "=" + p->value() + ", ";
                     if (i == 0)
                     {
                       wifiWsSsid = p->value().c_str();
                       Serial.println(wifiWsSsid);
                     }
                     if (i == 1)
                     {
                       wifiWsPwd = p->value().c_str();
                       Serial.println(wifiWsSsid);
                     }
                     if (i == 2)
                     {
                       sz = p->value().c_str();
                       wifiWsNetIp.fromString(sz);
                       Serial.println(wifiWsNetIp.toString());
                     }
                     if (i == 3)
                     {
                       sz = p->value().c_str();
                       wifiWsNetMask.fromString(sz);
                       Serial.println(wifiWsNetMask.toString());
                     }
                     if (i == 4)
                     {
                       sz = p->value().c_str();
                       wifiWsNetGat.fromString(sz);
                       Serial.println(wifiWsNetGat.toString());
                     }
                     if (i == 5)
                     {
                       sz = p->value().c_str();
                       ntpTimeZone = sz.toInt();
                       Serial.println(ntpTimeZone);
                     }
                     if (i == 6)
                     {
                       sz = p->value().c_str();
                       ntpTimeZoneDayLight = sz.toInt();
                       Serial.println(ntpTimeZoneDayLight);
                     }
                     if (i == 7)
                     {
                       sz = p->value().c_str();
                       gpsLongitude = sz.toDouble();

                       Serial.print("  gpsLongitude converted to double ");
                       Serial.println(gpsLongitude, 9);
                     }
                     if (i == 8)
                     {
                       sz = p->value().c_str();
                       gpsLatitude = sz.toDouble();
                       Serial.print(" sz= ");
                       Serial.print(sz);
                      Serial.print("  gpsLatitude converted to double ");
                       Serial.println(gpsLatitude, 9);
                     }
                   }
                   
            

                   bool b = true;
                   if (!g_Config.set_config_WS(wifiWsSsid, wifiWsPwd, wifiWsNetIp, wifiWsNetMask, wifiWsNetGat))
                   {
                     b = false;
                   }
                   else
                   {
                   szMsg += " wifiWsSsid=" + g_Config.getWiFiWsSSid();
                   szMsg += " wifiWsPwd=" +  g_Config.getWiFiWsPwd();
                   szMsg += " wifiWsNetIp=" + g_Config.getWiFiWsIP();
                   szMsg += " wifiWsNetMask=" + g_Config.getWiFiWsMask();
                   szMsg += " wifiWsNetGat=" + g_Config.getWiFiWsGat();

                   }

                   
                   if (!g_Config.set_config_TimeSun(ntpTimeZone, ntpTimeZoneDayLight, gpsLongitude, gpsLatitude))
                   {
                     b = false;
                   }
                   else
                   {
                    
                   szMsg += "ntpTimeZone=" + g_Config.getNtpTimeZone();
                   szMsg += "ntpTimeZoneDayLight=" +g_Config.getNtpTimeZoneDayLight();
                   szMsg += "GpsLongitude=" + g_Config.getGpsLongitude();
                   szMsg += "GpsLatitude=" + g_Config.getGpsLatitude();

                   }
                   if (b)
                   {
                     szMsg += "<br/>Saved";
                   }
                   else
                   {
                     szMsg += "<br/>ERROR: Not saved";
                   }

                   szMsg + "<br/><b>The changes will be applied on next restart: You can click on button abobe this form</b>";
                   request->send(200, "text/html", "message received: " + szMsg);
                   digitalWrite(2, LOW);

                   // ESP.restart();
                 });

  g_NetWebServer.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request)
                 {
                  digitalWrite(2,HIGH);
                  request->send(200, "text/css", "Restarting, Do You need connect to your wifi or AP?") ;
                
                  digitalWrite(2,LOW);
                  ESP.restart(); });
    //------------------------------------------------------------------------
    //------------------------------------------------------------------------
    //------------------------------------------------------------------------
    g_NetWebServer.on("/getconfig", HTTP_GET, [](AsyncWebServerRequest *request)
                 { request->send(200, "text/plain", g_Config.getConfigFull()); });                    
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

    szHtml = "Set: Rele ";
    szHtml += String(id+1)+ " ";
    if (id>-1 && id<g_RelaysCount)
    {
        if (p_value == "0")
        {
            g_Relays[id].m_programation.setupFixed_OFF();
            szHtml += " always OFF";
        }
        if (p_value == "1")
        {
            g_Relays[id].m_programation.setupFixed_ON();
            szHtml += " Always ON";
        }
        if (p_value == "2")
        {
            g_Relays[id].m_programation.setupIntevalFixed(1000);
            szHtml += " Flashing fixed interval";
        }
        if (p_value == "3")
        {
            g_Relays[id].m_programation.setupIntervalRandon(10000, 30000);
            szHtml += " Flashing randon interval";
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
  //------------------------------------------------------------------------
  //------------------------------------------------------------------------
  //------------------------------------------------------------------------
 g_NetWebServer.on("/config", HTTP_GET, [](AsyncWebServerRequest *request)
                   { request->send(200, "text/html", g_Web_Html_Config); });
  g_NetWebServer.on("/getconfig", HTTP_GET, [](AsyncWebServerRequest *request)
                    { request->send(200, "text/plain", g_Config.getConfigFull()); });
  g_NetWebServer.on("/getConfigdefault", HTTP_GET, [](AsyncWebServerRequest *request)
                    { request->send(200, "text/plain", g_Config.getConfigDefaultFull()); });

  g_NetWebServer.on("/cfgsave", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                      digitalWrite(2, HIGH);
                      Serial.println("/cfgsave-----------------------------");

                      String wifiWsSsid = "";
                      String wifiWsPwd = "";
                      IPAddress wifiWsNetIp;
                      IPAddress wifiWsNetMask;
                      IPAddress wifiWsNetGat;
                      int ntpTimeZone = 2;
                      int ntpTimeZoneDayLight = 0;
                      double gpsLongitude = 0;
                      double gpsLatitude = 0;
                      String szMsg = "";
                      String sz = "";
                      int paramsNr = request->params();
                      Serial.println(paramsNr);

                      for (int i = 0; i < paramsNr; i++)
                      {

                        AsyncWebParameter *p = request->getParam(i);
                        Serial.print("p->name(): ");
                        Serial.print(p->name());
                        Serial.print("p->value(): ");
                        Serial.print(p->value());
                        Serial.print(" Convert to: ");
                        szMsg = szMsg + p->name() + "=" + p->value() + ", ";
                        if (i == 0)
                        {
                          wifiWsSsid = p->value().c_str();
                          Serial.println(wifiWsSsid);
                        }
                        if (i == 1)
                        {
                          wifiWsPwd = p->value().c_str();
                          Serial.println(wifiWsSsid);
                        }
                        if (i == 2)
                        {
                          sz = p->value().c_str();
                          wifiWsNetIp.fromString(sz);
                          Serial.println(wifiWsNetIp.toString());
                        }
                        if (i == 3)
                        {
                          sz = p->value().c_str();
                          wifiWsNetMask.fromString(sz);
                          Serial.println(wifiWsNetMask.toString());
                        }
                        if (i == 4)
                        {
                          sz = p->value().c_str();
                          wifiWsNetGat.fromString(sz);
                          Serial.println(wifiWsNetGat.toString());
                        }
                        if (i == 5)
                        {
                          sz = p->value().c_str();
                          ntpTimeZone = sz.toInt();
                          Serial.println(ntpTimeZone);
                        }
                        if (i == 6)
                        {
                          sz = p->value().c_str();
                          ntpTimeZoneDayLight = sz.toInt();
                          Serial.println(ntpTimeZoneDayLight);
                        }
                        if (i == 7)
                        {
                          sz = p->value().c_str();
                          gpsLongitude = sz.toDouble();

                          Serial.print("  gpsLongitude converted to double ");
                          Serial.println(gpsLongitude, 9);
                        }
                        if (i == 8)
                        {
                          sz = p->value().c_str();
                          gpsLatitude = sz.toDouble();
                          Serial.print(" sz= ");
                          Serial.print(sz);
                          Serial.print("  gpsLatitude converted to double ");
                          Serial.println(gpsLatitude, 9);
                        }
                      }

                      bool b = true;
                      if (!g_Config.set_config_WS(wifiWsSsid, wifiWsPwd, wifiWsNetIp, wifiWsNetMask, wifiWsNetGat))
                      {
                        b = false;
                      }
                      else
                      {
                        szMsg += " wifiWsSsid=" + g_Config.getWiFiWsSSid();
                        szMsg += " wifiWsPwd=" + g_Config.getWiFiWsPwd();
                        szMsg += " wifiWsNetIp=" + g_Config.getWiFiWsIP();
                        szMsg += " wifiWsNetMask=" + g_Config.getWiFiWsMask();
                        szMsg += " wifiWsNetGat=" + g_Config.getWiFiWsGat();
                      }

                      if (!g_Config.set_config_TimeSun(ntpTimeZone, ntpTimeZoneDayLight, gpsLongitude, gpsLatitude))
                      {
                        b = false;
                      }
                      else
                      {

                        szMsg += "ntpTimeZone=" + g_Config.getNtpTimeZone();
                        szMsg += "ntpTimeZoneDayLight=" + g_Config.getNtpTimeZoneDayLight();
                        szMsg += "GpsLongitude=" + g_Config.getGpsLongitude();
                        szMsg += "GpsLatitude=" + g_Config.getGpsLatitude();
                      }
                      if (b)
                      {
                        szMsg += "<br/>Saved";
                      }
                      else
                      {
                        szMsg += "<br/>ERROR: Not saved";
                      }

                      szMsg + "<br/><b>The changes will be applied on next restart: You can click on button abobe this form</b>";
                      request->send(200, "text/html", "message received: " + szMsg);
                      digitalWrite(2, LOW);

                      // ESP.restart();
                    });

  g_NetWebServer.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                  digitalWrite(2,HIGH);
                  request->send(200, "text/css", "Restarting, Do You need connect to your wifi or AP?") ;
                
                  digitalWrite(2,LOW);
                  ESP.restart(); });
  g_NetWebServer.begin();
}
void fncSetupSoftFauxmoAlexa()
{

  Serial.println("fncSetupSoftFauxmoAlexa");
  g_NetFauxmoAlexa.createServer(false);
  g_NetFauxmoAlexa.setPort(80); // This is required for gen3 devices
  g_NetFauxmoAlexa.enable(true);
  for (int i = 0; i < g_RelaysCount; i++)
  {
    g_NetFauxmoAlexa.addDevice(g_AlexaDeviceNames[i]);
    g_NetFauxmoAlexa.setState(g_AlexaDeviceNames[i], false, 128);
  }
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
                                digitalWrite(g_pinIntLedBlue, HIGH);
                                Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
                                int8_t relayId = -1;
                                int8_t relaySwitch = 0;

                                for (int i = 0; i < g_RelaysCount; i++)
                                {
                                  if ((strcmp(device_name, g_AlexaDeviceNames[i]) == 0))
                                  {
                                    relayId = i;
                                    i = g_RelaysCount;
                                  }
                                }
                                if (state)
                                {
                                  relaySwitch = HIGH;
                                }
                                else
                                {
                                  relaySwitch = LOW;
                                }
                                if (relayId > -1)
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
                                digitalWrite(g_pinIntLedBlue, LOW); // we are nor-ing the state because our LED has inverse logic.
                              });
  g_NetWebServer.begin();
  g_NetFauxmoAlexa.enable(true);
}
void fncSetupMultiCoreTask()
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

  xTaskCreatePinnedToCore(
      g_TaskCore_1_LoopNetWork,     /* Task function. */
      "g_TaskCore_1_HandleNetWork", /* name of task. */
      10000,                        /* Stack size of task */
      NULL,                         /* parameter of the task */
      1,                            /* priority of the task */
      &g_TaskCore_1_HandleNetWork,  /* Task handle to keep track of created task */
      1);                           /* pin task to core 1 */

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
}
#endif