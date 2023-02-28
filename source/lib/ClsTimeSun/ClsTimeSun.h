#ifndef CLSTIMESUN_H
#define CLSTIMESUN_H
#include <Arduino.h>
#include "time.h"
#include "freertos/timers.h"
#include "sunset.h"
// https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/
// https://stackoverflow.com/questions/69993920/unable-to-get-time-form-the-ntp-server-in-esp8266-arduino
class ClsTimeSun
{
private:
    SunSet m_Sunset;
    bool m_NtpReaded=false;
    unsigned long m_Ntpcounter = 0;
    int64_t m_NtpIntervalSwitch = 15000;
    int64_t m_NtpIntervalPrevious = 0;
    int64_t m_NtpIntervalActual = 0;

    const char *m_NtpServer_default = "pool.ntp.org";
    int m_NtpTimeZone_default = 1;          // hour
    int m_NtpTimeZone_DayLight_default = 1; // add  hour summer
    const int m_NtpTime_HH_2_SS = 3600;

    String m_NtpServer = "pool.ntp.org";
    int m_NtpTimeZone = m_NtpTimeZone_default;
    int m_NtpTimeZoneDayLight = m_NtpTimeZone_DayLight_default;
    long m_NtpLocalGmtOffset_sec = m_NtpTimeZone * m_NtpTime_HH_2_SS;             //(de acuerdo al paralelo)
    int m_NtpLocalDaylightOffset_sec = m_NtpTimeZoneDayLight * m_NtpTime_HH_2_SS; //(De acuedo a reaguste pais)


    //Coordenadas geográficas de Madrid, España, en grados decimales:
    //    Longitud: -3.7025600
    //    Latitud: 40.4165000



    const double m_GpsLatitudeDefault = 40.4165000;   // Madrid spain
    const double m_GpsLongitudeDefault = -3.703228; // Madrid spain
    double m_GpsLatitude = 0;
    double m_GpsLongitude = 0;

    double m_SunriseTimeMM = 0;
    double m_SunsetTimeMM = 0;
    String m_Sunrise_HH_MM="";
    String m_Sunset_HH_MM="";
    int m_MoonFase = 0; // range 0-29,  0 y 20-> hidden,  14=full
    bool m_IsSunrise = false;
    // struct tm *m_Time_Local(const time_t *timer)
    struct tm m_Time_Local = {0};
    int m_TimelLocalYear = 0;
    int m_TimelLocalMonth = 0;
    int m_TimelLocalDayMonth = 0;
    int m_TimelLocalDayWeek = 0;
    int m_TimelLocalDayYear = 0;
    int m_TimelLocalHour = 0;
    int m_TimelLocalMin = 0;
    int m_TimelLocalSec = 0;
    int m_TimelLocalIdst = 0;
    int m_TimeLocal_MinuteOfDay = 0;
    String m_DateLocalYYYYMMDD="";
    String m_TimeLocalHHMM="";

    struct tm m_time_UTC = {0};
    int m_TimelUTCYear = 0;
    int m_TimelUTCMonth = 0;
    int m_TimelUTCDayMonth = 0;
    int m_TimelUTCDayWeek = 0;
    int m_TimelUTCDayYear = 0;
    int m_TimelUTCHour = 0;
    int m_TimelUTCMin = 0;
    int m_TimelUTCSec = 0;
    int m_TimelUTClIdst = 0;

    bool IsNight();
    void fncLoopSunsetSunrise(int iYear, int iMonth, int iDay);
    String fncMinutesToHour(double dMinutes);
    String fncFormatYYYYMMDD(int iYear, int iMonth, int iDay);
    String fncFormatHHMMSS(int iHH, int iMM, int iSS);
    String fncTwoDigit(int i);
public:
    ClsTimeSun(/* args */);
    ~ClsTimeSun();
    void setup();
    void setup(String ntpServer, int ntpTimeZone, int ntpTimeZoneDayLight, long gpsLatitude, long gpsLongitude);
    void loop();
    void fncReadNowNTP();
    void debugSerial();
    bool IsSunrise();
    String Sunrise_HH_MM();
    String Sunset_HH_MM();
    String DateLocalYYYYMMDD();
    String TimeLocalHHMM();


};

#endif