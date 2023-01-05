#include "ClsRelay.h"
#include "Arduino.h"

// The ChannelUsed array elements are 0 if never used, 1 if in use, and -1 if used and disposed
// (i.e., available for reuse)

ClsRelay::ClsRelay()
{
}

void ClsRelay::attach(uint8_t id, uint8_t pin)
{
    attach(id, pin, "No Id.");
}

void ClsRelay::attach(uint8_t id, uint8_t pin, String name)
{
    m_id = id;
    m_pin = pin;

    m_Name = name;
    pinMode(m_pin, OUTPUT);
    digitalWrite(m_pin, RELAY_OFF);
    m_programation.setPinRelay(m_pin);
    m_programation.setupFixed_OFF();
}
uint8_t ClsRelay::PrgStatusGet()
{
    return digitalRead(m_pin);
}
void ClsRelay::loop()
{
   
    m_programation.CalculateNewStatus();
}
