#ifndef MAINSETUPRELAYS_H
#define MAINSETUPRELAYS_H
#include "mainDefines.h"
#include "ClsRelay.h"
#include "ClsProgramation.h"
void fncMainSetupRelays()
{
  for (uint8_t i = 0; i < g_RelaysCount; i++)
  {
    g_Relays[i].attach(i, g_pinRelays[i], "No id");
  }
  g_Relays[0].m_programation.setupFixed_ON();
  g_Relays[1].m_programation.setupFixed_OFF();
  g_Relays[2].m_programation.setupFixed_OFF();
  g_Relays[3].m_programation.setupFixed_OFF();
  g_Relays[4].m_programation.setupFixed_OFF();
  g_Relays[5].m_programation.setupFixed_OFF();
  g_Relays[6].m_programation.setupFixed_OFF();
  g_Relays[7].m_programation.setupFixed_OFF();
}
#endif