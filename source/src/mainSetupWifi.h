#ifndef MAINSETUPWIFI_H
#define MAINSETUPWIFI_H
#include "mainDefines.h"
#include "ClsWifiConfig.h"
void fncMainSetupWifi()
{
  g_Config.setup(); 
  g_TimeSun.fncReadNowNTP();
  fncRelaysJsonApply(g_Config.relaysJson());
}
#endif
