#ifndef MAINRELAYSJSON_H
#define MAINRELAYSJSON_H
#include <Arduino.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "ClsRelay.h"
#include "mainDefines.h"

bool   fncRelaysJsonApply(String sJson)
{
    Serial.println("_____________ APPLY JSON STAR____________________________");
//    Serial.println(sJson);
  //  Serial.println("");

  bool bRepy = true;

  auto error = deserializeJson(g_docJsonRelays, sJson);
  if (error)
  {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
    return false;
  }
  int iIdRelay = -1;
  int iMode = -1;
  int iTime = -1;
  String sKey = "";
  String sValue = "";
  int fieldCount = -1;
  for (int i = 0; i < g_docJsonRelays.size(); i++)
  {
    JsonObject aJson = g_docJsonRelays[i].as<JsonObject>();
    fieldCount = 0;
    iIdRelay = -1;
    iMode = -1;
    iTime = -1;

  
    for (JsonPair kv : aJson)
    {
      fieldCount++;

      sKey = kv.key().c_str();
      sValue = kv.value().as<String>();
     // Serial.println("kEY: " + sKey + " Value: " + sValue );

      if (fieldCount == 1)
      {
        iIdRelay = sValue.toInt();
      }
      if (fieldCount == 3)
      {
        iMode = sValue.toInt();
      }
      if (fieldCount == 4)
      {
        iTime = sValue.toInt();
      }
    }
    Serial.print("idRelay=" + String(iIdRelay) + " Mode= " + String(iMode) + " time=" + String(iTime)+" -->  ");
    if (iIdRelay > -1)
    {
      Serial.print(iIdRelay);
      // enum eProgramationMode  {    FIXED_ON,    FLASH_FIXED,    FLASH_RANDON  };
      switch (iMode)
      {
      case 0:
        g_Relays[iIdRelay].setProgramationMode_Fixed_ON();
        Serial.print(" .setProgramationMode_Fixed_ON");
        break;
      case 1:
        g_Relays[iIdRelay].setProgramationMode_FlashingFixed();
        Serial.print(" .setProgramationMode_FlashingFixed");
        break;
      case 2:
        g_Relays[iIdRelay].setProgramationMode_FlashingRandon();
        Serial.print(" .setProgramationMode_FlashingRandon");
        break;
      default:
        break;
      }
      //   {    ON_DAY,    ON_NIGHT,    ON_ALWAIS,    OFF_ALWAYS  };
      switch (iTime)
      {
      case 0:
        g_Relays[iIdRelay].setProgramationTime_OnDay();
        Serial.println(" .setProgramationTime_OnDay");
        break;
      case 1:
        g_Relays[iIdRelay].setProgramationTime_OnNight();
        Serial.println(" .setProgramationTime_OnNight");
        break;
      case 2:
        g_Relays[iIdRelay].setProgramationTime_OnAlways();
        Serial.println(".setProgramationTime_OnAlways");
        break;
      case 3:
        g_Relays[iIdRelay].setProgramationTime_OffAlways();
        Serial.println(" .setProgramationTime_OffAlways");
        break;
      default:
        break;
      }
      g_Relays[iIdRelay].loop(g_TimeSun.IsSunrise());
   Serial.println("_____________ APPLY JSON  END __________________________");
    }
  }
  return bRepy;
}
String fncRelaysJsonGetString()
{
  String resultJson = "";
  String nightDay = "";
  if (g_TimeSun.IsSunrise())
  {
    nightDay += "Day";
  }
  else
  {
    nightDay += "Night";
  }
  resultJson = "[";
  resultJson += "{\"DateTime\":\"" + g_TimeSun.DateLocalYYYYMMDD() + g_TimeSun.TimeLocalHHMM() + "\", \"Sunrise\":\"" + g_TimeSun.Sunrise_HH_MM() + "\", \"Sunset\":\"" + g_TimeSun.Sunset_HH_MM() + "\", \"IsDay\":\"" + nightDay + "\"}";
  //{"idRelay":"0","scnName":"belen 0" ,"scnStatus": "OF","scnMode":"2","scnTime":"N"},

  for (int i = 0; i < g_RelaysCount; i++)
  {
    resultJson = resultJson + ", " + g_Relays[i].getJsonProgramation();
  }
  resultJson += " ]";
  return resultJson;
}
#endif