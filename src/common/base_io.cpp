#include "base_io.h"
#include "Arduino.h"
#include <stdio.h>
#include <string.h>

using namespace scpi_rp;

BaseIO::BaseIO() {
  m_bufferSize = 0;
  m_bufferReadPos = 0;
}

BaseIO::~BaseIO() {}

// bool BaseIO::cls() {
//   constexpr uint8_t command[] = {"*CLS"};
//   auto sendSize = strlen((const char *)command);
//   auto size = write(command, sendSize);
//   return size == (sendSize + 2);
// }

// bool BaseIO::ese(int _value) {
//   constexpr uint8_t command[] = {"*ESE {%d}"};
//   char buffer[18];
//   sprintf(buffer, (const char *)command, _value);
//   auto sendSize = strlen((const char *)buffer);
//   auto size = write((const uint8_t *)buffer, sendSize);
//   return size == (sendSize + 2);
// }

// const ReadData BaseIO::ese_q() {
//   constexpr uint8_t command[] = {"*ESE?"};
//   auto sendSize = strlen((const char *)command);
//   auto size = write(command, sendSize);
//   if (size != (sendSize + 2)) {

//     return ReadData();
//   }
//   return read();
// }

// const ReadData BaseIO::esr_q() {
//   constexpr uint8_t command[] = {"*ESR?"};
//   auto sendSize = strlen((const char *)command);
//   auto size = write(command, sendSize);
//   if (size != (sendSize + 2)) {
//     return ReadData();
//   }
//   return read();
// }

// const ReadData BaseIO::idn_q() {
//   constexpr uint8_t command[] = {"*IDN?"};
//   auto sendSize = strlen((const char *)command);
//   auto size = write(command, sendSize);
//   if (size != (sendSize + 2)) {
//     return ReadData();
//   }
//   return read();
// }

// bool BaseIO::opc() {
//   constexpr uint8_t command[] = {"*OPC"};
//   auto sendSize = strlen((const char *)command);
//   auto size = write(command, sendSize);
//   return size == (sendSize + 2);
// }

// const ReadData BaseIO::opc_q() {
//   constexpr uint8_t command[] = {"*OPC?"};
//   auto sendSize = strlen((const char *)command);
//   auto size = write(command, sendSize);
//   if (size != (sendSize + 2)) {
//     return ReadData();
//   }
//   return read();
// }

// bool BaseIO::rst() {
//   constexpr uint8_t command[] = {"*RST"};
//   auto sendSize = strlen((const char *)command);
//   auto size = write(command, sendSize);
//   return size == (sendSize + 2);
// }

// bool BaseIO::sre(int _value) {
//   constexpr uint8_t command[] = {"*SRE {%d}"};
//   char buffer[18];
//   sprintf(buffer, (const char *)command, _value);
//   auto sendSize = strlen((const char *)buffer);
//   auto size = write((const uint8_t *)buffer, sendSize);
//   return size == (sendSize + 2);
// }

// const ReadData BaseIO::sre_q() {
//   constexpr uint8_t command[] = {"*SRE?"};
//   auto sendSize = strlen((const char *)command);
//   auto size = write(command, sendSize);
//   if (size != (sendSize + 2)) {
//     return ReadData();
//   }
//   return read();
// }

// const ReadData BaseIO::stb_q() {
//   constexpr uint8_t command[] = {"*STB?"};
//   auto sendSize = strlen((const char *)command);
//   auto size = write(command, sendSize);
//   if (size != (sendSize + 2)) {
//     return ReadData();
//   }
//   return read();
// }

// const ReadData BaseIO::err_c() {
//   constexpr uint8_t command[] = {"SYST:ERR:COUN?"};
//   auto sendSize = strlen((const char *)command);
//   auto size = write(command, sendSize);
//   if (size != (sendSize + 2)) {
//     return ReadData();
//   }
//   return read();
// }

