#include <stdio.h>
#include <string.h>
#include "base_io.h"
#include "Arduino.h"

/**
 * Default constructor - setting all variabels to default values
 */
BaseIO::BaseIO()
{

}

bool BaseIO::cls(uint32_t _timeout_ms)
{
  constexpr uint8_t command[] = {"*CLS"};
  auto sendSize = strlen((const char*)command);
  auto size = write(command, sendSize,_timeout_ms);
  return size == (sendSize + 2);
}

bool BaseIO::ese(int _value, uint32_t _timeout_ms)
{
  constexpr uint8_t command[] = {"*ESE {%d}"};
  char buffer[18];
  sprintf(buffer, (const char*)command, _value);
  auto sendSize = strlen((const char*)buffer);
  auto size = write((const uint8_t*)buffer, sendSize,_timeout_ms);
  return size == (sendSize + 2);
}

const ReadData BaseIO::ese_q(uint32_t _timeout_ms)
{
  constexpr uint8_t command[] = {"*ESE?"};
  auto sendSize = strlen((const char*)command);
  auto size = write(command, sendSize,_timeout_ms);
  if (size != (sendSize + 2)){
    return ReadData();
  }
  return read(_timeout_ms);
}

const ReadData BaseIO::esr_q(uint32_t _timeout_ms)
{
  constexpr uint8_t command[] = {"*ESR?"};
  auto sendSize = strlen((const char*)command);
  auto size = write(command, sendSize,_timeout_ms);
  if (size != (sendSize + 2)){
    return ReadData();
  }
  return read(_timeout_ms);
}

const ReadData BaseIO::idn_q(uint32_t _timeout_ms)
{
  constexpr uint8_t command[] = {"*IDN?"};
  auto sendSize = strlen((const char*)command);
  auto size = write(command, sendSize,_timeout_ms);
  if (size != (sendSize + 2)){
    return ReadData();
  }
  return read(_timeout_ms);
}

bool BaseIO::opc(uint32_t _timeout_ms)
{
  constexpr uint8_t command[] = {"*OPC"};
  auto sendSize = strlen((const char*)command);
  auto size = write(command, sendSize,_timeout_ms);
  return size == (sendSize + 2);
}

const ReadData BaseIO::opc_q(uint32_t _timeout_ms)
{
  constexpr uint8_t command[] = {"*OPC?"};
  auto sendSize = strlen((const char*)command);
  auto size = write(command, sendSize,_timeout_ms);
  if (size != (sendSize + 2)){
    return ReadData();
  }
  return read(_timeout_ms);
}

bool BaseIO::rst(uint32_t _timeout_ms)
{
  constexpr uint8_t command[] = {"*RST"};
  auto sendSize = strlen((const char*)command);
  auto size = write(command, sendSize,_timeout_ms);
  return size == (sendSize + 2);
}

bool BaseIO::sre(int _value, uint32_t _timeout_ms)
{
  constexpr uint8_t command[] = {"*SRE {%d}"};
  char buffer[18];
  sprintf(buffer, (const char*)command, _value);
  auto sendSize = strlen((const char*)buffer);
  auto size = write((const uint8_t*)buffer, sendSize,_timeout_ms);
  return size == (sendSize + 2);
}

const ReadData BaseIO::sre_q(uint32_t _timeout_ms)
{
  constexpr uint8_t command[] = {"*SRE?"};
  auto sendSize = strlen((const char*)command);
  auto size = write(command, sendSize,_timeout_ms);
  if (size != (sendSize + 2)){
    return ReadData();
  }
  return read(_timeout_ms);
}

const ReadData BaseIO::stb_q(uint32_t _timeout_ms)
{
  constexpr uint8_t command[] = {"*STB?"};
  auto sendSize = strlen((const char*)command);
  auto size = write(command, sendSize,_timeout_ms);
  if (size != (sendSize + 2)){
    return ReadData();
  }
  return read(_timeout_ms);
}

const ReadData BaseIO::err_c(uint32_t _timeout_ms)
{
  constexpr uint8_t command[] = {"SYST:ERR:COUN?"};
  auto sendSize = strlen((const char*)command);
  auto size = write(command, sendSize,_timeout_ms);
  if (size != (sendSize + 2)){
    return ReadData();
  }
  return read(_timeout_ms);
}

const ReadData BaseIO::err_n(uint32_t _timeout_ms)
{
  constexpr uint8_t command[] = {"SYST:ERR:NEXT?"};
  auto sendSize = strlen((const char*)command);
  auto size = write(command, sendSize,_timeout_ms);
  if (size != (sendSize + 2)){
    return ReadData();
  }
  return read(_timeout_ms);
}

// function buffering delay()
// arduino uno function doesn't work well with interrupts
void BaseIO::_delay(unsigned long ms){
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328PB__)  || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__)
  // if arduino uno and other atmega328p chips
  // use while instad of delay,
  // due to wrong measurement based on changed timer0
  unsigned long t = _micros() + ms*1000;
  while( _micros() < t ){};
#else
  // regular micros
  delay(ms);
#endif
}


// function buffering _micros()
// arduino function doesn't work well with interrupts
unsigned long BaseIO::_micros(){
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328PB__)  || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__)
    // if arduino uno and other atmega328p chips
    //return the value based on the prescaler
    if((TCCR0B & 0b00000111) == 0x01) return (micros()/32);
    else return (micros());
#else
  // regular micros
  return micros();
#endif
}