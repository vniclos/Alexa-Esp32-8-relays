#include "ClsTimeSun.h"
#include <Arduino.h>
ClsTimeSun::ClsTimeSun(/* args */)
{
}

ClsTimeSun::~ClsTimeSun()
{
}
void ClsTimeSun::setup()
{

    setup(m_NtpServer_default, m_NtpTimeZone_default, m_NtpTimeZone_DayLight_default, m_GpsLatitudeDefault, m_GpsLongitudeDefault);
}

void ClsTimeSun::setup(String ntpServer, int ntpTimeZone, int ntpTimeZoneDayLight, long gpsLatitude, long gpsLongitude)
{
    m_NtpServer = ntpServer;
    m_NtpTimeZone = ntpTimeZone;
    m_NtpTimeZoneDayLight = ntpTimeZoneDayLight;
    m_GpsLatitude = gpsLatitude;
    m_GpsLongitude = gpsLongitude;

    m_NtpLocalGmtOffset_sec = m_NtpTimeZone * m_NtpTime_HH_2_SS;              //(de acuerdo al paralelo)
    m_NtpLocalDaylightOffset_sec = m_NtpTimeZoneDayLight * m_NtpTime_HH_2_SS; //(De acuedo a reaguste pais)

    m_Sunset.setPosition(m_GpsLatitude, m_GpsLongitude, m_NtpTimeZone);
    m_Sunset.setTZOffset(m_NtpTimeZone);
}
void ClsTimeSun::loop()
{
    // unsigned long m_Ntpcounter=0;
    // int64_t m_NtpIntervalSwitch=60000;
    // int64_t m_NtpIntervalPrevious=0;
    m_NtpIntervalActual = millis();
    if (m_NtpIntervalPrevious > m_NtpIntervalActual)
    {
        m_NtpIntervalPrevious = 0;
    }
    if (m_NtpIntervalActual - m_NtpIntervalPrevious < m_NtpIntervalSwitch)
    {
        return;
    }
    configTime(m_NtpLocalGmtOffset_sec, m_NtpLocalDaylightOffset_sec, m_NtpServer.c_str());
    if (!getLocalTime(&m_Time_Local))
    {
        Serial.println("Failed to obtain local time ");
        return;
    }
    configTime(0, 0, m_NtpServer.c_str());
    if (!getLocalTime(&m_time_UTC))
    {
        Serial.println("Failed to obtain UTC time ");
        return;
    }

    m_NtpIntervalPrevious = m_NtpIntervalActual;
    m_Ntpcounter++;
    m_TimelLocalYear = 1900 + m_Time_Local.tm_year;
    m_TimelLocalMonth = m_Time_Local.tm_mon;
    m_TimelLocalDayMonth = m_Time_Local.tm_mday;
    m_TimelLocalDayWeek = m_Time_Local.tm_wday;
    m_TimelLocalDayYear = m_Time_Local.tm_yday;
    m_TimelLocalHour = m_Time_Local.tm_hour;
    m_TimelLocalMin = m_Time_Local.tm_min;
    m_TimelLocalSec = m_Time_Local.tm_sec;
    m_TimeLocal_MinuteOfDay = m_Time_Local.tm_hour * 60 + m_Time_Local.tm_min;
     fncLoopSunset(m_TimelLocalYear,m_TimelLocalDayMonth,m_TimeLocal_MinuteOfDay);

    m_TimelUTCYear = 1900 + m_time_UTC.tm_year;
    m_TimelUTCMonth = m_time_UTC.tm_mon;
    m_TimelUTCDayMonth = m_time_UTC.tm_mday;
    m_TimelUTCDayWeek = m_time_UTC.tm_wday;
    m_TimelUTCDayYear = m_time_UTC.tm_yday;
    m_TimelUTCHour = m_time_UTC.tm_hour;
    m_TimelUTCMin = m_time_UTC.tm_min;
    m_TimelUTCSec = m_time_UTC.tm_sec;
    //fncLoopSunset(m_TimelUTCDayYear, m_TimelUTCDayMonth, m_TimelUTCMin);
    debugSerial();
}
void ClsTimeSun::debugSerial()
{
    // struct tm timeinfo;
    Serial.println("========================================================");
    Serial.print("m_Ntpcounter=");
    // Serial.print(m_Ntpcounter);
    // Serial.print(" m_NtpIntervalPrevious=");
    // Serial.print(m_NtpIntervalPrevious);
    // Serial.print(" m_NtpIntervalSwitch=");
    // Serial.println(m_NtpIntervalSwitch);
    Serial.print(" m_NtpLocalGmtOffset_sec=");
    Serial.print(m_NtpLocalGmtOffset_sec);
    Serial.print(" m_NtpLocalDaylightOffset_sec=");
    Serial.println(m_NtpLocalDaylightOffset_sec);

    Serial.println(&m_Time_Local, "Local=%A, %B %d %Y %H:%M:%S");
    Serial.println(&m_time_UTC, "Utc=%A, %B %d %Y %H:%M:%S");
    Serial.print("m_SunriseTimeMM= ");
    Serial.println(m_SunriseTimeMM);
    Serial.print("m_SunsetTimeMM=");
    Serial.println(m_SunsetTimeMM);
    Serial.print("IsSunrise()=");
    Serial.println(m_IsSunrise);
    Serial.println("m_Sunrise_HH_MM=" + m_Sunrise_HH_MM);
    Serial.println("m_Sunset_HH_MM=" + m_Sunset_HH_MM);

    /*
        Serial.print("Day of week: ");
        Serial.println(&m_Time_Local, "%A");
        Serial.print("Month: ");
        Serial.println(&m_Time_Local, "%B");
        Serial.print("Day of Month: ");
        Serial.println(&m_Time_Local, "%d");
        Serial.print("Year: ");
        Serial.println(&m_Time_Local, "%Y");
        Serial.print("Hour: ");
        Serial.println(&m_Time_Local, "%H");
        Serial.print("Hour (12 hour format): ");
        Serial.println(&m_Time_Local, "%I");
        Serial.print("Minute: ");
        Serial.println(&m_Time_Local, "%M");
        Serial.print("Second: ");
        Serial.println(&m_Time_Local, "%S");

        Serial.println("Time variables");
        char timeHour[3];
        strftime(timeHour, 3, "%H", &m_Time_Local);
        Serial.println(timeHour);
        char timeWeekDay[10];
        strftime(timeWeekDay, 10, "%A", &m_Time_Local);
        Serial.println(timeWeekDay);
        */
}

