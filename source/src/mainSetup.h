#ifndef MAINSETUP_H
#define MAINSETUP_H
#include "mainDefines.h"
#include "mainSetupAlexa"
#include "mainSetupRelays.h"
#include "mainSetupWebSrv.h"
#include "mainSetupWifi.h"
#include "mainSetupTimeSun.h"
#include "mainSetupTasks.h"
#include "ClsWifiConfig.h"
#include "web_html_root.h"
#include "web_Html_config.h"
#include "web_css.h"
#include "web_js.h"
#include "web_svg.h"
#include "web_favicon.h"
void fncMainSetup()
{

  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Startinng");
  Serial.println();
  pinMode(g_pinIntLedBlue, OUTPUT);
  digitalWrite(g_pinIntLedBlue, HIGH);
  g_Config.setup();

  fncMainSetupWifi();
  fncMainSetupTimeSun();
    fncMainSetupRelays();
  fncMainSetupWebSrv();
  fncMainSetupAlexa();
}
#endif
