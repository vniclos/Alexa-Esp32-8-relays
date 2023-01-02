#ifndef MAINBLINCK_H
#define MAINBLINCK_H
#include "mainDefines.h"
void fncBlinckOn()
{digitalWrite(g_pinIntLedBlue, HIGH);
}
void fncBlinckOff()
{
    digitalWrite(g_pinIntLedBlue, LOW);
}
void fncBlinckSwithc()

{
    if (digitalRead(g_pinIntLedBlue) == HIGH)
    {
        digitalWrite(g_pinIntLedBlue, LOW);
    }
    else
    {
        digitalWrite(g_pinIntLedBlue, HIGH);
    }
}
#endif