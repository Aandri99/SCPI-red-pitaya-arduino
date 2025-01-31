#include "aio.h"

#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_SAM)
#include <avr/dtostrf.h>
#endif

using namespace scpi_rp;

bool scpi_rp::setAIORst(BaseIO *io) {
  constexpr char cmd[] = "ANALOG:RST\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return true;
}

bool scpi_rp::setAIOValue(BaseIO *io, EAIOPin pin, float value) {
  auto writeState = [&](float value) {
    char buffer[8];
    dtostrf(value, 6, 3, buffer);
    if (!io->writeStr(buffer)) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    return io->writeStr(SCPI_COMMAND_SEPARATOR);
  };

  if (pin < AOUT_0 || pin > AOUT_3) return false;
  if (value < 0 || round(value * 10) > 18) return false;

  constexpr char cmd[] = "ANALOG:PIN ";
  char buffer[3];
  if (!io->writeStr(cmd)) {
    io->writeStr(SCPI_COMMAND_SEPARATOR);
    return false;
  }

  if (!io->writeStr("AOUT")) {
    io->writeStr(SCPI_COMMAND_SEPARATOR);
    return false;
  }
  itoa(pin - AOUT_0, buffer, 10);
  if (!io->writeStr(buffer)) {
    io->writeStr(SCPI_COMMAND_SEPARATOR);
    return false;
  }
  if (!io->writeStr(",")) {
    io->writeStr(SCPI_COMMAND_SEPARATOR);
    return false;
  }
  return writeState(value);
}

bool scpi_rp::getAIOValue(BaseIO *io, EAIOPin pin, float *_value) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *_value = atof(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };

  char buffer[3];
  constexpr char cmd[] = "ANALOG:PIN? ";
  if (!io->writeStr(cmd)) {
    io->writeStr(SCPI_COMMAND_SEPARATOR);
    return false;
  }

  if (pin <= AIN_3) {
    if (!io->writeStr("AIN")) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    itoa(pin, buffer, 10);
    if (!io->writeStr(buffer)) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    io->writeStr(SCPI_COMMAND_SEPARATOR);
    return readValue();
  }

  if (pin >= AOUT_0 && pin <= AOUT_3) {
    if (!io->writeStr("AOUT")) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    itoa(pin - AOUT_0, buffer, 10);
    if (!io->writeStr(buffer)) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    io->writeStr(SCPI_COMMAND_SEPARATOR);
    return readValue();
  }
  return false;
}
