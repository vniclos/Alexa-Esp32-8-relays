
#ifndef CLSRELAY_H
#define CLSRELAY_H
#include <Arduino.h>
#include "ClsProgramation.h"

#define RELAY_OFF 1
#define RELAY_ON 0

class ClsRelay
{
public:
  ClsRelay();
  void attach(uint8_t m_id, uint8_t pin);
  void attach(uint8_t m_id, uint8_t pin, String Name);
  String name();
  void Name(String Name);
  void loop();
  ClsProgramation m_programation;
  uint8_t PrgStatusGet();

private:
  uint8_t m_id = 0;
  uint8_t m_pin = 0;
  String m_Name;

};
#endif
