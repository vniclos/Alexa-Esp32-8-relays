#include "ClsProgramation.h"
#include "Arduino.h"
ClsProgramation::ClsProgramation()
{
}
void ClsProgramation::clear()
{
    m_ProgramationMode = 0; // 0 allways off, 1 =Always On, 2 flashing fixed interval , 3 flashin randon interval
    m_RelayIntervalPrevious = 0;
    m_IntervalSteep = 0;
    m_IntervalSteepRandonMin = 0;
    m_IntervalSteepRandonMax = 0;
    m_RelayStatus = false;
}
void ClsProgramation::setupFixed_ON()
{
    clear();
    m_ProgramationMode = 1; // 0 allways off, 1 =Always On, 2 flashing fixed interval , 3 flashin randon interval
    digitalWrite(m_pin, RELAY_ON);
    m_RelayStatus = true;
}
void ClsProgramation::setupFixed_OFF()
{
    clear();
    m_ProgramationMode = 0;
    digitalWrite(m_pin, RELAY_OFF);
    m_RelayStatus = false;
}

void ClsProgramation::setupIntevalFixed(uint32_t interval)
{
    clear();
    m_ProgramationMode = 2; // 0 allways off, 1 =Always On, 2 flashing fixed interval , 3 flashin randon interval
    m_IntervalSteep = interval;
    digitalWrite(m_pin, RELAY_OFF);
    m_RelayStatus = false;
}
void ClsProgramation::setupIntervalRandon(uint32_t IntervalRandonMin, uint32_t IntervalRandonMax)
{
    m_ProgramationMode = 3;
    digitalWrite(m_pin, RELAY_OFF);
    m_RelayStatus = false;
    m_IntervalSteepRandonMin = IntervalRandonMin;
    m_IntervalSteepRandonMax = IntervalRandonMax;
    m_IntervalSteep = random(m_IntervalSteepRandonMin, m_IntervalSteepRandonMax);
}
bool ClsProgramation::isInInterval()
{

    bool result = false;
    uint32_t uiMillis = 0;
    uiMillis = millis();
   
    if (m_RelayIntervalPrevious > uiMillis)
    {
        m_RelayIntervalPrevious = 0;
    }
    if ((uiMillis - m_RelayIntervalPrevious) > m_IntervalSteep)
    {
        result = true;
        m_RelayIntervalPrevious = uiMillis;
    }
    return result;
}
int ClsProgramation::CalculateNewStatus()
{
 
    bool result = 0;
    int status = digitalRead(m_pin);
    switch (m_ProgramationMode)
    {
    case 0: // allways off

        digitalWrite(m_pin, RELAY_OFF);
        m_RelayStatus = RELAY_OFF;
        result = RELAY_OFF;
        break;
    case 1: // allways on
        digitalWrite(m_pin, RELAY_ON);
        m_RelayStatus = RELAY_ON;
        result = RELAY_ON;
 
        break;

    case 2: // flashing inteval fixed
        Serial.println( "Case 2 flashing fixed");
        if (isInInterval())
        {
            if (status == RELAY_OFF)
            {
                result = RELAY_ON;
                digitalWrite(m_pin, RELAY_ON);
                m_RelayStatus = RELAY_ON;
            }
            else
            {
                result = RELAY_OFF;
                digitalWrite(m_pin, RELAY_OFF);
                m_RelayStatus = RELAY_OFF;
            }
        }
        break;

    case 3: // flashing interval randon
Serial.println( "Case 3 flashing randon" );
Serial.print(m_pin);
        m_IntervalSteep = random(m_IntervalSteepRandonMin, m_IntervalSteepRandonMax);

        if (isInInterval())
        {
            if (status == RELAY_OFF)
            {
                result = RELAY_ON;
                digitalWrite(m_pin, RELAY_ON);
                m_RelayStatus = RELAY_ON;
            }
            else
            {
                result = RELAY_OFF;
                digitalWrite(m_pin, RELAY_OFF);
                m_RelayStatus = RELAY_OFF;
            }
        }
        break;

    default:
        result = false;
        break;
    }

    return RELAY_OFF;
}
void ClsProgramation::setPinRelay(int8_t pin) { m_pin = pin; };
void ClsProgramation::setStatusRelay(bool RelayStatus) { m_RelayStatus = RelayStatus; }
void ClsProgramation::setRelayIntervalPrevious(uint32_t relayIntervalPrevious) { m_RelayIntervalPrevious = relayIntervalPrevious; }
uint8_t ClsProgramation::getProgramationMode() { return m_ProgramationMode; }
uint32_t ClsProgramation::getRelayIntervalPrevious() { return m_RelayIntervalPrevious; }
bool ClsProgramation::getIsInInterval() { return isInInterval(); }
bool ClsProgramation::getRelayStatus() { return m_RelayStatus; }
uint32_t ClsProgramation::getIntervalSteep() { return m_IntervalSteep; }

