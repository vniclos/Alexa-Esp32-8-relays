
#ifndef CLSRELAY_H
#define CLSRELAY_H
#include "Arduino.h"
#include <iostream>
#include <string>


class ClsRelay
{
public:
  ClsRelay();
  /// @brief enum {ON_DAY, ON_NIGHT, ON_ALWAIS, OFF_ALWAYS};
  enum eProgramationTime
  {
    ON_DAY,
    ON_NIGHT,
    ON_ALWAIS,
    OFF_ALWAYS
  };
  const char *eProgramationTimeString[4] = {"ON_DAY", "ON_NIGHT", "ON_ALWAIS", "OFF_ALWAYS"};
  String getProgramationTimeToString(int val);
  /// @brief enum {FIXED_ON, FIXED_OFF, FLASH_FIXED, FLASH_RANDON};
  enum eProgramationMode
  {
    FIXED_ON,
    FLASH_FIXED,
    FLASH_RANDON
  };
  const char *eProgramationModeString[4] = {"FIXED_ON", "FLASH_FIXED", "FLASH_RANDON"};
  String getProgramationModeToString(int val);
  //  int8_t m_idRelay = 0;

  /// @brief take default all default values
  /// programationMode, ProgramationTime, and intervalvals for flashing
  // void setup(int idRelay, int pin, String Name);
  void setup(int idRelay, int pin, String Name, eProgramationMode programtionMode, eProgramationTime programtionTime);
  void setIntervalRandon(uint32_t IntervalRandonMin, uint32_t IntervalRandonMax);
  void setIntevalFixed(uint32_t intervalFixed);

  void setProgramationTime_OnDay();
  void setProgramationTime_OnNight();
  void setProgramationTime_OnAlways();
  void setProgramationTime_OffAlways(

  );
  void setProgramationMode_Fixed_ON();
  void setProgramationMode_FlashingFixed();
  void setProgramationMode_FlashingRandon();

  void setJsonProgramation(String name, eProgramationMode programtionMode, eProgramationTime programtionTime);
  String getJsonProgramation();
  String fncJsonAdd(String name, String value);

  int getRelayStatus();

  String getProgramationMode();
  String getProgramationTime();
  uint32_t getRelayIntervalPrevious();

  bool getIsInInterval();

  uint32_t getInterval_InUse();
  uint32_t getIntervalFixed();
  uint32_t getIntervalRandoMin();
  uint32_t getIntervalRandonMax();

  void setPinRelay(int8_t pin);
  void setRelayIntervalPrevious(uint32_t relayIntervalPrevious);
  int loop(bool isDayLight);

  eProgramationMode m_ProgramationMode = FIXED_ON; // FIXED_ON,  FLASH_FIXED, FLASH_RANDON};
  eProgramationTime m_ProgramationTime = ON_DAY;   //{ON_DAY, ON_NIGHT, ON_ALWAIS, OFF_ALWAYS};

private:
  const uint8_t RELAY_ON = LOW;
  const uint8_t RELAY_OFF = HIGH;
  int CalculateStatusMode();
  bool m_isDayLight = false; // last daylisght set by function CalculateStatusMode

  eProgramationMode m_ProgramationMode_default = FLASH_FIXED;
  eProgramationTime m_ProgramationTime_default = ON_DAY;
  uint32_t m_IntervalRandonMin_default=1000;
  uint32_t m_IntervalRandonMax_default=5000;
  String m_Name;
  int m_idRelay = 0;
  int m_pin = 0;

  uint32_t m_Interval_InUse = 0; // may be =m_intervalFixed or betwen [m_IntervalRandonMin ... m_IntervalRandonMax]
  uint32_t m_intervalFixed = 2000;
  uint32_t m_IntervalRandonMin = 2000;
  uint32_t m_IntervalRandonMax = 10000;

  uint32_t m_RelayIntervalPrevious = 0;
  bool m_RelayStatus = 0;
  void clear();
  bool isInInterval();
};
#endif