bool ClsTimeSun::IsNight()
{
    bool result = false;
    return result;
}

void ClsTimeSun::fncLoopSunset(int iYear, int iMonth, int iDay)
{
    // get actual parameters for calculate.
    m_Sunset.setPosition(m_GpsLatitude, m_GpsLongitude, m_NtpTimeZone);
    m_Sunset.setTZOffset(m_NtpTimeZone);
    m_Sunset.setCurrentDate(iYear, iMonth, iDay);
    // If you have daylight savings time, make sure you set the timezone appropriately as well
    m_MoonFase = m_Sunset.moonPhase(std::time(nullptr));
    m_SunriseTimeMM = m_Sunset.calcSunrise(); // sunrise in minutes of day
    Serial.print("...................");
    Serial.println(m_SunriseTimeMM);
    m_Sunrise_HH_MM = fncMinutesToHour(m_SunriseTimeMM);

    m_SunsetTimeMM = m_Sunset.calcSunset(); // sunrset in minutes of day
    Serial.print("...................");
    Serial.println(m_SunsetTimeMM);

    m_Sunset_HH_MM = fncMinutesToHour(m_SunsetTimeMM);

    m_TimeLocal_MinuteOfDay = m_Time_Local.tm_hour * 60 + m_Time_Local.tm_min;
    if (m_TimeLocal_MinuteOfDay >= m_SunriseTimeMM && m_TimeLocal_MinuteOfDay <= m_SunsetTimeMM)
    {
        m_IsSunrise = true;
    }
    else
    {
        m_IsSunrise = false;
    }
}
String ClsTimeSun::Sunrise_HH_MM() { return m_Sunrise_HH_MM; }
String ClsTimeSun::Sunset_HH_MM() { return m_Sunset_HH_MM; }

String ClsTimeSun::fncMinutesToHour(double dMinutes)
{
    int iMinutes = (int)dMinutes;
    String result = "";
    int iHH = 0;
    int iMM = int(dMinutes);
    iHH =int( dMinutes / 60)    ;
    iMM = iMM % 60;
    if (iHH < 10)
    {
        result = "0";
    }
    result = result + String(iHH) + ":";
    if (iMM < 10)
    {
        result = result + "0";
    }
    result = result + String(iMM) ;
    return result;
}
bool ClsTimeSun::IsSunrise() { return m_IsSunrise; }