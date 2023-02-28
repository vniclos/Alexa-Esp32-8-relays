#include "ClsRelay.h"
#include "Arduino.h"
ClsRelay::ClsRelay() { clear(); }
// enum eProgramationTime  {    ON_DAY,    ON_NIGHT,    ON_ALWAIS,    OFF_ALWAYS  };�
//  enum eProgramationMode  {    FIXED_ON,    FLASH_FIXED,    FLASH_RANDON  };
void ClsRelay::setup(int idRelay, int pin, String name, eProgramationMode programtionMode, eProgramationTime programtionTime)
{
    clear();
    pinMode(pin,OUTPUT);
    digitalWrite(pin,RELAY_OFF);
    m_Name = name;
    m_idRelay = idRelay;
    m_pin = pin;

    m_ProgramationMode = programtionMode;
    m_ProgramationTime = programtionTime;
    getJsonProgramation();
}
void ClsRelay::clear()
{
    m_ProgramationMode = m_ProgramationMode_default; // 0 allways off, 1 =Always On, 2 flashing fixed interval , 3 flashin randon interval
    m_ProgramationTime = m_ProgramationTime_default;
    m_IntervalRandonMin = m_IntervalRandonMin_default;
    m_IntervalRandonMax = m_IntervalRandonMax_default;
    m_Interval_InUse = m_intervalFixed;
    m_RelayIntervalPrevious = 0;

    m_RelayStatus = false;
}

void ClsRelay::setIntevalFixed(uint32_t interval)
{

    m_ProgramationMode = FLASH_FIXED; // 0 allways off, 1 =Always On, 2 flashing fixed interval , 3 flashin randon interval
    m_Interval_InUse = interval;
    digitalWrite(m_pin, LOW);
}
void ClsRelay::setIntervalRandon(uint32_t IntervalRandonMin, uint32_t IntervalRandonMax)
{
    m_ProgramationMode = FLASH_RANDON;
    digitalWrite(m_pin, LOW);

    m_IntervalRandonMin = IntervalRandonMin;
    m_IntervalRandonMax = IntervalRandonMax;
    m_Interval_InUse = random(m_IntervalRandonMin, m_IntervalRandonMax);
}
bool ClsRelay::isInInterval()
{

    bool result = false;
    uint32_t uiMillis = 0;
    uiMillis = millis();

    if (m_RelayIntervalPrevious > uiMillis)
    {
        m_RelayIntervalPrevious = 0;
    }
    if ((uiMillis - m_RelayIntervalPrevious) > m_Interval_InUse)
    {
        result = true;
       
    }
    return result;
}
// enum eProgramationTime  {ON_DAY, ON_NIGHT, ON_ALWAIS, OFF_ALWAYS};
// enum eProgramationMode{FIXED_ON,  FLASH_FIXED, FLASH_RANDON};

int ClsRelay::loop(bool isDayLight)
{

    m_isDayLight = isDayLight;

    switch (m_ProgramationTime)
    {
    case OFF_ALWAYS:
        m_RelayStatus = RELAY_OFF;

        break;
    case ON_ALWAIS:
        m_RelayStatus = CalculateStatusMode();
        break;
    case ON_DAY:
        if (m_isDayLight)
        {

            m_RelayStatus = CalculateStatusMode();
        }
        else
        {
            m_RelayStatus = RELAY_OFF;
        }
        break;
    case ON_NIGHT:
       
        if (m_isDayLight)
        {
            m_RelayStatus = RELAY_OFF;
        }
        else
        {
            m_RelayStatus = CalculateStatusMode();
        }
        break;
    default:
        break;
    }

    digitalWrite(m_pin, m_RelayStatus);
    return m_RelayStatus;

    ;
}
int ClsRelay::CalculateStatusMode()
{
    // Serial.print("CalculateStatusMode m_ProgramationMode = ");
    // Serial.println(m_ProgramationMode);
    unsigned long now = millis();
    if (now < m_RelayIntervalPrevious)
    {
        m_RelayIntervalPrevious = 0;
    }
    int status = getRelayStatus();

    switch (m_ProgramationMode)
    {

    case FIXED_ON: // allways on
       
        m_RelayStatus = RELAY_ON;
        break;

    case FLASH_FIXED: // flashing inteval fixed
       
        m_Interval_InUse = m_intervalFixed;
        if (isInInterval())
        {
            if (status == RELAY_OFF)
            {
                m_RelayStatus = RELAY_ON;
            }
            else
            {
                m_RelayStatus = RELAY_OFF;
            }
            m_RelayIntervalPrevious = now;
        }
        break;

    case FLASH_RANDON: // flashing interval randon
       // Serial.println("case FLASH_RANDON:");
      
        m_Interval_InUse = random(m_IntervalRandonMin, m_IntervalRandonMax);
        if (isInInterval())
        {
            if (status == RELAY_OFF)
            {
                m_RelayStatus = RELAY_ON;
            }
            else
            {
                m_RelayStatus = RELAY_OFF;
            }
            m_RelayIntervalPrevious = now;
        }
        break;

    default:

        break;
    }
    return m_RelayStatus;
}

