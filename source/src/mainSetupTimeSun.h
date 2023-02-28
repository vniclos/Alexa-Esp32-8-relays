#ifndef MAINSETUPTIMESUN
#define MAINSETUPTIMESUN
#include "mainDefines.h"
#include "WiFi.h"

void fncMainSetupTimeSun()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        g_TimeSun.fncReadNowNTP();
    }
}
#endif