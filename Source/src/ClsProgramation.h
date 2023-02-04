
#ifndef CLSpROGRAMATION_H
#define CLSpROGRAMATION_H
#include "Arduino.h"
#define RELAY_OFF 1
#define RELAY_ON 0
class ClsProgramation
{
public:
    ClsProgramation();

    void setupFixed_OFF();
    void setupFixed_ON();
    void setupIntervalRandon(uint32_t IntervalRandonMin, uint32_t IntervalRandonMax);
    void setupIntevalFixed(uint32_t interval);

    int CalculateNewStatus( );
    uint8_t getProgramationMode();
    uint32_t getRelayIntervalPrevious();

    bool getIsInInterval();
    bool getRelayStatus();
    uint32_t getInterval();
    uint32_t getIntervalSteep();

    void setPinRelay(int8_t pin);
    void setStatusRelay(bool RelayStatus);
    void setRelayIntervalPrevious(uint32_t relayIntervalPrevious);
   
   

private:
    int8_t m_pin = 0;
    uint8_t m_ProgramationMode = 0; // 0=fixed 1 Randon
    uint32_t m_IntervalSteep = 0;

    uint32_t m_IntervalSteepRandonMin = 5;
    uint32_t m_IntervalSteepRandonMax = 10;

    uint32_t m_RelayIntervalPrevious = 0;
    bool m_RelayStatus = 0;
    void clear();
    bool isInInterval();

};
#endif
