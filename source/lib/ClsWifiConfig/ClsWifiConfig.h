#ifndef ClsWifiConfig_H
#define ClsWifiConfig_H
#include <Arduino.h>
#include <WiFi.h>
#include "SPIFFS.h"

/// @brief
class ClsWifiConfig
{
public:
    ClsWifiConfig();
    void set_config_AP(String wifi_AP_Ssid, String wifi_AP_Pwd);
    bool set_config_WS(String wifi_WS_Ssid, String wifi_WS_Pwd);
    bool set_config_WS(String wifi_WS_Ssid, String wifi_WS_Pwd, IPAddress wifi_WS_IP, IPAddress Wifi_AP_Mask, IPAddress wifi_AP_Gateway);
    bool set_config_TimeSun(int ntpTimeZone, int ntpTimeZoneDayLight, double GpsLongitude, double gpsLatitude);
    void set_config_default();
    void set_config_PinReset(int pinReset); // default =-1,  if pinRest < 0 then wifi  pin reset not used, else pin reset cheked on start
    void configSerialPrint();
    String macAddress = WiFi.macAddress();
    String chipId = String((uint32_t)ESP.getEfuseMac(), HEX);
    String getWiFiListOfNetworkHtml();
    String getWiFiWsSSid();
    String getWiFiWsPwd();
    String getWiFiWsIP();
    String getWiFiWsMask();
    String getWiFiWsGat();
    String getWiFiWsDNS1();
    String getWiFiWsDNS2();
    IPAddress getWiFiWsIPAdd();
    IPAddress getWiFiWsMaskAdd();
    IPAddress getWiFiWsGatAdd();
    IPAddress getWiFiWsDNS1Add();
    IPAddress getWiFiWsDNS2Add();

    String getWiFiApSsid();
    String getWiFiApPwd();
    String getWiFiApIP();
    String getWiFiApMask();
    String getWiFiApGateway();

    IPAddress getWiFiApIPAdd();
    IPAddress getWiFiApMaskAdd();
    IPAddress getWiFiApGatAdd();

    String getNtpTimeZone();
    String getNtpTimeZoneDayLight();
    String getGpsLongitude();
    String getGpsLatitude();
    String getConfigFull();
    String getConfigDefaultFull();
    __uint8_t get_connectedModeLast();
    bool get_readResetPin();

    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    /// @brief Beguin wifi according confituration reades, y fail then start as Acces point and show config page
    /// you need call on setup
    /// @return
    bool setup();
    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------

    /// @brief  call in your loop, at intervals update time from NTP server and
    //  calculate sunshine, sunset, momfase and if is daty
    void loop();

private:
    // AP for Access point mode

    int m_pinReset = -1;
    int m_WiFI_ConnectedModeLast = -1; //-1 not establised, 1=WS,2=AP
    long m_interval = 2000;
    long m_intervaPrevious = 0;
    long m_intervalCurrent = 0;

    String m_WiFI_AP_Ssid = "";
    String m_WiFI_AP_Pwd = "";
    IPAddress m_WiFI_AP_IP;
    IPAddress m_WiFI_AP_Mask;
    IPAddress m_WiFI_AP_Gateway;
    IPAddress m_WiFI_AP_DNS1;
    IPAddress m_WiFI_AP_DNS2;

    // WS Work station mode
    String m_WiFI_WS_Ssid = "";
    String m_WiFI_WS_Pwd = "";
    IPAddress m_WiFI_WS_IP;
    IPAddress m_WiFI_WS_Mask;
    IPAddress m_WiFI_WS_Gateway;
    IPAddress m_WiFI_WS_DNS1;
    IPAddress m_WiFI_WS_DNS2;
    //-----------------------------
    // default values for access point mode
    // m_WiFI_AP_Ssid_default  is buidl automatic
    // with "NewIOt" + four digits of  ESP.getEfuseMac()
    String m_WiFI_AP_Pwd_default = "123456789"; //=null
    IPAddress m_WiFI_AP_IP_default = {192, 168, 1, 1};
    IPAddress m_WiFI_AP_Mask_default = {255, 255, 255, 0};
    IPAddress m_WiFI_AP_Gateway_default = {192, 168, 1, 1};
    IPAddress m_WiFI_AP_DNS1_default = {192, 168, 1, 1};
    IPAddress m_WiFI_AP_DNS2_default = {192, 168, 1, 1};
    // default values for workstation mode
    String m_WiFI_WS_Ssid_default = "";
    String m_WiFI_WS_Pwd_default = "";
    IPAddress m_WiFI_WS_IP_default = {192, 168, 2, 254};
    IPAddress m_WiFI_WS_Mask_default = {255, 255, 255, 0};
    IPAddress m_WiFI_WS_Gateway_default = {192, 168, 2, 1};
    IPAddress m_WiFI_WS_DNS1_default = {8, 8, 8, 8};
    IPAddress m_WiFI_WS_DNS2_default = {8, 8, 4, 4};
    //-----------------------------
    const int m_NtpTimeZone_default = 1;
    int m_NtpTimeZone = m_NtpTimeZone_default;
    const int m_NtpTimeZoneDayLight_default = 1;
    int m_NtpTimeZoneDayLight = m_NtpTimeZoneDayLight_default;
    const double m_GpsLatitude_default = 40.4167;
    double m_GpsLatitude = m_GpsLatitude_default;
    const double m_GpsLongitude_default = -3.703228;
    double m_GpsLongitude = m_GpsLongitude_default;

    //-----------------------------

    bool connectAP();
    bool connectWS();
    bool configRead();
    // bool configSave();

    // each parameters is saved in diferent file path
    // each file only has one parameter
    const char *m_pathSsid = "/ssid.txt";
    const char *m_pathPass = "/pwd.txt";
    const char *m_pathIP = "/ip.txt";
    const char *m_pathMask = "/mask.txt";
    const char *m_pathGateway = "/gateway.txt";
    const char *m_pathDns1 = "/dns1.txt";
    const char *m_pathDns2 = "/dns2.txt";
    const char *m_pathTimeZone = "/timezone.txt";
    const char *m_pathTimeDayLight = "/timedaylight.txt";
    const char *m_pathLatitude = "/latitude.txt";
    const char *m_pathLongitude = "/longitude.txt";
    const char *m_pathPinReset = "/pinreset.txt";
    bool fncFileSpiffsInit();
    String fncFileReadValue(fs::FS &fs, const char *path);
    double fncFileReadValueDouble(fs::FS &fs, const char *path);
    void fncFileWriteValue(fs::FS &fs, const char *path, const char *value);
};
#endif