// const ReadData BaseIO::err_n() {
//   constexpr uint8_t command[] = {"SYST:ERR:NEXT?"};
//   auto sendSize = strlen((const char *)command);
//   auto size = write(command, sendSize);
//   if (size != (sendSize + 2)) {
//     return ReadData();
//   }
//   return read();
// }

// function buffering delay()
// arduino uno function doesn't work well with interrupts
void BaseIO::_delay(unsigned long ms) {
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__) ||               \
    defined(__AVR_ATmega328PB__) || defined(__AVR_ATmega2560__) ||             \
    defined(__AVR_ATmega32U4__)
  // if arduino uno and other atmega328p chips
  // use while instad of delay,
  // due to wrong measurement based on changed timer0
  unsigned long t = _micros() + ms * 1000;
  while (_micros() < t) {
  };
#else
  // regular micros
  delay(ms);
#endif
}

// function buffering _micros()
// arduino function doesn't work well with interrupts
unsigned long BaseIO::_micros() {
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__) ||               \
    defined(__AVR_ATmega328PB__) || defined(__AVR_ATmega2560__) ||             \
    defined(__AVR_ATmega32U4__)
  // if arduino uno and other atmega328p chips
  // return the value based on the prescaler
  if ((TCCR0B & 0b00000111) == 0x01)
    return (micros() / 32);
  else
    return (micros());
#else
  // regular micros
  return micros();
#endif
}

int BaseIO::checkParamSeparator() {
  for (scpi_size i = m_bufferReadPos; i < m_bufferSize; i++) {
    if (m_buffer[i] == SCPI_PARAM_SEPARATOR) {
      return i;
    }
  }
  return -1;
}

int BaseIO::checkCommandSeparator() {
  for (scpi_size i = m_bufferReadPos; i < m_bufferSize - 1 && m_bufferSize > 0;
       i++) {
    if (m_buffer[i] == SCPI_COMMAND_SEPARATOR[0] &&
        m_buffer[i + 1] == SCPI_COMMAND_SEPARATOR[1]) {
      return i;
    }
  }
  return -1;
}

int BaseIO::fillBuffer() {
  int end = -1;
  while (end == -1) {
    end = checkParamSeparator();
    if (end == -1) {
      end = checkCommandSeparator();
    }
    if (end == -1) {
      scpi_size ret = readToBuffer();
      if (ret == 0) {
        return -1;
      }
    }
  }
  return end;
}

const Value BaseIO::readStr() {
  Value value;
  int end = fillBuffer();
  if (end == -1)
    return value;
  if (m_buffer[m_bufferReadPos] == "\"" && m_buffer[end - 1] == "\"") {
    m_buffer[end - 1] = '\0';
    value.value = m_buffer + m_bufferReadPos + 1;
    value.size = end - m_bufferReadPos;
    value.isValid = true;
    value.next_value = m_buffer[end] == "," ? end + 1 : end + 2;
  }
  return value;
}

const Value BaseIO::read() {
  Value value;
  int end = fillBuffer();
  if (end == -1)
    return value;
  m_buffer[end] = '\0';
  value.value = m_buffer + m_bufferReadPos;
  value.size = end - m_bufferReadPos;
  value.isValid = true;
  value.next_value = m_buffer[end] == "," ? end + 1 : end + 2;
  return value;
}

bool BaseIO::writeStr(const char *_data) {
  scpi_size len = strlen((char *)_data);
  if (write(_data, len) != len) {
    return false;
  }
  return true;
}

void BaseIO::flush() {
  m_bufferSize = 0;
  m_bufferReadPos = 0;
}

void BaseIO::flushCommand(scpi_size value) {
  int next_block = value;
  if (m_bufferSize <= next_block) {
    flush();
    return;
  }
  memmove(m_buffer, m_buffer + next_block, m_bufferSize - next_block);
  m_bufferReadPos = 0;
  m_bufferSize = m_bufferSize - next_block;
}
