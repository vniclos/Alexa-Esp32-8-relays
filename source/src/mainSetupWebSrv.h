#ifndef MAINSETUPWEBSRV_H
#define MAINSETUPWEBSRV_H

#include <Arduino.h>
#include "mainDefines.h"
#include "ClsWifiConfig.h"
#include "ClsTimeSun.h"
#include "web_html_root.h"
#include "web_Html_config.h"
#include "web_css.h"
#include "web_js.h"
#include "web_svg.h"
#include "web_favicon.h"
void fncMainSetupWebSrv()
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
                        digitalWrite(g_pinIntLedBlue,HIGH);
                                       request->send(200, "text/html", g_Web_Htlm_Root);
                        digitalWrite(g_pinIntLedBlue,LOW); });

  g_NetWebServer.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        Serial.println("Index");
                        digitalWrite(g_pinIntLedBlue,HIGH);  
                        request->send(200, "text/plain", g_Web_Htlm_Root);
                        digitalWrite(g_pinIntLedBlue,LOW); });
  g_NetWebServer.on("/favicon.svg", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinIntLedBlue,HIGH);  
                       //<link rel="icon" type="image/svg+xml" href="/favicon.svg">
                       request->send(200,  "image/svg+xml", g_HTML_Web_faviconSvg);  
                       digitalWrite(g_pinIntLedBlue,LOW); });
  g_NetWebServer.on("/favicon.png", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinIntLedBlue,HIGH);  
                       //<link rel="icon" type="image/svg+xml" href="/favicon.svg">
                       request->send(200,  "image/png", g_HTML_Web_faviconPng);  
                       digitalWrite(g_pinIntLedBlue,LOW); });
  g_NetWebServer.on("/cmd", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                        digitalWrite(g_pinIntLedBlue,HIGH);  

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
                        digitalWrite(g_pinIntLedBlue,LOW); });
  g_NetWebServer.on("/js.js", HTTP_GET, [](AsyncWebServerRequest *request)
                    { 
                      digitalWrite(g_pinIntLedBlue,HIGH);  
                      request->send(200, "text/javascript", g_HTML_Web_JS);  
                      digitalWrite(g_pinIntLedBlue,LOW); });
  g_NetWebServer.on("/css.css", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinIntLedBlue,HIGH);  
                      request->send(200, "text/css", g_HTML_Web_CSS);  
                      digitalWrite(g_pinIntLedBlue,LOW); });
  g_NetWebServer.on("/svg.svg", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinIntLedBlue,HIGH);  
                       request->send(200, "image/svg+xml", g_HTML_Web_SVG);  
                       digitalWrite(g_pinIntLedBlue,LOW); });
  g_NetWebServer.on("/cmd", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
                       digitalWrite(g_pinIntLedBlue,HIGH);  
                       request->send(200, "text/plain", "not found"); 
                       digitalWrite(g_pinIntLedBlue,LOW); });
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

  //
  g_NetWebServer.on("/getrootstatus", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
    digitalWrite(2, HIGH);
    String result= g_TimeSun.DateLocalYYYYMMDD()+" "+g_TimeSun.TimeLocalHHMM()+" Sunrise at "+ g_TimeSun.Sunrise_HH_MM()+ +" Sunest at "+ g_TimeSun.Sunset_HH_MM() ;
    if (g_TimeSun.IsSunrise()) {result+= " is Day"; }else{ result+="is Night";}
    Serial.println("getRootStatus");
    Serial.println(result);
    request->send(200, "text/plain",result.c_str());
    digitalWrite(2, LOW); });

  g_NetWebServer.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
    digitalWrite(2, HIGH);
    request->send(200, "text/css", "Restarting, Do You need connect to your wifi or AP?");

    digitalWrite(2, LOW);
    ESP.restart(); });
  g_NetWebServer.begin();
}
#endif