void ClsRelay::setPinRelay(int8_t pin) { m_pin = pin; };

void ClsRelay::setRelayIntervalPrevious(uint32_t relayIntervalPrevious) { m_RelayIntervalPrevious = relayIntervalPrevious; }

String ClsRelay::getProgramationTimeToString(int val)
{
    String result(eProgramationTimeString[val]);
    return result;
}
String ClsRelay::getProgramationModeToString(int val)
{
    String result(eProgramationModeString[val]);
    return result;
}

String ClsRelay::getProgramationMode() { return String(m_ProgramationMode); }
String ClsRelay::getProgramationTime() { return String(m_ProgramationTime); }
uint32_t ClsRelay::getRelayIntervalPrevious() { return m_RelayIntervalPrevious; }
bool ClsRelay::getIsInInterval() { return isInInterval(); }
/// @brief when pin is HIGHT THE RELAY IS OFF
/// @return 1 RELAY ON , RETURN 0 RELAY OFF
int ClsRelay::getRelayStatus()
{
    // Relay on off are reversed
     //const uint8_t RELAY_ON = LOW;
     // const uint8_t RELAY_OFF = HIGH;
    if (digitalRead(m_pin) == HIGH)
    {
        return RELAY_OFF;
    }
    else
    {
        return RELAY_ON;
    }
}

uint32_t ClsRelay::getInterval_InUse() { return m_Interval_InUse; }
uint32_t ClsRelay::getIntervalFixed() { return m_intervalFixed; }
uint32_t ClsRelay::getIntervalRandoMin() { return m_IntervalRandonMin; }
uint32_t ClsRelay::getIntervalRandonMax() { return m_IntervalRandonMax; }

void ClsRelay::setProgramationTime_OnDay()
{
    m_ProgramationTime = ON_DAY;
    loop(m_isDayLight);
} // on On diay
void ClsRelay::setProgramationTime_OnNight()
{
    m_ProgramationTime = ON_NIGHT;
    loop(m_isDayLight);
} // On on night
void ClsRelay::setProgramationTime_OnAlways()
{
    m_ProgramationTime = ON_ALWAIS;
    loop(m_isDayLight);
} // on always
void ClsRelay::setProgramationTime_OffAlways()
{
    m_ProgramationTime = OFF_ALWAYS;
    loop(m_isDayLight);
} // off always
void ClsRelay::setProgramationMode_Fixed_ON()
{

    m_ProgramationMode = FIXED_ON;
    loop(m_isDayLight);
}
void ClsRelay::setProgramationMode_FlashingFixed()
{
    m_ProgramationMode = FLASH_FIXED;
    loop(m_isDayLight);
}
void ClsRelay::setProgramationMode_FlashingRandon()
{
    m_ProgramationMode = FLASH_RANDON;
    loop(m_isDayLight);
}
/// @brief
/// @return  String {"idRelay":"0","Name":"belen 0" ,"Status": "OFF","Mode":"1","Time":"D"}
String ClsRelay::getJsonProgramation()
{
    //{"idRelay":"0","Name":"belen 0" ,"Status": "OFF","Mode":"1","Time":"D"}
    String jsonResult = "{";
    jsonResult = jsonResult + fncJsonAdd("idRelay", String(m_idRelay)) + ", ";
    jsonResult = jsonResult + fncJsonAdd("Name", m_Name) + ", ";
    jsonResult = jsonResult + fncJsonAdd("Status", String(getRelayStatus())) + ", ";
    jsonResult = jsonResult + fncJsonAdd("Mode", String(m_ProgramationMode)) + ", ";
    jsonResult = jsonResult + fncJsonAdd("Time", String(m_ProgramationTime));
    jsonResult = jsonResult + "}";
    Serial.print("getJsonProgramation= ");
    Serial.println(jsonResult);
    return jsonResult;
}
void ClsRelay::setJsonProgramation(String name, eProgramationMode programtionMode, eProgramationTime programtionTime)
{
    m_Name = name;
    m_ProgramationMode = programtionMode;
    m_ProgramationTime = programtionTime;
}
String ClsRelay::fncJsonAdd(String name, String value)
{
    String result = "\"" + name + "\":";
    result = result + "\"" + value + "\"";
    return result;
}
